// commit message FFmpeg@b754978a3b (target=0, prob=0.3362758, correct=True): caching of timestamps for mpeg-ps so seeking is faster move (av_)find_stream_index() to utils.c as its usefull outside mpeg.c assert checking enabled, to find bugs quicker, should obviously be disabled later (av_)add_index_entry() inserts new entries so that the list stays ordered and updates entries if already in it (av_)index_search_timestamp() cleanup (kill ugly goto) and shorter
/*0  */ static void av_build_index_raw(AVFormatContext *s)                    // (8) 0.04938
/*2  */ {                                                                     // (18) 0.003086
/*4  */     AVPacket pkt1, *pkt = &pkt1;                                      // (6) 0.05864
/*6  */     int ret;                                                          // (16) 0.01852
/*8  */     AVStream *st;                                                     // (13) 0.02469
/*12 */     st = s->streams[0];                                               // (12) 0.03704
/*14 */     av_read_frame_flush(s);                                           // (9) 0.04012
/*16 */     url_fseek(&s->pb, s->data_offset, SEEK_SET);                      // (3) 0.07099
/*20 */     for(;;) {                                                         // (14) 0.02469
/*22 */         ret = av_read_frame(s, pkt);                                  // (5) 0.06173
/*24 */         if (ret < 0)                                                  // (10) 0.04012
/*26 */             break;                                                    // (11) 0.04012
/*28 */         if (pkt->stream_index == 0 && st->parser &&                   // (4) 0.0679
/*30 */             (pkt->flags & PKT_FLAG_KEY)) {                            // (2) 0.07716
/*32 */             add_index_entry(st, st->parser->frame_offset, pkt->dts,   // (1) 0.1049
/*34 */                             AVINDEX_KEYFRAME);                        // (0) 0.108
/*36 */         }                                                             // (15) 0.02469
/*38 */         av_free_packet(pkt);                                          // (7) 0.05247
/*40 */     }                                                                 // (17) 0.01235
/*42 */ }                                                                     // (19) 0.003086
