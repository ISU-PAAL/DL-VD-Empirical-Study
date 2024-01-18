// commit message FFmpeg@aac0eda407 (target=0, prob=0.37693432, correct=True): Validate pulse position and error out if an invalid position is encountered.
/*0  */ static int decode_ics(AACContext * ac, SingleChannelElement * sce, GetBitContext * gb, int common_window, int scale_flag) {  // (3) 0.07227
/*2  */     Pulse pulse;                                                                                                             // (21) 0.01172
/*4  */     TemporalNoiseShaping * tns = &sce->tns;                                                                                  // (7) 0.03907
/*6  */     IndividualChannelStream * ics = &sce->ics;                                                                               // (9) 0.03125
/*8  */     float * out = sce->coeffs;                                                                                               // (14) 0.02734
/*10 */     int global_gain, pulse_present = 0;                                                                                      // (13) 0.02735
/*14 */     /* This assignment is to silence a GCC warning about the variable being used                                             // (8) 0.03321
/*16 */      * uninitialized when in fact it always is.                                                                              // (15) 0.02734
/*18 */      */                                                                                                                      // (22) 0.009774
/*20 */     pulse.num_pulse = 0;                                                                                                     // (16) 0.02344
/*24 */     global_gain = get_bits(gb, 8);                                                                                           // (11) 0.02929
/*28 */     if (!common_window && !scale_flag) {                                                                                     // (10) 0.0293
/*30 */         if (decode_ics_info(ac, ics, gb, 0) < 0)                                                                             // (5) 0.05663
/*32 */             return -1;                                                                                                       // (12) 0.02929
/*34 */     }                                                                                                                        // (23) 0.007812
/*38 */     if (decode_band_types(ac, sce->band_type, sce->band_type_run_end, gb, ics) < 0)                                          // (2) 0.08006
/*40 */         return -1;                                                                                                           // (18) 0.02148
/*42 */     if (decode_scalefactors(ac, sce->sf, gb, global_gain, ics, sce->band_type, sce->band_type_run_end) < 0)                  // (0) 0.1015
/*44 */         return -1;                                                                                                           // (17) 0.02148
/*48 */     pulse_present = 0;                                                                                                       // (20) 0.01758
/*50 */     if (!scale_flag) {                                                                                                       // (19) 0.01953
/*52 */         if ((pulse_present = get_bits1(gb))) {                                                                               // (6) 0.04296
/*54 */             if (ics->window_sequence[0] == EIGHT_SHORT_SEQUENCE) {                                                           // (4) 0.06444
/*56 */                 av_log(ac->avccontext, AV_LOG_ERROR, "Pulse tool not allowed in eight short sequence.\n");                   // (1) 0.08988
/*58 */                 return -1;                                                                                                   // 0.0
/*60 */             }                                                                                                                // 0.0
/*62 */             decode_pulses(&pulse, gb, ics->swb_offset);                                                                      // 0.0
/*64 */         }                                                                                                                    // 0.0
/*66 */         if ((tns->present = get_bits1(gb)) && decode_tns(ac, tns, gb, ics))                                                  // 0.0
/*68 */             return -1;                                                                                                       // 0.0
/*70 */         if (get_bits1(gb)) {                                                                                                 // 0.0
/*72 */             av_log_missing_feature(ac->avccontext, "SSR", 1);                                                                // 0.0
/*74 */             return -1;                                                                                                       // 0.0
/*76 */         }                                                                                                                    // 0.0
/*78 */     }                                                                                                                        // 0.0
/*82 */     if (decode_spectrum_and_dequant(ac, out, gb, sce->sf, pulse_present, &pulse, ics, sce->band_type) < 0)                   // 0.0
/*84 */         return -1;                                                                                                           // 0.0
/*86 */     return 0;                                                                                                                // 0.0
/*88 */ }                                                                                                                            // 0.0
