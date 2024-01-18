// commit message FFmpeg@5d7e3d7167 (target=1, prob=0.39411703, correct=False): Check for out of bound reads in the Tiertex Limited SEQ decoder.
/*0  */ static const unsigned char *seq_unpack_rle_block(const unsigned char *src, unsigned char *dst, int dst_size)  // (0) 0.07459
/*2  */ {                                                                                                             // (25) 0.002331
/*4  */     int i, len, sz;                                                                                           // (15) 0.02564
/*6  */     GetBitContext gb;                                                                                         // (20) 0.02098
/*8  */     int code_table[64];                                                                                       // (18) 0.02331
/*12 */     /* get the rle codes (at most 64 bytes) */                                                                // (9) 0.0373
/*14 */     init_get_bits(&gb, src, 64 * 8);                                                                          // (8) 0.03963
/*16 */     for (i = 0, sz = 0; i < 64 && sz < dst_size; i++) {                                                       // (3) 0.06527
/*18 */         code_table[i] = get_sbits(&gb, 4);                                                                    // (4) 0.05361
/*20 */         sz += FFABS(code_table[i]);                                                                           // (6) 0.04662
/*22 */     }                                                                                                         // (23) 0.009324
/*24 */     src += (get_bits_count(&gb) + 7) / 8;                                                                     // (7) 0.04662
/*28 */     /* do the rle unpacking */                                                                                // (16) 0.02564
/*30 */     for (i = 0; i < 64 && dst_size > 0; i++) {                                                                // (5) 0.05128
/*32 */         len = code_table[i];                                                                                  // (11) 0.03497
/*34 */         if (len < 0) {                                                                                        // (13) 0.03263
/*36 */             len = -len;                                                                                       // (10) 0.0373
/*38 */             memset(dst, *src++, FFMIN(len, dst_size));                                                        // (1) 0.06993
/*40 */         } else {                                                                                              // (19) 0.02331
/*42 */             memcpy(dst, src, FFMIN(len, dst_size));                                                           // (2) 0.0676
/*44 */             src += len;                                                                                       // (12) 0.03497
/*46 */         }                                                                                                     // (21) 0.01865
/*48 */         dst += len;                                                                                           // (17) 0.02564
/*50 */         dst_size -= len;                                                                                      // (14) 0.0303
/*52 */     }                                                                                                         // (24) 0.009324
/*54 */     return src;                                                                                               // (22) 0.01399
/*56 */ }                                                                                                             // (26) 0.002331
