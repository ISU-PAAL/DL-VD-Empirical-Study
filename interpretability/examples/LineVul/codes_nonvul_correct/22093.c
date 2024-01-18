// commit message FFmpeg@e89f58810d (target=0, prob=0.109702565, correct=True): libx264: remove check_default_settings()
/*0  */ static void check_default_settings(AVCodecContext *avctx)                                  // (14) 0.04071
/*2  */ {                                                                                          // (18) 0.002545
/*4  */     X264Context *x4 = avctx->priv_data;                                                    // (13) 0.04326
/*8  */     int score = 0;                                                                         // (16) 0.02036
/*10 */     score += x4->params.analyse.i_me_range == 0;                                           // (5) 0.05344
/*12 */     score += x4->params.rc.i_qp_step == 3;                                                 // (6) 0.05344
/*14 */     score += x4->params.i_keyint_max == 12;                                                // (11) 0.04835
/*16 */     score += x4->params.rc.i_qp_min == 2;                                                  // (7) 0.05344
/*18 */     score += x4->params.rc.i_qp_max == 31;                                                 // (8) 0.05344
/*20 */     score += x4->params.rc.f_qcompress == 0.5;                                             // (4) 0.05598
/*22 */     score += fabs(x4->params.rc.f_ip_factor - 1.25) < 0.01;                                // (2) 0.07634
/*24 */     score += fabs(x4->params.rc.f_pb_factor - 1.25) < 0.01;                                // (3) 0.07634
/*26 */     score += x4->params.analyse.inter == 0 && x4->params.analyse.i_subpel_refine == 8;     // (0) 0.08906
/*28 */     if (score >= 5) {                                                                      // (15) 0.02545
/*30 */         av_log(avctx, AV_LOG_ERROR, "Default settings detected, using medium profile\n");  // (1) 0.07888
/*32 */         x4->preset = av_strdup("medium");                                                  // (9) 0.05344
/*34 */         if (avctx->bit_rate == 200*1000)                                                   // (10) 0.05089
/*36 */             avctx->crf = 23;                                                               // (12) 0.04835
/*38 */     }                                                                                      // (17) 0.01018
/*40 */ }                                                                                          // (19) 0.002545
