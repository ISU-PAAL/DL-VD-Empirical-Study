// commit message FFmpeg@25bcf24d4d (target=0, prob=0.5557006, correct=False): ffmpeg_opt: check that a subtitle encoder is available before auto mapping streams
/*0   */ static int open_output_file(OptionsContext *o, const char *filename)                                                                                    // (10) 0.03516
/*2   */ {                                                                                                                                                       // (27) 0.001953
/*4   */     AVFormatContext *oc;                                                                                                                                // (20) 0.01758
/*6   */     int i, j, err;                                                                                                                                      // (17) 0.01953
/*8   */     AVOutputFormat *file_oformat;                                                                                                                       // (16) 0.02344
/*10  */     OutputFile *of;                                                                                                                                     // (22) 0.01562
/*12  */     OutputStream *ost;                                                                                                                                  // (21) 0.01563
/*14  */     InputStream  *ist;                                                                                                                                  // (19) 0.01758
/*16  */     AVDictionary *unused_opts = NULL;                                                                                                                   // (13) 0.0293
/*18  */     AVDictionaryEntry *e = NULL;                                                                                                                        // (15) 0.02344
/*22  */     if (configure_complex_filters() < 0) {                                                                                                              // (12) 0.0332
/*24  */         av_log(NULL, AV_LOG_FATAL, "Error configuring filters.\n");                                                                                     // (3) 0.05859
/*26  */         exit_program(1);                                                                                                                                // (14) 0.02539
/*28  */     }                                                                                                                                                   // (26) 0.007812
/*32  */     if (o->stop_time != INT64_MAX && o->recording_time != INT64_MAX) {                                                                                  // (5) 0.05664
/*34  */         o->stop_time = INT64_MAX;                                                                                                                       // (11) 0.03516
/*36  */         av_log(NULL, AV_LOG_WARNING, "-t and -to cannot be used together; using -t.\n");                                                                // (2) 0.07031
/*38  */     }                                                                                                                                                   // (25) 0.007812
/*42  */     if (o->stop_time != INT64_MAX && o->recording_time == INT64_MAX) {                                                                                  // (4) 0.05664
/*44  */         int64_t start_time = o->start_time == AV_NOPTS_VALUE ? 0 : o->start_time;                                                                       // (1) 0.07227
/*46  */         if (o->stop_time <= start_time) {                                                                                                               // (9) 0.03906
/*48  */             av_log(NULL, AV_LOG_WARNING, "-to value smaller than -ss; ignoring -to.\n");                                                                // (0) 0.07422
/*50  */             o->stop_time = INT64_MAX;                                                                                                                   // (7) 0.04297
/*52  */         } else {                                                                                                                                        // (18) 0.01953
/*54  */             o->recording_time = o->stop_time - start_time;                                                                                              // (6) 0.05469
/*56  */         }                                                                                                                                               // (23) 0.01562
/*58  */     }                                                                                                                                                   // (24) 0.007812
/*62  */     GROW_ARRAY(output_files, nb_output_files);                                                                                                          // (8) 0.03906
/*64  */     of = av_mallocz(sizeof(*of));                                                                                                                       // 0.0
/*66  */     if (!of)                                                                                                                                            // 0.0
/*68  */         exit_program(1);                                                                                                                                // 0.0
/*70  */     output_files[nb_output_files - 1] = of;                                                                                                             // 0.0
/*74  */     of->ost_index      = nb_output_streams;                                                                                                             // 0.0
/*76  */     of->recording_time = o->recording_time;                                                                                                             // 0.0
/*78  */     of->start_time     = o->start_time;                                                                                                                 // 0.0
/*80  */     of->limit_filesize = o->limit_filesize;                                                                                                             // 0.0
/*82  */     of->shortest       = o->shortest;                                                                                                                   // 0.0
/*84  */     av_dict_copy(&of->opts, o->g->format_opts, 0);                                                                                                      // 0.0
/*88  */     if (!strcmp(filename, "-"))                                                                                                                         // 0.0
/*90  */         filename = "pipe:";                                                                                                                             // 0.0
/*94  */     err = avformat_alloc_output_context2(&oc, NULL, o->format, filename);                                                                               // 0.0
/*96  */     if (!oc) {                                                                                                                                          // 0.0
/*98  */         print_error(filename, err);                                                                                                                     // 0.0
/*100 */         exit_program(1);                                                                                                                                // 0.0
/*102 */     }                                                                                                                                                   // 0.0
/*106 */     of->ctx = oc;                                                                                                                                       // 0.0
/*108 */     if (o->recording_time != INT64_MAX)                                                                                                                 // 0.0
/*110 */         oc->duration = o->recording_time;                                                                                                               // 0.0
/*114 */     file_oformat= oc->oformat;                                                                                                                          // 0.0
/*116 */     oc->interrupt_callback = int_cb;                                                                                                                    // 0.0
/*120 */     /* create streams for all unlabeled output pads */                                                                                                  // 0.0
/*122 */     for (i = 0; i < nb_filtergraphs; i++) {                                                                                                             // 0.0
/*124 */         FilterGraph *fg = filtergraphs[i];                                                                                                              // 0.0
/*126 */         for (j = 0; j < fg->nb_outputs; j++) {                                                                                                          // 0.0
/*128 */             OutputFilter *ofilter = fg->outputs[j];                                                                                                     // 0.0
/*132 */             if (!ofilter->out_tmp || ofilter->out_tmp->name)                                                                                            // 0.0
/*134 */                 continue;                                                                                                                               // 0.0
/*138 */             switch (avfilter_pad_get_type(ofilter->out_tmp->filter_ctx->output_pads,                                                                    // 0.0
/*140 */                                           ofilter->out_tmp->pad_idx)) {                                                                                 // 0.0
/*142 */             case AVMEDIA_TYPE_VIDEO:    o->video_disable    = 1; break;                                                                                 // 0.0
/*144 */             case AVMEDIA_TYPE_AUDIO:    o->audio_disable    = 1; break;                                                                                 // 0.0
/*146 */             case AVMEDIA_TYPE_SUBTITLE: o->subtitle_disable = 1; break;                                                                                 // 0.0
/*148 */             }                                                                                                                                           // 0.0
/*150 */             init_output_filter(ofilter, o, oc);                                                                                                         // 0.0
/*152 */         }                                                                                                                                               // 0.0
/*154 */     }                                                                                                                                                   // 0.0
/*158 */     /* ffserver seeking with date=... needs a date reference */                                                                                         // 0.0
/*160 */     if (!strcmp(file_oformat->name, "ffm") &&                                                                                                           // 0.0
/*162 */         av_strstart(filename, "http:", NULL)) {                                                                                                         // 0.0
/*164 */         int err = parse_option(o, "metadata", "creation_time=now", options);                                                                            // 0.0
/*166 */         if (err < 0) {                                                                                                                                  // 0.0
/*168 */             print_error(filename, err);                                                                                                                 // 0.0
/*170 */             exit_program(1);                                                                                                                            // 0.0
/*172 */         }                                                                                                                                               // 0.0
/*174 */     }                                                                                                                                                   // 0.0
/*178 */     if (!strcmp(file_oformat->name, "ffm") && !override_ffserver &&                                                                                     // 0.0
/*180 */         av_strstart(filename, "http:", NULL)) {                                                                                                         // 0.0
/*182 */         int j;                                                                                                                                          // 0.0
/*184 */         /* special case for files sent to ffserver: we get the stream                                                                                   // 0.0
/*186 */            parameters from ffserver */                                                                                                                  // 0.0
/*188 */         int err = read_ffserver_streams(o, oc, filename);                                                                                               // 0.0
/*190 */         if (err < 0) {                                                                                                                                  // 0.0
/*192 */             print_error(filename, err);                                                                                                                 // 0.0
/*194 */             exit_program(1);                                                                                                                            // 0.0
/*196 */         }                                                                                                                                               // 0.0
/*198 */         for(j = nb_output_streams - oc->nb_streams; j < nb_output_streams; j++) {                                                                       // 0.0
/*200 */             ost = output_streams[j];                                                                                                                    // 0.0
/*202 */             for (i = 0; i < nb_input_streams; i++) {                                                                                                    // 0.0
/*204 */                 ist = input_streams[i];                                                                                                                 // 0.0
/*206 */                 if(ist->st->codec->codec_type == ost->st->codec->codec_type){                                                                           // 0.0
/*208 */                     ost->sync_ist= ist;                                                                                                                 // 0.0
/*210 */                     ost->source_index= i;                                                                                                               // 0.0
/*212 */                     if(ost->st->codec->codec_type == AVMEDIA_TYPE_AUDIO) ost->avfilter = av_strdup("anull");                                            // 0.0
/*214 */                     if(ost->st->codec->codec_type == AVMEDIA_TYPE_VIDEO) ost->avfilter = av_strdup("null");                                             // 0.0
/*216 */                     ist->discard = 0;                                                                                                                   // 0.0
/*218 */                     ist->st->discard = AVDISCARD_NONE;                                                                                                  // 0.0
/*220 */                     break;                                                                                                                              // 0.0
/*222 */                 }                                                                                                                                       // 0.0
/*224 */             }                                                                                                                                           // 0.0
/*226 */             if(!ost->sync_ist){                                                                                                                         // 0.0
/*228 */                 av_log(NULL, AV_LOG_FATAL, "Missing %s stream which is required by this ffm\n", av_get_media_type_string(ost->st->codec->codec_type));  // 0.0
/*230 */                 exit_program(1);                                                                                                                        // 0.0
/*232 */             }                                                                                                                                           // 0.0
/*234 */         }                                                                                                                                               // 0.0
/*236 */     } else if (!o->nb_stream_maps) {                                                                                                                    // 0.0
/*238 */         char *subtitle_codec_name = NULL;                                                                                                               // 0.0
/*240 */         /* pick the "best" stream of each type */                                                                                                       // 0.0
/*244 */         /* video: highest resolution */                                                                                                                 // 0.0
/*246 */         if (!o->video_disable && oc->oformat->video_codec != AV_CODEC_ID_NONE) {                                                                        // 0.0
/*248 */             int area = 0, idx = -1;                                                                                                                     // 0.0
/*250 */             int qcr = avformat_query_codec(oc->oformat, oc->oformat->video_codec, 0);                                                                   // 0.0
/*252 */             for (i = 0; i < nb_input_streams; i++) {                                                                                                    // 0.0
/*254 */                 int new_area;                                                                                                                           // 0.0
/*256 */                 ist = input_streams[i];                                                                                                                 // 0.0
/*258 */                 new_area = ist->st->codec->width * ist->st->codec->height;                                                                              // 0.0
/*260 */                 if((qcr!=MKTAG('A', 'P', 'I', 'C')) && (ist->st->disposition & AV_DISPOSITION_ATTACHED_PIC))                                            // 0.0
/*262 */                     new_area = 1;                                                                                                                       // 0.0
/*264 */                 if (ist->st->codec->codec_type == AVMEDIA_TYPE_VIDEO &&                                                                                 // 0.0
/*266 */                     new_area > area) {                                                                                                                  // 0.0
/*268 */                     if((qcr==MKTAG('A', 'P', 'I', 'C')) && !(ist->st->disposition & AV_DISPOSITION_ATTACHED_PIC))                                       // 0.0
/*270 */                         continue;                                                                                                                       // 0.0
/*272 */                     area = new_area;                                                                                                                    // 0.0
/*274 */                     idx = i;                                                                                                                            // 0.0
/*276 */                 }                                                                                                                                       // 0.0
/*278 */             }                                                                                                                                           // 0.0
/*280 */             if (idx >= 0)                                                                                                                               // 0.0
/*282 */                 new_video_stream(o, oc, idx);                                                                                                           // 0.0
/*284 */         }                                                                                                                                               // 0.0
/*288 */         /* audio: most channels */                                                                                                                      // 0.0
/*290 */         if (!o->audio_disable && oc->oformat->audio_codec != AV_CODEC_ID_NONE) {                                                                        // 0.0
/*292 */             int channels = 0, idx = -1;                                                                                                                 // 0.0
/*294 */             for (i = 0; i < nb_input_streams; i++) {                                                                                                    // 0.0
/*296 */                 ist = input_streams[i];                                                                                                                 // 0.0
/*298 */                 if (ist->st->codec->codec_type == AVMEDIA_TYPE_AUDIO &&                                                                                 // 0.0
/*300 */                     ist->st->codec->channels > channels) {                                                                                              // 0.0
/*302 */                     channels = ist->st->codec->channels;                                                                                                // 0.0
/*304 */                     idx = i;                                                                                                                            // 0.0
/*306 */                 }                                                                                                                                       // 0.0
/*308 */             }                                                                                                                                           // 0.0
/*310 */             if (idx >= 0)                                                                                                                               // 0.0
/*312 */                 new_audio_stream(o, oc, idx);                                                                                                           // 0.0
/*314 */         }                                                                                                                                               // 0.0
/*318 */         /* subtitles: pick first */                                                                                                                     // 0.0
/*320 */         MATCH_PER_TYPE_OPT(codec_names, str, subtitle_codec_name, oc, "s");                                                                             // 0.0
/*322 */         if (!o->subtitle_disable && (oc->oformat->subtitle_codec != AV_CODEC_ID_NONE || subtitle_codec_name)) {                                         // 0.0
/*324 */             for (i = 0; i < nb_input_streams; i++)                                                                                                      // 0.0
/*326 */                 if (input_streams[i]->st->codec->codec_type == AVMEDIA_TYPE_SUBTITLE) {                                                                 // 0.0
/*328 */                     new_subtitle_stream(o, oc, i);                                                                                                      // 0.0
/*330 */                     break;                                                                                                                              // 0.0
/*332 */                 }                                                                                                                                       // 0.0
/*334 */         }                                                                                                                                               // 0.0
/*336 */         /* do something with data? */                                                                                                                   // 0.0
/*338 */     } else {                                                                                                                                            // 0.0
/*340 */         for (i = 0; i < o->nb_stream_maps; i++) {                                                                                                       // 0.0
/*342 */             StreamMap *map = &o->stream_maps[i];                                                                                                        // 0.0
/*346 */             if (map->disabled)                                                                                                                          // 0.0
/*348 */                 continue;                                                                                                                               // 0.0
/*352 */             if (map->linklabel) {                                                                                                                       // 0.0
/*354 */                 FilterGraph *fg;                                                                                                                        // 0.0
/*356 */                 OutputFilter *ofilter = NULL;                                                                                                           // 0.0
/*358 */                 int j, k;                                                                                                                               // 0.0
/*362 */                 for (j = 0; j < nb_filtergraphs; j++) {                                                                                                 // 0.0
/*364 */                     fg = filtergraphs[j];                                                                                                               // 0.0
/*366 */                     for (k = 0; k < fg->nb_outputs; k++) {                                                                                              // 0.0
/*368 */                         AVFilterInOut *out = fg->outputs[k]->out_tmp;                                                                                   // 0.0
/*370 */                         if (out && !strcmp(out->name, map->linklabel)) {                                                                                // 0.0
/*372 */                             ofilter = fg->outputs[k];                                                                                                   // 0.0
/*374 */                             goto loop_end;                                                                                                              // 0.0
/*376 */                         }                                                                                                                               // 0.0
/*378 */                     }                                                                                                                                   // 0.0
/*380 */                 }                                                                                                                                       // 0.0
/*382 */ loop_end:                                                                                                                                               // 0.0
/*384 */                 if (!ofilter) {                                                                                                                         // 0.0
/*386 */                     av_log(NULL, AV_LOG_FATAL, "Output with label '%s' does not exist "                                                                 // 0.0
/*388 */                            "in any defined filter graph, or was already used elsewhere.\n", map->linklabel);                                            // 0.0
/*390 */                     exit_program(1);                                                                                                                    // 0.0
/*392 */                 }                                                                                                                                       // 0.0
/*394 */                 init_output_filter(ofilter, o, oc);                                                                                                     // 0.0
/*396 */             } else {                                                                                                                                    // 0.0
/*398 */                 int src_idx = input_files[map->file_index]->ist_index + map->stream_index;                                                              // 0.0
/*402 */                 ist = input_streams[input_files[map->file_index]->ist_index + map->stream_index];                                                       // 0.0
/*404 */                 if(o->subtitle_disable && ist->st->codec->codec_type == AVMEDIA_TYPE_SUBTITLE)                                                          // 0.0
/*406 */                     continue;                                                                                                                           // 0.0
/*408 */                 if(o->   audio_disable && ist->st->codec->codec_type == AVMEDIA_TYPE_AUDIO)                                                             // 0.0
/*410 */                     continue;                                                                                                                           // 0.0
/*412 */                 if(o->   video_disable && ist->st->codec->codec_type == AVMEDIA_TYPE_VIDEO)                                                             // 0.0
/*414 */                     continue;                                                                                                                           // 0.0
/*416 */                 if(o->    data_disable && ist->st->codec->codec_type == AVMEDIA_TYPE_DATA)                                                              // 0.0
/*418 */                     continue;                                                                                                                           // 0.0
/*422 */                 switch (ist->st->codec->codec_type) {                                                                                                   // 0.0
/*424 */                 case AVMEDIA_TYPE_VIDEO:      ost = new_video_stream     (o, oc, src_idx); break;                                                       // 0.0
/*426 */                 case AVMEDIA_TYPE_AUDIO:      ost = new_audio_stream     (o, oc, src_idx); break;                                                       // 0.0
/*428 */                 case AVMEDIA_TYPE_SUBTITLE:   ost = new_subtitle_stream  (o, oc, src_idx); break;                                                       // 0.0
/*430 */                 case AVMEDIA_TYPE_DATA:       ost = new_data_stream      (o, oc, src_idx); break;                                                       // 0.0
/*432 */                 case AVMEDIA_TYPE_ATTACHMENT: ost = new_attachment_stream(o, oc, src_idx); break;                                                       // 0.0
/*434 */                 default:                                                                                                                                // 0.0
/*436 */                     av_log(NULL, AV_LOG_FATAL, "Cannot map stream #%d:%d - unsupported type.\n",                                                        // 0.0
/*438 */                            map->file_index, map->stream_index);                                                                                         // 0.0
/*440 */                     exit_program(1);                                                                                                                    // 0.0
/*442 */                 }                                                                                                                                       // 0.0
/*444 */             }                                                                                                                                           // 0.0
/*446 */         }                                                                                                                                               // 0.0
/*448 */     }                                                                                                                                                   // 0.0
/*452 */     /* handle attached files */                                                                                                                         // 0.0
/*454 */     for (i = 0; i < o->nb_attachments; i++) {                                                                                                           // 0.0
/*456 */         AVIOContext *pb;                                                                                                                                // 0.0
/*458 */         uint8_t *attachment;                                                                                                                            // 0.0
/*460 */         const char *p;                                                                                                                                  // 0.0
/*462 */         int64_t len;                                                                                                                                    // 0.0
/*466 */         if ((err = avio_open2(&pb, o->attachments[i], AVIO_FLAG_READ, &int_cb, NULL)) < 0) {                                                            // 0.0
/*468 */             av_log(NULL, AV_LOG_FATAL, "Could not open attachment file %s.\n",                                                                          // 0.0
/*470 */                    o->attachments[i]);                                                                                                                  // 0.0
/*472 */             exit_program(1);                                                                                                                            // 0.0
/*474 */         }                                                                                                                                               // 0.0
/*476 */         if ((len = avio_size(pb)) <= 0) {                                                                                                               // 0.0
/*478 */             av_log(NULL, AV_LOG_FATAL, "Could not get size of the attachment %s.\n",                                                                    // 0.0
/*480 */                    o->attachments[i]);                                                                                                                  // 0.0
/*482 */             exit_program(1);                                                                                                                            // 0.0
/*484 */         }                                                                                                                                               // 0.0
/*486 */         if (!(attachment = av_malloc(len))) {                                                                                                           // 0.0
/*488 */             av_log(NULL, AV_LOG_FATAL, "Attachment %s too large to fit into memory.\n",                                                                 // 0.0
/*490 */                    o->attachments[i]);                                                                                                                  // 0.0
/*492 */             exit_program(1);                                                                                                                            // 0.0
/*494 */         }                                                                                                                                               // 0.0
/*496 */         avio_read(pb, attachment, len);                                                                                                                 // 0.0
/*500 */         ost = new_attachment_stream(o, oc, -1);                                                                                                         // 0.0
/*502 */         ost->stream_copy               = 0;                                                                                                             // 0.0
/*504 */         ost->attachment_filename       = o->attachments[i];                                                                                             // 0.0
/*506 */         ost->finished                  = 1;                                                                                                             // 0.0
/*508 */         ost->st->codec->extradata      = attachment;                                                                                                    // 0.0
/*510 */         ost->st->codec->extradata_size = len;                                                                                                           // 0.0
/*514 */         p = strrchr(o->attachments[i], '/');                                                                                                            // 0.0
/*516 */         av_dict_set(&ost->st->metadata, "filename", (p && *p) ? p + 1 : o->attachments[i], AV_DICT_DONT_OVERWRITE);                                     // 0.0
/*518 */         avio_close(pb);                                                                                                                                 // 0.0
/*520 */     }                                                                                                                                                   // 0.0
/*524 */     for (i = nb_output_streams - oc->nb_streams; i < nb_output_streams; i++) { //for all streams of this output file                                    // 0.0
/*526 */         AVDictionaryEntry *e;                                                                                                                           // 0.0
/*528 */         ost = output_streams[i];                                                                                                                        // 0.0
/*532 */         if ((ost->stream_copy || ost->attachment_filename)                                                                                              // 0.0
/*534 */             && (e = av_dict_get(o->g->codec_opts, "flags", NULL, AV_DICT_IGNORE_SUFFIX))                                                                // 0.0
/*536 */             && (!e->key[5] || check_stream_specifier(oc, ost->st, e->key+6)))                                                                           // 0.0
/*538 */             if (av_opt_set(ost->st->codec, "flags", e->value, 0) < 0)                                                                                   // 0.0
/*540 */                 exit_program(1);                                                                                                                        // 0.0
/*542 */     }                                                                                                                                                   // 0.0
/*546 */     /* check if all codec options have been used */                                                                                                     // 0.0
/*548 */     unused_opts = strip_specifiers(o->g->codec_opts);                                                                                                   // 0.0
/*550 */     for (i = of->ost_index; i < nb_output_streams; i++) {                                                                                               // 0.0
/*552 */         e = NULL;                                                                                                                                       // 0.0
/*554 */         while ((e = av_dict_get(output_streams[i]->opts, "", e,                                                                                         // 0.0
/*556 */                                 AV_DICT_IGNORE_SUFFIX)))                                                                                                // 0.0
/*558 */             av_dict_set(&unused_opts, e->key, NULL, 0);                                                                                                 // 0.0
/*560 */     }                                                                                                                                                   // 0.0
/*564 */     e = NULL;                                                                                                                                           // 0.0
/*566 */     while ((e = av_dict_get(unused_opts, "", e, AV_DICT_IGNORE_SUFFIX))) {                                                                              // 0.0
/*568 */         const AVClass *class = avcodec_get_class();                                                                                                     // 0.0
/*570 */         const AVOption *option = av_opt_find(&class, e->key, NULL, 0,                                                                                   // 0.0
/*572 */                                              AV_OPT_SEARCH_CHILDREN | AV_OPT_SEARCH_FAKE_OBJ);                                                          // 0.0
/*574 */         if (!option)                                                                                                                                    // 0.0
/*576 */             continue;                                                                                                                                   // 0.0
/*578 */         if (!(option->flags & AV_OPT_FLAG_ENCODING_PARAM)) {                                                                                            // 0.0
/*580 */             av_log(NULL, AV_LOG_ERROR, "Codec AVOption %s (%s) specified for "                                                                          // 0.0
/*582 */                    "output file #%d (%s) is not an encoding option.\n", e->key,                                                                         // 0.0
/*584 */                    option->help ? option->help : "", nb_output_files - 1,                                                                               // 0.0
/*586 */                    filename);                                                                                                                           // 0.0
/*588 */             exit_program(1);                                                                                                                            // 0.0
/*590 */         }                                                                                                                                               // 0.0
/*594 */         // gop_timecode is injected by generic code but not always used                                                                                 // 0.0
/*596 */         if (!strcmp(e->key, "gop_timecode"))                                                                                                            // 0.0
/*598 */             continue;                                                                                                                                   // 0.0
/*602 */         av_log(NULL, AV_LOG_WARNING, "Codec AVOption %s (%s) specified for "                                                                            // 0.0
/*604 */                "output file #%d (%s) has not been used for any stream. The most "                                                                       // 0.0
/*606 */                "likely reason is either wrong type (e.g. a video option with "                                                                          // 0.0
/*608 */                "no video streams) or that it is a private option of some encoder "                                                                      // 0.0
/*610 */                "which was not actually used for any stream.\n", e->key,                                                                                 // 0.0
/*612 */                option->help ? option->help : "", nb_output_files - 1, filename);                                                                        // 0.0
/*614 */     }                                                                                                                                                   // 0.0
/*616 */     av_dict_free(&unused_opts);                                                                                                                         // 0.0
/*620 */     /* check filename in case of an image number is expected */                                                                                         // 0.0
/*622 */     if (oc->oformat->flags & AVFMT_NEEDNUMBER) {                                                                                                        // 0.0
/*624 */         if (!av_filename_number_test(oc->filename)) {                                                                                                   // 0.0
/*626 */             print_error(oc->filename, AVERROR(EINVAL));                                                                                                 // 0.0
/*628 */             exit_program(1);                                                                                                                            // 0.0
/*630 */         }                                                                                                                                               // 0.0
/*632 */     }                                                                                                                                                   // 0.0
/*636 */     if (!(oc->oformat->flags & AVFMT_NOFILE)) {                                                                                                         // 0.0
/*638 */         /* test if it already exists to avoid losing precious files */                                                                                  // 0.0
/*640 */         assert_file_overwrite(filename);                                                                                                                // 0.0
/*644 */         /* open the file */                                                                                                                             // 0.0
/*646 */         if ((err = avio_open2(&oc->pb, filename, AVIO_FLAG_WRITE,                                                                                       // 0.0
/*648 */                               &oc->interrupt_callback,                                                                                                  // 0.0
/*650 */                               &of->opts)) < 0) {                                                                                                        // 0.0
/*652 */             print_error(filename, err);                                                                                                                 // 0.0
/*654 */             exit_program(1);                                                                                                                            // 0.0
/*656 */         }                                                                                                                                               // 0.0
/*658 */     } else if (strcmp(oc->oformat->name, "image2")==0 && !av_filename_number_test(filename))                                                            // 0.0
/*660 */         assert_file_overwrite(filename);                                                                                                                // 0.0
/*664 */     if (o->mux_preload) {                                                                                                                               // 0.0
/*666 */         uint8_t buf[64];                                                                                                                                // 0.0
/*668 */         snprintf(buf, sizeof(buf), "%d", (int)(o->mux_preload*AV_TIME_BASE));                                                                           // 0.0
/*670 */         av_dict_set(&of->opts, "preload", buf, 0);                                                                                                      // 0.0
/*672 */     }                                                                                                                                                   // 0.0
/*674 */     oc->max_delay = (int)(o->mux_max_delay * AV_TIME_BASE);                                                                                             // 0.0
/*678 */     /* copy metadata */                                                                                                                                 // 0.0
/*680 */     for (i = 0; i < o->nb_metadata_map; i++) {                                                                                                          // 0.0
/*682 */         char *p;                                                                                                                                        // 0.0
/*684 */         int in_file_index = strtol(o->metadata_map[i].u.str, &p, 0);                                                                                    // 0.0
/*688 */         if (in_file_index >= nb_input_files) {                                                                                                          // 0.0
/*690 */             av_log(NULL, AV_LOG_FATAL, "Invalid input file index %d while processing metadata maps\n", in_file_index);                                  // 0.0
/*692 */             exit_program(1);                                                                                                                            // 0.0
/*694 */         }                                                                                                                                               // 0.0
/*696 */         copy_metadata(o->metadata_map[i].specifier, *p ? p + 1 : p, oc,                                                                                 // 0.0
/*698 */                       in_file_index >= 0 ?                                                                                                              // 0.0
/*700 */                       input_files[in_file_index]->ctx : NULL, o);                                                                                       // 0.0
/*702 */     }                                                                                                                                                   // 0.0
/*706 */     /* copy chapters */                                                                                                                                 // 0.0
/*708 */     if (o->chapters_input_file >= nb_input_files) {                                                                                                     // 0.0
/*710 */         if (o->chapters_input_file == INT_MAX) {                                                                                                        // 0.0
/*712 */             /* copy chapters from the first input file that has them*/                                                                                  // 0.0
/*714 */             o->chapters_input_file = -1;                                                                                                                // 0.0
/*716 */             for (i = 0; i < nb_input_files; i++)                                                                                                        // 0.0
/*718 */                 if (input_files[i]->ctx->nb_chapters) {                                                                                                 // 0.0
/*720 */                     o->chapters_input_file = i;                                                                                                         // 0.0
/*722 */                     break;                                                                                                                              // 0.0
/*724 */                 }                                                                                                                                       // 0.0
/*726 */         } else {                                                                                                                                        // 0.0
/*728 */             av_log(NULL, AV_LOG_FATAL, "Invalid input file index %d in chapter mapping.\n",                                                             // 0.0
/*730 */                    o->chapters_input_file);                                                                                                             // 0.0
/*732 */             exit_program(1);                                                                                                                            // 0.0
/*734 */         }                                                                                                                                               // 0.0
/*736 */     }                                                                                                                                                   // 0.0
/*738 */     if (o->chapters_input_file >= 0)                                                                                                                    // 0.0
/*740 */         copy_chapters(input_files[o->chapters_input_file], of,                                                                                          // 0.0
/*742 */                       !o->metadata_chapters_manual);                                                                                                    // 0.0
/*746 */     /* copy global metadata by default */                                                                                                               // 0.0
/*748 */     if (!o->metadata_global_manual && nb_input_files){                                                                                                  // 0.0
/*750 */         av_dict_copy(&oc->metadata, input_files[0]->ctx->metadata,                                                                                      // 0.0
/*752 */                      AV_DICT_DONT_OVERWRITE);                                                                                                           // 0.0
/*754 */         if(o->recording_time != INT64_MAX)                                                                                                              // 0.0
/*756 */             av_dict_set(&oc->metadata, "duration", NULL, 0);                                                                                            // 0.0
/*758 */         av_dict_set(&oc->metadata, "creation_time", NULL, 0);                                                                                           // 0.0
/*760 */     }                                                                                                                                                   // 0.0
/*762 */     if (!o->metadata_streams_manual)                                                                                                                    // 0.0
/*764 */         for (i = of->ost_index; i < nb_output_streams; i++) {                                                                                           // 0.0
/*766 */             InputStream *ist;                                                                                                                           // 0.0
/*768 */             if (output_streams[i]->source_index < 0)         /* this is true e.g. for attached files */                                                 // 0.0
/*770 */                 continue;                                                                                                                               // 0.0
/*772 */             ist = input_streams[output_streams[i]->source_index];                                                                                       // 0.0
/*774 */             av_dict_copy(&output_streams[i]->st->metadata, ist->st->metadata, AV_DICT_DONT_OVERWRITE);                                                  // 0.0
/*776 */         }                                                                                                                                               // 0.0
/*780 */     /* process manually set metadata */                                                                                                                 // 0.0
/*782 */     for (i = 0; i < o->nb_metadata; i++) {                                                                                                              // 0.0
/*784 */         AVDictionary **m;                                                                                                                               // 0.0
/*786 */         char type, *val;                                                                                                                                // 0.0
/*788 */         const char *stream_spec;                                                                                                                        // 0.0
/*790 */         int index = 0, j, ret = 0;                                                                                                                      // 0.0
/*794 */         val = strchr(o->metadata[i].u.str, '=');                                                                                                        // 0.0
/*796 */         if (!val) {                                                                                                                                     // 0.0
/*798 */             av_log(NULL, AV_LOG_FATAL, "No '=' character in metadata string %s.\n",                                                                     // 0.0
/*800 */                    o->metadata[i].u.str);                                                                                                               // 0.0
/*802 */             exit_program(1);                                                                                                                            // 0.0
/*804 */         }                                                                                                                                               // 0.0
/*806 */         *val++ = 0;                                                                                                                                     // 0.0
/*810 */         parse_meta_type(o->metadata[i].specifier, &type, &index, &stream_spec);                                                                         // 0.0
/*812 */         if (type == 's') {                                                                                                                              // 0.0
/*814 */             for (j = 0; j < oc->nb_streams; j++) {                                                                                                      // 0.0
/*816 */                 if ((ret = check_stream_specifier(oc, oc->streams[j], stream_spec)) > 0) {                                                              // 0.0
/*818 */                     av_dict_set(&oc->streams[j]->metadata, o->metadata[i].u.str, *val ? val : NULL, 0);                                                 // 0.0
/*820 */                 } else if (ret < 0)                                                                                                                     // 0.0
/*822 */                     exit_program(1);                                                                                                                    // 0.0
/*824 */             }                                                                                                                                           // 0.0
/*826 */         }                                                                                                                                               // 0.0
/*828 */         else {                                                                                                                                          // 0.0
/*830 */             switch (type) {                                                                                                                             // 0.0
/*832 */             case 'g':                                                                                                                                   // 0.0
/*834 */                 m = &oc->metadata;                                                                                                                      // 0.0
/*836 */                 break;                                                                                                                                  // 0.0
/*838 */             case 'c':                                                                                                                                   // 0.0
/*840 */                 if (index < 0 || index >= oc->nb_chapters) {                                                                                            // 0.0
/*842 */                     av_log(NULL, AV_LOG_FATAL, "Invalid chapter index %d in metadata specifier.\n", index);                                             // 0.0
/*844 */                     exit_program(1);                                                                                                                    // 0.0
/*846 */                 }                                                                                                                                       // 0.0
/*848 */                 m = &oc->chapters[index]->metadata;                                                                                                     // 0.0
/*850 */                 break;                                                                                                                                  // 0.0
/*852 */             default:                                                                                                                                    // 0.0
/*854 */                 av_log(NULL, AV_LOG_FATAL, "Invalid metadata specifier %s.\n", o->metadata[i].specifier);                                               // 0.0
/*856 */                 exit_program(1);                                                                                                                        // 0.0
/*858 */             }                                                                                                                                           // 0.0
/*860 */             av_dict_set(m, o->metadata[i].u.str, *val ? val : NULL, 0);                                                                                 // 0.0
/*862 */         }                                                                                                                                               // 0.0
/*864 */     }                                                                                                                                                   // 0.0
/*868 */     return 0;                                                                                                                                           // 0.0
/*870 */ }                                                                                                                                                       // 0.0
