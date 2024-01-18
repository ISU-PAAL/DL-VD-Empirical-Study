// commit message qemu@185698715d (target=0, prob=0.0057279407, correct=True): softfloat: Rename float*_is_nan() functions to float*_is_quiet_nan()
/*0  */ uint64_t helper_fnmadd (uint64_t arg1, uint64_t arg2, uint64_t arg3)                    // (7) 0.06055
/*2  */ {                                                                                       // (20) 0.001953
/*4  */     CPU_DoubleU farg1, farg2, farg3;                                                    // (10) 0.03711
/*8  */     farg1.ll = arg1;                                                                    // (14) 0.02344
/*10 */     farg2.ll = arg2;                                                                    // (15) 0.02344
/*12 */     farg3.ll = arg3;                                                                    // (16) 0.02344
/*16 */     if (unlikely(float64_is_signaling_nan(farg1.d) ||                                   // (8) 0.04883
/*18 */                  float64_is_signaling_nan(farg2.d) ||                                   // (4) 0.06445
/*20 */                  float64_is_signaling_nan(farg3.d))) {                                  // (6) 0.06445
/*22 */         /* sNaN operation */                                                            // (13) 0.02539
/*24 */         farg1.ll = fload_invalid_op_excp(POWERPC_EXCP_FP_VXSNAN);                       // (2) 0.07422
/*26 */     } else if (unlikely((float64_is_infinity(farg1.d) && float64_is_zero(farg2.d)) ||   // (1) 0.07617
/*28 */                         (float64_is_zero(farg1.d) && float64_is_infinity(farg2.d)))) {  // (0) 0.1035
/*30 */         /* Multiplication of zero by infinity */                                        // (12) 0.03125
/*32 */         farg1.ll = fload_invalid_op_excp(POWERPC_EXCP_FP_VXIMZ);                        // (3) 0.07422
/*34 */     } else {                                                                            // (19) 0.01172
/*36 */ #if USE_PRECISE_EMULATION                                                               // (17) 0.02148
/*38 */ #ifdef FLOAT128                                                                         // (18) 0.01367
/*40 */         /* This is the way the PowerPC specification defines it */                      // (9) 0.03711
/*42 */         float128 ft0_128, ft1_128;                                                      // (11) 0.03711
/*46 */         ft0_128 = float64_to_float128(farg1.d, &env->fp_status);                        // (5) 0.06445
/*48 */         ft1_128 = float64_to_float128(farg2.d, &env->fp_status);                        // 0.0
/*50 */         ft0_128 = float128_mul(ft0_128, ft1_128, &env->fp_status);                      // 0.0
/*52 */         if (unlikely(float128_is_infinity(ft0_128) && float64_is_infinity(farg3.d) &&   // 0.0
/*54 */                      float128_is_neg(ft0_128) != float64_is_neg(farg3.d))) {            // 0.0
/*56 */             /* Magnitude subtraction of infinities */                                   // 0.0
/*58 */             farg1.ll = fload_invalid_op_excp(POWERPC_EXCP_FP_VXISI);                    // 0.0
/*60 */         } else {                                                                        // 0.0
/*62 */             ft1_128 = float64_to_float128(farg3.d, &env->fp_status);                    // 0.0
/*64 */             ft0_128 = float128_add(ft0_128, ft1_128, &env->fp_status);                  // 0.0
/*66 */             farg1.d = float128_to_float64(ft0_128, &env->fp_status);                    // 0.0
/*68 */         }                                                                               // 0.0
/*70 */ #else                                                                                   // 0.0
/*72 */         /* This is OK on x86 hosts */                                                   // 0.0
/*74 */         farg1.d = (farg1.d * farg2.d) + farg3.d;                                        // 0.0
/*76 */ #endif                                                                                  // 0.0
/*78 */ #else                                                                                   // 0.0
/*80 */         farg1.d = float64_mul(farg1.d, farg2.d, &env->fp_status);                       // 0.0
/*82 */         farg1.d = float64_add(farg1.d, farg3.d, &env->fp_status);                       // 0.0
/*84 */ #endif                                                                                  // 0.0
/*86 */         if (likely(!float64_is_nan(farg1.d)))                                           // 0.0
/*88 */             farg1.d = float64_chs(farg1.d);                                             // 0.0
/*90 */     }                                                                                   // 0.0
/*92 */     return farg1.ll;                                                                    // 0.0
/*94 */ }                                                                                       // 0.0
