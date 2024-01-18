// commit message qemu@02cb7f3a25 (target=0, prob=0.03258558, correct=True): hw/9pfs: Use read-write lock for protecting fid path.
/*0  */ int v9fs_co_open2(V9fsState *s, V9fsFidState *fidp, char *fullname, gid_t gid,  // (0) 0.1034
/*2  */                   int flags, int mode)                                          // (3) 0.05943
/*4  */ {                                                                               // (23) 0.002584
/*6  */     int err;                                                                    // (20) 0.0155
/*8  */     FsCred cred;                                                                // (15) 0.02326
/*12 */     cred_init(&cred);                                                           // (14) 0.02584
/*14 */     cred.fc_mode = mode & 07777;                                                // (7) 0.03876
/*16 */     cred.fc_uid = fidp->uid;                                                    // (10) 0.03618
/*18 */     cred.fc_gid = gid;                                                          // (11) 0.03359
/*20 */     v9fs_co_run_in_worker(                                                      // (8) 0.03876
/*22 */         {                                                                       // (16) 0.02067
/*24 */             fidp->fs.fd = s->ops->open2(&s->ctx, fullname, flags, &cred);       // (1) 0.09819
/*26 */             err = 0;                                                            // (9) 0.03876
/*28 */             if (fidp->fs.fd == -1) {                                            // (2) 0.0646
/*30 */                 err = -errno;                                                   // (6) 0.05426
/*32 */             }                                                                   // (13) 0.03101
/*34 */         });                                                                     // (17) 0.02067
/*36 */     if (!err) {                                                                 // (18) 0.02067
/*38 */         total_open_fd++;                                                        // (12) 0.03359
/*40 */         if (total_open_fd > open_fd_hw) {                                       // (4) 0.05685
/*42 */             v9fs_reclaim_fd(s);                                                 // (5) 0.05685
/*44 */         }                                                                       // (19) 0.02067
/*46 */     }                                                                           // (22) 0.01034
/*48 */     return err;                                                                 // (21) 0.0155
/*50 */ }                                                                               // (24) 0.002584
