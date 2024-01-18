// commit message FFmpeg@073c2593c9 (target=1, prob=0.7371419, correct=True): Memory leak fix patch by (Burkhard Plaum <plaum >at< ipf.uni-stuttgart )dot( de>)
/*0  */ static int svq1_decode_init(AVCodecContext *avctx)                                                    // (12) 0.03711
/*2  */ {                                                                                                     // (22) 0.001953
/*4  */     MpegEncContext *s = avctx->priv_data;                                                             // (16) 0.03321
/*6  */     int i;                                                                                            // (21) 0.01172
/*10 */     MPV_decode_defaults(s);                                                                           // (18) 0.02735
/*14 */     s->avctx = avctx;                                                                                 // (20) 0.02148
/*16 */     s->width = (avctx->width+3)&~3;                                                                   // (14) 0.03711
/*18 */     s->height = (avctx->height+3)&~3;                                                                 // (13) 0.03711
/*20 */     s->codec_id= avctx->codec->id;                                                                    // (15) 0.03516
/*22 */     avctx->pix_fmt = PIX_FMT_YUV410P;                                                                 // (6) 0.04492
/*24 */     avctx->has_b_frames= 1; // not true, but DP frames and these behave like unidirectional b frames  // (2) 0.06055
/*26 */     s->flags= avctx->flags;                                                                           // (19) 0.02344
/*28 */     if (MPV_common_init(s) < 0) return -1;                                                            // (7) 0.04102
/*32 */     init_vlc(&svq1_block_type, 2, 4,                                                                  // (10) 0.03906
/*34 */         &svq1_block_type_vlc[0][1], 2, 1,                                                             // (5) 0.05273
/*36 */         &svq1_block_type_vlc[0][0], 2, 1);                                                            // (4) 0.05273
/*40 */     init_vlc(&svq1_motion_component, 7, 33,                                                           // (8) 0.03906
/*42 */         &mvtab[0][1], 2, 1,                                                                           // (11) 0.03906
/*44 */         &mvtab[0][0], 2, 1);                                                                          // (9) 0.03906
/*48 */     for (i = 0; i < 6; i++) {                                                                         // (17) 0.03125
/*50 */         init_vlc(&svq1_intra_multistage[i], 3, 8,                                                     // (3) 0.05664
/*52 */             &svq1_intra_multistage_vlc[i][0][1], 2, 1,                                                // (0) 0.07031
/*54 */             &svq1_intra_multistage_vlc[i][0][0], 2, 1);                                               // (1) 0.07031
/*56 */         init_vlc(&svq1_inter_multistage[i], 3, 8,                                                     // 0.0
/*58 */             &svq1_inter_multistage_vlc[i][0][1], 2, 1,                                                // 0.0
/*60 */             &svq1_inter_multistage_vlc[i][0][0], 2, 1);                                               // 0.0
/*62 */     }                                                                                                 // 0.0
/*66 */     init_vlc(&svq1_intra_mean, 8, 256,                                                                // 0.0
/*68 */         &svq1_intra_mean_vlc[0][1], 4, 2,                                                             // 0.0
/*70 */         &svq1_intra_mean_vlc[0][0], 4, 2);                                                            // 0.0
/*74 */     init_vlc(&svq1_inter_mean, 9, 512,                                                                // 0.0
/*76 */         &svq1_inter_mean_vlc[0][1], 4, 2,                                                             // 0.0
/*78 */         &svq1_inter_mean_vlc[0][0], 4, 2);                                                            // 0.0
/*82 */     return 0;                                                                                         // 0.0
/*84 */ }                                                                                                     // 0.0
