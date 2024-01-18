// commit message qemu@364031f179 (target=0, prob=0.005576418, correct=True): 9pfs: rename virtio-9p-synth.{c,h} to 9p-synth.{c,h}
/*0  */ static int v9fs_synth_lstat(FsContext *fs_ctx,                      // (3) 0.1473
/*2  */                             V9fsPath *fs_path, struct stat *stbuf)  // (0) 0.3256
/*4  */ {                                                                   // (5) 0.007752
/*6  */     V9fsSynthNode *node = *(V9fsSynthNode **)fs_path->data;         // (1) 0.2171
/*10 */     v9fs_synth_fill_statbuf(node, stbuf);                           // (2) 0.155
/*12 */     return 0;                                                       // (4) 0.04651
/*14 */ }                                                                   // (6) 0.007752
