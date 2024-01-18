// commit message FFmpeg@6fd00e9dd9 (target=1, prob=0.47306892, correct=False): aacdec: add decode_channel_map overread check
/*0  */ static int decode_pce(AVCodecContext *avctx, MPEG4AudioConfig *m4ac,                                                                                       // (5) 0.04693
/*2  */                       enum ChannelPosition new_che_pos[4][MAX_ELEM_ID],                                                                                    // (1) 0.07811
/*4  */                       GetBitContext *gb)                                                                                                                   // (4) 0.05272
/*6  */ {                                                                                                                                                          // (21) 0.001955
/*8  */     int num_front, num_side, num_back, num_lfe, num_assoc_data, num_cc, sampling_index;                                                                    // (2) 0.07029
/*10 */     int comment_len;                                                                                                                                       // (20) 0.01565
/*14 */     skip_bits(gb, 2);  // object_type                                                                                                                      // (15) 0.03124
/*18 */     sampling_index = get_bits(gb, 4);                                                                                                                      // (16) 0.02928
/*20 */     if (m4ac->sampling_index != sampling_index)                                                                                                            // (14) 0.03514
/*22 */         av_log(avctx, AV_LOG_WARNING, "Sample rate index in program config element does not match the sample rate index configured by the container.\n");  // (0) 0.08395
/*26 */     num_front       = get_bits(gb, 4);                                                                                                                     // (12) 0.041
/*28 */     num_side        = get_bits(gb, 4);                                                                                                                     // (11) 0.04295
/*30 */     num_back        = get_bits(gb, 4);                                                                                                                     // (10) 0.04295
/*32 */     num_lfe         = get_bits(gb, 2);                                                                                                                     // (7) 0.04686
/*34 */     num_assoc_data  = get_bits(gb, 3);                                                                                                                     // (13) 0.03709
/*36 */     num_cc          = get_bits(gb, 4);                                                                                                                     // (6) 0.04686
/*40 */     if (get_bits1(gb))                                                                                                                                     // (19) 0.02343
/*42 */         skip_bits(gb, 4); // mono_mixdown_tag                                                                                                              // (9) 0.04296
/*44 */     if (get_bits1(gb))                                                                                                                                     // (18) 0.02343
/*46 */         skip_bits(gb, 4); // stereo_mixdown_tag                                                                                                            // (8) 0.04297
/*50 */     if (get_bits1(gb))                                                                                                                                     // (17) 0.02343
/*52 */         skip_bits(gb, 3); // mixdown_coeff_index and pseudo_surround                                                                                       // (3) 0.05483
/*60 */     decode_channel_map(new_che_pos[TYPE_CPE], new_che_pos[TYPE_SCE], AAC_CHANNEL_FRONT, gb, num_front);                                                    // 0.0
/*62 */     decode_channel_map(new_che_pos[TYPE_CPE], new_che_pos[TYPE_SCE], AAC_CHANNEL_SIDE,  gb, num_side );                                                    // 0.0
/*64 */     decode_channel_map(new_che_pos[TYPE_CPE], new_che_pos[TYPE_SCE], AAC_CHANNEL_BACK,  gb, num_back );                                                    // 0.0
/*66 */     decode_channel_map(NULL,                  new_che_pos[TYPE_LFE], AAC_CHANNEL_LFE,   gb, num_lfe  );                                                    // 0.0
/*70 */     skip_bits_long(gb, 4 * num_assoc_data);                                                                                                                // 0.0
/*74 */     decode_channel_map(new_che_pos[TYPE_CCE], new_che_pos[TYPE_CCE], AAC_CHANNEL_CC,    gb, num_cc   );                                                    // 0.0
/*78 */     align_get_bits(gb);                                                                                                                                    // 0.0
/*82 */     /* comment field, first byte is length */                                                                                                              // 0.0
/*84 */     comment_len = get_bits(gb, 8) * 8;                                                                                                                     // 0.0
/*86 */     if (get_bits_left(gb) < comment_len) {                                                                                                                 // 0.0
/*91 */     skip_bits_long(gb, comment_len);                                                                                                                       // 0.0
/*93 */     return 0;                                                                                                                                              // 0.0
