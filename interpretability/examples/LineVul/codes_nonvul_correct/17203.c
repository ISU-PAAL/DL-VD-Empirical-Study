// commit message FFmpeg@e62ef8f2db (target=0, prob=0.3574859, correct=True): Check user-specified cutoff frequency in validate_options().
/*0  */ static av_cold void set_bandwidth(AC3EncodeContext *s, int cutoff)             // (7) 0.04839
/*2  */ {                                                                              // (21) 0.002304
/*4  */     int ch, bw_code;                                                           // (16) 0.02535
/*8  */     if (cutoff) {                                                              // (17) 0.02074
/*10 */         /* calculate bandwidth based on user-specified cutoff frequency */     // (10) 0.04147
/*12 */         int fbw_coeffs;                                                        // (11) 0.03687
/*14 */         cutoff         = av_clip(cutoff, 1, s->sample_rate >> 1);              // (3) 0.07834
/*16 */         fbw_coeffs     = cutoff * 2 * AC3_MAX_COEFS / s->sample_rate;          // (1) 0.08756
/*18 */         bw_code        = av_clip((fbw_coeffs - 73) / 3, 0, 60);                // (0) 0.08986
/*20 */     } else {                                                                   // (18) 0.01382
/*22 */         /* use default bandwidth setting */                                    // (13) 0.02995
/*24 */         /* XXX: should compute the bandwidth according to the frame            // (9) 0.04147
/*26 */            size, so that we avoid annoying high frequency artifacts */         // (8) 0.04839
/*28 */         bw_code = 50;                                                          // (12) 0.03226
/*30 */     }                                                                          // (19) 0.009217
/*34 */     /* set number of coefficients for each channel */                          // (14) 0.02765
/*36 */     for (ch = 0; ch < s->fbw_channels; ch++) {                                 // (5) 0.05069
/*38 */         s->bandwidth_code[ch] = bw_code;                                       // (6) 0.05069
/*40 */         s->nb_coefs[ch]       = bw_code * 3 + 73;                              // (4) 0.07604
/*42 */     }                                                                          // (20) 0.009217
/*44 */     if (s->lfe_on)                                                             // (15) 0.02765
/*46 */         s->nb_coefs[s->lfe_channel] = 7; /* LFE channel always has 7 coefs */  // (2) 0.08295
/*48 */ }                                                                              // (22) 0.002304
