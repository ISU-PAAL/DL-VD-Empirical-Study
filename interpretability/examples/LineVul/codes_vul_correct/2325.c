// commit message FFmpeg@e838c9852e (target=1, prob=0.982739, correct=True): avcodec/bink: use av_mallocz for data
/*0  */ static av_cold int init_bundles(BinkContext *c)                   // (7) 0.07203
/*2  */ {                                                                 // (13) 0.004237
/*4  */     int bw, bh, blocks;                                           // (8) 0.05085
/*6  */     int i;                                                        // (10) 0.02542
/*10 */     bw = (c->avctx->width  + 7) >> 3;                             // (3) 0.08475
/*12 */     bh = (c->avctx->height + 7) >> 3;                             // (5) 0.08051
/*14 */     blocks = bw * bh;                                             // (9) 0.04661
/*18 */     for (i = 0; i < BINKB_NB_SRC; i++) {                          // (2) 0.09746
/*20 */         c->bundle[i].data = av_malloc(blocks * 64);               // (1) 0.1059
/*22 */         if (!c->bundle[i].data)                                   // (6) 0.07627
/*24 */             return AVERROR(ENOMEM);                               // (4) 0.08475
/*26 */         c->bundle[i].data_end = c->bundle[i].data + blocks * 64;  // (0) 0.1314
/*28 */     }                                                             // (12) 0.01695
/*32 */     return 0;                                                     // (11) 0.02542
/*34 */ }                                                                 // (14) 0.004237
