// commit message qemu@b3a6a2e041 (target=1, prob=0.72623247, correct=True): softfloat: float*_to_int32_round_to_zero: don't assume int32 is 32 bits
/*0  */ int32 float64_to_int32_round_to_zero( float64 a STATUS_PARAM )                    // (4) 0.0504
/*2  */ {                                                                                 // (32) 0.002016
/*4  */     flag aSign;                                                                   // (24) 0.01411
/*6  */     int16 aExp, shiftCount;                                                       // (18) 0.02218
/*8  */     uint64_t aSig, savedASig;                                                     // (10) 0.03024
/*10 */     int32 z;                                                                      // (25) 0.01411
/*12 */     a = float64_squash_input_denormal(a STATUS_VAR);                              // (5) 0.04637
/*16 */     aSig = extractFloat64Frac( a );                                               // (9) 0.03024
/*18 */     aExp = extractFloat64Exp( a );                                                // (15) 0.02621
/*20 */     aSign = extractFloat64Sign( a );                                              // (14) 0.02621
/*22 */     if ( 0x41E < aExp ) {                                                         // (13) 0.02823
/*24 */         if ( ( aExp == 0x7FF ) && aSig ) aSign = 0;                               // (2) 0.05645
/*26 */         goto invalid;                                                             // (22) 0.02016
/*28 */     }                                                                             // (27) 0.008065
/*30 */     else if ( aExp < 0x3FF ) {                                                    // (12) 0.03024
/*32 */         if ( aExp || aSig ) STATUS(float_exception_flags) |= float_flag_inexact;  // (0) 0.07258
/*34 */         return 0;                                                                 // (21) 0.02016
/*36 */     }                                                                             // (28) 0.008065
/*38 */     aSig |= LIT64( 0x0010000000000000 );                                          // (8) 0.03629
/*40 */     shiftCount = 0x433 - aExp;                                                    // (16) 0.02621
/*42 */     savedASig = aSig;                                                             // (19) 0.02218
/*44 */     aSig >>= shiftCount;                                                          // (20) 0.02218
/*46 */     z = aSig;                                                                     // (23) 0.01815
/*48 */     if ( aSign ) z = - z;                                                         // (17) 0.02621
/*50 */     if ( ( z < 0 ) ^ aSign ) {                                                    // (11) 0.03024
/*52 */  invalid:                                                                         // (31) 0.004032
/*54 */         float_raise( float_flag_invalid STATUS_VAR);                              // (6) 0.04637
/*56 */         return aSign ? (int32_t) 0x80000000 : 0x7FFFFFFF;                         // (1) 0.05847
/*58 */     }                                                                             // (29) 0.008065
/*60 */     if ( ( aSig<<shiftCount ) != savedASig ) {                                    // (7) 0.03831
/*62 */         STATUS(float_exception_flags) |= float_flag_inexact;                      // (3) 0.05444
/*64 */     }                                                                             // (30) 0.008065
/*66 */     return z;                                                                     // (26) 0.0121
/*70 */ }                                                                                 // (33) 0.002016
