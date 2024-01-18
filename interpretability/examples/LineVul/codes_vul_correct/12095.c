// commit message FFmpeg@6a99310fce (target=1, prob=0.90236396, correct=True): wmalosslessdec: Fix reading too many bits in decode_channel_residues()
/*0   */ static int decode_channel_residues(WmallDecodeCtx *s, int ch, int tile_size)                // (5) 0.05469
/*2   */ {                                                                                           // (24) 0.001953
/*4   */     int i = 0;                                                                              // (20) 0.01562
/*6   */     unsigned int ave_mean;                                                                  // (18) 0.01953
/*8   */     s->transient[ch] = get_bits1(&s->gb);                                                   // (9) 0.03906
/*10  */     if (s->transient[ch]) {                                                                 // (17) 0.02539
/*12  */         s->transient_pos[ch] = get_bits(&s->gb, av_log2(tile_size));                        // (3) 0.06641
/*14  */         if (s->transient_pos[ch])                                                           // (12) 0.03516
/*16  */             s->transient[ch] = 0;                                                           // (7) 0.04102
/*18  */         s->channel[ch].transient_counter =                                                  // (11) 0.03516
/*20  */             FFMAX(s->channel[ch].transient_counter, s->samples_per_frame / 2);              // (2) 0.07031
/*22  */     } else if (s->channel[ch].transient_counter)                                            // (10) 0.03516
/*24  */         s->transient[ch] = 1;                                                               // (13) 0.0332
/*28  */     if (s->seekable_tile) {                                                                 // (15) 0.02539
/*30  */         ave_mean = get_bits(&s->gb, s->bits_per_sample);                                    // (6) 0.05469
/*32  */         s->ave_sum[ch] = ave_mean << (s->movave_scaling + 1);                               // (4) 0.06445
/*34  */     }                                                                                       // (23) 0.007812
/*38  */     if (s->seekable_tile) {                                                                 // (16) 0.02539
/*40  */         if (s->do_inter_ch_decorr)                                                          // (8) 0.03906
/*42  */             s->channel_residues[ch][0] = get_sbits(&s->gb, s->bits_per_sample + 1);         // (0) 0.08398
/*44  */         else                                                                                // (21) 0.01562
/*46  */             s->channel_residues[ch][0] = get_sbits(&s->gb, s->bits_per_sample);             // (1) 0.08008
/*48  */         i++;                                                                                // (19) 0.01758
/*50  */     }                                                                                       // (22) 0.007813
/*52  */     for (; i < tile_size; i++) {                                                            // (14) 0.0293
/*54  */         int quo = 0, rem, rem_bits, residue;                                                // 0.0
/*56  */         while(get_bits1(&s->gb)) {                                                          // 0.0
/*58  */             quo++;                                                                          // 0.0
/*60  */             if (get_bits_left(&s->gb) <= 0)                                                 // 0.0
/*62  */                 return -1;                                                                  // 0.0
/*64  */         }                                                                                   // 0.0
/*66  */         if (quo >= 32)                                                                      // 0.0
/*68  */             quo += get_bits_long(&s->gb, get_bits(&s->gb, 5) + 1);                          // 0.0
/*72  */         ave_mean = (s->ave_sum[ch] + (1 << s->movave_scaling)) >> (s->movave_scaling + 1);  // 0.0
/*74  */         if (ave_mean <= 1)                                                                  // 0.0
/*76  */             residue = quo;                                                                  // 0.0
/*78  */         else {                                                                              // 0.0
/*80  */             rem_bits = av_ceil_log2(ave_mean);                                              // 0.0
/*82  */             rem      = rem_bits ? get_bits(&s->gb, rem_bits) : 0;                           // 0.0
/*84  */             residue  = (quo << rem_bits) + rem;                                             // 0.0
/*86  */         }                                                                                   // 0.0
/*90  */         s->ave_sum[ch] = residue + s->ave_sum[ch] -                                         // 0.0
/*92  */                          (s->ave_sum[ch] >> s->movave_scaling);                             // 0.0
/*96  */         if (residue & 1)                                                                    // 0.0
/*98  */             residue = -(residue >> 1) - 1;                                                  // 0.0
/*100 */         else                                                                                // 0.0
/*102 */             residue = residue >> 1;                                                         // 0.0
/*104 */         s->channel_residues[ch][i] = residue;                                               // 0.0
/*106 */     }                                                                                       // 0.0
/*110 */     return 0;                                                                               // 0.0
/*114 */ }                                                                                           // 0.0
