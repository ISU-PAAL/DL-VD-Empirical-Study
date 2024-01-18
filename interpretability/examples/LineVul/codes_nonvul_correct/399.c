// commit message qemu@d1eb8f2acb (target=0, prob=0.012147589, correct=True): fpu: add mechanism to check for invalid long double formats
/*0  */ int floatx80_eq(floatx80 a, floatx80 b, float_status *status)          // (6) 0.06845
/*2  */ {                                                                      // (15) 0.002976
/*6  */     if (    (    ( extractFloatx80Exp( a ) == 0x7FFF )                 // (4) 0.08333
/*8  */               && (uint64_t) ( extractFloatx80Frac( a )<<1 ) )          // (1) 0.1012
/*10 */          || (    ( extractFloatx80Exp( b ) == 0x7FFF )                 // (3) 0.08631
/*12 */               && (uint64_t) ( extractFloatx80Frac( b )<<1 ) )          // (2) 0.1012
/*14 */        ) {                                                             // (12) 0.02381
/*16 */         float_raise(float_flag_invalid, status);                       // (8) 0.05952
/*18 */         return 0;                                                      // (11) 0.02976
/*20 */     }                                                                  // (13) 0.0119
/*22 */     return                                                             // (14) 0.0119
/*24 */            ( a.low == b.low )                                          // (9) 0.05655
/*26 */         && (    ( a.high == b.high )                                   // (7) 0.0625
/*28 */              || (    ( a.low == 0 )                                    // (5) 0.07143
/*30 */                   && ( (uint16_t) ( ( a.high | b.high )<<1 ) == 0 ) )  // (0) 0.125
/*32 */            );                                                          // (10) 0.03274
/*36 */ }                                                                      // (16) 0.002976
