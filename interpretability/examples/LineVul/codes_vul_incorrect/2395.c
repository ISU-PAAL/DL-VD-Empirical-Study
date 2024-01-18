// commit message qemu@e167adc9d9 (target=1, prob=0.48785183, correct=False): target-arm: A64: Fix handling of rotate in logic_imm_decode_wmask
/*0   */ static bool logic_imm_decode_wmask(uint64_t *result, unsigned int immn,   // (6) 0.04688
/*2   */                                    unsigned int imms, unsigned int immr)  // (0) 0.08594
/*4   */ {                                                                         // (24) 0.001954
/*6   */     uint64_t mask;                                                        // (20) 0.01758
/*8   */     unsigned e, levels, s, r;                                             // (19) 0.02344
/*10  */     int len;                                                              // (21) 0.01172
/*14  */     assert(immn < 2 && imms < 64 && immr < 64);                           // (11) 0.03906
/*18  */     /* The bit patterns we create here are 64 bit patterns which          // (16) 0.0293
/*20  */      * are vectors of identical elements of size e = 2, 4, 8, 16, 32 or   // (7) 0.04687
/*22  */      * 64 bits each. Each element contains the same value: a run          // (14) 0.03516
/*24  */      * of between 1 and e-1 non-zero bits, rotated within the             // (13) 0.03906
/*26  */      * element by between 0 and e-1 bits.                                 // (17) 0.0293
/*28  */      *                                                                    // (22) 0.009766
/*30  */      * The element size and run length are encoded into immn (1 bit)      // (12) 0.03906
/*32  */      * and imms (6 bits) as follows:                                      // (18) 0.0293
/*34  */      * 64 bit elements: immn = 1, imms = <length of run - 1>              // (8) 0.04687
/*36  */      * 32 bit elements: immn = 0, imms = 0 : <length of run - 1>          // (5) 0.05078
/*38  */      * 16 bit elements: immn = 0, imms = 10 : <length of run - 1>         // (4) 0.05078
/*40  */      *  8 bit elements: immn = 0, imms = 110 : <length of run - 1>        // (3) 0.05273
/*42  */      *  4 bit elements: immn = 0, imms = 1110 : <length of run - 1>       // (2) 0.05469
/*44  */      *  2 bit elements: immn = 0, imms = 11110 : <length of run - 1>      // (1) 0.05469
/*46  */      * Notice that immn = 0, imms = 11111x is the only combination        // (10) 0.04297
/*48  */      * not covered by one of the above options; this is reserved.         // (15) 0.03516
/*50  */      * Further, <length of run - 1> all-ones is a reserved pattern.       // (9) 0.04297
/*52  */      *                                                                    // (23) 0.009766
/*54  */      * In all cases the rotation is by immr % e (and immr is 6 bits).     // 0.0
/*56  */      */                                                                   // 0.0
/*60  */     /* First determine the element size */                                // 0.0
/*62  */     len = 31 - clz32((immn << 6) | (~imms & 0x3f));                       // 0.0
/*64  */     if (len < 1) {                                                        // 0.0
/*66  */         /* This is the immn == 0, imms == 0x11111x case */                // 0.0
/*68  */         return false;                                                     // 0.0
/*70  */     }                                                                     // 0.0
/*72  */     e = 1 << len;                                                         // 0.0
/*76  */     levels = e - 1;                                                       // 0.0
/*78  */     s = imms & levels;                                                    // 0.0
/*80  */     r = immr & levels;                                                    // 0.0
/*84  */     if (s == levels) {                                                    // 0.0
/*86  */         /* <length of run - 1> mustn't be all-ones. */                    // 0.0
/*88  */         return false;                                                     // 0.0
/*90  */     }                                                                     // 0.0
/*94  */     /* Create the value of one element: s+1 set bits rotated              // 0.0
/*96  */      * by r within the element (which is e bits wide)...                  // 0.0
/*98  */      */                                                                   // 0.0
/*100 */     mask = bitmask64(s + 1);                                              // 0.0
/*102 */     mask = (mask >> r) | (mask << (e - r));                               // 0.0
/*104 */     /* ...then replicate the element over the whole 64 bit value */       // 0.0
/*106 */     mask = bitfield_replicate(mask, e);                                   // 0.0
/*108 */     *result = mask;                                                       // 0.0
/*110 */     return true;                                                          // 0.0
/*112 */ }                                                                         // 0.0
