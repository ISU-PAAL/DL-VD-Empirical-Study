// commit message FFmpeg@369cb092ec (target=1, prob=0.23387454, correct=False): avconv: add support for audio filters.
/*0  */ static OutputStream *new_audio_stream(OptionsContext *o, AVFormatContext *oc)                 // (6) 0.04895
/*2  */ {                                                                                             // (20) 0.002331
/*4  */     AVStream *st;                                                                             // (16) 0.01865
/*6  */     OutputStream *ost;                                                                        // (15) 0.01865
/*8  */     AVCodecContext *audio_enc;                                                                // (11) 0.02797
/*12 */     ost = new_output_stream(o, oc, AVMEDIA_TYPE_AUDIO);                                       // (5) 0.05828
/*14 */     st  = ost->st;                                                                            // (14) 0.02331
/*18 */     audio_enc = st->codec;                                                                    // (12) 0.02797
/*20 */     audio_enc->codec_type = AVMEDIA_TYPE_AUDIO;                                               // (7) 0.04895
/*24 */     if (!ost->stream_copy) {                                                                  // (13) 0.02797
/*26 */         char *sample_fmt = NULL;                                                              // (9) 0.0373
/*30 */         MATCH_PER_STREAM_OPT(audio_channels, i, audio_enc->channels, oc, st);                 // (3) 0.08625
/*34 */         MATCH_PER_STREAM_OPT(sample_fmts, str, sample_fmt, oc, st);                           // (4) 0.08159
/*36 */         if (sample_fmt &&                                                                     // (10) 0.03263
/*38 */             (audio_enc->sample_fmt = av_get_sample_fmt(sample_fmt)) == AV_SAMPLE_FMT_NONE) {  // (0) 0.1119
/*40 */             av_log(NULL, AV_LOG_FATAL, "Invalid sample format '%s'\n", sample_fmt);           // (1) 0.09557
/*42 */             exit_program(1);                                                                  // (8) 0.03963
/*44 */         }                                                                                     // (17) 0.01865
/*48 */         MATCH_PER_STREAM_OPT(audio_sample_rate, i, audio_enc->sample_rate, oc, st);           // (2) 0.09091
/*50 */     }                                                                                         // (19) 0.009324
/*54 */     return ost;                                                                               // (18) 0.01399
/*56 */ }                                                                                             // (21) 0.002331
