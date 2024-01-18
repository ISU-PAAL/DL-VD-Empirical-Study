// commit message FFmpeg@491eaf35ae (target=1, prob=0.5365523, correct=True): Fix out of bound reads in the QDM2 decoder.
/*0   */ static void qdm2_fft_decode_tones (QDM2Context *q, int duration, GetBitContext *gb, int b)                            // (3) 0.06445
/*2   */ {                                                                                                                     // (22) 0.001953
/*4   */     int channel, stereo, phase, exp;                                                                                  // (15) 0.02344
/*6   */     int local_int_4,  local_int_8,  stereo_phase,  local_int_10;                                                      // (6) 0.05664
/*8   */     int local_int_14, stereo_exp, local_int_20, local_int_28;                                                         // (7) 0.05078
/*10  */     int n, offset;                                                                                                    // (20) 0.01562
/*14  */     local_int_4 = 0;                                                                                                  // (16) 0.02148
/*16  */     local_int_28 = 0;                                                                                                 // (17) 0.02148
/*18  */     local_int_20 = 2;                                                                                                 // (18) 0.02148
/*20  */     local_int_8 = (4 - duration);                                                                                     // (14) 0.02734
/*22  */     local_int_10 = 1 << (q->group_order - duration - 1);                                                              // (8) 0.04297
/*24  */     offset = 1;                                                                                                       // (21) 0.01367
/*28  */     while (1) {                                                                                                       // (19) 0.01563
/*30  */         if (q->superblocktype_2_3) {                                                                                  // (10) 0.03906
/*32  */             while ((n = qdm2_get_vlc(gb, &vlc_tab_fft_tone_offset[local_int_8], 1, 2)) < 2) {                         // (0) 0.1035
/*34  */                 offset = 1;                                                                                           // (11) 0.03711
/*36  */                 if (n == 0) {                                                                                         // (9) 0.04297
/*38  */                     local_int_4 += local_int_10;                                                                      // (5) 0.06055
/*40  */                     local_int_28 += (1 << local_int_8);                                                               // (2) 0.06641
/*42  */                 } else {                                                                                              // (12) 0.03516
/*44  */                     local_int_4 += 8*local_int_10;                                                                    // (4) 0.06445
/*46  */                     local_int_28 += (8 << local_int_8);                                                               // (1) 0.06641
/*48  */                 }                                                                                                     // (13) 0.03125
/*50  */             }                                                                                                         // 0.0
/*52  */             offset += (n - 2);                                                                                        // 0.0
/*54  */         } else {                                                                                                      // 0.0
/*56  */             offset += qdm2_get_vlc(gb, &vlc_tab_fft_tone_offset[local_int_8], 1, 2);                                  // 0.0
/*58  */             while (offset >= (local_int_10 - 1)) {                                                                    // 0.0
/*60  */                 offset += (1 - (local_int_10 - 1));                                                                   // 0.0
/*62  */                 local_int_4  += local_int_10;                                                                         // 0.0
/*64  */                 local_int_28 += (1 << local_int_8);                                                                   // 0.0
/*66  */             }                                                                                                         // 0.0
/*68  */         }                                                                                                             // 0.0
/*72  */         if (local_int_4 >= q->group_size)                                                                             // 0.0
/*77  */         local_int_14 = (offset >> local_int_8);                                                                       // 0.0
/*83  */         if (q->nb_channels > 1) {                                                                                     // 0.0
/*85  */             channel = get_bits1(gb);                                                                                  // 0.0
/*87  */             stereo = get_bits1(gb);                                                                                   // 0.0
/*89  */         } else {                                                                                                      // 0.0
/*91  */             channel = 0;                                                                                              // 0.0
/*93  */             stereo = 0;                                                                                               // 0.0
/*95  */         }                                                                                                             // 0.0
/*99  */         exp = qdm2_get_vlc(gb, (b ? &fft_level_exp_vlc : &fft_level_exp_alt_vlc), 0, 2);                              // 0.0
/*101 */         exp += q->fft_level_exp[fft_level_index_table[local_int_14]];                                                 // 0.0
/*103 */         exp = (exp < 0) ? 0 : exp;                                                                                    // 0.0
/*107 */         phase = get_bits(gb, 3);                                                                                      // 0.0
/*109 */         stereo_exp = 0;                                                                                               // 0.0
/*111 */         stereo_phase = 0;                                                                                             // 0.0
/*115 */         if (stereo) {                                                                                                 // 0.0
/*117 */             stereo_exp = (exp - qdm2_get_vlc(gb, &fft_stereo_exp_vlc, 0, 1));                                         // 0.0
/*119 */             stereo_phase = (phase - qdm2_get_vlc(gb, &fft_stereo_phase_vlc, 0, 1));                                   // 0.0
/*121 */             if (stereo_phase < 0)                                                                                     // 0.0
/*123 */                 stereo_phase += 8;                                                                                    // 0.0
/*125 */         }                                                                                                             // 0.0
/*129 */         if (q->frequency_range > (local_int_14 + 1)) {                                                                // 0.0
/*131 */             int sub_packet = (local_int_20 + local_int_28);                                                           // 0.0
/*135 */             qdm2_fft_init_coefficient(q, sub_packet, offset, duration, channel, exp, phase);                          // 0.0
/*137 */             if (stereo)                                                                                               // 0.0
/*139 */                 qdm2_fft_init_coefficient(q, sub_packet, offset, duration, (1 - channel), stereo_exp, stereo_phase);  // 0.0
/*141 */         }                                                                                                             // 0.0
/*145 */         offset++;                                                                                                     // 0.0
/*147 */     }                                                                                                                 // 0.0
/*149 */ }                                                                                                                     // 0.0
