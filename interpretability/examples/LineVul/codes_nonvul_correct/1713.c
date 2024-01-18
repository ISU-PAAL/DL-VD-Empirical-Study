// commit message FFmpeg@a70a3f0b4d (target=0, prob=0.30296195, correct=True): remove some useless initializations (the whole context is initialized to 0)
/*0  */ static int adpcm_decode_init(AVCodecContext * avctx)                 // (7) 0.04726
/*2  */ {                                                                    // (23) 0.002488
/*4  */     ADPCMContext *c = avctx->priv_data;                              // (9) 0.04229
/*8  */     if(avctx->channels > 2U){                                        // (11) 0.03483
/*10 */         return -1;                                                   // (13) 0.02736
/*12 */     }                                                                // (21) 0.00995
/*16 */     c->channel = 0;                                                  // (14) 0.02239
/*18 */     c->status[0].predictor = c->status[1].predictor = 0;             // (4) 0.06219
/*20 */     c->status[0].step_index = c->status[1].step_index = 0;           // (5) 0.06219
/*22 */     c->status[0].step = c->status[1].step = 0;                       // (6) 0.05224
/*26 */     switch(avctx->codec->id) {                                       // (12) 0.03483
/*28 */     case CODEC_ID_ADPCM_CT:                                          // (10) 0.0398
/*30 */         c->status[0].step = c->status[1].step = 511;                 // (3) 0.06468
/*32 */         break;                                                       // (15) 0.02239
/*34 */     case CODEC_ID_ADPCM_IMA_WS:                                      // (8) 0.04726
/*36 */         if (avctx->extradata && avctx->extradata_size == 2 * 4) {    // (2) 0.07463
/*38 */             c->status[0].predictor = AV_RL32(avctx->extradata);      // (1) 0.08209
/*40 */             c->status[1].predictor = AV_RL32(avctx->extradata + 4);  // (0) 0.08706
/*42 */         }                                                            // (18) 0.0199
/*44 */         break;                                                       // (16) 0.02239
/*46 */     default:                                                         // (20) 0.01244
/*48 */         break;                                                       // (17) 0.02239
/*50 */     }                                                                // (22) 0.00995
/*52 */     return 0;                                                        // (19) 0.01493
/*54 */ }                                                                    // (24) 0.002488
