// commit message FFmpeg@1330a0f31f (target=1, prob=0.21023737, correct=False): avcodec/nvenc: Fix forcing constqp rc mode
/*0   */ static av_cold void nvenc_setup_rate_control(AVCodecContext *avctx)                                  // (7) 0.04492
/*2   */ {                                                                                                    // (22) 0.001953
/*4   */     NvencContext *ctx = avctx->priv_data;                                                            // (13) 0.0332
/*8   */     if (avctx->bit_rate > 0) {                                                                       // (16) 0.0293
/*10  */         ctx->encode_config.rcParams.averageBitRate = avctx->bit_rate;                                // (5) 0.05859
/*12  */     } else if (ctx->encode_config.rcParams.averageBitRate > 0) {                                     // (6) 0.04883
/*14  */         ctx->encode_config.rcParams.maxBitRate = ctx->encode_config.rcParams.averageBitRate;         // (0) 0.07617
/*16  */     }                                                                                                // (21) 0.007812
/*20  */     if (avctx->rc_max_rate > 0)                                                                      // (15) 0.03125
/*22  */         ctx->encode_config.rcParams.maxBitRate = avctx->rc_max_rate;                                 // (3) 0.0625
/*26  */     if (ctx->rc < 0) {                                                                               // (19) 0.02344
/*28  */         if (ctx->flags & NVENC_ONE_PASS)                                                             // (9) 0.03906
/*30  */             ctx->twopass = 0;                                                                        // (10) 0.03906
/*32  */         if (ctx->flags & NVENC_TWO_PASSES)                                                           // (8) 0.04297
/*34  */             ctx->twopass = 1;                                                                        // (11) 0.03906
/*38  */         if (ctx->twopass < 0)                                                                        // (14) 0.0332
/*40  */             ctx->twopass = (ctx->flags & NVENC_LOWLATENCY) != 0;                                     // (2) 0.06836
/*44  */         if (ctx->cbr) {                                                                              // (17) 0.0293
/*46  */             if (ctx->twopass) {                                                                      // (12) 0.03906
/*48  */                 ctx->rc = NV_ENC_PARAMS_RC_2_PASS_QUALITY;                                           // (1) 0.07227
/*50  */             } else {                                                                                 // (18) 0.02734
/*52  */                 ctx->rc = NV_ENC_PARAMS_RC_CBR;                                                      // (4) 0.0625
/*54  */             }                                                                                        // (20) 0.02344
/*56  */         } else if (avctx->global_quality > 0) {                                                      // 0.0
/*58  */             ctx->rc = NV_ENC_PARAMS_RC_CONSTQP;                                                      // 0.0
/*60  */         } else if (ctx->twopass) {                                                                   // 0.0
/*62  */             ctx->rc = NV_ENC_PARAMS_RC_2_PASS_VBR;                                                   // 0.0
/*64  */         } else if (avctx->qmin >= 0 && avctx->qmax >= 0) {                                           // 0.0
/*66  */             ctx->rc = NV_ENC_PARAMS_RC_VBR_MINQP;                                                    // 0.0
/*68  */         }                                                                                            // 0.0
/*70  */     }                                                                                                // 0.0
/*74  */     if (ctx->flags & NVENC_LOSSLESS) {                                                               // 0.0
/*76  */         set_lossless(avctx);                                                                         // 0.0
/*78  */     } else if (ctx->rc > 0) {                                                                        // 0.0
/*80  */         nvenc_override_rate_control(avctx);                                                          // 0.0
/*82  */     } else {                                                                                         // 0.0
/*84  */         ctx->encode_config.rcParams.rateControlMode = NV_ENC_PARAMS_RC_VBR;                          // 0.0
/*86  */         set_vbr(avctx);                                                                              // 0.0
/*88  */     }                                                                                                // 0.0
/*92  */     if (avctx->rc_buffer_size > 0) {                                                                 // 0.0
/*94  */         ctx->encode_config.rcParams.vbvBufferSize = avctx->rc_buffer_size;                           // 0.0
/*96  */     } else if (ctx->encode_config.rcParams.averageBitRate > 0) {                                     // 0.0
/*98  */         ctx->encode_config.rcParams.vbvBufferSize = 2 * ctx->encode_config.rcParams.averageBitRate;  // 0.0
/*100 */     }                                                                                                // 0.0
/*102 */ }                                                                                                    // 0.0
