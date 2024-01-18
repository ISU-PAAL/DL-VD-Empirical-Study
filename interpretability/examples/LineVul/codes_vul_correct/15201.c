// commit message qemu@b47b35250f (target=1, prob=0.69437104, correct=True): fdc: Reject unimplemented error actions
/*0  */ FDCtrl *fdctrl_init_isa(DriveInfo **fds)                                 // (4) 0.07522
/*2  */ {                                                                        // (12) 0.004425
/*4  */     ISADevice *dev;                                                      // (8) 0.04425
/*8  */     dev = isa_create("isa-fdc");                                         // (5) 0.06637
/*10 */     if (fds[0]) {                                                        // (6) 0.04867
/*12 */         qdev_prop_set_drive_nofail(&dev->qdev, "driveA", fds[0]->bdrv);  // (0) 0.1726
/*14 */     }                                                                    // (10) 0.0177
/*16 */     if (fds[1]) {                                                        // (7) 0.04867
/*18 */         qdev_prop_set_drive_nofail(&dev->qdev, "driveB", fds[1]->bdrv);  // (1) 0.1726
/*20 */     }                                                                    // (11) 0.0177
/*22 */     if (qdev_init(&dev->qdev) < 0)                                       // (3) 0.07965
/*24 */         return NULL;                                                     // (9) 0.04425
/*26 */     return &(DO_UPCAST(FDCtrlISABus, busdev, dev)->state);               // (2) 0.1195
/*28 */ }                                                                        // (13) 0.004425
