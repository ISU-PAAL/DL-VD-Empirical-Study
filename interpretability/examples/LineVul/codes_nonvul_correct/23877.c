// commit message FFmpeg@aca490777f (target=0, prob=0.38017583, correct=True): Correct validity checks.
/*0  */ static av_cold int g726_init(AVCodecContext * avctx)                                            // (9) 0.03711
/*2  */ {                                                                                               // (27) 0.001953
/*4  */     AVG726Context* c = (AVG726Context*)avctx->priv_data;                                        // (8) 0.04688
/*6  */     unsigned int index= (avctx->bit_rate + avctx->sample_rate/2) / avctx->sample_rate - 2;      // (2) 0.06641
/*10 */     if (                                                                                        // (22) 0.009766
/*12 */         (avctx->bit_rate != 16000 && avctx->bit_rate != 24000 &&                                // (6) 0.05469
/*14 */          avctx->bit_rate != 32000 && avctx->bit_rate != 40000)) {                               // (5) 0.05664
/*16 */         av_log(avctx, AV_LOG_ERROR, "G726: unsupported audio format\n");                        // (3) 0.06055
/*18 */         return -1;                                                                              // (17) 0.02148
/*20 */     }                                                                                           // (23) 0.007812
/*22 */     if (avctx->sample_rate != 8000 && avctx->strict_std_compliance>FF_COMPLIANCE_INOFFICIAL) {  // (0) 0.07227
/*24 */         av_log(avctx, AV_LOG_ERROR, "G726: unsupported audio format\n");                        // (4) 0.06055
/*26 */         return -1;                                                                              // (19) 0.02148
/*28 */     }                                                                                           // (26) 0.007812
/*30 */     if(avctx->channels != 1){                                                                   // (13) 0.02539
/*32 */         av_log(avctx, AV_LOG_ERROR, "Only mono is supported\n");                                // (7) 0.05469
/*34 */         return -1;                                                                              // (18) 0.02148
/*36 */     }                                                                                           // (24) 0.007812
/*38 */     if(index>3){                                                                                // (21) 0.01758
/*40 */         av_log(avctx, AV_LOG_ERROR, "Unsupported number of bits %d\n", index+2);                // (1) 0.06836
/*42 */         return -1;                                                                              // (20) 0.02148
/*44 */     }                                                                                           // (25) 0.007812
/*46 */     g726_reset(&c->c, index);                                                                   // (12) 0.0293
/*48 */     c->code_size = c->c.tbls->bits;                                                             // (10) 0.03711
/*50 */     c->bit_buffer = 0;                                                                          // (15) 0.02148
/*52 */     c->bits_left = 0;                                                                           // (16) 0.02148
/*56 */     avctx->coded_frame = avcodec_alloc_frame();                                                 // (11) 0.03516
/*58 */     if (!avctx->coded_frame)                                                                    // (14) 0.02344
/*60 */         return AVERROR(ENOMEM);                                                                 // 0.0
/*62 */     avctx->coded_frame->key_frame = 1;                                                          // 0.0
/*66 */     return 0;                                                                                   // 0.0
/*68 */ }                                                                                               // 0.0
