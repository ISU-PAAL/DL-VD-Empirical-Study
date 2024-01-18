// commit message FFmpeg@94bb1ce882 (target=0, prob=0.94710207, correct=False): alsdec: check sample pointer range in revert_channel_correlation
/*0   */ static int revert_channel_correlation(ALSDecContext *ctx, ALSBlockData *bd,    // (7) 0.04297
/*2   */                                        ALSChannelData **cd, int *reverted,     // (0) 0.0957
/*4   */                                        unsigned int offset, int c)             // (1) 0.08789
/*6   */ {                                                                              // (23) 0.001953
/*8   */     ALSChannelData *ch = cd[c];                                                // (14) 0.02539
/*10  */     unsigned int   dep = 0;                                                    // (15) 0.02148
/*12  */     unsigned int channels = ctx->avctx->channels;                              // (13) 0.03125
/*16  */     if (reverted[c])                                                           // (18) 0.01953
/*18  */         return 0;                                                              // (16) 0.01953
/*22  */     reverted[c] = 1;                                                           // (17) 0.01953
/*26  */     while (dep < channels && !ch[dep].stop_flag) {                             // (10) 0.03711
/*28  */         revert_channel_correlation(ctx, bd, cd, reverted, offset,              // (5) 0.04883
/*30  */                                    ch[dep].master_channel);                    // (2) 0.08203
/*34  */         dep++;                                                                 // (20) 0.01758
/*36  */     }                                                                          // (21) 0.007812
/*40  */     if (dep == channels) {                                                     // (19) 0.01953
/*42  */         av_log(ctx->avctx, AV_LOG_WARNING, "Invalid channel correlation!\n");  // (3) 0.05859
/*44  */         return AVERROR_INVALIDDATA;                                            // (12) 0.0332
/*46  */     }                                                                          // (22) 0.007812
/*50  */     bd->const_block = ctx->const_block + c;                                    // (11) 0.03711
/*52  */     bd->shift_lsbs  = ctx->shift_lsbs + c;                                     // (8) 0.04297
/*54  */     bd->opt_order   = ctx->opt_order + c;                                      // (9) 0.04102
/*56  */     bd->store_prev_samples = ctx->store_prev_samples + c;                      // (4) 0.04883
/*58  */     bd->use_ltp     = ctx->use_ltp + c;                                        // (6) 0.04883
/*60  */     bd->ltp_lag     = ctx->ltp_lag + c;                                        // 0.0
/*62  */     bd->ltp_gain    = ctx->ltp_gain[c];                                        // 0.0
/*64  */     bd->lpc_cof     = ctx->lpc_cof[c];                                         // 0.0
/*66  */     bd->quant_cof   = ctx->quant_cof[c];                                       // 0.0
/*68  */     bd->raw_samples = ctx->raw_samples[c] + offset;                            // 0.0
/*72  */     dep = 0;                                                                   // 0.0
/*74  */     while (!ch[dep].stop_flag) {                                               // 0.0
/*76  */         unsigned int smp;                                                      // 0.0
/*78  */         unsigned int begin = 1;                                                // 0.0
/*80  */         unsigned int end   = bd->block_length - 1;                             // 0.0
/*82  */         int64_t y;                                                             // 0.0
/*84  */         int32_t *master = ctx->raw_samples[ch[dep].master_channel] + offset;   // 0.0
/*88  */         if (ch[dep].time_diff_flag) {                                          // 0.0
/*90  */             int t = ch[dep].time_diff_index;                                   // 0.0
/*94  */             if (ch[dep].time_diff_sign) {                                      // 0.0
/*96  */                 t      = -t;                                                   // 0.0
/*98  */                 begin -= t;                                                    // 0.0
/*100 */             } else {                                                           // 0.0
/*102 */                 end   -= t;                                                    // 0.0
/*104 */             }                                                                  // 0.0
/*108 */             for (smp = begin; smp < end; smp++) {                              // 0.0
/*110 */                 y  = (1 << 6) +                                                // 0.0
/*112 */                      MUL64(ch[dep].weighting[0], master[smp - 1    ]) +        // 0.0
/*114 */                      MUL64(ch[dep].weighting[1], master[smp        ]) +        // 0.0
/*116 */                      MUL64(ch[dep].weighting[2], master[smp + 1    ]) +        // 0.0
/*118 */                      MUL64(ch[dep].weighting[3], master[smp - 1 + t]) +        // 0.0
/*120 */                      MUL64(ch[dep].weighting[4], master[smp     + t]) +        // 0.0
/*122 */                      MUL64(ch[dep].weighting[5], master[smp + 1 + t]);         // 0.0
/*126 */                 bd->raw_samples[smp] += y >> 7;                                // 0.0
/*128 */             }                                                                  // 0.0
/*130 */         } else {                                                               // 0.0
/*132 */             for (smp = begin; smp < end; smp++) {                              // 0.0
/*134 */                 y  = (1 << 6) +                                                // 0.0
/*136 */                      MUL64(ch[dep].weighting[0], master[smp - 1]) +            // 0.0
/*138 */                      MUL64(ch[dep].weighting[1], master[smp    ]) +            // 0.0
/*140 */                      MUL64(ch[dep].weighting[2], master[smp + 1]);             // 0.0
/*144 */                 bd->raw_samples[smp] += y >> 7;                                // 0.0
/*146 */             }                                                                  // 0.0
/*148 */         }                                                                      // 0.0
/*152 */         dep++;                                                                 // 0.0
/*154 */     }                                                                          // 0.0
/*158 */     return 0;                                                                  // 0.0
/*160 */ }                                                                              // 0.0
