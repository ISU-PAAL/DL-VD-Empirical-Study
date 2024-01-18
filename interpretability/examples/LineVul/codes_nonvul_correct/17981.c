// commit message qemu@7bbcb0afe7 (target=0, prob=0.46179658, correct=True): target-arm: use clz32() instead of a for loop
/*0  */ uint32_t HELPER(clz)(uint32_t x)  // (0) 0.2388
/*2  */ {                                 // (5) 0.01493
/*4  */     int count;                    // (4) 0.08955
/*6  */     for (count = 32; x; count--)  // (1) 0.209
/*8  */         x >>= 1;                  // (2) 0.1791
/*10 */     return count;                 // (3) 0.08955
/*12 */ }                                 // (6) 0.01493
