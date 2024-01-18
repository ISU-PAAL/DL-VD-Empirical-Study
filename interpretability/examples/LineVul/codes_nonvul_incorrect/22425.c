// commit message FFmpeg@043800a968 (target=0, prob=0.520727, correct=False): vf_fps: add more error checks.
/*0   */ static int end_frame(AVFilterLink *inlink)                                                       // (15) 0.02539
/*2   */ {                                                                                                // (28) 0.001953
/*4   */     AVFilterContext    *ctx = inlink->dst;                                                       // (12) 0.03516
/*6   */     FPSContext           *s = ctx->priv;                                                         // (5) 0.04492
/*8   */     AVFilterLink   *outlink = ctx->outputs[0];                                                   // (9) 0.03906
/*10  */     AVFilterBufferRef  *buf = inlink->cur_buf;                                                   // (13) 0.03516
/*12  */     int64_t delta;                                                                               // (22) 0.01758
/*14  */     int i, ret;                                                                                  // (24) 0.01563
/*18  */     inlink->cur_buf = NULL;                                                                      // (17) 0.02344
/*20  */     s->frames_in++;                                                                              // (23) 0.01758
/*22  */     /* discard frames until we get the first timestamp */                                        // (16) 0.02539
/*24  */     if (s->pts == AV_NOPTS_VALUE) {                                                              // (11) 0.03711
/*26  */         if (buf->pts != AV_NOPTS_VALUE) {                                                        // (6) 0.04492
/*28  */             write_to_fifo(s->fifo, buf);                                                         // (3) 0.04883
/*30  */             s->first_pts = s->pts = buf->pts;                                                    // (2) 0.05469
/*32  */         } else {                                                                                 // (19) 0.01953
/*34  */             av_log(ctx, AV_LOG_WARNING, "Discarding initial frame(s) with no "                   // (0) 0.06641
/*36  */                    "timestamp.\n");                                                              // (4) 0.04883
/*38  */             avfilter_unref_buffer(buf);                                                          // (8) 0.04102
/*40  */             s->drop++;                                                                           // (14) 0.0293
/*42  */         }                                                                                        // (25) 0.01562
/*44  */         return 0;                                                                                // (20) 0.01953
/*46  */     }                                                                                            // (26) 0.007812
/*50  */     /* now wait for the next timestamp */                                                        // (18) 0.02148
/*52  */     if (buf->pts == AV_NOPTS_VALUE) {                                                            // (10) 0.03711
/*54  */         return write_to_fifo(s->fifo, buf);                                                      // (7) 0.04297
/*56  */     }                                                                                            // (27) 0.007812
/*60  */     /* number of output frames */                                                                // (21) 0.01758
/*62  */     delta = av_rescale_q(buf->pts - s->pts, inlink->time_base,                                   // (1) 0.05664
/*64  */                          outlink->time_base);                                                    // 0.0
/*68  */     if (delta < 1) {                                                                             // 0.0
/*70  */         /* drop the frame and everything buffered except the first */                            // 0.0
/*72  */         AVFilterBufferRef *tmp;                                                                  // 0.0
/*74  */         int drop = av_fifo_size(s->fifo)/sizeof(AVFilterBufferRef*);                             // 0.0
/*78  */         av_log(ctx, AV_LOG_DEBUG, "Dropping %d frame(s).\n", drop);                              // 0.0
/*80  */         s->drop += drop;                                                                         // 0.0
/*84  */         av_fifo_generic_read(s->fifo, &tmp, sizeof(tmp), NULL);                                  // 0.0
/*86  */         flush_fifo(s->fifo);                                                                     // 0.0
/*88  */         ret = write_to_fifo(s->fifo, tmp);                                                       // 0.0
/*92  */         avfilter_unref_buffer(buf);                                                              // 0.0
/*94  */         return ret;                                                                              // 0.0
/*96  */     }                                                                                            // 0.0
/*100 */     /* can output >= 1 frames */                                                                 // 0.0
/*102 */     for (i = 0; i < delta; i++) {                                                                // 0.0
/*104 */         AVFilterBufferRef *buf_out;                                                              // 0.0
/*106 */         av_fifo_generic_read(s->fifo, &buf_out, sizeof(buf_out), NULL);                          // 0.0
/*110 */         /* duplicate the frame if needed */                                                      // 0.0
/*112 */         if (!av_fifo_size(s->fifo) && i < delta - 1) {                                           // 0.0
/*114 */             av_log(ctx, AV_LOG_DEBUG, "Duplicating frame.\n");                                   // 0.0
/*116 */             write_to_fifo(s->fifo, avfilter_ref_buffer(buf_out, AV_PERM_READ));                  // 0.0
/*118 */             s->dup++;                                                                            // 0.0
/*120 */         }                                                                                        // 0.0
/*124 */         buf_out->pts = av_rescale_q(s->first_pts, inlink->time_base,                             // 0.0
/*126 */                                     outlink->time_base) + s->frames_out;                         // 0.0
/*130 */         if ((ret = ff_start_frame(outlink, buf_out)) < 0 ||                                      // 0.0
/*132 */             (ret = ff_draw_slice(outlink, 0, outlink->h, 1)) < 0 ||                              // 0.0
/*134 */             (ret = ff_end_frame(outlink)) < 0) {                                                 // 0.0
/*136 */             avfilter_unref_bufferp(&buf);                                                        // 0.0
/*138 */             return ret;                                                                          // 0.0
/*140 */         }                                                                                        // 0.0
/*144 */         s->frames_out++;                                                                         // 0.0
/*146 */     }                                                                                            // 0.0
/*148 */     flush_fifo(s->fifo);                                                                         // 0.0
/*152 */     ret = write_to_fifo(s->fifo, buf);                                                           // 0.0
/*154 */     s->pts = s->first_pts + av_rescale_q(s->frames_out, outlink->time_base, inlink->time_base);  // 0.0
/*158 */     return ret;                                                                                  // 0.0
/*160 */ }                                                                                                // 0.0
