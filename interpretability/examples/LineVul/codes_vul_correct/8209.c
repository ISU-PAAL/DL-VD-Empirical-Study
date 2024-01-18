// commit message qemu@29851ee7c8 (target=1, prob=0.6263777, correct=True): target-mips: fix calculation of overflow for SHLL.PH and SHLL.QB
/*0  */ int main()                           // (15) 0.01271
/*2  */ {                                    // (16) 0.004237
/*4  */     int rd, rt, dsp;                 // (7) 0.05508
/*6  */     int result, resultdsp;           // (10) 0.04237
/*10 */     rt        = 0x12345678;          // (2) 0.08051
/*12 */     result    = 0xA000C000;          // (5) 0.06356
/*14 */     resultdsp = 1;                   // (11) 0.03814
/*18 */     __asm                            // (14) 0.02119
/*20 */         ("shll.ph %0, %2, 0x0B\n\t"  // (0) 0.1144
/*22 */          "rddsp %1\n\t"              // (3) 0.08051
/*24 */          : "=r"(rd), "=r"(dsp)       // (1) 0.09322
/*26 */          : "r"(rt)                   // (6) 0.05932
/*28 */         );                           // (12) 0.0339
/*30 */     dsp = (dsp >> 22) & 0x01;        // (4) 0.07203
/*32 */     assert(dsp == resultdsp);        // (8) 0.05085
/*34 */     assert(rd  == result);           // (9) 0.04237
/*38 */     return 0;                        // (13) 0.02542
/*40 */ }                                    // (17) 0.004237
