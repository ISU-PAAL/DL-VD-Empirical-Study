// commit message qemu@e8ede0a8bb (target=0, prob=0.0075509963, correct=True): unicore32: Split UniCore-F64 instruction helpers from helper.c
/*0 */ float32 HELPER(ucf64_abss)(float32 a)  // (0) 0.4324
/*2 */ {                                      // (2) 0.02703
/*4 */     return float32_abs(a);             // (1) 0.2973
/*6 */ }                                      // (3) 0.02703
