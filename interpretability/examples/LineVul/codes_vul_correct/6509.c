// commit message FFmpeg@5d20f19be2 (target=1, prob=0.81439054, correct=True): aes: fix invalid array indexing in init code
/*0   */ int av_aes_init(AVAES *a, const uint8_t *key, int key_bits, int decrypt)               // (2) 0.05859
/*2   */ {                                                                                      // (23) 0.001953
/*4   */     int i, j, t, rconpointer = 0;                                                      // (14) 0.03125
/*6   */     uint8_t tk[8][4];                                                                  // (15) 0.02734
/*8   */     int KC = key_bits >> 5;                                                            // (17) 0.02344
/*10  */     int rounds = KC + 6;                                                               // (20) 0.01953
/*12  */     uint8_t log8[256];                                                                 // (18) 0.02344
/*14  */     uint8_t alog8[512];                                                                // (16) 0.02539
/*18  */     if (!enc_multbl[FF_ARRAY_ELEMS(enc_multbl)-1][FF_ARRAY_ELEMS(enc_multbl[0])-1]) {  // (0) 0.08984
/*20  */         j = 1;                                                                         // (19) 0.02148
/*22  */         for (i = 0; i < 255; i++) {                                                    // (9) 0.03906
/*24  */             alog8[i] = alog8[i + 255] = j;                                             // (3) 0.05664
/*26  */             log8[j] = i;                                                               // (11) 0.03711
/*28  */             j ^= j + j;                                                                // (12) 0.03516
/*30  */             if (j > 255)                                                               // (13) 0.0332
/*32  */                 j ^= 0x11B;                                                            // (6) 0.04492
/*34  */         }                                                                              // (22) 0.01562
/*36  */         for (i = 0; i < 256; i++) {                                                    // (8) 0.03906
/*38  */             j = i ? alog8[255 - log8[i]] : 0;                                          // (4) 0.05664
/*40  */             j ^= (j << 1) ^ (j << 2) ^ (j << 3) ^ (j << 4);                            // (1) 0.07227
/*42  */             j = (j ^ (j >> 8) ^ 99) & 255;                                             // (5) 0.05273
/*44  */             inv_sbox[j] = i;                                                           // (7) 0.04102
/*46  */             sbox[i] = j;                                                               // (10) 0.03711
/*48  */         }                                                                              // (21) 0.01562
/*50  */         init_multbl2(dec_multbl[0], (const int[4]) { 0xe, 0x9, 0xd, 0xb },             // 0.0
/*52  */                      log8, alog8, inv_sbox);                                           // 0.0
/*54  */         init_multbl2(enc_multbl[0], (const int[4]) { 0x2, 0x1, 0x1, 0x3 },             // 0.0
/*56  */                      log8, alog8, sbox);                                               // 0.0
/*58  */     }                                                                                  // 0.0
/*62  */     if (key_bits != 128 && key_bits != 192 && key_bits != 256)                         // 0.0
/*64  */         return -1;                                                                     // 0.0
/*68  */     a->rounds = rounds;                                                                // 0.0
/*72  */     memcpy(tk, key, KC * 4);                                                           // 0.0
/*76  */     for (t = 0; t < (rounds + 1) * 16;) {                                              // 0.0
/*78  */         memcpy(a->round_key[0].u8 + t, tk, KC * 4);                                    // 0.0
/*80  */         t += KC * 4;                                                                   // 0.0
/*84  */         for (i = 0; i < 4; i++)                                                        // 0.0
/*86  */             tk[0][i] ^= sbox[tk[KC - 1][(i + 1) & 3]];                                 // 0.0
/*88  */         tk[0][0] ^= rcon[rconpointer++];                                               // 0.0
/*92  */         for (j = 1; j < KC; j++) {                                                     // 0.0
/*94  */             if (KC != 8 || j != KC >> 1)                                               // 0.0
/*96  */                 for (i = 0; i < 4; i++)                                                // 0.0
/*98  */                     tk[j][i] ^= tk[j - 1][i];                                          // 0.0
/*100 */             else                                                                       // 0.0
/*102 */                 for (i = 0; i < 4; i++)                                                // 0.0
/*104 */                     tk[j][i] ^= sbox[tk[j - 1][i]];                                    // 0.0
/*106 */         }                                                                              // 0.0
/*108 */     }                                                                                  // 0.0
/*112 */     if (decrypt) {                                                                     // 0.0
/*114 */         for (i = 1; i < rounds; i++) {                                                 // 0.0
/*116 */             av_aes_block tmp[3];                                                       // 0.0
/*118 */             tmp[2] = a->round_key[i];                                                  // 0.0
/*120 */             subshift(&tmp[1], 0, sbox);                                                // 0.0
/*122 */             mix(tmp, dec_multbl, 1, 3);                                                // 0.0
/*124 */             a->round_key[i] = tmp[0];                                                  // 0.0
/*126 */         }                                                                              // 0.0
/*128 */     } else {                                                                           // 0.0
/*130 */         for (i = 0; i < (rounds + 1) >> 1; i++) {                                      // 0.0
/*132 */             FFSWAP(av_aes_block, a->round_key[i], a->round_key[rounds-i]);             // 0.0
/*134 */         }                                                                              // 0.0
/*136 */     }                                                                                  // 0.0
/*140 */     return 0;                                                                          // 0.0
/*142 */ }                                                                                      // 0.0
