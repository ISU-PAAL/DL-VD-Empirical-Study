// commit message FFmpeg@1f4ff53aea (target=0, prob=0.50849664, correct=False): dnxhddec: Introduce DNXHD_VARIABLE
/*0  */ static int dnxhd_init_vlc(DNXHDContext *ctx, uint32_t cid)                                                                          // (8) 0.05078
/*2  */ {                                                                                                                                   // (18) 0.001953
/*4  */     if (cid != ctx->cid) {                                                                                                          // (14) 0.0293
/*6  */         int index;                                                                                                                  // (15) 0.01953
/*10 */         if ((index = ff_dnxhd_get_cid_table(cid)) < 0) {                                                                            // (6) 0.06055
/*12 */             av_log(ctx->avctx, AV_LOG_ERROR, "unsupported cid %d\n", cid);                                                          // (1) 0.07617
/*14 */             return AVERROR(ENOSYS);                                                                                                 // (13) 0.03906
/*16 */         }                                                                                                                           // (16) 0.01562
/*18 */         if (ff_dnxhd_cid_table[index].bit_depth != ctx->bit_depth) {                                                                // (3) 0.06641
/*20 */             av_log(ctx->avctx, AV_LOG_ERROR, "bit depth mismatches %d %d\n", ff_dnxhd_cid_table[index].bit_depth, ctx->bit_depth);  // (0) 0.1211
/*22 */             return AVERROR_INVALIDDATA;                                                                                             // (10) 0.04102
/*24 */         }                                                                                                                           // (17) 0.01562
/*26 */         ctx->cid_table = &ff_dnxhd_cid_table[index];                                                                                // (7) 0.05664
/*28 */         av_log(ctx->avctx, AV_LOG_VERBOSE, "Profile cid %d.\n", cid);                                                               // (2) 0.07227
/*32 */         ff_free_vlc(&ctx->ac_vlc);                                                                                                  // (11) 0.04102
/*34 */         ff_free_vlc(&ctx->dc_vlc);                                                                                                  // (12) 0.04102
/*36 */         ff_free_vlc(&ctx->run_vlc);                                                                                                 // (9) 0.04102
/*40 */         init_vlc(&ctx->ac_vlc, DNXHD_VLC_BITS, 257,                                                                                 // (5) 0.06055
/*42 */                  ctx->cid_table->ac_bits, 1, 1,                                                                                     // (4) 0.0625
/*44 */                  ctx->cid_table->ac_codes, 2, 2, 0);                                                                                // 0.0
/*46 */         init_vlc(&ctx->dc_vlc, DNXHD_DC_VLC_BITS, ctx->bit_depth + 4,                                                               // 0.0
/*48 */                  ctx->cid_table->dc_bits, 1, 1,                                                                                     // 0.0
/*50 */                  ctx->cid_table->dc_codes, 1, 1, 0);                                                                                // 0.0
/*52 */         init_vlc(&ctx->run_vlc, DNXHD_VLC_BITS, 62,                                                                                 // 0.0
/*54 */                  ctx->cid_table->run_bits, 1, 1,                                                                                    // 0.0
/*56 */                  ctx->cid_table->run_codes, 2, 2, 0);                                                                               // 0.0
/*60 */         ctx->cid = cid;                                                                                                             // 0.0
/*62 */     }                                                                                                                               // 0.0
/*64 */     return 0;                                                                                                                       // 0.0
/*66 */ }                                                                                                                                   // 0.0
