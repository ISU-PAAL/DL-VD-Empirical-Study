// commit message FFmpeg@452ac2aaec (target=0, prob=0.034208223, correct=True): lavu/ripemd: Fully unroll the transform function loops
/*0   */ static void ripemd160_transform(uint32_t *state, const uint8_t buffer[64], int ext)  // (7) 0.05469
/*2   */ {                                                                                    // (22) 0.001954
/*4   */     uint32_t a, b, c, d, e, f, g, h, i, j;                                           // (8) 0.05273
/*6   */     uint32_t block[16];                                                              // (17) 0.02148
/*8   */     int n;                                                                           // (20) 0.01172
/*12  */     if (ext) {                                                                       // (18) 0.01562
/*14  */         a = state[0]; b = state[1]; c = state[2]; d = state[3]; e = state[4];        // (0) 0.07227
/*16  */         f = state[5]; g = state[6]; h = state[7]; i = state[8]; j = state[9];        // (3) 0.07227
/*18  */     } else {                                                                         // (19) 0.01172
/*20  */         a = f = state[0];                                                            // (14) 0.0293
/*22  */         b = g = state[1];                                                            // (12) 0.0293
/*24  */         c = h = state[2];                                                            // (13) 0.0293
/*26  */         d = i = state[3];                                                            // (15) 0.0293
/*28  */         e = j = state[4];                                                            // (16) 0.0293
/*30  */     }                                                                                // (21) 0.007812
/*34  */     for (n = 0; n < 16; n++)                                                         // (11) 0.0293
/*36  */         block[n] = AV_RL32(buffer + 4 * n);                                          // (9) 0.04492
/*40  */     for (n = 0; n < 16 - 1;) {                                                       // (10) 0.0332
/*42  */         ROUND160_0_TO_15(a,b,c,d,e,f,g,h,i,j);                                       // (5) 0.07227
/*44  */         ROUND160_0_TO_15(e,a,b,c,d,j,f,g,h,i);                                       // (6) 0.07227
/*46  */         ROUND160_0_TO_15(d,e,a,b,c,i,j,f,g,h);                                       // (1) 0.07227
/*48  */         ROUND160_0_TO_15(c,d,e,a,b,h,i,j,f,g);                                       // (4) 0.07227
/*50  */         ROUND160_0_TO_15(b,c,d,e,a,g,h,i,j,f);                                       // (2) 0.07227
/*52  */     }                                                                                // 0.0
/*54  */     ROUND160_0_TO_15(a,b,c,d,e,f,g,h,i,j);                                           // 0.0
/*56  */     SWAP(a,f)                                                                        // 0.0
/*60  */     for (; n < 32 - 1;) {                                                            // 0.0
/*62  */         ROUND160_16_TO_31(e,a,b,c,d,j,f,g,h,i);                                      // 0.0
/*64  */         ROUND160_16_TO_31(d,e,a,b,c,i,j,f,g,h);                                      // 0.0
/*66  */         ROUND160_16_TO_31(c,d,e,a,b,h,i,j,f,g);                                      // 0.0
/*68  */         ROUND160_16_TO_31(b,c,d,e,a,g,h,i,j,f);                                      // 0.0
/*70  */         ROUND160_16_TO_31(a,b,c,d,e,f,g,h,i,j);                                      // 0.0
/*72  */     }                                                                                // 0.0
/*74  */     ROUND160_16_TO_31(e,a,b,c,d,j,f,g,h,i);                                          // 0.0
/*76  */     SWAP(b,g)                                                                        // 0.0
/*80  */     for (; n < 48 - 1;) {                                                            // 0.0
/*82  */         ROUND160_32_TO_47(d,e,a,b,c,i,j,f,g,h);                                      // 0.0
/*84  */         ROUND160_32_TO_47(c,d,e,a,b,h,i,j,f,g);                                      // 0.0
/*86  */         ROUND160_32_TO_47(b,c,d,e,a,g,h,i,j,f);                                      // 0.0
/*88  */         ROUND160_32_TO_47(a,b,c,d,e,f,g,h,i,j);                                      // 0.0
/*90  */         ROUND160_32_TO_47(e,a,b,c,d,j,f,g,h,i);                                      // 0.0
/*92  */     }                                                                                // 0.0
/*94  */     ROUND160_32_TO_47(d,e,a,b,c,i,j,f,g,h);                                          // 0.0
/*96  */     SWAP(c,h)                                                                        // 0.0
/*100 */     for (; n < 64 - 1;) {                                                            // 0.0
/*102 */         ROUND160_48_TO_63(c,d,e,a,b,h,i,j,f,g);                                      // 0.0
/*104 */         ROUND160_48_TO_63(b,c,d,e,a,g,h,i,j,f);                                      // 0.0
/*106 */         ROUND160_48_TO_63(a,b,c,d,e,f,g,h,i,j);                                      // 0.0
/*108 */         ROUND160_48_TO_63(e,a,b,c,d,j,f,g,h,i);                                      // 0.0
/*110 */         ROUND160_48_TO_63(d,e,a,b,c,i,j,f,g,h);                                      // 0.0
/*112 */     }                                                                                // 0.0
/*114 */     ROUND160_48_TO_63(c,d,e,a,b,h,i,j,f,g);                                          // 0.0
/*116 */     SWAP(d,i)                                                                        // 0.0
/*120 */     for (; n < 75;) {                                                                // 0.0
/*122 */         ROUND160_64_TO_79(b,c,d,e,a,g,h,i,j,f);                                      // 0.0
/*124 */         ROUND160_64_TO_79(a,b,c,d,e,f,g,h,i,j);                                      // 0.0
/*126 */         ROUND160_64_TO_79(e,a,b,c,d,j,f,g,h,i);                                      // 0.0
/*128 */         ROUND160_64_TO_79(d,e,a,b,c,i,j,f,g,h);                                      // 0.0
/*130 */         ROUND160_64_TO_79(c,d,e,a,b,h,i,j,f,g);                                      // 0.0
/*132 */     }                                                                                // 0.0
/*134 */     ROUND160_64_TO_79(b,c,d,e,a,g,h,i,j,f);                                          // 0.0
/*136 */     SWAP(e,j)                                                                        // 0.0
/*140 */     if (ext) {                                                                       // 0.0
/*142 */         state[0] += a; state[1] += b; state[2] += c; state[3] += d; state[4] += e;   // 0.0
/*144 */         state[5] += f; state[6] += g; state[7] += h; state[8] += i; state[9] += j;   // 0.0
/*146 */     } else {                                                                         // 0.0
/*148 */         i += c + state[1];                                                           // 0.0
/*150 */         state[1] = state[2] + d + j;                                                 // 0.0
/*152 */         state[2] = state[3] + e + f;                                                 // 0.0
/*154 */         state[3] = state[4] + a + g;                                                 // 0.0
/*156 */         state[4] = state[0] + b + h;                                                 // 0.0
/*158 */         state[0] = i;                                                                // 0.0
/*160 */     }                                                                                // 0.0
/*162 */ }                                                                                    // 0.0
