// commit message qemu@1bf6beec8a (target=1, prob=0.16650982, correct=False): softfloat: Fix exception flag handling for float32_to_float16()
/*0   */ float16 float32_to_float16(float32 a, flag ieee STATUS_PARAM)                                 // (5) 0.04492
/*2   */ {                                                                                             // (31) 0.001954
/*4   */     flag aSign;                                                                               // (28) 0.01367
/*6   */     int_fast16_t aExp;                                                                        // (19) 0.02344
/*8   */     uint32_t aSig;                                                                            // (21) 0.02148
/*10  */     uint32_t mask;                                                                            // (23) 0.01761
/*12  */     uint32_t increment;                                                                       // (24) 0.0176
/*14  */     int8 roundingMode;                                                                        // (25) 0.01563
/*16  */     a = float32_squash_input_denormal(a STATUS_VAR);                                          // (4) 0.04495
/*20  */     aSig = extractFloat32Frac( a );                                                           // (11) 0.0293
/*22  */     aExp = extractFloat32Exp( a );                                                            // (16) 0.02539
/*24  */     aSign = extractFloat32Sign( a );                                                          // (15) 0.02539
/*26  */     if ( aExp == 0xFF ) {                                                                     // (18) 0.02539
/*28  */         if (aSig) {                                                                           // (13) 0.02734
/*30  */             /* Input is a NaN */                                                              // (8) 0.03515
/*32  */             float16 r = commonNaNToFloat16( float32ToCommonNaN( a STATUS_VAR ) STATUS_VAR );  // (0) 0.08202
/*34  */             if (!ieee) {                                                                      // (10) 0.0332
/*36  */                 return packFloat16(aSign, 0, 0);                                              // (3) 0.05273
/*38  */             }                                                                                 // (20) 0.02343
/*40  */             return r;                                                                         // (14) 0.02734
/*42  */         }                                                                                     // (27) 0.01562
/*44  */         /* Infinity */                                                                        // (22) 0.01953
/*46  */         if (!ieee) {                                                                          // (17) 0.02539
/*48  */             float_raise(float_flag_invalid STATUS_VAR);                                       // (2) 0.05273
/*50  */             return packFloat16(aSign, 0x1f, 0x3ff);                                           // (1) 0.05663
/*52  */         }                                                                                     // (26) 0.01562
/*54  */         return packFloat16(aSign, 0x1f, 0);                                                   // (6) 0.04296
/*56  */     }                                                                                         // (29) 0.007811
/*58  */     if (aExp == 0 && aSig == 0) {                                                             // (9) 0.0332
/*60  */         return packFloat16(aSign, 0, 0);                                                      // (7) 0.0371
/*62  */     }                                                                                         // (30) 0.007811
/*64  */     /* Decimal point between bits 22 and 23.  */                                              // (12) 0.02929
/*66  */     aSig |= 0x00800000;                                                                       // 0.0
/*68  */     aExp -= 0x7f;                                                                             // 0.0
/*70  */     if (aExp < -14) {                                                                         // 0.0
/*72  */         mask = 0x00ffffff;                                                                    // 0.0
/*74  */         if (aExp >= -24) {                                                                    // 0.0
/*76  */             mask >>= 25 + aExp;                                                               // 0.0
/*78  */         }                                                                                     // 0.0
/*80  */     } else {                                                                                  // 0.0
/*82  */         mask = 0x00001fff;                                                                    // 0.0
/*84  */     }                                                                                         // 0.0
/*86  */     if (aSig & mask) {                                                                        // 0.0
/*88  */         float_raise( float_flag_underflow STATUS_VAR );                                       // 0.0
/*90  */         roundingMode = STATUS(float_rounding_mode);                                           // 0.0
/*92  */         switch (roundingMode) {                                                               // 0.0
/*94  */         case float_round_nearest_even:                                                        // 0.0
/*96  */             increment = (mask + 1) >> 1;                                                      // 0.0
/*98  */             if ((aSig & mask) == increment) {                                                 // 0.0
/*100 */                 increment = aSig & (increment << 1);                                          // 0.0
/*102 */             }                                                                                 // 0.0
/*104 */             break;                                                                            // 0.0
/*106 */         case float_round_up:                                                                  // 0.0
/*108 */             increment = aSign ? 0 : mask;                                                     // 0.0
/*110 */             break;                                                                            // 0.0
/*112 */         case float_round_down:                                                                // 0.0
/*114 */             increment = aSign ? mask : 0;                                                     // 0.0
/*116 */             break;                                                                            // 0.0
/*118 */         default: /* round_to_zero */                                                          // 0.0
/*120 */             increment = 0;                                                                    // 0.0
/*122 */             break;                                                                            // 0.0
/*124 */         }                                                                                     // 0.0
/*126 */         aSig += increment;                                                                    // 0.0
/*128 */         if (aSig >= 0x01000000) {                                                             // 0.0
/*130 */             aSig >>= 1;                                                                       // 0.0
/*132 */             aExp++;                                                                           // 0.0
/*134 */         }                                                                                     // 0.0
/*136 */     } else if (aExp < -14                                                                     // 0.0
/*138 */           && STATUS(float_detect_tininess) == float_tininess_before_rounding) {               // 0.0
/*140 */         float_raise( float_flag_underflow STATUS_VAR);                                        // 0.0
/*142 */     }                                                                                         // 0.0
/*146 */     if (ieee) {                                                                               // 0.0
/*148 */         if (aExp > 15) {                                                                      // 0.0
/*150 */             float_raise( float_flag_overflow | float_flag_inexact STATUS_VAR);                // 0.0
/*152 */             return packFloat16(aSign, 0x1f, 0);                                               // 0.0
/*154 */         }                                                                                     // 0.0
/*156 */     } else {                                                                                  // 0.0
/*158 */         if (aExp > 16) {                                                                      // 0.0
/*160 */             float_raise(float_flag_invalid | float_flag_inexact STATUS_VAR);                  // 0.0
/*162 */             return packFloat16(aSign, 0x1f, 0x3ff);                                           // 0.0
/*164 */         }                                                                                     // 0.0
/*166 */     }                                                                                         // 0.0
/*168 */     if (aExp < -24) {                                                                         // 0.0
/*170 */         return packFloat16(aSign, 0, 0);                                                      // 0.0
/*172 */     }                                                                                         // 0.0
/*174 */     if (aExp < -14) {                                                                         // 0.0
/*176 */         aSig >>= -14 - aExp;                                                                  // 0.0
/*178 */         aExp = -14;                                                                           // 0.0
/*180 */     }                                                                                         // 0.0
/*182 */     return packFloat16(aSign, aExp + 14, aSig >> 13);                                         // 0.0
/*184 */ }                                                                                             // 0.0
