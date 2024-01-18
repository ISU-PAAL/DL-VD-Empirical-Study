// commit message FFmpeg@3a8c95f730 (target=0, prob=0.4386501, correct=True): avprobe: output proper INI format
/*0   */ static void show_stream(AVFormatContext *fmt_ctx, int stream_idx)                                    // (9) 0.04102
/*2   */ {                                                                                                    // (24) 0.001953
/*4   */     AVStream *stream = fmt_ctx->streams[stream_idx];                                                 // (10) 0.03906
/*6   */     AVCodecContext *dec_ctx;                                                                         // (18) 0.02344
/*8   */     AVCodec *dec;                                                                                    // (22) 0.01758
/*10  */     char val_str[128];                                                                               // (20) 0.01953
/*12  */     AVDictionaryEntry *tag = NULL;                                                                   // (19) 0.02344
/*14  */     AVRational display_aspect_ratio;                                                                 // (16) 0.02734
/*18  */     printf("[STREAM]\n");                                                                            // (17) 0.02344
/*22  */     printf("index=%d\n", stream->index);                                                             // (13) 0.03125
/*26  */     if ((dec_ctx = stream->codec)) {                                                                 // (15) 0.0293
/*28  */         if ((dec = dec_ctx->codec)) {                                                                // (12) 0.03711
/*30  */             printf("codec_name=%s\n", dec->name);                                                    // (5) 0.05273
/*32  */             printf("codec_long_name=%s\n", dec->long_name);                                          // (3) 0.06055
/*34  */         } else {                                                                                     // (21) 0.01953
/*36  */             printf("codec_name=unknown\n");                                                          // (8) 0.04297
/*38  */         }                                                                                            // (23) 0.01562
/*42  */         printf("codec_type=%s\n", media_type_string(dec_ctx->codec_type));                           // (1) 0.06641
/*44  */         printf("codec_time_base=%d/%d\n",                                                            // (7) 0.04687
/*46  */                dec_ctx->time_base.num, dec_ctx->time_base.den);                                      // (2) 0.06641
/*50  */         /* print AVI/FourCC tag */                                                                   // (14) 0.03125
/*52  */         av_get_codec_tag_string(val_str, sizeof(val_str), dec_ctx->codec_tag);                       // (0) 0.07227
/*54  */         printf("codec_tag_string=%s\n", val_str);                                                    // (6) 0.04883
/*56  */         printf("codec_tag=0x%04x\n", dec_ctx->codec_tag);                                            // (4) 0.06055
/*60  */         switch (dec_ctx->codec_type) {                                                               // (11) 0.03711
/*62  */         case AVMEDIA_TYPE_VIDEO:                                                                     // 0.0
/*64  */             printf("width=%d\n", dec_ctx->width);                                                    // 0.0
/*66  */             printf("height=%d\n", dec_ctx->height);                                                  // 0.0
/*68  */             printf("has_b_frames=%d\n", dec_ctx->has_b_frames);                                      // 0.0
/*70  */             if (dec_ctx->sample_aspect_ratio.num) {                                                  // 0.0
/*72  */                 printf("sample_aspect_ratio=%d:%d\n",                                                // 0.0
/*74  */                        dec_ctx->sample_aspect_ratio.num,                                             // 0.0
/*76  */                        dec_ctx->sample_aspect_ratio.den);                                            // 0.0
/*78  */                 av_reduce(&display_aspect_ratio.num, &display_aspect_ratio.den,                      // 0.0
/*80  */                           dec_ctx->width  * dec_ctx->sample_aspect_ratio.num,                        // 0.0
/*82  */                           dec_ctx->height * dec_ctx->sample_aspect_ratio.den,                        // 0.0
/*84  */                           1024*1024);                                                                // 0.0
/*86  */                 printf("display_aspect_ratio=%d:%d\n",                                               // 0.0
/*88  */                        display_aspect_ratio.num, display_aspect_ratio.den);                          // 0.0
/*90  */             }                                                                                        // 0.0
/*92  */             printf("pix_fmt=%s\n",                                                                   // 0.0
/*94  */                    dec_ctx->pix_fmt != PIX_FMT_NONE ? av_pix_fmt_descriptors[dec_ctx->pix_fmt].name  // 0.0
/*96  */                                                     : "unknown");                                    // 0.0
/*98  */             printf("level=%d\n", dec_ctx->level);                                                    // 0.0
/*100 */             break;                                                                                   // 0.0
/*104 */         case AVMEDIA_TYPE_AUDIO:                                                                     // 0.0
/*106 */             printf("sample_rate=%s\n", value_string(val_str, sizeof(val_str),                        // 0.0
/*108 */                                                     dec_ctx->sample_rate,                            // 0.0
/*110 */                                                     unit_hertz_str));                                // 0.0
/*112 */             printf("channels=%d\n", dec_ctx->channels);                                              // 0.0
/*114 */             printf("bits_per_sample=%d\n",                                                           // 0.0
/*116 */                    av_get_bits_per_sample(dec_ctx->codec_id));                                       // 0.0
/*118 */             break;                                                                                   // 0.0
/*120 */         }                                                                                            // 0.0
/*122 */     } else {                                                                                         // 0.0
/*124 */         printf("codec_type=unknown\n");                                                              // 0.0
/*126 */     }                                                                                                // 0.0
/*130 */     if (fmt_ctx->iformat->flags & AVFMT_SHOW_IDS)                                                    // 0.0
/*132 */         printf("id=0x%x\n", stream->id);                                                             // 0.0
/*134 */     printf("r_frame_rate=%d/%d\n",                                                                   // 0.0
/*136 */            stream->r_frame_rate.num, stream->r_frame_rate.den);                                      // 0.0
/*138 */     printf("avg_frame_rate=%d/%d\n",                                                                 // 0.0
/*140 */            stream->avg_frame_rate.num, stream->avg_frame_rate.den);                                  // 0.0
/*142 */     printf("time_base=%d/%d\n",                                                                      // 0.0
/*144 */            stream->time_base.num, stream->time_base.den);                                            // 0.0
/*146 */     printf("start_time=%s\n",                                                                        // 0.0
/*148 */            time_value_string(val_str, sizeof(val_str),                                               // 0.0
/*150 */                              stream->start_time, &stream->time_base));                               // 0.0
/*152 */     printf("duration=%s\n",                                                                          // 0.0
/*154 */            time_value_string(val_str, sizeof(val_str),                                               // 0.0
/*156 */                              stream->duration, &stream->time_base));                                 // 0.0
/*158 */     if (stream->nb_frames)                                                                           // 0.0
/*160 */         printf("nb_frames=%"PRId64"\n", stream->nb_frames);                                          // 0.0
/*164 */     while ((tag = av_dict_get(stream->metadata, "", tag,                                             // 0.0
/*166 */                               AV_DICT_IGNORE_SUFFIX)))                                               // 0.0
/*168 */         printf("TAG:%s=%s\n", tag->key, tag->value);                                                 // 0.0
/*172 */     printf("[/STREAM]\n");                                                                           // 0.0
/*174 */ }                                                                                                    // 0.0
