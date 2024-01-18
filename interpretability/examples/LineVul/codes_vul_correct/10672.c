// commit message FFmpeg@64f7db554e (target=1, prob=0.54553175, correct=True): mpegencts: Fix overflow in cbr mode period calculations
/*0   */ static int mpegts_write_header(AVFormatContext *s)                                                         // (10) 0.03125
/*2   */ {                                                                                                          // (27) 0.001953
/*4   */     MpegTSWrite *ts = s->priv_data;                                                                        // (12) 0.03125
/*6   */     MpegTSWriteStream *ts_st;                                                                              // (17) 0.02539
/*8   */     MpegTSService *service;                                                                                // (20) 0.01953
/*10  */     AVStream *st, *pcr_st = NULL;                                                                          // (11) 0.03125
/*12  */     AVDictionaryEntry *title, *provider;                                                                   // (15) 0.02734
/*14  */     int i, j;                                                                                              // (23) 0.01562
/*16  */     const char *service_name;                                                                              // (21) 0.01953
/*18  */     const char *provider_name;                                                                             // (18) 0.02148
/*20  */     int *pids;                                                                                             // (22) 0.01563
/*22  */     int ret;                                                                                               // (26) 0.01172
/*26  */     if (s->max_delay < 0) /* Not set by the caller */                                                      // (8) 0.03906
/*28  */         s->max_delay = 0;                                                                                  // (14) 0.0293
/*32  */     // round up to a whole number of TS packets                                                            // (16) 0.02539
/*34  */     ts->pes_payload_size = (ts->pes_payload_size + 14 + 183) / 184 * 184 - 14;                             // (1) 0.06445
/*38  */     ts->tsid = ts->transport_stream_id;                                                                    // (9) 0.0332
/*40  */     ts->onid = ts->original_network_id;                                                                    // (13) 0.03125
/*42  */     /* allocate a single DVB service */                                                                    // (19) 0.02148
/*44  */     title = av_dict_get(s->metadata, "service_name", NULL, 0);                                             // (5) 0.04687
/*46  */     if (!title)                                                                                            // (25) 0.01367
/*48  */         title = av_dict_get(s->metadata, "title", NULL, 0);                                                // (4) 0.05078
/*50  */     service_name  = title ? title->value : DEFAULT_SERVICE_NAME;                                           // (6) 0.04297
/*52  */     provider      = av_dict_get(s->metadata, "service_provider", NULL, 0);                                 // (2) 0.05859
/*54  */     provider_name = provider ? provider->value : DEFAULT_PROVIDER_NAME;                                    // (7) 0.04101
/*56  */     service       = mpegts_add_service(ts, ts->service_id,                                                 // (3) 0.05273
/*58  */                                        provider_name, service_name);                                       // (0) 0.08984
/*62  */     if (!service)                                                                                          // (24) 0.01367
/*64  */         return AVERROR(ENOMEM);                                                                            // 0.0
/*68  */     service->pmt.write_packet = section_write_packet;                                                      // 0.0
/*70  */     service->pmt.opaque       = s;                                                                         // 0.0
/*72  */     service->pmt.cc           = 15;                                                                        // 0.0
/*76  */     ts->pat.pid          = PAT_PID;                                                                        // 0.0
/*78  */     /* Initialize at 15 so that it wraps and is equal to 0 for the                                         // 0.0
/*80  */      * first packet we write. */                                                                           // 0.0
/*82  */     ts->pat.cc           = 15;                                                                             // 0.0
/*84  */     ts->pat.write_packet = section_write_packet;                                                           // 0.0
/*86  */     ts->pat.opaque       = s;                                                                              // 0.0
/*90  */     ts->sdt.pid          = SDT_PID;                                                                        // 0.0
/*92  */     ts->sdt.cc           = 15;                                                                             // 0.0
/*94  */     ts->sdt.write_packet = section_write_packet;                                                           // 0.0
/*96  */     ts->sdt.opaque       = s;                                                                              // 0.0
/*100 */     pids = av_malloc_array(s->nb_streams, sizeof(*pids));                                                  // 0.0
/*102 */     if (!pids) {                                                                                           // 0.0
/*104 */         ret = AVERROR(ENOMEM);                                                                             // 0.0
/*106 */         goto fail;                                                                                         // 0.0
/*108 */     }                                                                                                      // 0.0
/*112 */     /* assign pids to each stream */                                                                       // 0.0
/*114 */     for (i = 0; i < s->nb_streams; i++) {                                                                  // 0.0
/*116 */         st = s->streams[i];                                                                                // 0.0
/*120 */         ts_st = av_mallocz(sizeof(MpegTSWriteStream));                                                     // 0.0
/*122 */         if (!ts_st) {                                                                                      // 0.0
/*124 */             ret = AVERROR(ENOMEM);                                                                         // 0.0
/*126 */             goto fail;                                                                                     // 0.0
/*128 */         }                                                                                                  // 0.0
/*130 */         st->priv_data = ts_st;                                                                             // 0.0
/*134 */         ts_st->user_tb = st->time_base;                                                                    // 0.0
/*136 */         avpriv_set_pts_info(st, 33, 1, 90000);                                                             // 0.0
/*140 */         ts_st->payload = av_mallocz(ts->pes_payload_size);                                                 // 0.0
/*142 */         if (!ts_st->payload) {                                                                             // 0.0
/*144 */             ret = AVERROR(ENOMEM);                                                                         // 0.0
/*146 */             goto fail;                                                                                     // 0.0
/*148 */         }                                                                                                  // 0.0
/*150 */         ts_st->service = service;                                                                          // 0.0
/*152 */         /* MPEG pid values < 16 are reserved. Applications which set st->id in                             // 0.0
/*154 */          * this range are assigned a calculated pid. */                                                    // 0.0
/*156 */         if (st->id < 16) {                                                                                 // 0.0
/*158 */             ts_st->pid = ts->start_pid + i;                                                                // 0.0
/*160 */         } else if (st->id < 0x1FFF) {                                                                      // 0.0
/*162 */             ts_st->pid = st->id;                                                                           // 0.0
/*164 */         } else {                                                                                           // 0.0
/*166 */             av_log(s, AV_LOG_ERROR,                                                                        // 0.0
/*168 */                    "Invalid stream id %d, must be less than 8191\n", st->id);                              // 0.0
/*170 */             ret = AVERROR(EINVAL);                                                                         // 0.0
/*172 */             goto fail;                                                                                     // 0.0
/*174 */         }                                                                                                  // 0.0
/*176 */         if (ts_st->pid == service->pmt.pid) {                                                              // 0.0
/*178 */             av_log(s, AV_LOG_ERROR, "Duplicate stream id %d\n", ts_st->pid);                               // 0.0
/*180 */             ret = AVERROR(EINVAL);                                                                         // 0.0
/*182 */             goto fail;                                                                                     // 0.0
/*184 */         }                                                                                                  // 0.0
/*186 */         for (j = 0; j < i; j++) {                                                                          // 0.0
/*188 */             if (pids[j] == ts_st->pid) {                                                                   // 0.0
/*190 */                 av_log(s, AV_LOG_ERROR, "Duplicate stream id %d\n", ts_st->pid);                           // 0.0
/*192 */                 ret = AVERROR(EINVAL);                                                                     // 0.0
/*194 */                 goto fail;                                                                                 // 0.0
/*196 */             }                                                                                              // 0.0
/*198 */         }                                                                                                  // 0.0
/*200 */         pids[i]                = ts_st->pid;                                                               // 0.0
/*202 */         ts_st->payload_pts     = AV_NOPTS_VALUE;                                                           // 0.0
/*204 */         ts_st->payload_dts     = AV_NOPTS_VALUE;                                                           // 0.0
/*206 */         ts_st->first_pts_check = 1;                                                                        // 0.0
/*208 */         ts_st->cc              = 15;                                                                       // 0.0
/*210 */         /* update PCR pid by using the first video stream */                                               // 0.0
/*212 */         if (st->codec->codec_type == AVMEDIA_TYPE_VIDEO &&                                                 // 0.0
/*214 */             service->pcr_pid == 0x1fff) {                                                                  // 0.0
/*216 */             service->pcr_pid = ts_st->pid;                                                                 // 0.0
/*218 */             pcr_st           = st;                                                                         // 0.0
/*220 */         }                                                                                                  // 0.0
/*222 */         if (st->codec->codec_id == AV_CODEC_ID_AAC &&                                                      // 0.0
/*224 */             st->codec->extradata_size > 0) {                                                               // 0.0
/*226 */             AVStream *ast;                                                                                 // 0.0
/*228 */             ts_st->amux = avformat_alloc_context();                                                        // 0.0
/*230 */             if (!ts_st->amux) {                                                                            // 0.0
/*232 */                 ret = AVERROR(ENOMEM);                                                                     // 0.0
/*234 */                 goto fail;                                                                                 // 0.0
/*236 */             }                                                                                              // 0.0
/*238 */             ts_st->amux->oformat =                                                                         // 0.0
/*240 */                 av_guess_format((ts->flags & MPEGTS_FLAG_AAC_LATM) ? "latm" : "adts",                      // 0.0
/*242 */                                 NULL, NULL);                                                               // 0.0
/*244 */             if (!ts_st->amux->oformat) {                                                                   // 0.0
/*246 */                 ret = AVERROR(EINVAL);                                                                     // 0.0
/*248 */                 goto fail;                                                                                 // 0.0
/*250 */             }                                                                                              // 0.0
/*252 */             if (!(ast = avformat_new_stream(ts_st->amux, NULL))) {                                         // 0.0
/*254 */                 ret = AVERROR(ENOMEM);                                                                     // 0.0
/*256 */                 goto fail;                                                                                 // 0.0
/*258 */             }                                                                                              // 0.0
/*260 */             ret = avcodec_copy_context(ast->codec, st->codec);                                             // 0.0
/*262 */             if (ret != 0)                                                                                  // 0.0
/*264 */                 goto fail;                                                                                 // 0.0
/*266 */             ast->time_base = st->time_base;                                                                // 0.0
/*268 */             ret = avformat_write_header(ts_st->amux, NULL);                                                // 0.0
/*270 */             if (ret < 0)                                                                                   // 0.0
/*272 */                 goto fail;                                                                                 // 0.0
/*274 */         }                                                                                                  // 0.0
/*276 */         if (st->codec->codec_id == AV_CODEC_ID_OPUS) {                                                     // 0.0
/*278 */             ts_st->opus_pending_trim_start = st->codec->initial_padding * 48000 / st->codec->sample_rate;  // 0.0
/*280 */         }                                                                                                  // 0.0
/*282 */     }                                                                                                      // 0.0
/*286 */     av_freep(&pids);                                                                                       // 0.0
/*290 */     /* if no video stream, use the first stream as PCR */                                                  // 0.0
/*292 */     if (service->pcr_pid == 0x1fff && s->nb_streams > 0) {                                                 // 0.0
/*294 */         pcr_st           = s->streams[0];                                                                  // 0.0
/*296 */         ts_st            = pcr_st->priv_data;                                                              // 0.0
/*298 */         service->pcr_pid = ts_st->pid;                                                                     // 0.0
/*300 */     } else                                                                                                 // 0.0
/*302 */         ts_st = pcr_st->priv_data;                                                                         // 0.0
/*306 */     if (ts->mux_rate > 1) {                                                                                // 0.0
/*308 */         service->pcr_packet_period = (ts->mux_rate * ts->pcr_period) /                                     // 0.0
/*310 */                                      (TS_PACKET_SIZE * 8 * 1000);                                          // 0.0
/*312 */         ts->sdt_packet_period      = (ts->mux_rate * SDT_RETRANS_TIME) /                                   // 0.0
/*314 */                                      (TS_PACKET_SIZE * 8 * 1000);                                          // 0.0
/*316 */         ts->pat_packet_period      = (ts->mux_rate * PAT_RETRANS_TIME) /                                   // 0.0
/*318 */                                      (TS_PACKET_SIZE * 8 * 1000);                                          // 0.0
/*322 */         if (ts->copyts < 1)                                                                                // 0.0
/*324 */             ts->first_pcr = av_rescale(s->max_delay, PCR_TIME_BASE, AV_TIME_BASE);                         // 0.0
/*326 */     } else {                                                                                               // 0.0
/*328 */         /* Arbitrary values, PAT/PMT will also be written on video key frames */                           // 0.0
/*330 */         ts->sdt_packet_period = 200;                                                                       // 0.0
/*332 */         ts->pat_packet_period = 40;                                                                        // 0.0
/*334 */         if (pcr_st->codec->codec_type == AVMEDIA_TYPE_AUDIO) {                                             // 0.0
/*336 */             if (!pcr_st->codec->frame_size) {                                                              // 0.0
/*338 */                 av_log(s, AV_LOG_WARNING, "frame size not set\n");                                         // 0.0
/*340 */                 service->pcr_packet_period =                                                               // 0.0
/*342 */                     pcr_st->codec->sample_rate / (10 * 512);                                               // 0.0
/*344 */             } else {                                                                                       // 0.0
/*346 */                 service->pcr_packet_period =                                                               // 0.0
/*348 */                     pcr_st->codec->sample_rate / (10 * pcr_st->codec->frame_size);                         // 0.0
/*350 */             }                                                                                              // 0.0
/*352 */         } else {                                                                                           // 0.0
/*354 */             // max delta PCR 0.1s                                                                          // 0.0
/*356 */             // TODO: should be avg_frame_rate                                                              // 0.0
/*358 */             service->pcr_packet_period =                                                                   // 0.0
/*360 */                 ts_st->user_tb.den / (10 * ts_st->user_tb.num);                                            // 0.0
/*362 */         }                                                                                                  // 0.0
/*364 */         if (!service->pcr_packet_period)                                                                   // 0.0
/*366 */             service->pcr_packet_period = 1;                                                                // 0.0
/*368 */     }                                                                                                      // 0.0
/*372 */     ts->last_pat_ts = AV_NOPTS_VALUE;                                                                      // 0.0
/*374 */     ts->last_sdt_ts = AV_NOPTS_VALUE;                                                                      // 0.0
/*376 */     // The user specified a period, use only it                                                            // 0.0
/*378 */     if (ts->pat_period < INT_MAX/2) {                                                                      // 0.0
/*380 */         ts->pat_packet_period = INT_MAX;                                                                   // 0.0
/*382 */     }                                                                                                      // 0.0
/*384 */     if (ts->sdt_period < INT_MAX/2) {                                                                      // 0.0
/*386 */         ts->sdt_packet_period = INT_MAX;                                                                   // 0.0
/*388 */     }                                                                                                      // 0.0
/*392 */     // output a PCR as soon as possible                                                                    // 0.0
/*394 */     service->pcr_packet_count = service->pcr_packet_period;                                                // 0.0
/*396 */     ts->pat_packet_count      = ts->pat_packet_period - 1;                                                 // 0.0
/*398 */     ts->sdt_packet_count      = ts->sdt_packet_period - 1;                                                 // 0.0
/*402 */     if (ts->mux_rate == 1)                                                                                 // 0.0
/*404 */         av_log(s, AV_LOG_VERBOSE, "muxrate VBR, ");                                                        // 0.0
/*406 */     else                                                                                                   // 0.0
/*408 */         av_log(s, AV_LOG_VERBOSE, "muxrate %d, ", ts->mux_rate);                                           // 0.0
/*410 */     av_log(s, AV_LOG_VERBOSE,                                                                              // 0.0
/*412 */            "pcr every %d pkts, sdt every %d, pat/pmt every %d pkts\n",                                     // 0.0
/*414 */            service->pcr_packet_period,                                                                     // 0.0
/*416 */            ts->sdt_packet_period, ts->pat_packet_period);                                                  // 0.0
/*420 */     if (ts->m2ts_mode == -1) {                                                                             // 0.0
/*422 */         if (av_match_ext(s->filename, "m2ts")) {                                                           // 0.0
/*424 */             ts->m2ts_mode = 1;                                                                             // 0.0
/*426 */         } else {                                                                                           // 0.0
/*428 */             ts->m2ts_mode = 0;                                                                             // 0.0
/*430 */         }                                                                                                  // 0.0
/*432 */     }                                                                                                      // 0.0
/*436 */     return 0;                                                                                              // 0.0
/*440 */ fail:                                                                                                      // 0.0
/*442 */     av_freep(&pids);                                                                                       // 0.0
/*444 */     for (i = 0; i < s->nb_streams; i++) {                                                                  // 0.0
/*446 */         st    = s->streams[i];                                                                             // 0.0
/*448 */         ts_st = st->priv_data;                                                                             // 0.0
/*450 */         if (ts_st) {                                                                                       // 0.0
/*452 */             av_freep(&ts_st->payload);                                                                     // 0.0
/*454 */             if (ts_st->amux) {                                                                             // 0.0
/*456 */                 avformat_free_context(ts_st->amux);                                                        // 0.0
/*458 */                 ts_st->amux = NULL;                                                                        // 0.0
/*460 */             }                                                                                              // 0.0
/*462 */         }                                                                                                  // 0.0
/*464 */         av_freep(&st->priv_data);                                                                          // 0.0
/*466 */     }                                                                                                      // 0.0
/*470 */     for (i = 0; i < ts->nb_services; i++) {                                                                // 0.0
/*472 */         service = ts->services[i];                                                                         // 0.0
/*474 */         av_freep(&service->provider_name);                                                                 // 0.0
/*476 */         av_freep(&service->name);                                                                          // 0.0
/*478 */         av_freep(&service);                                                                                // 0.0
/*480 */     }                                                                                                      // 0.0
/*482 */     av_freep(&ts->services);                                                                               // 0.0
/*484 */     return ret;                                                                                            // 0.0
/*486 */ }                                                                                                          // 0.0
