// commit message FFmpeg@a55692a960 (target=1, prob=0.99922717, correct=True): ffprobe: check av_frame_alloc() failure.
/*0   */ static int read_interval_packets(WriterContext *w, AVFormatContext *fmt_ctx,                  // (7) 0.04688
/*2   */                                  const ReadInterval *interval, int64_t *cur_ts)               // (0) 0.0957
/*4   */ {                                                                                             // (21) 0.001953
/*6   */     AVPacket pkt, pkt1;                                                                       // (16) 0.02539
/*8   */     AVFrame *frame = NULL;                                                                    // (19) 0.01953
/*10  */     int ret = 0, i = 0, frame_count = 0;                                                      // (13) 0.03516
/*12  */     int64_t start = -INT64_MAX, end = interval->end;                                          // (11) 0.04102
/*14  */     int has_start = 0, has_end = interval->has_end && !interval->end_is_offset;               // (3) 0.05859
/*18  */     av_init_packet(&pkt);                                                                     // (15) 0.02539
/*22  */     av_log(NULL, AV_LOG_VERBOSE, "Processing read interval ");                                // (8) 0.04688
/*24  */     log_read_interval(interval, NULL, AV_LOG_VERBOSE);                                        // (9) 0.04492
/*28  */     if (interval->has_start) {                                                                // (17) 0.02539
/*30  */         int64_t target;                                                                       // (18) 0.02539
/*32  */         if (interval->start_is_offset) {                                                      // (12) 0.03711
/*34  */             if (*cur_ts == AV_NOPTS_VALUE) {                                                  // (5) 0.05078
/*36  */                 av_log(NULL, AV_LOG_ERROR,                                                    // (4) 0.05273
/*38  */                        "Could not seek to relative position since current "                   // (1) 0.0625
/*40  */                        "timestamp is not defined\n");                                         // (2) 0.06055
/*42  */                 ret = AVERROR(EINVAL);                                                        // (6) 0.04883
/*46  */             target = *cur_ts + interval->start;                                               // (10) 0.04297
/*48  */         } else {                                                                              // (20) 0.01953
/*50  */             target = interval->start;                                                         // (14) 0.0332
/*55  */         av_log(NULL, AV_LOG_VERBOSE, "Seeking to read interval start point %s\n",             // 0.0
/*57  */                av_ts2timestr(target, &AV_TIME_BASE_Q));                                       // 0.0
/*59  */         if ((ret = avformat_seek_file(fmt_ctx, -1, -INT64_MAX, target, INT64_MAX, 0)) < 0) {  // 0.0
/*61  */             av_log(NULL, AV_LOG_ERROR, "Could not seek to position %"PRId64": %s\n",          // 0.0
/*63  */                    interval->start, av_err2str(ret));                                         // 0.0
/*70  */     frame = av_frame_alloc();                                                                 // 0.0
/*76  */     while (!av_read_frame(fmt_ctx, &pkt)) {                                                   // 0.0
/*78  */         if (selected_streams[pkt.stream_index]) {                                             // 0.0
/*80  */             AVRational tb = fmt_ctx->streams[pkt.stream_index]->time_base;                    // 0.0
/*84  */             if (pkt.pts != AV_NOPTS_VALUE)                                                    // 0.0
/*86  */                 *cur_ts = av_rescale_q(pkt.pts, tb, AV_TIME_BASE_Q);                          // 0.0
/*90  */             if (!has_start && *cur_ts != AV_NOPTS_VALUE) {                                    // 0.0
/*92  */                 start = *cur_ts;                                                              // 0.0
/*94  */                 has_start = 1;                                                                // 0.0
/*99  */             if (has_start && !has_end && interval->end_is_offset) {                           // 0.0
/*101 */                 end = start + interval->end;                                                  // 0.0
/*103 */                 has_end = 1;                                                                  // 0.0
/*108 */             if (interval->end_is_offset && interval->duration_frames) {                       // 0.0
/*110 */                 if (frame_count >= interval->end)                                             // 0.0
/*112 */                     break;                                                                    // 0.0
/*114 */             } else if (has_end && *cur_ts != AV_NOPTS_VALUE && *cur_ts >= end) {              // 0.0
/*116 */                 break;                                                                        // 0.0
/*121 */             frame_count++;                                                                    // 0.0
/*123 */             if (do_read_packets) {                                                            // 0.0
/*125 */                 if (do_show_packets)                                                          // 0.0
/*127 */                     show_packet(w, fmt_ctx, &pkt, i++);                                       // 0.0
/*129 */                 nb_streams_packets[pkt.stream_index]++;                                       // 0.0
/*132 */             if (do_read_frames) {                                                             // 0.0
/*134 */                 pkt1 = pkt;                                                                   // 0.0
/*136 */                 while (pkt1.size && process_frame(w, fmt_ctx, frame, &pkt1) > 0);             // 0.0
/*140 */         av_free_packet(&pkt);                                                                 // 0.0
/*143 */     av_init_packet(&pkt);                                                                     // 0.0
/*145 */     pkt.data = NULL;                                                                          // 0.0
/*147 */     pkt.size = 0;                                                                             // 0.0
/*149 */     //Flush remaining frames that are cached in the decoder                                   // 0.0
/*151 */     for (i = 0; i < fmt_ctx->nb_streams; i++) {                                               // 0.0
/*153 */         pkt.stream_index = i;                                                                 // 0.0
/*155 */         if (do_read_frames)                                                                   // 0.0
/*157 */             while (process_frame(w, fmt_ctx, frame, &pkt) > 0);                               // 0.0
/*162 */ end:                                                                                          // 0.0
/*164 */     av_frame_free(&frame);                                                                    // 0.0
/*166 */     if (ret < 0) {                                                                            // 0.0
/*168 */         av_log(NULL, AV_LOG_ERROR, "Could not read packets in interval ");                    // 0.0
/*170 */         log_read_interval(interval, NULL, AV_LOG_ERROR);                                      // 0.0
/*173 */     return ret;                                                                               // 0.0
