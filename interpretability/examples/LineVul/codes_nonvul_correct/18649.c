// commit message FFmpeg@1dff9adcb9 (target=0, prob=0.4759513, correct=True): avformat/hls: Factor playlist need check to a common function
/*0  */ static int recheck_discard_flags(AVFormatContext *s, int first)                                     // (11) 0.03906
/*2  */ {                                                                                                   // (23) 0.001953
/*4  */     HLSContext *c = s->priv_data;                                                                   // (18) 0.0293
/*6  */     int i, changed = 0;                                                                             // (21) 0.01953
/*10 */     /* Check if any new streams are needed */                                                       // (20) 0.02344
/*12 */     for (i = 0; i < c->n_playlists; i++)                                                            // (12) 0.03906
/*14 */         c->playlists[i]->cur_needed = 0;                                                            // (7) 0.04102
/*18 */     for (i = 0; i < s->nb_streams; i++) {                                                           // (8) 0.04102
/*20 */         AVStream *st = s->streams[i];                                                               // (15) 0.03711
/*22 */         struct playlist *pls = c->playlists[s->streams[i]->id];                                     // (4) 0.05469
/*24 */         if (st->discard < AVDISCARD_ALL)                                                            // (9) 0.04102
/*26 */             pls->cur_needed = 1;                                                                    // (13) 0.03906
/*28 */     }                                                                                               // (22) 0.007812
/*30 */     for (i = 0; i < c->n_playlists; i++) {                                                          // (10) 0.04102
/*32 */         struct playlist *pls = c->playlists[i];                                                     // (14) 0.03906
/*34 */         if (pls->cur_needed && !pls->needed) {                                                      // (6) 0.04492
/*36 */             pls->needed = 1;                                                                        // (17) 0.03516
/*38 */             changed = 1;                                                                            // (19) 0.0293
/*40 */             pls->cur_seq_no = select_cur_seq_no(c, pls);                                            // (0) 0.06445
/*42 */             pls->pb.eof_reached = 0;                                                                // (5) 0.04688
/*44 */             if (c->cur_timestamp != AV_NOPTS_VALUE) {                                               // (3) 0.05664
/*46 */                 /* catch up */                                                                      // (16) 0.03711
/*48 */                 pls->seek_timestamp = c->cur_timestamp;                                             // (1) 0.05859
/*50 */                 pls->seek_flags = AVSEEK_FLAG_ANY;                                                  // (2) 0.05859
/*52 */                 pls->seek_stream_index = -1;                                                        // 0.0
/*54 */             }                                                                                       // 0.0
/*56 */             av_log(s, AV_LOG_INFO, "Now receiving playlist %d, segment %d\n", i, pls->cur_seq_no);  // 0.0
/*58 */         } else if (first && !pls->cur_needed && pls->needed) {                                      // 0.0
/*60 */             if (pls->input)                                                                         // 0.0
/*62 */                 ff_format_io_close(pls->parent, &pls->input);                                       // 0.0
/*64 */             pls->needed = 0;                                                                        // 0.0
/*66 */             changed = 1;                                                                            // 0.0
/*68 */             av_log(s, AV_LOG_INFO, "No longer receiving playlist %d\n", i);                         // 0.0
/*70 */         }                                                                                           // 0.0
/*72 */     }                                                                                               // 0.0
/*74 */     return changed;                                                                                 // 0.0
/*76 */ }                                                                                                   // 0.0
