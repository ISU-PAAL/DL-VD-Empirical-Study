// commit message qemu@51b19ebe43 (target=0, prob=0.30794287, correct=True): virtio: move allocation to virtqueue_pop/vring_pop
/*0  */ static size_t send_control_msg(VirtIOSerial *vser, void *buf, size_t len)  // (1) 0.1143
/*2  */ {                                                                          // (15) 0.004082
/*4  */     VirtQueueElement elem;                                                 // (10) 0.03673
/*6  */     VirtQueue *vq;                                                         // (11) 0.03673
/*10 */     vq = vser->c_ivq;                                                      // (7) 0.05714
/*12 */     if (!virtio_queue_ready(vq)) {                                         // (6) 0.06531
/*14 */         return 0;                                                          // (8) 0.04082
/*16 */     }                                                                      // (13) 0.01633
/*18 */     if (!virtqueue_pop(vq, &elem)) {                                       // (4) 0.07347
/*20 */         return 0;                                                          // (9) 0.04082
/*22 */     }                                                                      // (14) 0.01633
/*26 */     /* TODO: detect a buffer that's too short, set NEEDS_RESET */          // (2) 0.0898
/*28 */     iov_from_buf(elem.in_sg, elem.in_num, 0, buf, len);                    // (0) 0.1224
/*32 */     virtqueue_push(vq, &elem, len);                                        // (5) 0.06939
/*34 */     virtio_notify(VIRTIO_DEVICE(vser), vq);                                // (3) 0.0898
/*36 */     return len;                                                            // (12) 0.02449
/*38 */ }                                                                          // (16) 0.004082
