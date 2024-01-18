// commit message FFmpeg@fb14730802 (target=1, prob=0.50650334, correct=True): aac_parser: add required padding for GetBitContext buffer
/*0  */ static int aac_sync(uint64_t state, AACAC3ParseContext *hdr_info,                   // (3) 0.06906
/*2  */         int *need_next_header, int *new_frame_start)                                // (4) 0.06354
/*4  */ {                                                                                   // (20) 0.002762
/*6  */     GetBitContext bits;                                                             // (15) 0.0221
/*8  */     AACADTSHeaderInfo hdr;                                                          // (13) 0.03039
/*10 */     int size;                                                                       // (16) 0.01657
/*12 */     union {                                                                         // (19) 0.01381
/*14 */         uint64_t u64;                                                               // (10) 0.03867
/*16 */         uint8_t  u8[8];                                                             // (8) 0.04696
/*18 */     } tmp;                                                                          // (17) 0.01657
/*22 */     tmp.u64 = av_be2ne64(state);                                                    // (9) 0.04696
/*24 */     init_get_bits(&bits, tmp.u8+8-AAC_ADTS_HEADER_SIZE, AAC_ADTS_HEADER_SIZE * 8);  // (0) 0.1133
/*28 */     if ((size = avpriv_aac_parse_header(&bits, &hdr)) < 0)                          // (2) 0.07182
/*30 */         return 0;                                                                   // (14) 0.02762
/*32 */     *need_next_header = 0;                                                          // (12) 0.03315
/*34 */     *new_frame_start  = 1;                                                          // (11) 0.03591
/*36 */     hdr_info->sample_rate = hdr.sample_rate;                                        // (7) 0.05249
/*38 */     hdr_info->channels    = ff_mpeg4audio_channels[hdr.chan_config];                // (1) 0.08287
/*40 */     hdr_info->samples     = hdr.samples;                                            // (6) 0.05801
/*42 */     hdr_info->bit_rate    = hdr.bit_rate;                                           // (5) 0.06077
/*44 */     return size;                                                                    // (18) 0.01657
/*46 */ }                                                                                   // (21) 0.002762
