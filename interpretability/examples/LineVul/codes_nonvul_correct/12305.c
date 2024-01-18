// commit message FFmpeg@32c3047cac (target=0, prob=0.47896636, correct=True): These video decoders do not need to include and initialize the DSP support functions.
/*0  */ static int idcin_decode_init(AVCodecContext *avctx)                                                             // (7) 0.04615
/*2  */ {                                                                                                               // (21) 0.002564
/*4  */     IdcinContext *s = avctx->priv_data;                                                                         // (9) 0.04103
/*6  */     int i, j, histogram_index = 0;                                                                              // (11) 0.03846
/*8  */     unsigned char *histograms;                                                                                  // (17) 0.02308
/*12 */     s->avctx = avctx;                                                                                           // (15) 0.02821
/*14 */     avctx->pix_fmt = PIX_FMT_PAL8;                                                                              // (4) 0.05641
/*16 */     dsputil_init(&s->dsp, avctx);                                                                               // (8) 0.04615
/*20 */     /* make sure the Huffman tables make it */                                                                  // (13) 0.03333
/*22 */     if (s->avctx->extradata_size != HUFFMAN_TABLE_SIZE) {                                                       // (2) 0.0641
/*24 */         av_log(s->avctx, AV_LOG_ERROR, "  Id CIN video: expected extradata size of %d\n", HUFFMAN_TABLE_SIZE);  // (0) 0.1205
/*26 */         return -1;                                                                                              // (16) 0.02821
/*28 */     }                                                                                                           // (19) 0.01026
/*32 */     /* build the 256 Huffman decode trees */                                                                    // (14) 0.03077
/*34 */     histograms = (unsigned char *)s->avctx->extradata;                                                          // (5) 0.04872
/*36 */     for (i = 0; i < 256; i++) {                                                                                 // (10) 0.04103
/*38 */         for(j = 0; j < HUF_TOKENS; j++)                                                                         // (3) 0.06154
/*40 */             s->huff_nodes[i][j].count = histograms[histogram_index++];                                          // (1) 0.08718
/*42 */         huff_build_tree(s, i);                                                                                  // (6) 0.04615
/*44 */     }                                                                                                           // (20) 0.01026
/*48 */     s->frame.data[0] = NULL;                                                                                    // (12) 0.0359
/*52 */     return 0;                                                                                                   // (18) 0.01538
/*54 */ }                                                                                                               // (22) 0.002564
