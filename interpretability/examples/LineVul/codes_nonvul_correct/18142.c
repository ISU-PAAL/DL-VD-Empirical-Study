// commit message qemu@2c30dd744a (target=0, prob=0.008467269, correct=True): hw/9pfs: Add new security model mapped-file.
/*0  */ static int local_readdir_r(FsContext *ctx, V9fsFidOpenState *fs,  // (2) 0.2051
/*2  */                            struct dirent *entry,                  // (0) 0.2735
/*4  */                            struct dirent **result)                // (1) 0.2735
/*6  */ {                                                                 // (4) 0.008547
/*8  */     return readdir_r(fs->dir, entry, result);                     // (3) 0.1453
/*10 */ }                                                                 // (5) 0.008547
