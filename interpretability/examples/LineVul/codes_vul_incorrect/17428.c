// commit message qemu@f897bf751f (target=1, prob=0.39612076, correct=False): virtio-blk: embed VirtQueueElement in VirtIOBlockReq
/*0   */ int vring_pop(VirtIODevice *vdev, Vring *vring,                               // (4) 0.04297
/*2   */               VirtQueueElement **p_elem)                                      // (2) 0.04297
/*4   */ {                                                                             // (31) 0.001953
/*6   */     struct vring_desc desc;                                                   // (22) 0.01953
/*8   */     unsigned int i, head, found = 0, num = vring->vr.num;                     // (3) 0.04297
/*10  */     uint16_t avail_idx, last_avail_idx;                                       // (7) 0.03906
/*12  */     VirtQueueElement *elem = NULL;                                            // (19) 0.02344
/*14  */     int ret;                                                                  // (27) 0.01172
/*18  */     /* If there was a fatal error then refuse operation */                    // (16) 0.02734
/*20  */     if (vring->broken) {                                                      // (21) 0.02148
/*22  */         ret = -EFAULT;                                                        // (18) 0.02539
/*24  */         goto out;                                                             // (23) 0.01953
/*26  */     }                                                                         // (30) 0.007812
/*30  */     /* Check it isn't doing very strange things with descriptor numbers. */   // (11) 0.0332
/*32  */     last_avail_idx = vring->last_avail_idx;                                   // (6) 0.04297
/*34  */     avail_idx = vring->vr.avail->idx;                                         // (9) 0.03711
/*36  */     barrier(); /* load indices now and not again later */                     // (15) 0.02734
/*40  */     if (unlikely((uint16_t)(avail_idx - last_avail_idx) > num)) {             // (1) 0.06055
/*42  */         error_report("Guest moved used index from %u to %u",                  // (5) 0.04297
/*44  */                      last_avail_idx, avail_idx);                              // (0) 0.06445
/*46  */         ret = -EFAULT;                                                        // (17) 0.02539
/*48  */         goto out;                                                             // (25) 0.01953
/*50  */     }                                                                         // (28) 0.007812
/*54  */     /* If there's nothing new since last we looked. */                        // (13) 0.0293
/*56  */     if (avail_idx == last_avail_idx) {                                        // (8) 0.03906
/*58  */         ret = -EAGAIN;                                                        // (14) 0.02734
/*60  */         goto out;                                                             // (24) 0.01953
/*62  */     }                                                                         // (29) 0.007812
/*66  */     /* Only get avail ring entries after they have been exposed by guest. */  // (10) 0.03516
/*68  */     smp_rmb();                                                                // (26) 0.01758
/*72  */     /* Grab the next descriptor number they're advertising, and increment     // (12) 0.0293
/*74  */      * the index we've seen. */                                               // (20) 0.02344
/*76  */     head = vring->vr.avail->ring[last_avail_idx % num];                       // 0.0
/*80  */     elem = g_slice_new(VirtQueueElement);                                     // 0.0
/*82  */     elem->index = head;                                                       // 0.0
/*84  */     elem->in_num = elem->out_num = 0;                                         // 0.0
/*86  */                                                                               // 0.0
/*88  */     /* If their number is silly, that's an error. */                          // 0.0
/*90  */     if (unlikely(head >= num)) {                                              // 0.0
/*92  */         error_report("Guest says index %u > %u is available", head, num);     // 0.0
/*94  */         ret = -EFAULT;                                                        // 0.0
/*96  */         goto out;                                                             // 0.0
/*98  */     }                                                                         // 0.0
/*102 */     if (vdev->guest_features & (1 << VIRTIO_RING_F_EVENT_IDX)) {              // 0.0
/*104 */         vring_avail_event(&vring->vr) = vring->vr.avail->idx;                 // 0.0
/*106 */     }                                                                         // 0.0
/*110 */     i = head;                                                                 // 0.0
/*112 */     do {                                                                      // 0.0
/*114 */         if (unlikely(i >= num)) {                                             // 0.0
/*116 */             error_report("Desc index is %u > %u, head = %u", i, num, head);   // 0.0
/*118 */             ret = -EFAULT;                                                    // 0.0
/*120 */             goto out;                                                         // 0.0
/*122 */         }                                                                     // 0.0
/*124 */         if (unlikely(++found > num)) {                                        // 0.0
/*126 */             error_report("Loop detected: last one at %u vq size %u head %u",  // 0.0
/*128 */                          i, num, head);                                       // 0.0
/*130 */             ret = -EFAULT;                                                    // 0.0
/*132 */             goto out;                                                         // 0.0
/*134 */         }                                                                     // 0.0
/*136 */         desc = vring->vr.desc[i];                                             // 0.0
/*140 */         /* Ensure descriptor is loaded before accessing fields */             // 0.0
/*142 */         barrier();                                                            // 0.0
/*146 */         if (desc.flags & VRING_DESC_F_INDIRECT) {                             // 0.0
/*148 */             ret = get_indirect(vring, elem, &desc);                           // 0.0
/*150 */             if (ret < 0) {                                                    // 0.0
/*152 */                 goto out;                                                     // 0.0
/*154 */             }                                                                 // 0.0
/*156 */             continue;                                                         // 0.0
/*158 */         }                                                                     // 0.0
/*162 */         ret = get_desc(vring, elem, &desc);                                   // 0.0
/*164 */         if (ret < 0) {                                                        // 0.0
/*166 */             goto out;                                                         // 0.0
/*168 */         }                                                                     // 0.0
/*172 */         i = desc.next;                                                        // 0.0
/*174 */     } while (desc.flags & VRING_DESC_F_NEXT);                                 // 0.0
/*178 */     /* On success, increment avail index. */                                  // 0.0
/*180 */     vring->last_avail_idx++;                                                  // 0.0
/*182 */     *p_elem = elem;                                                           // 0.0
/*184 */     return head;                                                              // 0.0
/*188 */ out:                                                                          // 0.0
/*190 */     assert(ret < 0);                                                          // 0.0
/*192 */     if (ret == -EFAULT) {                                                     // 0.0
/*194 */         vring->broken = true;                                                 // 0.0
/*196 */     }                                                                         // 0.0
/*198 */     if (elem) {                                                               // 0.0
/*200 */         vring_unmap_element(elem);                                            // 0.0
/*202 */         g_slice_free(VirtQueueElement, elem);                                 // 0.0
/*204 */     }                                                                         // 0.0
/*206 */     *p_elem = NULL;                                                           // 0.0
/*208 */     return ret;                                                               // 0.0
/*210 */ }                                                                             // 0.0
