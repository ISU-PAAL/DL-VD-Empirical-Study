// commit message FFmpeg@ac87c273a6 (target=1, prob=0.5480829, correct=True): src_buffer: propagate errors from copy_buffer_ref()
/*0  */ int av_buffersrc_add_ref(AVFilterContext *buffer_filter,                        // (9) 0.03711
/*2  */                          AVFilterBufferRef *picref, int flags)                  // (2) 0.06836
/*4  */ {                                                                               // (27) 0.001953
/*6  */     BufferSourceContext *c = buffer_filter->priv;                               // (12) 0.0293
/*8  */     AVFilterBufferRef *buf;                                                     // (19) 0.01953
/*10 */     int ret;                                                                    // (24) 0.01172
/*14 */     if (!picref) {                                                              // (23) 0.01758
/*16 */         c->eof = 1;                                                             // (13) 0.02734
/*18 */         return 0;                                                               // (20) 0.01953
/*20 */     } else if (c->eof)                                                          // (17) 0.02344
/*22 */         return AVERROR(EINVAL);                                                 // (11) 0.03125
/*26 */     if (!av_fifo_space(c->fifo) &&                                              // (10) 0.03516
/*28 */         (ret = av_fifo_realloc2(c->fifo, av_fifo_size(c->fifo) +                // (1) 0.07227
/*30 */                                          sizeof(buf))) < 0)                     // (0) 0.0918
/*32 */         return ret;                                                             // (21) 0.01953
/*36 */     if (!(flags & AV_BUFFERSRC_FLAG_NO_CHECK_FORMAT)) {                         // (4) 0.04883
/*38 */         ret = check_format_change(buffer_filter, picref);                       // (6) 0.04297
/*40 */         if (ret < 0)                                                            // (16) 0.02539
/*42 */             return ret;                                                         // (14) 0.02734
/*44 */     }                                                                           // (26) 0.007812
/*46 */     if (flags & AV_BUFFERSRC_FLAG_NO_COPY)                                      // (7) 0.04297
/*48 */         buf = picref;                                                           // (18) 0.02344
/*50 */     else                                                                        // (25) 0.007813
/*52 */         buf = copy_buffer_ref(buffer_filter, picref);                           // (5) 0.04297
/*58 */     if ((ret = av_fifo_generic_write(c->fifo, &buf, sizeof(buf), NULL)) < 0) {  // (3) 0.06641
/*60 */         if (buf != picref)                                                      // (15) 0.02734
/*62 */             avfilter_unref_buffer(buf);                                         // (8) 0.04102
/*64 */         return ret;                                                             // (22) 0.01953
/*66 */     }                                                                           // 0.0
/*68 */     c->nb_failed_requests = 0;                                                  // 0.0
/*72 */     return 0;                                                                   // 0.0
/*74 */ }                                                                               // 0.0
