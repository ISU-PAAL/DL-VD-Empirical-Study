// commit message FFmpeg@8155233413 (target=1, prob=0.33863828, correct=False): fixed layer1/2 overflow if very loud sound - fixed broken free format decoding to pass all mpeg audio standard decoding tests (please avoid patching the parser without having all test streams available - contact me if necessary)
/*0   */ static int decode_header(MPADecodeContext *s, UINT32 header)                   // (4) 0.03718
/*2   */ {                                                                              // (33) 0.001955
/*4   */     int sample_rate, frame_size, mpeg25, padding;                              // (5) 0.03516
/*6   */     int sample_rate_index, bitrate_index;                                      // (16) 0.02929
/*8   */     if (header & (1<<20)) {                                                    // (21) 0.02539
/*10  */         s->lsf = (header & (1<<19)) ? 0 : 1;                                   // (1) 0.04882
/*12  */         mpeg25 = 0;                                                            // (22) 0.02539
/*14  */     } else {                                                                   // (28) 0.01172
/*16  */         s->lsf = 1;                                                            // (19) 0.02734
/*18  */         mpeg25 = 1;                                                            // (23) 0.02539
/*20  */     }                                                                          // (30) 0.007811
/*22  */                                                                                // (31) 0.007811
/*24  */     s->layer = 4 - ((header >> 17) & 3);                                       // (7) 0.0332
/*26  */     /* extract frequency */                                                    // (27) 0.01367
/*28  */     sample_rate_index = (header >> 10) & 3;                                    // (9) 0.0332
/*30  */     sample_rate = mpa_freq_tab[sample_rate_index] >> (s->lsf + mpeg25);        // (0) 0.06249
/*32  */     if (sample_rate == 0)                                                      // (24) 0.02148
/*34  */         return 1;                                                              // (26) 0.01953
/*36  */     sample_rate_index += 3 * (s->lsf + mpeg25);                                // (2) 0.04101
/*38  */     s->sample_rate_index = sample_rate_index;                                  // (10) 0.0332
/*40  */     s->error_protection = ((header >> 16) & 1) ^ 1;                            // (3) 0.03906
/*44  */     bitrate_index = (header >> 12) & 0xf;                                      // (6) 0.03321
/*46  */     padding = (header >> 9) & 1;                                               // (20) 0.02539
/*48  */     //extension = (header >> 8) & 1;                                           // (14) 0.0293
/*50  */     s->mode = (header >> 6) & 3;                                               // (17) 0.02929
/*52  */     s->mode_ext = (header >> 4) & 3;                                           // (8) 0.0332
/*54  */     //copyright = (header >> 3) & 1;                                           // (13) 0.02931
/*56  */     //original = (header >> 2) & 1;                                            // (18) 0.02734
/*58  */     //emphasis = header & 3;                                                   // (25) 0.01954
/*62  */     if (s->mode == MPA_MONO)                                                   // (15) 0.0293
/*64  */         s->nb_channels = 1;                                                    // (12) 0.03125
/*66  */     else                                                                       // (29) 0.007812
/*68  */         s->nb_channels = 2;                                                    // (11) 0.03125
/*70  */                                                                                // (32) 0.007811
/*72  */     if (bitrate_index != 0) {                                                  // 0.0
/*74  */         frame_size = mpa_bitrate_tab[s->lsf][s->layer - 1][bitrate_index];     // 0.0
/*76  */         s->bit_rate = frame_size * 1000;                                       // 0.0
/*78  */         switch(s->layer) {                                                     // 0.0
/*80  */         case 1:                                                                // 0.0
/*82  */             frame_size = (frame_size * 12000) / sample_rate;                   // 0.0
/*84  */             frame_size = (frame_size + padding) * 4;                           // 0.0
/*86  */             break;                                                             // 0.0
/*88  */         case 2:                                                                // 0.0
/*90  */             frame_size = (frame_size * 144000) / sample_rate;                  // 0.0
/*92  */             frame_size += padding;                                             // 0.0
/*94  */             break;                                                             // 0.0
/*96  */         default:                                                               // 0.0
/*98  */         case 3:                                                                // 0.0
/*100 */             frame_size = (frame_size * 144000) / (sample_rate << s->lsf);      // 0.0
/*102 */             frame_size += padding;                                             // 0.0
/*104 */             break;                                                             // 0.0
/*106 */         }                                                                      // 0.0
/*108 */         s->frame_size = frame_size;                                            // 0.0
/*110 */     } else {                                                                   // 0.0
/*112 */         /* if no frame size computed, signal it */                             // 0.0
/*114 */         if (!s->free_format_frame_size)                                        // 0.0
/*116 */             return 1;                                                          // 0.0
/*118 */         /* free format: compute bitrate and real frame size from the           // 0.0
/*120 */            frame size we extracted by reading the bitstream */                 // 0.0
/*122 */         s->frame_size = s->free_format_frame_size;                             // 0.0
/*124 */         switch(s->layer) {                                                     // 0.0
/*126 */         case 1:                                                                // 0.0
/*128 */             s->frame_size += padding  * 4;                                     // 0.0
/*130 */             s->bit_rate = (s->frame_size * sample_rate) / 48000;               // 0.0
/*132 */             break;                                                             // 0.0
/*134 */         case 2:                                                                // 0.0
/*136 */             s->frame_size += padding;                                          // 0.0
/*138 */             s->bit_rate = (s->frame_size * sample_rate) / 144000;              // 0.0
/*140 */             break;                                                             // 0.0
/*142 */         default:                                                               // 0.0
/*144 */         case 3:                                                                // 0.0
/*146 */             s->frame_size += padding;                                          // 0.0
/*148 */             s->bit_rate = (s->frame_size * (sample_rate << s->lsf)) / 144000;  // 0.0
/*150 */             break;                                                             // 0.0
/*152 */         }                                                                      // 0.0
/*154 */     }                                                                          // 0.0
/*156 */     s->sample_rate = sample_rate;                                              // 0.0
/*158 */                                                                                // 0.0
/*160 */ #if defined(DEBUG)                                                             // 0.0
/*162 */     printf("layer%d, %d Hz, %d kbits/s, ",                                     // 0.0
/*164 */            s->layer, s->sample_rate, s->bit_rate);                             // 0.0
/*166 */     if (s->nb_channels == 2) {                                                 // 0.0
/*168 */         if (s->layer == 3) {                                                   // 0.0
/*170 */             if (s->mode_ext & MODE_EXT_MS_STEREO)                              // 0.0
/*172 */                 printf("ms-");                                                 // 0.0
/*174 */             if (s->mode_ext & MODE_EXT_I_STEREO)                               // 0.0
/*176 */                 printf("i-");                                                  // 0.0
/*178 */         }                                                                      // 0.0
/*180 */         printf("stereo");                                                      // 0.0
/*182 */     } else {                                                                   // 0.0
/*184 */         printf("mono");                                                        // 0.0
/*186 */     }                                                                          // 0.0
/*188 */     printf("\n");                                                              // 0.0
/*190 */ #endif                                                                         // 0.0
/*192 */     return 0;                                                                  // 0.0
/*194 */ }                                                                              // 0.0
