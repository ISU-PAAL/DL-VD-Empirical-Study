// commit message FFmpeg@ddd86a2924 (target=1, prob=0.43690568, correct=False): ffmpeg: Fix division by 0 due to invalid timebase
/*0   */ static int output_packet(InputStream *ist,                                                                        // (15) 0.02344
/*2   */                          OutputStream *ost_table, int nb_ostreams,                                                // (1) 0.07617
/*4   */                          const AVPacket *pkt)                                                                     // (3) 0.0625
/*6   */ {                                                                                                                 // (23) 0.001953
/*8   */     int ret = 0, i;                                                                                               // (18) 0.01953
/*10  */     int got_output;                                                                                               // (20) 0.01563
/*12  */     int64_t pkt_pts = AV_NOPTS_VALUE;                                                                             // (4) 0.04102
/*16  */     AVPacket avpkt;                                                                                               // (19) 0.01953
/*20  */     if (ist->next_dts == AV_NOPTS_VALUE)                                                                          // (7) 0.03906
/*22  */         ist->next_dts = ist->dts;                                                                                 // (6) 0.04102
/*24  */     if (ist->next_pts == AV_NOPTS_VALUE)                                                                          // (8) 0.03906
/*26  */         ist->next_pts = ist->pts;                                                                                 // (5) 0.04102
/*30  */     if (pkt == NULL) {                                                                                            // (17) 0.02148
/*32  */         /* EOF handling */                                                                                        // (16) 0.02344
/*34  */         av_init_packet(&avpkt);                                                                                   // (10) 0.03516
/*36  */         avpkt.data = NULL;                                                                                        // (12) 0.0293
/*38  */         avpkt.size = 0;                                                                                           // (13) 0.0293
/*40  */         goto handle_eof;                                                                                          // (14) 0.02539
/*42  */     } else {                                                                                                      // (21) 0.01172
/*44  */         avpkt = *pkt;                                                                                             // (11) 0.0293
/*46  */     }                                                                                                             // (22) 0.007812
/*50  */     if (pkt->dts != AV_NOPTS_VALUE) {                                                                             // (9) 0.03906
/*52  */         ist->next_dts = ist->dts = av_rescale_q(pkt->dts, ist->st->time_base, AV_TIME_BASE_Q);                    // (0) 0.1016
/*54  */         if (ist->st->codec->codec_type != AVMEDIA_TYPE_VIDEO || !ist->decoding_needed)                            // (2) 0.07227
/*56  */             ist->next_pts = ist->pts = av_rescale_q(pkt->dts, ist->st->time_base, AV_TIME_BASE_Q);                // 0.0
/*58  */     }                                                                                                             // 0.0
/*60  */     if(pkt->pts != AV_NOPTS_VALUE)                                                                                // 0.0
/*62  */         pkt_pts = av_rescale_q(pkt->pts, ist->st->time_base, AV_TIME_BASE_Q);                                     // 0.0
/*66  */     // while we have more to decode or while the decoder did output something on EOF                              // 0.0
/*68  */     while (ist->decoding_needed && (avpkt.size > 0 || (!pkt && got_output))) {                                    // 0.0
/*70  */         int duration;                                                                                             // 0.0
/*72  */     handle_eof:                                                                                                   // 0.0
/*76  */         ist->pts = ist->next_pts;                                                                                 // 0.0
/*78  */         ist->dts = ist->next_dts;                                                                                 // 0.0
/*82  */         if (avpkt.size && avpkt.size != pkt->size) {                                                              // 0.0
/*84  */             av_log(NULL, ist->showed_multi_packet_warning ? AV_LOG_VERBOSE : AV_LOG_WARNING,                      // 0.0
/*86  */                    "Multiple frames in a packet from stream %d\n", pkt->stream_index);                            // 0.0
/*88  */             ist->showed_multi_packet_warning = 1;                                                                 // 0.0
/*90  */         }                                                                                                         // 0.0
/*94  */         switch (ist->st->codec->codec_type) {                                                                     // 0.0
/*96  */         case AVMEDIA_TYPE_AUDIO:                                                                                  // 0.0
/*98  */             ret = transcode_audio    (ist, &avpkt, &got_output);                                                  // 0.0
/*100 */             break;                                                                                                // 0.0
/*102 */         case AVMEDIA_TYPE_VIDEO:                                                                                  // 0.0
/*104 */             ret = transcode_video    (ist, &avpkt, &got_output, &pkt_pts);                                        // 0.0
/*106 */             if (avpkt.duration) {                                                                                 // 0.0
/*108 */                 duration = av_rescale_q(avpkt.duration, ist->st->time_base, AV_TIME_BASE_Q);                      // 0.0
/*110 */             } else if(ist->st->codec->time_base.num != 0) {                                                       // 0.0
/*112 */                 int ticks= ist->st->parser ? ist->st->parser->repeat_pict+1 : ist->st->codec->ticks_per_frame;    // 0.0
/*114 */                 duration = ((int64_t)AV_TIME_BASE *                                                               // 0.0
/*116 */                                 ist->st->codec->time_base.num * ticks) /                                          // 0.0
/*118 */                                 ist->st->codec->time_base.den;                                                    // 0.0
/*120 */             } else                                                                                                // 0.0
/*122 */                 duration = 0;                                                                                     // 0.0
/*126 */             if(ist->dts != AV_NOPTS_VALUE && duration) {                                                          // 0.0
/*128 */                 ist->next_dts += duration;                                                                        // 0.0
/*130 */             }else                                                                                                 // 0.0
/*132 */                 ist->next_dts = AV_NOPTS_VALUE;                                                                   // 0.0
/*136 */             if (got_output)                                                                                       // 0.0
/*138 */                 ist->next_pts += duration; //FIXME the duration is not correct in some cases                      // 0.0
/*140 */             break;                                                                                                // 0.0
/*142 */         case AVMEDIA_TYPE_SUBTITLE:                                                                               // 0.0
/*144 */             ret = transcode_subtitles(ist, &avpkt, &got_output);                                                  // 0.0
/*146 */             break;                                                                                                // 0.0
/*148 */         default:                                                                                                  // 0.0
/*150 */             return -1;                                                                                            // 0.0
/*152 */         }                                                                                                         // 0.0
/*156 */         if (ret < 0)                                                                                              // 0.0
/*158 */             return ret;                                                                                           // 0.0
/*162 */         avpkt.dts=                                                                                                // 0.0
/*164 */         avpkt.pts= AV_NOPTS_VALUE;                                                                                // 0.0
/*168 */         // touch data and size only if not EOF                                                                    // 0.0
/*170 */         if (pkt) {                                                                                                // 0.0
/*172 */             if(ist->st->codec->codec_type != AVMEDIA_TYPE_AUDIO)                                                  // 0.0
/*174 */                 ret = avpkt.size;                                                                                 // 0.0
/*176 */             avpkt.data += ret;                                                                                    // 0.0
/*178 */             avpkt.size -= ret;                                                                                    // 0.0
/*180 */         }                                                                                                         // 0.0
/*182 */         if (!got_output) {                                                                                        // 0.0
/*184 */             continue;                                                                                             // 0.0
/*186 */         }                                                                                                         // 0.0
/*188 */     }                                                                                                             // 0.0
/*192 */     /* handle stream copy */                                                                                      // 0.0
/*194 */     if (!ist->decoding_needed) {                                                                                  // 0.0
/*196 */         rate_emu_sleep(ist);                                                                                      // 0.0
/*198 */         ist->dts = ist->next_dts;                                                                                 // 0.0
/*200 */         switch (ist->st->codec->codec_type) {                                                                     // 0.0
/*202 */         case AVMEDIA_TYPE_AUDIO:                                                                                  // 0.0
/*204 */             ist->next_dts += ((int64_t)AV_TIME_BASE * ist->st->codec->frame_size) /                               // 0.0
/*206 */                              ist->st->codec->sample_rate;                                                         // 0.0
/*208 */             break;                                                                                                // 0.0
/*210 */         case AVMEDIA_TYPE_VIDEO:                                                                                  // 0.0
/*212 */             if (pkt->duration) {                                                                                  // 0.0
/*214 */                 ist->next_dts += av_rescale_q(pkt->duration, ist->st->time_base, AV_TIME_BASE_Q);                 // 0.0
/*216 */             } else if(ist->st->codec->time_base.num != 0) {                                                       // 0.0
/*218 */                 int ticks= ist->st->parser ? ist->st->parser->repeat_pict + 1 : ist->st->codec->ticks_per_frame;  // 0.0
/*220 */                 ist->next_dts += ((int64_t)AV_TIME_BASE *                                                         // 0.0
/*222 */                                   ist->st->codec->time_base.num * ticks) /                                        // 0.0
/*224 */                                   ist->st->codec->time_base.den;                                                  // 0.0
/*226 */             }                                                                                                     // 0.0
/*228 */             break;                                                                                                // 0.0
/*230 */         }                                                                                                         // 0.0
/*232 */         ist->pts = ist->dts;                                                                                      // 0.0
/*234 */         ist->next_pts = ist->next_dts;                                                                            // 0.0
/*236 */     }                                                                                                             // 0.0
/*238 */     for (i = 0; pkt && i < nb_ostreams; i++) {                                                                    // 0.0
/*240 */         OutputStream *ost = &ost_table[i];                                                                        // 0.0
/*244 */         if (!check_output_constraints(ist, ost) || ost->encoding_needed)                                          // 0.0
/*246 */             continue;                                                                                             // 0.0
/*250 */         do_streamcopy(ist, ost, pkt);                                                                             // 0.0
/*252 */     }                                                                                                             // 0.0
/*256 */     return 0;                                                                                                     // 0.0
/*258 */ }                                                                                                                 // 0.0
