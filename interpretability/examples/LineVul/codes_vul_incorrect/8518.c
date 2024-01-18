// commit message qemu@e1622f4b15 (target=1, prob=0.21153995, correct=False): exec: fix incorrect assumptions in memory_access_size
/*0  */ static int memory_access_size(MemoryRegion *mr, unsigned l, hwaddr addr)         // (5) 0.04884
/*2  */ {                                                                                // (26) 0.002326
/*4  */     unsigned access_size_min = mr->ops->impl.min_access_size;                    // (2) 0.05349
/*6  */     unsigned access_size_max = mr->ops->impl.max_access_size;                    // (3) 0.05349
/*10 */     /* Regions are assumed to support 1-4 byte accesses unless                   // (9) 0.03721
/*12 */        otherwise specified.  */                                                  // (19) 0.02558
/*14 */     if (access_size_min == 0) {                                                  // (15) 0.03256
/*16 */         access_size_min = 1;                                                     // (11) 0.03488
/*18 */     }                                                                            // (22) 0.009302
/*20 */     if (access_size_max == 0) {                                                  // (16) 0.03256
/*22 */         access_size_max = 4;                                                     // (12) 0.03488
/*24 */     }                                                                            // (23) 0.009302
/*28 */     /* Bound the maximum access by the alignment of the address.  */             // (8) 0.03953
/*30 */     if (!mr->ops->impl.unaligned) {                                              // (13) 0.03488
/*32 */         unsigned align_size_max = addr & -addr;                                  // (6) 0.04419
/*34 */         if (align_size_max != 0 && align_size_max < access_size_max) {           // (0) 0.06977
/*36 */             access_size_max = align_size_max;                                    // (4) 0.05349
/*38 */         }                                                                        // (20) 0.0186
/*40 */     }                                                                            // (24) 0.009302
/*44 */     /* Don't attempt accesses larger than the maximum.  */                       // (10) 0.03721
/*46 */     if (l > access_size_max) {                                                   // (17) 0.03256
/*48 */         l = access_size_max;                                                     // (14) 0.03488
/*50 */     }                                                                            // (25) 0.009302
/*52 */     /* ??? The users of this function are wrong, not supporting minimums larger  // (7) 0.04186
/*54 */        than the remaining length.  C.f. memory.c:access_with_adjusted_size.  */  // (1) 0.06977
/*56 */     assert(l >= access_size_min);                                                // (18) 0.03023
/*60 */     return l;                                                                    // (21) 0.01395
/*62 */ }                                                                                // (27) 0.002326
