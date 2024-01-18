// commit message qemu@51b19ebe43 (target=0, prob=0.2739659, correct=True): virtio: move allocation to virtqueue_pop/vring_pop
/*0  */ static void virtio_balloon_handle_output(VirtIODevice *vdev, VirtQueue *vq)     // (7) 0.05469
/*2  */ {                                                                               // (19) 0.001953
/*4  */     VirtIOBalloon *s = VIRTIO_BALLOON(vdev);                                    // (9) 0.04102
/*6  */     VirtQueueElement elem;                                                      // (17) 0.01758
/*8  */     MemoryRegionSection section;                                                // (18) 0.01563
/*12 */     while (virtqueue_pop(vq, &elem)) {                                          // (10) 0.03516
/*14 */         size_t offset = 0;                                                      // (16) 0.02734
/*16 */         uint32_t pfn;                                                           // (15) 0.02734
/*20 */         while (iov_to_buf(elem.out_sg, elem.out_num, offset, &pfn, 4) == 4) {   // (1) 0.08008
/*22 */             ram_addr_t pa;                                                      // (12) 0.03516
/*24 */             ram_addr_t addr;                                                    // (11) 0.03516
/*26 */             int p = virtio_ldl_p(vdev, &pfn);                                   // (5) 0.05664
/*30 */             pa = (ram_addr_t) p << VIRTIO_BALLOON_PFN_SHIFT;                    // (2) 0.07031
/*32 */             offset += 4;                                                        // (14) 0.0293
/*36 */             /* FIXME: remove get_system_memory(), but how? */                   // (8) 0.05078
/*38 */             section = memory_region_find(get_system_memory(), pa, 1);           // (6) 0.05664
/*40 */             if (!int128_nz(section.size) || !memory_region_is_ram(section.mr))  // (3) 0.07031
/*42 */                 continue;                                                       // (13) 0.0332
/*46 */             trace_virtio_balloon_handle_output(memory_region_name(section.mr),  // (4) 0.06445
/*48 */                                                pa);                             // (0) 0.09375
/*50 */             /* Using memory_region_get_ram_ptr is bending the rules a bit, but  // 0.0
/*52 */                should be OK because we only want a single page.  */             // 0.0
/*54 */             addr = section.offset_within_region;                                // 0.0
/*56 */             balloon_page(memory_region_get_ram_ptr(section.mr) + addr,          // 0.0
/*58 */                          !!(vq == s->dvq));                                     // 0.0
/*60 */             memory_region_unref(section.mr);                                    // 0.0
/*62 */         }                                                                       // 0.0
/*66 */         virtqueue_push(vq, &elem, offset);                                      // 0.0
/*68 */         virtio_notify(vdev, vq);                                                // 0.0
/*70 */     }                                                                           // 0.0
/*72 */ }                                                                               // 0.0
