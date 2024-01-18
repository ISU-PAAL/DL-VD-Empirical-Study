// commit message FFmpeg@c3778df2d4 (target=0, prob=0.25983223, correct=True): ffmpeg: fix negative array index
/*0  */ enum AVPixelFormat choose_pixel_fmt(AVStream *st, AVCodec *codec, enum AVPixelFormat target)                                                             // (6) 0.06055
/*2  */ {                                                                                                                                                        // (10) 0.001953
/*4  */     if (codec && codec->pix_fmts) {                                                                                                                      // (9) 0.0332
/*6  */         const enum AVPixelFormat *p = codec->pix_fmts;                                                                                                   // (8) 0.04688
/*8  */         int has_alpha= av_pix_fmt_desc_get(target)->nb_components % 2 == 0;                                                                              // (3) 0.07031
/*10 */         enum AVPixelFormat best= AV_PIX_FMT_NONE;                                                                                                        // (7) 0.04883
/*12 */         if (st->codec->strict_std_compliance <= FF_COMPLIANCE_UNOFFICIAL) {                                                                              // (5) 0.06641
/*14 */             if (st->codec->codec_id == AV_CODEC_ID_MJPEG) {                                                                                              // (4) 0.07031
/*16 */                 p = (const enum AVPixelFormat[]) { AV_PIX_FMT_YUVJ420P, AV_PIX_FMT_YUVJ422P, AV_PIX_FMT_YUV420P, AV_PIX_FMT_YUV422P, AV_PIX_FMT_NONE };  // (0) 0.1797
/*18 */             } else if (st->codec->codec_id == AV_CODEC_ID_LJPEG) {                                                                                       // (2) 0.07422
/*20 */                 p = (const enum AVPixelFormat[]) { AV_PIX_FMT_YUVJ420P, AV_PIX_FMT_YUVJ422P, AV_PIX_FMT_YUVJ444P, AV_PIX_FMT_YUV420P,                    // (1) 0.1602
/*22 */                                                  AV_PIX_FMT_YUV422P, AV_PIX_FMT_YUV444P, AV_PIX_FMT_BGRA, AV_PIX_FMT_NONE };                             // 0.0
/*24 */             }                                                                                                                                            // 0.0
/*26 */         }                                                                                                                                                // 0.0
/*28 */         for (; *p != AV_PIX_FMT_NONE; p++) {                                                                                                             // 0.0
/*30 */             best= avcodec_find_best_pix_fmt_of_2(best, *p, target, has_alpha, NULL);                                                                     // 0.0
/*32 */             if (*p == target)                                                                                                                            // 0.0
/*34 */                 break;                                                                                                                                   // 0.0
/*36 */         }                                                                                                                                                // 0.0
/*38 */         if (*p == AV_PIX_FMT_NONE) {                                                                                                                     // 0.0
/*40 */             if (target != AV_PIX_FMT_NONE)                                                                                                               // 0.0
/*42 */                 av_log(NULL, AV_LOG_WARNING,                                                                                                             // 0.0
/*44 */                        "Incompatible pixel format '%s' for codec '%s', auto-selecting format '%s'\n",                                                    // 0.0
/*46 */                        av_get_pix_fmt_name(target),                                                                                                      // 0.0
/*48 */                        codec->name,                                                                                                                      // 0.0
/*50 */                        av_get_pix_fmt_name(best));                                                                                                       // 0.0
/*52 */             return best;                                                                                                                                 // 0.0
/*54 */         }                                                                                                                                                // 0.0
/*56 */     }                                                                                                                                                    // 0.0
/*58 */     return target;                                                                                                                                       // 0.0
/*60 */ }                                                                                                                                                        // 0.0
