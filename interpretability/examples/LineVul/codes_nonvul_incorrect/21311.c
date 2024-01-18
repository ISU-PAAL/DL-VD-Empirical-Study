// commit message FFmpeg@eb38d8fe92 (target=0, prob=0.5064537, correct=False): qdm2: remove unneeded checks for channel count
/*0   */ static void fill_coding_method_array (sb_int8_array tone_level_idx, sb_int8_array tone_level_idx_temp,               // (1) 0.07812
/*2   */                 sb_int8_array coding_method, int nb_channels,                                                        // (4) 0.06445
/*4   */                 int c, int superblocktype_2_3, int cm_table_select)                                                  // (3) 0.06641
/*6   */ {                                                                                                                    // (21) 0.001956
/*8   */     int ch, sb, j;                                                                                                   // (17) 0.02148
/*10  */     int tmp, acc, esp_40, comp;                                                                                      // (14) 0.02734
/*12  */     int add1, add2, add3, add4;                                                                                      // (12) 0.03125
/*14  */     int64_t multres;                                                                                                 // (18) 0.01953
/*18  */     // This should never happen                                                                                      // (20) 0.01563
/*20  */     if (nb_channels <= 0)                                                                                            // (16) 0.02344
/*22  */         return;                                                                                                      // (19) 0.01758
/*26  */     if (!superblocktype_2_3) {                                                                                       // (13) 0.02734
/*28  */         /* This case is untested, no samples available */                                                            // (11) 0.03516
/*30  */         SAMPLES_NEEDED                                                                                               // (15) 0.02734
/*32  */         for (ch = 0; ch < nb_channels; ch++)                                                                         // (10) 0.04492
/*34  */             for (sb = 0; sb < 30; sb++) {                                                                            // (7) 0.05078
/*36  */                 for (j = 1; j < 63; j++) {  // The loop only iterates to 63 so the code doesn't overflow the buffer  // (0) 0.08789
/*38  */                     add1 = tone_level_idx[ch][sb][j] - 10;                                                           // (2) 0.07422
/*40  */                     if (add1 < 0)                                                                                    // (9) 0.05078
/*42  */                         add1 = 0;                                                                                    // (6) 0.05468
/*44  */                     add2 = add3 = add4 = 0;                                                                          // (5) 0.05859
/*46  */                     if (sb > 1) {                                                                                    // (8) 0.05078
/*48  */                         add2 = tone_level_idx[ch][sb - 2][j] + tone_level_idx_offset_table[sb][0] - 6;               // 0.0
/*50  */                         if (add2 < 0)                                                                                // 0.0
/*52  */                             add2 = 0;                                                                                // 0.0
/*54  */                     }                                                                                                // 0.0
/*56  */                     if (sb > 0) {                                                                                    // 0.0
/*58  */                         add3 = tone_level_idx[ch][sb - 1][j] + tone_level_idx_offset_table[sb][1] - 6;               // 0.0
/*60  */                         if (add3 < 0)                                                                                // 0.0
/*62  */                             add3 = 0;                                                                                // 0.0
/*64  */                     }                                                                                                // 0.0
/*66  */                     if (sb < 29) {                                                                                   // 0.0
/*68  */                         add4 = tone_level_idx[ch][sb + 1][j] + tone_level_idx_offset_table[sb][3] - 6;               // 0.0
/*70  */                         if (add4 < 0)                                                                                // 0.0
/*72  */                             add4 = 0;                                                                                // 0.0
/*74  */                     }                                                                                                // 0.0
/*76  */                     tmp = tone_level_idx[ch][sb][j + 1] * 2 - add4 - add3 - add2 - add1;                             // 0.0
/*78  */                     if (tmp < 0)                                                                                     // 0.0
/*80  */                         tmp = 0;                                                                                     // 0.0
/*82  */                     tone_level_idx_temp[ch][sb][j + 1] = tmp & 0xff;                                                 // 0.0
/*84  */                 }                                                                                                    // 0.0
/*86  */                 tone_level_idx_temp[ch][sb][0] = tone_level_idx_temp[ch][sb][1];                                     // 0.0
/*88  */             }                                                                                                        // 0.0
/*90  */             acc = 0;                                                                                                 // 0.0
/*92  */             for (ch = 0; ch < nb_channels; ch++)                                                                     // 0.0
/*94  */                 for (sb = 0; sb < 30; sb++)                                                                          // 0.0
/*96  */                     for (j = 0; j < 64; j++)                                                                         // 0.0
/*98  */                         acc += tone_level_idx_temp[ch][sb][j];                                                       // 0.0
/*102 */             multres = 0x66666667 * (acc * 10);                                                                       // 0.0
/*104 */             esp_40 = (multres >> 32) / 8 + ((multres & 0xffffffff) >> 31);                                           // 0.0
/*106 */             for (ch = 0;  ch < nb_channels; ch++)                                                                    // 0.0
/*108 */                 for (sb = 0; sb < 30; sb++)                                                                          // 0.0
/*110 */                     for (j = 0; j < 64; j++) {                                                                       // 0.0
/*112 */                         comp = tone_level_idx_temp[ch][sb][j]* esp_40 * 10;                                          // 0.0
/*114 */                         if (comp < 0)                                                                                // 0.0
/*116 */                             comp += 0xff;                                                                            // 0.0
/*118 */                         comp /= 256; // signed shift                                                                 // 0.0
/*120 */                         switch(sb) {                                                                                 // 0.0
/*122 */                             case 0:                                                                                  // 0.0
/*124 */                                 if (comp < 30)                                                                       // 0.0
/*126 */                                     comp = 30;                                                                       // 0.0
/*128 */                                 comp += 15;                                                                          // 0.0
/*130 */                                 break;                                                                               // 0.0
/*132 */                             case 1:                                                                                  // 0.0
/*134 */                                 if (comp < 24)                                                                       // 0.0
/*136 */                                     comp = 24;                                                                       // 0.0
/*138 */                                 comp += 10;                                                                          // 0.0
/*140 */                                 break;                                                                               // 0.0
/*142 */                             case 2:                                                                                  // 0.0
/*144 */                             case 3:                                                                                  // 0.0
/*146 */                             case 4:                                                                                  // 0.0
/*148 */                                 if (comp < 16)                                                                       // 0.0
/*150 */                                     comp = 16;                                                                       // 0.0
/*152 */                         }                                                                                            // 0.0
/*154 */                         if (comp <= 5)                                                                               // 0.0
/*156 */                             tmp = 0;                                                                                 // 0.0
/*158 */                         else if (comp <= 10)                                                                         // 0.0
/*160 */                             tmp = 10;                                                                                // 0.0
/*162 */                         else if (comp <= 16)                                                                         // 0.0
/*164 */                             tmp = 16;                                                                                // 0.0
/*166 */                         else if (comp <= 24)                                                                         // 0.0
/*168 */                             tmp = -1;                                                                                // 0.0
/*170 */                         else                                                                                         // 0.0
/*172 */                             tmp = 0;                                                                                 // 0.0
/*174 */                         coding_method[ch][sb][j] = ((tmp & 0xfffa) + 30 )& 0xff;                                     // 0.0
/*176 */                     }                                                                                                // 0.0
/*178 */             for (sb = 0; sb < 30; sb++)                                                                              // 0.0
/*180 */                 fix_coding_method_array(sb, nb_channels, coding_method);                                             // 0.0
/*182 */             for (ch = 0; ch < nb_channels; ch++)                                                                     // 0.0
/*184 */                 for (sb = 0; sb < 30; sb++)                                                                          // 0.0
/*186 */                     for (j = 0; j < 64; j++)                                                                         // 0.0
/*188 */                         if (sb >= 10) {                                                                              // 0.0
/*190 */                             if (coding_method[ch][sb][j] < 10)                                                       // 0.0
/*192 */                                 coding_method[ch][sb][j] = 10;                                                       // 0.0
/*194 */                         } else {                                                                                     // 0.0
/*196 */                             if (sb >= 2) {                                                                           // 0.0
/*198 */                                 if (coding_method[ch][sb][j] < 16)                                                   // 0.0
/*200 */                                     coding_method[ch][sb][j] = 16;                                                   // 0.0
/*202 */                             } else {                                                                                 // 0.0
/*204 */                                 if (coding_method[ch][sb][j] < 30)                                                   // 0.0
/*206 */                                     coding_method[ch][sb][j] = 30;                                                   // 0.0
/*208 */                             }                                                                                        // 0.0
/*210 */                         }                                                                                            // 0.0
/*212 */     } else { // superblocktype_2_3 != 0                                                                              // 0.0
/*214 */         for (ch = 0; ch < nb_channels; ch++)                                                                         // 0.0
/*216 */             for (sb = 0; sb < 30; sb++)                                                                              // 0.0
/*218 */                 for (j = 0; j < 64; j++)                                                                             // 0.0
/*220 */                     coding_method[ch][sb][j] = coding_method_table[cm_table_select][sb];                             // 0.0
/*222 */     }                                                                                                                // 0.0
/*226 */     return;                                                                                                          // 0.0
/*228 */ }                                                                                                                    // 0.0
