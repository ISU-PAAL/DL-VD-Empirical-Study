// commit message FFmpeg@e87190f5d2 (target=0, prob=0.26699528, correct=True): ffprobe: check for errors, and abort immediately
/*0   */ static void show_stream(WriterContext *w, AVFormatContext *fmt_ctx, int stream_idx, int in_program)                      // (3) 0.06055
/*2   */ {                                                                                                                        // (24) 0.001953
/*4   */     AVStream *stream = fmt_ctx->streams[stream_idx];                                                                     // (8) 0.03906
/*6   */     AVCodecContext *dec_ctx;                                                                                             // (15) 0.02344
/*8   */     const AVCodec *dec;                                                                                                  // (20) 0.01953
/*10  */     char val_str[128];                                                                                                   // (19) 0.01953
/*12  */     const char *s;                                                                                                       // (23) 0.01563
/*14  */     AVRational sar, dar;                                                                                                 // (18) 0.02149
/*16  */     AVBPrint pbuf;                                                                                                       // (22) 0.01758
/*20  */     av_bprint_init(&pbuf, 1, AV_BPRINT_SIZE_UNLIMITED);                                                                  // (5) 0.05469
/*24  */     writer_print_section_header(w, in_program ? SECTION_ID_PROGRAM_STREAM : SECTION_ID_STREAM);                          // (2) 0.06836
/*28  */     print_int("index", stream->index);                                                                                   // (14) 0.02539
/*32  */     if ((dec_ctx = stream->codec)) {                                                                                     // (12) 0.0293
/*34  */         const char *profile = NULL;                                                                                      // (13) 0.02734
/*36  */         dec = dec_ctx->codec;                                                                                            // (11) 0.03125
/*38  */         if (dec) {                                                                                                       // (16) 0.02344
/*40  */             print_str("codec_name", dec->name);                                                                          // (7) 0.04687
/*42  */             if (!do_bitexact) {                                                                                          // (10) 0.03906
/*44  */                 if (dec->long_name) print_str    ("codec_long_name", dec->long_name);                                    // (1) 0.08398
/*46  */                 else                print_str_opt("codec_long_name", "unknown");                                         // (0) 0.0918
/*48  */             }                                                                                                            // (17) 0.02344
/*50  */         } else {                                                                                                         // (21) 0.01953
/*52  */             print_str_opt("codec_name", "unknown");                                                                      // (6) 0.04883
/*54  */             if (!do_bitexact) {                                                                                          // (9) 0.03906
/*56  */                 print_str_opt("codec_long_name", "unknown");                                                             // (4) 0.06055
/*58  */             }                                                                                                            // 0.0
/*60  */         }                                                                                                                // 0.0
/*64  */         if (dec && (profile = av_get_profile_name(dec, dec_ctx->profile)))                                               // 0.0
/*66  */             print_str("profile", profile);                                                                               // 0.0
/*68  */         else                                                                                                             // 0.0
/*70  */             print_str_opt("profile", "unknown");                                                                         // 0.0
/*74  */         s = av_get_media_type_string(dec_ctx->codec_type);                                                               // 0.0
/*76  */         if (s) print_str    ("codec_type", s);                                                                           // 0.0
/*78  */         else   print_str_opt("codec_type", "unknown");                                                                   // 0.0
/*80  */         print_q("codec_time_base", dec_ctx->time_base, '/');                                                             // 0.0
/*84  */         /* print AVI/FourCC tag */                                                                                       // 0.0
/*86  */         av_get_codec_tag_string(val_str, sizeof(val_str), dec_ctx->codec_tag);                                           // 0.0
/*88  */         print_str("codec_tag_string",    val_str);                                                                       // 0.0
/*90  */         print_fmt("codec_tag", "0x%04x", dec_ctx->codec_tag);                                                            // 0.0
/*94  */         switch (dec_ctx->codec_type) {                                                                                   // 0.0
/*96  */         case AVMEDIA_TYPE_VIDEO:                                                                                         // 0.0
/*98  */             print_int("width",        dec_ctx->width);                                                                   // 0.0
/*100 */             print_int("height",       dec_ctx->height);                                                                  // 0.0
/*102 */             print_int("has_b_frames", dec_ctx->has_b_frames);                                                            // 0.0
/*104 */             sar = av_guess_sample_aspect_ratio(fmt_ctx, stream, NULL);                                                   // 0.0
/*106 */             if (sar.den) {                                                                                               // 0.0
/*108 */                 print_q("sample_aspect_ratio", sar, ':');                                                                // 0.0
/*110 */                 av_reduce(&dar.num, &dar.den,                                                                            // 0.0
/*112 */                           dec_ctx->width  * sar.num,                                                                     // 0.0
/*114 */                           dec_ctx->height * sar.den,                                                                     // 0.0
/*116 */                           1024*1024);                                                                                    // 0.0
/*118 */                 print_q("display_aspect_ratio", dar, ':');                                                               // 0.0
/*120 */             } else {                                                                                                     // 0.0
/*122 */                 print_str_opt("sample_aspect_ratio", "N/A");                                                             // 0.0
/*124 */                 print_str_opt("display_aspect_ratio", "N/A");                                                            // 0.0
/*126 */             }                                                                                                            // 0.0
/*128 */             s = av_get_pix_fmt_name(dec_ctx->pix_fmt);                                                                   // 0.0
/*130 */             if (s) print_str    ("pix_fmt", s);                                                                          // 0.0
/*132 */             else   print_str_opt("pix_fmt", "unknown");                                                                  // 0.0
/*134 */             print_int("level",   dec_ctx->level);                                                                        // 0.0
/*136 */             if (dec_ctx->timecode_frame_start >= 0) {                                                                    // 0.0
/*138 */                 char tcbuf[AV_TIMECODE_STR_SIZE];                                                                        // 0.0
/*140 */                 av_timecode_make_mpeg_tc_string(tcbuf, dec_ctx->timecode_frame_start);                                   // 0.0
/*142 */                 print_str("timecode", tcbuf);                                                                            // 0.0
/*144 */             } else {                                                                                                     // 0.0
/*146 */                 print_str_opt("timecode", "N/A");                                                                        // 0.0
/*148 */             }                                                                                                            // 0.0
/*150 */             break;                                                                                                       // 0.0
/*154 */         case AVMEDIA_TYPE_AUDIO:                                                                                         // 0.0
/*156 */             s = av_get_sample_fmt_name(dec_ctx->sample_fmt);                                                             // 0.0
/*158 */             if (s) print_str    ("sample_fmt", s);                                                                       // 0.0
/*160 */             else   print_str_opt("sample_fmt", "unknown");                                                               // 0.0
/*162 */             print_val("sample_rate",     dec_ctx->sample_rate, unit_hertz_str);                                          // 0.0
/*164 */             print_int("channels",        dec_ctx->channels);                                                             // 0.0
/*168 */             if (dec_ctx->channel_layout) {                                                                               // 0.0
/*170 */                 av_bprint_clear(&pbuf);                                                                                  // 0.0
/*172 */                 av_bprint_channel_layout(&pbuf, dec_ctx->channels, dec_ctx->channel_layout);                             // 0.0
/*174 */                 print_str    ("channel_layout", pbuf.str);                                                               // 0.0
/*176 */             } else {                                                                                                     // 0.0
/*178 */                 print_str_opt("channel_layout", "unknown");                                                              // 0.0
/*180 */             }                                                                                                            // 0.0
/*184 */             print_int("bits_per_sample", av_get_bits_per_sample(dec_ctx->codec_id));                                     // 0.0
/*186 */             break;                                                                                                       // 0.0
/*190 */         case AVMEDIA_TYPE_SUBTITLE:                                                                                      // 0.0
/*192 */             if (dec_ctx->width)                                                                                          // 0.0
/*194 */                 print_int("width",       dec_ctx->width);                                                                // 0.0
/*196 */             else                                                                                                         // 0.0
/*198 */                 print_str_opt("width",   "N/A");                                                                         // 0.0
/*200 */             if (dec_ctx->height)                                                                                         // 0.0
/*202 */                 print_int("height",      dec_ctx->height);                                                               // 0.0
/*204 */             else                                                                                                         // 0.0
/*206 */                 print_str_opt("height",  "N/A");                                                                         // 0.0
/*208 */             break;                                                                                                       // 0.0
/*210 */         }                                                                                                                // 0.0
/*212 */     } else {                                                                                                             // 0.0
/*214 */         print_str_opt("codec_type", "unknown");                                                                          // 0.0
/*216 */     }                                                                                                                    // 0.0
/*218 */     if (dec_ctx->codec && dec_ctx->codec->priv_class && show_private_data) {                                             // 0.0
/*220 */         const AVOption *opt = NULL;                                                                                      // 0.0
/*222 */         while (opt = av_opt_next(dec_ctx->priv_data,opt)) {                                                              // 0.0
/*224 */             uint8_t *str;                                                                                                // 0.0
/*226 */             if (opt->flags) continue;                                                                                    // 0.0
/*228 */             if (av_opt_get(dec_ctx->priv_data, opt->name, 0, &str) >= 0) {                                               // 0.0
/*230 */                 print_str(opt->name, str);                                                                               // 0.0
/*232 */                 av_free(str);                                                                                            // 0.0
/*234 */             }                                                                                                            // 0.0
/*236 */         }                                                                                                                // 0.0
/*238 */     }                                                                                                                    // 0.0
/*242 */     if (fmt_ctx->iformat->flags & AVFMT_SHOW_IDS) print_fmt    ("id", "0x%x", stream->id);                               // 0.0
/*244 */     else                                          print_str_opt("id", "N/A");                                            // 0.0
/*246 */     print_q("r_frame_rate",   stream->r_frame_rate,   '/');                                                              // 0.0
/*248 */     print_q("avg_frame_rate", stream->avg_frame_rate, '/');                                                              // 0.0
/*250 */     print_q("time_base",      stream->time_base,      '/');                                                              // 0.0
/*252 */     print_ts  ("start_pts",   stream->start_time);                                                                       // 0.0
/*254 */     print_time("start_time",  stream->start_time, &stream->time_base);                                                   // 0.0
/*256 */     print_ts  ("duration_ts", stream->duration);                                                                         // 0.0
/*258 */     print_time("duration",    stream->duration, &stream->time_base);                                                     // 0.0
/*260 */     if (dec_ctx->bit_rate > 0) print_val    ("bit_rate", dec_ctx->bit_rate, unit_bit_per_second_str);                    // 0.0
/*262 */     else                       print_str_opt("bit_rate", "N/A");                                                         // 0.0
/*264 */     if (stream->nb_frames) print_fmt    ("nb_frames", "%"PRId64, stream->nb_frames);                                     // 0.0
/*266 */     else                   print_str_opt("nb_frames", "N/A");                                                            // 0.0
/*268 */     if (nb_streams_frames[stream_idx])  print_fmt    ("nb_read_frames", "%"PRIu64, nb_streams_frames[stream_idx]);       // 0.0
/*270 */     else                                print_str_opt("nb_read_frames", "N/A");                                          // 0.0
/*272 */     if (nb_streams_packets[stream_idx]) print_fmt    ("nb_read_packets", "%"PRIu64, nb_streams_packets[stream_idx]);     // 0.0
/*274 */     else                                print_str_opt("nb_read_packets", "N/A");                                         // 0.0
/*276 */     if (do_show_data)                                                                                                    // 0.0
/*278 */         writer_print_data(w, "extradata", dec_ctx->extradata,                                                            // 0.0
/*280 */                                           dec_ctx->extradata_size);                                                      // 0.0
/*284 */     /* Print disposition information */                                                                                  // 0.0
/*286 */ #define PRINT_DISPOSITION(flagname, name) do {                                \                                          // 0.0
/*288 */         print_int(name, !!(stream->disposition & AV_DISPOSITION_##flagname)); \                                          // 0.0
/*290 */     } while (0)                                                                                                          // 0.0
/*294 */     if (do_show_stream_disposition) {                                                                                    // 0.0
/*296 */     writer_print_section_header(w, in_program ? SECTION_ID_PROGRAM_STREAM_DISPOSITION : SECTION_ID_STREAM_DISPOSITION);  // 0.0
/*298 */     PRINT_DISPOSITION(DEFAULT,          "default");                                                                      // 0.0
/*300 */     PRINT_DISPOSITION(DUB,              "dub");                                                                          // 0.0
/*302 */     PRINT_DISPOSITION(ORIGINAL,         "original");                                                                     // 0.0
/*304 */     PRINT_DISPOSITION(COMMENT,          "comment");                                                                      // 0.0
/*306 */     PRINT_DISPOSITION(LYRICS,           "lyrics");                                                                       // 0.0
/*308 */     PRINT_DISPOSITION(KARAOKE,          "karaoke");                                                                      // 0.0
/*310 */     PRINT_DISPOSITION(FORCED,           "forced");                                                                       // 0.0
/*312 */     PRINT_DISPOSITION(HEARING_IMPAIRED, "hearing_impaired");                                                             // 0.0
/*314 */     PRINT_DISPOSITION(VISUAL_IMPAIRED,  "visual_impaired");                                                              // 0.0
/*316 */     PRINT_DISPOSITION(CLEAN_EFFECTS,    "clean_effects");                                                                // 0.0
/*318 */     PRINT_DISPOSITION(ATTACHED_PIC,     "attached_pic");                                                                 // 0.0
/*320 */     writer_print_section_footer(w);                                                                                      // 0.0
/*322 */     }                                                                                                                    // 0.0
/*326 */     show_tags(w, stream->metadata, in_program ? SECTION_ID_PROGRAM_STREAM_TAGS : SECTION_ID_STREAM_TAGS);                // 0.0
/*330 */     writer_print_section_footer(w);                                                                                      // 0.0
/*332 */     av_bprint_finalize(&pbuf, NULL);                                                                                     // 0.0
/*334 */     fflush(stdout);                                                                                                      // 0.0
/*336 */ }                                                                                                                        // 0.0
