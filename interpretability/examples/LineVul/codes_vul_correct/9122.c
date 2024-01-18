// commit message qemu@b8aecea23a (target=1, prob=0.6899484, correct=True): memory: don't try to adjust endianness for zero length eventfd
/*0  */ void memory_region_add_eventfd(MemoryRegion *mr,                                // (12) 0.0293
/*2  */                                hwaddr addr,                                     // (2) 0.06836
/*4  */                                unsigned size,                                   // (5) 0.06445
/*6  */                                bool match_data,                                 // (3) 0.06836
/*8  */                                uint64_t data,                                   // (0) 0.07031
/*10 */                                EventNotifier *e)                                // (1) 0.07031
/*12 */ {                                                                               // (23) 0.001953
/*14 */     MemoryRegionIoeventfd mrfd = {                                              // (13) 0.02734
/*16 */         .addr.start = int128_make64(addr),                                      // (8) 0.03906
/*18 */         .addr.size = int128_make64(size),                                       // (9) 0.03906
/*20 */         .match_data = match_data,                                               // (11) 0.03125
/*22 */         .data = data,                                                           // (15) 0.02344
/*24 */         .e = e,                                                                 // (16) 0.02344
/*26 */     };                                                                          // (21) 0.007813
/*28 */     unsigned i;                                                                 // (20) 0.01172
/*32 */     adjust_endianness(mr, &mrfd.data, size);                                    // (10) 0.03711
/*34 */     memory_region_transaction_begin();                                          // (17) 0.02344
/*36 */     for (i = 0; i < mr->ioeventfd_nb; ++i) {                                    // (6) 0.04688
/*38 */         if (memory_region_ioeventfd_before(mrfd, mr->ioeventfds[i])) {          // (4) 0.06641
/*40 */             break;                                                              // (14) 0.02539
/*42 */         }                                                                       // (19) 0.01562
/*44 */     }                                                                           // (22) 0.007812
/*46 */     ++mr->ioeventfd_nb;                                                         // (18) 0.02344
/*48 */     mr->ioeventfds = g_realloc(mr->ioeventfds,                                  // (7) 0.04492
/*50 */                                   sizeof(*mr->ioeventfds) * mr->ioeventfd_nb);  // 0.0
/*52 */     memmove(&mr->ioeventfds[i+1], &mr->ioeventfds[i],                           // 0.0
/*54 */             sizeof(*mr->ioeventfds) * (mr->ioeventfd_nb-1 - i));                // 0.0
/*56 */     mr->ioeventfds[i] = mrfd;                                                   // 0.0
/*58 */     ioeventfd_update_pending |= mr->enabled;                                    // 0.0
/*60 */     memory_region_transaction_commit();                                         // 0.0
/*62 */ }                                                                               // 0.0
