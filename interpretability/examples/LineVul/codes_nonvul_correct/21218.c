// commit message qemu@970d622e8a (target=0, prob=0.40394711, correct=True): target-alpha: fix cmpbge instruction
/*0  */ uint64_t helper_cmpbge (uint64_t op1, uint64_t op2)  // (0) 0.1446
/*2  */ {                                                    // (11) 0.006024
/*4  */     uint8_t opa, opb, res;                           // (5) 0.09036
/*6  */     int i;                                           // (9) 0.03614
/*10 */     res = 0;                                         // (7) 0.04217
/*12 */     for (i = 0; i < 7; i++) {                        // (4) 0.09639
/*14 */         opa = op1 >> (i * 8);                        // (1) 0.1084
/*16 */         opb = op2 >> (i * 8);                        // (2) 0.1084
/*18 */         if (opa >= opb)                              // (6) 0.08434
/*20 */             res |= 1 << i;                           // (3) 0.1084
/*22 */     }                                                // (10) 0.0241
/*24 */     return res;                                      // (8) 0.03614
/*26 */ }                                                    // (12) 0.006024
