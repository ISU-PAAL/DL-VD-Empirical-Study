// commit message FFmpeg@bb146bb57b (target=0, prob=0.97583914, correct=False): ogg: prevent NULL pointer deference in theora gptopts
/*0  */ theora_gptopts(AVFormatContext *ctx, int idx, uint64_t gp, int64_t *dts)  // (0) 0.1345
/*2  */ {                                                                         // (13) 0.004202
/*4  */     struct ogg *ogg = ctx->priv_data;                                     // (6) 0.06723
/*6  */     struct ogg_stream *os = ogg->streams + idx;                           // (2) 0.08403
/*8  */     struct theora_params *thp = os->private;                              // (7) 0.06723
/*10 */     uint64_t iframe = gp >> thp->gpshift;                                 // (3) 0.07983
/*12 */     uint64_t pframe = gp & thp->gpmask;                                   // (4) 0.07983
/*16 */     if (thp->version < 0x030201)                                          // (8) 0.06303
/*18 */         iframe++;                                                         // (9) 0.04202
/*22 */     if(!pframe)                                                           // (11) 0.03782
/*24 */         os->pflags |= AV_PKT_FLAG_KEY;                                    // (1) 0.09244
/*28 */     if (dts)                                                              // (12) 0.03361
/*30 */         *dts = iframe + pframe;                                           // (5) 0.07143
/*34 */     return iframe + pframe;                                               // (10) 0.04202
/*36 */ }                                                                         // (14) 0.004202
