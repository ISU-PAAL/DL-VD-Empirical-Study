// commit message FFmpeg@fbaf75b166 (target=1, prob=0.058215328, correct=False): h264: Use the correct croping values.
/*0  */ static int output_frame(H264Context *h, AVFrame *dst, AVFrame *src)      // (4) 0.08303
/*2  */ {                                                                        // (15) 0.00361
/*4  */     int i;                                                               // (12) 0.02166
/*6  */     int ret = av_frame_ref(dst, src);                                    // (5) 0.06137
/*8  */     if (ret < 0)                                                         // (11) 0.03249
/*10 */         return ret;                                                      // (9) 0.0361
/*14 */     if (!h->sps.crop)                                                    // (8) 0.04332
/*16 */         return 0;                                                        // (10) 0.0361
/*20 */     for (i = 0; i < 3; i++) {                                            // (6) 0.05776
/*22 */         int hshift = (i > 0) ? h->chroma_x_shift : 0;                    // (2) 0.1011
/*24 */         int vshift = (i > 0) ? h->chroma_y_shift : 0;                    // (3) 0.1011
/*26 */         int off    = ((h->sps.crop_left >> hshift) << h->pixel_shift) +  // (0) 0.1227
/*28 */             (h->sps.crop_top  >> vshift) * dst->linesize[i];             // (1) 0.1191
/*30 */         dst->data[i] += off;                                             // (7) 0.05776
/*32 */     }                                                                    // (14) 0.01444
/*34 */     return 0;                                                            // (13) 0.02166
/*36 */ }                                                                        // (16) 0.00361
