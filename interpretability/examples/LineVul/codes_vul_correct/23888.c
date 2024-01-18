// commit message qemu@fbeadf50f2 (target=1, prob=0.9032345, correct=True): bitops: unify bitops_ffsl with the one in host-utils.h, call it bitops_ctzl
/*0  */ unsigned long find_next_zero_bit(const unsigned long *addr, unsigned long size,  // (2) 0.03906
/*2  */ 				 unsigned long offset)                                                       // (24) 0.01563
/*4  */ {                                                                                // (37) 0.001953
/*6  */     const unsigned long *p = addr + BITOP_WORD(offset);                          // (6) 0.03711
/*8  */     unsigned long result = offset & ~(BITS_PER_LONG-1);                          // (1) 0.04102
/*10 */     unsigned long tmp;                                                           // (30) 0.01367
/*14 */     if (offset >= size) {                                                        // (20) 0.01953
/*16 */         return size;                                                             // (21) 0.01953
/*18 */     }                                                                            // (33) 0.007812
/*20 */     size -= result;                                                              // (31) 0.01367
/*22 */     offset %= BITS_PER_LONG;                                                     // (17) 0.02734
/*24 */     if (offset) {                                                                // (25) 0.01562
/*26 */         tmp = *(p++);                                                            // (16) 0.02734
/*28 */         tmp |= ~0UL >> (BITS_PER_LONG - offset);                                 // (0) 0.04883
/*30 */         if (size < BITS_PER_LONG) {                                              // (5) 0.03906
/*32 */             goto found_first;                                                    // (15) 0.03125
/*34 */         }                                                                        // (27) 0.01562
/*36 */         if (~tmp) {                                                              // (19) 0.02344
/*38 */             goto found_middle;                                                   // (13) 0.03125
/*40 */         }                                                                        // (28) 0.01562
/*42 */         size -= BITS_PER_LONG;                                                   // (9) 0.0332
/*44 */         result += BITS_PER_LONG;                                                 // (10) 0.0332
/*46 */     }                                                                            // (36) 0.007812
/*48 */     while (size & ~(BITS_PER_LONG-1)) {                                          // (4) 0.03906
/*50 */         if (~(tmp = *(p++))) {                                                   // (7) 0.03516
/*52 */             goto found_middle;                                                   // (14) 0.03125
/*54 */         }                                                                        // (29) 0.01562
/*56 */         result += BITS_PER_LONG;                                                 // (12) 0.0332
/*58 */         size -= BITS_PER_LONG;                                                   // (11) 0.0332
/*60 */     }                                                                            // (35) 0.007812
/*62 */     if (!size) {                                                                 // (26) 0.01562
/*64 */         return result;                                                           // (22) 0.01953
/*66 */     }                                                                            // (34) 0.007812
/*68 */     tmp = *p;                                                                    // (23) 0.01563
/*72 */ found_first:                                                                     // (32) 0.007813
/*74 */     tmp |= ~0UL << size;                                                         // (18) 0.02344
/*76 */     if (tmp == ~0UL) {	/* Are any bits zero? */                                  // (3) 0.03906
/*78 */         return result + size;	/* Nope. */                                        // (8) 0.0332
/*80 */     }                                                                            // 0.0
/*82 */ found_middle:                                                                    // 0.0
/*84 */     return result + ffz(tmp);                                                    // 0.0
/*86 */ }                                                                                // 0.0
