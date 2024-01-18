// commit message FFmpeg@4bb0b31f76 (target=0, prob=0.45364913, correct=True): avconv: Initialize return value for codec copy path.
/*0   */ static int output_packet(InputStream *ist, int ist_index,                                                                                                 // (8) 0.03517
/*2   */                          OutputStream *ost_table, int nb_ostreams,                                                                                        // (1) 0.07617
/*4   */                          const AVPacket *pkt)                                                                                                             // (2) 0.0625
/*6   */ {                                                                                                                                                         // (30) 0.001958
/*8   */     AVFormatContext *os;                                                                                                                                  // (20) 0.01758
/*10  */     OutputStream *ost;                                                                                                                                    // (22) 0.01563
/*12  */     int ret, i;                                                                                                                                           // (21) 0.01566
/*14  */     int got_output;                                                                                                                                       // (23) 0.01563
/*16  */     void *buffer_to_free = NULL;                                                                                                                          // (14) 0.02539
/*18  */     static unsigned int samples_size= 0;                                                                                                                  // (16) 0.02344
/*20  */     AVSubtitle subtitle, *subtitle_to_free;                                                                                                               // (10) 0.03125
/*22  */     int64_t pkt_pts = AV_NOPTS_VALUE;                                                                                                                     // (4) 0.04101
/*24  */ #if CONFIG_AVFILTER                                                                                                                                       // (25) 0.01367
/*26  */     int frame_available;                                                                                                                                  // (24) 0.01562
/*28  */ #endif                                                                                                                                                    // (29) 0.003906
/*30  */     float quality;                                                                                                                                        // (26) 0.01172
/*34  */     AVPacket avpkt;                                                                                                                                       // (19) 0.01953
/*36  */     int bps = av_get_bytes_per_sample(ist->st->codec->sample_fmt);                                                                                        // (3) 0.05664
/*40  */     if(ist->next_pts == AV_NOPTS_VALUE)                                                                                                                   // (6) 0.03906
/*42  */         ist->next_pts= ist->pts;                                                                                                                          // (5) 0.04101
/*46  */     if (pkt == NULL) {                                                                                                                                    // (18) 0.02148
/*48  */         /* EOF handling */                                                                                                                                // (17) 0.02344
/*50  */         av_init_packet(&avpkt);                                                                                                                           // (9) 0.03515
/*52  */         avpkt.data = NULL;                                                                                                                                // (12) 0.02929
/*54  */         avpkt.size = 0;                                                                                                                                   // (13) 0.02929
/*56  */         goto handle_eof;                                                                                                                                  // (15) 0.02539
/*58  */     } else {                                                                                                                                              // (27) 0.01172
/*60  */         avpkt = *pkt;                                                                                                                                     // (11) 0.02929
/*62  */     }                                                                                                                                                     // (28) 0.007812
/*66  */     if(pkt->dts != AV_NOPTS_VALUE)                                                                                                                        // (7) 0.03711
/*68  */         ist->next_pts = ist->pts = av_rescale_q(pkt->dts, ist->st->time_base, AV_TIME_BASE_Q);                                                            // (0) 0.1016
/*70  */     if(pkt->pts != AV_NOPTS_VALUE)                                                                                                                        // 0.0
/*72  */         pkt_pts = av_rescale_q(pkt->pts, ist->st->time_base, AV_TIME_BASE_Q);                                                                             // 0.0
/*76  */     //while we have more to decode or while the decoder did output something on EOF                                                                       // 0.0
/*78  */     while (avpkt.size > 0 || (!pkt && got_output)) {                                                                                                      // 0.0
/*80  */         uint8_t *data_buf, *decoded_data_buf;                                                                                                             // 0.0
/*82  */         int data_size, decoded_data_size;                                                                                                                 // 0.0
/*84  */         AVFrame *decoded_frame, *filtered_frame;                                                                                                          // 0.0
/*86  */     handle_eof:                                                                                                                                           // 0.0
/*88  */         ist->pts= ist->next_pts;                                                                                                                          // 0.0
/*92  */         if(avpkt.size && avpkt.size != pkt->size)                                                                                                         // 0.0
/*94  */             av_log(NULL, ist->showed_multi_packet_warning ? AV_LOG_VERBOSE : AV_LOG_WARNING,                                                              // 0.0
/*96  */                    "Multiple frames in a packet from stream %d\n", pkt->stream_index);                                                                    // 0.0
/*98  */             ist->showed_multi_packet_warning=1;                                                                                                           // 0.0
/*102 */         /* decode the packet if needed */                                                                                                                 // 0.0
/*104 */         decoded_frame    = filtered_frame = NULL;                                                                                                         // 0.0
/*106 */         decoded_data_buf = NULL; /* fail safe */                                                                                                          // 0.0
/*108 */         decoded_data_size= 0;                                                                                                                             // 0.0
/*110 */         data_buf  = avpkt.data;                                                                                                                           // 0.0
/*112 */         data_size = avpkt.size;                                                                                                                           // 0.0
/*114 */         subtitle_to_free = NULL;                                                                                                                          // 0.0
/*116 */         if (ist->decoding_needed) {                                                                                                                       // 0.0
/*118 */             switch(ist->st->codec->codec_type) {                                                                                                          // 0.0
/*120 */             case AVMEDIA_TYPE_AUDIO:{                                                                                                                     // 0.0
/*122 */                 if(pkt && samples_size < FFMAX(pkt->size * bps, AVCODEC_MAX_AUDIO_FRAME_SIZE)) {                                                          // 0.0
/*124 */                     samples_size = FFMAX(pkt->size * bps, AVCODEC_MAX_AUDIO_FRAME_SIZE);                                                                  // 0.0
/*126 */                     av_free(samples);                                                                                                                     // 0.0
/*128 */                     samples= av_malloc(samples_size);                                                                                                     // 0.0
/*130 */                 }                                                                                                                                         // 0.0
/*132 */                 decoded_data_size= samples_size;                                                                                                          // 0.0
/*134 */                     /* XXX: could avoid copy if PCM 16 bits with same                                                                                     // 0.0
/*136 */                        endianness as CPU */                                                                                                               // 0.0
/*138 */                 ret = avcodec_decode_audio3(ist->st->codec, samples, &decoded_data_size,                                                                  // 0.0
/*140 */                                             &avpkt);                                                                                                      // 0.0
/*142 */                 if (ret < 0)                                                                                                                              // 0.0
/*144 */                     return ret;                                                                                                                           // 0.0
/*146 */                 avpkt.data += ret;                                                                                                                        // 0.0
/*148 */                 avpkt.size -= ret;                                                                                                                        // 0.0
/*150 */                 data_size   = ret;                                                                                                                        // 0.0
/*152 */                 got_output  = decoded_data_size > 0;                                                                                                      // 0.0
/*154 */                 /* Some bug in mpeg audio decoder gives */                                                                                                // 0.0
/*156 */                 /* decoded_data_size < 0, it seems they are overflows */                                                                                  // 0.0
/*158 */                 if (!got_output) {                                                                                                                        // 0.0
/*160 */                     /* no audio frame */                                                                                                                  // 0.0
/*162 */                     continue;                                                                                                                             // 0.0
/*164 */                 }                                                                                                                                         // 0.0
/*166 */                 decoded_data_buf = (uint8_t *)samples;                                                                                                    // 0.0
/*168 */                 ist->next_pts += ((int64_t)AV_TIME_BASE/bps * decoded_data_size) /                                                                        // 0.0
/*170 */                     (ist->st->codec->sample_rate * ist->st->codec->channels);                                                                             // 0.0
/*172 */                 break;}                                                                                                                                   // 0.0
/*174 */             case AVMEDIA_TYPE_VIDEO:                                                                                                                      // 0.0
/*176 */                     decoded_data_size = (ist->st->codec->width * ist->st->codec->height * 3) / 2;                                                         // 0.0
/*178 */                     if (!(decoded_frame = avcodec_alloc_frame()))                                                                                         // 0.0
/*180 */                         return AVERROR(ENOMEM);                                                                                                           // 0.0
/*182 */                     avpkt.pts = pkt_pts;                                                                                                                  // 0.0
/*184 */                     avpkt.dts = ist->pts;                                                                                                                 // 0.0
/*186 */                     pkt_pts = AV_NOPTS_VALUE;                                                                                                             // 0.0
/*190 */                     ret = avcodec_decode_video2(ist->st->codec,                                                                                           // 0.0
/*192 */                                                 decoded_frame, &got_output, &avpkt);                                                                      // 0.0
/*194 */                     quality = same_quant ? decoded_frame->quality : 0;                                                                                    // 0.0
/*196 */                     if (ret < 0)                                                                                                                          // 0.0
/*198 */                         goto fail;                                                                                                                        // 0.0
/*200 */                     if (!got_output) {                                                                                                                    // 0.0
/*202 */                         /* no picture yet */                                                                                                              // 0.0
/*204 */                         av_freep(&decoded_frame);                                                                                                         // 0.0
/*206 */                         goto discard_packet;                                                                                                              // 0.0
/*208 */                     }                                                                                                                                     // 0.0
/*210 */                     ist->next_pts = ist->pts = guess_correct_pts(&ist->pts_ctx, decoded_frame->pkt_pts,                                                   // 0.0
/*212 */                                                                  decoded_frame->pkt_dts);                                                                 // 0.0
/*214 */                     if (ist->st->codec->time_base.num != 0) {                                                                                             // 0.0
/*216 */                         int ticks= ist->st->parser ? ist->st->parser->repeat_pict+1 : ist->st->codec->ticks_per_frame;                                    // 0.0
/*218 */                         ist->next_pts += ((int64_t)AV_TIME_BASE *                                                                                         // 0.0
/*220 */                                           ist->st->codec->time_base.num * ticks) /                                                                        // 0.0
/*222 */                             ist->st->codec->time_base.den;                                                                                                // 0.0
/*224 */                     }                                                                                                                                     // 0.0
/*226 */                     avpkt.size = 0;                                                                                                                       // 0.0
/*228 */                     buffer_to_free = NULL;                                                                                                                // 0.0
/*230 */                     pre_process_video_frame(ist, (AVPicture *)decoded_frame, &buffer_to_free);                                                            // 0.0
/*232 */                     break;                                                                                                                                // 0.0
/*234 */             case AVMEDIA_TYPE_SUBTITLE:                                                                                                                   // 0.0
/*236 */                 ret = avcodec_decode_subtitle2(ist->st->codec,                                                                                            // 0.0
/*238 */                                                &subtitle, &got_output, &avpkt);                                                                           // 0.0
/*240 */                 if (ret < 0)                                                                                                                              // 0.0
/*242 */                     return ret;                                                                                                                           // 0.0
/*244 */                 if (!got_output) {                                                                                                                        // 0.0
/*246 */                     goto discard_packet;                                                                                                                  // 0.0
/*248 */                 }                                                                                                                                         // 0.0
/*250 */                 subtitle_to_free = &subtitle;                                                                                                             // 0.0
/*252 */                 avpkt.size = 0;                                                                                                                           // 0.0
/*254 */                 break;                                                                                                                                    // 0.0
/*256 */             default:                                                                                                                                      // 0.0
/*258 */                 return -1;                                                                                                                                // 0.0
/*260 */             }                                                                                                                                             // 0.0
/*262 */         } else {                                                                                                                                          // 0.0
/*264 */             switch(ist->st->codec->codec_type) {                                                                                                          // 0.0
/*266 */             case AVMEDIA_TYPE_AUDIO:                                                                                                                      // 0.0
/*268 */                 ist->next_pts += ((int64_t)AV_TIME_BASE * ist->st->codec->frame_size) /                                                                   // 0.0
/*270 */                     ist->st->codec->sample_rate;                                                                                                          // 0.0
/*272 */                 break;                                                                                                                                    // 0.0
/*274 */             case AVMEDIA_TYPE_VIDEO:                                                                                                                      // 0.0
/*276 */                 if (ist->st->codec->time_base.num != 0) {                                                                                                 // 0.0
/*278 */                     int ticks= ist->st->parser ? ist->st->parser->repeat_pict+1 : ist->st->codec->ticks_per_frame;                                        // 0.0
/*280 */                     ist->next_pts += ((int64_t)AV_TIME_BASE *                                                                                             // 0.0
/*282 */                                       ist->st->codec->time_base.num * ticks) /                                                                            // 0.0
/*284 */                         ist->st->codec->time_base.den;                                                                                                    // 0.0
/*286 */                 }                                                                                                                                         // 0.0
/*288 */                 break;                                                                                                                                    // 0.0
/*290 */             }                                                                                                                                             // 0.0
/*292 */             avpkt.size = 0;                                                                                                                               // 0.0
/*294 */         }                                                                                                                                                 // 0.0
/*298 */         // preprocess audio (volume)                                                                                                                      // 0.0
/*300 */         if (ist->st->codec->codec_type == AVMEDIA_TYPE_AUDIO) {                                                                                           // 0.0
/*302 */             if (audio_volume != 256) {                                                                                                                    // 0.0
/*304 */                 switch (ist->st->codec->sample_fmt) {                                                                                                     // 0.0
/*306 */                 case AV_SAMPLE_FMT_U8:                                                                                                                    // 0.0
/*308 */                 {                                                                                                                                         // 0.0
/*310 */                     uint8_t *volp = samples;                                                                                                              // 0.0
/*312 */                     for (i = 0; i < (decoded_data_size / sizeof(*volp)); i++) {                                                                           // 0.0
/*314 */                         int v = (((*volp - 128) * audio_volume + 128) >> 8) + 128;                                                                        // 0.0
/*316 */                         *volp++ = av_clip_uint8(v);                                                                                                       // 0.0
/*318 */                     }                                                                                                                                     // 0.0
/*320 */                     break;                                                                                                                                // 0.0
/*322 */                 }                                                                                                                                         // 0.0
/*324 */                 case AV_SAMPLE_FMT_S16:                                                                                                                   // 0.0
/*326 */                 {                                                                                                                                         // 0.0
/*328 */                 short *volp;                                                                                                                              // 0.0
/*330 */                 volp = samples;                                                                                                                           // 0.0
/*332 */                 for(i=0;i<(decoded_data_size / sizeof(short));i++) {                                                                                      // 0.0
/*334 */                     int v = ((*volp) * audio_volume + 128) >> 8;                                                                                          // 0.0
/*336 */                     *volp++ = av_clip_int16(v);                                                                                                           // 0.0
/*338 */                 }                                                                                                                                         // 0.0
/*340 */                 break;                                                                                                                                    // 0.0
/*342 */                 }                                                                                                                                         // 0.0
/*344 */                 case AV_SAMPLE_FMT_S32:                                                                                                                   // 0.0
/*346 */                 {                                                                                                                                         // 0.0
/*348 */                     int32_t *volp = samples;                                                                                                              // 0.0
/*350 */                     for (i = 0; i < (decoded_data_size / sizeof(*volp)); i++) {                                                                           // 0.0
/*352 */                         int64_t v = (((int64_t)*volp * audio_volume + 128) >> 8);                                                                         // 0.0
/*354 */                         *volp++ = av_clipl_int32(v);                                                                                                      // 0.0
/*356 */                     }                                                                                                                                     // 0.0
/*358 */                     break;                                                                                                                                // 0.0
/*360 */                 }                                                                                                                                         // 0.0
/*362 */                 case AV_SAMPLE_FMT_FLT:                                                                                                                   // 0.0
/*364 */                 {                                                                                                                                         // 0.0
/*366 */                     float *volp = samples;                                                                                                                // 0.0
/*368 */                     float scale = audio_volume / 256.f;                                                                                                   // 0.0
/*370 */                     for (i = 0; i < (decoded_data_size / sizeof(*volp)); i++) {                                                                           // 0.0
/*372 */                         *volp++ *= scale;                                                                                                                 // 0.0
/*374 */                     }                                                                                                                                     // 0.0
/*376 */                     break;                                                                                                                                // 0.0
/*378 */                 }                                                                                                                                         // 0.0
/*380 */                 case AV_SAMPLE_FMT_DBL:                                                                                                                   // 0.0
/*382 */                 {                                                                                                                                         // 0.0
/*384 */                     double *volp = samples;                                                                                                               // 0.0
/*386 */                     double scale = audio_volume / 256.;                                                                                                   // 0.0
/*388 */                     for (i = 0; i < (decoded_data_size / sizeof(*volp)); i++) {                                                                           // 0.0
/*390 */                         *volp++ *= scale;                                                                                                                 // 0.0
/*392 */                     }                                                                                                                                     // 0.0
/*394 */                     break;                                                                                                                                // 0.0
/*396 */                 }                                                                                                                                         // 0.0
/*398 */                 default:                                                                                                                                  // 0.0
/*400 */                     av_log(NULL, AV_LOG_FATAL,                                                                                                            // 0.0
/*402 */                            "Audio volume adjustment on sample format %s is not supported.\n",                                                             // 0.0
/*404 */                            av_get_sample_fmt_name(ist->st->codec->sample_fmt));                                                                           // 0.0
/*406 */                     exit_program(1);                                                                                                                      // 0.0
/*408 */                 }                                                                                                                                         // 0.0
/*410 */             }                                                                                                                                             // 0.0
/*412 */         }                                                                                                                                                 // 0.0
/*416 */         /* frame rate emulation */                                                                                                                        // 0.0
/*418 */         if (input_files[ist->file_index].rate_emu) {                                                                                                      // 0.0
/*420 */             int64_t pts = av_rescale(ist->pts, 1000000, AV_TIME_BASE);                                                                                    // 0.0
/*422 */             int64_t now = av_gettime() - ist->start;                                                                                                      // 0.0
/*424 */             if (pts > now)                                                                                                                                // 0.0
/*426 */                 usleep(pts - now);                                                                                                                        // 0.0
/*428 */         }                                                                                                                                                 // 0.0
/*430 */         /* if output time reached then transcode raw format,                                                                                              // 0.0
/*432 */            encode packets and output them */                                                                                                              // 0.0
/*434 */         for (i = 0; i < nb_ostreams; i++) {                                                                                                               // 0.0
/*436 */             OutputFile *of = &output_files[ost_table[i].file_index];                                                                                      // 0.0
/*438 */             int frame_size;                                                                                                                               // 0.0
/*442 */             ost = &ost_table[i];                                                                                                                          // 0.0
/*444 */             if (ost->source_index != ist_index)                                                                                                           // 0.0
/*446 */                 continue;                                                                                                                                 // 0.0
/*450 */             if (of->start_time && ist->pts < of->start_time)                                                                                              // 0.0
/*452 */                 continue;                                                                                                                                 // 0.0
/*456 */             if (of->recording_time != INT64_MAX &&                                                                                                        // 0.0
/*458 */                 av_compare_ts(ist->pts, AV_TIME_BASE_Q, of->recording_time + of->start_time,                                                              // 0.0
/*460 */                               (AVRational){1, 1000000}) >= 0) {                                                                                           // 0.0
/*462 */                 ost->is_past_recording_time = 1;                                                                                                          // 0.0
/*464 */                 continue;                                                                                                                                 // 0.0
/*466 */             }                                                                                                                                             // 0.0
/*470 */ #if CONFIG_AVFILTER                                                                                                                                       // 0.0
/*472 */             if (ist->st->codec->codec_type == AVMEDIA_TYPE_VIDEO &&                                                                                       // 0.0
/*474 */                 ost->input_video_filter) {                                                                                                                // 0.0
/*476 */                 AVRational sar;                                                                                                                           // 0.0
/*478 */                 if (ist->st->sample_aspect_ratio.num)                                                                                                     // 0.0
/*480 */                     sar = ist->st->sample_aspect_ratio;                                                                                                   // 0.0
/*482 */                 else                                                                                                                                      // 0.0
/*484 */                     sar = ist->st->codec->sample_aspect_ratio;                                                                                            // 0.0
/*486 */                 av_vsrc_buffer_add_frame(ost->input_video_filter, decoded_frame, ist->pts, sar);                                                          // 0.0
/*488 */                 if (!(filtered_frame = avcodec_alloc_frame())) {                                                                                          // 0.0
/*490 */                     ret = AVERROR(ENOMEM);                                                                                                                // 0.0
/*492 */                     goto fail;                                                                                                                            // 0.0
/*494 */                 }                                                                                                                                         // 0.0
/*496 */             }                                                                                                                                             // 0.0
/*498 */             frame_available = ist->st->codec->codec_type != AVMEDIA_TYPE_VIDEO ||                                                                         // 0.0
/*500 */                 !ost->output_video_filter || avfilter_poll_frame(ost->output_video_filter->inputs[0]);                                                    // 0.0
/*502 */             while (frame_available) {                                                                                                                     // 0.0
/*504 */                 AVRational ist_pts_tb;                                                                                                                    // 0.0
/*506 */                 if (ist->st->codec->codec_type == AVMEDIA_TYPE_VIDEO && ost->output_video_filter)                                                         // 0.0
/*508 */                     get_filtered_video_frame(ost->output_video_filter, filtered_frame, &ost->picref, &ist_pts_tb);                                        // 0.0
/*510 */                 if (ost->picref)                                                                                                                          // 0.0
/*512 */                     ist->pts = av_rescale_q(ost->picref->pts, ist_pts_tb, AV_TIME_BASE_Q);                                                                // 0.0
/*514 */ #else                                                                                                                                                     // 0.0
/*516 */                 filtered_frame = decoded_frame;                                                                                                           // 0.0
/*518 */ #endif                                                                                                                                                    // 0.0
/*520 */                 os = output_files[ost->file_index].ctx;                                                                                                   // 0.0
/*524 */                 /* set the input output pts pairs */                                                                                                      // 0.0
/*526 */                 //ost->sync_ipts = (double)(ist->pts + input_files[ist->file_index].ts_offset - start_time)/ AV_TIME_BASE;                                // 0.0
/*530 */                 if (ost->encoding_needed) {                                                                                                               // 0.0
/*532 */                     av_assert0(ist->decoding_needed);                                                                                                     // 0.0
/*534 */                     switch(ost->st->codec->codec_type) {                                                                                                  // 0.0
/*536 */                     case AVMEDIA_TYPE_AUDIO:                                                                                                              // 0.0
/*538 */                         do_audio_out(os, ost, ist, decoded_data_buf, decoded_data_size);                                                                  // 0.0
/*540 */                         break;                                                                                                                            // 0.0
/*542 */                     case AVMEDIA_TYPE_VIDEO:                                                                                                              // 0.0
/*544 */ #if CONFIG_AVFILTER                                                                                                                                       // 0.0
/*546 */                         if (ost->picref->video && !ost->frame_aspect_ratio)                                                                               // 0.0
/*548 */                             ost->st->codec->sample_aspect_ratio = ost->picref->video->pixel_aspect;                                                       // 0.0
/*550 */ #endif                                                                                                                                                    // 0.0
/*552 */                         do_video_out(os, ost, ist, filtered_frame, &frame_size,                                                                           // 0.0
/*554 */                                      same_quant ? quality : ost->st->codec->global_quality);                                                              // 0.0
/*556 */                         if (vstats_filename && frame_size)                                                                                                // 0.0
/*558 */                             do_video_stats(os, ost, frame_size);                                                                                          // 0.0
/*560 */                         break;                                                                                                                            // 0.0
/*562 */                     case AVMEDIA_TYPE_SUBTITLE:                                                                                                           // 0.0
/*564 */                         do_subtitle_out(os, ost, ist, &subtitle,                                                                                          // 0.0
/*566 */                                         pkt->pts);                                                                                                        // 0.0
/*568 */                         break;                                                                                                                            // 0.0
/*570 */                     default:                                                                                                                              // 0.0
/*572 */                         abort();                                                                                                                          // 0.0
/*574 */                     }                                                                                                                                     // 0.0
/*576 */                 } else {                                                                                                                                  // 0.0
/*578 */                     AVPacket opkt;                                                                                                                        // 0.0
/*580 */                     int64_t ost_tb_start_time= av_rescale_q(of->start_time, AV_TIME_BASE_Q, ost->st->time_base);                                          // 0.0
/*584 */                     av_init_packet(&opkt);                                                                                                                // 0.0
/*588 */                     if ((!ost->frame_number && !(pkt->flags & AV_PKT_FLAG_KEY)) && !copy_initial_nonkeyframes)                                            // 0.0
/*590 */ #if !CONFIG_AVFILTER                                                                                                                                      // 0.0
/*592 */                         continue;                                                                                                                         // 0.0
/*594 */ #else                                                                                                                                                     // 0.0
/*596 */                         goto cont;                                                                                                                        // 0.0
/*598 */ #endif                                                                                                                                                    // 0.0
/*602 */                     /* no reencoding needed : output the packet directly */                                                                               // 0.0
/*604 */                     /* force the input stream PTS */                                                                                                      // 0.0
/*608 */                     if(ost->st->codec->codec_type == AVMEDIA_TYPE_AUDIO)                                                                                  // 0.0
/*610 */                         audio_size += data_size;                                                                                                          // 0.0
/*612 */                     else if (ost->st->codec->codec_type == AVMEDIA_TYPE_VIDEO) {                                                                          // 0.0
/*614 */                         video_size += data_size;                                                                                                          // 0.0
/*616 */                         ost->sync_opts++;                                                                                                                 // 0.0
/*618 */                     }                                                                                                                                     // 0.0
/*622 */                     opkt.stream_index= ost->index;                                                                                                        // 0.0
/*624 */                     if(pkt->pts != AV_NOPTS_VALUE)                                                                                                        // 0.0
/*626 */                         opkt.pts= av_rescale_q(pkt->pts, ist->st->time_base, ost->st->time_base) - ost_tb_start_time;                                     // 0.0
/*628 */                     else                                                                                                                                  // 0.0
/*630 */                         opkt.pts= AV_NOPTS_VALUE;                                                                                                         // 0.0
/*634 */                     if (pkt->dts == AV_NOPTS_VALUE)                                                                                                       // 0.0
/*636 */                         opkt.dts = av_rescale_q(ist->pts, AV_TIME_BASE_Q, ost->st->time_base);                                                            // 0.0
/*638 */                     else                                                                                                                                  // 0.0
/*640 */                         opkt.dts = av_rescale_q(pkt->dts, ist->st->time_base, ost->st->time_base);                                                        // 0.0
/*642 */                     opkt.dts -= ost_tb_start_time;                                                                                                        // 0.0
/*646 */                     opkt.duration = av_rescale_q(pkt->duration, ist->st->time_base, ost->st->time_base);                                                  // 0.0
/*648 */                     opkt.flags= pkt->flags;                                                                                                               // 0.0
/*652 */                     //FIXME remove the following 2 lines they shall be replaced by the bitstream filters                                                  // 0.0
/*654 */                     if(   ost->st->codec->codec_id != CODEC_ID_H264                                                                                       // 0.0
/*656 */                        && ost->st->codec->codec_id != CODEC_ID_MPEG1VIDEO                                                                                 // 0.0
/*658 */                        && ost->st->codec->codec_id != CODEC_ID_MPEG2VIDEO                                                                                 // 0.0
/*660 */                        ) {                                                                                                                                // 0.0
/*662 */                         if(av_parser_change(ist->st->parser, ost->st->codec, &opkt.data, &opkt.size, data_buf, data_size, pkt->flags & AV_PKT_FLAG_KEY))  // 0.0
/*664 */                             opkt.destruct= av_destruct_packet;                                                                                            // 0.0
/*666 */                     } else {                                                                                                                              // 0.0
/*668 */                         opkt.data = data_buf;                                                                                                             // 0.0
/*670 */                         opkt.size = data_size;                                                                                                            // 0.0
/*672 */                     }                                                                                                                                     // 0.0
/*676 */                     write_frame(os, &opkt, ost->st->codec, ost->bitstream_filters);                                                                       // 0.0
/*678 */                     ost->st->codec->frame_number++;                                                                                                       // 0.0
/*680 */                     ost->frame_number++;                                                                                                                  // 0.0
/*682 */                     av_free_packet(&opkt);                                                                                                                // 0.0
/*684 */                 }                                                                                                                                         // 0.0
/*686 */ #if CONFIG_AVFILTER                                                                                                                                       // 0.0
/*688 */                 cont:                                                                                                                                     // 0.0
/*690 */                 frame_available = (ist->st->codec->codec_type == AVMEDIA_TYPE_VIDEO) &&                                                                   // 0.0
/*692 */                                    ost->output_video_filter && avfilter_poll_frame(ost->output_video_filter->inputs[0]);                                  // 0.0
/*694 */                 if (ost->picref)                                                                                                                          // 0.0
/*696 */                     avfilter_unref_buffer(ost->picref);                                                                                                   // 0.0
/*698 */             }                                                                                                                                             // 0.0
/*700 */             av_freep(&filtered_frame);                                                                                                                    // 0.0
/*702 */ #endif                                                                                                                                                    // 0.0
/*704 */             }                                                                                                                                             // 0.0
/*708 */ fail:                                                                                                                                                     // 0.0
/*710 */         av_free(buffer_to_free);                                                                                                                          // 0.0
/*712 */         /* XXX: allocate the subtitles in the codec ? */                                                                                                  // 0.0
/*714 */         if (subtitle_to_free) {                                                                                                                           // 0.0
/*716 */             avsubtitle_free(subtitle_to_free);                                                                                                            // 0.0
/*718 */             subtitle_to_free = NULL;                                                                                                                      // 0.0
/*720 */         }                                                                                                                                                 // 0.0
/*722 */         av_freep(&decoded_frame);                                                                                                                         // 0.0
/*724 */         if (ret < 0)                                                                                                                                      // 0.0
/*726 */             return ret;                                                                                                                                   // 0.0
/*728 */     }                                                                                                                                                     // 0.0
/*730 */  discard_packet:                                                                                                                                          // 0.0
/*734 */     return 0;                                                                                                                                             // 0.0
/*736 */ }                                                                                                                                                         // 0.0
