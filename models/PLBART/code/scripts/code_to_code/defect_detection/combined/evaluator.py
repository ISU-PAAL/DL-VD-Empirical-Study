import argparse
import math
import torch
import numpy as np
from tqdm import tqdm
from sklearn.metrics import classification_report
from fairseq.data import data_utils
from fairseq.models.bart import BARTModel


# https://github.com/pytorch/fairseq/blob/108f7204f6ccddb676e6d52006da219ce96a02dc/fairseq/models/bart/hub_interface.py#L33
def encode(model, sentence, max_positions=512):
    tokens = sentence
    if len(tokens.split(" ")) > max_positions - 2:
        tokens = " ".join(tokens.split(" ")[: max_positions - 2])
    bpe_sentence = "<s> " + tokens + " </s>"
    tokens = model.task.source_dictionary.encode_line(
        bpe_sentence, add_if_not_exist=False, append_eos=False
    )
    return tokens.long()


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--model_dir', required=True)
    parser.add_argument('--user_dir', default=None)
    parser.add_argument('--model_name', required=True)
    parser.add_argument('--csv_filename', required=True)
    parser.add_argument('--data_bin_path', required=True)
    parser.add_argument('--input_file', required=True)
    parser.add_argument('--output', default='result.txt')
    parser.add_argument('--label_file', required=True)
    parser.add_argument('--classification_head_name', default='sentence_classification_head')
    parser.add_argument('--batch_size', default=32, type=int)
    parser.add_argument('--max_example', default=-1, type=int)
    args = parser.parse_args()
    print("csv_filesname: " + args.csv_filename)
    bart = BARTModel.from_pretrained(
        args.model_dir,
        checkpoint_file=args.model_name,
        data_name_or_path=args.data_bin_path,
        user_dir=args.user_dir,
        task="plbart_sentence_prediction",
    )

    label_fn = lambda label: bart.task.label_dictionary.string(
        [label + bart.task.label_dictionary.nspecial]
    )

    bart.cuda()
    bart.eval()
    ncorrect, nsamples = 0.0, 0.0
    y_true, y_pred, y_prob = [], [], []
    from scipy.special import softmax
    #prediction_prob = []
    with open(args.input_file) as inpf, open(args.label_file) as labelf, open(args.output, 'w') as outp:
        inputs = inpf.readlines()
        labels = labelf.readlines()
        if args.max_example != -1 and args.max_example > 0:
            inputs = inputs[:args.max_example]
            labels = labels[:args.max_example]

        total_batches = int(math.ceil(len(inputs) / args.batch_size))
        start = 0
        start_indices = np.arange(0, len(inputs), args.batch_size)
        for start in tqdm(start_indices, total=total_batches):
            batch_input = []
            batch_targets = []
            batch_size = args.batch_size if start + args.batch_size <= len(inputs) \
                else len(inputs) - start
            for idx in range(start, start + batch_size):
                line = inputs[idx].strip()
                label = int(labels[idx])
                tokens = encode(bart, line)
                batch_input.append(tokens)
                batch_targets.append(label)
            
            y_true.extend(batch_targets)
            with torch.no_grad():
                batch_input = data_utils.collate_tokens(
                    batch_input, bart.model.encoder.dictionary.pad(), left_pad=False
                )
                prediction = bart.predict(args.classification_head_name, batch_input)
                #prediction_prob += prediction

                y_prob.extend(softmax(prediction.cpu().numpy().tolist(), axis=1)[:,1])
                prediction = prediction.argmax(dim=1).cpu().numpy().tolist()
                
                prediction = [int(label_fn(p)) for p in prediction]
                y_pred.extend(prediction)
                ncorrect += sum([int(p == t) for p, t in zip(prediction, batch_targets)])
                nsamples += len(prediction)
                log = ['{}\t{}'.format(p, t) for p, t in zip(prediction, batch_targets)]
                # outp.write('\n'.join(log) + '\n')

        import pandas as pd
        output_csv = {'Pred': y_pred, 'Prob': y_prob, 'Target': y_true}
        df_csv = pd.DataFrame(output_csv)
        #breakpoint()
        df_csv.to_csv(args.csv_filename + '.csv', index=False)
        assert len(inputs) == nsamples
        acc = round(100.0 * ncorrect / nsamples, 3)
        print('Accuracy: ', acc)
        outp.write('Accuracy: ' + str(acc) + '\n')
        target_names = ['0', '1']
        report = classification_report(y_true, y_pred, target_names=target_names, digits=3)
        import sklearn.metrics
        print('\nAccuracy: '+ str(sklearn.metrics.accuracy_score(y_true, y_pred)))
        print('Precision: '+ str(sklearn.metrics.precision_score(y_true, y_pred)))
        print('F-measure: '+ str(sklearn.metrics.f1_score(y_true, y_pred)))
        print('Recall: '+ str(sklearn.metrics.recall_score(y_true, y_pred)))
        
        print(report)
        outp.write(report + '\n')
