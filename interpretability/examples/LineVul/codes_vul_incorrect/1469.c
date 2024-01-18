// commit message FFmpeg@73a6063314 (target=1, prob=0.41911665, correct=False): ffprobe: fix crash happening because of new streams occuring
/*0   */ static int probe_file(WriterContext *wctx, const char *filename)                       // (11) 0.03322
/*2   */ {                                                                                      // (21) 0.001953
/*4   */     AVFormatContext *fmt_ctx;                                                          // (15) 0.02344
/*6   */     int ret, i;                                                                        // (20) 0.01563
/*8   */     int section_id;                                                                    // (19) 0.01568
/*12  */     do_read_frames = do_show_frames || do_count_frames;                                // (9) 0.04101
/*14  */     do_read_packets = do_show_packets || do_count_packets;                             // (7) 0.04687
/*18  */     ret = open_input_file(&fmt_ctx, filename);                                         // (10) 0.03516
/*20  */     if (ret < 0)                                                                       // (18) 0.01758
/*22  */         return ret;                                                                    // (17) 0.01953
/*26  */ #define CHECK_END if (ret < 0) goto end                                                // (14) 0.02734
/*30  */     nb_streams_frames  = av_calloc(fmt_ctx->nb_streams, sizeof(*nb_streams_frames));   // (3) 0.07031
/*32  */     nb_streams_packets = av_calloc(fmt_ctx->nb_streams, sizeof(*nb_streams_packets));  // (2) 0.07226
/*34  */     selected_streams   = av_calloc(fmt_ctx->nb_streams, sizeof(*selected_streams));    // (4) 0.06249
/*38  */     for (i = 0; i < fmt_ctx->nb_streams; i++) {                                        // (8) 0.04492
/*40  */         if (stream_specifier) {                                                        // (13) 0.02929
/*42  */             ret = avformat_match_stream_specifier(fmt_ctx,                             // (5) 0.05468
/*44  */                                                   fmt_ctx->streams[i],                 // (0) 0.1133
/*46  */                                                   stream_specifier);                   // (1) 0.1055
/*48  */             CHECK_END;                                                                 // (12) 0.03125
/*50  */             else                                                                       // (16) 0.02344
/*52  */                 selected_streams[i] = ret;                                             // (6) 0.04882
/*54  */             ret = 0;                                                                   // 0.0
/*56  */         } else {                                                                       // 0.0
/*58  */             selected_streams[i] = 1;                                                   // 0.0
/*60  */         }                                                                              // 0.0
/*62  */     }                                                                                  // 0.0
/*66  */     if (do_read_frames || do_read_packets) {                                           // 0.0
/*68  */         if (do_show_frames && do_show_packets &&                                       // 0.0
/*70  */             wctx->writer->flags & WRITER_FLAG_PUT_PACKETS_AND_FRAMES_IN_SAME_CHAPTER)  // 0.0
/*72  */             section_id = SECTION_ID_PACKETS_AND_FRAMES;                                // 0.0
/*74  */         else if (do_show_packets && !do_show_frames)                                   // 0.0
/*76  */             section_id = SECTION_ID_PACKETS;                                           // 0.0
/*78  */         else // (!do_show_packets && do_show_frames)                                   // 0.0
/*80  */             section_id = SECTION_ID_FRAMES;                                            // 0.0
/*82  */         if (do_show_frames || do_show_packets)                                         // 0.0
/*84  */             writer_print_section_header(wctx, section_id);                             // 0.0
/*86  */         ret = read_packets(wctx, fmt_ctx);                                             // 0.0
/*88  */         if (do_show_frames || do_show_packets)                                         // 0.0
/*90  */             writer_print_section_footer(wctx);                                         // 0.0
/*92  */         CHECK_END;                                                                     // 0.0
/*94  */     }                                                                                  // 0.0
/*98  */     if (do_show_programs) {                                                            // 0.0
/*100 */         ret = show_programs(wctx, fmt_ctx);                                            // 0.0
/*102 */         CHECK_END;                                                                     // 0.0
/*104 */     }                                                                                  // 0.0
/*108 */     if (do_show_streams) {                                                             // 0.0
/*110 */         ret = show_streams(wctx, fmt_ctx);                                             // 0.0
/*112 */         CHECK_END;                                                                     // 0.0
/*114 */     }                                                                                  // 0.0
/*116 */     if (do_show_chapters) {                                                            // 0.0
/*118 */         ret = show_chapters(wctx, fmt_ctx);                                            // 0.0
/*120 */         CHECK_END;                                                                     // 0.0
/*122 */     }                                                                                  // 0.0
/*124 */     if (do_show_format) {                                                              // 0.0
/*126 */         ret = show_format(wctx, fmt_ctx);                                              // 0.0
/*128 */         CHECK_END;                                                                     // 0.0
/*130 */     }                                                                                  // 0.0
/*134 */ end:                                                                                   // 0.0
/*136 */     close_input_file(&fmt_ctx);                                                        // 0.0
/*138 */     av_freep(&nb_streams_frames);                                                      // 0.0
/*140 */     av_freep(&nb_streams_packets);                                                     // 0.0
/*142 */     av_freep(&selected_streams);                                                       // 0.0
/*146 */     return ret;                                                                        // 0.0
/*148 */ }                                                                                      // 0.0
