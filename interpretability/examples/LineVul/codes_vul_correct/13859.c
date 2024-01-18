// commit message FFmpeg@4749e07498 (target=1, prob=0.9277457, correct=True): Fix out of bound reads in rle_unpack() of vmd video decoder.
/*0  */ static int rle_unpack(const unsigned char *src, unsigned char *dest,  // (9) 0.03718
/*2  */     int src_len, int dest_len)                                        // (16) 0.02544
/*4  */ {                                                                     // (33) 0.001957
/*6  */     const unsigned char *ps;                                          // (24) 0.01761
/*8  */     unsigned char *pd;                                                // (26) 0.01566
/*10 */     int i, l;                                                         // (28) 0.01566
/*12 */     unsigned char *dest_end = dest + dest_len;                        // (11) 0.03131
/*16 */     ps = src;                                                         // (30) 0.0137
/*18 */     pd = dest;                                                        // (25) 0.01566
/*20 */     if (src_len & 1)                                                  // (20) 0.02153
/*22 */         *pd++ = *ps++;                                                // (15) 0.0274
/*26 */     src_len >>= 1;                                                    // (22) 0.01957
/*28 */     i = 0;                                                            // (31) 0.0137
/*30 */     do {                                                              // (32) 0.009785
/*32 */         l = *ps++;                                                    // (17) 0.02348
/*34 */         if (l & 0x80) {                                               // (12) 0.03131
/*36 */             l = (l & 0x7F) * 2;                                       // (1) 0.04697
/*38 */             if (pd + l > dest_end)                                    // (5) 0.0411
/*40 */                 return ps - src;                                      // (7) 0.03914
/*42 */             memcpy(pd, ps, l);                                        // (4) 0.0411
/*44 */             ps += l;                                                  // (13) 0.02935
/*46 */             pd += l;                                                  // (10) 0.03131
/*48 */         } else {                                                      // (23) 0.01957
/*50 */             if (pd + i > dest_end)                                    // (6) 0.0411
/*52 */                 return ps - src;                                      // (8) 0.03914
/*54 */             for (i = 0; i < l; i++) {                                 // (0) 0.04697
/*56 */                 *pd++ = ps[0];                                        // (2) 0.04501
/*58 */                 *pd++ = ps[1];                                        // (3) 0.04501
/*60 */             }                                                         // (19) 0.02348
/*62 */             ps += 2;                                                  // (14) 0.02935
/*64 */         }                                                             // (29) 0.01566
/*66 */         i += l;                                                       // (21) 0.02153
/*68 */     } while (i < src_len);                                            // (18) 0.02348
/*72 */     return ps - src;                                                  // (27) 0.01566
/*74 */ }                                                                     // (34) 0.001957
