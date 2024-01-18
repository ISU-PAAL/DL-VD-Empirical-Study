// commit message qemu@0e22a2d189 (target=1, prob=0.51329404, correct=True): vhost-scsi: fix k->set_guest_notifiers() NULL dereference
/*0  */ static void vhost_scsi_stop(VHostSCSI *s)                                        // (6) 0.05822
/*2  */ {                                                                                // (15) 0.003425
/*4  */     VirtIODevice *vdev = VIRTIO_DEVICE(s);                                       // (4) 0.07192
/*6  */     BusState *qbus = BUS(qdev_get_parent_bus(DEVICE(vdev)));                     // (2) 0.09247
/*8  */     VirtioBusClass *k = VIRTIO_BUS_GET_CLASS(qbus);                              // (3) 0.07877
/*10 */     int ret = 0;                                                                 // (12) 0.0274
/*14 */     if (!k->set_guest_notifiers) {                                               // (9) 0.05479
/*16 */         ret = k->set_guest_notifiers(qbus->parent, s->dev.nvqs, false);          // (1) 0.113
/*18 */         if (ret < 0) {                                                           // (10) 0.04795
/*20 */                 error_report("vhost guest notifier cleanup failed: %d\n", ret);  // (0) 0.1164
/*22 */         }                                                                        // (13) 0.0274
/*24 */     }                                                                            // (14) 0.0137
/*26 */     assert(ret >= 0);                                                            // (11) 0.03082
/*30 */     vhost_scsi_clear_endpoint(s);                                                // (8) 0.05479
/*32 */     vhost_dev_stop(&s->dev, vdev);                                               // (7) 0.05822
/*34 */     vhost_dev_disable_notifiers(&s->dev, vdev);                                  // (5) 0.06849
/*36 */ }                                                                                // (16) 0.003425
