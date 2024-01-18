// commit message FFmpeg@ff763351e7 (target=1, prob=0.9990274, correct=True): avfilter/zscale: fix memory leak
/*0  */ static void uninit(AVFilterContext *ctx)  // (3) 0.141
/*2  */ {                                         // (6) 0.01282
/*4  */     ZScaleContext *s = ctx->priv;         // (1) 0.1795
/*8  */     zimg_filter_graph_free(s->graph);     // (0) 0.2051
/*11 */     av_freep(&s->tmp);                    // (2) 0.1538
/*13 */     s->tmp_size = 0;                      // (4) 0.141
/*15 */ }                                         // (5) 0.01282
