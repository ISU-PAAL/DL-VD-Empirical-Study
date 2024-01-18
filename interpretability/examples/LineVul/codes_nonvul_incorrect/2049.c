// commit message FFmpeg@f566ac48ce (target=0, prob=0.6108726, correct=False): avutil/frame: fix video buffer allocation
/*0  */ static int get_video_buffer(AVFrame *frame, int align)                          // (12) 0.03125
/*2  */ {                                                                               // (24) 0.001953
/*4  */     const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(frame->format);        // (2) 0.06055
/*6  */     int ret, i;                                                                 // (20) 0.01563
/*10 */     if (!desc)                                                                  // (21) 0.01367
/*12 */         return AVERROR(EINVAL);                                                 // (13) 0.03125
/*16 */     if ((ret = av_image_check_size(frame->width, frame->height, 0, NULL)) < 0)  // (3) 0.05859
/*18 */         return ret;                                                             // (19) 0.01953
/*22 */     if (!frame->linesize[0]) {                                                  // (17) 0.02539
/*24 */         ret = av_image_fill_linesizes(frame->linesize, frame->format,           // (6) 0.05273
/*26 */                                       frame->width);                            // (0) 0.08008
/*28 */         if (ret < 0)                                                            // (18) 0.02539
/*30 */             return ret;                                                         // (16) 0.02734
/*34 */         for (i = 0; i < 4 && frame->linesize[i]; i++)                           // (7) 0.05078
/*36 */             frame->linesize[i] = FFALIGN(frame->linesize[i], align);            // (1) 0.0625
/*38 */     }                                                                           // (22) 0.007812
/*42 */     for (i = 0; i < 4 && frame->linesize[i]; i++) {                             // (8) 0.04492
/*44 */         int h = FFALIGN(frame->height, 32);                                     // (10) 0.03906
/*46 */         if (i == 1 || i == 2)                                                   // (11) 0.0332
/*48 */             h = -((-h) >> desc->log2_chroma_h);                                 // (5) 0.05664
/*52 */         frame->buf[i] = av_buffer_alloc(frame->linesize[i] * h);                // (4) 0.05859
/*54 */         if (!frame->buf[i])                                                     // (14) 0.0293
/*56 */             goto fail;                                                          // (15) 0.02734
/*60 */         frame->data[i] = frame->buf[i]->data;                                   // (9) 0.04492
/*62 */     }                                                                           // (23) 0.007812
/*64 */     if (desc->flags & PIX_FMT_PAL || desc->flags & PIX_FMT_PSEUDOPAL) {         // 0.0
/*66 */         av_buffer_unref(&frame->buf[1]);                                        // 0.0
/*68 */         frame->buf[1] = av_buffer_alloc(1024);                                  // 0.0
/*70 */         if (!frame->buf[1])                                                     // 0.0
/*72 */             goto fail;                                                          // 0.0
/*74 */         frame->data[1] = frame->buf[1]->data;                                   // 0.0
/*76 */     }                                                                           // 0.0
/*80 */     frame->extended_data = frame->data;                                         // 0.0
/*84 */     return 0;                                                                   // 0.0
/*86 */ fail:                                                                           // 0.0
/*88 */     av_frame_unref(frame);                                                      // 0.0
/*90 */     return AVERROR(ENOMEM);                                                     // 0.0
/*92 */ }                                                                               // 0.0
