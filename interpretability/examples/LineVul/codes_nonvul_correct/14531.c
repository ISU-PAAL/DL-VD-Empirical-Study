// commit message qemu@0d8d769085 (target=0, prob=0.29334414, correct=True): virtio: Introduce virtqueue_get_avail_bytes()
/*0   */ int virtqueue_avail_bytes(VirtQueue *vq, int in_bytes, int out_bytes)        // (2) 0.05078
/*2   */ {                                                                            // (24) 0.001953
/*4   */     unsigned int idx;                                                        // (23) 0.01562
/*6   */     unsigned int total_bufs, in_total, out_total;                            // (16) 0.03516
/*10  */     idx = vq->last_avail_idx;                                                // (17) 0.0332
/*14  */     total_bufs = in_total = out_total = 0;                                   // (14) 0.03516
/*16  */     while (virtqueue_num_heads(vq, idx)) {                                   // (9) 0.03711
/*18  */         unsigned int max, num_bufs, indirect = 0;                            // (8) 0.03906
/*20  */         target_phys_addr_t desc_pa;                                          // (15) 0.03516
/*22  */         int i;                                                               // (22) 0.01953
/*26  */         max = vq->vring.num;                                                 // (18) 0.0332
/*28  */         num_bufs = total_bufs;                                               // (19) 0.0332
/*30  */         i = virtqueue_get_head(vq, idx++);                                   // (6) 0.04492
/*32  */         desc_pa = vq->vring.desc;                                            // (10) 0.03711
/*36  */         if (vring_desc_flags(desc_pa, i) & VRING_DESC_F_INDIRECT) {          // (0) 0.07031
/*38  */             if (vring_desc_len(desc_pa, i) % sizeof(VRingDesc)) {            // (1) 0.06641
/*40  */                 error_report("Invalid size for indirect buffer table");      // (4) 0.05078
/*42  */                 exit(1);                                                     // (13) 0.03711
/*44  */             }                                                                // (20) 0.02344
/*48  */             /* If we've got too many, that implies a descriptor loop. */     // (3) 0.05078
/*50  */             if (num_bufs >= max) {                                           // (7) 0.04102
/*52  */                 error_report("Looped descriptor");                           // (5) 0.04492
/*54  */                 exit(1);                                                     // (12) 0.03711
/*56  */             }                                                                // (21) 0.02344
/*60  */             /* loop over the indirect descriptor table */                    // (11) 0.03711
/*62  */             indirect = 1;                                                    // 0.0
/*64  */             max = vring_desc_len(desc_pa, i) / sizeof(VRingDesc);            // 0.0
/*66  */             num_bufs = i = 0;                                                // 0.0
/*68  */             desc_pa = vring_desc_addr(desc_pa, i);                           // 0.0
/*70  */         }                                                                    // 0.0
/*74  */         do {                                                                 // 0.0
/*76  */             /* If we've got too many, that implies a descriptor loop. */     // 0.0
/*78  */             if (++num_bufs > max) {                                          // 0.0
/*80  */                 error_report("Looped descriptor");                           // 0.0
/*82  */                 exit(1);                                                     // 0.0
/*84  */             }                                                                // 0.0
/*88  */             if (vring_desc_flags(desc_pa, i) & VRING_DESC_F_WRITE) {         // 0.0
/*90  */                 if (in_bytes > 0 &&                                          // 0.0
/*92  */                     (in_total += vring_desc_len(desc_pa, i)) >= in_bytes)    // 0.0
/*94  */                     return 1;                                                // 0.0
/*96  */             } else {                                                         // 0.0
/*98  */                 if (out_bytes > 0 &&                                         // 0.0
/*100 */                     (out_total += vring_desc_len(desc_pa, i)) >= out_bytes)  // 0.0
/*102 */                     return 1;                                                // 0.0
/*104 */             }                                                                // 0.0
/*106 */         } while ((i = virtqueue_next_desc(desc_pa, i, max)) != max);         // 0.0
/*110 */         if (!indirect)                                                       // 0.0
/*112 */             total_bufs = num_bufs;                                           // 0.0
/*114 */         else                                                                 // 0.0
/*116 */             total_bufs++;                                                    // 0.0
/*118 */     }                                                                        // 0.0
/*122 */     return 0;                                                                // 0.0
/*124 */ }                                                                            // 0.0
