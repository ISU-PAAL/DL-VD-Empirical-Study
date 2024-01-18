// commit message FFmpeg@fc49f22c3b (target=1, prob=0.4973734, correct=False): ffmpeg: add support for audio filters.
/*0  */ static char *choose_pixel_fmts(OutputStream *ost)                                                                                       // (11) 0.03125
/*2  */ {                                                                                                                                       // (21) 0.001953
/*4  */     if (ost->keep_pix_fmt) {                                                                                                            // (12) 0.03125
/*6  */         if (ost->filter)                                                                                                                // (18) 0.02539
/*8  */             avfilter_graph_set_auto_convert(ost->filter->graph->graph,                                                                  // (3) 0.06055
/*10 */                                             AVFILTER_AUTO_CONVERT_NONE);                                                                // (1) 0.1094
/*12 */         if (ost->st->codec->pix_fmt == PIX_FMT_NONE)                                                                                    // (5) 0.06055
/*14 */             return NULL;                                                                                                                // (17) 0.02734
/*16 */         ost->pix_fmts[0] = ost->st->codec->pix_fmt;                                                                                     // (4) 0.06055
/*18 */         return ost->pix_fmts;                                                                                                           // (13) 0.03125
/*20 */     }                                                                                                                                   // (20) 0.007812
/*22 */     if (ost->st->codec->pix_fmt != PIX_FMT_NONE) {                                                                                      // (6) 0.05469
/*24 */         return av_strdup(av_get_pix_fmt_name(choose_pixel_fmt(ost->st, ost->enc, ost->st->codec->pix_fmt)));                            // (0) 0.1094
/*26 */     } else if (ost->enc->pix_fmts) {                                                                                                    // (9) 0.03516
/*28 */         const enum PixelFormat *p;                                                                                                      // (16) 0.02734
/*30 */         AVIOContext *s = NULL;                                                                                                          // (14) 0.0293
/*32 */         uint8_t *ret;                                                                                                                   // (15) 0.02734
/*34 */         int len;                                                                                                                        // (19) 0.01953
/*38 */         if (avio_open_dyn_buf(&s) < 0)                                                                                                  // (7) 0.04687
/*40 */             exit_program(1);                                                                                                            // (10) 0.0332
/*44 */         p = ost->enc->pix_fmts;                                                                                                         // (8) 0.03711
/*46 */         if (ost->st->codec->strict_std_compliance <= FF_COMPLIANCE_UNOFFICIAL) {                                                        // (2) 0.07031
/*48 */             if (ost->st->codec->codec_id == CODEC_ID_MJPEG) {                                                                           // 0.0
/*50 */                 p = (const enum PixelFormat[]) { PIX_FMT_YUVJ420P, PIX_FMT_YUVJ422P, PIX_FMT_YUV420P, PIX_FMT_YUV422P, PIX_FMT_NONE };  // 0.0
/*52 */             } else if (ost->st->codec->codec_id == CODEC_ID_LJPEG) {                                                                    // 0.0
/*54 */                 p = (const enum PixelFormat[]) { PIX_FMT_YUVJ420P, PIX_FMT_YUVJ422P, PIX_FMT_YUVJ444P, PIX_FMT_YUV420P,                 // 0.0
/*56 */                                                     PIX_FMT_YUV422P, PIX_FMT_YUV444P, PIX_FMT_BGRA, PIX_FMT_NONE };                     // 0.0
/*58 */             }                                                                                                                           // 0.0
/*60 */         }                                                                                                                               // 0.0
/*64 */         for (; *p != PIX_FMT_NONE; p++)                                                                                                 // 0.0
/*66 */             avio_printf(s, "%s:", av_get_pix_fmt_name(*p));                                                                             // 0.0
/*68 */         len = avio_close_dyn_buf(s, &ret);                                                                                              // 0.0
/*70 */         ret[len - 1] = 0;                                                                                                               // 0.0
/*72 */         return ret;                                                                                                                     // 0.0
/*74 */     } else                                                                                                                              // 0.0
/*76 */         return NULL;                                                                                                                    // 0.0
/*78 */ }                                                                                                                                       // 0.0
