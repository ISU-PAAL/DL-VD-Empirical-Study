// commit message FFmpeg@cf7d2f2d21 (target=0, prob=0.38858536, correct=True): lavc: Simplify checking quant bias option
/*0   */ static av_cold int dnxhd_encode_init(AVCodecContext *avctx)               // (5) 0.04492
/*2   */ {                                                                         // (29) 0.001953
/*4   */     DNXHDEncContext *ctx = avctx->priv_data;                              // (10) 0.03516
/*6   */     int i, index, bit_depth, ret;                                         // (18) 0.02734
/*10  */     switch (avctx->pix_fmt) {                                             // (17) 0.0293
/*12  */     case AV_PIX_FMT_YUV422P:                                              // (11) 0.0332
/*14  */         bit_depth = 8;                                                    // (20) 0.02539
/*16  */         break;                                                            // (23) 0.01758
/*18  */     case AV_PIX_FMT_YUV422P10:                                            // (9) 0.03516
/*20  */         bit_depth = 10;                                                   // (19) 0.02539
/*22  */         break;                                                            // (24) 0.01758
/*24  */     default:                                                              // (26) 0.009766
/*26  */         av_log(avctx, AV_LOG_ERROR,                                       // (7) 0.03906
/*28  */                "pixel format is incompatible with DNxHD\n");              // (2) 0.05078
/*30  */         return AVERROR(EINVAL);                                           // (13) 0.03125
/*32  */     }                                                                     // (27) 0.007813
/*36  */     ctx->cid = ff_dnxhd_find_cid(avctx, bit_depth);                       // (1) 0.05273
/*38  */     if (!ctx->cid) {                                                      // (21) 0.02148
/*40  */         av_log(avctx, AV_LOG_ERROR,                                       // (8) 0.03906
/*42  */                "video parameters incompatible with DNxHD\n");             // (3) 0.04883
/*44  */         return AVERROR(EINVAL);                                           // (14) 0.03125
/*46  */     }                                                                     // (28) 0.007812
/*48  */     av_log(avctx, AV_LOG_DEBUG, "cid %d\n", ctx->cid);                    // (0) 0.05859
/*52  */     index = ff_dnxhd_get_cid_table(ctx->cid);                             // (6) 0.04492
/*54  */     if (index < 0)                                                        // (25) 0.01758
/*56  */         return index;                                                     // (22) 0.01953
/*58  */     ctx->cid_table = &ff_dnxhd_cid_table[index];                          // (4) 0.04883
/*62  */     ctx->m.avctx    = avctx;                                              // (12) 0.0332
/*64  */     ctx->m.mb_intra = 1;                                                  // (15) 0.0293
/*66  */     ctx->m.h263_aic = 1;                                                  // (16) 0.0293
/*70  */     avctx->bits_per_raw_sample = ctx->cid_table->bit_depth;               // 0.0
/*74  */     ff_blockdsp_init(&ctx->bdsp, avctx);                                  // 0.0
/*76  */     ff_fdctdsp_init(&ctx->m.fdsp, avctx);                                 // 0.0
/*78  */     ff_mpv_idct_init(&ctx->m);                                            // 0.0
/*80  */     ff_mpegvideoencdsp_init(&ctx->m.mpvencdsp, avctx);                    // 0.0
/*82  */     ff_pixblockdsp_init(&ctx->m.pdsp, avctx);                             // 0.0
/*84  */     if (!ctx->m.dct_quantize)                                             // 0.0
/*86  */         ctx->m.dct_quantize = ff_dct_quantize_c;                          // 0.0
/*90  */     if (ctx->cid_table->bit_depth == 10) {                                // 0.0
/*92  */         ctx->m.dct_quantize     = dnxhd_10bit_dct_quantize;               // 0.0
/*94  */         ctx->get_pixels_8x4_sym = dnxhd_10bit_get_pixels_8x4_sym;         // 0.0
/*96  */         ctx->block_width_l2     = 4;                                      // 0.0
/*98  */     } else {                                                              // 0.0
/*100 */         ctx->get_pixels_8x4_sym = dnxhd_8bit_get_pixels_8x4_sym;          // 0.0
/*102 */         ctx->block_width_l2     = 3;                                      // 0.0
/*104 */     }                                                                     // 0.0
/*108 */     if (ARCH_X86)                                                         // 0.0
/*110 */         ff_dnxhdenc_init_x86(ctx);                                        // 0.0
/*114 */     ctx->m.mb_height = (avctx->height + 15) / 16;                         // 0.0
/*116 */     ctx->m.mb_width  = (avctx->width  + 15) / 16;                         // 0.0
/*120 */     if (avctx->flags & AV_CODEC_FLAG_INTERLACED_DCT) {                    // 0.0
/*122 */         ctx->interlaced   = 1;                                            // 0.0
/*124 */         ctx->m.mb_height /= 2;                                            // 0.0
/*126 */     }                                                                     // 0.0
/*130 */     ctx->m.mb_num = ctx->m.mb_height * ctx->m.mb_width;                   // 0.0
/*134 */ #if FF_API_QUANT_BIAS                                                     // 0.0
/*136 */ FF_DISABLE_DEPRECATION_WARNINGS                                           // 0.0
/*138 */     if (ctx->intra_quant_bias == FF_DEFAULT_QUANT_BIAS &&                 // 0.0
/*140 */         avctx->intra_quant_bias != FF_DEFAULT_QUANT_BIAS)                 // 0.0
/*142 */         ctx->intra_quant_bias = avctx->intra_quant_bias;                  // 0.0
/*144 */ FF_ENABLE_DEPRECATION_WARNINGS                                            // 0.0
/*146 */ #endif                                                                    // 0.0
/*148 */     // XXX tune lbias/cbias                                               // 0.0
/*150 */     if ((ret = dnxhd_init_qmat(ctx, ctx->intra_quant_bias, 0)) < 0)       // 0.0
/*152 */         return ret;                                                       // 0.0
/*156 */     /* Avid Nitris hardware decoder requires a minimum amount of padding  // 0.0
/*158 */      * in the coding unit payload */                                      // 0.0
/*160 */     if (ctx->nitris_compat)                                               // 0.0
/*162 */         ctx->min_padding = 1600;                                          // 0.0
/*166 */     if ((ret = dnxhd_init_vlc(ctx)) < 0)                                  // 0.0
/*168 */         return ret;                                                       // 0.0
/*170 */     if ((ret = dnxhd_init_rc(ctx)) < 0)                                   // 0.0
/*172 */         return ret;                                                       // 0.0
/*176 */     FF_ALLOCZ_OR_GOTO(ctx->m.avctx, ctx->slice_size,                      // 0.0
/*178 */                       ctx->m.mb_height * sizeof(uint32_t), fail);         // 0.0
/*180 */     FF_ALLOCZ_OR_GOTO(ctx->m.avctx, ctx->slice_offs,                      // 0.0
/*182 */                       ctx->m.mb_height * sizeof(uint32_t), fail);         // 0.0
/*184 */     FF_ALLOCZ_OR_GOTO(ctx->m.avctx, ctx->mb_bits,                         // 0.0
/*186 */                       ctx->m.mb_num * sizeof(uint16_t), fail);            // 0.0
/*188 */     FF_ALLOCZ_OR_GOTO(ctx->m.avctx, ctx->mb_qscale,                       // 0.0
/*190 */                       ctx->m.mb_num * sizeof(uint8_t), fail);             // 0.0
/*194 */ #if FF_API_CODED_FRAME                                                    // 0.0
/*196 */ FF_DISABLE_DEPRECATION_WARNINGS                                           // 0.0
/*198 */     avctx->coded_frame->key_frame = 1;                                    // 0.0
/*200 */     avctx->coded_frame->pict_type = AV_PICTURE_TYPE_I;                    // 0.0
/*202 */ FF_ENABLE_DEPRECATION_WARNINGS                                            // 0.0
/*204 */ #endif                                                                    // 0.0
/*208 */     if (avctx->thread_count > MAX_THREADS) {                              // 0.0
/*210 */         av_log(avctx, AV_LOG_ERROR, "too many threads\n");                // 0.0
/*212 */         return AVERROR(EINVAL);                                           // 0.0
/*214 */     }                                                                     // 0.0
/*218 */     ctx->thread[0] = ctx;                                                 // 0.0
/*220 */     for (i = 1; i < avctx->thread_count; i++) {                           // 0.0
/*222 */         ctx->thread[i] = av_malloc(sizeof(DNXHDEncContext));              // 0.0
/*224 */         memcpy(ctx->thread[i], ctx, sizeof(DNXHDEncContext));             // 0.0
/*226 */     }                                                                     // 0.0
/*230 */     return 0;                                                             // 0.0
/*232 */ fail:  // for FF_ALLOCZ_OR_GOTO                                           // 0.0
/*234 */     return AVERROR(ENOMEM);                                               // 0.0
/*236 */ }                                                                         // 0.0
