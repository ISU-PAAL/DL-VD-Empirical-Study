// commit message qemu@bf18bee547 (target=0, prob=0.33094418, correct=True): blockdev: clean up error handling in do_open_tray
/*0  */ void qmp_eject(const char *device, bool has_force, bool force, Error **errp)    // (2) 0.09398
/*2  */ {                                                                               // (17) 0.003759
/*4  */     Error *local_err = NULL;                                                    // (7) 0.04135
/*6  */     int rc;                                                                     // (13) 0.02256
/*10 */     if (!has_force) {                                                           // (9) 0.03759
/*12 */         force = false;                                                          // (8) 0.04135
/*14 */     }                                                                           // (15) 0.01504
/*18 */     rc = do_open_tray(device, force, &local_err);                               // (3) 0.07895
/*20 */     if (local_err) {                                                            // (10) 0.03759
/*22 */         error_propagate(errp, local_err);                                       // (5) 0.07143
/*24 */         return;                                                                 // (11) 0.03383
/*26 */     }                                                                           // (16) 0.01504
/*30 */     if (rc == EINPROGRESS) {                                                    // (6) 0.05263
/*32 */         error_setg(errp, "Device '%s' is locked and force was not specified, "  // (0) 0.1128
/*34 */                    "wait for tray to open and try again", device);              // (1) 0.1128
/*36 */         return;                                                                 // (12) 0.03383
/*38 */     }                                                                           // (14) 0.01504
/*42 */     qmp_x_blockdev_remove_medium(device, errp);                                 // (4) 0.07519
/*44 */ }                                                                               // (18) 0.003759
