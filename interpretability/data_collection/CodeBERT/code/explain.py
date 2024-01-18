
import json
import time
import pickle
import pandas as pd



from codebert_explainer import CodebertModel, Arg
# from linevul_explainer import LineVulModelExplainer, Args
from lit_nlp.components import gradient_maps


start_time = time.time()




def get_data(file_path='../data/big-vul_dataset/test.csv', top_x=3):
  df = pd.read_csv(file_path)
  funcs = df["func"].tolist()
  labels = df["target"].tolist()
  input = []
  for i in range(len(funcs)):
    input.append({
        'sentence': funcs[i],
        'label': labels[i]
    })
  return input


inputs = get_data(file_path='<ANONYMOUS>/<ANONYMOUS>/data/devign/test.csv')


# from lit_nlp.components import lime_explainer
# lime = lime_explainer.LIME()


# lime_results = lime.run(inputs, model, inputs)
args = Arg()
print(args)
model = CodebertModel()
model.load_model(args)
# model.activate_evaluation()
print(model.output_spec())


ig = gradient_maps.IntegratedGradients()

print("Input Data size: ", len(inputs))
ig_results = []
for i in range(0, len(inputs), 128):
  ig_results += ig.run(inputs[i : i + 128], model, inputs)
  print("Finished from {} to {}, result length {}".format(i, i + 128, len(ig_results)))
print("Finished ", len(ig_results))
pickle.dump(ig_results,open('explanation_devign.pkl', 'wb'))
pickle.dump(ig_results,open('./results/explanation_devign.pkl', 'wb'))
print("Explanation DOne for {}".format(len(ig_results)))
