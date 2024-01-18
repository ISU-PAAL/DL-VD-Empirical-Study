// commit message FFmpeg@ed1c83508e (target=0, prob=0.4370149, correct=True): lavfi/trim: remove request frame hack
/*0   */ static int atrim_filter_frame(AVFilterLink *inlink, AVFrame *frame)                                 // (7) 0.04102
/*2   */ {                                                                                                   // (27) 0.001953
/*4   */     AVFilterContext *ctx = inlink->dst;                                                             // (15) 0.0293
/*6   */     TrimContext       *s = ctx->priv;                                                               // (8) 0.03906
/*8   */     int64_t start_sample, end_sample = frame->nb_samples;                                           // (6) 0.04297
/*10  */     int64_t pts;                                                                                    // (22) 0.01758
/*12  */     int drop;                                                                                       // (23) 0.01172
/*16  */     /* drop everything if EOF has already been returned */                                          // (17) 0.02734
/*18  */     if (s->eof) {                                                                                   // (19) 0.02148
/*20  */         av_frame_free(&frame);                                                                      // (16) 0.0293
/*22  */         return 0;                                                                                   // (21) 0.01953
/*24  */     }                                                                                               // (25) 0.007812
/*28  */     if (frame->pts != AV_NOPTS_VALUE)                                                               // (11) 0.03516
/*30  */         pts = av_rescale_q(frame->pts, inlink->time_base,                                           // (4) 0.05469
/*32  */                            (AVRational){ 1, inlink->sample_rate });                                 // (0) 0.07812
/*34  */     else                                                                                            // (26) 0.007812
/*36  */         pts = s->next_pts;                                                                          // (14) 0.03125
/*38  */     s->next_pts = pts + frame->nb_samples;                                                          // (9) 0.03711
/*42  */     /* check if at least a part of the frame is after the start time */                             // (10) 0.03711
/*44  */     if (s->start_sample < 0 && s->start_pts == AV_NOPTS_VALUE) {                                    // (3) 0.05664
/*46  */         start_sample = 0;                                                                           // (18) 0.02539
/*48  */     } else {                                                                                        // (24) 0.01172
/*50  */         drop = 1;                                                                                   // (20) 0.02148
/*52  */         start_sample = frame->nb_samples;                                                           // (12) 0.03516
/*56  */         if (s->start_sample >= 0 &&                                                                 // (13) 0.0332
/*58  */             s->nb_samples + frame->nb_samples > s->start_sample) {                                  // (2) 0.0625
/*60  */             drop         = 0;                                                                       // (5) 0.04492
/*62  */             start_sample = FFMIN(start_sample, s->start_sample - s->nb_samples);                    // (1) 0.06836
/*64  */         }                                                                                           // 0.0
/*68  */         if (s->start_pts != AV_NOPTS_VALUE && pts != AV_NOPTS_VALUE &&                              // 0.0
/*70  */             pts + frame->nb_samples > s->start_pts) {                                               // 0.0
/*72  */             drop = 0;                                                                               // 0.0
/*74  */             start_sample = FFMIN(start_sample, s->start_pts - pts);                                 // 0.0
/*76  */         }                                                                                           // 0.0
/*80  */         if (drop)                                                                                   // 0.0
/*82  */             goto drop;                                                                              // 0.0
/*84  */     }                                                                                               // 0.0
/*88  */     if (s->first_pts == AV_NOPTS_VALUE)                                                             // 0.0
/*90  */         s->first_pts = pts + start_sample;                                                          // 0.0
/*94  */     /* check if at least a part of the frame is before the end time */                              // 0.0
/*96  */     if (s->end_sample == INT64_MAX && s->end_pts == AV_NOPTS_VALUE && !s->duration_tb) {            // 0.0
/*98  */         end_sample = frame->nb_samples;                                                             // 0.0
/*100 */     } else {                                                                                        // 0.0
/*102 */         drop       = 1;                                                                             // 0.0
/*104 */         end_sample = 0;                                                                             // 0.0
/*108 */         if (s->end_sample != INT64_MAX &&                                                           // 0.0
/*110 */             s->nb_samples < s->end_sample) {                                                        // 0.0
/*112 */             drop       = 0;                                                                         // 0.0
/*114 */             end_sample = FFMAX(end_sample, s->end_sample - s->nb_samples);                          // 0.0
/*116 */         }                                                                                           // 0.0
/*120 */         if (s->end_pts != AV_NOPTS_VALUE && pts != AV_NOPTS_VALUE &&                                // 0.0
/*122 */             pts < s->end_pts) {                                                                     // 0.0
/*124 */             drop       = 0;                                                                         // 0.0
/*126 */             end_sample = FFMAX(end_sample, s->end_pts - pts);                                       // 0.0
/*128 */         }                                                                                           // 0.0
/*132 */         if (s->duration_tb && pts - s->first_pts < s->duration_tb) {                                // 0.0
/*134 */             drop       = 0;                                                                         // 0.0
/*136 */             end_sample = FFMAX(end_sample, s->first_pts + s->duration_tb - pts);                    // 0.0
/*138 */         }                                                                                           // 0.0
/*142 */         if (drop) {                                                                                 // 0.0
/*144 */             s->eof = 1;                                                                             // 0.0
/*146 */             goto drop;                                                                              // 0.0
/*148 */         }                                                                                           // 0.0
/*150 */     }                                                                                               // 0.0
/*154 */     s->nb_samples += frame->nb_samples;                                                             // 0.0
/*156 */     start_sample   = FFMAX(0, start_sample);                                                        // 0.0
/*158 */     end_sample     = FFMIN(frame->nb_samples, end_sample);                                          // 0.0
/*160 */     av_assert0(start_sample < end_sample);                                                          // 0.0
/*164 */     if (start_sample) {                                                                             // 0.0
/*166 */         AVFrame *out = ff_get_audio_buffer(ctx->outputs[0], end_sample - start_sample);             // 0.0
/*168 */         if (!out) {                                                                                 // 0.0
/*170 */             av_frame_free(&frame);                                                                  // 0.0
/*172 */             return AVERROR(ENOMEM);                                                                 // 0.0
/*174 */         }                                                                                           // 0.0
/*178 */         av_frame_copy_props(out, frame);                                                            // 0.0
/*180 */         av_samples_copy(out->extended_data, frame->extended_data, 0, start_sample,                  // 0.0
/*182 */                         out->nb_samples, av_get_channel_layout_nb_channels(frame->channel_layout),  // 0.0
/*184 */                         frame->format);                                                             // 0.0
/*186 */         if (out->pts != AV_NOPTS_VALUE)                                                             // 0.0
/*188 */             out->pts += av_rescale_q(start_sample, (AVRational){ 1, out->sample_rate },             // 0.0
/*190 */                                      inlink->time_base);                                            // 0.0
/*194 */         av_frame_free(&frame);                                                                      // 0.0
/*196 */         frame = out;                                                                                // 0.0
/*198 */     } else                                                                                          // 0.0
/*200 */         frame->nb_samples = end_sample;                                                             // 0.0
/*204 */     s->got_output = 1;                                                                              // 0.0
/*206 */     return ff_filter_frame(ctx->outputs[0], frame);                                                 // 0.0
/*210 */ drop:                                                                                               // 0.0
/*212 */     s->nb_samples += frame->nb_samples;                                                             // 0.0
/*214 */     av_frame_free(&frame);                                                                          // 0.0
/*216 */     return 0;                                                                                       // 0.0
/*218 */ }                                                                                                   // 0.0
