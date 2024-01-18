// commit message qemu@b97400caef (target=0, prob=0.113719106, correct=True): hw/9pfs: Use export flag for indicating security model
/*0  */ static int local_lstat(FsContext *fs_ctx, V9fsPath *fs_path, struct stat *stbuf)  // (5) 0.05664
/*2  */ {                                                                                 // (24) 0.001953
/*4  */     int err;                                                                      // (22) 0.01172
/*6  */     char buffer[PATH_MAX];                                                        // (17) 0.01953
/*8  */     char *path = fs_path->data;                                                   // (16) 0.02539
/*12 */     err =  lstat(rpath(fs_ctx, path, buffer), stbuf);                             // (8) 0.04492
/*14 */     if (err) {                                                                    // (19) 0.01562
/*16 */         return err;                                                               // (18) 0.01953
/*18 */     }                                                                             // (23) 0.007812
/*20 */     if (fs_ctx->fs_sm == SM_MAPPED) {                                             // (10) 0.03906
/*22 */         /* Actual credentials are part of extended attrs */                       // (11) 0.0332
/*24 */         uid_t tmp_uid;                                                            // (13) 0.0293
/*26 */         gid_t tmp_gid;                                                            // (12) 0.03125
/*28 */         mode_t tmp_mode;                                                          // (14) 0.02734
/*30 */         dev_t tmp_dev;                                                            // (15) 0.02734
/*32 */         if (getxattr(rpath(fs_ctx, path, buffer), "user.virtfs.uid", &tmp_uid,    // (1) 0.07227
/*34 */                     sizeof(uid_t)) > 0) {                                         // (6) 0.05664
/*36 */             stbuf->st_uid = tmp_uid;                                              // (9) 0.04297
/*38 */         }                                                                         // (20) 0.01562
/*40 */         if (getxattr(rpath(fs_ctx, path, buffer), "user.virtfs.gid", &tmp_gid,    // (0) 0.07617
/*42 */                     sizeof(gid_t)) > 0) {                                         // (4) 0.05859
/*44 */             stbuf->st_gid = tmp_gid;                                              // (7) 0.04688
/*46 */         }                                                                         // (21) 0.01562
/*48 */         if (getxattr(rpath(fs_ctx, path, buffer), "user.virtfs.mode",             // (3) 0.0625
/*50 */                     &tmp_mode, sizeof(mode_t)) > 0) {                             // (2) 0.06641
/*52 */             stbuf->st_mode = tmp_mode;                                            // 0.0
/*54 */         }                                                                         // 0.0
/*56 */         if (getxattr(rpath(fs_ctx, path, buffer), "user.virtfs.rdev", &tmp_dev,   // 0.0
/*58 */                         sizeof(dev_t)) > 0) {                                     // 0.0
/*60 */                 stbuf->st_rdev = tmp_dev;                                         // 0.0
/*62 */         }                                                                         // 0.0
/*64 */     }                                                                             // 0.0
/*66 */     return err;                                                                   // 0.0
/*68 */ }                                                                                 // 0.0
