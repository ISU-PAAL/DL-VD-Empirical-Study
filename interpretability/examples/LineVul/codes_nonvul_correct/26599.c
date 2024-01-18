// commit message qemu@f090c9d4ad (target=0, prob=0.008200524, correct=True): Add strict checking mode for softfp code.
/*0  */ float32 int32_to_float32( int32 a STATUS_PARAM )                                     // (2) 0.1473
/*2  */ {                                                                                    // (6) 0.007752
/*4  */     flag zSign;                                                                      // (5) 0.05426
/*8  */     if ( a == 0 ) return 0;                                                          // (3) 0.09302
/*10 */     if ( a == (sbits32) 0x80000000 ) return packFloat32( 1, 0x9E, 0 );               // (1) 0.2403
/*12 */     zSign = ( a < 0 );                                                               // (4) 0.08527
/*14 */     return normalizeRoundAndPackFloat32( zSign, 0x9C, zSign ? - a : a STATUS_VAR );  // (0) 0.2558
/*18 */ }                                                                                    // (7) 0.007752
