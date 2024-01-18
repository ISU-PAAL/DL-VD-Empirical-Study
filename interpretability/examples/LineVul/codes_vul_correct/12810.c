// commit message FFmpeg@2fc9a3eb7a (target=1, prob=0.9989785, correct=True): avformat/mux: Restore original ts in write_packet on error
/*0  */ static int write_packet(AVFormatContext *s, AVPacket *pkt)                                               // (12) 0.04151
/*1  */ {                                                                                                        // (21) 0.001978
/*2  */     int ret, did_split;                                                                                  // (18) 0.02627
/*3  */     if (s->output_ts_offset) {                                                                           // (17) 0.02718
/*4  */         AVStream *st = s->streams[pkt->stream_index];                                                    // (6) 0.04664
/*5  */         int64_t offset = av_rescale_q(s->output_ts_offset, AV_TIME_BASE_Q, st->time_base);               // (1) 0.08313
/*6  */         if (pkt->dts != AV_NOPTS_VALUE)                                                                  // (8) 0.04436
/*7  */             pkt->dts += offset;                                                                          // (15) 0.03663
/*8  */         if (pkt->pts != AV_NOPTS_VALUE)                                                                  // (9) 0.04435
/*9  */             pkt->pts += offset;                                                                          // (14) 0.03666
/*10 */     }                                                                                                    // (20) 0.007946
/*11 */     if (s->avoid_negative_ts > 0) {                                                                      // (16) 0.03088
/*12 */         AVStream *st = s->streams[pkt->stream_index];                                                    // (7) 0.04635
/*13 */         int64_t offset = st->mux_ts_offset;                                                              // (10) 0.04251
/*14 */         int64_t ts = s->internal->avoid_negative_ts_use_pts ? pkt->pts : pkt->dts;                       // (2) 0.07717
/*15 */         if (s->internal->offset == AV_NOPTS_VALUE && ts != AV_NOPTS_VALUE &&                             // (3) 0.06366
/*16 */             (ts < 0 || s->avoid_negative_ts == AVFMT_AVOID_NEG_TS_MAKE_ZERO)) {                          // (0) 0.0849
/*17 */             s->internal->offset = -ts;                                                                   // (13) 0.03857
/*18 */             s->internal->offset_timebase = st->time_base;                                                // (5) 0.05014
/*19 */         }                                                                                                // (19) 0.0157
/*20 */         if (s->internal->offset != AV_NOPTS_VALUE && !offset) {                                          // (4) 0.05217
/*21 */             offset = st->mux_ts_offset =                                                                 // (11) 0.04248
/*22 */                 av_rescale_q_rnd(s->internal->offset,                                                    // 0.0
/*23 */                                  s->internal->offset_timebase,                                           // 0.0
/*24 */                                  st->time_base,                                                          // 0.0
/*25 */                                  AV_ROUND_UP);                                                           // 0.0
/*26 */         }                                                                                                // 0.0
/*27 */         if (pkt->dts != AV_NOPTS_VALUE)                                                                  // 0.0
/*28 */             pkt->dts += offset;                                                                          // 0.0
/*29 */         if (pkt->pts != AV_NOPTS_VALUE)                                                                  // 0.0
/*30 */             pkt->pts += offset;                                                                          // 0.0
/*31 */         if (s->internal->avoid_negative_ts_use_pts) {                                                    // 0.0
/*32 */             if (pkt->pts != AV_NOPTS_VALUE && pkt->pts < 0) {                                            // 0.0
/*33 */                 av_log(s, AV_LOG_WARNING, "failed to avoid negative "                                    // 0.0
/*34 */                     "pts %s in stream %d.\n"                                                             // 0.0
/*35 */                     "Try -avoid_negative_ts 1 as a possible workaround.\n",                              // 0.0
/*36 */                     av_ts2str(pkt->dts),                                                                 // 0.0
/*37 */                     pkt->stream_index                                                                    // 0.0
/*38 */                 );                                                                                       // 0.0
/*39 */             }                                                                                            // 0.0
/*40 */         } else {                                                                                         // 0.0
/*41 */             av_assert2(pkt->dts == AV_NOPTS_VALUE || pkt->dts >= 0 || s->max_interleave_delta > 0);      // 0.0
/*42 */             if (pkt->dts != AV_NOPTS_VALUE && pkt->dts < 0) {                                            // 0.0
/*43 */                 av_log(s, AV_LOG_WARNING,                                                                // 0.0
/*44 */                     "Packets poorly interleaved, failed to avoid negative "                              // 0.0
/*45 */                     "timestamp %s in stream %d.\n"                                                       // 0.0
/*46 */                     "Try -max_interleave_delta 0 as a possible workaround.\n",                           // 0.0
/*47 */                     av_ts2str(pkt->dts),                                                                 // 0.0
/*48 */                     pkt->stream_index                                                                    // 0.0
/*49 */                 );                                                                                       // 0.0
/*50 */             }                                                                                            // 0.0
/*51 */         }                                                                                                // 0.0
/*52 */     }                                                                                                    // 0.0
/*53 */     did_split = av_packet_split_side_data(pkt);                                                          // 0.0
/*54 */     if (!s->internal->header_written) {                                                                  // 0.0
/*55 */         ret = s->internal->write_header_ret ? s->internal->write_header_ret : write_header_internal(s);  // 0.0
/*56 */         if (ret < 0)                                                                                     // 0.0
/*57 */             goto fail;                                                                                   // 0.0
/*58 */     }                                                                                                    // 0.0
/*59 */     if ((pkt->flags & AV_PKT_FLAG_UNCODED_FRAME)) {                                                      // 0.0
/*60 */         AVFrame *frame = (AVFrame *)pkt->data;                                                           // 0.0
/*61 */         av_assert0(pkt->size == UNCODED_FRAME_PACKET_SIZE);                                              // 0.0
/*62 */         ret = s->oformat->write_uncoded_frame(s, pkt->stream_index, &frame, 0);                          // 0.0
/*63 */         av_frame_free(&frame);                                                                           // 0.0
/*64 */     } else {                                                                                             // 0.0
/*65 */         ret = s->oformat->write_packet(s, pkt);                                                          // 0.0
/*66 */     }                                                                                                    // 0.0
/*67 */     if (s->pb && ret >= 0) {                                                                             // 0.0
/*68 */         if (s->flush_packets && s->flags & AVFMT_FLAG_FLUSH_PACKETS)                                     // 0.0
/*69 */             avio_flush(s->pb);                                                                           // 0.0
/*70 */         if (s->pb->error < 0)                                                                            // 0.0
/*71 */             ret = s->pb->error;                                                                          // 0.0
/*72 */     }                                                                                                    // 0.0
/*73 */ fail:                                                                                                    // 0.0
/*74 */     if (did_split)                                                                                       // 0.0
/*75 */         av_packet_merge_side_data(pkt);                                                                  // 0.0
/*76 */     if (ret < 0) {                                                                                       // 0.0
/*77 */         pkt->pts = pts_backup;                                                                           // 0.0
/*78 */         pkt->dts = dts_backup;                                                                           // 0.0
/*79 */     }                                                                                                    // 0.0
/*80 */     return ret;                                                                                          // 0.0
/*81 */ }                                                                                                        // 0.0
