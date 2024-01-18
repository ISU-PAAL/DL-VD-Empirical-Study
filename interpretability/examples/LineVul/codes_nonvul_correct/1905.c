// commit message qemu@ba0e276db4 (target=0, prob=0.04854934, correct=True): target-alpha: Fixes for alpha-linux syscalls.
/*0  */ void helper_store_fpcr (uint64_t val)                                   // (5) 0.05072
/*2  */ {                                                                       // (18) 0.003623
/*4  */ #ifdef CONFIG_SOFTFLOAT                                                 // (7) 0.03623
/*6  */     set_float_exception_flags((val >> 52) & 0x3F, &FP_STATUS);          // (2) 0.1014
/*8  */ #endif                                                                  // (17) 0.007246
/*10 */     switch ((val >> 58) & 3) {                                          // (6) 0.0471
/*12 */     case 0:                                                             // (12) 0.02174
/*14 */         set_float_rounding_mode(float_round_to_zero, &FP_STATUS);       // (1) 0.1087
/*16 */         break;                                                          // (8) 0.03261
/*18 */     case 1:                                                             // (13) 0.02174
/*20 */         set_float_rounding_mode(float_round_down, &FP_STATUS);          // (3) 0.1014
/*22 */         break;                                                          // (9) 0.03261
/*24 */     case 2:                                                             // (14) 0.02174
/*26 */         set_float_rounding_mode(float_round_nearest_even, &FP_STATUS);  // (0) 0.1123
/*28 */         break;                                                          // (10) 0.03261
/*30 */     case 3:                                                             // (15) 0.02174
/*32 */         set_float_rounding_mode(float_round_up, &FP_STATUS);            // (4) 0.1014
/*34 */         break;                                                          // (11) 0.03261
/*36 */     }                                                                   // (16) 0.01449
/*38 */ }                                                                       // (19) 0.003623
