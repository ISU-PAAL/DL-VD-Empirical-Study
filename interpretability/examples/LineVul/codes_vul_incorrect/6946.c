// commit message qemu@361dcc790d (target=1, prob=0.36453083, correct=False): virtio-scsi: dataplane: fail setup gracefully
/*0  */ static VirtIOSCSIVring *virtio_scsi_vring_init(VirtIOSCSI *s,                  // (4) 0.05469
/*2  */                                                VirtQueue *vq,                  // (1) 0.1016
/*4  */                                                EventNotifierHandler *handler,  // (0) 0.1035
/*6  */                                                int n)                          // (2) 0.0957
/*8  */ {                                                                              // (19) 0.001953
/*10 */     BusState *qbus = BUS(qdev_get_parent_bus(DEVICE(s)));                      // (8) 0.05078
/*12 */     VirtioBusClass *k = VIRTIO_BUS_GET_CLASS(qbus);                            // (10) 0.04492
/*14 */     VirtIOSCSIVring *r = g_slice_new(VirtIOSCSIVring);                         // (7) 0.05078
/*16 */     int rc;                                                                    // (17) 0.01172
/*20 */     /* Set up virtqueue notify */                                              // (14) 0.01953
/*22 */     rc = k->set_host_notifier(qbus->parent, n, true);                          // (11) 0.04492
/*24 */     if (rc != 0) {                                                             // (15) 0.01953
/*26 */         fprintf(stderr, "virtio-scsi: Failed to set host notifier (%d)\n",     // (3) 0.0625
/*28 */                 rc);                                                           // (12) 0.0332
/*30 */         exit(1);                                                               // (13) 0.02148
/*32 */     }                                                                          // (18) 0.007812
/*34 */     r->host_notifier = *virtio_queue_get_host_notifier(vq);                    // (9) 0.05078
/*36 */     r->guest_notifier = *virtio_queue_get_guest_notifier(vq);                  // (5) 0.05469
/*38 */     aio_set_event_notifier(s->ctx, &r->host_notifier, handler);                // (6) 0.05273
/*42 */     r->parent = s;                                                             // (16) 0.01758
/*46 */     if (!vring_setup(&r->vring, VIRTIO_DEVICE(s), n)) {                        // 0.0
/*48 */         fprintf(stderr, "virtio-scsi: VRing setup failed\n");                  // 0.0
/*50 */         exit(1);                                                               // 0.0
/*52 */     }                                                                          // 0.0
/*54 */     return r;                                                                  // 0.0
/*56 */ }                                                                              // 0.0
