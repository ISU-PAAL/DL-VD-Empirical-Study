// commit message FFmpeg@f929ab0569 (target=0, prob=0.48130256, correct=True): cosmetics: Write NULL pointer equality checks more compactly
/*0  */ static int copy_from(IpvideoContext *s, AVFrame *src, AVFrame *dst, int delta_x, int delta_y)         // (5) 0.06982
/*2  */ {                                                                                                     // (19) 0.002053
/*4  */     int current_offset = s->pixel_ptr - dst->data[0];                                                 // (10) 0.04107
/*6  */     int motion_offset = current_offset + delta_y * dst->linesize[0]                                   // (8) 0.04723
/*8  */                        + delta_x * (1 + s->is_16bpp);                                                 // (4) 0.07803
/*10 */     if (motion_offset < 0) {                                                                          // (15) 0.02464
/*12 */         av_log(s->avctx, AV_LOG_ERROR, " Interplay video: motion offset < 0 (%d)\n", motion_offset);  // (2) 0.08214
/*14 */         return AVERROR_INVALIDDATA;                                                                   // (11) 0.03491
/*16 */     } else if (motion_offset > s->upper_motion_limit_offset) {                                        // (9) 0.04517
/*18 */         av_log(s->avctx, AV_LOG_ERROR, " Interplay video: motion offset above limit (%d >= %d)\n",    // (3) 0.08008
/*20 */             motion_offset, s->upper_motion_limit_offset);                                             // (7) 0.05133
/*22 */         return AVERROR_INVALIDDATA;                                                                   // (12) 0.03491
/*24 */     }                                                                                                 // (17) 0.008214
/*26 */     if (src->data[0] == NULL) {                                                                       // (14) 0.0308
/*28 */         av_log(s->avctx, AV_LOG_ERROR, "Invalid decode type, corrupted header?\n");                   // (6) 0.06776
/*30 */         return AVERROR(EINVAL);                                                                       // (13) 0.03285
/*32 */     }                                                                                                 // (18) 0.008214
/*34 */     s->hdsp.put_pixels_tab[!s->is_16bpp][0](s->pixel_ptr, src->data[0] + motion_offset,               // (1) 0.0883
/*36 */                                             dst->linesize[0], 8);                                     // (0) 0.1068
/*38 */     return 0;                                                                                         // (16) 0.01232
/*40 */ }                                                                                                     // (20) 0.002053
