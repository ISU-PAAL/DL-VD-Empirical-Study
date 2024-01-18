// commit message qemu@b931bfbf04 (target=0, prob=0.7873772, correct=False): vhost-user: add multiple queue support
/*0  */ static int vhost_virtqueue_init(struct vhost_dev *dev,                 // (5) 0.0598
/*2  */                                 struct vhost_virtqueue *vq, int n)     // (0) 0.1462
/*4  */ {                                                                      // (19) 0.003322
/*6  */     struct vhost_vring_file file = {                                   // (6) 0.04651
/*8  */         .index = n,                                                    // (8) 0.03987
/*10 */     };                                                                 // (15) 0.01329
/*12 */     int r = event_notifier_init(&vq->masked_notifier, 0);              // (3) 0.07973
/*14 */     if (r < 0) {                                                       // (10) 0.03322
/*16 */         return r;                                                      // (11) 0.03322
/*18 */     }                                                                  // (16) 0.01329
/*22 */     file.fd = event_notifier_get_fd(&vq->masked_notifier);             // (2) 0.08306
/*24 */     r = dev->vhost_ops->vhost_call(dev, VHOST_SET_VRING_CALL, &file);  // (1) 0.113
/*26 */     if (r) {                                                           // (12) 0.02658
/*28 */         r = -errno;                                                    // (7) 0.04319
/*30 */         goto fail_call;                                                // (9) 0.03987
/*32 */     }                                                                  // (17) 0.01329
/*34 */     return 0;                                                          // (13) 0.01993
/*36 */ fail_call:                                                             // (18) 0.01329
/*38 */     event_notifier_cleanup(&vq->masked_notifier);                      // (4) 0.06645
/*40 */     return r;                                                          // (14) 0.01993
/*42 */ }                                                                      // (20) 0.003322
