// commit message qemu@e8ede0a8bb (target=0, prob=0.0049364036, correct=True): unicore32: Split UniCore-F64 instruction helpers from helper.c
/*0 */ float32 HELPER(ucf64_subs)(float32 a, float32 b, CPUUniCore32State *env)  // (0) 0.4603
/*2 */ {                                                                         // (2) 0.01587
/*4 */     return float32_sub(a, b, &env->ucf64.fp_status);                      // (1) 0.381
/*6 */ }                                                                         // (3) 0.01587
