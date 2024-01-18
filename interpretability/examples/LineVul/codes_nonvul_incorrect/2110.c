// commit message FFmpeg@17ee7b5515 (target=0, prob=0.57109714, correct=False): ffmpeg:Fix negative verbositiy Signed-off-by: Michael Niedermayer <michaelni@gmx.at>
/*0   */ static void print_report(AVFormatContext **output_files,                                                                       // (13) 0.02734
/*2   */                          AVOutputStream **ost_table, int nb_ostreams,                                                          // (0) 0.07812
/*4   */                          int is_last_report)                                                                                   // (1) 0.06055
/*6   */ {                                                                                                                              // (31) 0.001964
/*8   */     char buf[1024];                                                                                                            // (28) 0.01562
/*10  */     AVOutputStream *ost;                                                                                                       // (26) 0.01758
/*12  */     AVFormatContext *oc;                                                                                                       // (25) 0.01758
/*14  */     int64_t total_size;                                                                                                        // (22) 0.02148
/*16  */     AVCodecContext *enc;                                                                                                       // (24) 0.01953
/*18  */     int frame_number, vid, i;                                                                                                  // (14) 0.02539
/*20  */     double bitrate, ti1, pts;                                                                                                  // (18) 0.02344
/*22  */     static int64_t last_time = -1;                                                                                             // (10) 0.0293
/*24  */     static int qp_histogram[52];                                                                                               // (15) 0.02539
/*28  */     if (!is_last_report) {                                                                                                     // (19) 0.02344
/*30  */         int64_t cur_time;                                                                                                      // (11) 0.0293
/*32  */         /* display the report every 0.5 seconds */                                                                             // (6) 0.0332
/*34  */         cur_time = av_gettime();                                                                                               // (9) 0.03125
/*36  */         if (last_time == -1) {                                                                                                 // (7) 0.0332
/*38  */             last_time = cur_time;                                                                                              // (5) 0.03711
/*40  */             return;                                                                                                            // (16) 0.02539
/*42  */         }                                                                                                                      // (29) 0.01562
/*44  */         if ((cur_time - last_time) < 500000)                                                                                   // (3) 0.04101
/*46  */             return;                                                                                                            // (17) 0.02539
/*48  */         last_time = cur_time;                                                                                                  // (12) 0.0293
/*50  */     }                                                                                                                          // (30) 0.007812
/*56  */     oc = output_files[0];                                                                                                      // (21) 0.02344
/*60  */     total_size = avio_size(oc->pb);                                                                                            // (8) 0.03125
/*62  */     if(total_size<0) // FIXME improve avio_size() so it works with non seekable output too                                     // (2) 0.05664
/*64  */         total_size= avio_tell(oc->pb);                                                                                         // (4) 0.03906
/*68  */     buf[0] = '\0';                                                                                                             // (20) 0.02344
/*70  */     ti1 = 1e10;                                                                                                                // (23) 0.01953
/*72  */     vid = 0;                                                                                                                   // (27) 0.01562
/*74  */     for(i=0;i<nb_ostreams;i++) {                                                                                               // 0.0
/*76  */         float q= -1;                                                                                                           // 0.0
/*78  */         ost = ost_table[i];                                                                                                    // 0.0
/*80  */         enc = ost->st->codec;                                                                                                  // 0.0
/*82  */         if(!ost->st->stream_copy && enc->coded_frame)                                                                          // 0.0
/*84  */             q= enc->coded_frame->quality/(float)FF_QP2LAMBDA;                                                                  // 0.0
/*86  */         if (vid && enc->codec_type == AVMEDIA_TYPE_VIDEO) {                                                                    // 0.0
/*88  */             snprintf(buf + strlen(buf), sizeof(buf) - strlen(buf), "q=%2.1f ", q);                                             // 0.0
/*90  */         }                                                                                                                      // 0.0
/*92  */         if (!vid && enc->codec_type == AVMEDIA_TYPE_VIDEO) {                                                                   // 0.0
/*94  */             float t = (av_gettime()-timer_start) / 1000000.0;                                                                  // 0.0
/*98  */             frame_number = ost->frame_number;                                                                                  // 0.0
/*100 */             snprintf(buf + strlen(buf), sizeof(buf) - strlen(buf), "frame=%5d fps=%3d q=%3.1f ",                               // 0.0
/*102 */                      frame_number, (t>1)?(int)(frame_number/t+0.5) : 0, q);                                                    // 0.0
/*104 */             if(is_last_report)                                                                                                 // 0.0
/*106 */                 snprintf(buf + strlen(buf), sizeof(buf) - strlen(buf), "L");                                                   // 0.0
/*108 */             if(qp_hist){                                                                                                       // 0.0
/*110 */                 int j;                                                                                                         // 0.0
/*112 */                 int qp= lrintf(q);                                                                                             // 0.0
/*114 */                 if(qp>=0 && qp<FF_ARRAY_ELEMS(qp_histogram))                                                                   // 0.0
/*116 */                     qp_histogram[qp]++;                                                                                        // 0.0
/*118 */                 for(j=0; j<32; j++)                                                                                            // 0.0
/*120 */                     snprintf(buf + strlen(buf), sizeof(buf) - strlen(buf), "%X", (int)lrintf(log(qp_histogram[j]+1)/log(2)));  // 0.0
/*122 */             }                                                                                                                  // 0.0
/*124 */             if (enc->flags&CODEC_FLAG_PSNR){                                                                                   // 0.0
/*126 */                 int j;                                                                                                         // 0.0
/*128 */                 double error, error_sum=0;                                                                                     // 0.0
/*130 */                 double scale, scale_sum=0;                                                                                     // 0.0
/*132 */                 char type[3]= {'Y','U','V'};                                                                                   // 0.0
/*134 */                 snprintf(buf + strlen(buf), sizeof(buf) - strlen(buf), "PSNR=");                                               // 0.0
/*136 */                 for(j=0; j<3; j++){                                                                                            // 0.0
/*138 */                     if(is_last_report){                                                                                        // 0.0
/*140 */                         error= enc->error[j];                                                                                  // 0.0
/*142 */                         scale= enc->width*enc->height*255.0*255.0*frame_number;                                                // 0.0
/*144 */                     }else{                                                                                                     // 0.0
/*146 */                         error= enc->coded_frame->error[j];                                                                     // 0.0
/*148 */                         scale= enc->width*enc->height*255.0*255.0;                                                             // 0.0
/*150 */                     }                                                                                                          // 0.0
/*152 */                     if(j) scale/=4;                                                                                            // 0.0
/*154 */                     error_sum += error;                                                                                        // 0.0
/*156 */                     scale_sum += scale;                                                                                        // 0.0
/*158 */                     snprintf(buf + strlen(buf), sizeof(buf) - strlen(buf), "%c:%2.2f ", type[j], psnr(error/scale));           // 0.0
/*160 */                 }                                                                                                              // 0.0
/*162 */                 snprintf(buf + strlen(buf), sizeof(buf) - strlen(buf), "*:%2.2f ", psnr(error_sum/scale_sum));                 // 0.0
/*164 */             }                                                                                                                  // 0.0
/*166 */             vid = 1;                                                                                                           // 0.0
/*168 */         }                                                                                                                      // 0.0
/*170 */         /* compute min output value */                                                                                         // 0.0
/*172 */         pts = (double)ost->st->pts.val * av_q2d(ost->st->time_base);                                                           // 0.0
/*174 */         if ((pts < ti1) && (pts > 0))                                                                                          // 0.0
/*176 */             ti1 = pts;                                                                                                         // 0.0
/*178 */     }                                                                                                                          // 0.0
/*180 */     if (ti1 < 0.01)                                                                                                            // 0.0
/*182 */         ti1 = 0.01;                                                                                                            // 0.0
/*186 */     if (verbose || is_last_report) {                                                                                           // 0.0
/*188 */         bitrate = (double)(total_size * 8) / ti1 / 1000.0;                                                                     // 0.0
/*192 */         snprintf(buf + strlen(buf), sizeof(buf) - strlen(buf),                                                                 // 0.0
/*194 */             "size=%8.0fkB time=%0.2f bitrate=%6.1fkbits/s",                                                                    // 0.0
/*196 */             (double)total_size / 1024, ti1, bitrate);                                                                          // 0.0
/*200 */         if (nb_frames_dup || nb_frames_drop)                                                                                   // 0.0
/*202 */           snprintf(buf + strlen(buf), sizeof(buf) - strlen(buf), " dup=%d drop=%d",                                            // 0.0
/*204 */                   nb_frames_dup, nb_frames_drop);                                                                              // 0.0
/*208 */         if (verbose >= 0)                                                                                                      // 0.0
/*210 */             fprintf(stderr, "%s    \r", buf);                                                                                  // 0.0
/*214 */         fflush(stderr);                                                                                                        // 0.0
/*216 */     }                                                                                                                          // 0.0
/*220 */     if (is_last_report && verbose >= 0){                                                                                       // 0.0
/*222 */         int64_t raw= audio_size + video_size + extra_size;                                                                     // 0.0
/*224 */         fprintf(stderr, "\n");                                                                                                 // 0.0
/*226 */         fprintf(stderr, "video:%1.0fkB audio:%1.0fkB global headers:%1.0fkB muxing overhead %f%%\n",                           // 0.0
/*228 */                 video_size/1024.0,                                                                                             // 0.0
/*230 */                 audio_size/1024.0,                                                                                             // 0.0
/*232 */                 extra_size/1024.0,                                                                                             // 0.0
/*234 */                 100.0*(total_size - raw)/raw                                                                                   // 0.0
/*236 */         );                                                                                                                     // 0.0
/*238 */     }                                                                                                                          // 0.0
/*240 */ }                                                                                                                              // 0.0
