// commit message FFmpeg@9f61abc811 (target=0, prob=0.45664686, correct=True): lavf: allow custom IO for all files
/*0  */ static void hds_free(AVFormatContext *s)            // (15) 0.02968
/*2  */ {                                                   // (24) 0.002283
/*4  */     HDSContext *c = s->priv_data;                   // (13) 0.03425
/*6  */     int i, j;                                       // (22) 0.01826
/*8  */     if (!c->streams)                                // (20) 0.02283
/*10 */         return;                                     // (21) 0.02055
/*12 */     for (i = 0; i < s->nb_streams; i++) {           // (6) 0.04795
/*14 */         OutputStream *os = &c->streams[i];          // (8) 0.04566
/*16 */         if (os->out)                                // (16) 0.02968
/*18 */             avio_close(os->out);                    // (9) 0.04566
/*20 */         os->out = NULL;                             // (17) 0.02968
/*22 */         if (os->ctx && os->ctx_inited)              // (10) 0.04566
/*24 */             av_write_trailer(os->ctx);              // (4) 0.05023
/*26 */         if (os->ctx && os->ctx->pb)                 // (11) 0.04338
/*28 */             av_free(os->ctx->pb);                   // (7) 0.04795
/*30 */         if (os->ctx)                                // (18) 0.02968
/*32 */             avformat_free_context(os->ctx);         // (5) 0.05023
/*34 */         av_free(os->metadata);                      // (14) 0.03425
/*36 */         for (j = 0; j < os->nb_extra_packets; j++)  // (0) 0.05936
/*38 */             av_free(os->extra_packets[j]);          // (2) 0.05479
/*40 */         for (j = 0; j < os->nb_fragments; j++)      // (1) 0.05708
/*42 */             av_free(os->fragments[j]);              // (3) 0.05251
/*44 */         av_free(os->fragments);                     // (12) 0.03881
/*46 */     }                                               // (23) 0.009132
/*48 */     av_freep(&c->streams);                          // (19) 0.02968
/*50 */ }                                                   // (25) 0.002283
