// commit message qemu@f090c9d4ad (target=0, prob=0.0065325894, correct=True): Add strict checking mode for softfp code.
/*0  */ int float64_eq( float64 a, float64 b STATUS_PARAM )                              // (5) 0.08407
/*2  */ {                                                                                // (10) 0.004425
/*6  */     if (    ( ( extractFloat64Exp( a ) == 0x7FF ) && extractFloat64Frac( a ) )   // (2) 0.146
/*8  */          || ( ( extractFloat64Exp( b ) == 0x7FF ) && extractFloat64Frac( b ) )   // (1) 0.1504
/*10 */        ) {                                                                       // (7) 0.0354
/*12 */         if ( float64_is_signaling_nan( a ) || float64_is_signaling_nan( b ) ) {  // (0) 0.1593
/*14 */             float_raise( float_flag_invalid STATUS_VAR);                         // (3) 0.1195
/*16 */         }                                                                        // (8) 0.0354
/*18 */         return 0;                                                                // (6) 0.04425
/*20 */     }                                                                            // (9) 0.0177
/*22 */     return ( a == b ) || ( (bits64) ( ( a | b )<<1 ) == 0 );                     // (4) 0.1195
/*26 */ }                                                                                // (11) 0.004425
