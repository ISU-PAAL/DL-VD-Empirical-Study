// commit message FFmpeg@08d2cee49c (target=0, prob=0.29562613, correct=True): Fix -loop_input.
/*0   */ static int opt_input_file(const char *opt, const char *filename)                                                                              // (9) 0.03516
/*2   */ {                                                                                                                                             // (28) 0.001953
/*4   */     AVFormatContext *ic;                                                                                                                      // (22) 0.01758
/*6   */     AVInputFormat *file_iformat = NULL;                                                                                                       // (12) 0.02734
/*8   */     int err, i, ret, rfps, rfps_base;                                                                                                         // (8) 0.03516
/*10  */     int64_t timestamp;                                                                                                                        // (23) 0.01758
/*12  */     uint8_t buf[128];                                                                                                                         // (19) 0.02148
/*14  */     AVDictionary **opts;                                                                                                                      // (21) 0.01953
/*16  */     int orig_nb_streams;                     // number of streams before avformat_find_stream_info                                            // (0) 0.08594
/*20  */     if (last_asked_format) {                                                                                                                  // (15) 0.02539
/*22  */         if (!(file_iformat = av_find_input_format(last_asked_format))) {                                                                      // (2) 0.06055
/*24  */             fprintf(stderr, "Unknown input format: '%s'\n", last_asked_format);                                                               // (1) 0.07227
/*26  */             ffmpeg_exit(1);                                                                                                                   // (10) 0.03516
/*28  */         }                                                                                                                                     // (25) 0.01562
/*30  */         last_asked_format = NULL;                                                                                                             // (11) 0.03125
/*32  */     }                                                                                                                                         // (27) 0.007812
/*36  */     if (!strcmp(filename, "-"))                                                                                                               // (16) 0.02539
/*38  */         filename = "pipe:";                                                                                                                   // (14) 0.02539
/*42  */     using_stdin |= !strncmp(filename, "pipe:", 5) ||                                                                                          // (6) 0.04492
/*44  */                     !strcmp(filename, "/dev/stdin");                                                                                          // (3) 0.06055
/*48  */     /* get default parameters from command line */                                                                                            // (20) 0.02148
/*50  */     ic = avformat_alloc_context();                                                                                                            // (17) 0.02344
/*52  */     if (!ic) {                                                                                                                                // (24) 0.01562
/*54  */         print_error(filename, AVERROR(ENOMEM));                                                                                               // (7) 0.04102
/*56  */         ffmpeg_exit(1);                                                                                                                       // (13) 0.02734
/*58  */     }                                                                                                                                         // (26) 0.007812
/*60  */     if (audio_sample_rate) {                                                                                                                  // (18) 0.02344
/*62  */         snprintf(buf, sizeof(buf), "%d", audio_sample_rate);                                                                                  // (5) 0.04883
/*64  */         av_dict_set(&format_opts, "sample_rate", buf, 0);                                                                                     // (4) 0.05273
/*66  */     }                                                                                                                                         // 0.0
/*68  */     if (audio_channels) {                                                                                                                     // 0.0
/*70  */         snprintf(buf, sizeof(buf), "%d", audio_channels);                                                                                     // 0.0
/*72  */         av_dict_set(&format_opts, "channels", buf, 0);                                                                                        // 0.0
/*74  */     }                                                                                                                                         // 0.0
/*76  */     if (frame_rate.num) {                                                                                                                     // 0.0
/*78  */         snprintf(buf, sizeof(buf), "%d/%d", frame_rate.num, frame_rate.den);                                                                  // 0.0
/*80  */         av_dict_set(&format_opts, "framerate", buf, 0);                                                                                       // 0.0
/*82  */     }                                                                                                                                         // 0.0
/*84  */     if (frame_width && frame_height) {                                                                                                        // 0.0
/*86  */         snprintf(buf, sizeof(buf), "%dx%d", frame_width, frame_height);                                                                       // 0.0
/*88  */         av_dict_set(&format_opts, "video_size", buf, 0);                                                                                      // 0.0
/*90  */     }                                                                                                                                         // 0.0
/*92  */     if (frame_pix_fmt != PIX_FMT_NONE)                                                                                                        // 0.0
/*94  */         av_dict_set(&format_opts, "pixel_format", av_get_pix_fmt_name(frame_pix_fmt), 0);                                                     // 0.0
/*98  */     ic->video_codec_id   =                                                                                                                    // 0.0
/*100 */         find_codec_or_die(video_codec_name   , AVMEDIA_TYPE_VIDEO   , 0);                                                                     // 0.0
/*102 */     ic->audio_codec_id   =                                                                                                                    // 0.0
/*104 */         find_codec_or_die(audio_codec_name   , AVMEDIA_TYPE_AUDIO   , 0);                                                                     // 0.0
/*106 */     ic->subtitle_codec_id=                                                                                                                    // 0.0
/*108 */         find_codec_or_die(subtitle_codec_name, AVMEDIA_TYPE_SUBTITLE, 0);                                                                     // 0.0
/*110 */     ic->flags |= AVFMT_FLAG_NONBLOCK;                                                                                                         // 0.0
/*114 */     /* open the input file with generic libav function */                                                                                     // 0.0
/*116 */     err = avformat_open_input(&ic, filename, file_iformat, &format_opts);                                                                     // 0.0
/*118 */     if (err < 0) {                                                                                                                            // 0.0
/*120 */         print_error(filename, err);                                                                                                           // 0.0
/*122 */         ffmpeg_exit(1);                                                                                                                       // 0.0
/*124 */     }                                                                                                                                         // 0.0
/*126 */     assert_avoptions(format_opts);                                                                                                            // 0.0
/*130 */     if(opt_programid) {                                                                                                                       // 0.0
/*132 */         int i, j;                                                                                                                             // 0.0
/*134 */         int found=0;                                                                                                                          // 0.0
/*136 */         for(i=0; i<ic->nb_streams; i++){                                                                                                      // 0.0
/*138 */             ic->streams[i]->discard= AVDISCARD_ALL;                                                                                           // 0.0
/*140 */         }                                                                                                                                     // 0.0
/*142 */         for(i=0; i<ic->nb_programs; i++){                                                                                                     // 0.0
/*144 */             AVProgram *p= ic->programs[i];                                                                                                    // 0.0
/*146 */             if(p->id != opt_programid){                                                                                                       // 0.0
/*148 */                 p->discard = AVDISCARD_ALL;                                                                                                   // 0.0
/*150 */             }else{                                                                                                                            // 0.0
/*152 */                 found=1;                                                                                                                      // 0.0
/*154 */                 for(j=0; j<p->nb_stream_indexes; j++){                                                                                        // 0.0
/*156 */                     ic->streams[p->stream_index[j]]->discard= AVDISCARD_DEFAULT;                                                              // 0.0
/*158 */                 }                                                                                                                             // 0.0
/*160 */             }                                                                                                                                 // 0.0
/*162 */         }                                                                                                                                     // 0.0
/*164 */         if(!found){                                                                                                                           // 0.0
/*166 */             fprintf(stderr, "Specified program id not found\n");                                                                              // 0.0
/*168 */             ffmpeg_exit(1);                                                                                                                   // 0.0
/*170 */         }                                                                                                                                     // 0.0
/*172 */         opt_programid=0;                                                                                                                      // 0.0
/*174 */     }                                                                                                                                         // 0.0
/*178 */     if (loop_input) {                                                                                                                         // 0.0
/*180 */         av_log(NULL, AV_LOG_WARNING, "-loop_input is deprecated, use -loop 1\n");                                                             // 0.0
/*182 */         ic->loop_input = loop_input;                                                                                                          // 0.0
/*184 */     }                                                                                                                                         // 0.0
/*188 */     /* Set AVCodecContext options for avformat_find_stream_info */                                                                            // 0.0
/*190 */     opts = setup_find_stream_info_opts(ic, codec_opts);                                                                                       // 0.0
/*192 */     orig_nb_streams = ic->nb_streams;                                                                                                         // 0.0
/*196 */     /* If not enough info to get the stream parameters, we decode the                                                                         // 0.0
/*198 */        first frames to get it. (used in mpeg case for example) */                                                                             // 0.0
/*200 */     ret = avformat_find_stream_info(ic, opts);                                                                                                // 0.0
/*202 */     if (ret < 0 && verbose >= 0) {                                                                                                            // 0.0
/*204 */         fprintf(stderr, "%s: could not find codec parameters\n", filename);                                                                   // 0.0
/*206 */         av_close_input_file(ic);                                                                                                              // 0.0
/*208 */         ffmpeg_exit(1);                                                                                                                       // 0.0
/*210 */     }                                                                                                                                         // 0.0
/*214 */     timestamp = start_time;                                                                                                                   // 0.0
/*216 */     /* add the stream start time */                                                                                                           // 0.0
/*218 */     if (ic->start_time != AV_NOPTS_VALUE)                                                                                                     // 0.0
/*220 */         timestamp += ic->start_time;                                                                                                          // 0.0
/*224 */     /* if seeking requested, we execute it */                                                                                                 // 0.0
/*226 */     if (start_time != 0) {                                                                                                                    // 0.0
/*228 */         ret = av_seek_frame(ic, -1, timestamp, AVSEEK_FLAG_BACKWARD);                                                                         // 0.0
/*230 */         if (ret < 0) {                                                                                                                        // 0.0
/*232 */             fprintf(stderr, "%s: could not seek to position %0.3f\n",                                                                         // 0.0
/*234 */                     filename, (double)timestamp / AV_TIME_BASE);                                                                              // 0.0
/*236 */         }                                                                                                                                     // 0.0
/*238 */         /* reset seek info */                                                                                                                 // 0.0
/*240 */         start_time = 0;                                                                                                                       // 0.0
/*242 */     }                                                                                                                                         // 0.0
/*246 */     /* update the current parameters so that they match the one of the input stream */                                                        // 0.0
/*248 */     for(i=0;i<ic->nb_streams;i++) {                                                                                                           // 0.0
/*250 */         AVStream *st = ic->streams[i];                                                                                                        // 0.0
/*252 */         AVCodecContext *dec = st->codec;                                                                                                      // 0.0
/*254 */         InputStream *ist;                                                                                                                     // 0.0
/*258 */         dec->thread_count = thread_count;                                                                                                     // 0.0
/*262 */         input_streams = grow_array(input_streams, sizeof(*input_streams), &nb_input_streams, nb_input_streams + 1);                           // 0.0
/*264 */         ist = &input_streams[nb_input_streams - 1];                                                                                           // 0.0
/*266 */         ist->st = st;                                                                                                                         // 0.0
/*268 */         ist->file_index = nb_input_files;                                                                                                     // 0.0
/*270 */         ist->discard = 1;                                                                                                                     // 0.0
/*272 */         ist->opts = filter_codec_opts(codec_opts, ist->st->codec->codec_id, 0);                                                               // 0.0
/*276 */         if (i < nb_ts_scale)                                                                                                                  // 0.0
/*278 */             ist->ts_scale = ts_scale[i];                                                                                                      // 0.0
/*282 */         switch (dec->codec_type) {                                                                                                            // 0.0
/*284 */         case AVMEDIA_TYPE_AUDIO:                                                                                                              // 0.0
/*286 */             ist->dec = avcodec_find_decoder_by_name(audio_codec_name);                                                                        // 0.0
/*288 */             if(!ist->dec)                                                                                                                     // 0.0
/*290 */                 ist->dec = avcodec_find_decoder(dec->codec_id);                                                                               // 0.0
/*292 */             if(audio_disable)                                                                                                                 // 0.0
/*294 */                 st->discard= AVDISCARD_ALL;                                                                                                   // 0.0
/*296 */             break;                                                                                                                            // 0.0
/*298 */         case AVMEDIA_TYPE_VIDEO:                                                                                                              // 0.0
/*300 */             ist->dec= avcodec_find_decoder_by_name(video_codec_name);                                                                         // 0.0
/*302 */             if(!ist->dec)                                                                                                                     // 0.0
/*304 */                 ist->dec = avcodec_find_decoder(dec->codec_id);                                                                               // 0.0
/*306 */             rfps      = ic->streams[i]->r_frame_rate.num;                                                                                     // 0.0
/*308 */             rfps_base = ic->streams[i]->r_frame_rate.den;                                                                                     // 0.0
/*310 */             if (dec->lowres) {                                                                                                                // 0.0
/*312 */                 dec->flags |= CODEC_FLAG_EMU_EDGE;                                                                                            // 0.0
/*314 */             }                                                                                                                                 // 0.0
/*316 */             if(me_threshold)                                                                                                                  // 0.0
/*318 */                 dec->debug |= FF_DEBUG_MV;                                                                                                    // 0.0
/*322 */             if (dec->time_base.den != rfps*dec->ticks_per_frame || dec->time_base.num != rfps_base) {                                         // 0.0
/*326 */                 if (verbose >= 0)                                                                                                             // 0.0
/*328 */                     fprintf(stderr,"\nSeems stream %d codec frame rate differs from container frame rate: %2.2f (%d/%d) -> %2.2f (%d/%d)\n",  // 0.0
/*330 */                             i, (float)dec->time_base.den / dec->time_base.num, dec->time_base.den, dec->time_base.num,                        // 0.0
/*334 */                     (float)rfps / rfps_base, rfps, rfps_base);                                                                                // 0.0
/*336 */             }                                                                                                                                 // 0.0
/*340 */             if(video_disable)                                                                                                                 // 0.0
/*342 */                 st->discard= AVDISCARD_ALL;                                                                                                   // 0.0
/*344 */             else if(video_discard)                                                                                                            // 0.0
/*346 */                 st->discard= video_discard;                                                                                                   // 0.0
/*348 */             break;                                                                                                                            // 0.0
/*350 */         case AVMEDIA_TYPE_DATA:                                                                                                               // 0.0
/*352 */             break;                                                                                                                            // 0.0
/*354 */         case AVMEDIA_TYPE_SUBTITLE:                                                                                                           // 0.0
/*356 */             ist->dec = avcodec_find_decoder_by_name(subtitle_codec_name);                                                                     // 0.0
/*358 */             if(!ist->dec)                                                                                                                     // 0.0
/*360 */                 ist->dec = avcodec_find_decoder(dec->codec_id);                                                                               // 0.0
/*362 */             if(subtitle_disable)                                                                                                              // 0.0
/*364 */                 st->discard = AVDISCARD_ALL;                                                                                                  // 0.0
/*366 */             break;                                                                                                                            // 0.0
/*368 */         case AVMEDIA_TYPE_ATTACHMENT:                                                                                                         // 0.0
/*370 */         case AVMEDIA_TYPE_UNKNOWN:                                                                                                            // 0.0
/*372 */             break;                                                                                                                            // 0.0
/*374 */         default:                                                                                                                              // 0.0
/*376 */             abort();                                                                                                                          // 0.0
/*378 */         }                                                                                                                                     // 0.0
/*380 */     }                                                                                                                                         // 0.0
/*384 */     /* dump the file content */                                                                                                               // 0.0
/*386 */     if (verbose >= 0)                                                                                                                         // 0.0
/*388 */         av_dump_format(ic, nb_input_files, filename, 0);                                                                                      // 0.0
/*392 */     input_files = grow_array(input_files, sizeof(*input_files), &nb_input_files, nb_input_files + 1);                                         // 0.0
/*394 */     input_files[nb_input_files - 1].ctx        = ic;                                                                                          // 0.0
/*396 */     input_files[nb_input_files - 1].ist_index  = nb_input_streams - ic->nb_streams;                                                           // 0.0
/*398 */     input_files[nb_input_files - 1].ts_offset  = input_ts_offset - (copy_ts ? 0 : timestamp);                                                 // 0.0
/*402 */     top_field_first = -1;                                                                                                                     // 0.0
/*404 */     frame_rate    = (AVRational){0, 0};                                                                                                       // 0.0
/*406 */     frame_pix_fmt = PIX_FMT_NONE;                                                                                                             // 0.0
/*408 */     frame_height = 0;                                                                                                                         // 0.0
/*410 */     frame_width  = 0;                                                                                                                         // 0.0
/*412 */     audio_sample_rate = 0;                                                                                                                    // 0.0
/*414 */     audio_channels    = 0;                                                                                                                    // 0.0
/*416 */     audio_sample_fmt  = AV_SAMPLE_FMT_NONE;                                                                                                   // 0.0
/*418 */     av_freep(&ts_scale);                                                                                                                      // 0.0
/*420 */     nb_ts_scale = 0;                                                                                                                          // 0.0
/*424 */     for (i = 0; i < orig_nb_streams; i++)                                                                                                     // 0.0
/*426 */         av_dict_free(&opts[i]);                                                                                                               // 0.0
/*428 */     av_freep(&opts);                                                                                                                          // 0.0
/*430 */     av_freep(&video_codec_name);                                                                                                              // 0.0
/*432 */     av_freep(&audio_codec_name);                                                                                                              // 0.0
/*434 */     av_freep(&subtitle_codec_name);                                                                                                           // 0.0
/*436 */     uninit_opts();                                                                                                                            // 0.0
/*438 */     init_opts();                                                                                                                              // 0.0
/*440 */     return 0;                                                                                                                                 // 0.0
/*442 */ }                                                                                                                                             // 0.0
