// commit message FFmpeg@50c466d609 (target=1, prob=0.21825682, correct=False): g726enc: use av_assert0() for sample_rate validation
/*0  */ static av_cold int g726_encode_init(AVCodecContext *avctx)                             // (9) 0.04297
/*2  */ {                                                                                      // (24) 0.001953
/*4  */     G726Context* c = avctx->priv_data;                                                 // (12) 0.0332
/*8  */     if (avctx->strict_std_compliance > FF_COMPLIANCE_UNOFFICIAL &&                     // (6) 0.05273
/*10 */         avctx->sample_rate != 8000) {                                                  // (13) 0.0332
/*12 */         av_log(avctx, AV_LOG_ERROR, "Sample rates other than 8kHz are not "            // (3) 0.05859
/*14 */                "allowed when the compliance level is higher than unofficial. "         // (7) 0.05078
/*16 */                "Resample or reduce the compliance level.\n");                          // (8) 0.05078
/*18 */         return AVERROR(EINVAL);                                                        // (14) 0.03125
/*20 */     }                                                                                  // (21) 0.007812
/*22 */     if (avctx->sample_rate <= 0) {                                                     // (16) 0.0293
/*24 */         av_log(avctx, AV_LOG_ERROR, "Samplerate is invalid\n");                        // (4) 0.05664
/*26 */         return -1;                                                                     // (18) 0.02148
/*28 */     }                                                                                  // (20) 0.007812
/*32 */     if(avctx->channels != 1){                                                          // (17) 0.02539
/*34 */         av_log(avctx, AV_LOG_ERROR, "Only mono is supported\n");                       // (5) 0.05469
/*36 */         return -1;                                                                     // (19) 0.02148
/*38 */     }                                                                                  // (22) 0.007812
/*42 */     if (avctx->bit_rate % avctx->sample_rate) {                                        // (11) 0.03906
/*44 */         av_log(avctx, AV_LOG_ERROR, "Bitrate - Samplerate combination is invalid\n");  // (2) 0.06445
/*46 */         return AVERROR(EINVAL);                                                        // (15) 0.03125
/*48 */     }                                                                                  // (23) 0.007812
/*50 */     c->code_size = (avctx->bit_rate + avctx->sample_rate/2) / avctx->sample_rate;      // (1) 0.06641
/*52 */     if (c->code_size < 2 || c->code_size > 5) {                                        // (10) 0.04297
/*54 */         av_log(avctx, AV_LOG_ERROR, "Invalid number of bits %d\n", c->code_size);      // (0) 0.07031
/*56 */         return AVERROR(EINVAL);                                                        // 0.0
/*58 */     }                                                                                  // 0.0
/*60 */     avctx->bits_per_coded_sample = c->code_size;                                       // 0.0
/*64 */     g726_reset(c, c->code_size - 2);                                                   // 0.0
/*68 */     avctx->coded_frame = avcodec_alloc_frame();                                        // 0.0
/*70 */     if (!avctx->coded_frame)                                                           // 0.0
/*72 */         return AVERROR(ENOMEM);                                                        // 0.0
/*74 */     avctx->coded_frame->key_frame = 1;                                                 // 0.0
/*78 */     /* select a frame size that will end on a byte boundary and have a size of         // 0.0
/*80 */        approximately 1024 bytes */                                                     // 0.0
/*82 */     avctx->frame_size = ((int[]){ 4096, 2736, 2048, 1640 })[c->code_size - 2];         // 0.0
/*86 */     return 0;                                                                          // 0.0
/*88 */ }                                                                                      // 0.0
