// commit message FFmpeg@4b5a12a2cb (target=0, prob=0.5797077, correct=False): af_aresample: fix rounding of negative timestamps
/*0  */ static int filter_samples(AVFilterLink *inlink, AVFilterBufferRef *insamplesref)                                                                            // (6) 0.04492
/*2  */ {                                                                                                                                                           // (21) 0.001953
/*4  */     AResampleContext *aresample = inlink->dst->priv;                                                                                                        // (14) 0.03711
/*6  */     const int n_in  = insamplesref->audio->nb_samples;                                                                                                      // (12) 0.04102
/*8  */     int n_out       = FFMAX(n_in * aresample->ratio * 2, 1);                                                                                                // (4) 0.06055
/*10 */     AVFilterLink *const outlink = inlink->dst->outputs[0];                                                                                                  // (10) 0.04297
/*12 */     AVFilterBufferRef *outsamplesref = ff_get_audio_buffer(outlink, AV_PERM_WRITE, n_out);                                                                  // (2) 0.06836
/*14 */     int ret;                                                                                                                                                // (18) 0.01172
/*18 */     if(!outsamplesref)                                                                                                                                      // (17) 0.01953
/*20 */         return AVERROR(ENOMEM);                                                                                                                             // (15) 0.03125
/*24 */     avfilter_copy_buffer_ref_props(outsamplesref, insamplesref);                                                                                            // (8) 0.04492
/*26 */     outsamplesref->format                = outlink->format;                                                                                                 // (5) 0.05664
/*28 */     outsamplesref->audio->channel_layout = outlink->channel_layout;                                                                                         // (13) 0.03906
/*30 */     outsamplesref->audio->sample_rate    = outlink->sample_rate;                                                                                            // (7) 0.04492
/*34 */     if(insamplesref->pts != AV_NOPTS_VALUE) {                                                                                                               // (11) 0.04102
/*36 */         int64_t inpts = av_rescale(insamplesref->pts, inlink->time_base.num * (int64_t)outlink->sample_rate * inlink->sample_rate, inlink->time_base.den);  // (0) 0.127
/*38 */         int64_t outpts= swr_next_pts(aresample->swr, inpts);                                                                                                // (3) 0.06445
/*40 */         aresample->next_pts =                                                                                                                               // (16) 0.0293
/*42 */         outsamplesref->pts  = (outpts + inlink->sample_rate/2) / inlink->sample_rate;                                                                       // (1) 0.07227
/*44 */     } else {                                                                                                                                                // (19) 0.01172
/*46 */         outsamplesref->pts  = AV_NOPTS_VALUE;                                                                                                               // (9) 0.04492
/*48 */     }                                                                                                                                                       // (20) 0.007813
/*52 */     n_out = swr_convert(aresample->swr, outsamplesref->extended_data, n_out,                                                                                // 0.0
/*54 */                                  (void *)insamplesref->extended_data, n_in);                                                                                // 0.0
/*56 */     if (n_out <= 0) {                                                                                                                                       // 0.0
/*58 */         avfilter_unref_buffer(outsamplesref);                                                                                                               // 0.0
/*60 */         avfilter_unref_buffer(insamplesref);                                                                                                                // 0.0
/*62 */         return 0;                                                                                                                                           // 0.0
/*64 */     }                                                                                                                                                       // 0.0
/*68 */     outsamplesref->audio->nb_samples  = n_out;                                                                                                              // 0.0
/*72 */     ret = ff_filter_samples(outlink, outsamplesref);                                                                                                        // 0.0
/*74 */     aresample->req_fullfilled= 1;                                                                                                                           // 0.0
/*76 */     avfilter_unref_buffer(insamplesref);                                                                                                                    // 0.0
/*78 */     return ret;                                                                                                                                             // 0.0
/*80 */ }                                                                                                                                                           // 0.0
