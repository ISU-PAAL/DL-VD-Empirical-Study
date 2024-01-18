// commit message FFmpeg@c1f2c4c3b4 (target=0, prob=0.9146028, correct=False): vmdav: Try to fix unpack_rle()
/*0  */ static int rle_unpack(const unsigned char *src, unsigned char *dest,       // (10) 0.03711
/*2  */                       int src_count, int src_size, int dest_len)           // (2) 0.07031
/*4  */ {                                                                          // (27) 0.001965
/*6  */     unsigned char *pd;                                                     // (21) 0.01562
/*8  */     int i, l;                                                              // (22) 0.01562
/*10 */     unsigned char *dest_end = dest + dest_len;                             // (12) 0.03125
/*12 */     GetByteContext gb;                                                     // (20) 0.01758
/*16 */     bytestream2_init(&gb, src, src_size);                                  // (11) 0.03515
/*18 */     pd = dest;                                                             // (23) 0.01562
/*20 */     if (src_count & 1) {                                                   // (17) 0.02344
/*22 */         if (bytestream2_get_bytes_left(&gb) < 1)                           // (5) 0.04882
/*24 */             return 0;                                                      // (15) 0.02734
/*26 */         *pd++ = bytestream2_get_byteu(&gb);                                // (8) 0.04492
/*28 */     }                                                                      // (26) 0.007812
/*32 */     src_count >>= 1;                                                       // (18) 0.01953
/*34 */     i = 0;                                                                 // (24) 0.01367
/*36 */     do {                                                                   // (25) 0.009765
/*38 */         if (bytestream2_get_bytes_left(&gb) < 1)                           // (6) 0.04882
/*40 */             break;                                                         // (16) 0.02539
/*42 */         l = bytestream2_get_byteu(&gb);                                    // (9) 0.04101
/*44 */         if (l & 0x80) {                                                    // (14) 0.03125
/*46 */             l = (l & 0x7F) * 2;                                            // (7) 0.04687
/*48 */             if (dest_end - pd < l || bytestream2_get_bytes_left(&gb) < l)  // (1) 0.07421
/*50 */                 return bytestream2_tell(&gb);                              // (4) 0.04882
/*52 */             bytestream2_get_bufferu(&gb, pd, l);                           // (3) 0.05468
/*54 */             pd += l;                                                       // (13) 0.03125
/*56 */         } else {                                                           // (19) 0.01953
/*58 */             if (dest_end - pd < i || bytestream2_get_bytes_left(&gb) < 2)  // (0) 0.07421
/*60 */                 return bytestream2_tell(&gb);                              // 0.0
/*62 */             for (i = 0; i < l; i++) {                                      // 0.0
/*64 */                 *pd++ = bytestream2_get_byteu(&gb);                        // 0.0
/*66 */                 *pd++ = bytestream2_get_byteu(&gb);                        // 0.0
/*68 */             }                                                              // 0.0
/*70 */             bytestream2_skip(&gb, 2);                                      // 0.0
/*72 */         }                                                                  // 0.0
/*74 */         i += l;                                                            // 0.0
/*76 */     } while (i < src_count);                                               // 0.0
/*80 */     return bytestream2_tell(&gb);                                          // 0.0
/*82 */ }                                                                          // 0.0
