// commit message qemu@2958620f67 (target=1, prob=0.99751174, correct=True): target-alpha: Move integer overflow helpers to int_helper.c.
/*0  */ uint64_t helper_addlv (uint64_t op1, uint64_t op2)                     // (2) 0.1655
/*2  */ {                                                                      // (7) 0.007194
/*4  */     uint64_t tmp = op1;                                                // (4) 0.08633
/*6  */     op1 = (uint32_t)(op1 + op2);                                       // (3) 0.1295
/*8  */     if (unlikely((tmp ^ op2 ^ (-1UL)) & (tmp ^ op1) & (1UL << 31))) {  // (0) 0.2302
/*10 */         arith_excp(env, GETPC(), EXC_M_IOV, 0);                        // (1) 0.2014
/*12 */     }                                                                  // (6) 0.02878
/*14 */     return op1;                                                        // (5) 0.05036
/*16 */ }                                                                      // (8) 0.007194
