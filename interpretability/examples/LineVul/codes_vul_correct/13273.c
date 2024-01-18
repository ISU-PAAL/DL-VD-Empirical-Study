// commit message FFmpeg@f37b2d5a68 (target=1, prob=0.99910706, correct=True): aacdec: Fix null pointer crash Fixes bug170 Bug found by: Gautam Gupta
/*0  */ int avpriv_mpeg4audio_get_config(MPEG4AudioConfig *c, const uint8_t *buf,               // (5) 0.05471
/*1  */                                  int bit_size, int sync_extension)                      // (0) 0.08409
/*2  */ {                                                                                       // (22) 0.001955
/*3  */     GetBitContext gb;                                                                   // (21) 0.01758
/*4  */     int specific_config_bitindex;                                                       // (18) 0.02148
/*5  */     init_get_bits(&gb, buf, bit_size);                                                  // (13) 0.0332
/*6  */     c->object_type = get_object_type(&gb);                                              // (15) 0.03319
/*7  */     c->sample_rate = get_sample_rate(&gb, &c->sampling_index);                          // (7) 0.04881
/*8  */     c->chan_config = get_bits(&gb, 4);                                                  // (14) 0.03319
/*9  */     if (c->chan_config < FF_ARRAY_ELEMS(ff_mpeg4audio_channels))                        // (4) 0.05662
/*10 */         c->channels = ff_mpeg4audio_channels[c->chan_config];                           // (6) 0.05272
/*11 */     c->sbr = -1;                                                                        // (20) 0.02148
/*12 */     c->ps  = -1;                                                                        // (19) 0.02148
/*13 */     if (c->object_type == AOT_SBR || (c->object_type == AOT_PS &&                       // (3) 0.05663
/*14 */         // check for W6132 Annex YYYY draft MP3onMP4                                    // (8) 0.045
/*15 */         !(show_bits(&gb, 3) & 0x03 && !(show_bits(&gb, 9) & 0x3F)))) {                  // (1) 0.07615
/*16 */         if (c->object_type == AOT_PS)                                                   // (12) 0.03905
/*17 */             c->ps = 1;                                                                  // (16) 0.03319
/*18 */         c->ext_object_type = AOT_SBR;                                                   // (10) 0.041
/*19 */         c->sbr = 1;                                                                     // (17) 0.02733
/*20 */         c->ext_sample_rate = get_sample_rate(&gb, &c->ext_sampling_index);              // (2) 0.06443
/*21 */         c->object_type = get_object_type(&gb);                                          // (11) 0.041
/*22 */         if (c->object_type == AOT_ER_BSAC)                                              // (9) 0.04491
/*23 */             c->ext_chan_config = get_bits(&gb, 4);                                      // 0.0
/*24 */     } else {                                                                            // 0.0
/*25 */         c->ext_object_type = AOT_NULL;                                                  // 0.0
/*26 */         c->ext_sample_rate = 0;                                                         // 0.0
/*27 */     }                                                                                   // 0.0
/*28 */     specific_config_bitindex = get_bits_count(&gb);                                     // 0.0
/*29 */     if (c->object_type == AOT_ALS) {                                                    // 0.0
/*30 */         skip_bits(&gb, 5);                                                              // 0.0
/*31 */         if (show_bits_long(&gb, 24) != MKBETAG('\0','A','L','S'))                       // 0.0
/*32 */             skip_bits_long(&gb, 24);                                                    // 0.0
/*33 */         specific_config_bitindex = get_bits_count(&gb);                                 // 0.0
/*34 */         if (parse_config_ALS(&gb, c))                                                   // 0.0
/*35 */             return -1;                                                                  // 0.0
/*36 */     }                                                                                   // 0.0
/*37 */     if (c->ext_object_type != AOT_SBR && sync_extension) {                              // 0.0
/*38 */         while (get_bits_left(&gb) > 15) {                                               // 0.0
/*39 */             if (show_bits(&gb, 11) == 0x2b7) { // sync extension                        // 0.0
/*40 */                 get_bits(&gb, 11);                                                      // 0.0
/*41 */                 c->ext_object_type = get_object_type(&gb);                              // 0.0
/*42 */                 if (c->ext_object_type == AOT_SBR && (c->sbr = get_bits1(&gb)) == 1)    // 0.0
/*43 */                     c->ext_sample_rate = get_sample_rate(&gb, &c->ext_sampling_index);  // 0.0
/*44 */                 if (get_bits_left(&gb) > 11 && get_bits(&gb, 11) == 0x548)              // 0.0
/*45 */                     c->ps = get_bits1(&gb);                                             // 0.0
/*46 */                 break;                                                                  // 0.0
/*47 */             } else                                                                      // 0.0
/*48 */                 get_bits1(&gb); // skip 1 bit                                           // 0.0
/*49 */         }                                                                               // 0.0
/*50 */     }                                                                                   // 0.0
/*51 */     //PS requires SBR                                                                   // 0.0
/*52 */     if (!c->sbr)                                                                        // 0.0
/*53 */         c->ps = 0;                                                                      // 0.0
/*54 */     //Limit implicit PS to the HE-AACv2 Profile                                         // 0.0
/*55 */     if ((c->ps == -1 && c->object_type != AOT_AAC_LC) || c->channels & ~0x01)           // 0.0
/*56 */         c->ps = 0;                                                                      // 0.0
/*57 */     return specific_config_bitindex;                                                    // 0.0
/*58 */ }                                                                                       // 0.0
