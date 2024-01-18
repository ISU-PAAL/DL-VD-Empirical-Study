// commit message FFmpeg@9aa0606e87 (target=0, prob=0.44470468, correct=True): avformat/hls: properly take stream_index into account when seeking
/*0   */ static int hls_read_seek(AVFormatContext *s, int stream_index,                     // (7) 0.03906
/*2   */                                int64_t timestamp, int flags)                       // (3) 0.07617
/*4   */ {                                                                                  // (19) 0.001953
/*6   */     HLSContext *c = s->priv_data;                                                  // (12) 0.0293
/*8   */     int i;                                                                         // (18) 0.01172
/*10  */     int64_t seek_timestamp;                                                        // (16) 0.02344
/*12  */     int valid_for = -1;                                                            // (17) 0.02148
/*16  */     if ((flags & AVSEEK_FLAG_BYTE) || !c->variants[0]->playlists[0]->finished)     // (5) 0.06641
/*18  */         return AVERROR(ENOSYS);                                                    // (11) 0.03125
/*22  */     seek_timestamp = stream_index < 0 ? timestamp :                                // (10) 0.03125
/*24  */                      av_rescale_rnd(timestamp, AV_TIME_BASE,                       // (4) 0.07422
/*26  */                                     s->streams[stream_index]->time_base.den,       // (0) 0.09961
/*28  */                                     flags & AVSEEK_FLAG_BACKWARD ?                 // (2) 0.08984
/*30  */                                     AV_ROUND_DOWN : AV_ROUND_UP);                  // (1) 0.0957
/*34  */     if (s->duration < seek_timestamp)                                              // (14) 0.02734
/*36  */         return AVERROR(EIO);                                                       // (13) 0.0293
/*40  */     for (i = 0; i < c->n_playlists; i++) {                                         // (6) 0.04102
/*42  */         /* check first that the timestamp is valid for some playlist */            // (9) 0.03711
/*44  */         struct playlist *pls = c->playlists[i];                                    // (8) 0.03906
/*46  */         int seq_no;                                                                // (15) 0.02344
/*48  */         if (find_timestamp_in_playlist(c, pls, seek_timestamp, &seq_no)) {         // 0.0
/*50  */             /* set segment now so we do not need to search again below */          // 0.0
/*52  */             pls->cur_seq_no = seq_no;                                              // 0.0
/*54  */             valid_for = i;                                                         // 0.0
/*56  */             break;                                                                 // 0.0
/*58  */         }                                                                          // 0.0
/*60  */     }                                                                              // 0.0
/*64  */     if (valid_for < 0)                                                             // 0.0
/*66  */         return AVERROR(EIO);                                                       // 0.0
/*70  */     for (i = 0; i < c->n_playlists; i++) {                                         // 0.0
/*72  */         /* Reset reading */                                                        // 0.0
/*74  */         struct playlist *pls = c->playlists[i];                                    // 0.0
/*76  */         if (pls->input) {                                                          // 0.0
/*78  */             ffurl_close(pls->input);                                               // 0.0
/*80  */             pls->input = NULL;                                                     // 0.0
/*82  */         }                                                                          // 0.0
/*84  */         av_free_packet(&pls->pkt);                                                 // 0.0
/*86  */         reset_packet(&pls->pkt);                                                   // 0.0
/*88  */         pls->pb.eof_reached = 0;                                                   // 0.0
/*90  */         /* Clear any buffered data */                                              // 0.0
/*92  */         pls->pb.buf_end = pls->pb.buf_ptr = pls->pb.buffer;                        // 0.0
/*94  */         /* Reset the pos, to let the mpegts demuxer know we've seeked. */          // 0.0
/*96  */         pls->pb.pos = 0;                                                           // 0.0
/*100 */         pls->seek_timestamp = seek_timestamp;                                      // 0.0
/*102 */         pls->seek_flags = flags;                                                   // 0.0
/*106 */         /* set closest segment seq_no for playlists not handled above */           // 0.0
/*108 */         if (valid_for != i)                                                        // 0.0
/*110 */             find_timestamp_in_playlist(c, pls, seek_timestamp, &pls->cur_seq_no);  // 0.0
/*112 */     }                                                                              // 0.0
/*116 */     c->cur_timestamp = seek_timestamp;                                             // 0.0
/*120 */     return 0;                                                                      // 0.0
/*122 */ }                                                                                  // 0.0
