// commit message FFmpeg@73789b85a7 (target=0, prob=0.29598513, correct=True): avcodec/dca_core: always limit frame size to data size
/*0  */ int ff_dca_core_parse(DCACoreDecoder *s, uint8_t *data, int size)         // (1) 0.06286
/*2  */ {                                                                         // (24) 0.002226
/*4  */     int ret;                                                              // (21) 0.01329
/*8  */     s->ext_audio_mask = 0;                                                // (14) 0.02877
/*10 */     s->xch_pos = s->xxch_pos = s->x96_pos = 0;                            // (5) 0.05749
/*14 */     if ((ret = init_get_bits8(&s->gb, data, size)) < 0)                   // (6) 0.05529
/*16 */         return ret;                                                       // (19) 0.02211
/*18 */     s->gb_in = s->gb;                                                     // (15) 0.02877
/*22 */     if ((ret = parse_frame_header(s)) < 0)                                // (10) 0.03985
/*24 */         return ret;                                                       // (20) 0.02211
/*26 */     if ((ret = alloc_sample_buffer(s)) < 0)                               // (11) 0.03982
/*28 */         return ret;                                                       // (18) 0.02211
/*30 */     if ((ret = parse_frame_data(s, HEADER_CORE, 0)) < 0)                  // (4) 0.05756
/*32 */         return ret;                                                       // (17) 0.02212
/*34 */     if ((ret = parse_optional_info(s)) < 0)                               // (9) 0.03986
/*36 */         return ret;                                                       // (16) 0.0226
/*40 */     // Workaround for DTS in WAV                                          // (12) 0.03563
/*42 */     if (s->frame_size > size && s->frame_size < size + 4)                 // (7) 0.05135
/*44 */         s->frame_size = size;                                             // (13) 0.03321
/*48 */     if (ff_dca_seek_bits(&s->gb, s->frame_size * 8)) {                    // (2) 0.05983
/*50 */         av_log(s->avctx, AV_LOG_ERROR, "Read past end of core frame\n");  // (0) 0.07091
/*52 */         if (s->avctx->err_recognition & AV_EF_EXPLODE)                    // (3) 0.05979
/*54 */             return AVERROR_INVALIDDATA;                                   // (8) 0.04657
/*56 */     }                                                                     // (23) 0.008874
/*60 */     return 0;                                                             // (22) 0.01328
/*62 */ }                                                                         // (25) 0.002216
