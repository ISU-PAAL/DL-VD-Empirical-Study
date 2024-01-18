// commit message qemu@8607f5c307 (target=0, prob=0.40819827, correct=True): virtio: convert to use DMA api
/*0  */ static void virtqueue_unmap_sg(VirtQueue *vq, const VirtQueueElement *elem,  // (8) 0.05828
/*2  */                                unsigned int len)                             // (4) 0.07925
/*4  */ {                                                                            // (16) 0.002331
/*6  */     unsigned int offset;                                                     // (12) 0.01632
/*8  */     int i;                                                                   // (14) 0.01399
/*12 */     offset = 0;                                                              // (13) 0.01632
/*14 */     for (i = 0; i < elem->in_num; i++) {                                     // (9) 0.04895
/*16 */         size_t size = MIN(len - offset, elem->in_sg[i].iov_len);             // (5) 0.07226
/*20 */         cpu_physical_memory_unmap(elem->in_sg[i].iov_base,                   // (6) 0.0676
/*22 */                                   elem->in_sg[i].iov_len,                    // (1) 0.1072
/*24 */                                   1, size);                                  // (3) 0.08625
/*28 */         offset += size;                                                      // (11) 0.02564
/*30 */     }                                                                        // (15) 0.009324
/*34 */     for (i = 0; i < elem->out_num; i++)                                      // (10) 0.04662
/*36 */         cpu_physical_memory_unmap(elem->out_sg[i].iov_base,                  // (7) 0.0676
/*38 */                                   elem->out_sg[i].iov_len,                   // (2) 0.1072
/*40 */                                   0, elem->out_sg[i].iov_len);               // (0) 0.1119
/*42 */ }                                                                            // (17) 0.002331
