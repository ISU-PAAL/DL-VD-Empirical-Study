// commit message FFmpeg@56ee3f9de7 (target=0, prob=0.505611, correct=False): avconv: distinguish between -ss 0 and -ss not being used
/*0   */ static int poll_filter(OutputStream *ost)                                               // (14) 0.02148
/*2   */ {                                                                                       // (20) 0.001953
/*4   */     OutputFile    *of = output_files[ost->file_index];                                  // (9) 0.04102
/*6   */     AVFrame *filtered_frame = NULL;                                                     // (13) 0.02539
/*8   */     int frame_size, ret;                                                                // (16) 0.01953
/*12  */     if (!ost->filtered_frame && !(ost->filtered_frame = avcodec_alloc_frame())) {       // (3) 0.06055
/*14  */         return AVERROR(ENOMEM);                                                         // (11) 0.03125
/*16  */     } else                                                                              // (18) 0.009766
/*18  */         avcodec_get_frame_defaults(ost->filtered_frame);                                // (7) 0.04883
/*20  */     filtered_frame = ost->filtered_frame;                                               // (12) 0.02734
/*24  */     if (ost->enc->type == AVMEDIA_TYPE_AUDIO &&                                         // (10) 0.03906
/*26  */         !(ost->enc->capabilities & CODEC_CAP_VARIABLE_FRAME_SIZE))                      // (2) 0.0625
/*28  */         ret = av_buffersink_get_samples(ost->filter->filter, filtered_frame,            // (4) 0.05859
/*30  */                                          ost->st->codec->frame_size);                   // (1) 0.09961
/*32  */     else                                                                                // (19) 0.007812
/*34  */         ret = av_buffersink_get_frame(ost->filter->filter, filtered_frame);             // (5) 0.05664
/*38  */     if (ret < 0)                                                                        // (17) 0.01758
/*40  */         return ret;                                                                     // (15) 0.01953
/*44  */     if (filtered_frame->pts != AV_NOPTS_VALUE) {                                        // (8) 0.04297
/*46  */         filtered_frame->pts = av_rescale_q(filtered_frame->pts,                         // (6) 0.05664
/*48  */                                            ost->filter->filter->inputs[0]->time_base,   // (0) 0.1133
/*50  */                                            ost->st->codec->time_base) -                 // 0.0
/*52  */                               av_rescale_q(of->start_time,                              // 0.0
/*54  */                                            AV_TIME_BASE_Q,                              // 0.0
/*56  */                                            ost->st->codec->time_base);                  // 0.0
/*58  */     }                                                                                   // 0.0
/*62  */     switch (ost->filter->filter->inputs[0]->type) {                                     // 0.0
/*64  */     case AVMEDIA_TYPE_VIDEO:                                                            // 0.0
/*66  */         if (!ost->frame_aspect_ratio)                                                   // 0.0
/*68  */             ost->st->codec->sample_aspect_ratio = filtered_frame->sample_aspect_ratio;  // 0.0
/*72  */         do_video_out(of->ctx, ost, filtered_frame, &frame_size);                        // 0.0
/*74  */         if (vstats_filename && frame_size)                                              // 0.0
/*76  */             do_video_stats(ost, frame_size);                                            // 0.0
/*78  */         break;                                                                          // 0.0
/*80  */     case AVMEDIA_TYPE_AUDIO:                                                            // 0.0
/*82  */         do_audio_out(of->ctx, ost, filtered_frame);                                     // 0.0
/*84  */         break;                                                                          // 0.0
/*86  */     default:                                                                            // 0.0
/*88  */         // TODO support subtitle filters                                                // 0.0
/*90  */         av_assert0(0);                                                                  // 0.0
/*92  */     }                                                                                   // 0.0
/*96  */     av_frame_unref(filtered_frame);                                                     // 0.0
/*100 */     return 0;                                                                           // 0.0
/*102 */ }                                                                                       // 0.0
