// commit message qemu@4fa4ce7107 (target=0, prob=0.4219365, correct=True): hw/9pfs: use g_strdup_printf() instead of PATH_MAX limitation
/*0  */ static int local_chown(FsContext *fs_ctx, V9fsPath *fs_path, FsCred *credp)  // (1) 0.09357
/*2  */ {                                                                            // (14) 0.002924
/*4  */     char buffer[PATH_MAX];                                                   // (11) 0.02924
/*6  */     char *path = fs_path->data;                                              // (10) 0.03801
/*10 */     if ((credp->fc_uid == -1 && credp->fc_gid == -1) ||                      // (5) 0.08187
/*12 */         (fs_ctx->export_flags & V9FS_SM_PASSTHROUGH) ||                      // (2) 0.0848
/*14 */         (fs_ctx->export_flags & V9FS_SM_NONE)) {                             // (7) 0.07602
/*16 */         return lchown(rpath(fs_ctx, path, buffer),                           // (9) 0.06725
/*18 */                       credp->fc_uid, credp->fc_gid);                         // (0) 0.1053
/*20 */     } else if (fs_ctx->export_flags & V9FS_SM_MAPPED) {                      // (8) 0.07602
/*22 */         return local_set_xattr(rpath(fs_ctx, path, buffer), credp);          // (3) 0.0848
/*24 */     } else if (fs_ctx->export_flags & V9FS_SM_MAPPED_FILE) {                 // (4) 0.08187
/*26 */         return local_set_mapped_file_attr(fs_ctx, path, credp);              // (6) 0.08187
/*28 */     }                                                                        // (13) 0.0117
/*30 */     return -1;                                                               // (12) 0.02047
/*32 */ }                                                                            // (15) 0.002924
