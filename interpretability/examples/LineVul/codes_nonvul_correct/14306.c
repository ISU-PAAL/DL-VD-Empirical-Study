// commit message FFmpeg@f1ffb01ee9 (target=0, prob=0.3624788, correct=True): avplay: use libavresample for sample format conversion and channel mixing
/*0   */ static int synchronize_audio(VideoState *is, short *samples,                                            // (14) 0.0332
/*2   */                              int samples_size1, double pts)                                             // (1) 0.07227
/*4   */ {                                                                                                       // (20) 0.001953
/*6   */     int n, samples_size;                                                                                // (18) 0.01953
/*8   */     double ref_clock;                                                                                   // (19) 0.01562
/*12  */     n = 2 * is->audio_st->codec->channels;                                                              // (12) 0.03711
/*14  */     samples_size = samples_size1;                                                                       // (17) 0.02344
/*18  */     /* if not master, then we try to remove or add samples to correct the clock */                      // (11) 0.04102
/*20  */     if (((is->av_sync_type == AV_SYNC_VIDEO_MASTER && is->video_st) ||                                  // (3) 0.06055
/*22  */          is->av_sync_type == AV_SYNC_EXTERNAL_CLOCK)) {                                                 // (4) 0.05664
/*24  */         double diff, avg_diff;                                                                          // (15) 0.02734
/*26  */         int wanted_size, min_size, max_size, nb_samples;                                                // (5) 0.05078
/*30  */         ref_clock = get_master_clock(is);                                                               // (13) 0.03711
/*32  */         diff = get_audio_clock(is) - ref_clock;                                                         // (10) 0.04297
/*36  */         if (diff < AV_NOSYNC_THRESHOLD) {                                                               // (8) 0.04687
/*38  */             is->audio_diff_cum = diff + is->audio_diff_avg_coef * is->audio_diff_cum;                   // (0) 0.08008
/*40  */             if (is->audio_diff_avg_count < AUDIO_DIFF_AVG_NB) {                                         // (2) 0.07031
/*42  */                 /* not enough measures to have a correct estimate */                                    // (7) 0.04883
/*44  */                 is->audio_diff_avg_count++;                                                             // (6) 0.05078
/*46  */             } else {                                                                                    // (16) 0.02734
/*48  */                 /* estimate the A-V difference */                                                       // (9) 0.04492
/*50  */                 avg_diff = is->audio_diff_cum * (1.0 - is->audio_diff_avg_coef);                        // 0.0
/*54  */                 if (fabs(avg_diff) >= is->audio_diff_threshold) {                                       // 0.0
/*56  */                     wanted_size = samples_size + ((int)(diff * is->audio_st->codec->sample_rate) * n);  // 0.0
/*58  */                     nb_samples = samples_size / n;                                                      // 0.0
/*62  */                     min_size = ((nb_samples * (100 - SAMPLE_CORRECTION_PERCENT_MAX)) / 100) * n;        // 0.0
/*64  */                     max_size = ((nb_samples * (100 + SAMPLE_CORRECTION_PERCENT_MAX)) / 100) * n;        // 0.0
/*66  */                     if (wanted_size < min_size)                                                         // 0.0
/*68  */                         wanted_size = min_size;                                                         // 0.0
/*70  */                     else if (wanted_size > max_size)                                                    // 0.0
/*72  */                         wanted_size = max_size;                                                         // 0.0
/*76  */                     /* add or remove samples to correction the synchro */                               // 0.0
/*78  */                     if (wanted_size < samples_size) {                                                   // 0.0
/*80  */                         /* remove samples */                                                            // 0.0
/*82  */                         samples_size = wanted_size;                                                     // 0.0
/*84  */                     } else if (wanted_size > samples_size) {                                            // 0.0
/*86  */                         uint8_t *samples_end, *q;                                                       // 0.0
/*88  */                         int nb;                                                                         // 0.0
/*92  */                         /* add samples */                                                               // 0.0
/*94  */                         nb = (samples_size - wanted_size);                                              // 0.0
/*96  */                         samples_end = (uint8_t *)samples + samples_size - n;                            // 0.0
/*98  */                         q = samples_end + n;                                                            // 0.0
/*100 */                         while (nb > 0) {                                                                // 0.0
/*102 */                             memcpy(q, samples_end, n);                                                  // 0.0
/*104 */                             q += n;                                                                     // 0.0
/*106 */                             nb -= n;                                                                    // 0.0
/*108 */                         }                                                                               // 0.0
/*110 */                         samples_size = wanted_size;                                                     // 0.0
/*112 */                     }                                                                                   // 0.0
/*114 */                 }                                                                                       // 0.0
/*116 */                 av_dlog(NULL, "diff=%f adiff=%f sample_diff=%d apts=%0.3f vpts=%0.3f %f\n",             // 0.0
/*118 */                         diff, avg_diff, samples_size - samples_size1,                                   // 0.0
/*120 */                         is->audio_clock, is->video_clock, is->audio_diff_threshold);                    // 0.0
/*122 */             }                                                                                           // 0.0
/*124 */         } else {                                                                                        // 0.0
/*126 */             /* too big difference : may be initial PTS errors, so                                       // 0.0
/*128 */                reset A-V filter */                                                                      // 0.0
/*130 */             is->audio_diff_avg_count = 0;                                                               // 0.0
/*132 */             is->audio_diff_cum       = 0;                                                               // 0.0
/*134 */         }                                                                                               // 0.0
/*136 */     }                                                                                                   // 0.0
/*140 */     return samples_size;                                                                                // 0.0
/*142 */ }                                                                                                       // 0.0
