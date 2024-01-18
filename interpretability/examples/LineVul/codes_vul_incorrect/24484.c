// commit message FFmpeg@abb5e37f64 (target=1, prob=0.38241675, correct=False): avfilter: fix leaks on error in ff_filter_frame
/*0   */ int ff_filter_frame(AVFilterLink *link, AVFrame *frame)                                // (8) 0.03516
/*2   */ {                                                                                      // (27) 0.001953
/*4   */     int (*filter_frame)(AVFilterLink *, AVFrame *);                                    // (9) 0.03516
/*6   */     AVFilterPad *dst = link->dstpad;                                                   // (13) 0.03125
/*8   */     AVFrame *out;                                                                      // (24) 0.01562
/*12  */     FF_DPRINTF_START(NULL, filter_frame);                                              // (6) 0.03711
/*14  */     ff_dlog_link(NULL, link, 1);                                                       // (14) 0.03125
/*18  */     if (!(filter_frame = dst->filter_frame))                                           // (15) 0.03125
/*20  */         filter_frame = default_filter_frame;                                           // (11) 0.0332
/*24  */     /* copy the frame if needed */                                                     // (23) 0.01953
/*26  */     if (dst->needs_writable && !av_frame_is_writable(frame)) {                         // (3) 0.05078
/*28  */         av_log(link->dst, AV_LOG_DEBUG, "Copying data in avfilter.\n");                // (0) 0.06445
/*32  */         switch (link->type) {                                                          // (19) 0.02734
/*34  */         case AVMEDIA_TYPE_VIDEO:                                                       // (17) 0.03125
/*36  */             out = ff_get_video_buffer(link, link->w, link->h);                         // (1) 0.06055
/*38  */             break;                                                                     // (20) 0.02539
/*40  */         case AVMEDIA_TYPE_AUDIO:                                                       // (12) 0.0332
/*42  */             out = ff_get_audio_buffer(link, frame->nb_samples);                        // (2) 0.05859
/*44  */             break;                                                                     // (21) 0.02539
/*46  */         default: return AVERROR(EINVAL);                                               // (10) 0.03516
/*48  */         }                                                                              // (25) 0.01562
/*50  */         if (!out) {                                                                    // (22) 0.02344
/*52  */             av_frame_free(&frame);                                                     // (7) 0.03711
/*54  */             return AVERROR(ENOMEM);                                                    // (4) 0.03906
/*56  */         }                                                                              // (26) 0.01562
/*58  */         av_frame_copy_props(out, frame);                                               // (5) 0.03906
/*62  */         switch (link->type) {                                                          // (18) 0.02734
/*64  */         case AVMEDIA_TYPE_VIDEO:                                                       // (16) 0.03125
/*66  */             av_image_copy(out->data, out->linesize, frame->data, frame->linesize,      // 0.0
/*68  */                           frame->format, frame->width, frame->height);                 // 0.0
/*70  */             break;                                                                     // 0.0
/*72  */         case AVMEDIA_TYPE_AUDIO:                                                       // 0.0
/*74  */             av_samples_copy(out->extended_data, frame->extended_data,                  // 0.0
/*76  */                             0, 0, frame->nb_samples,                                   // 0.0
/*78  */                             av_get_channel_layout_nb_channels(frame->channel_layout),  // 0.0
/*80  */                             frame->format);                                            // 0.0
/*82  */             break;                                                                     // 0.0
/*84  */         default: return AVERROR(EINVAL);                                               // 0.0
/*86  */         }                                                                              // 0.0
/*90  */         av_frame_free(&frame);                                                         // 0.0
/*92  */     } else                                                                             // 0.0
/*94  */         out = frame;                                                                   // 0.0
/*98  */     return filter_frame(link, out);                                                    // 0.0
/*100 */ }                                                                                      // 0.0
