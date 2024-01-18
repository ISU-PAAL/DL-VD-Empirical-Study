// commit message FFmpeg@45198477de (target=1, prob=0.07292561, correct=False): avcodec/simple_idct_template: Fix several integer overflows
/*0   */ static inline void FUNC(idctRowCondDC_extrashift)(int16_t *row, int extra_shift)                       // (3) 0.05664
/*2   */ #else                                                                                                  // (23) 0.003906
/*4   */ static inline void FUNC(idctRowCondDC)(int16_t *row, int extra_shift)                                  // (5) 0.04688
/*6   */ #endif                                                                                                 // (24) 0.003906
/*8   */ {                                                                                                      // (26) 0.001953
/*10  */     int a0, a1, a2, a3, b0, b1, b2, b3;                                                                // (4) 0.05469
/*14  */ #if HAVE_FAST_64BIT                                                                                    // (19) 0.01758
/*16  */ #define ROW0_MASK (0xffffLL << 48 * HAVE_BIGENDIAN)                                                    // (6) 0.04492
/*18  */     if (((AV_RN64A(row) & ~ROW0_MASK) | AV_RN64A(row+4)) == 0) {                                       // (1) 0.07422
/*20  */         uint64_t temp;                                                                                 // (16) 0.02539
/*22  */         if (DC_SHIFT - extra_shift >= 0) {                                                             // (7) 0.04102
/*24  */             temp = (row[0] * (1 << (DC_SHIFT - extra_shift))) & 0xffff;                                // (2) 0.07227
/*26  */         } else {                                                                                       // (18) 0.01953
/*28  */             temp = ((row[0] + (1<<(extra_shift - DC_SHIFT-1))) >> (extra_shift - DC_SHIFT)) & 0xffff;  // (0) 0.09766
/*30  */         }                                                                                              // (21) 0.01562
/*32  */         temp += temp * (1 << 16);                                                                      // (14) 0.03125
/*34  */         temp += temp * ((uint64_t) 1 << 32);                                                           // (8) 0.04102
/*36  */         AV_WN64A(row, temp);                                                                           // (13) 0.0332
/*38  */         AV_WN64A(row + 4, temp);                                                                       // (11) 0.03711
/*40  */         return;                                                                                        // (20) 0.01758
/*42  */     }                                                                                                  // (22) 0.007813
/*44  */ #else                                                                                                  // (25) 0.003906
/*46  */     if (!(AV_RN32A(row+2) |                                                                            // (12) 0.0332
/*48  */           AV_RN32A(row+4) |                                                                            // (9) 0.03906
/*50  */           AV_RN32A(row+6) |                                                                            // (10) 0.03906
/*52  */           row[1])) {                                                                                   // (15) 0.0293
/*54  */         uint32_t temp;                                                                                 // (17) 0.02539
/*56  */         if (DC_SHIFT - extra_shift >= 0) {                                                             // 0.0
/*58  */             temp = (row[0] * (1 << (DC_SHIFT - extra_shift))) & 0xffff;                                // 0.0
/*60  */         } else {                                                                                       // 0.0
/*62  */             temp = ((row[0] + (1<<(extra_shift - DC_SHIFT-1))) >> (extra_shift - DC_SHIFT)) & 0xffff;  // 0.0
/*64  */         }                                                                                              // 0.0
/*66  */         temp += temp * (1 << 16);                                                                      // 0.0
/*68  */         AV_WN32A(row, temp);                                                                           // 0.0
/*70  */         AV_WN32A(row+2, temp);                                                                         // 0.0
/*72  */         AV_WN32A(row+4, temp);                                                                         // 0.0
/*74  */         AV_WN32A(row+6, temp);                                                                         // 0.0
/*76  */         return;                                                                                        // 0.0
/*78  */     }                                                                                                  // 0.0
/*80  */ #endif                                                                                                 // 0.0
/*84  */     a0 = (W4 * row[0]) + (1 << (ROW_SHIFT + extra_shift - 1));                                         // 0.0
/*86  */     a1 = a0;                                                                                           // 0.0
/*88  */     a2 = a0;                                                                                           // 0.0
/*90  */     a3 = a0;                                                                                           // 0.0
/*94  */     a0 += W2 * row[2];                                                                                 // 0.0
/*96  */     a1 += W6 * row[2];                                                                                 // 0.0
/*98  */     a2 -= W6 * row[2];                                                                                 // 0.0
/*100 */     a3 -= W2 * row[2];                                                                                 // 0.0
/*104 */     b0 = MUL(W1, row[1]);                                                                              // 0.0
/*106 */     MAC(b0, W3, row[3]);                                                                               // 0.0
/*108 */     b1 = MUL(W3, row[1]);                                                                              // 0.0
/*110 */     MAC(b1, -W7, row[3]);                                                                              // 0.0
/*112 */     b2 = MUL(W5, row[1]);                                                                              // 0.0
/*114 */     MAC(b2, -W1, row[3]);                                                                              // 0.0
/*116 */     b3 = MUL(W7, row[1]);                                                                              // 0.0
/*118 */     MAC(b3, -W5, row[3]);                                                                              // 0.0
/*122 */     if (AV_RN64A(row + 4)) {                                                                           // 0.0
/*124 */         a0 +=   W4*row[4] + W6*row[6];                                                                 // 0.0
/*126 */         a1 += - W4*row[4] - W2*row[6];                                                                 // 0.0
/*128 */         a2 += - W4*row[4] + W2*row[6];                                                                 // 0.0
/*130 */         a3 +=   W4*row[4] - W6*row[6];                                                                 // 0.0
/*134 */         MAC(b0,  W5, row[5]);                                                                          // 0.0
/*136 */         MAC(b0,  W7, row[7]);                                                                          // 0.0
/*140 */         MAC(b1, -W1, row[5]);                                                                          // 0.0
/*142 */         MAC(b1, -W5, row[7]);                                                                          // 0.0
/*146 */         MAC(b2,  W7, row[5]);                                                                          // 0.0
/*148 */         MAC(b2,  W3, row[7]);                                                                          // 0.0
/*152 */         MAC(b3,  W3, row[5]);                                                                          // 0.0
/*154 */         MAC(b3, -W1, row[7]);                                                                          // 0.0
/*156 */     }                                                                                                  // 0.0
/*160 */     row[0] = (a0 + b0) >> (ROW_SHIFT + extra_shift);                                                   // 0.0
/*162 */     row[7] = (a0 - b0) >> (ROW_SHIFT + extra_shift);                                                   // 0.0
/*164 */     row[1] = (a1 + b1) >> (ROW_SHIFT + extra_shift);                                                   // 0.0
/*166 */     row[6] = (a1 - b1) >> (ROW_SHIFT + extra_shift);                                                   // 0.0
/*168 */     row[2] = (a2 + b2) >> (ROW_SHIFT + extra_shift);                                                   // 0.0
/*170 */     row[5] = (a2 - b2) >> (ROW_SHIFT + extra_shift);                                                   // 0.0
/*172 */     row[3] = (a3 + b3) >> (ROW_SHIFT + extra_shift);                                                   // 0.0
/*174 */     row[4] = (a3 - b3) >> (ROW_SHIFT + extra_shift);                                                   // 0.0
/*176 */ }                                                                                                      // 0.0
