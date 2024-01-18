// commit message FFmpeg@38d5533228 (target=1, prob=0.6833975, correct=True): pixdesc: mark pseudopaletted formats with a special flag.
/*0  */ int av_image_alloc(uint8_t *pointers[4], int linesizes[4],                           // (8) 0.05023
/*2  */                    int w, int h, enum PixelFormat pix_fmt, int align)                // (0) 0.08219
/*4  */ {                                                                                    // (22) 0.002283
/*6  */     int i, ret;                                                                      // (18) 0.01826
/*8  */     uint8_t *buf;                                                                    // (13) 0.02283
/*12 */     if ((ret = av_image_check_size(w, h, 0, NULL)) < 0)                              // (6) 0.05936
/*14 */         return ret;                                                                  // (14) 0.02283
/*16 */     if ((ret = av_image_fill_linesizes(linesizes, pix_fmt, w)) < 0)                  // (5) 0.06849
/*18 */         return ret;                                                                  // (15) 0.02283
/*22 */     for (i = 0; i < 4; i++)                                                          // (10) 0.03425
/*24 */         linesizes[i] = FFALIGN(linesizes[i], align);                                 // (7) 0.05479
/*28 */     if ((ret = av_image_fill_pointers(pointers, pix_fmt, h, NULL, linesizes)) < 0)   // (3) 0.07534
/*30 */         return ret;                                                                  // (16) 0.02283
/*32 */     buf = av_malloc(ret + align);                                                    // (11) 0.03196
/*34 */     if (!buf)                                                                        // (19) 0.01598
/*36 */         return AVERROR(ENOMEM);                                                      // (9) 0.03653
/*38 */     if ((ret = av_image_fill_pointers(pointers, pix_fmt, h, buf, linesizes)) < 0) {  // (2) 0.07763
/*40 */         av_free(buf);                                                                // (12) 0.02968
/*42 */         return ret;                                                                  // (17) 0.02283
/*44 */     }                                                                                // (21) 0.009132
/*46 */     if (av_pix_fmt_descriptors[pix_fmt].flags & PIX_FMT_PAL)                         // (1) 0.07763
/*48 */         ff_set_systematic_pal2((uint32_t*)pointers[1], pix_fmt);                     // (4) 0.07306
/*52 */     return ret;                                                                      // (20) 0.0137
/*54 */ }                                                                                    // (23) 0.002283
