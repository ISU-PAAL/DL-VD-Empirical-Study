// commit message FFmpeg@b67f3d6575 (target=1, prob=0.73312384, correct=True): Fix ffserver-related regression (and crash) introduced in r25500. Fixes issue 2317.
/*0   */ static int read_ffserver_streams(AVFormatContext *s, const char *filename)  // (3) 0.02135
/*2   */ {                                                                           // (27) 0.0006587
/*4   */     int i, err;                                                             // (18) 0.002987
/*6   */     AVFormatContext *ic;                                                    // (12) 0.004363
/*8   */     int nopts = 0;                                                          // (25) 0.001565
/*12  */     err = av_open_input_file(&ic, filename, NULL, FFM_PACKET_SIZE, NULL);   // (5) 0.01848
/*14  */     if (err < 0)                                                            // (21) 0.002341
/*16  */         return err;                                                         // (22) 0.002292
/*18  */     /* copy stream format */                                                // (2) 0.02418
/*20  */     s->nb_streams = ic->nb_streams;                                         // (11) 0.004452
/*22  */     for(i=0;i<ic->nb_streams;i++) {                                         // (9) 0.005713
/*24  */         AVStream *st;                                                       // (14) 0.003773
/*26  */         AVCodec *codec;                                                     // (4) 0.01976
/*30  */         // FIXME: a more elegant solution is needed                         // (0) 0.72
/*32  */         st = av_mallocz(sizeof(AVStream));                                  // (1) 0.02511
/*34  */         memcpy(st, ic->streams[i], sizeof(AVStream));                       // (7) 0.006267
/*36  */         st->codec = avcodec_alloc_context();                                // (15) 0.003695
/*38  */         if (!st->codec) {                                                   // (17) 0.00334
/*40  */             print_error(filename, AVERROR(ENOMEM));                         // (8) 0.005949
/*42  */             ffmpeg_exit(1);                                                 // (6) 0.01302
/*44  */         }                                                                   // (24) 0.001838
/*46  */         avcodec_copy_context(st->codec, ic->streams[i]->codec);             // (13) 0.004178
/*48  */         s->streams[i] = st;                                                 // (20) 0.002393
/*52  */         codec = avcodec_find_encoder(st->codec->codec_id);                  // (10) 0.005606
/*54  */         if (st->codec->codec_type == AVMEDIA_TYPE_AUDIO) {                  // (16) 0.003549
/*56  */             if (audio_stream_copy) {                                        // (19) 0.002604
/*58  */                 st->stream_copy = 1;                                        // (23) 0.002133
/*60  */             } else                                                          // 0.0
/*62  */                 choose_sample_fmt(st, codec);                               // 0.0
/*64  */         } else if (st->codec->codec_type == AVMEDIA_TYPE_VIDEO) {           // 0.0
/*66  */             if (video_stream_copy) {                                        // 0.0
/*68  */                 st->stream_copy = 1;                                        // 0.0
/*70  */             } else                                                          // 0.0
/*72  */                 choose_pixel_fmt(st, codec);                                // 0.0
/*74  */         }                                                                   // (26) 0.0008467
/*78  */         if(!st->codec->thread_count)                                        // 0.0
/*80  */             st->codec->thread_count = 1;                                    // 0.0
/*82  */         if(st->codec->thread_count>1)                                       // 0.0
/*84  */             avcodec_thread_init(st->codec, st->codec->thread_count);        // 0.0
/*88  */         if(st->codec->flags & CODEC_FLAG_BITEXACT)                          // 0.0
/*90  */             nopts = 1;                                                      // 0.0
/*92  */     }                                                                       // 0.0
/*96  */     if (!nopts)                                                             // 0.0
/*98  */         s->timestamp = av_gettime();                                        // 0.0
/*102 */     av_close_input_file(ic);                                                // 0.0
/*104 */     return 0;                                                               // 0.0
/*106 */ }                                                                           // 0.0
