// commit message FFmpeg@ba3f07d061 (target=1, prob=0.49969435, correct=False): wmavoice: fix a signed overflow
/*0   */ static void aw_pulse_set2(WMAVoiceContext *s, GetBitContext *gb,                 // (7) 0.04492
/*2   */                           int block_idx, AMRFixed *fcb)                          // (0) 0.07422
/*4   */ {                                                                                // (23) 0.001953
/*6   */     uint16_t use_mask_mem[9]; // only 5 are used, rest is padding                // (4) 0.04687
/*8   */     uint16_t *use_mask = use_mask_mem + 2;                                       // (13) 0.03906
/*10  */     /* in this function, idx is the index in the 80-bit (+ padding) use_mask     // (5) 0.04687
/*12  */      * bit-array. Since use_mask consists of 16-bit values, the lower 4 bits     // (6) 0.04687
/*14  */      * of idx are the position of the bit within a particular item in the        // (12) 0.03906
/*16  */      * array (0 being the most significant bit, and 15 being the least           // (15) 0.03711
/*18  */      * significant bit), and the remainder (>> 4) is the index in the            // (14) 0.03906
/*20  */      * use_mask[]-array. This is faster and uses less memory than using a        // (10) 0.04297
/*22  */      * 80-byte/80-int array. */                                                  // (18) 0.0293
/*24  */     int pulse_off = s->aw_first_pulse_off[block_idx],                            // (3) 0.04688
/*26  */         pulse_start, n, idx, range, aidx, start_off = 0;                         // (1) 0.05273
/*30  */     /* set offset of first pulse to within this block */                         // (21) 0.02734
/*32  */     if (s->aw_n_pulses[block_idx] > 0)                                           // (9) 0.04492
/*34  */         while (pulse_off + s->aw_pulse_range < 1)                                // (2) 0.04883
/*36  */             pulse_off += fcb->pitch_lag;                                         // (8) 0.04492
/*40  */     /* find range per pulse */                                                   // (22) 0.01758
/*42  */     if (s->aw_n_pulses[0] > 0) {                                                 // (11) 0.04102
/*44  */         if (block_idx == 0) {                                                    // (17) 0.0332
/*46  */             range = 32;                                                          // (19) 0.0293
/*48  */         } else /* block_idx = 1 */ {                                             // (16) 0.03516
/*50  */             range = 8;                                                           // (20) 0.0293
/*52  */             if (s->aw_n_pulses[block_idx] > 0)                                   // 0.0
/*54  */                 pulse_off = s->aw_next_pulse_off_cache;                          // 0.0
/*56  */         }                                                                        // 0.0
/*58  */     } else                                                                       // 0.0
/*60  */         range = 16;                                                              // 0.0
/*62  */     pulse_start = s->aw_n_pulses[block_idx] > 0 ? pulse_off - range / 2 : 0;     // 0.0
/*66  */     /* aw_pulse_set1() already applies pulses around pulse_off (to be exactly,   // 0.0
/*68  */      * in the range of [pulse_off, pulse_off + s->aw_pulse_range], and thus      // 0.0
/*70  */      * we exclude that range from being pulsed again in this function. */        // 0.0
/*72  */     memset(&use_mask[-2], 0, 2 * sizeof(use_mask[0]));                           // 0.0
/*74  */     memset( use_mask,   -1, 5 * sizeof(use_mask[0]));                            // 0.0
/*76  */     memset(&use_mask[5], 0, 2 * sizeof(use_mask[0]));                            // 0.0
/*78  */     if (s->aw_n_pulses[block_idx] > 0)                                           // 0.0
/*80  */         for (idx = pulse_off; idx < MAX_FRAMESIZE / 2; idx += fcb->pitch_lag) {  // 0.0
/*82  */             int excl_range         = s->aw_pulse_range; // always 16 or 24       // 0.0
/*84  */             uint16_t *use_mask_ptr = &use_mask[idx >> 4];                        // 0.0
/*86  */             int first_sh           = 16 - (idx & 15);                            // 0.0
/*88  */             *use_mask_ptr++       &= 0xFFFF << first_sh;                         // 0.0
/*90  */             excl_range            -= first_sh;                                   // 0.0
/*92  */             if (excl_range >= 16) {                                              // 0.0
/*94  */                 *use_mask_ptr++    = 0;                                          // 0.0
/*96  */                 *use_mask_ptr     &= 0xFFFF >> (excl_range - 16);                // 0.0
/*98  */             } else                                                               // 0.0
/*100 */                 *use_mask_ptr     &= 0xFFFF >> excl_range;                       // 0.0
/*102 */         }                                                                        // 0.0
/*106 */     /* find the 'aidx'th offset that is not excluded */                          // 0.0
/*108 */     aidx = get_bits(gb, s->aw_n_pulses[0] > 0 ? 5 - 2 * block_idx : 4);          // 0.0
/*110 */     for (n = 0; n <= aidx; pulse_start++) {                                      // 0.0
/*112 */         for (idx = pulse_start; idx < 0; idx += fcb->pitch_lag) ;                // 0.0
/*114 */         if (idx >= MAX_FRAMESIZE / 2) { // find from zero                        // 0.0
/*116 */             if (use_mask[0])      idx = 0x0F;                                    // 0.0
/*118 */             else if (use_mask[1]) idx = 0x1F;                                    // 0.0
/*120 */             else if (use_mask[2]) idx = 0x2F;                                    // 0.0
/*122 */             else if (use_mask[3]) idx = 0x3F;                                    // 0.0
/*124 */             else if (use_mask[4]) idx = 0x4F;                                    // 0.0
/*126 */             else                  return;                                        // 0.0
/*128 */             idx -= av_log2_16bit(use_mask[idx >> 4]);                            // 0.0
/*130 */         }                                                                        // 0.0
/*132 */         if (use_mask[idx >> 4] & (0x8000 >> (idx & 15))) {                       // 0.0
/*134 */             use_mask[idx >> 4] &= ~(0x8000 >> (idx & 15));                       // 0.0
/*136 */             n++;                                                                 // 0.0
/*138 */             start_off = idx;                                                     // 0.0
/*140 */         }                                                                        // 0.0
/*142 */     }                                                                            // 0.0
/*146 */     fcb->x[fcb->n] = start_off;                                                  // 0.0
/*148 */     fcb->y[fcb->n] = get_bits1(gb) ? -1.0 : 1.0;                                 // 0.0
/*150 */     fcb->n++;                                                                    // 0.0
/*154 */     /* set offset for next block, relative to start of that block */             // 0.0
/*156 */     n = (MAX_FRAMESIZE / 2 - start_off) % fcb->pitch_lag;                        // 0.0
/*158 */     s->aw_next_pulse_off_cache = n ? fcb->pitch_lag - n : 0;                     // 0.0
/*160 */ }                                                                                // 0.0
