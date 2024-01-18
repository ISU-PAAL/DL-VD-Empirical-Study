// commit message FFmpeg@5dbb63feef (target=0, prob=0.5308394, correct=False): Apply the same logic used for subtitle stream selection to audio and video stream selection.
/*0   */ static int decode_thread(void *arg)                                                                            // (20) 0.01953
/*2   */ {                                                                                                              // (35) 0.001953
/*4   */     VideoState *is = arg;                                                                                      // (21) 0.01953
/*6   */     AVFormatContext *ic;                                                                                       // (30) 0.01758
/*8   */     int err, i, ret, video_index, audio_index, subtitle_index;                                                 // (2) 0.04297
/*10  */     AVPacket pkt1, *pkt = &pkt1;                                                                               // (5) 0.03711
/*12  */     AVFormatParameters params, *ap = &params;                                                                  // (10) 0.02734
/*16  */     video_index = -1;                                                                                          // (22) 0.01953
/*18  */     audio_index = -1;                                                                                          // (24) 0.01953
/*20  */     subtitle_index = -1;                                                                                       // (26) 0.01953
/*22  */     is->video_stream = -1;                                                                                     // (15) 0.02344
/*24  */     is->audio_stream = -1;                                                                                     // (14) 0.02344
/*26  */     is->subtitle_stream = -1;                                                                                  // (12) 0.02539
/*30  */     global_video_state = is;                                                                                   // (18) 0.02148
/*32  */     url_set_interrupt_cb(decode_interrupt_cb);                                                                 // (4) 0.03906
/*36  */     memset(ap, 0, sizeof(*ap));                                                                                // (11) 0.02734
/*40  */     ap->width = frame_width;                                                                                   // (17) 0.02148
/*42  */     ap->height= frame_height;                                                                                  // (19) 0.02148
/*44  */     ap->time_base= (AVRational){1, 25};                                                                        // (7) 0.03516
/*46  */     ap->pix_fmt = frame_pix_fmt;                                                                               // (6) 0.03711
/*50  */     err = av_open_input_file(&ic, is->filename, is->iformat, 0, ap);                                           // (1) 0.05469
/*52  */     if (err < 0) {                                                                                             // (28) 0.01953
/*54  */         print_error(is->filename, err);                                                                        // (8) 0.0332
/*56  */         ret = -1;                                                                                              // (16) 0.02344
/*58  */         goto fail;                                                                                             // (27) 0.01953
/*60  */     }                                                                                                          // (34) 0.007812
/*62  */     is->ic = ic;                                                                                               // (29) 0.01758
/*66  */     if(genpts)                                                                                                 // (32) 0.01758
/*68  */         ic->flags |= AVFMT_FLAG_GENPTS;                                                                        // (3) 0.04297
/*72  */     err = av_find_stream_info(ic);                                                                             // (9) 0.0293
/*74  */     if (err < 0) {                                                                                             // (23) 0.01953
/*76  */         fprintf(stderr, "%s: could not find codec parameters\n", is->filename);                                // (0) 0.05664
/*78  */         ret = -1;                                                                                              // (13) 0.02344
/*80  */         goto fail;                                                                                             // (25) 0.01953
/*82  */     }                                                                                                          // (33) 0.007812
/*84  */     if(ic->pb)                                                                                                 // (31) 0.01758
/*86  */         ic->pb->eof_reached= 0; //FIXME hack, ffplay maybe should not use url_feof() to test for the end       // 0.0
/*90  */     /* if seeking requested, we execute it */                                                                  // 0.0
/*92  */     if (start_time != AV_NOPTS_VALUE) {                                                                        // 0.0
/*94  */         int64_t timestamp;                                                                                     // 0.0
/*98  */         timestamp = start_time;                                                                                // 0.0
/*100 */         /* add the stream start time */                                                                        // 0.0
/*102 */         if (ic->start_time != AV_NOPTS_VALUE)                                                                  // 0.0
/*104 */             timestamp += ic->start_time;                                                                       // 0.0
/*106 */         ret = av_seek_frame(ic, -1, timestamp, AVSEEK_FLAG_BACKWARD);                                          // 0.0
/*108 */         if (ret < 0) {                                                                                         // 0.0
/*110 */             fprintf(stderr, "%s: could not seek to position %0.3f\n",                                          // 0.0
/*112 */                     is->filename, (double)timestamp / AV_TIME_BASE);                                           // 0.0
/*114 */         }                                                                                                      // 0.0
/*116 */     }                                                                                                          // 0.0
/*120 */     for(i = 0; i < ic->nb_streams; i++) {                                                                      // 0.0
/*122 */         AVCodecContext *enc = ic->streams[i]->codec;                                                           // 0.0
/*124 */         ic->streams[i]->discard = AVDISCARD_ALL;                                                               // 0.0
/*126 */         switch(enc->codec_type) {                                                                              // 0.0
/*128 */         case CODEC_TYPE_AUDIO:                                                                                 // 0.0
/*130 */             if ((audio_index < 0 || wanted_audio_stream-- > 0) && !audio_disable)                              // 0.0
/*132 */                 audio_index = i;                                                                               // 0.0
/*134 */             break;                                                                                             // 0.0
/*136 */         case CODEC_TYPE_VIDEO:                                                                                 // 0.0
/*138 */             if ((video_index < 0 || wanted_video_stream-- > 0) && !video_disable)                              // 0.0
/*140 */                 video_index = i;                                                                               // 0.0
/*142 */             break;                                                                                             // 0.0
/*144 */         case CODEC_TYPE_SUBTITLE:                                                                              // 0.0
/*146 */             if (wanted_subtitle_stream-- >= 0 && !video_disable)                                               // 0.0
/*148 */                 subtitle_index = i;                                                                            // 0.0
/*150 */             break;                                                                                             // 0.0
/*152 */         default:                                                                                               // 0.0
/*154 */             break;                                                                                             // 0.0
/*156 */         }                                                                                                      // 0.0
/*158 */     }                                                                                                          // 0.0
/*160 */     if (show_status) {                                                                                         // 0.0
/*162 */         dump_format(ic, 0, is->filename, 0);                                                                   // 0.0
/*164 */         dump_stream_info(ic);                                                                                  // 0.0
/*166 */     }                                                                                                          // 0.0
/*170 */     /* open the streams */                                                                                     // 0.0
/*172 */     if (audio_index >= 0) {                                                                                    // 0.0
/*174 */         stream_component_open(is, audio_index);                                                                // 0.0
/*176 */     }                                                                                                          // 0.0
/*180 */     if (video_index >= 0) {                                                                                    // 0.0
/*182 */         stream_component_open(is, video_index);                                                                // 0.0
/*184 */     } else {                                                                                                   // 0.0
/*186 */         if (!display_disable)                                                                                  // 0.0
/*188 */             is->show_audio = 1;                                                                                // 0.0
/*190 */     }                                                                                                          // 0.0
/*194 */     if (subtitle_index >= 0) {                                                                                 // 0.0
/*196 */         stream_component_open(is, subtitle_index);                                                             // 0.0
/*198 */     }                                                                                                          // 0.0
/*202 */     if (is->video_stream < 0 && is->audio_stream < 0) {                                                        // 0.0
/*204 */         fprintf(stderr, "%s: could not open codecs\n", is->filename);                                          // 0.0
/*206 */         ret = -1;                                                                                              // 0.0
/*208 */         goto fail;                                                                                             // 0.0
/*210 */     }                                                                                                          // 0.0
/*214 */     for(;;) {                                                                                                  // 0.0
/*216 */         if (is->abort_request)                                                                                 // 0.0
/*218 */             break;                                                                                             // 0.0
/*220 */         if (is->paused != is->last_paused) {                                                                   // 0.0
/*222 */             is->last_paused = is->paused;                                                                      // 0.0
/*224 */             if (is->paused)                                                                                    // 0.0
/*226 */                 av_read_pause(ic);                                                                             // 0.0
/*228 */             else                                                                                               // 0.0
/*230 */                 av_read_play(ic);                                                                              // 0.0
/*232 */         }                                                                                                      // 0.0
/*234 */ #if CONFIG_RTSP_DEMUXER                                                                                        // 0.0
/*236 */         if (is->paused && !strcmp(ic->iformat->name, "rtsp")) {                                                // 0.0
/*238 */             /* wait 10 ms to avoid trying to get another packet */                                             // 0.0
/*240 */             /* XXX: horrible */                                                                                // 0.0
/*242 */             SDL_Delay(10);                                                                                     // 0.0
/*244 */             continue;                                                                                          // 0.0
/*246 */         }                                                                                                      // 0.0
/*248 */ #endif                                                                                                         // 0.0
/*250 */         if (is->seek_req) {                                                                                    // 0.0
/*252 */             int stream_index= -1;                                                                              // 0.0
/*254 */             int64_t seek_target= is->seek_pos;                                                                 // 0.0
/*258 */             if     (is->   video_stream >= 0) stream_index= is->   video_stream;                               // 0.0
/*260 */             else if(is->   audio_stream >= 0) stream_index= is->   audio_stream;                               // 0.0
/*262 */             else if(is->subtitle_stream >= 0) stream_index= is->subtitle_stream;                               // 0.0
/*266 */             if(stream_index>=0){                                                                               // 0.0
/*268 */                 seek_target= av_rescale_q(seek_target, AV_TIME_BASE_Q, ic->streams[stream_index]->time_base);  // 0.0
/*270 */             }                                                                                                  // 0.0
/*274 */             ret = av_seek_frame(is->ic, stream_index, seek_target, is->seek_flags);                            // 0.0
/*276 */             if (ret < 0) {                                                                                     // 0.0
/*278 */                 fprintf(stderr, "%s: error while seeking\n", is->ic->filename);                                // 0.0
/*280 */             }else{                                                                                             // 0.0
/*282 */                 if (is->audio_stream >= 0) {                                                                   // 0.0
/*284 */                     packet_queue_flush(&is->audioq);                                                           // 0.0
/*286 */                     packet_queue_put(&is->audioq, &flush_pkt);                                                 // 0.0
/*288 */                 }                                                                                              // 0.0
/*290 */                 if (is->subtitle_stream >= 0) {                                                                // 0.0
/*292 */                     packet_queue_flush(&is->subtitleq);                                                        // 0.0
/*294 */                     packet_queue_put(&is->subtitleq, &flush_pkt);                                              // 0.0
/*296 */                 }                                                                                              // 0.0
/*298 */                 if (is->video_stream >= 0) {                                                                   // 0.0
/*300 */                     packet_queue_flush(&is->videoq);                                                           // 0.0
/*302 */                     packet_queue_put(&is->videoq, &flush_pkt);                                                 // 0.0
/*304 */                 }                                                                                              // 0.0
/*306 */             }                                                                                                  // 0.0
/*308 */             is->seek_req = 0;                                                                                  // 0.0
/*310 */         }                                                                                                      // 0.0
/*314 */         /* if the queue are full, no need to read more */                                                      // 0.0
/*316 */         if (is->audioq.size > MAX_AUDIOQ_SIZE ||                                                               // 0.0
/*318 */             is->videoq.size > MAX_VIDEOQ_SIZE ||                                                               // 0.0
/*320 */             is->subtitleq.size > MAX_SUBTITLEQ_SIZE) {                                                         // 0.0
/*322 */             /* wait 10 ms */                                                                                   // 0.0
/*324 */             SDL_Delay(10);                                                                                     // 0.0
/*326 */             continue;                                                                                          // 0.0
/*328 */         }                                                                                                      // 0.0
/*330 */         if(url_feof(ic->pb)) {                                                                                 // 0.0
/*332 */             av_init_packet(pkt);                                                                               // 0.0
/*334 */             pkt->data=NULL;                                                                                    // 0.0
/*336 */             pkt->size=0;                                                                                       // 0.0
/*338 */             pkt->stream_index= is->video_stream;                                                               // 0.0
/*340 */             packet_queue_put(&is->videoq, pkt);                                                                // 0.0
/*342 */             continue;                                                                                          // 0.0
/*344 */         }                                                                                                      // 0.0
/*346 */         ret = av_read_frame(ic, pkt);                                                                          // 0.0
/*348 */         if (ret < 0) {                                                                                         // 0.0
/*350 */             if (ret != AVERROR_EOF && url_ferror(ic->pb) == 0) {                                               // 0.0
/*352 */                 SDL_Delay(100); /* wait for user event */                                                      // 0.0
/*354 */                 continue;                                                                                      // 0.0
/*356 */             } else                                                                                             // 0.0
/*358 */                 break;                                                                                         // 0.0
/*360 */         }                                                                                                      // 0.0
/*362 */         if (pkt->stream_index == is->audio_stream) {                                                           // 0.0
/*364 */             packet_queue_put(&is->audioq, pkt);                                                                // 0.0
/*366 */         } else if (pkt->stream_index == is->video_stream) {                                                    // 0.0
/*368 */             packet_queue_put(&is->videoq, pkt);                                                                // 0.0
/*370 */         } else if (pkt->stream_index == is->subtitle_stream) {                                                 // 0.0
/*372 */             packet_queue_put(&is->subtitleq, pkt);                                                             // 0.0
/*374 */         } else {                                                                                               // 0.0
/*376 */             av_free_packet(pkt);                                                                               // 0.0
/*378 */         }                                                                                                      // 0.0
/*380 */     }                                                                                                          // 0.0
/*382 */     /* wait until the end */                                                                                   // 0.0
/*384 */     while (!is->abort_request) {                                                                               // 0.0
/*386 */         SDL_Delay(100);                                                                                        // 0.0
/*388 */     }                                                                                                          // 0.0
/*392 */     ret = 0;                                                                                                   // 0.0
/*394 */  fail:                                                                                                         // 0.0
/*396 */     /* disable interrupting */                                                                                 // 0.0
/*398 */     global_video_state = NULL;                                                                                 // 0.0
/*402 */     /* close each stream */                                                                                    // 0.0
/*404 */     if (is->audio_stream >= 0)                                                                                 // 0.0
/*406 */         stream_component_close(is, is->audio_stream);                                                          // 0.0
/*408 */     if (is->video_stream >= 0)                                                                                 // 0.0
/*410 */         stream_component_close(is, is->video_stream);                                                          // 0.0
/*412 */     if (is->subtitle_stream >= 0)                                                                              // 0.0
/*414 */         stream_component_close(is, is->subtitle_stream);                                                       // 0.0
/*416 */     if (is->ic) {                                                                                              // 0.0
/*418 */         av_close_input_file(is->ic);                                                                           // 0.0
/*420 */         is->ic = NULL; /* safety */                                                                            // 0.0
/*422 */     }                                                                                                          // 0.0
/*424 */     url_set_interrupt_cb(NULL);                                                                                // 0.0
/*428 */     if (ret != 0) {                                                                                            // 0.0
/*430 */         SDL_Event event;                                                                                       // 0.0
/*434 */         event.type = FF_QUIT_EVENT;                                                                            // 0.0
/*436 */         event.user.data1 = is;                                                                                 // 0.0
/*438 */         SDL_PushEvent(&event);                                                                                 // 0.0
/*440 */     }                                                                                                          // 0.0
/*442 */     return 0;                                                                                                  // 0.0
/*444 */ }                                                                                                              // 0.0
