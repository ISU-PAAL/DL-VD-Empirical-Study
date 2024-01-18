// commit message FFmpeg@a6191d098a (target=0, prob=0.28230134, correct=True): dcaenc: Reverse data layout to prevent data copies during Huffman encoding introduction
/*0   */ static void put_subframe(DCAEncContext *c, int subframe)                                      // (14) 0.03516
/*2   */ {                                                                                             // (24) 0.001953
/*4   */     int i, band, ss, ch;                                                                      // (19) 0.02344
/*8   */     /* Subsubframes count */                                                                  // (20) 0.01758
/*10  */     put_bits(&c->pb, 2, SUBSUBFRAMES -1);                                                     // (8) 0.04102
/*14  */     /* Partial subsubframe sample count: dummy */                                             // (17) 0.02539
/*16  */     put_bits(&c->pb, 3, 0);                                                                   // (15) 0.0293
/*20  */     /* Prediction mode: no ADPCM, in each channel and subband */                              // (12) 0.03711
/*22  */     for (ch = 0; ch < c->fullband_channels; ch++)                                             // (9) 0.04102
/*24  */         for (band = 0; band < DCAENC_SUBBANDS; band++)                                        // (3) 0.05273
/*26  */             put_bits(&c->pb, 1, 0);                                                           // (7) 0.04492
/*30  */     /* Prediction VQ address: not transmitted */                                              // (18) 0.02344
/*32  */     /* Bit allocation index */                                                                // (21) 0.01563
/*34  */     for (ch = 0; ch < c->fullband_channels; ch++)                                             // (10) 0.04102
/*36  */         for (band = 0; band < DCAENC_SUBBANDS; band++)                                        // (4) 0.05273
/*38  */             put_bits(&c->pb, 5, c->abits[band][ch]);                                          // (2) 0.05859
/*42  */     if (SUBSUBFRAMES > 1) {                                                                   // (16) 0.02734
/*44  */         /* Transition mode: none for each channel and subband */                              // (13) 0.03711
/*46  */         for (ch = 0; ch < c->fullband_channels; ch++)                                         // (6) 0.04883
/*48  */             for (band = 0; band < DCAENC_SUBBANDS; band++)                                    // (1) 0.06055
/*50  */                 put_bits(&c->pb, 1, 0); /* codebook A4 */                                     // (0) 0.06445
/*52  */     }                                                                                         // (23) 0.007812
/*56  */     /* Scale factors */                                                                       // (22) 0.01367
/*58  */     for (ch = 0; ch < c->fullband_channels; ch++)                                             // (11) 0.04102
/*60  */         for (band = 0; band < DCAENC_SUBBANDS; band++)                                        // (5) 0.05273
/*62  */             put_bits(&c->pb, 7, c->scale_factor[band][ch]);                                   // 0.0
/*66  */     /* Joint subband scale factor codebook select: not transmitted */                         // 0.0
/*68  */     /* Scale factors for joint subband coding: not transmitted */                             // 0.0
/*70  */     /* Stereo down-mix coefficients: not transmitted */                                       // 0.0
/*72  */     /* Dynamic range coefficient: not transmitted */                                          // 0.0
/*74  */     /* Stde information CRC check word: not transmitted */                                    // 0.0
/*76  */     /* VQ encoded high frequency subbands: not transmitted */                                 // 0.0
/*80  */     /* LFE data: 8 samples and scalefactor */                                                 // 0.0
/*82  */     if (c->lfe_channel) {                                                                     // 0.0
/*84  */         for (i = 0; i < DCA_LFE_SAMPLES; i++)                                                 // 0.0
/*86  */             put_bits(&c->pb, 8, quantize_value(c->downsampled_lfe[i], c->lfe_quant) & 0xff);  // 0.0
/*88  */         put_bits(&c->pb, 8, c->lfe_scale_factor);                                             // 0.0
/*90  */     }                                                                                         // 0.0
/*94  */     /* Audio data (subsubframes) */                                                           // 0.0
/*96  */     for (ss = 0; ss < SUBSUBFRAMES ; ss++)                                                    // 0.0
/*98  */         for (ch = 0; ch < c->fullband_channels; ch++)                                         // 0.0
/*100 */             for (band = 0; band < DCAENC_SUBBANDS; band++)                                    // 0.0
/*102 */                     put_subframe_samples(c, ss, band, ch);                                    // 0.0
/*106 */     /* DSYNC */                                                                               // 0.0
/*108 */     put_bits(&c->pb, 16, 0xffff);                                                             // 0.0
/*110 */ }                                                                                             // 0.0
