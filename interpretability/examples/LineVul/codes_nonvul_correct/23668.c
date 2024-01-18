// commit message FFmpeg@0058584580 (target=0, prob=0.0465019, correct=True): AC-3 decoder, soc revision 31, Jul 14 23:53:28 2006 UTC by cloud9 Removed _ from names Removed temporary storage for the exponents Removed ctx->samples Now each transform coefficients are stored in audio block as an array of transform coefficients for each channel added ctx->delay (output of later half of previous block) added audio_block->block_output(output of this block)
/*0  */ static int do_bit_allocation(AC3DecodeContext *ctx, int flags)                  // (11) 0.03906
/*2  */ {                                                                               // (22) 0.001953
/*4  */     ac3_audio_block *ab = &ctx->audio_block;                                    // (13) 0.03711
/*6  */     int i, snroffst = 0;                                                        // (17) 0.02539
/*10 */     if (!flags) /* bit allocation is not required */                            // (15) 0.02734
/*12 */         return 0;                                                               // (18) 0.01953
/*16 */     if (ab->flags & AC3_AB_SNROFFSTE) { /* check whether snroffsts are zero */  // (3) 0.05859
/*18 */         snroffst += ab->csnroffst;                                              // (12) 0.03906
/*20 */         if (ab->flags & AC3_AB_CPLINU)                                          // (10) 0.04492
/*22 */             snroffst += ab->cplfsnroffst;                                       // (7) 0.05078
/*24 */         for (i = 0; i < ctx->bsi.nfchans; i++)                                  // (5) 0.05469
/*26 */             snroffst += ab->fsnroffst[i];                                       // (8) 0.05078
/*28 */         if (ctx->bsi.flags & AC3_BSI_LFEON)                                     // (6) 0.05078
/*30 */             snroffst += ab->lfefsnroffst;                                       // (9) 0.04883
/*32 */         if (!snroffst) {                                                        // (14) 0.0293
/*34 */             memset(ab->cplbap, 0, sizeof (ab->cplbap));                         // (1) 0.0625
/*36 */             for (i = 0; i < ctx->bsi.nfchans; i++)                              // (2) 0.0625
/*38 */                 memset(ab->bap[i], 0, sizeof (ab->bap[i]));                     // (0) 0.07227
/*40 */             memset(ab->lfebap, 0, sizeof (ab->lfebap));                         // (4) 0.05859
/*44 */             return 0;                                                           // (16) 0.02734
/*46 */         }                                                                       // (20) 0.01562
/*48 */     }                                                                           // (21) 0.007812
/*52 */     /* perform bit allocation */                                                // (19) 0.01563
/*54 */     if ((ab->flags & AC3_AB_CPLINU) && (flags & 64))                            // 0.0
/*56 */         if (_do_bit_allocation(ctx, 5))                                         // 0.0
/*58 */             return -1;                                                          // 0.0
/*60 */     for (i = 0; i < ctx->bsi.nfchans; i++)                                      // 0.0
/*62 */         if (flags & (1 << i))                                                   // 0.0
/*64 */             if (_do_bit_allocation(ctx, i))                                     // 0.0
/*66 */                 return -1;                                                      // 0.0
/*68 */     if ((ctx->bsi.flags & AC3_BSI_LFEON) && (flags & 32))                       // 0.0
/*70 */         if (_do_bit_allocation(ctx, 6))                                         // 0.0
/*72 */             return -1;                                                          // 0.0
/*76 */     return 0;                                                                   // 0.0
/*78 */ }                                                                               // 0.0
