// commit message qemu@f090c9d4ad (target=0, prob=0.006032968, correct=True): Add strict checking mode for softfp code.
/*0  */ int float64_eq_signaling( float64 a, float64 b STATUS_PARAM )                   // (4) 0.1229
/*2  */ {                                                                               // (8) 0.005587
/*6  */     if (    ( ( extractFloat64Exp( a ) == 0x7FF ) && extractFloat64Frac( a ) )  // (1) 0.1844
/*8  */          || ( ( extractFloat64Exp( b ) == 0x7FF ) && extractFloat64Frac( b ) )  // (0) 0.1899
/*10 */        ) {                                                                      // (6) 0.04469
/*12 */         float_raise( float_flag_invalid STATUS_VAR);                            // (3) 0.1285
/*14 */         return 0;                                                               // (5) 0.05587
/*16 */     }                                                                           // (7) 0.02235
/*18 */     return ( a == b ) || ( (bits64) ( ( a | b )<<1 ) == 0 );                    // (2) 0.1508
/*22 */ }                                                                               // (9) 0.005587
