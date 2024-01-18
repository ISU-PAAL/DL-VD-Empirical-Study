// commit message FFmpeg@931da6a5e9 (target=0, prob=0.4974826, correct=True): lavd/v4l2: don't use avpriv_ prefix for internal functions
/*0   */ static int device_try_init(AVFormatContext *ctx,                                                                   // (13) 0.02734
/*2   */                            enum AVPixelFormat pix_fmt,                                                             // (4) 0.07227
/*4   */                            int *width,                                                                             // (7) 0.05859
/*6   */                            int *height,                                                                            // (8) 0.05859
/*8   */                            uint32_t *desired_format,                                                               // (5) 0.07031
/*10  */                            enum AVCodecID *codec_id)                                                               // (2) 0.07227
/*12  */ {                                                                                                                  // (20) 0.001953
/*14  */     int ret, i;                                                                                                    // (17) 0.01562
/*18  */     *desired_format = avpriv_fmt_ff2v4l(pix_fmt, ctx->video_codec_id);                                             // (3) 0.07227
/*22  */     if (*desired_format) {                                                                                         // (16) 0.02148
/*24  */         ret = device_init(ctx, width, height, *desired_format);                                                    // (9) 0.04883
/*26  */         if (ret < 0) {                                                                                             // (14) 0.02734
/*28  */             *desired_format = 0;                                                                                   // (11) 0.03711
/*30  */             if (ret != AVERROR(EINVAL))                                                                            // (10) 0.04492
/*32  */                 return ret;                                                                                        // (12) 0.03516
/*34  */         }                                                                                                          // (18) 0.01562
/*36  */     }                                                                                                              // (19) 0.007812
/*40  */     if (!*desired_format) {                                                                                        // (15) 0.02344
/*42  */         for (i = 0; avpriv_fmt_conversion_table[i].codec_id != AV_CODEC_ID_NONE; i++) {                            // (0) 0.08789
/*44  */             if (ctx->video_codec_id == AV_CODEC_ID_NONE ||                                                         // (6) 0.06445
/*46  */                 avpriv_fmt_conversion_table[i].codec_id == ctx->video_codec_id) {                                  // (1) 0.08594
/*48  */                 av_log(ctx, AV_LOG_DEBUG, "Trying to set codec:%s pix_fmt:%s\n",                                   // 0.0
/*50  */                        avcodec_get_name(avpriv_fmt_conversion_table[i].codec_id),                                  // 0.0
/*52  */                        (char *)av_x_if_null(av_get_pix_fmt_name(avpriv_fmt_conversion_table[i].ff_fmt), "none"));  // 0.0
/*56  */                 *desired_format = avpriv_fmt_conversion_table[i].v4l2_fmt;                                         // 0.0
/*58  */                 ret = device_init(ctx, width, height, *desired_format);                                            // 0.0
/*60  */                 if (ret >= 0)                                                                                      // 0.0
/*62  */                     break;                                                                                         // 0.0
/*64  */                 else if (ret != AVERROR(EINVAL))                                                                   // 0.0
/*66  */                     return ret;                                                                                    // 0.0
/*68  */                 *desired_format = 0;                                                                               // 0.0
/*70  */             }                                                                                                      // 0.0
/*72  */         }                                                                                                          // 0.0
/*76  */         if (*desired_format == 0) {                                                                                // 0.0
/*78  */             av_log(ctx, AV_LOG_ERROR, "Cannot find a proper format for "                                           // 0.0
/*80  */                    "codec '%s' (id %d), pixel format '%s' (id %d)\n",                                              // 0.0
/*82  */                    avcodec_get_name(ctx->video_codec_id), ctx->video_codec_id,                                     // 0.0
/*84  */                    (char *)av_x_if_null(av_get_pix_fmt_name(pix_fmt), "none"), pix_fmt);                           // 0.0
/*86  */             ret = AVERROR(EINVAL);                                                                                 // 0.0
/*88  */         }                                                                                                          // 0.0
/*90  */     }                                                                                                              // 0.0
/*94  */     *codec_id = avpriv_fmt_v4l2codec(*desired_format);                                                             // 0.0
/*96  */     av_assert0(*codec_id != AV_CODEC_ID_NONE);                                                                     // 0.0
/*98  */     return ret;                                                                                                    // 0.0
/*100 */ }                                                                                                                  // 0.0
