// commit message FFmpeg@d600b18f22 (target=1, prob=0.9991647, correct=True): avformat/utils: limit rfps to values larger than fps
/*0  */ void ff_rfps_calculate(AVFormatContext *ic)                                                                                                                                        // (12) 0.03125
/*1  */ {                                                                                                                                                                                  // (16) 0.001953
/*2  */     int i, j;                                                                                                                                                                      // (15) 0.01562
/*3  */     for (i = 0; i<ic->nb_streams; i++) {                                                                                                                                           // (8) 0.04101
/*4  */         AVStream *st = ic->streams[i];                                                                                                                                             // (10) 0.0371
/*5  */         if (st->codec->codec_type != AVMEDIA_TYPE_VIDEO)                                                                                                                           // (6) 0.05273
/*6  */         // the check for tb_unreliable() is not completely correct, since this is not about handling                                                                               // (4) 0.05667
/*7  */         // a unreliable/inexact time base, but a time base that is finer than necessary, as e.g.                                                                                   // (2) 0.06253
/*8  */         // ipmovie.c produces.                                                                                                                                                     // (14) 0.02738
/*9  */         if (tb_unreliable(st->codec) && st->info->duration_count > 15 && st->info->duration_gcd > FFMAX(1, st->time_base.den/(500LL*st->time_base.num)) && !st->r_frame_rate.num)  // (0) 0.1504
/*10 */             av_reduce(&st->r_frame_rate.num, &st->r_frame_rate.den, st->time_base.den, st->time_base.num * st->info->duration_gcd, INT_MAX);                                       // (1) 0.1289
/*11 */         if (st->info->duration_count>1 && !st->r_frame_rate.num                                                                                                                    // (5) 0.05663
/*12 */             && tb_unreliable(st->codec)) {                                                                                                                                         // (7) 0.04882
/*13 */             int num = 0;                                                                                                                                                           // (13) 0.03125
/*14 */             double best_error= 0.01;                                                                                                                                               // (9) 0.03906
/*15 */             for (j=0; j<MAX_STD_TIMEBASES; j++) {                                                                                                                                  // (3) 0.06054
/*16 */                 int k;                                                                                                                                                             // (11) 0.03515
/*17 */                 if(st->info->codec_info_duration && st->info->codec_info_duration*av_q2d(st->time_base) < (1001*12.0)/get_std_framerate(j))                                        // 0.0
/*18 */                 if(!st->info->codec_info_duration && 1.0 < (1001*12.0)/get_std_framerate(j))                                                                                       // 0.0
/*19 */                 for(k=0; k<2; k++){                                                                                                                                                // 0.0
/*20 */                     int n= st->info->duration_count;                                                                                                                               // 0.0
/*21 */                     double a= st->info->duration_error[k][0][j] / n;                                                                                                               // 0.0
/*22 */                     double error= st->info->duration_error[k][1][j]/n - a*a;                                                                                                       // 0.0
/*23 */                     if(error < best_error && best_error> 0.000000001){                                                                                                             // 0.0
/*24 */                         best_error= error;                                                                                                                                         // 0.0
/*25 */                         num = get_std_framerate(j);                                                                                                                                // 0.0
/*26 */                     }                                                                                                                                                              // 0.0
/*27 */                     if(error < 0.02)                                                                                                                                               // 0.0
/*28 */                         av_log(NULL, AV_LOG_DEBUG, "rfps: %f %f\n", get_std_framerate(j) / 12.0/1001, error);                                                                      // 0.0
/*29 */                 }                                                                                                                                                                  // 0.0
/*30 */             }                                                                                                                                                                      // 0.0
/*31 */             // do not increase frame rate by more than 1 % in order to match a standard rate.                                                                                      // 0.0
/*32 */             if (num && (!st->r_frame_rate.num || (double)num/(12*1001) < 1.01 * av_q2d(st->r_frame_rate)))                                                                         // 0.0
/*33 */                 av_reduce(&st->r_frame_rate.num, &st->r_frame_rate.den, num, 12*1001, INT_MAX);                                                                                    // 0.0
/*34 */         }                                                                                                                                                                          // 0.0
/*35 */         av_freep(&st->info->duration_error);                                                                                                                                       // 0.0
/*36 */         st->info->last_dts = AV_NOPTS_VALUE;                                                                                                                                       // 0.0
/*37 */         st->info->duration_count = 0;                                                                                                                                              // 0.0
/*38 */         st->info->rfps_duration_sum = 0;                                                                                                                                           // 0.0
/*39 */     }                                                                                                                                                                              // 0.0
/*40 */ }                                                                                                                                                                                  // 0.0
