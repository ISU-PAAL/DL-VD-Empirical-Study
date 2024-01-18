// commit message FFmpeg@47219e1c0c (target=1, prob=0.46198002, correct=False): avconv: fix uninitialized variable
/*0   */ static void do_video_out(AVFormatContext *s,                                                                                                        // (14) 0.02734
/*2   */                          OutputStream *ost,                                                                                                         // (5) 0.05662
/*4   */                          InputStream *ist,                                                                                                          // (6) 0.05662
/*6   */                          AVFrame *in_picture,                                                                                                       // (3) 0.06053
/*8   */                          int *frame_size, float quality)                                                                                            // (1) 0.06445
/*10  */ {                                                                                                                                                   // (23) 0.001972
/*12  */     int nb_frames, i, ret, av_unused resample_changed;                                                                                              // (8) 0.04297
/*14  */     AVFrame *final_picture, *formatted_picture;                                                                                                     // (13) 0.03124
/*16  */     AVCodecContext *enc, *dec;                                                                                                                      // (17) 0.02538
/*18  */     double sync_ipts;                                                                                                                               // (22) 0.01757
/*22  */     enc = ost->st->codec;                                                                                                                           // (18) 0.02343
/*24  */     dec = ist->st->codec;                                                                                                                           // (16) 0.02538
/*28  */     sync_ipts = get_sync_ipts(ost) / av_q2d(enc->time_base);                                                                                        // (4) 0.05858
/*32  */     /* by default, we output a single frame */                                                                                                      // (15) 0.02539
/*34  */     nb_frames = 1;                                                                                                                                  // (20) 0.01953
/*38  */     *frame_size = 0;                                                                                                                                // (21) 0.01953
/*42  */     if(video_sync_method){                                                                                                                          // (19) 0.02148
/*44  */         double vdelta = sync_ipts - ost->sync_opts;                                                                                                 // (7) 0.04687
/*46  */         //FIXME set to 0.5 after we fix some dts/pts bugs like in avidec.c                                                                          // (2) 0.06257
/*48  */         if (vdelta < -1.1)                                                                                                                          // (12) 0.03319
/*50  */             nb_frames = 0;                                                                                                                          // (11) 0.03515
/*52  */         else if (video_sync_method == 2 || (video_sync_method<0 && (s->oformat->flags & AVFMT_VARIABLE_FPS))){                                      // (0) 0.09372
/*54  */             if(vdelta<=-0.6){                                                                                                                       // (10) 0.041
/*56  */                 nb_frames=0;                                                                                                                        // (9) 0.04296
/*58  */             }else if(vdelta>0.6)                                                                                                                    // 0.0
/*60  */                 ost->sync_opts= lrintf(sync_ipts);                                                                                                  // 0.0
/*62  */         }else if (vdelta > 1.1)                                                                                                                     // 0.0
/*64  */             nb_frames = lrintf(vdelta);                                                                                                             // 0.0
/*66  */ //fprintf(stderr, "vdelta:%f, ost->sync_opts:%"PRId64", ost->sync_ipts:%f nb_frames:%d\n", vdelta, ost->sync_opts, get_sync_ipts(ost), nb_frames);  // 0.0
/*68  */         if (nb_frames == 0){                                                                                                                        // 0.0
/*70  */             ++nb_frames_drop;                                                                                                                       // 0.0
/*72  */             if (verbose>2)                                                                                                                          // 0.0
/*74  */                 fprintf(stderr, "*** drop!\n");                                                                                                     // 0.0
/*76  */         }else if (nb_frames > 1) {                                                                                                                  // 0.0
/*78  */             nb_frames_dup += nb_frames - 1;                                                                                                         // 0.0
/*80  */             if (verbose>2)                                                                                                                          // 0.0
/*82  */                 fprintf(stderr, "*** %d dup!\n", nb_frames-1);                                                                                      // 0.0
/*84  */         }                                                                                                                                           // 0.0
/*86  */     }else                                                                                                                                           // 0.0
/*88  */         ost->sync_opts= lrintf(sync_ipts);                                                                                                          // 0.0
/*92  */     nb_frames= FFMIN(nb_frames, max_frames[AVMEDIA_TYPE_VIDEO] - ost->frame_number);                                                                // 0.0
/*94  */     if (nb_frames <= 0)                                                                                                                             // 0.0
/*96  */         return;                                                                                                                                     // 0.0
/*100 */     formatted_picture = in_picture;                                                                                                                 // 0.0
/*102 */     final_picture = formatted_picture;                                                                                                              // 0.0
/*106 */ #if !CONFIG_AVFILTER                                                                                                                                // 0.0
/*108 */     resample_changed = ost->resample_width   != dec->width  ||                                                                                      // 0.0
/*110 */                        ost->resample_height  != dec->height ||                                                                                      // 0.0
/*112 */                        ost->resample_pix_fmt != dec->pix_fmt;                                                                                       // 0.0
/*116 */     if (resample_changed) {                                                                                                                         // 0.0
/*118 */         av_log(NULL, AV_LOG_INFO,                                                                                                                   // 0.0
/*120 */                "Input stream #%d.%d frame changed from size:%dx%d fmt:%s to size:%dx%d fmt:%s\n",                                                   // 0.0
/*122 */                ist->file_index, ist->st->index,                                                                                                     // 0.0
/*124 */                ost->resample_width, ost->resample_height, av_get_pix_fmt_name(ost->resample_pix_fmt),                                               // 0.0
/*126 */                dec->width         , dec->height         , av_get_pix_fmt_name(dec->pix_fmt));                                                       // 0.0
/*128 */         ost->resample_width   = dec->width;                                                                                                         // 0.0
/*130 */         ost->resample_height  = dec->height;                                                                                                        // 0.0
/*132 */         ost->resample_pix_fmt = dec->pix_fmt;                                                                                                       // 0.0
/*134 */     }                                                                                                                                               // 0.0
/*138 */     ost->video_resample = dec->width   != enc->width  ||                                                                                            // 0.0
/*140 */                           dec->height  != enc->height ||                                                                                            // 0.0
/*142 */                           dec->pix_fmt != enc->pix_fmt;                                                                                             // 0.0
/*146 */     if (ost->video_resample) {                                                                                                                      // 0.0
/*148 */         final_picture = &ost->resample_frame;                                                                                                       // 0.0
/*150 */         if (!ost->img_resample_ctx || resample_changed) {                                                                                           // 0.0
/*152 */             /* initialize the destination picture */                                                                                                // 0.0
/*154 */             if (!ost->resample_frame.data[0]) {                                                                                                     // 0.0
/*156 */                 avcodec_get_frame_defaults(&ost->resample_frame);                                                                                   // 0.0
/*158 */                 if (avpicture_alloc((AVPicture *)&ost->resample_frame, enc->pix_fmt,                                                                // 0.0
/*160 */                                     enc->width, enc->height)) {                                                                                     // 0.0
/*162 */                     fprintf(stderr, "Cannot allocate temp picture, check pix fmt\n");                                                               // 0.0
/*164 */                     exit_program(1);                                                                                                                // 0.0
/*166 */                 }                                                                                                                                   // 0.0
/*168 */             }                                                                                                                                       // 0.0
/*170 */             /* initialize a new scaler context */                                                                                                   // 0.0
/*172 */             sws_freeContext(ost->img_resample_ctx);                                                                                                 // 0.0
/*174 */             ost->img_resample_ctx = sws_getContext(dec->width, dec->height, dec->pix_fmt,                                                           // 0.0
/*176 */                                                    enc->width, enc->height, enc->pix_fmt,                                                           // 0.0
/*178 */                                                    ost->sws_flags, NULL, NULL, NULL);                                                               // 0.0
/*180 */             if (ost->img_resample_ctx == NULL) {                                                                                                    // 0.0
/*182 */                 fprintf(stderr, "Cannot get resampling context\n");                                                                                 // 0.0
/*184 */                 exit_program(1);                                                                                                                    // 0.0
/*186 */             }                                                                                                                                       // 0.0
/*188 */         }                                                                                                                                           // 0.0
/*190 */         sws_scale(ost->img_resample_ctx, formatted_picture->data, formatted_picture->linesize,                                                      // 0.0
/*192 */               0, ost->resample_height, final_picture->data, final_picture->linesize);                                                               // 0.0
/*194 */     }                                                                                                                                               // 0.0
/*196 */ #else                                                                                                                                               // 0.0
/*198 */     if (resample_changed) {                                                                                                                         // 0.0
/*200 */         avfilter_graph_free(&ost->graph);                                                                                                           // 0.0
/*202 */         if (configure_video_filters(ist, ost)) {                                                                                                    // 0.0
/*204 */             fprintf(stderr, "Error reinitialising filters!\n");                                                                                     // 0.0
/*206 */             exit_program(1);                                                                                                                        // 0.0
/*208 */         }                                                                                                                                           // 0.0
/*210 */     }                                                                                                                                               // 0.0
/*212 */ #endif                                                                                                                                              // 0.0
/*214 */     if (resample_changed) {                                                                                                                         // 0.0
/*216 */         ost->resample_width   = dec->width;                                                                                                         // 0.0
/*218 */         ost->resample_height  = dec->height;                                                                                                        // 0.0
/*220 */         ost->resample_pix_fmt = dec->pix_fmt;                                                                                                       // 0.0
/*222 */     }                                                                                                                                               // 0.0
/*226 */     /* duplicates frame if needed */                                                                                                                // 0.0
/*228 */     for(i=0;i<nb_frames;i++) {                                                                                                                      // 0.0
/*230 */         AVPacket pkt;                                                                                                                               // 0.0
/*232 */         av_init_packet(&pkt);                                                                                                                       // 0.0
/*234 */         pkt.stream_index= ost->index;                                                                                                               // 0.0
/*238 */         if (s->oformat->flags & AVFMT_RAWPICTURE) {                                                                                                 // 0.0
/*240 */             /* raw pictures are written as AVPicture structure to                                                                                   // 0.0
/*242 */                avoid any copies. We support temorarily the older                                                                                    // 0.0
/*244 */                method. */                                                                                                                           // 0.0
/*246 */             AVFrame* old_frame = enc->coded_frame;                                                                                                  // 0.0
/*248 */             enc->coded_frame = dec->coded_frame; //FIXME/XXX remove this hack                                                                       // 0.0
/*250 */             pkt.data= (uint8_t *)final_picture;                                                                                                     // 0.0
/*252 */             pkt.size=  sizeof(AVPicture);                                                                                                           // 0.0
/*254 */             pkt.pts= av_rescale_q(ost->sync_opts, enc->time_base, ost->st->time_base);                                                              // 0.0
/*256 */             pkt.flags |= AV_PKT_FLAG_KEY;                                                                                                           // 0.0
/*260 */             write_frame(s, &pkt, ost->st->codec, ost->bitstream_filters);                                                                           // 0.0
/*262 */             enc->coded_frame = old_frame;                                                                                                           // 0.0
/*264 */         } else {                                                                                                                                    // 0.0
/*266 */             AVFrame big_picture;                                                                                                                    // 0.0
/*270 */             big_picture= *final_picture;                                                                                                            // 0.0
/*272 */             /* better than nothing: use input picture interlaced                                                                                    // 0.0
/*274 */                settings */                                                                                                                          // 0.0
/*276 */             big_picture.interlaced_frame = in_picture->interlaced_frame;                                                                            // 0.0
/*278 */             if (ost->st->codec->flags & (CODEC_FLAG_INTERLACED_DCT|CODEC_FLAG_INTERLACED_ME)) {                                                     // 0.0
/*280 */                 if(top_field_first == -1)                                                                                                           // 0.0
/*282 */                     big_picture.top_field_first = in_picture->top_field_first;                                                                      // 0.0
/*284 */                 else                                                                                                                                // 0.0
/*286 */                     big_picture.top_field_first = top_field_first;                                                                                  // 0.0
/*288 */             }                                                                                                                                       // 0.0
/*292 */             /* handles sameq here. This is not correct because it may                                                                               // 0.0
/*294 */                not be a global option */                                                                                                            // 0.0
/*296 */             big_picture.quality = quality;                                                                                                          // 0.0
/*298 */             if(!me_threshold)                                                                                                                       // 0.0
/*300 */                 big_picture.pict_type = 0;                                                                                                          // 0.0
/*302 */ //            big_picture.pts = AV_NOPTS_VALUE;                                                                                                     // 0.0
/*304 */             big_picture.pts= ost->sync_opts;                                                                                                        // 0.0
/*306 */ //            big_picture.pts= av_rescale(ost->sync_opts, AV_TIME_BASE*(int64_t)enc->time_base.num, enc->time_base.den);                            // 0.0
/*308 */ //av_log(NULL, AV_LOG_DEBUG, "%"PRId64" -> encoder\n", ost->sync_opts);                                                                             // 0.0
/*310 */             if (ost->forced_kf_index < ost->forced_kf_count &&                                                                                      // 0.0
/*312 */                 big_picture.pts >= ost->forced_kf_pts[ost->forced_kf_index]) {                                                                      // 0.0
/*314 */                 big_picture.pict_type = AV_PICTURE_TYPE_I;                                                                                          // 0.0
/*316 */                 ost->forced_kf_index++;                                                                                                             // 0.0
/*318 */             }                                                                                                                                       // 0.0
/*320 */             ret = avcodec_encode_video(enc,                                                                                                         // 0.0
/*322 */                                        bit_buffer, bit_buffer_size,                                                                                 // 0.0
/*324 */                                        &big_picture);                                                                                               // 0.0
/*326 */             if (ret < 0) {                                                                                                                          // 0.0
/*328 */                 fprintf(stderr, "Video encoding failed\n");                                                                                         // 0.0
/*330 */                 exit_program(1);                                                                                                                    // 0.0
/*332 */             }                                                                                                                                       // 0.0
/*336 */             if(ret>0){                                                                                                                              // 0.0
/*338 */                 pkt.data= bit_buffer;                                                                                                               // 0.0
/*340 */                 pkt.size= ret;                                                                                                                      // 0.0
/*342 */                 if(enc->coded_frame->pts != AV_NOPTS_VALUE)                                                                                         // 0.0
/*344 */                     pkt.pts= av_rescale_q(enc->coded_frame->pts, enc->time_base, ost->st->time_base);                                               // 0.0
/*346 */ /*av_log(NULL, AV_LOG_DEBUG, "encoder -> %"PRId64"/%"PRId64"\n",                                                                                    // 0.0
/*348 */    pkt.pts != AV_NOPTS_VALUE ? av_rescale(pkt.pts, enc->time_base.den, AV_TIME_BASE*(int64_t)enc->time_base.num) : -1,                              // 0.0
/*350 */    pkt.dts != AV_NOPTS_VALUE ? av_rescale(pkt.dts, enc->time_base.den, AV_TIME_BASE*(int64_t)enc->time_base.num) : -1);*/                           // 0.0
/*354 */                 if(enc->coded_frame->key_frame)                                                                                                     // 0.0
/*356 */                     pkt.flags |= AV_PKT_FLAG_KEY;                                                                                                   // 0.0
/*358 */                 write_frame(s, &pkt, ost->st->codec, ost->bitstream_filters);                                                                       // 0.0
/*360 */                 *frame_size = ret;                                                                                                                  // 0.0
/*362 */                 video_size += ret;                                                                                                                  // 0.0
/*364 */                 //fprintf(stderr,"\nFrame: %3d size: %5d type: %d",                                                                                 // 0.0
/*366 */                 //        enc->frame_number-1, ret, enc->pict_type);                                                                                // 0.0
/*368 */                 /* if two pass, output log */                                                                                                       // 0.0
/*370 */                 if (ost->logfile && enc->stats_out) {                                                                                               // 0.0
/*372 */                     fprintf(ost->logfile, "%s", enc->stats_out);                                                                                    // 0.0
/*374 */                 }                                                                                                                                   // 0.0
/*376 */             }                                                                                                                                       // 0.0
/*378 */         }                                                                                                                                           // 0.0
/*380 */         ost->sync_opts++;                                                                                                                           // 0.0
/*382 */         ost->frame_number++;                                                                                                                        // 0.0
/*384 */     }                                                                                                                                               // 0.0
/*386 */ }                                                                                                                                                   // 0.0
