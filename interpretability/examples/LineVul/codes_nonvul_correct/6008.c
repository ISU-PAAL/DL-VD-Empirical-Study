// commit message FFmpeg@f7a02d5d69 (target=0, prob=0.42711684, correct=True): ffmpeg: initialize got_output, this silences a compiler warning from icc
/*0   */ static int output_packet(InputStream *ist, const AVPacket *pkt)                                                                        // (6) 0.03913
/*2   */ {                                                                                                                                      // (24) 0.001967
/*4   */     int ret = 0, i;                                                                                                                    // (18) 0.01953
/*6   */     int got_output;                                                                                                                    // (20) 0.01565
/*10  */     AVPacket avpkt;                                                                                                                    // (19) 0.01953
/*12  */     if (!ist->saw_first_ts) {                                                                                                          // (14) 0.02734
/*14  */         ist->dts = ist->st->avg_frame_rate.num ? - ist->st->codec->has_b_frames * AV_TIME_BASE / av_q2d(ist->st->avg_frame_rate) : 0;  // (0) 0.1347
/*16  */         ist->pts = 0;                                                                                                                  // (13) 0.02929
/*18  */         if (pkt != NULL && pkt->pts != AV_NOPTS_VALUE && !ist->decoding_needed) {                                                      // (3) 0.07225
/*20  */             ist->dts += av_rescale_q(pkt->pts, ist->st->time_base, AV_TIME_BASE_Q);                                                    // (1) 0.09373
/*22  */             ist->pts = ist->dts; //unused but better to set it to a value thats not totally wrong                                      // (2) 0.0742
/*24  */         }                                                                                                                              // (21) 0.01562
/*26  */         ist->saw_first_ts = 1;                                                                                                         // (10) 0.03515
/*28  */     }                                                                                                                                  // (23) 0.007811
/*32  */     if (ist->next_dts == AV_NOPTS_VALUE)                                                                                               // (7) 0.03905
/*34  */         ist->next_dts = ist->dts;                                                                                                      // (5) 0.04101
/*36  */     if (ist->next_pts == AV_NOPTS_VALUE)                                                                                               // (8) 0.03905
/*38  */         ist->next_pts = ist->pts;                                                                                                      // (4) 0.04101
/*42  */     if (pkt == NULL) {                                                                                                                 // (17) 0.02148
/*44  */         /* EOF handling */                                                                                                             // (16) 0.02344
/*46  */         av_init_packet(&avpkt);                                                                                                        // (9) 0.03515
/*48  */         avpkt.data = NULL;                                                                                                             // (12) 0.02929
/*50  */         avpkt.size = 0;                                                                                                                // (11) 0.02929
/*52  */         goto handle_eof;                                                                                                               // (15) 0.02543
/*54  */     } else {                                                                                                                           // (22) 0.01172
/*56  */         avpkt = *pkt;                                                                                                                  // 0.0
/*58  */     }                                                                                                                                  // 0.0
/*62  */     if (pkt->dts != AV_NOPTS_VALUE) {                                                                                                  // 0.0
/*64  */         ist->next_dts = ist->dts = av_rescale_q(pkt->dts, ist->st->time_base, AV_TIME_BASE_Q);                                         // 0.0
/*66  */         if (ist->st->codec->codec_type != AVMEDIA_TYPE_VIDEO || !ist->decoding_needed)                                                 // 0.0
/*68  */             ist->next_pts = ist->pts = ist->dts;                                                                                       // 0.0
/*70  */     }                                                                                                                                  // 0.0
/*74  */     // while we have more to decode or while the decoder did output something on EOF                                                   // 0.0
/*76  */     while (ist->decoding_needed && (avpkt.size > 0 || (!pkt && got_output))) {                                                         // 0.0
/*78  */         int duration;                                                                                                                  // 0.0
/*80  */     handle_eof:                                                                                                                        // 0.0
/*84  */         ist->pts = ist->next_pts;                                                                                                      // 0.0
/*86  */         ist->dts = ist->next_dts;                                                                                                      // 0.0
/*90  */         if (avpkt.size && avpkt.size != pkt->size) {                                                                                   // 0.0
/*92  */             av_log(NULL, ist->showed_multi_packet_warning ? AV_LOG_VERBOSE : AV_LOG_WARNING,                                           // 0.0
/*94  */                    "Multiple frames in a packet from stream %d\n", pkt->stream_index);                                                 // 0.0
/*96  */             ist->showed_multi_packet_warning = 1;                                                                                      // 0.0
/*98  */         }                                                                                                                              // 0.0
/*102 */         switch (ist->st->codec->codec_type) {                                                                                          // 0.0
/*104 */         case AVMEDIA_TYPE_AUDIO:                                                                                                       // 0.0
/*106 */             ret = decode_audio    (ist, &avpkt, &got_output);                                                                          // 0.0
/*108 */             break;                                                                                                                     // 0.0
/*110 */         case AVMEDIA_TYPE_VIDEO:                                                                                                       // 0.0
/*112 */             ret = decode_video    (ist, &avpkt, &got_output);                                                                          // 0.0
/*114 */             if (avpkt.duration) {                                                                                                      // 0.0
/*116 */                 duration = av_rescale_q(avpkt.duration, ist->st->time_base, AV_TIME_BASE_Q);                                           // 0.0
/*118 */             } else if(ist->st->codec->time_base.num != 0 && ist->st->codec->time_base.den != 0) {                                      // 0.0
/*120 */                 int ticks= ist->st->parser ? ist->st->parser->repeat_pict+1 : ist->st->codec->ticks_per_frame;                         // 0.0
/*122 */                 duration = ((int64_t)AV_TIME_BASE *                                                                                    // 0.0
/*124 */                                 ist->st->codec->time_base.num * ticks) /                                                               // 0.0
/*126 */                                 ist->st->codec->time_base.den;                                                                         // 0.0
/*128 */             } else                                                                                                                     // 0.0
/*130 */                 duration = 0;                                                                                                          // 0.0
/*134 */             if(ist->dts != AV_NOPTS_VALUE && duration) {                                                                               // 0.0
/*136 */                 ist->next_dts += duration;                                                                                             // 0.0
/*138 */             }else                                                                                                                      // 0.0
/*140 */                 ist->next_dts = AV_NOPTS_VALUE;                                                                                        // 0.0
/*144 */             if (got_output)                                                                                                            // 0.0
/*146 */                 ist->next_pts += duration; //FIXME the duration is not correct in some cases                                           // 0.0
/*148 */             break;                                                                                                                     // 0.0
/*150 */         case AVMEDIA_TYPE_SUBTITLE:                                                                                                    // 0.0
/*152 */             ret = transcode_subtitles(ist, &avpkt, &got_output);                                                                       // 0.0
/*154 */             break;                                                                                                                     // 0.0
/*156 */         default:                                                                                                                       // 0.0
/*158 */             return -1;                                                                                                                 // 0.0
/*160 */         }                                                                                                                              // 0.0
/*164 */         if (ret < 0)                                                                                                                   // 0.0
/*166 */             return ret;                                                                                                                // 0.0
/*170 */         avpkt.dts=                                                                                                                     // 0.0
/*172 */         avpkt.pts= AV_NOPTS_VALUE;                                                                                                     // 0.0
/*176 */         // touch data and size only if not EOF                                                                                         // 0.0
/*178 */         if (pkt) {                                                                                                                     // 0.0
/*180 */             if(ist->st->codec->codec_type != AVMEDIA_TYPE_AUDIO)                                                                       // 0.0
/*182 */                 ret = avpkt.size;                                                                                                      // 0.0
/*184 */             avpkt.data += ret;                                                                                                         // 0.0
/*186 */             avpkt.size -= ret;                                                                                                         // 0.0
/*188 */         }                                                                                                                              // 0.0
/*190 */         if (!got_output) {                                                                                                             // 0.0
/*192 */             continue;                                                                                                                  // 0.0
/*194 */         }                                                                                                                              // 0.0
/*196 */     }                                                                                                                                  // 0.0
/*200 */     /* handle stream copy */                                                                                                           // 0.0
/*202 */     if (!ist->decoding_needed) {                                                                                                       // 0.0
/*204 */         rate_emu_sleep(ist);                                                                                                           // 0.0
/*206 */         ist->dts = ist->next_dts;                                                                                                      // 0.0
/*208 */         switch (ist->st->codec->codec_type) {                                                                                          // 0.0
/*210 */         case AVMEDIA_TYPE_AUDIO:                                                                                                       // 0.0
/*212 */             ist->next_dts += ((int64_t)AV_TIME_BASE * ist->st->codec->frame_size) /                                                    // 0.0
/*214 */                              ist->st->codec->sample_rate;                                                                              // 0.0
/*216 */             break;                                                                                                                     // 0.0
/*218 */         case AVMEDIA_TYPE_VIDEO:                                                                                                       // 0.0
/*220 */             if (pkt->duration) {                                                                                                       // 0.0
/*222 */                 ist->next_dts += av_rescale_q(pkt->duration, ist->st->time_base, AV_TIME_BASE_Q);                                      // 0.0
/*224 */             } else if(ist->st->codec->time_base.num != 0) {                                                                            // 0.0
/*226 */                 int ticks= ist->st->parser ? ist->st->parser->repeat_pict + 1 : ist->st->codec->ticks_per_frame;                       // 0.0
/*228 */                 ist->next_dts += ((int64_t)AV_TIME_BASE *                                                                              // 0.0
/*230 */                                   ist->st->codec->time_base.num * ticks) /                                                             // 0.0
/*232 */                                   ist->st->codec->time_base.den;                                                                       // 0.0
/*234 */             }                                                                                                                          // 0.0
/*236 */             break;                                                                                                                     // 0.0
/*238 */         }                                                                                                                              // 0.0
/*240 */         ist->pts = ist->dts;                                                                                                           // 0.0
/*242 */         ist->next_pts = ist->next_dts;                                                                                                 // 0.0
/*244 */     }                                                                                                                                  // 0.0
/*246 */     for (i = 0; pkt && i < nb_output_streams; i++) {                                                                                   // 0.0
/*248 */         OutputStream *ost = output_streams[i];                                                                                         // 0.0
/*252 */         if (!check_output_constraints(ist, ost) || ost->encoding_needed)                                                               // 0.0
/*254 */             continue;                                                                                                                  // 0.0
/*258 */         do_streamcopy(ist, ost, pkt);                                                                                                  // 0.0
/*260 */     }                                                                                                                                  // 0.0
/*264 */     return 0;                                                                                                                          // 0.0
/*266 */ }                                                                                                                                      // 0.0
