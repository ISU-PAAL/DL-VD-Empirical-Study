// commit message qemu@12848bfc5d (target=1, prob=0.619337, correct=True): virtio-9p: Add SM_NONE security model
/*0  */ static int local_open2(FsContext *fs_ctx, const char *path, int flags,  // (6) 0.04297
/*2  */         FsCred *credp)                                                  // (10) 0.03125
/*4  */ {                                                                       // (29) 0.001953
/*6  */     int fd = -1;                                                        // (21) 0.01953
/*8  */     int err = -1;                                                       // (23) 0.01758
/*10 */     int serrno = 0;                                                     // (22) 0.01953
/*14 */     /* Determine the security model */                                  // (20) 0.01953
/*16 */     if (fs_ctx->fs_sm == SM_MAPPED) {                                   // (7) 0.03906
/*18 */         fd = open(rpath(fs_ctx, path), flags, SM_LOCAL_MODE_BITS);      // (0) 0.06445
/*20 */         if (fd == -1) {                                                 // (14) 0.0293
/*22 */             return fd;                                                  // (15) 0.0293
/*24 */         }                                                               // (24) 0.01562
/*26 */         credp->fc_mode = credp->fc_mode|S_IFREG;                        // (4) 0.05078
/*28 */         /* Set cleint credentials in xattr */                           // (11) 0.03125
/*30 */         err = local_set_xattr(rpath(fs_ctx, path), credp);              // (3) 0.05469
/*32 */         if (err == -1) {                                                // (16) 0.0293
/*34 */             serrno = errno;                                             // (8) 0.03516
/*36 */             goto err_end;                                               // (12) 0.03125
/*38 */         }                                                               // (25) 0.01562
/*40 */     } else if (fs_ctx->fs_sm == SM_PASSTHROUGH) {                       // (5) 0.04688
/*42 */         fd = open(rpath(fs_ctx, path), flags, credp->fc_mode);          // (1) 0.05859
/*44 */         if (fd == -1) {                                                 // (17) 0.0293
/*46 */             return fd;                                                  // (18) 0.0293
/*48 */         }                                                               // (26) 0.01562
/*50 */         err = local_post_create_passthrough(fs_ctx, path, credp);       // (2) 0.05469
/*52 */         if (err == -1) {                                                // (19) 0.0293
/*54 */             serrno = errno;                                             // (9) 0.03516
/*56 */             goto err_end;                                               // (13) 0.03125
/*58 */         }                                                               // (27) 0.01562
/*60 */     }                                                                   // (28) 0.007812
/*62 */     return fd;                                                          // 0.0
/*66 */ err_end:                                                                // 0.0
/*68 */     close(fd);                                                          // 0.0
/*70 */     remove(rpath(fs_ctx, path));                                        // 0.0
/*72 */     errno = serrno;                                                     // 0.0
/*74 */     return err;                                                         // 0.0
/*76 */ }                                                                       // 0.0
