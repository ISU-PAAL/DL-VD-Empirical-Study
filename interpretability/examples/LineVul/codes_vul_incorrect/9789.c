// commit message FFmpeg@22ecfcd4c7 (target=1, prob=0.15072316, correct=False): af_channelmap: properly set the supported output channel layouts
/*0  */ static int channelmap_query_formats(AVFilterContext *ctx)                                    // (4) 0.08989
/*2  */ {                                                                                            // (7) 0.005618
/*4  */     ChannelMapContext *s = ctx->priv;                                                        // (5) 0.07865
/*8  */     ff_set_common_formats(ctx, ff_planar_sample_fmts());                                     // (2) 0.1348
/*10 */     ff_set_common_samplerates(ctx, ff_all_samplerates());                                    // (3) 0.1292
/*12 */     ff_channel_layouts_ref(ff_all_channel_layouts(), &ctx->inputs[0]->out_channel_layouts);  // (1) 0.2079
/*14 */     ff_channel_layouts_ref(s->channel_layouts,       &ctx->outputs[0]->in_channel_layouts);  // (0) 0.2303
/*18 */     return 0;                                                                                // (6) 0.03371
/*20 */ }                                                                                            // (8) 0.005618
