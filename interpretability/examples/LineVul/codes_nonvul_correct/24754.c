// commit message qemu@63729c3692 (target=0, prob=0.08884113, correct=True): virtio-9p: Implement Security model for mksock using mknod.
/*0   */ static void v9fs_create_post_lstat(V9fsState *s, V9fsCreateState *vs, int err)  // (1) 0.06055
/*2   */ {                                                                               // (24) 0.001953
/*6   */     if (err == 0 || errno != ENOENT) {                                          // (14) 0.0332
/*8   */         err = -errno;                                                           // (19) 0.02539
/*10  */         goto out;                                                               // (21) 0.01953
/*12  */     }                                                                           // (23) 0.007812
/*16  */     if (vs->perm & P9_STAT_MODE_DIR) {                                          // (13) 0.03711
/*18  */         err = v9fs_do_mkdir(s, vs);                                             // (12) 0.04297
/*20  */         v9fs_create_post_mkdir(s, vs, err);                                     // (6) 0.04687
/*22  */     } else if (vs->perm & P9_STAT_MODE_SYMLINK) {                               // (8) 0.04492
/*24  */         err = v9fs_do_symlink(s, vs);                                           // (9) 0.04492
/*26  */         v9fs_create_post_perms(s, vs, err);                                     // (7) 0.04687
/*28  */     } else if (vs->perm & P9_STAT_MODE_LINK) {                                  // (11) 0.04297
/*30  */         int32_t nfid = atoi(vs->extension.data);                                // (3) 0.04883
/*32  */         V9fsFidState *nfidp = lookup_fid(s, nfid);                              // (2) 0.05859
/*34  */         if (nfidp == NULL) {                                                    // (15) 0.0332
/*36  */             err = -errno;                                                       // (16) 0.0332
/*38  */             v9fs_post_create(s, vs, err);                                       // (4) 0.04883
/*40  */         }                                                                       // (22) 0.01562
/*42  */         err = v9fs_do_link(s, &nfidp->path, &vs->fullname);                     // (0) 0.06445
/*44  */         v9fs_create_post_perms(s, vs, err);                                     // (5) 0.04687
/*46  */     } else if (vs->perm & P9_STAT_MODE_DEVICE) {                                // (10) 0.04297
/*48  */         char ctype;                                                             // (20) 0.02148
/*50  */         uint32_t major, minor;                                                  // (17) 0.0293
/*52  */         mode_t nmode = 0;                                                       // (18) 0.0293
/*56  */         if (sscanf(vs->extension.data, "%c %u %u", &ctype, &major,              // 0.0
/*58  */                                         &minor) != 3) {                         // 0.0
/*60  */             err = -errno;                                                       // 0.0
/*62  */             v9fs_post_create(s, vs, err);                                       // 0.0
/*64  */         }                                                                       // 0.0
/*68  */         switch (ctype) {                                                        // 0.0
/*70  */         case 'c':                                                               // 0.0
/*72  */             nmode = S_IFCHR;                                                    // 0.0
/*74  */             break;                                                              // 0.0
/*76  */         case 'b':                                                               // 0.0
/*78  */             nmode = S_IFBLK;                                                    // 0.0
/*80  */             break;                                                              // 0.0
/*82  */         default:                                                                // 0.0
/*84  */             err = -EIO;                                                         // 0.0
/*86  */             v9fs_post_create(s, vs, err);                                       // 0.0
/*88  */         }                                                                       // 0.0
/*92  */         nmode |= vs->perm & 0777;                                               // 0.0
/*94  */         err = v9fs_do_mknod(s, vs, nmode, makedev(major, minor));               // 0.0
/*96  */         v9fs_create_post_perms(s, vs, err);                                     // 0.0
/*98  */     } else if (vs->perm & P9_STAT_MODE_NAMED_PIPE) {                            // 0.0
/*100 */         err = v9fs_do_mknod(s, vs, S_IFIFO | (vs->perm & 0777), 0);             // 0.0
/*102 */         v9fs_post_create(s, vs, err);                                           // 0.0
/*104 */     } else if (vs->perm & P9_STAT_MODE_SOCKET) {                                // 0.0
/*106 */         err = v9fs_do_mksock(s, &vs->fullname);                                 // 0.0
/*108 */         v9fs_create_post_mksock(s, vs, err);                                    // 0.0
/*110 */     } else {                                                                    // 0.0
/*112 */         vs->fidp->fd = v9fs_do_open2(s, vs);                                    // 0.0
/*114 */         v9fs_create_post_open2(s, vs, err);                                     // 0.0
/*116 */     }                                                                           // 0.0
/*120 */     return;                                                                     // 0.0
/*124 */ out:                                                                            // 0.0
/*126 */     v9fs_post_create(s, vs, err);                                               // 0.0
/*128 */ }                                                                               // 0.0
