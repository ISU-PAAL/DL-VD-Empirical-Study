// commit message FFmpeg@f929ab0569 (target=0, prob=0.44085202, correct=True): cosmetics: Write NULL pointer equality checks more compactly
/*0   */ static int process_input_packet(InputStream *ist, const AVPacket *pkt)                                           // (5) 0.04448
/*2   */ {                                                                                                                // (25) 0.002141
/*4   */     int i;                                                                                                       // (22) 0.01159
/*6   */     int got_output;                                                                                              // (20) 0.01548
/*8   */     AVPacket avpkt;                                                                                              // (19) 0.01929
/*12  */     if (ist->next_dts == AV_NOPTS_VALUE)                                                                         // (9) 0.03883
/*14  */         ist->next_dts = ist->last_dts;                                                                           // (7) 0.04428
/*18  */     if (pkt == NULL) {                                                                                           // (18) 0.02118
/*20  */         /* EOF handling */                                                                                       // (16) 0.02314
/*22  */         av_init_packet(&avpkt);                                                                                  // (11) 0.03471
/*24  */         avpkt.data = NULL;                                                                                       // (13) 0.02888
/*26  */         avpkt.size = 0;                                                                                          // (14) 0.02888
/*28  */         goto handle_eof;                                                                                         // (15) 0.02505
/*30  */     } else {                                                                                                     // (23) 0.01155
/*32  */         avpkt = *pkt;                                                                                            // (12) 0.02888
/*34  */     }                                                                                                            // (24) 0.007701
/*38  */     if (pkt->dts != AV_NOPTS_VALUE)                                                                              // (10) 0.03663
/*40  */         ist->next_dts = ist->last_dts = av_rescale_q(pkt->dts, ist->st->time_base, AV_TIME_BASE_Q);              // (0) 0.1041
/*44  */     // while we have more to decode or while the decoder did output something on EOF                             // (8) 0.04083
/*46  */     while (ist->decoding_needed && (avpkt.size > 0 || (!pkt && got_output))) {                                   // (3) 0.0579
/*48  */         int ret = 0;                                                                                             // (17) 0.02312
/*50  */     handle_eof:                                                                                                  // (21) 0.01542
/*54  */         ist->last_dts = ist->next_dts;                                                                           // (6) 0.04428
/*58  */         if (avpkt.size && avpkt.size != pkt->size &&                                                             // (4) 0.05011
/*60  */             !(ist->dec->capabilities & CODEC_CAP_SUBFRAMES)) {                                                   // (2) 0.06971
/*62  */             av_log(NULL, ist->showed_multi_packet_warning ? AV_LOG_VERBOSE : AV_LOG_WARNING,                     // (1) 0.08499
/*64  */                    "Multiple frames in a packet from stream %d\n", pkt->stream_index);                           // 0.0
/*66  */             ist->showed_multi_packet_warning = 1;                                                                // 0.0
/*68  */         }                                                                                                        // 0.0
/*72  */         switch (ist->dec_ctx->codec_type) {                                                                      // 0.0
/*74  */         case AVMEDIA_TYPE_AUDIO:                                                                                 // 0.0
/*76  */             ret = decode_audio    (ist, &avpkt, &got_output);                                                    // 0.0
/*78  */             break;                                                                                               // 0.0
/*80  */         case AVMEDIA_TYPE_VIDEO:                                                                                 // 0.0
/*82  */             ret = decode_video    (ist, &avpkt, &got_output);                                                    // 0.0
/*84  */             if (avpkt.duration)                                                                                  // 0.0
/*86  */                 ist->next_dts += av_rescale_q(avpkt.duration, ist->st->time_base, AV_TIME_BASE_Q);               // 0.0
/*88  */             else if (ist->st->avg_frame_rate.num)                                                                // 0.0
/*90  */                 ist->next_dts += av_rescale_q(1, av_inv_q(ist->st->avg_frame_rate),                              // 0.0
/*92  */                                               AV_TIME_BASE_Q);                                                   // 0.0
/*94  */             else if (ist->dec_ctx->time_base.num != 0) {                                                         // 0.0
/*96  */                 int ticks      = ist->st->parser ? ist->st->parser->repeat_pict + 1 :                            // 0.0
/*98  */                                                    ist->dec_ctx->ticks_per_frame;                                // 0.0
/*100 */                 ist->next_dts += av_rescale_q(ticks, ist->dec_ctx->time_base, AV_TIME_BASE_Q);                   // 0.0
/*102 */             }                                                                                                    // 0.0
/*104 */             break;                                                                                               // 0.0
/*106 */         case AVMEDIA_TYPE_SUBTITLE:                                                                              // 0.0
/*108 */             ret = transcode_subtitles(ist, &avpkt, &got_output);                                                 // 0.0
/*110 */             break;                                                                                               // 0.0
/*112 */         default:                                                                                                 // 0.0
/*114 */             return -1;                                                                                           // 0.0
/*116 */         }                                                                                                        // 0.0
/*120 */         if (ret < 0)                                                                                             // 0.0
/*122 */             return ret;                                                                                          // 0.0
/*124 */         // touch data and size only if not EOF                                                                   // 0.0
/*126 */         if (pkt) {                                                                                               // 0.0
/*128 */             avpkt.data += ret;                                                                                   // 0.0
/*130 */             avpkt.size -= ret;                                                                                   // 0.0
/*132 */         }                                                                                                        // 0.0
/*134 */         if (!got_output) {                                                                                       // 0.0
/*136 */             continue;                                                                                            // 0.0
/*138 */         }                                                                                                        // 0.0
/*140 */     }                                                                                                            // 0.0
/*144 */     /* handle stream copy */                                                                                     // 0.0
/*146 */     if (!ist->decoding_needed) {                                                                                 // 0.0
/*148 */         ist->last_dts = ist->next_dts;                                                                           // 0.0
/*150 */         switch (ist->dec_ctx->codec_type) {                                                                      // 0.0
/*152 */         case AVMEDIA_TYPE_AUDIO:                                                                                 // 0.0
/*154 */             ist->next_dts += ((int64_t)AV_TIME_BASE * ist->dec_ctx->frame_size) /                                // 0.0
/*156 */                              ist->dec_ctx->sample_rate;                                                          // 0.0
/*158 */             break;                                                                                               // 0.0
/*160 */         case AVMEDIA_TYPE_VIDEO:                                                                                 // 0.0
/*162 */             if (ist->dec_ctx->time_base.num != 0) {                                                              // 0.0
/*164 */                 int ticks = ist->st->parser ? ist->st->parser->repeat_pict + 1 : ist->dec_ctx->ticks_per_frame;  // 0.0
/*166 */                 ist->next_dts += ((int64_t)AV_TIME_BASE *                                                        // 0.0
/*168 */                                   ist->dec_ctx->time_base.num * ticks) /                                         // 0.0
/*170 */                                   ist->dec_ctx->time_base.den;                                                   // 0.0
/*172 */             }                                                                                                    // 0.0
/*174 */             break;                                                                                               // 0.0
/*176 */         }                                                                                                        // 0.0
/*178 */     }                                                                                                            // 0.0
/*180 */     for (i = 0; pkt && i < nb_output_streams; i++) {                                                             // 0.0
/*182 */         OutputStream *ost = output_streams[i];                                                                   // 0.0
/*186 */         if (!check_output_constraints(ist, ost) || ost->encoding_needed)                                         // 0.0
/*188 */             continue;                                                                                            // 0.0
/*192 */         do_streamcopy(ist, ost, pkt);                                                                            // 0.0
/*194 */     }                                                                                                            // 0.0
/*198 */     return 0;                                                                                                    // 0.0
/*200 */ }                                                                                                                // 0.0
