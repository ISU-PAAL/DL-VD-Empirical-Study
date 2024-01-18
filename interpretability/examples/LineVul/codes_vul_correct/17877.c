// commit message FFmpeg@bacc4b6e81 (target=1, prob=0.97299206, correct=True): avcodec/wmalosslessdec: Use unsigned operations for overflowing cases
/*0  */ static void mclms_predict(WmallDecodeCtx *s, int icoef, int *pred)         // (4) 0.06278
/*2  */ {                                                                          // (18) 0.002242
/*4  */     int ich, i;                                                            // (16) 0.02018
/*6  */     int order        = s->mclms_order;                                     // (9) 0.04709
/*8  */     int num_channels = s->num_channels;                                    // (13) 0.03587
/*12 */     for (ich = 0; ich < num_channels; ich++) {                             // (10) 0.04709
/*14 */         pred[ich] = 0;                                                     // (14) 0.03139
/*16 */         if (!s->is_channel_coded[ich])                                     // (12) 0.0426
/*18 */             continue;                                                      // (15) 0.02915
/*20 */         for (i = 0; i < order * num_channels; i++)                         // (7) 0.05381
/*22 */             pred[ich] += s->mclms_prevvalues[i + s->mclms_recent] *        // (2) 0.08072
/*24 */                          s->mclms_coeffs[i + order * num_channels * ich];  // (0) 0.1031
/*26 */         for (i = 0; i < ich; i++)                                          // (11) 0.04484
/*28 */             pred[ich] += s->channel_residues[i][icoef] *                   // (3) 0.06726
/*30 */                          s->mclms_coeffs_cur[i + num_channels * ich];      // (1) 0.1031
/*32 */         pred[ich] += 1 << s->mclms_scaling - 1;                            // (5) 0.05605
/*34 */         pred[ich] >>= s->mclms_scaling;                                    // (8) 0.04933
/*36 */         s->channel_residues[ich][icoef] += pred[ich];                      // (6) 0.05605
/*38 */     }                                                                      // (17) 0.008969
/*40 */ }                                                                          // (19) 0.002242
