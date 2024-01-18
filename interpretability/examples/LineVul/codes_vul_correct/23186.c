// commit message qemu@faab207f11 (target=1, prob=0.999154, correct=True): 9pfs: fix fd leak in local_opendir()
/*0  */ static int local_opendir(FsContext *ctx,                           // (3) 0.065
/*2  */                          V9fsPath *fs_path, V9fsFidOpenState *fs)  // (0) 0.215
/*4  */ {                                                                  // (15) 0.005
/*6  */     int dirfd;                                                     // (10) 0.035
/*8  */     DIR *stream;                                                   // (8) 0.04
/*12 */     dirfd = local_opendir_nofollow(ctx, fs_path->data);            // (1) 0.12
/*14 */     if (dirfd == -1) {                                             // (4) 0.06
/*16 */         return -1;                                                 // (6) 0.055
/*18 */     }                                                              // (13) 0.02
/*22 */     stream = fdopendir(dirfd);                                     // (2) 0.07
/*24 */     if (!stream) {                                                 // (9) 0.04
/*27 */         return -1;                                                 // (7) 0.055
/*29 */     }                                                              // (12) 0.02
/*31 */     fs->dir.stream = stream;                                       // (5) 0.055
/*33 */     return 0;                                                      // (11) 0.03
/*35 */ }                                                                  // (14) 0.005
