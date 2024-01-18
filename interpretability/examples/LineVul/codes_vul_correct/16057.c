// commit message qemu@ac125d993b (target=1, prob=0.95677316, correct=True): 9pfs: local: truncate: don't follow symlinks
/*0  */ static int local_truncate(FsContext *ctx, V9fsPath *fs_path, off_t size)  // (0) 0.2477
/*2  */ {                                                                         // (8) 0.009174
/*4  */     char *buffer;                                                         // (5) 0.06422
/*6  */     int ret;                                                              // (6) 0.05505
/*8  */     char *path = fs_path->data;                                           // (1) 0.1193
/*12 */     buffer = rpath(ctx, path);                                            // (2) 0.1101
/*14 */     ret = truncate(buffer, size);                                         // (3) 0.1101
/*16 */     g_free(buffer);                                                       // (4) 0.08257
/*18 */     return ret;                                                           // (7) 0.05505
/*20 */ }                                                                         // (9) 0.009174
