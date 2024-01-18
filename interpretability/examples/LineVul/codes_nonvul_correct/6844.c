// commit message qemu@f090c9d4ad (target=0, prob=0.0064121922, correct=True): Add strict checking mode for softfp code.
/*0  */ INLINE int16 extractFloat64Exp( float64 a )  // (1) 0.325
/*2  */ {                                            // (2) 0.025
/*6  */     return ( a>>52 ) & 0x7FF;                // (0) 0.375
/*10 */ }                                            // (3) 0.025
