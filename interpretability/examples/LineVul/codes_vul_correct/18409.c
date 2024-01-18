// commit message qemu@e5d9adbdab (target=1, prob=0.5314399, correct=True): qemu-ga: execute fsfreeze-freeze in reverse order of mounts
/*0   */ int64_t qmp_guest_fsfreeze_freeze(Error **err)                                  // (6) 0.04102
/*2   */ {                                                                               // (29) 0.001953
/*4   */     int ret = 0, i = 0;                                                         // (19) 0.02344
/*6   */     FsMountList mounts;                                                         // (24) 0.01758
/*8   */     struct FsMount *mount;                                                      // (23) 0.01953
/*10  */     Error *local_err = NULL;                                                    // (20) 0.02148
/*12  */     int fd;                                                                     // (26) 0.01367
/*16  */     slog("guest-fsfreeze called");                                              // (18) 0.02539
/*20  */     execute_fsfreeze_hook(FSFREEZE_HOOK_FREEZE, &local_err);                    // (2) 0.05078
/*22  */     if (error_is_set(&local_err)) {                                             // (12) 0.03125
/*24  */         error_propagate(err, local_err);                                        // (9) 0.03516
/*26  */         return -1;                                                              // (21) 0.02148
/*28  */     }                                                                           // (27) 0.007812
/*32  */     QTAILQ_INIT(&mounts);                                                       // (16) 0.02734
/*34  */     build_fs_mount_list(&mounts, &local_err);                                   // (8) 0.03711
/*36  */     if (error_is_set(&local_err)) {                                             // (13) 0.03125
/*38  */         error_propagate(err, local_err);                                        // (10) 0.03516
/*40  */         return -1;                                                              // (22) 0.02148
/*42  */     }                                                                           // (28) 0.007812
/*46  */     /* cannot risk guest agent blocking itself on a write in this state */      // (11) 0.0332
/*48  */     ga_set_frozen(ga_state);                                                    // (15) 0.02734
/*52  */     QTAILQ_FOREACH(mount, &mounts, next) {                                      // (7) 0.03906
/*54  */         fd = qemu_open(mount->dirname, O_RDONLY);                               // (1) 0.05273
/*56  */         if (fd == -1) {                                                         // (14) 0.0293
/*58  */             error_setg_errno(err, errno, "failed to open %s", mount->dirname);  // (0) 0.07031
/*60  */             goto error;                                                         // (17) 0.02734
/*62  */         }                                                                       // (25) 0.01563
/*66  */         /* we try to cull filesytems we know won't work in advance, but other   // (3) 0.04883
/*68  */          * filesytems may not implement fsfreeze for less obvious reasons.      // (5) 0.04492
/*70  */          * these will report EOPNOTSUPP. we simply ignore these when tallying   // (4) 0.04883
/*72  */          * the number of frozen filesystems.                                    // 0.0
/*74  */          *                                                                      // 0.0
/*76  */          * any other error means a failure to freeze a filesystem we            // 0.0
/*78  */          * expect to be freezable, so return an error in those cases            // 0.0
/*80  */          * and return system to thawed state.                                   // 0.0
/*82  */          */                                                                     // 0.0
/*84  */         ret = ioctl(fd, FIFREEZE);                                              // 0.0
/*86  */         if (ret == -1) {                                                        // 0.0
/*88  */             if (errno != EOPNOTSUPP) {                                          // 0.0
/*90  */                 error_setg_errno(err, errno, "failed to freeze %s",             // 0.0
/*92  */                                  mount->dirname);                               // 0.0
/*94  */                 close(fd);                                                      // 0.0
/*96  */                 goto error;                                                     // 0.0
/*98  */             }                                                                   // 0.0
/*100 */         } else {                                                                // 0.0
/*102 */             i++;                                                                // 0.0
/*104 */         }                                                                       // 0.0
/*106 */         close(fd);                                                              // 0.0
/*108 */     }                                                                           // 0.0
/*112 */     free_fs_mount_list(&mounts);                                                // 0.0
/*114 */     return i;                                                                   // 0.0
/*118 */ error:                                                                          // 0.0
/*120 */     free_fs_mount_list(&mounts);                                                // 0.0
/*122 */     qmp_guest_fsfreeze_thaw(NULL);                                              // 0.0
/*124 */     return 0;                                                                   // 0.0
/*126 */ }                                                                               // 0.0
