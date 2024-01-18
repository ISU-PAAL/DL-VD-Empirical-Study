// commit message FFmpeg@2162b862eb (target=1, prob=0.68322664, correct=True): avcodec/magicyuv: Check len to be supported
/*0  */ static int huff_build10(VLC *vlc, uint8_t *len)                          // (7) 0.04393
/*2  */ {                                                                        // (24) 0.002092
/*4  */     HuffEntry he[1024];                                                  // (18) 0.01883
/*6  */     uint32_t codes[1024];                                                // (16) 0.02301
/*8  */     uint8_t bits[1024];                                                  // (17) 0.02301
/*10 */     uint16_t syms[1024];                                                 // (15) 0.0251
/*12 */     uint32_t code;                                                       // (19) 0.01883
/*14 */     int i;                                                               // (21) 0.01255
/*18 */     for (i = 0; i < 1024; i++) {                                         // (13) 0.03347
/*20 */         he[i].sym = 1023 - i;                                            // (10) 0.03766
/*22 */         he[i].len = len[i];                                              // (12) 0.03556
/*26 */     }                                                                    // (22) 0.008368
/*28 */     AV_QSORT(he, 1024, HuffEntry, huff_cmp_len10);                       // (4) 0.05021
/*32 */     code = 1;                                                            // (20) 0.01464
/*34 */     for (i = 1023; i >= 0; i--) {                                        // (11) 0.03766
/*36 */         codes[i] = code >> (32 - he[i].len);                             // (6) 0.04812
/*38 */         bits[i]  = he[i].len;                                            // (9) 0.03975
/*40 */         syms[i]  = he[i].sym;                                            // (8) 0.04184
/*42 */         code += 0x80000000u >> (he[i].len - 1);                          // (5) 0.05021
/*44 */     }                                                                    // (23) 0.008368
/*48 */     ff_free_vlc(vlc);                                                    // (14) 0.0272
/*50 */     return ff_init_vlc_sparse(vlc, FFMIN(he[1023].len, 12), 1024,        // (3) 0.06485
/*52 */                               bits,  sizeof(*bits),  sizeof(*bits),      // (1) 0.08577
/*54 */                               codes, sizeof(*codes), sizeof(*codes),     // (2) 0.08159
/*56 */                               syms,  sizeof(*syms),  sizeof(*syms), 0);  // (0) 0.09623
/*58 */ }                                                                        // (25) 0.002092
