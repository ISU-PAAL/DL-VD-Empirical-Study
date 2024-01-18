// commit message FFmpeg@c90b88090c (target=1, prob=0.4968976, correct=False): avfilter: do not leak AVFrame on failed buffer allocation
/*0  */ static int filter_frame(AVFilterLink *inlink, AVFrame *src_buffer)          // (10) 0.03906
/*2  */ {                                                                           // (20) 0.001955
/*4  */     AVFilterContext  *ctx = inlink->dst;                                    // (15) 0.03125
/*6  */     ATempoContext *atempo = ctx->priv;                                      // (16) 0.03125
/*8  */     AVFilterLink *outlink = ctx->outputs[0];                                // (12) 0.03516
/*12 */     int ret = 0;                                                            // (18) 0.01562
/*14 */     int n_in = src_buffer->nb_samples;                                      // (14) 0.0332
/*16 */     int n_out = (int)(0.5 + ((double)n_in) / atempo->tempo);                // (5) 0.05859
/*20 */     const uint8_t *src = src_buffer->data[0];                               // (11) 0.03711
/*22 */     const uint8_t *src_end = src + n_in * atempo->stride;                   // (6) 0.05078
/*26 */     while (src < src_end) {                                                 // (17) 0.02344
/*28 */         if (!atempo->dst_buffer) {                                          // (13) 0.03516
/*30 */             atempo->dst_buffer = ff_get_audio_buffer(outlink, n_out);       // (2) 0.06836
/*32 */             if (!atempo->dst_buffer)                                        // (9) 0.04102
/*34 */                 return AVERROR(ENOMEM);                                     // (8) 0.04687
/*36 */             av_frame_copy_props(atempo->dst_buffer, src_buffer);            // (3) 0.0625
/*40 */             atempo->dst = atempo->dst_buffer->data[0];                      // (4) 0.06055
/*42 */             atempo->dst_end = atempo->dst + n_out * atempo->stride;         // (1) 0.07422
/*44 */         }                                                                   // (19) 0.01562
/*48 */         yae_apply(atempo, &src, src_end, &atempo->dst, atempo->dst_end);    // (0) 0.07422
/*52 */         if (atempo->dst == atempo->dst_end) {                               // (7) 0.04883
/*54 */             int n_samples = ((atempo->dst - atempo->dst_buffer->data[0]) /  // 0.0
/*56 */                              atempo->stride);                               // 0.0
/*58 */             ret = push_samples(atempo, outlink, n_samples);                 // 0.0
/*60 */             if (ret < 0)                                                    // 0.0
/*62 */                 goto end;                                                   // 0.0
/*64 */         }                                                                   // 0.0
/*66 */     }                                                                       // 0.0
/*70 */     atempo->nsamples_in += n_in;                                            // 0.0
/*72 */ end:                                                                        // 0.0
/*74 */     av_frame_free(&src_buffer);                                             // 0.0
/*76 */     return ret;                                                             // 0.0
/*78 */ }                                                                           // 0.0
