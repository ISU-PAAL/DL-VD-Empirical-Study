// commit message qemu@494a8ebe71 (target=0, prob=0.01464768, correct=True): 9pfs: rename virtio-9p-proxy.{c,h} to 9p-proxy.{c,h}
/*0  */ static int proxy_symlink(FsContext *fs_ctx, const char *oldpath,               // (4) 0.06105
/*2  */                          V9fsPath *dir_path, const char *name, FsCred *credp)  // (0) 0.1366
/*4  */ {                                                                              // (17) 0.002907
/*6  */     int retval;                                                                // (14) 0.02035
/*8  */     V9fsString fullname, target;                                               // (12) 0.03488
/*12 */     v9fs_string_init(&fullname);                                               // (6) 0.0407
/*14 */     v9fs_string_init(&target);                                                 // (9) 0.03779
/*18 */     v9fs_string_sprintf(&fullname, "%s/%s", dir_path->data, name);             // (3) 0.0843
/*20 */     v9fs_string_sprintf(&target, "%s", oldpath);                               // (5) 0.05814
/*24 */     retval = v9fs_request(fs_ctx->private, T_SYMLINK, NULL, "ssdd",            // (2) 0.08721
/*26 */                           &target, &fullname, credp->fc_uid, credp->fc_gid);   // (1) 0.1366
/*28 */     v9fs_string_free(&fullname);                                               // (7) 0.0407
/*30 */     v9fs_string_free(&target);                                                 // (10) 0.03779
/*32 */     if (retval < 0) {                                                          // (13) 0.03198
/*34 */         errno = -retval;                                                       // (8) 0.0407
/*36 */         retval = -1;                                                           // (11) 0.03779
/*38 */     }                                                                          // (16) 0.01163
/*40 */     return retval;                                                             // (15) 0.02035
/*42 */ }                                                                              // (18) 0.002907
