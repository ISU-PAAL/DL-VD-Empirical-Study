// commit message qemu@cd7fdfe59f (target=1, prob=0.37294436, correct=False): dataplane: avoid reentrancy during virtio_blk_data_plane_stop()
/*0  */ void virtio_blk_data_plane_stop(VirtIOBlockDataPlane *s)                       // (2) 0.06745
/*2  */ {                                                                              // (20) 0.002933
/*4  */     if (!s->started) {                                                         // (14) 0.02933
/*6  */         return;                                                                // (15) 0.02639
/*8  */     }                                                                          // (18) 0.01173
/*10 */     s->started = false;                                                        // (16) 0.02639
/*12 */     trace_virtio_blk_data_plane_stop(s);                                       // (5) 0.05572
/*16 */     /* Stop thread or cancel pending thread creation BH */                     // (11) 0.04106
/*18 */     if (s->start_bh) {                                                         // (13) 0.03519
/*20 */         qemu_bh_delete(s->start_bh);                                           // (3) 0.06158
/*22 */         s->start_bh = NULL;                                                    // (9) 0.04399
/*24 */     } else {                                                                   // (17) 0.0176
/*26 */         event_poll_notify(&s->event_poll);                                     // (4) 0.05865
/*28 */         qemu_thread_join(&s->thread);                                          // (6) 0.05572
/*30 */     }                                                                          // (19) 0.01173
/*34 */     ioq_cleanup(&s->ioqueue);                                                  // (12) 0.04106
/*38 */     s->vdev->binding->set_host_notifier(s->vdev->binding_opaque, 0, false);    // (1) 0.09091
/*42 */     event_poll_cleanup(&s->event_poll);                                        // (7) 0.04692
/*46 */     /* Clean up guest notifier (irq) */                                        // (10) 0.04106
/*48 */     s->vdev->binding->set_guest_notifiers(s->vdev->binding_opaque, 1, false);  // (0) 0.09384
/*52 */     vring_teardown(&s->vring);                                                 // (8) 0.04399
/*54 */ }                                                                              // (21) 0.002933
