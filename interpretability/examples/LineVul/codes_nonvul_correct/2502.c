// commit message FFmpeg@13ccba50d4 (target=0, prob=0.3009833, correct=True): avconv: move limit_filesize to options context
/*0   */ static void opt_output_file(void *optctx, const char *filename)                                                    // (7) 0.03516
/*2   */ {                                                                                                                  // (31) 0.001953
/*4   */     OptionsContext *o = optctx;                                                                                    // (20) 0.02148
/*6   */     AVFormatContext *oc;                                                                                           // (22) 0.01758
/*8   */     int i, err;                                                                                                    // (24) 0.01563
/*10  */     AVOutputFormat *file_oformat;                                                                                  // (19) 0.02344
/*12  */     OutputStream *ost;                                                                                             // (23) 0.01563
/*14  */     InputStream  *ist;                                                                                             // (21) 0.01758
/*18  */     if (!strcmp(filename, "-"))                                                                                    // (15) 0.02539
/*20  */         filename = "pipe:";                                                                                        // (14) 0.02539
/*24  */     oc = avformat_alloc_context();                                                                                 // (16) 0.02539
/*26  */     if (!oc) {                                                                                                     // (25) 0.01562
/*28  */         print_error(filename, AVERROR(ENOMEM));                                                                    // (5) 0.04101
/*30  */         exit_program(1);                                                                                           // (17) 0.02539
/*32  */     }                                                                                                              // (30) 0.007812
/*36  */     if (last_asked_format) {                                                                                       // (18) 0.02539
/*38  */         file_oformat = av_guess_format(last_asked_format, NULL, NULL);                                             // (2) 0.05859
/*40  */         if (!file_oformat) {                                                                                       // (11) 0.0293
/*42  */             fprintf(stderr, "Requested output format '%s' is not a suitable output format\n", last_asked_format);  // (0) 0.08398
/*44  */             exit_program(1);                                                                                       // (9) 0.0332
/*46  */         }                                                                                                          // (27) 0.01562
/*48  */         last_asked_format = NULL;                                                                                  // (10) 0.03125
/*50  */     } else {                                                                                                       // (28) 0.01172
/*52  */         file_oformat = av_guess_format(NULL, filename, NULL);                                                      // (3) 0.04883
/*54  */         if (!file_oformat) {                                                                                       // (12) 0.0293
/*56  */             fprintf(stderr, "Unable to find a suitable output format for '%s'\n",                                  // (1) 0.06836
/*58  */                     filename);                                                                                     // (6) 0.04101
/*60  */             exit_program(1);                                                                                       // (8) 0.0332
/*62  */         }                                                                                                          // (26) 0.01562
/*64  */     }                                                                                                              // (29) 0.007812
/*68  */     oc->oformat = file_oformat;                                                                                    // (13) 0.02734
/*70  */     av_strlcpy(oc->filename, filename, sizeof(oc->filename));                                                      // (4) 0.04102
/*74  */     if (!strcmp(file_oformat->name, "ffm") &&                                                                      // 0.0
/*76  */         av_strstart(filename, "http:", NULL)) {                                                                    // 0.0
/*78  */         /* special case for files sent to avserver: we get the stream                                              // 0.0
/*80  */            parameters from avserver */                                                                             // 0.0
/*82  */         int err = read_avserver_streams(oc, filename);                                                             // 0.0
/*84  */         if (err < 0) {                                                                                             // 0.0
/*86  */             print_error(filename, err);                                                                            // 0.0
/*88  */             exit_program(1);                                                                                       // 0.0
/*90  */         }                                                                                                          // 0.0
/*92  */     } else if (!o->nb_stream_maps) {                                                                               // 0.0
/*94  */         /* pick the "best" stream of each type */                                                                  // 0.0
/*96  */ #define NEW_STREAM(type, index)\                                                                                   // 0.0
/*98  */         if (index >= 0) {\                                                                                         // 0.0
/*100 */             ost = new_ ## type ## _stream(oc);\                                                                    // 0.0
/*102 */             ost->source_index = index;\                                                                            // 0.0
/*104 */             ost->sync_ist     = &input_streams[index];\                                                            // 0.0
/*106 */             input_streams[index].discard = 0;\                                                                     // 0.0
/*108 */         }                                                                                                          // 0.0
/*112 */         /* video: highest resolution */                                                                            // 0.0
/*114 */         if (!video_disable && oc->oformat->video_codec != CODEC_ID_NONE) {                                         // 0.0
/*116 */             int area = 0, idx = -1;                                                                                // 0.0
/*118 */             for (i = 0; i < nb_input_streams; i++) {                                                               // 0.0
/*120 */                 ist = &input_streams[i];                                                                           // 0.0
/*122 */                 if (ist->st->codec->codec_type == AVMEDIA_TYPE_VIDEO &&                                            // 0.0
/*124 */                     ist->st->codec->width * ist->st->codec->height > area) {                                       // 0.0
/*126 */                     area = ist->st->codec->width * ist->st->codec->height;                                         // 0.0
/*128 */                     idx = i;                                                                                       // 0.0
/*130 */                 }                                                                                                  // 0.0
/*132 */             }                                                                                                      // 0.0
/*134 */             NEW_STREAM(video, idx);                                                                                // 0.0
/*136 */         }                                                                                                          // 0.0
/*140 */         /* audio: most channels */                                                                                 // 0.0
/*142 */         if (!audio_disable && oc->oformat->audio_codec != CODEC_ID_NONE) {                                         // 0.0
/*144 */             int channels = 0, idx = -1;                                                                            // 0.0
/*146 */             for (i = 0; i < nb_input_streams; i++) {                                                               // 0.0
/*148 */                 ist = &input_streams[i];                                                                           // 0.0
/*150 */                 if (ist->st->codec->codec_type == AVMEDIA_TYPE_AUDIO &&                                            // 0.0
/*152 */                     ist->st->codec->channels > channels) {                                                         // 0.0
/*154 */                     channels = ist->st->codec->channels;                                                           // 0.0
/*156 */                     idx = i;                                                                                       // 0.0
/*158 */                 }                                                                                                  // 0.0
/*160 */             }                                                                                                      // 0.0
/*162 */             NEW_STREAM(audio, idx);                                                                                // 0.0
/*164 */         }                                                                                                          // 0.0
/*168 */         /* subtitles: pick first */                                                                                // 0.0
/*170 */         if (!subtitle_disable && oc->oformat->subtitle_codec != CODEC_ID_NONE) {                                   // 0.0
/*172 */             for (i = 0; i < nb_input_streams; i++)                                                                 // 0.0
/*174 */                 if (input_streams[i].st->codec->codec_type == AVMEDIA_TYPE_SUBTITLE) {                             // 0.0
/*176 */                     NEW_STREAM(subtitle, i);                                                                       // 0.0
/*178 */                     break;                                                                                         // 0.0
/*180 */                 }                                                                                                  // 0.0
/*182 */         }                                                                                                          // 0.0
/*184 */         /* do something with data? */                                                                              // 0.0
/*186 */     } else {                                                                                                       // 0.0
/*188 */         for (i = 0; i < o->nb_stream_maps; i++) {                                                                  // 0.0
/*190 */             StreamMap *map = &o->stream_maps[i];                                                                   // 0.0
/*194 */             if (map->disabled)                                                                                     // 0.0
/*196 */                 continue;                                                                                          // 0.0
/*200 */             ist = &input_streams[input_files[map->file_index].ist_index + map->stream_index];                      // 0.0
/*202 */             switch (ist->st->codec->codec_type) {                                                                  // 0.0
/*204 */             case AVMEDIA_TYPE_VIDEO:    ost = new_video_stream(oc);    break;                                      // 0.0
/*206 */             case AVMEDIA_TYPE_AUDIO:    ost = new_audio_stream(oc);    break;                                      // 0.0
/*208 */             case AVMEDIA_TYPE_SUBTITLE: ost = new_subtitle_stream(oc); break;                                      // 0.0
/*210 */             case AVMEDIA_TYPE_DATA:     ost = new_data_stream(oc);     break;                                      // 0.0
/*212 */             default:                                                                                               // 0.0
/*214 */                 av_log(NULL, AV_LOG_ERROR, "Cannot map stream #%d.%d - unsupported type.\n",                       // 0.0
/*216 */                        map->file_index, map->stream_index);                                                        // 0.0
/*218 */                 exit_program(1);                                                                                   // 0.0
/*220 */             }                                                                                                      // 0.0
/*224 */             ost->source_index = input_files[map->file_index].ist_index + map->stream_index;                        // 0.0
/*226 */             ost->sync_ist = &input_streams[input_files[map->sync_file_index].ist_index +                           // 0.0
/*228 */                                            map->sync_stream_index];                                                // 0.0
/*230 */             ist->discard = 0;                                                                                      // 0.0
/*232 */         }                                                                                                          // 0.0
/*234 */     }                                                                                                              // 0.0
/*238 */     av_dict_copy(&oc->metadata, metadata, 0);                                                                      // 0.0
/*240 */     av_dict_free(&metadata);                                                                                       // 0.0
/*246 */     output_files = grow_array(output_files, sizeof(*output_files), &nb_output_files, nb_output_files + 1);         // 0.0
/*248 */     output_files[nb_output_files - 1].ctx       = oc;                                                              // 0.0
/*250 */     output_files[nb_output_files - 1].ost_index = nb_output_streams - oc->nb_streams;                              // 0.0
/*252 */     output_files[nb_output_files - 1].recording_time = o->recording_time;                                          // 0.0
/*254 */     output_files[nb_output_files - 1].start_time     = o->start_time;                                              // 0.0
/*256 */     output_files[nb_output_files - 1].limit_filesize = limit_filesize;                                             // 0.0
/*258 */     av_dict_copy(&output_files[nb_output_files - 1].opts, format_opts, 0);                                         // 0.0
/*262 */     /* check filename in case of an image number is expected */                                                    // 0.0
/*264 */     if (oc->oformat->flags & AVFMT_NEEDNUMBER) {                                                                   // 0.0
/*266 */         if (!av_filename_number_test(oc->filename)) {                                                              // 0.0
/*268 */             print_error(oc->filename, AVERROR(EINVAL));                                                            // 0.0
/*270 */             exit_program(1);                                                                                       // 0.0
/*272 */         }                                                                                                          // 0.0
/*274 */     }                                                                                                              // 0.0
/*278 */     if (!(oc->oformat->flags & AVFMT_NOFILE)) {                                                                    // 0.0
/*280 */         /* test if it already exists to avoid loosing precious files */                                            // 0.0
/*282 */         if (!file_overwrite &&                                                                                     // 0.0
/*284 */             (strchr(filename, ':') == NULL ||                                                                      // 0.0
/*286 */              filename[1] == ':' ||                                                                                 // 0.0
/*288 */              av_strstart(filename, "file:", NULL))) {                                                              // 0.0
/*290 */             if (avio_check(filename, 0) == 0) {                                                                    // 0.0
/*292 */                 if (!using_stdin) {                                                                                // 0.0
/*294 */                     fprintf(stderr,"File '%s' already exists. Overwrite ? [y/N] ", filename);                      // 0.0
/*296 */                     fflush(stderr);                                                                                // 0.0
/*298 */                     if (!read_yesno()) {                                                                           // 0.0
/*300 */                         fprintf(stderr, "Not overwriting - exiting\n");                                            // 0.0
/*302 */                         exit_program(1);                                                                           // 0.0
/*304 */                     }                                                                                              // 0.0
/*306 */                 }                                                                                                  // 0.0
/*308 */                 else {                                                                                             // 0.0
/*310 */                     fprintf(stderr,"File '%s' already exists. Exiting.\n", filename);                              // 0.0
/*312 */                     exit_program(1);                                                                               // 0.0
/*314 */                 }                                                                                                  // 0.0
/*316 */             }                                                                                                      // 0.0
/*318 */         }                                                                                                          // 0.0
/*322 */         /* open the file */                                                                                        // 0.0
/*324 */         if ((err = avio_open(&oc->pb, filename, AVIO_FLAG_WRITE)) < 0) {                                           // 0.0
/*326 */             print_error(filename, err);                                                                            // 0.0
/*328 */             exit_program(1);                                                                                       // 0.0
/*330 */         }                                                                                                          // 0.0
/*332 */     }                                                                                                              // 0.0
/*336 */     oc->preload= (int)(mux_preload*AV_TIME_BASE);                                                                  // 0.0
/*338 */     oc->max_delay= (int)(mux_max_delay*AV_TIME_BASE);                                                              // 0.0
/*340 */     oc->flags |= AVFMT_FLAG_NONBLOCK;                                                                              // 0.0
/*344 */     /* copy chapters */                                                                                            // 0.0
/*346 */     if (chapters_input_file >= nb_input_files) {                                                                   // 0.0
/*348 */         if (chapters_input_file == INT_MAX) {                                                                      // 0.0
/*350 */             /* copy chapters from the first input file that has them*/                                             // 0.0
/*352 */             chapters_input_file = -1;                                                                              // 0.0
/*354 */             for (i = 0; i < nb_input_files; i++)                                                                   // 0.0
/*356 */                 if (input_files[i].ctx->nb_chapters) {                                                             // 0.0
/*358 */                     chapters_input_file = i;                                                                       // 0.0
/*360 */                     break;                                                                                         // 0.0
/*362 */                 }                                                                                                  // 0.0
/*364 */         } else {                                                                                                   // 0.0
/*366 */             av_log(NULL, AV_LOG_ERROR, "Invalid input file index %d in chapter mapping.\n",                        // 0.0
/*368 */                    chapters_input_file);                                                                           // 0.0
/*370 */             exit_program(1);                                                                                       // 0.0
/*372 */         }                                                                                                          // 0.0
/*374 */     }                                                                                                              // 0.0
/*376 */     if (chapters_input_file >= 0)                                                                                  // 0.0
/*378 */         copy_chapters(&input_files[chapters_input_file], &output_files[nb_output_files - 1]);                      // 0.0
/*382 */     /* copy metadata */                                                                                            // 0.0
/*384 */     for (i = 0; i < nb_meta_data_maps; i++) {                                                                      // 0.0
/*386 */         AVFormatContext *files[2];                                                                                 // 0.0
/*388 */         AVDictionary    **meta[2];                                                                                 // 0.0
/*390 */         int j;                                                                                                     // 0.0
/*394 */ #define METADATA_CHECK_INDEX(index, nb_elems, desc)\                                                               // 0.0
/*396 */         if ((index) < 0 || (index) >= (nb_elems)) {\                                                               // 0.0
/*398 */             av_log(NULL, AV_LOG_ERROR, "Invalid %s index %d while processing metadata maps\n",\                    // 0.0
/*400 */                      (desc), (index));\                                                                            // 0.0
/*402 */             exit_program(1);\                                                                                      // 0.0
/*404 */         }                                                                                                          // 0.0
/*408 */         int in_file_index = meta_data_maps[i][1].file;                                                             // 0.0
/*410 */         if (in_file_index < 0)                                                                                     // 0.0
/*412 */             continue;                                                                                              // 0.0
/*414 */         METADATA_CHECK_INDEX(in_file_index, nb_input_files, "input file")                                          // 0.0
/*418 */         files[0] = oc;                                                                                             // 0.0
/*420 */         files[1] = input_files[in_file_index].ctx;                                                                 // 0.0
/*424 */         for (j = 0; j < 2; j++) {                                                                                  // 0.0
/*426 */             MetadataMap *map = &meta_data_maps[i][j];                                                              // 0.0
/*430 */             switch (map->type) {                                                                                   // 0.0
/*432 */             case 'g':                                                                                              // 0.0
/*434 */                 meta[j] = &files[j]->metadata;                                                                     // 0.0
/*436 */                 break;                                                                                             // 0.0
/*438 */             case 's':                                                                                              // 0.0
/*440 */                 METADATA_CHECK_INDEX(map->index, files[j]->nb_streams, "stream")                                   // 0.0
/*442 */                 meta[j] = &files[j]->streams[map->index]->metadata;                                                // 0.0
/*444 */                 break;                                                                                             // 0.0
/*446 */             case 'c':                                                                                              // 0.0
/*448 */                 METADATA_CHECK_INDEX(map->index, files[j]->nb_chapters, "chapter")                                 // 0.0
/*450 */                 meta[j] = &files[j]->chapters[map->index]->metadata;                                               // 0.0
/*452 */                 break;                                                                                             // 0.0
/*454 */             case 'p':                                                                                              // 0.0
/*456 */                 METADATA_CHECK_INDEX(map->index, files[j]->nb_programs, "program")                                 // 0.0
/*458 */                 meta[j] = &files[j]->programs[map->index]->metadata;                                               // 0.0
/*460 */                 break;                                                                                             // 0.0
/*462 */             }                                                                                                      // 0.0
/*464 */         }                                                                                                          // 0.0
/*468 */         av_dict_copy(meta[0], *meta[1], AV_DICT_DONT_OVERWRITE);                                                   // 0.0
/*470 */     }                                                                                                              // 0.0
/*474 */     /* copy global metadata by default */                                                                          // 0.0
/*476 */     if (metadata_global_autocopy && nb_input_files)                                                                // 0.0
/*478 */         av_dict_copy(&oc->metadata, input_files[0].ctx->metadata,                                                  // 0.0
/*480 */                      AV_DICT_DONT_OVERWRITE);                                                                      // 0.0
/*482 */     if (metadata_streams_autocopy)                                                                                 // 0.0
/*484 */         for (i = output_files[nb_output_files - 1].ost_index; i < nb_output_streams; i++) {                        // 0.0
/*486 */             InputStream *ist = &input_streams[output_streams[i].source_index];                                     // 0.0
/*488 */             av_dict_copy(&output_streams[i].st->metadata, ist->st->metadata, AV_DICT_DONT_OVERWRITE);              // 0.0
/*490 */         }                                                                                                          // 0.0
/*494 */     frame_rate    = (AVRational){0, 0};                                                                            // 0.0
/*496 */     frame_width   = 0;                                                                                             // 0.0
/*498 */     frame_height  = 0;                                                                                             // 0.0
/*500 */     audio_sample_rate = 0;                                                                                         // 0.0
/*502 */     audio_channels    = 0;                                                                                         // 0.0
/*504 */     audio_sample_fmt  = AV_SAMPLE_FMT_NONE;                                                                        // 0.0
/*506 */     chapters_input_file = INT_MAX;                                                                                 // 0.0
/*508 */     limit_filesize = UINT64_MAX;                                                                                   // 0.0
/*512 */     av_freep(&meta_data_maps);                                                                                     // 0.0
/*514 */     nb_meta_data_maps = 0;                                                                                         // 0.0
/*516 */     metadata_global_autocopy   = 1;                                                                                // 0.0
/*518 */     metadata_streams_autocopy  = 1;                                                                                // 0.0
/*520 */     metadata_chapters_autocopy = 1;                                                                                // 0.0
/*522 */     av_freep(&streamid_map);                                                                                       // 0.0
/*524 */     nb_streamid_map = 0;                                                                                           // 0.0
/*528 */     av_dict_free(&codec_names);                                                                                    // 0.0
/*532 */     av_freep(&forced_key_frames);                                                                                  // 0.0
/*534 */     reset_options(o);                                                                                              // 0.0
/*536 */ }                                                                                                                  // 0.0
