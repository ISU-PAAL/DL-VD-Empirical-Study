// commit message qemu@4ed7b2c3a7 (target=1, prob=0.7600894, correct=True): virtio: Fix memory leaks reported by Coverity
/*0   */ static int local_open2(FsContext *fs_ctx, V9fsPath *dir_path, const char *name,  // (2) 0.05469
/*2   */                        int flags, FsCred *credp, V9fsFidOpenState *fs)           // (0) 0.08594
/*4   */ {                                                                                // (30) 0.001953
/*6   */     char *path;                                                                  // (26) 0.01367
/*8   */     int fd = -1;                                                                 // (21) 0.01953
/*10  */     int err = -1;                                                                // (24) 0.01758
/*12  */     int serrno = 0;                                                              // (22) 0.01953
/*14  */     V9fsString fullname;                                                         // (20) 0.01953
/*16  */     char *buffer;                                                                // (27) 0.01367
/*20  */     /*                                                                           // (29) 0.007812
/*22  */      * Mark all the open to not follow symlinks                                  // (16) 0.02734
/*24  */      */                                                                          // (28) 0.009766
/*26  */     flags |= O_NOFOLLOW;                                                         // (18) 0.02344
/*30  */     v9fs_string_init(&fullname);                                                 // (17) 0.02734
/*32  */     v9fs_string_sprintf(&fullname, "%s/%s", dir_path->data, name);               // (1) 0.05664
/*34  */     path = fullname.data;                                                        // (23) 0.01953
/*38  */     /* Determine the security model */                                           // (19) 0.01953
/*40  */     if (fs_ctx->export_flags & V9FS_SM_MAPPED) {                                 // (5) 0.04688
/*42  */         buffer = rpath(fs_ctx, path);                                            // (7) 0.03516
/*44  */         fd = open(buffer, flags, SM_LOCAL_MODE_BITS);                            // (3) 0.05078
/*46  */         if (fd == -1) {                                                          // (13) 0.0293
/*48  */             g_free(buffer);                                                      // (9) 0.0332
/*50  */             err = fd;                                                            // (11) 0.03125
/*52  */             goto out;                                                            // (15) 0.02734
/*54  */         }                                                                        // (25) 0.01562
/*56  */         credp->fc_mode = credp->fc_mode|S_IFREG;                                 // (4) 0.05078
/*58  */         /* Set cleint credentials in xattr */                                    // (12) 0.03125
/*60  */         err = local_set_xattr(buffer, credp);                                    // (6) 0.04102
/*62  */         if (err == -1) {                                                         // (14) 0.0293
/*64  */             serrno = errno;                                                      // (8) 0.03516
/*66  */             goto err_end;                                                        // (10) 0.03125
/*68  */         }                                                                        // 0.0
/*70  */     } else if (fs_ctx->export_flags & V9FS_SM_MAPPED_FILE) {                     // 0.0
/*72  */         buffer = rpath(fs_ctx, path);                                            // 0.0
/*74  */         fd = open(buffer, flags, SM_LOCAL_MODE_BITS);                            // 0.0
/*76  */         if (fd == -1) {                                                          // 0.0
/*78  */             g_free(buffer);                                                      // 0.0
/*80  */             err = fd;                                                            // 0.0
/*82  */             goto out;                                                            // 0.0
/*84  */         }                                                                        // 0.0
/*86  */         credp->fc_mode = credp->fc_mode|S_IFREG;                                 // 0.0
/*88  */         /* Set client credentials in .virtfs_metadata directory files */         // 0.0
/*90  */         err = local_set_mapped_file_attr(fs_ctx, path, credp);                   // 0.0
/*92  */         if (err == -1) {                                                         // 0.0
/*94  */             serrno = errno;                                                      // 0.0
/*96  */             goto err_end;                                                        // 0.0
/*98  */         }                                                                        // 0.0
/*100 */     } else if ((fs_ctx->export_flags & V9FS_SM_PASSTHROUGH) ||                   // 0.0
/*102 */                (fs_ctx->export_flags & V9FS_SM_NONE)) {                          // 0.0
/*104 */         buffer = rpath(fs_ctx, path);                                            // 0.0
/*106 */         fd = open(buffer, flags, credp->fc_mode);                                // 0.0
/*108 */         if (fd == -1) {                                                          // 0.0
/*110 */             g_free(buffer);                                                      // 0.0
/*112 */             err = fd;                                                            // 0.0
/*114 */             goto out;                                                            // 0.0
/*116 */         }                                                                        // 0.0
/*118 */         err = local_post_create_passthrough(fs_ctx, path, credp);                // 0.0
/*120 */         if (err == -1) {                                                         // 0.0
/*122 */             serrno = errno;                                                      // 0.0
/*124 */             goto err_end;                                                        // 0.0
/*126 */         }                                                                        // 0.0
/*128 */     }                                                                            // 0.0
/*130 */     err = fd;                                                                    // 0.0
/*132 */     fs->fd = fd;                                                                 // 0.0
/*134 */     goto out;                                                                    // 0.0
/*138 */ err_end:                                                                         // 0.0
/*140 */     close(fd);                                                                   // 0.0
/*142 */     remove(buffer);                                                              // 0.0
/*144 */     errno = serrno;                                                              // 0.0
/*146 */     g_free(buffer);                                                              // 0.0
/*148 */ out:                                                                             // 0.0
/*150 */     v9fs_string_free(&fullname);                                                 // 0.0
/*152 */     return err;                                                                  // 0.0
/*154 */ }                                                                                // 0.0
