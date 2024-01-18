// commit message FFmpeg@b853cfe7ea (target=0, prob=0.53828037, correct=False): ffplay: remove refresh thread to achieve more precise frame delay
/*0   */ static int read_thread(void *arg)                                                                                          // (19) 0.01953
/*2   */ {                                                                                                                          // (31) 0.001953
/*4   */     VideoState *is = arg;                                                                                                  // (20) 0.01953
/*6   */     AVFormatContext *ic = NULL;                                                                                            // (17) 0.02148
/*8   */     int err, i, ret;                                                                                                       // (25) 0.01953
/*10  */     int st_index[AVMEDIA_TYPE_NB];                                                                                         // (12) 0.03125
/*12  */     AVPacket pkt1, *pkt = &pkt1;                                                                                           // (7) 0.03711
/*14  */     int eof = 0;                                                                                                           // (27) 0.01758
/*16  */     int pkt_in_play_range = 0;                                                                                             // (13) 0.0293
/*18  */     AVDictionaryEntry *t;                                                                                                  // (21) 0.01953
/*20  */     AVDictionary **opts;                                                                                                   // (24) 0.01953
/*22  */     int orig_nb_streams;                                                                                                   // (18) 0.02148
/*24  */     SDL_mutex *wait_mutex = SDL_CreateMutex();                                                                             // (8) 0.03711
/*28  */     memset(st_index, -1, sizeof(st_index));                                                                                // (10) 0.03711
/*30  */     is->last_video_stream = is->video_stream = -1;                                                                         // (6) 0.03906
/*32  */     is->last_audio_stream = is->audio_stream = -1;                                                                         // (5) 0.03906
/*34  */     is->last_subtitle_stream = is->subtitle_stream = -1;                                                                   // (3) 0.04297
/*38  */     ic = avformat_alloc_context();                                                                                         // (15) 0.02344
/*40  */     ic->interrupt_callback.callback = decode_interrupt_cb;                                                                 // (9) 0.03711
/*42  */     ic->interrupt_callback.opaque = is;                                                                                    // (14) 0.0293
/*44  */     err = avformat_open_input(&ic, is->filename, is->iformat, &format_opts);                                               // (2) 0.05664
/*46  */     if (err < 0) {                                                                                                         // (26) 0.01953
/*48  */         print_error(is->filename, err);                                                                                    // (11) 0.0332
/*50  */         ret = -1;                                                                                                          // (16) 0.02344
/*52  */         goto fail;                                                                                                         // (23) 0.01953
/*54  */     }                                                                                                                      // (30) 0.007812
/*56  */     if ((t = av_dict_get(format_opts, "", NULL, AV_DICT_IGNORE_SUFFIX))) {                                                 // (0) 0.06836
/*58  */         av_log(NULL, AV_LOG_ERROR, "Option %s not found.\n", t->key);                                                      // (1) 0.06445
/*60  */         ret = AVERROR_OPTION_NOT_FOUND;                                                                                    // (4) 0.04102
/*62  */         goto fail;                                                                                                         // (22) 0.01953
/*64  */     }                                                                                                                      // (29) 0.007812
/*66  */     is->ic = ic;                                                                                                           // (28) 0.01758
/*70  */     if (genpts)                                                                                                            // 0.0
/*72  */         ic->flags |= AVFMT_FLAG_GENPTS;                                                                                    // 0.0
/*76  */     opts = setup_find_stream_info_opts(ic, codec_opts);                                                                    // 0.0
/*78  */     orig_nb_streams = ic->nb_streams;                                                                                      // 0.0
/*82  */     err = avformat_find_stream_info(ic, opts);                                                                             // 0.0
/*84  */     if (err < 0) {                                                                                                         // 0.0
/*86  */         fprintf(stderr, "%s: could not find codec parameters\n", is->filename);                                            // 0.0
/*88  */         ret = -1;                                                                                                          // 0.0
/*90  */         goto fail;                                                                                                         // 0.0
/*92  */     }                                                                                                                      // 0.0
/*94  */     for (i = 0; i < orig_nb_streams; i++)                                                                                  // 0.0
/*96  */         av_dict_free(&opts[i]);                                                                                            // 0.0
/*98  */     av_freep(&opts);                                                                                                       // 0.0
/*102 */     if (ic->pb)                                                                                                            // 0.0
/*104 */         ic->pb->eof_reached = 0; // FIXME hack, ffplay maybe should not use url_feof() to test for the end                 // 0.0
/*108 */     if (seek_by_bytes < 0)                                                                                                 // 0.0
/*110 */         seek_by_bytes = !!(ic->iformat->flags & AVFMT_TS_DISCONT);                                                         // 0.0
/*114 */     is->max_frame_duration = (ic->iformat->flags & AVFMT_TS_DISCONT) ? 10.0 : 3600.0;                                      // 0.0
/*118 */     /* if seeking requested, we execute it */                                                                              // 0.0
/*120 */     if (start_time != AV_NOPTS_VALUE) {                                                                                    // 0.0
/*122 */         int64_t timestamp;                                                                                                 // 0.0
/*126 */         timestamp = start_time;                                                                                            // 0.0
/*128 */         /* add the stream start time */                                                                                    // 0.0
/*130 */         if (ic->start_time != AV_NOPTS_VALUE)                                                                              // 0.0
/*132 */             timestamp += ic->start_time;                                                                                   // 0.0
/*134 */         ret = avformat_seek_file(ic, -1, INT64_MIN, timestamp, INT64_MAX, 0);                                              // 0.0
/*136 */         if (ret < 0) {                                                                                                     // 0.0
/*138 */             fprintf(stderr, "%s: could not seek to position %0.3f\n",                                                      // 0.0
/*140 */                     is->filename, (double)timestamp / AV_TIME_BASE);                                                       // 0.0
/*142 */         }                                                                                                                  // 0.0
/*144 */     }                                                                                                                      // 0.0
/*148 */     is->realtime = is_realtime(ic);                                                                                        // 0.0
/*152 */     for (i = 0; i < ic->nb_streams; i++)                                                                                   // 0.0
/*154 */         ic->streams[i]->discard = AVDISCARD_ALL;                                                                           // 0.0
/*156 */     if (!video_disable)                                                                                                    // 0.0
/*158 */         st_index[AVMEDIA_TYPE_VIDEO] =                                                                                     // 0.0
/*160 */             av_find_best_stream(ic, AVMEDIA_TYPE_VIDEO,                                                                    // 0.0
/*162 */                                 wanted_stream[AVMEDIA_TYPE_VIDEO], -1, NULL, 0);                                           // 0.0
/*164 */     if (!audio_disable)                                                                                                    // 0.0
/*166 */         st_index[AVMEDIA_TYPE_AUDIO] =                                                                                     // 0.0
/*168 */             av_find_best_stream(ic, AVMEDIA_TYPE_AUDIO,                                                                    // 0.0
/*170 */                                 wanted_stream[AVMEDIA_TYPE_AUDIO],                                                         // 0.0
/*172 */                                 st_index[AVMEDIA_TYPE_VIDEO],                                                              // 0.0
/*174 */                                 NULL, 0);                                                                                  // 0.0
/*176 */     if (!video_disable)                                                                                                    // 0.0
/*178 */         st_index[AVMEDIA_TYPE_SUBTITLE] =                                                                                  // 0.0
/*180 */             av_find_best_stream(ic, AVMEDIA_TYPE_SUBTITLE,                                                                 // 0.0
/*182 */                                 wanted_stream[AVMEDIA_TYPE_SUBTITLE],                                                      // 0.0
/*184 */                                 (st_index[AVMEDIA_TYPE_AUDIO] >= 0 ?                                                       // 0.0
/*186 */                                  st_index[AVMEDIA_TYPE_AUDIO] :                                                            // 0.0
/*188 */                                  st_index[AVMEDIA_TYPE_VIDEO]),                                                            // 0.0
/*190 */                                 NULL, 0);                                                                                  // 0.0
/*192 */     if (show_status) {                                                                                                     // 0.0
/*194 */         av_dump_format(ic, 0, is->filename, 0);                                                                            // 0.0
/*196 */     }                                                                                                                      // 0.0
/*200 */     is->show_mode = show_mode;                                                                                             // 0.0
/*204 */     /* open the streams */                                                                                                 // 0.0
/*206 */     if (st_index[AVMEDIA_TYPE_AUDIO] >= 0) {                                                                               // 0.0
/*208 */         stream_component_open(is, st_index[AVMEDIA_TYPE_AUDIO]);                                                           // 0.0
/*210 */     }                                                                                                                      // 0.0
/*214 */     ret = -1;                                                                                                              // 0.0
/*216 */     if (st_index[AVMEDIA_TYPE_VIDEO] >= 0) {                                                                               // 0.0
/*218 */         ret = stream_component_open(is, st_index[AVMEDIA_TYPE_VIDEO]);                                                     // 0.0
/*220 */     }                                                                                                                      // 0.0
/*222 */     if (is->show_mode == SHOW_MODE_NONE)                                                                                   // 0.0
/*224 */         is->show_mode = ret >= 0 ? SHOW_MODE_VIDEO : SHOW_MODE_RDFT;                                                       // 0.0
/*228 */     is->refresh_tid = SDL_CreateThread(refresh_thread, is);                                                                // 0.0
/*232 */     if (st_index[AVMEDIA_TYPE_SUBTITLE] >= 0) {                                                                            // 0.0
/*234 */         stream_component_open(is, st_index[AVMEDIA_TYPE_SUBTITLE]);                                                        // 0.0
/*236 */     }                                                                                                                      // 0.0
/*240 */     if (is->video_stream < 0 && is->audio_stream < 0) {                                                                    // 0.0
/*242 */         fprintf(stderr, "%s: could not open codecs\n", is->filename);                                                      // 0.0
/*244 */         ret = -1;                                                                                                          // 0.0
/*246 */         goto fail;                                                                                                         // 0.0
/*248 */     }                                                                                                                      // 0.0
/*252 */     if (infinite_buffer < 0 && is->realtime)                                                                               // 0.0
/*254 */         infinite_buffer = 1;                                                                                               // 0.0
/*258 */     for (;;) {                                                                                                             // 0.0
/*260 */         if (is->abort_request)                                                                                             // 0.0
/*262 */             break;                                                                                                         // 0.0
/*264 */         if (is->paused != is->last_paused) {                                                                               // 0.0
/*266 */             is->last_paused = is->paused;                                                                                  // 0.0
/*268 */             if (is->paused)                                                                                                // 0.0
/*270 */                 is->read_pause_return = av_read_pause(ic);                                                                 // 0.0
/*272 */             else                                                                                                           // 0.0
/*274 */                 av_read_play(ic);                                                                                          // 0.0
/*276 */         }                                                                                                                  // 0.0
/*278 */ #if CONFIG_RTSP_DEMUXER || CONFIG_MMSH_PROTOCOL                                                                            // 0.0
/*280 */         if (is->paused &&                                                                                                  // 0.0
/*282 */                 (!strcmp(ic->iformat->name, "rtsp") ||                                                                     // 0.0
/*284 */                  (ic->pb && !strncmp(input_filename, "mmsh:", 5)))) {                                                      // 0.0
/*286 */             /* wait 10 ms to avoid trying to get another packet */                                                         // 0.0
/*288 */             /* XXX: horrible */                                                                                            // 0.0
/*290 */             SDL_Delay(10);                                                                                                 // 0.0
/*292 */             continue;                                                                                                      // 0.0
/*294 */         }                                                                                                                  // 0.0
/*296 */ #endif                                                                                                                     // 0.0
/*298 */         if (is->seek_req) {                                                                                                // 0.0
/*300 */             int64_t seek_target = is->seek_pos;                                                                            // 0.0
/*302 */             int64_t seek_min    = is->seek_rel > 0 ? seek_target - is->seek_rel + 2: INT64_MIN;                            // 0.0
/*304 */             int64_t seek_max    = is->seek_rel < 0 ? seek_target - is->seek_rel - 2: INT64_MAX;                            // 0.0
/*306 */ // FIXME the +-2 is due to rounding being not done in the correct direction in generation                                  // 0.0
/*308 */ //      of the seek_pos/seek_rel variables                                                                                 // 0.0
/*312 */             ret = avformat_seek_file(is->ic, -1, seek_min, seek_target, seek_max, is->seek_flags);                         // 0.0
/*314 */             if (ret < 0) {                                                                                                 // 0.0
/*316 */                 fprintf(stderr, "%s: error while seeking\n", is->ic->filename);                                            // 0.0
/*318 */             } else {                                                                                                       // 0.0
/*320 */                 if (is->audio_stream >= 0) {                                                                               // 0.0
/*322 */                     packet_queue_flush(&is->audioq);                                                                       // 0.0
/*324 */                     packet_queue_put(&is->audioq, &flush_pkt);                                                             // 0.0
/*326 */                 }                                                                                                          // 0.0
/*328 */                 if (is->subtitle_stream >= 0) {                                                                            // 0.0
/*330 */                     packet_queue_flush(&is->subtitleq);                                                                    // 0.0
/*332 */                     packet_queue_put(&is->subtitleq, &flush_pkt);                                                          // 0.0
/*334 */                 }                                                                                                          // 0.0
/*336 */                 if (is->video_stream >= 0) {                                                                               // 0.0
/*338 */                     packet_queue_flush(&is->videoq);                                                                       // 0.0
/*340 */                     packet_queue_put(&is->videoq, &flush_pkt);                                                             // 0.0
/*342 */                 }                                                                                                          // 0.0
/*344 */                 if (is->seek_flags & AVSEEK_FLAG_BYTE) {                                                                   // 0.0
/*346 */                    //FIXME: use a cleaner way to signal obsolete external clock...                                         // 0.0
/*348 */                    update_external_clock_pts(is, (double)AV_NOPTS_VALUE);                                                  // 0.0
/*350 */                 } else {                                                                                                   // 0.0
/*352 */                    update_external_clock_pts(is, seek_target / (double)AV_TIME_BASE);                                      // 0.0
/*354 */                 }                                                                                                          // 0.0
/*356 */             }                                                                                                              // 0.0
/*358 */             is->seek_req = 0;                                                                                              // 0.0
/*360 */             eof = 0;                                                                                                       // 0.0
/*362 */             if (is->paused)                                                                                                // 0.0
/*364 */                 step_to_next_frame(is);                                                                                    // 0.0
/*366 */         }                                                                                                                  // 0.0
/*368 */         if (is->queue_attachments_req) {                                                                                   // 0.0
/*370 */             avformat_queue_attached_pictures(ic);                                                                          // 0.0
/*372 */             is->queue_attachments_req = 0;                                                                                 // 0.0
/*374 */         }                                                                                                                  // 0.0
/*378 */         /* if the queue are full, no need to read more */                                                                  // 0.0
/*380 */         if (infinite_buffer<1 &&                                                                                           // 0.0
/*382 */               (is->audioq.size + is->videoq.size + is->subtitleq.size > MAX_QUEUE_SIZE                                     // 0.0
/*384 */             || (   (is->audioq   .nb_packets > MIN_FRAMES || is->audio_stream < 0 || is->audioq.abort_request)             // 0.0
/*386 */                 && (is->videoq   .nb_packets > MIN_FRAMES || is->video_stream < 0 || is->videoq.abort_request)             // 0.0
/*388 */                 && (is->subtitleq.nb_packets > MIN_FRAMES || is->subtitle_stream < 0 || is->subtitleq.abort_request)))) {  // 0.0
/*390 */             /* wait 10 ms */                                                                                               // 0.0
/*392 */             SDL_LockMutex(wait_mutex);                                                                                     // 0.0
/*394 */             SDL_CondWaitTimeout(is->continue_read_thread, wait_mutex, 10);                                                 // 0.0
/*396 */             SDL_UnlockMutex(wait_mutex);                                                                                   // 0.0
/*398 */             continue;                                                                                                      // 0.0
/*400 */         }                                                                                                                  // 0.0
/*402 */         if (eof) {                                                                                                         // 0.0
/*404 */             if (is->video_stream >= 0) {                                                                                   // 0.0
/*406 */                 av_init_packet(pkt);                                                                                       // 0.0
/*408 */                 pkt->data = NULL;                                                                                          // 0.0
/*410 */                 pkt->size = 0;                                                                                             // 0.0
/*412 */                 pkt->stream_index = is->video_stream;                                                                      // 0.0
/*414 */                 packet_queue_put(&is->videoq, pkt);                                                                        // 0.0
/*416 */             }                                                                                                              // 0.0
/*418 */             if (is->audio_stream >= 0 &&                                                                                   // 0.0
/*420 */                 is->audio_st->codec->codec->capabilities & CODEC_CAP_DELAY) {                                              // 0.0
/*422 */                 av_init_packet(pkt);                                                                                       // 0.0
/*424 */                 pkt->data = NULL;                                                                                          // 0.0
/*426 */                 pkt->size = 0;                                                                                             // 0.0
/*428 */                 pkt->stream_index = is->audio_stream;                                                                      // 0.0
/*430 */                 packet_queue_put(&is->audioq, pkt);                                                                        // 0.0
/*432 */             }                                                                                                              // 0.0
/*434 */             SDL_Delay(10);                                                                                                 // 0.0
/*436 */             if (is->audioq.size + is->videoq.size + is->subtitleq.size == 0) {                                             // 0.0
/*438 */                 if (loop != 1 && (!loop || --loop)) {                                                                      // 0.0
/*440 */                     stream_seek(is, start_time != AV_NOPTS_VALUE ? start_time : 0, 0, 0);                                  // 0.0
/*442 */                 } else if (autoexit) {                                                                                     // 0.0
/*444 */                     ret = AVERROR_EOF;                                                                                     // 0.0
/*446 */                     goto fail;                                                                                             // 0.0
/*448 */                 }                                                                                                          // 0.0
/*450 */             }                                                                                                              // 0.0
/*452 */             eof=0;                                                                                                         // 0.0
/*454 */             continue;                                                                                                      // 0.0
/*456 */         }                                                                                                                  // 0.0
/*458 */         ret = av_read_frame(ic, pkt);                                                                                      // 0.0
/*460 */         if (ret < 0) {                                                                                                     // 0.0
/*462 */             if (ret == AVERROR_EOF || url_feof(ic->pb))                                                                    // 0.0
/*464 */                 eof = 1;                                                                                                   // 0.0
/*466 */             if (ic->pb && ic->pb->error)                                                                                   // 0.0
/*468 */                 break;                                                                                                     // 0.0
/*470 */             SDL_LockMutex(wait_mutex);                                                                                     // 0.0
/*472 */             SDL_CondWaitTimeout(is->continue_read_thread, wait_mutex, 10);                                                 // 0.0
/*474 */             SDL_UnlockMutex(wait_mutex);                                                                                   // 0.0
/*476 */             continue;                                                                                                      // 0.0
/*478 */         }                                                                                                                  // 0.0
/*480 */         /* check if packet is in play range specified by user, then queue, otherwise discard */                            // 0.0
/*482 */         pkt_in_play_range = duration == AV_NOPTS_VALUE ||                                                                  // 0.0
/*484 */                 (pkt->pts - ic->streams[pkt->stream_index]->start_time) *                                                  // 0.0
/*486 */                 av_q2d(ic->streams[pkt->stream_index]->time_base) -                                                        // 0.0
/*488 */                 (double)(start_time != AV_NOPTS_VALUE ? start_time : 0) / 1000000                                          // 0.0
/*490 */                 <= ((double)duration / 1000000);                                                                           // 0.0
/*492 */         if (pkt->stream_index == is->audio_stream && pkt_in_play_range) {                                                  // 0.0
/*494 */             packet_queue_put(&is->audioq, pkt);                                                                            // 0.0
/*496 */         } else if (pkt->stream_index == is->video_stream && pkt_in_play_range) {                                           // 0.0
/*498 */             packet_queue_put(&is->videoq, pkt);                                                                            // 0.0
/*500 */         } else if (pkt->stream_index == is->subtitle_stream && pkt_in_play_range) {                                        // 0.0
/*502 */             packet_queue_put(&is->subtitleq, pkt);                                                                         // 0.0
/*504 */         } else {                                                                                                           // 0.0
/*506 */             av_free_packet(pkt);                                                                                           // 0.0
/*508 */         }                                                                                                                  // 0.0
/*510 */     }                                                                                                                      // 0.0
/*512 */     /* wait until the end */                                                                                               // 0.0
/*514 */     while (!is->abort_request) {                                                                                           // 0.0
/*516 */         SDL_Delay(100);                                                                                                    // 0.0
/*518 */     }                                                                                                                      // 0.0
/*522 */     ret = 0;                                                                                                               // 0.0
/*524 */  fail:                                                                                                                     // 0.0
/*526 */     /* close each stream */                                                                                                // 0.0
/*528 */     if (is->audio_stream >= 0)                                                                                             // 0.0
/*530 */         stream_component_close(is, is->audio_stream);                                                                      // 0.0
/*532 */     if (is->video_stream >= 0)                                                                                             // 0.0
/*534 */         stream_component_close(is, is->video_stream);                                                                      // 0.0
/*536 */     if (is->subtitle_stream >= 0)                                                                                          // 0.0
/*538 */         stream_component_close(is, is->subtitle_stream);                                                                   // 0.0
/*540 */     if (is->ic) {                                                                                                          // 0.0
/*542 */         avformat_close_input(&is->ic);                                                                                     // 0.0
/*544 */     }                                                                                                                      // 0.0
/*548 */     if (ret != 0) {                                                                                                        // 0.0
/*550 */         SDL_Event event;                                                                                                   // 0.0
/*554 */         event.type = FF_QUIT_EVENT;                                                                                        // 0.0
/*556 */         event.user.data1 = is;                                                                                             // 0.0
/*558 */         SDL_PushEvent(&event);                                                                                             // 0.0
/*560 */     }                                                                                                                      // 0.0
/*562 */     SDL_DestroyMutex(wait_mutex);                                                                                          // 0.0
/*564 */     return 0;                                                                                                              // 0.0
/*566 */ }                                                                                                                          // 0.0
