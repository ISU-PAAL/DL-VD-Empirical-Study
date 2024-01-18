// commit message FFmpeg@eb24fd6458 (target=0, prob=0.45842844, correct=True): fix indention (less work to fix it myself than to check if a indention fix patch is ok ...)
/*0  */ int ff_rle_encode(uint8_t *outbuf, int out_size, const uint8_t *ptr , int bpp, int w, int8_t add, uint8_t xor)  // (0) 0.09766
/*2  */ {                                                                                                               // (22) 0.001953
/*4  */     int count, x;                                                                                               // (18) 0.01562
/*6  */     uint8_t *out;                                                                                               // (16) 0.01953
/*10 */     out = outbuf;                                                                                               // (19) 0.01562
/*16 */         for(x = 0; x < w; x += count) {                                                                         // (10) 0.04297
/*18 */             /* see if we can encode the next set of pixels with RLE */                                          // (7) 0.05078
/*20 */             if((count = count_pixels(ptr, w-x, bpp, 1)) > 1) {                                                  // (1) 0.06836
/*22 */                 if(out + bpp + 1 > outbuf + out_size) return -1;                                                // (3) 0.06836
/*24 */                 *out++ = (count ^ xor) + add;                                                                   // (6) 0.05469
/*26 */                 memcpy(out, ptr, bpp);                                                                          // (8) 0.05078
/*28 */                 out += bpp;                                                                                     // (13) 0.03906
/*30 */             } else {                                                                                            // (15) 0.02734
/*32 */                 /* fall back on uncompressed */                                                                 // (11) 0.04297
/*34 */                 count = count_pixels(ptr, w-x, bpp, 0);                                                         // (4) 0.06445
/*36 */                 *out++ = count - 1;                                                                             // (9) 0.04492
/*40 */                 if(out + bpp*count > outbuf + out_size) return -1;                                              // (2) 0.06836
/*42 */                 memcpy(out, ptr, bpp * count);                                                                  // (5) 0.05469
/*44 */                 out += bpp * count;                                                                             // (12) 0.04297
/*46 */         }                                                                                                       // (20) 0.01562
/*50 */         ptr += count * bpp;                                                                                     // (14) 0.02734
/*52 */     }                                                                                                           // (21) 0.007812
/*56 */     return out - outbuf;                                                                                        // (17) 0.01758
/*58 */ }                                                                                                               // 0.0
