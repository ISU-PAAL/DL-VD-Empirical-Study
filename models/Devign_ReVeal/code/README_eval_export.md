This is one example in eval_export.json.
* Each example in the dataset has a unique sequential id in `index`.
* `split` is the dataset split from which the example came from.
* `correct` is true/false whether the example was correctly predicted by the model.
* `prediction` is the binary 0/1 prediction made by the model.
* `target` is the ground truth label of the dataset.
* `prob` is the probability predicted by the model whether the example is 1 or 0.

```
{
  "index": 14749.0,
  "split": "train",
  "correct": true,
  "prediction": 0,
  "target": 0.0,
  "prob": 8.072679962568216e-23
},
```

Devign dataset exports a file called `data/line_ggnn/devign/v1/eval_export.json`. This file holds the source code of the dataset examples.
The actual indices of the examples in this file correspond to the `index` field in eval_export.json. Here is the first example from the file for your reference.
```
{
  "code": "static int tight_compress_data(VncState *vs, int stream_id, size_t bytes,\n                                int level, int strategy)\n {\n     z_streamp zstream = &vs->tight.stream[stream_id];\n     int previous_out;\n     if (bytes < VNC_TIGHT_MIN_TO_COMPRESS) {\n         vnc_write(vs, vs->tight.tight.buffer, vs->tight.tight.offset);\n         return bytes;\n     }\n     if (tight_init_stream(vs, stream_id, level, strategy)) {\n         return -1;\n     }\n     /* reserve memory in output buffer */\n     buffer_reserve(&vs->tight.zlib, bytes + 64);\n     /* set pointers */\n     zstream->next_in = vs->tight.tight.buffer;\n     zstream->avail_in = vs->tight.tight.offset;\n     zstream->next_out = vs->tight.zlib.buffer + vs->tight.zlib.offset;\n     zstream->avail_out = vs->tight.zlib.capacity - vs->tight.zlib.offset;\n     zstream->data_type = Z_BINARY;\n     previous_out = zstream->total_out;\n     /* start encoding */\n     if (deflate(zstream, Z_SYNC_FLUSH) != Z_OK) {\n         fprintf(stderr, \"VNC: error during tight compression\\n\");\n         return -1;\n     }\n     vs->tight.zlib.offset = vs->tight.zlib.capacity - zstream->avail_out;\n     bytes = zstream->total_out - previous_out;\n     tight_send_compact_size(vs, bytes);\n     vnc_write(vs, vs->tight.zlib.buffer, bytes);\n     buffer_reset(&vs->tight.zlib);\n     return bytes;\n }",
  "label": 1,
  "file_name": "21396_qemu_2caa9e9d2e0f356cc244bc41ce1d3e81663f6782_1.c"
},
```