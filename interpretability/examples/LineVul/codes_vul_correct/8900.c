// commit message FFmpeg@35cb6854bb (target=1, prob=0.8519885, correct=True): Fix potential pointer arithmetic overflows in rle_unpack() of vmd video decoder.
/*0  */ static int rle_unpack(const unsigned char *src, int src_len, int src_count,  // (3) 0.04688
/*2  */                       unsigned char *dest, int dest_len)                     // (0) 0.06055
/*4  */ {                                                                            // (31) 0.001954
/*6  */     const unsigned char *ps;                                                 // (23) 0.01758
/*8  */     const unsigned char *ps_end;                                             // (20) 0.02148
/*10 */     unsigned char *pd;                                                       // (25) 0.01563
/*12 */     int i, l;                                                                // (26) 0.01562
/*14 */     unsigned char *dest_end = dest + dest_len;                               // (11) 0.03125
/*18 */     ps = src;                                                                // (27) 0.01367
/*20 */     ps_end = src + src_len;                                                  // (16) 0.02539
/*22 */     pd = dest;                                                               // (24) 0.01563
/*24 */     if (src_count & 1) {                                                     // (19) 0.02344
/*26 */         if (ps_end - ps < 1)                                                 // (8) 0.0332
/*28 */             return 0;                                                        // (15) 0.02734
/*30 */         *pd++ = *ps++;                                                       // (14) 0.02734
/*32 */     }                                                                        // (30) 0.007812
/*36 */     src_count >>= 1;                                                         // (21) 0.01953
/*38 */     i = 0;                                                                   // (28) 0.01367
/*40 */     do {                                                                     // (29) 0.009765
/*42 */         if (ps_end - ps < 1)                                                 // (9) 0.0332
/*44 */             break;                                                           // (17) 0.02539
/*46 */         l = *ps++;                                                           // (18) 0.02344
/*48 */         if (l & 0x80) {                                                      // (12) 0.03125
/*50 */             l = (l & 0x7F) * 2;                                              // (4) 0.04687
/*52 */             if (pd + l > dest_end || ps_end - ps < l)                        // (2) 0.05664
/*54 */                 return ps - src;                                             // (7) 0.03906
/*56 */             memcpy(pd, ps, l);                                               // (5) 0.04102
/*58 */             ps += l;                                                         // (13) 0.0293
/*60 */             pd += l;                                                         // (10) 0.03125
/*62 */         } else {                                                             // (22) 0.01953
/*64 */             if (pd + i > dest_end || ps_end - ps < 2)                        // (1) 0.05664
/*66 */                 return ps - src;                                             // (6) 0.03906
/*68 */             for (i = 0; i < l; i++) {                                        // 0.0
/*70 */                 *pd++ = ps[0];                                               // 0.0
/*72 */                 *pd++ = ps[1];                                               // 0.0
/*74 */             }                                                                // 0.0
/*76 */             ps += 2;                                                         // 0.0
/*78 */         }                                                                    // 0.0
/*80 */         i += l;                                                              // 0.0
/*82 */     } while (i < src_count);                                                 // 0.0
/*86 */     return ps - src;                                                         // 0.0
/*88 */ }                                                                            // 0.0
