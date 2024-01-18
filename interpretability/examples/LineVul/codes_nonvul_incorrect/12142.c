// commit message qemu@c471ad0e9b (target=0, prob=0.6244499, correct=False): vhost_net: device IOTLB support
/*0  */ static int vhost_verify_ring_mappings(struct vhost_dev *dev,                   // (7) 0.04102
/*2  */                                       uint64_t start_addr,                     // (2) 0.08789
/*4  */                                       uint64_t size)                           // (3) 0.08398
/*6  */ {                                                                              // (23) 0.001953
/*8  */     int i, j;                                                                  // (19) 0.01562
/*10 */     int r = 0;                                                                 // (20) 0.01562
/*12 */     const char *part_name[] = {                                                // (12) 0.02344
/*14 */         "descriptor table",                                                    // (9) 0.02539
/*16 */         "available ring",                                                      // (15) 0.02148
/*18 */         "used ring"                                                            // (16) 0.02148
/*20 */     };                                                                         // (22) 0.007812
/*24 */     for (i = 0; i < dev->nvqs; ++i) {                                          // (8) 0.03906
/*26 */         struct vhost_virtqueue *vq = dev->vqs + i;                             // (6) 0.04688
/*30 */         j = 0;                                                                 // (17) 0.02148
/*32 */         r = vhost_verify_ring_part_mapping(vq->desc, vq->desc_phys,            // (5) 0.06641
/*34 */                                            vq->desc_size, start_addr, size);   // (1) 0.1074
/*36 */         if (!r) {                                                              // (13) 0.02344
/*38 */             break;                                                             // (10) 0.02539
/*40 */         }                                                                      // (21) 0.01562
/*44 */         j++;                                                                   // (18) 0.01758
/*46 */         r = vhost_verify_ring_part_mapping(vq->avail, vq->avail_phys,          // (4) 0.07031
/*48 */                                            vq->avail_size, start_addr, size);  // (0) 0.1094
/*50 */         if (!r) {                                                              // (14) 0.02344
/*52 */             break;                                                             // (11) 0.02539
/*54 */         }                                                                      // 0.0
/*58 */         j++;                                                                   // 0.0
/*60 */         r = vhost_verify_ring_part_mapping(vq->used, vq->used_phys,            // 0.0
/*62 */                                            vq->used_size, start_addr, size);   // 0.0
/*64 */         if (!r) {                                                              // 0.0
/*66 */             break;                                                             // 0.0
/*68 */         }                                                                      // 0.0
/*70 */     }                                                                          // 0.0
/*74 */     if (r == -ENOMEM) {                                                        // 0.0
/*76 */         error_report("Unable to map %s for ring %d", part_name[j], i);         // 0.0
/*78 */     } else if (r == -EBUSY) {                                                  // 0.0
/*80 */         error_report("%s relocated for ring %d", part_name[j], i);             // 0.0
/*82 */     }                                                                          // 0.0
/*84 */     return r;                                                                  // 0.0
/*86 */ }                                                                              // 0.0
