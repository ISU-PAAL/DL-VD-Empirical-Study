// commit message FFmpeg@4189fe11ff (target=1, prob=0.6145663, correct=True): avformat/vobsub: fix invalid sub queue access while seeking.
/*0  */ static int vobsub_read_seek(AVFormatContext *s, int stream_index,                   // (10) 0.04102
/*2  */                             int64_t min_ts, int64_t ts, int64_t max_ts, int flags)  // (0) 0.1016
/*4  */ {                                                                                   // (15) 0.001954
/*6  */     MpegDemuxContext *vobsub = s->priv_data;                                        // (12) 0.03711
/*10 */     /* Rescale requested timestamps based on the first stream (timebase is the      // (11) 0.03906
/*12 */      * same for all subtitles stream within a .idx/.sub). Rescaling is done just    // (8) 0.04687
/*14 */      * like in avformat_seek_file(). */                                             // (13) 0.0293
/*16 */     if (stream_index == -1 && s->nb_streams != 1) {                                 // (9) 0.04297
/*18 */         int i, ret = 0;                                                             // (14) 0.02734
/*20 */         AVRational time_base = s->streams[0]->time_base;                            // (7) 0.05078
/*22 */         ts = av_rescale_q(ts, AV_TIME_BASE_Q, time_base);                           // (4) 0.06055
/*24 */         min_ts = av_rescale_rnd(min_ts, time_base.den,                              // (5) 0.05664
/*26 */                                 time_base.num * (int64_t)AV_TIME_BASE,              // (2) 0.09766
/*28 */                                 AV_ROUND_UP   | AV_ROUND_PASS_MINMAX);              // (3) 0.09766
/*30 */         max_ts = av_rescale_rnd(max_ts, time_base.den,                              // (6) 0.05664
/*32 */                                 time_base.num * (int64_t)AV_TIME_BASE,              // (1) 0.09766
/*34 */                                 AV_ROUND_DOWN | AV_ROUND_PASS_MINMAX);              // 0.0
/*36 */         for (i = 0; i < s->nb_streams; i++) {                                       // 0.0
/*38 */             int r = ff_subtitles_queue_seek(&vobsub->q[i], s, stream_index,         // 0.0
/*40 */                                             min_ts, ts, max_ts, flags);             // 0.0
/*42 */             if (r < 0)                                                              // 0.0
/*44 */                 ret = r;                                                            // 0.0
/*46 */         }                                                                           // 0.0
/*48 */         return ret;                                                                 // 0.0
/*50 */     }                                                                               // 0.0
/*56 */     return ff_subtitles_queue_seek(&vobsub->q[stream_index], s, stream_index,       // 0.0
/*58 */                                    min_ts, ts, max_ts, flags);                      // 0.0
/*60 */ }                                                                                   // 0.0
