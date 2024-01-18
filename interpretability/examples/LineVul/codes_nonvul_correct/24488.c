// commit message FFmpeg@3176217c60 (target=0, prob=0.028839841, correct=True): h264: decouple h264_ps from the h264 decoder
/*0  */ void ff_h264_filter_mb_fast(const H264Context *h, H264SliceContext *sl,                                            // (8) 0.05455
/*2  */                             int mb_x, int mb_y, uint8_t *img_y,                                                    // (4) 0.09697
/*4  */                             uint8_t *img_cb, uint8_t *img_cr,                                                      // (5) 0.09091
/*6  */                             unsigned int linesize, unsigned int uvlinesize)                                        // (6) 0.07879
/*8  */ {                                                                                                                  // (18) 0.00202
/*10 */     assert(!FRAME_MBAFF(h));                                                                                       // (9) 0.0303
/*12 */     if(!h->h264dsp.h264_loop_filter_strength || h->pps.chroma_qp_diff) {                                           // (7) 0.07071
/*14 */         ff_h264_filter_mb(h, sl, mb_x, mb_y, img_y, img_cb, img_cr, linesize, uvlinesize);                         // (3) 0.101
/*16 */         return;                                                                                                    // (11) 0.01818
/*18 */     }                                                                                                              // (14) 0.008081
/*22 */ #if CONFIG_SMALL                                                                                                   // (12) 0.01212
/*24 */     h264_filter_mb_fast_internal(h, sl, mb_x, mb_y, img_y, img_cb, img_cr, linesize, uvlinesize, h->pixel_shift);  // (0) 0.1091
/*26 */ #else                                                                                                              // (16) 0.00404
/*28 */     if(h->pixel_shift){                                                                                            // (10) 0.02222
/*30 */         h264_filter_mb_fast_internal(h, sl, mb_x, mb_y, img_y, img_cb, img_cr, linesize, uvlinesize, 1);           // (1) 0.1091
/*32 */     }else{                                                                                                         // (13) 0.01212
/*34 */         h264_filter_mb_fast_internal(h, sl, mb_x, mb_y, img_y, img_cb, img_cr, linesize, uvlinesize, 0);           // (2) 0.1091
/*36 */     }                                                                                                              // (15) 0.008081
/*38 */ #endif                                                                                                             // (17) 0.00404
/*40 */ }                                                                                                                  // (19) 0.00202
