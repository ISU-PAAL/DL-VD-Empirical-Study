// commit message FFmpeg@2c90316b46 (target=1, prob=0.389514, correct=False): hls: fix leaking avio_opts on hls_read_header error
/*0   */ static int hls_read_header(AVFormatContext *s)                                                          // (17) 0.0293
/*2   */ {                                                                                                       // (26) 0.001955
/*4   */     void *u = (s->flags & AVFMT_FLAG_CUSTOM_IO) ? NULL : s->pb;                                         // (0) 0.06054
/*6   */     HLSContext *c = s->priv_data;                                                                       // (18) 0.02929
/*8   */     int ret = 0, i;                                                                                     // (23) 0.01953
/*10  */     int highest_cur_seq_no = 0;                                                                         // (19) 0.02734
/*14  */     c->ctx                = s;                                                                          // (5) 0.04687
/*16  */     c->interrupt_callback = &s->interrupt_callback;                                                     // (15) 0.03515
/*18  */     c->strict_std_compliance = s->strict_std_compliance;                                                // (10) 0.04101
/*22  */     c->first_packet = 1;                                                                                // (20) 0.02344
/*24  */     c->first_timestamp = AV_NOPTS_VALUE;                                                                // (14) 0.03515
/*26  */     c->cur_timestamp = AV_NOPTS_VALUE;                                                                  // (13) 0.03515
/*30  */     if (u) {                                                                                            // (24) 0.01563
/*32  */         // get the previous user agent & set back to null if string size is zero                        // (6) 0.04494
/*34  */         update_options(&c->user_agent, "user-agent", u);                                                // (3) 0.04687
/*38  */         // get the previous cookies & set back to null if string size is zero                           // (9) 0.04297
/*40  */         update_options(&c->cookies, "cookies", u);                                                      // (8) 0.04297
/*44  */         // get the previous headers & set back to null if string size is zero                           // (7) 0.04298
/*46  */         update_options(&c->headers, "headers", u);                                                      // (11) 0.03906
/*50  */         // get the previous http proxt & set back to null if string size is zero                        // (2) 0.04687
/*52  */         update_options(&c->http_proxy, "http_proxy", u);                                                // (4) 0.04687
/*54  */     }                                                                                                   // (25) 0.007812
/*58  */     if ((ret = parse_playlist(c, s->filename, NULL, s->pb)) < 0)                                        // (1) 0.05273
/*60  */         goto fail;                                                                                      // (22) 0.01953
/*64  */     if ((ret = save_avio_options(s)) < 0)                                                               // (12) 0.03711
/*66  */         goto fail;                                                                                      // (21) 0.01954
/*70  */     /* Some HLS servers don't like being sent the range header */                                       // (16) 0.0332
/*72  */     av_dict_set(&c->avio_opts, "seekable", "0", 0);                                                     // 0.0
/*76  */     if (c->n_variants == 0) {                                                                           // 0.0
/*78  */         av_log(NULL, AV_LOG_WARNING, "Empty playlist\n");                                               // 0.0
/*80  */         ret = AVERROR_EOF;                                                                              // 0.0
/*82  */         goto fail;                                                                                      // 0.0
/*84  */     }                                                                                                   // 0.0
/*86  */     /* If the playlist only contained playlists (Master Playlist),                                      // 0.0
/*88  */      * parse each individual playlist. */                                                               // 0.0
/*90  */     if (c->n_playlists > 1 || c->playlists[0]->n_segments == 0) {                                       // 0.0
/*92  */         for (i = 0; i < c->n_playlists; i++) {                                                          // 0.0
/*94  */             struct playlist *pls = c->playlists[i];                                                     // 0.0
/*96  */             if ((ret = parse_playlist(c, pls->url, pls, NULL)) < 0)                                     // 0.0
/*98  */                 goto fail;                                                                              // 0.0
/*100 */         }                                                                                               // 0.0
/*102 */     }                                                                                                   // 0.0
/*106 */     if (c->variants[0]->playlists[0]->n_segments == 0) {                                                // 0.0
/*108 */         av_log(NULL, AV_LOG_WARNING, "Empty playlist\n");                                               // 0.0
/*110 */         ret = AVERROR_EOF;                                                                              // 0.0
/*112 */         goto fail;                                                                                      // 0.0
/*114 */     }                                                                                                   // 0.0
/*118 */     /* If this isn't a live stream, calculate the total duration of the                                 // 0.0
/*120 */      * stream. */                                                                                       // 0.0
/*122 */     if (c->variants[0]->playlists[0]->finished) {                                                       // 0.0
/*124 */         int64_t duration = 0;                                                                           // 0.0
/*126 */         for (i = 0; i < c->variants[0]->playlists[0]->n_segments; i++)                                  // 0.0
/*128 */             duration += c->variants[0]->playlists[0]->segments[i]->duration;                            // 0.0
/*130 */         s->duration = duration;                                                                         // 0.0
/*132 */     }                                                                                                   // 0.0
/*136 */     /* Associate renditions with variants */                                                            // 0.0
/*138 */     for (i = 0; i < c->n_variants; i++) {                                                               // 0.0
/*140 */         struct variant *var = c->variants[i];                                                           // 0.0
/*144 */         if (var->audio_group[0])                                                                        // 0.0
/*146 */             add_renditions_to_variant(c, var, AVMEDIA_TYPE_AUDIO, var->audio_group);                    // 0.0
/*148 */         if (var->video_group[0])                                                                        // 0.0
/*150 */             add_renditions_to_variant(c, var, AVMEDIA_TYPE_VIDEO, var->video_group);                    // 0.0
/*152 */         if (var->subtitles_group[0])                                                                    // 0.0
/*154 */             add_renditions_to_variant(c, var, AVMEDIA_TYPE_SUBTITLE, var->subtitles_group);             // 0.0
/*156 */     }                                                                                                   // 0.0
/*160 */     /* Create a program for each variant */                                                             // 0.0
/*162 */     for (i = 0; i < c->n_variants; i++) {                                                               // 0.0
/*164 */         struct variant *v = c->variants[i];                                                             // 0.0
/*166 */         AVProgram *program;                                                                             // 0.0
/*170 */         program = av_new_program(s, i);                                                                 // 0.0
/*172 */         if (!program)                                                                                   // 0.0
/*174 */             goto fail;                                                                                  // 0.0
/*176 */         av_dict_set_int(&program->metadata, "variant_bitrate", v->bandwidth, 0);                        // 0.0
/*178 */     }                                                                                                   // 0.0
/*182 */     /* Select the starting segments */                                                                  // 0.0
/*184 */     for (i = 0; i < c->n_playlists; i++) {                                                              // 0.0
/*186 */         struct playlist *pls = c->playlists[i];                                                         // 0.0
/*190 */         if (pls->n_segments == 0)                                                                       // 0.0
/*192 */             continue;                                                                                   // 0.0
/*196 */         pls->cur_seq_no = select_cur_seq_no(c, pls);                                                    // 0.0
/*198 */         highest_cur_seq_no = FFMAX(highest_cur_seq_no, pls->cur_seq_no);                                // 0.0
/*200 */     }                                                                                                   // 0.0
/*204 */     /* Open the demuxer for each playlist */                                                            // 0.0
/*206 */     for (i = 0; i < c->n_playlists; i++) {                                                              // 0.0
/*208 */         struct playlist *pls = c->playlists[i];                                                         // 0.0
/*210 */         AVInputFormat *in_fmt = NULL;                                                                   // 0.0
/*214 */         if (!(pls->ctx = avformat_alloc_context())) {                                                   // 0.0
/*216 */             ret = AVERROR(ENOMEM);                                                                      // 0.0
/*218 */             goto fail;                                                                                  // 0.0
/*220 */         }                                                                                               // 0.0
/*224 */         if (pls->n_segments == 0)                                                                       // 0.0
/*226 */             continue;                                                                                   // 0.0
/*230 */         pls->index  = i;                                                                                // 0.0
/*232 */         pls->needed = 1;                                                                                // 0.0
/*234 */         pls->parent = s;                                                                                // 0.0
/*238 */         /*                                                                                              // 0.0
/*240 */          * If this is a live stream and this playlist looks like it is one segment                      // 0.0
/*242 */          * behind, try to sync it up so that every substream starts at the same                         // 0.0
/*244 */          * time position (so e.g. avformat_find_stream_info() will see packets from                     // 0.0
/*246 */          * all active streams within the first few seconds). This is not very generic,                  // 0.0
/*248 */          * though, as the sequence numbers are technically independent.                                 // 0.0
/*250 */          */                                                                                             // 0.0
/*252 */         if (!pls->finished && pls->cur_seq_no == highest_cur_seq_no - 1 &&                              // 0.0
/*254 */             highest_cur_seq_no < pls->start_seq_no + pls->n_segments) {                                 // 0.0
/*256 */             pls->cur_seq_no = highest_cur_seq_no;                                                       // 0.0
/*258 */         }                                                                                               // 0.0
/*262 */         pls->read_buffer = av_malloc(INITIAL_BUFFER_SIZE);                                              // 0.0
/*264 */         if (!pls->read_buffer){                                                                         // 0.0
/*266 */             ret = AVERROR(ENOMEM);                                                                      // 0.0
/*268 */             avformat_free_context(pls->ctx);                                                            // 0.0
/*270 */             pls->ctx = NULL;                                                                            // 0.0
/*272 */             goto fail;                                                                                  // 0.0
/*274 */         }                                                                                               // 0.0
/*276 */         ffio_init_context(&pls->pb, pls->read_buffer, INITIAL_BUFFER_SIZE, 0, pls,                      // 0.0
/*278 */                           read_data, NULL, NULL);                                                       // 0.0
/*280 */         pls->pb.seekable = 0;                                                                           // 0.0
/*282 */         ret = av_probe_input_buffer(&pls->pb, &in_fmt, pls->segments[0]->url,                           // 0.0
/*284 */                                     NULL, 0, 0);                                                        // 0.0
/*286 */         if (ret < 0) {                                                                                  // 0.0
/*288 */             /* Free the ctx - it isn't initialized properly at this point,                              // 0.0
/*290 */              * so avformat_close_input shouldn't be called. If                                          // 0.0
/*292 */              * avformat_open_input fails below, it frees and zeros the                                  // 0.0
/*294 */              * context, so it doesn't need any special treatment like this. */                          // 0.0
/*296 */             av_log(s, AV_LOG_ERROR, "Error when loading first segment '%s'\n", pls->segments[0]->url);  // 0.0
/*298 */             avformat_free_context(pls->ctx);                                                            // 0.0
/*300 */             pls->ctx = NULL;                                                                            // 0.0
/*302 */             goto fail;                                                                                  // 0.0
/*304 */         }                                                                                               // 0.0
/*306 */         pls->ctx->pb       = &pls->pb;                                                                  // 0.0
/*308 */         pls->ctx->io_open  = nested_io_open;                                                            // 0.0
/*312 */         if ((ret = ff_copy_whiteblacklists(pls->ctx, s)) < 0)                                           // 0.0
/*314 */             goto fail;                                                                                  // 0.0
/*318 */         ret = avformat_open_input(&pls->ctx, pls->segments[0]->url, in_fmt, NULL);                      // 0.0
/*320 */         if (ret < 0)                                                                                    // 0.0
/*322 */             goto fail;                                                                                  // 0.0
/*326 */         if (pls->id3_deferred_extra && pls->ctx->nb_streams == 1) {                                     // 0.0
/*328 */             ff_id3v2_parse_apic(pls->ctx, &pls->id3_deferred_extra);                                    // 0.0
/*330 */             avformat_queue_attached_pictures(pls->ctx);                                                 // 0.0
/*332 */             ff_id3v2_free_extra_meta(&pls->id3_deferred_extra);                                         // 0.0
/*334 */             pls->id3_deferred_extra = NULL;                                                             // 0.0
/*336 */         }                                                                                               // 0.0
/*340 */         if (pls->is_id3_timestamped == -1)                                                              // 0.0
/*342 */             av_log(s, AV_LOG_WARNING, "No expected HTTP requests have been made\n");                    // 0.0
/*346 */         /*                                                                                              // 0.0
/*348 */          * For ID3 timestamped raw audio streams we need to detect the packet                           // 0.0
/*350 */          * durations to calculate timestamps in fill_timing_for_id3_timestamped_stream(),               // 0.0
/*352 */          * but for other streams we can rely on our user calling avformat_find_stream_info()            // 0.0
/*354 */          * on us if they want to.                                                                       // 0.0
/*356 */          */                                                                                             // 0.0
/*358 */         if (pls->is_id3_timestamped) {                                                                  // 0.0
/*360 */             ret = avformat_find_stream_info(pls->ctx, NULL);                                            // 0.0
/*362 */             if (ret < 0)                                                                                // 0.0
/*364 */                 goto fail;                                                                              // 0.0
/*366 */         }                                                                                               // 0.0
/*370 */         pls->has_noheader_flag = !!(pls->ctx->ctx_flags & AVFMTCTX_NOHEADER);                           // 0.0
/*374 */         /* Create new AVStreams for each stream in this playlist */                                     // 0.0
/*376 */         ret = update_streams_from_subdemuxer(s, pls);                                                   // 0.0
/*378 */         if (ret < 0)                                                                                    // 0.0
/*380 */             goto fail;                                                                                  // 0.0
/*384 */         add_metadata_from_renditions(s, pls, AVMEDIA_TYPE_AUDIO);                                       // 0.0
/*386 */         add_metadata_from_renditions(s, pls, AVMEDIA_TYPE_VIDEO);                                       // 0.0
/*388 */         add_metadata_from_renditions(s, pls, AVMEDIA_TYPE_SUBTITLE);                                    // 0.0
/*390 */     }                                                                                                   // 0.0
/*394 */     update_noheader_flag(s);                                                                            // 0.0
/*398 */     return 0;                                                                                           // 0.0
/*400 */ fail:                                                                                                   // 0.0
/*402 */     free_playlist_list(c);                                                                              // 0.0
/*404 */     free_variant_list(c);                                                                               // 0.0
/*406 */     free_rendition_list(c);                                                                             // 0.0
/*408 */     return ret;                                                                                         // 0.0
/*410 */ }                                                                                                       // 0.0
