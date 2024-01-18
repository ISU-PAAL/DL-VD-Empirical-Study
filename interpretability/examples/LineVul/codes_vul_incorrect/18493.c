// commit message qemu@e6afc87f80 (target=1, prob=0.38541922, correct=False): softfloat: Add new flag for when denormal result is flushed to zero
/*0   */ static float64 roundAndPackFloat64( flag zSign, int16 zExp, uint64_t zSig STATUS_PARAM)  // (3) 0.06055
/*2   */ {                                                                                        // (28) 0.001953
/*4   */     int8 roundingMode;                                                                   // (24) 0.01562
/*6   */     flag roundNearestEven;                                                               // (21) 0.01758
/*8   */     int16 roundIncrement, roundBits;                                                     // (14) 0.02539
/*10  */     flag isTiny;                                                                         // (23) 0.01563
/*14  */     roundingMode = STATUS(float_rounding_mode);                                          // (12) 0.03125
/*16  */     roundNearestEven = ( roundingMode == float_round_nearest_even );                     // (5) 0.04102
/*18  */     roundIncrement = 0x200;                                                              // (20) 0.02148
/*20  */     if ( ! roundNearestEven ) {                                                          // (16) 0.02344
/*22  */         if ( roundingMode == float_round_to_zero ) {                                     // (7) 0.04102
/*24  */             roundIncrement = 0;                                                          // (11) 0.0332
/*26  */         }                                                                                // (25) 0.01562
/*28  */         else {                                                                           // (22) 0.01758
/*30  */             roundIncrement = 0x3FF;                                                      // (9) 0.03906
/*32  */             if ( zSign ) {                                                               // (10) 0.0332
/*34  */                 if ( roundingMode == float_round_up ) roundIncrement = 0;                // (1) 0.0625
/*36  */             }                                                                            // (17) 0.02344
/*38  */             else {                                                                       // (15) 0.02539
/*40  */                 if ( roundingMode == float_round_down ) roundIncrement = 0;              // (2) 0.0625
/*42  */             }                                                                            // (18) 0.02344
/*44  */         }                                                                                // (26) 0.01562
/*46  */     }                                                                                    // (27) 0.007812
/*48  */     roundBits = zSig & 0x3FF;                                                            // (13) 0.03125
/*50  */     if ( 0x7FD <= (uint16_t) zExp ) {                                                    // (8) 0.03906
/*52  */         if (    ( 0x7FD < zExp )                                                         // (6) 0.04102
/*54  */              || (    ( zExp == 0x7FD )                                                   // (4) 0.05078
/*56  */                   && ( (int64_t) ( zSig + roundIncrement ) < 0 ) )                       // (0) 0.07422
/*58  */            ) {                                                                           // (19) 0.02344
/*60  */             float_raise( float_flag_overflow | float_flag_inexact STATUS_VAR);           // 0.0
/*62  */             return packFloat64( zSign, 0x7FF, - ( roundIncrement == 0 ));                // 0.0
/*64  */         }                                                                                // 0.0
/*66  */         if ( zExp < 0 ) {                                                                // 0.0
/*68  */             if ( STATUS(flush_to_zero) ) return packFloat64( zSign, 0, 0 );              // 0.0
/*70  */             isTiny =                                                                     // 0.0
/*72  */                    ( STATUS(float_detect_tininess) == float_tininess_before_rounding )   // 0.0
/*74  */                 || ( zExp < -1 )                                                         // 0.0
/*76  */                 || ( zSig + roundIncrement < LIT64( 0x8000000000000000 ) );              // 0.0
/*78  */             shift64RightJamming( zSig, - zExp, &zSig );                                  // 0.0
/*80  */             zExp = 0;                                                                    // 0.0
/*82  */             roundBits = zSig & 0x3FF;                                                    // 0.0
/*84  */             if ( isTiny && roundBits ) float_raise( float_flag_underflow STATUS_VAR);    // 0.0
/*86  */         }                                                                                // 0.0
/*88  */     }                                                                                    // 0.0
/*90  */     if ( roundBits ) STATUS(float_exception_flags) |= float_flag_inexact;                // 0.0
/*92  */     zSig = ( zSig + roundIncrement )>>10;                                                // 0.0
/*94  */     zSig &= ~ ( ( ( roundBits ^ 0x200 ) == 0 ) & roundNearestEven );                     // 0.0
/*96  */     if ( zSig == 0 ) zExp = 0;                                                           // 0.0
/*98  */     return packFloat64( zSign, zExp, zSig );                                             // 0.0
/*102 */ }                                                                                        // 0.0
