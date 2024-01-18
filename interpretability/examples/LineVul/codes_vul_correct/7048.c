// commit message FFmpeg@7117547298 (target=1, prob=0.77363116, correct=True): hevc: fix incorrect sao buffer size
/*0  */ static int get_buffer_sao(HEVCContext *s, AVFrame *frame, const HEVCSPS *sps)  // (1) 0.1213
/*2  */ {                                                                              // (13) 0.004184
/*4  */     int ret, i;                                                                // (10) 0.03347
/*8  */     frame->width  = s->avctx->width  + 2;                                      // (3) 0.07531
/*10 */     frame->height = s->avctx->height + 2;                                      // (5) 0.06695
/*12 */     if ((ret = ff_get_buffer(s->avctx, frame, AV_GET_BUFFER_FLAG_REF)) < 0)    // (0) 0.1423
/*14 */         return ret;                                                            // (9) 0.04184
/*16 */     for (i = 0; frame->data[i]; i++) {                                         // (4) 0.07531
/*18 */         int offset = frame->linesize[i] + (1 << sps->pixel_shift);             // (2) 0.1172
/*20 */         frame->data[i] += offset;                                              // (6) 0.06695
/*22 */     }                                                                          // (12) 0.01674
/*24 */     frame->width  = s->avctx->width;                                           // (7) 0.06276
/*26 */     frame->height = s->avctx->height;                                          // (8) 0.05858
/*30 */     return 0;                                                                  // (11) 0.0251
/*32 */ }                                                                              // (14) 0.004184
