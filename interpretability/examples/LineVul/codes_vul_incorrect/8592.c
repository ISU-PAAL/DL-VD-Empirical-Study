// commit message qemu@8417cebfda (target=1, prob=0.19045128, correct=False): memory: use signed arithmetic
/*0  */ static AddrRange addrrange_intersection(AddrRange r1, AddrRange r2)    // (1) 0.1833
/*2  */ {                                                                      // (5) 0.008333
/*4  */     uint64_t start = MAX(r1.start, r2.start);                          // (2) 0.175
/*6  */     /* off-by-one arithmetic to prevent overflow */                    // (4) 0.1167
/*8  */     uint64_t end = MIN(addrrange_end(r1) - 1, addrrange_end(r2) - 1);  // (0) 0.275
/*10 */     return addrrange_make(start, end - start + 1);                     // (3) 0.1417
/*12 */ }                                                                      // (6) 0.008333
