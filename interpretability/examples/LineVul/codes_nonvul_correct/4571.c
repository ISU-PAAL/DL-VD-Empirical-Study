// commit message qemu@e8ede0a8bb (target=0, prob=0.006092758, correct=True): unicore32: Split UniCore-F64 instruction helpers from helper.c
/*0 */ float64 HELPER(ucf64_absd)(float64 a)  // (0) 0.4324
/*2 */ {                                      // (3) 0.02702
/*4 */     return float64_abs(a);             // (1) 0.2972
/*6 */ }                                      // (2) 0.02702
