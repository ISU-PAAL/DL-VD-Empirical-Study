// commit message FFmpeg@ca488ad480 (target=1, prob=0.82533044, correct=True): alsdec: Clean up error paths
/*0   */ static int decode_blocks(ALSDecContext *ctx, unsigned int ra_frame,                  // (14) 0.03711
/*2   */                          unsigned int c, const unsigned int *div_blocks,             // (0) 0.07031
/*4   */                          unsigned int *js_blocks)                                    // (2) 0.06055
/*6   */ {                                                                                    // (19) 0.001953
/*8   */     ALSSpecificConfig *sconf = &ctx->sconf;                                          // (16) 0.03125
/*10  */     unsigned int offset = 0;                                                         // (17) 0.01758
/*12  */     unsigned int b;                                                                  // (18) 0.01367
/*14  */     ALSBlockData bd[2] = { { 0 } };                                                  // (15) 0.0332
/*18  */     bd[0].ra_block         = ra_frame;                                               // (12) 0.04687
/*20  */     bd[0].const_block      = ctx->const_block;                                       // (11) 0.04687
/*22  */     bd[0].shift_lsbs       = ctx->shift_lsbs;                                        // (7) 0.05273
/*24  */     bd[0].opt_order        = ctx->opt_order;                                         // (8) 0.05078
/*26  */     bd[0].store_prev_samples = ctx->store_prev_samples;                              // (10) 0.04883
/*28  */     bd[0].use_ltp          = ctx->use_ltp;                                           // (6) 0.05859
/*30  */     bd[0].ltp_lag          = ctx->ltp_lag;                                           // (4) 0.05859
/*32  */     bd[0].ltp_gain         = ctx->ltp_gain[0];                                       // (3) 0.06055
/*34  */     bd[0].quant_cof        = ctx->quant_cof[0];                                      // (5) 0.05859
/*36  */     bd[0].lpc_cof          = ctx->lpc_cof[0];                                        // (1) 0.06641
/*38  */     bd[0].prev_raw_samples = ctx->prev_raw_samples;                                  // (9) 0.04883
/*40  */     bd[0].js_blocks        = *js_blocks;                                             // (13) 0.04687
/*44  */     bd[1].ra_block         = ra_frame;                                               // 0.0
/*46  */     bd[1].const_block      = ctx->const_block;                                       // 0.0
/*48  */     bd[1].shift_lsbs       = ctx->shift_lsbs;                                        // 0.0
/*50  */     bd[1].opt_order        = ctx->opt_order;                                         // 0.0
/*52  */     bd[1].store_prev_samples = ctx->store_prev_samples;                              // 0.0
/*54  */     bd[1].use_ltp          = ctx->use_ltp;                                           // 0.0
/*56  */     bd[1].ltp_lag          = ctx->ltp_lag;                                           // 0.0
/*58  */     bd[1].ltp_gain         = ctx->ltp_gain[0];                                       // 0.0
/*60  */     bd[1].quant_cof        = ctx->quant_cof[0];                                      // 0.0
/*62  */     bd[1].lpc_cof          = ctx->lpc_cof[0];                                        // 0.0
/*64  */     bd[1].prev_raw_samples = ctx->prev_raw_samples;                                  // 0.0
/*66  */     bd[1].js_blocks        = *(js_blocks + 1);                                       // 0.0
/*70  */     // decode all blocks                                                             // 0.0
/*72  */     for (b = 0; b < ctx->num_blocks; b++) {                                          // 0.0
/*74  */         unsigned int s;                                                              // 0.0
/*78  */         bd[0].block_length = div_blocks[b];                                          // 0.0
/*80  */         bd[1].block_length = div_blocks[b];                                          // 0.0
/*84  */         bd[0].raw_samples  = ctx->raw_samples[c    ] + offset;                       // 0.0
/*86  */         bd[1].raw_samples  = ctx->raw_samples[c + 1] + offset;                       // 0.0
/*90  */         bd[0].raw_other    = bd[1].raw_samples;                                      // 0.0
/*92  */         bd[1].raw_other    = bd[0].raw_samples;                                      // 0.0
/*96  */         if(read_decode_block(ctx, &bd[0]) || read_decode_block(ctx, &bd[1])) {       // 0.0
/*98  */             // damaged block, write zero for the rest of the frame                   // 0.0
/*100 */             zero_remaining(b, ctx->num_blocks, div_blocks, bd[0].raw_samples);       // 0.0
/*102 */             zero_remaining(b, ctx->num_blocks, div_blocks, bd[1].raw_samples);       // 0.0
/*104 */             return -1;                                                               // 0.0
/*106 */         }                                                                            // 0.0
/*110 */         // reconstruct joint-stereo blocks                                           // 0.0
/*112 */         if (bd[0].js_blocks) {                                                       // 0.0
/*114 */             if (bd[1].js_blocks)                                                     // 0.0
/*116 */                 av_log(ctx->avctx, AV_LOG_WARNING, "Invalid channel pair!\n");       // 0.0
/*120 */             for (s = 0; s < div_blocks[b]; s++)                                      // 0.0
/*122 */                 bd[0].raw_samples[s] = bd[1].raw_samples[s] - bd[0].raw_samples[s];  // 0.0
/*124 */         } else if (bd[1].js_blocks) {                                                // 0.0
/*126 */             for (s = 0; s < div_blocks[b]; s++)                                      // 0.0
/*128 */                 bd[1].raw_samples[s] = bd[1].raw_samples[s] + bd[0].raw_samples[s];  // 0.0
/*130 */         }                                                                            // 0.0
/*134 */         offset  += div_blocks[b];                                                    // 0.0
/*136 */         bd[0].ra_block = 0;                                                          // 0.0
/*138 */         bd[1].ra_block = 0;                                                          // 0.0
/*140 */     }                                                                                // 0.0
/*144 */     // store carryover raw samples,                                                  // 0.0
/*146 */     // the others channel raw samples are stored by the calling function.            // 0.0
/*148 */     memmove(ctx->raw_samples[c] - sconf->max_order,                                  // 0.0
/*150 */             ctx->raw_samples[c] - sconf->max_order + sconf->frame_length,            // 0.0
/*152 */             sizeof(*ctx->raw_samples[c]) * sconf->max_order);                        // 0.0
/*156 */     return 0;                                                                        // 0.0
/*158 */ }                                                                                    // 0.0
