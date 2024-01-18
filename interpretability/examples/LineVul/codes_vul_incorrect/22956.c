// commit message FFmpeg@1f80742f49 (target=1, prob=0.42870256, correct=False): qdm2: avoid integer overflow
/*0   */ static void fill_coding_method_array(sb_int8_array tone_level_idx,                                                   // (8) 0.04688
/*2   */                                      sb_int8_array tone_level_idx_temp,                                              // (0) 0.1016
/*4   */                                      sb_int8_array coding_method,                                                    // (2) 0.09179
/*6   */                                      int nb_channels,                                                                // (4) 0.08398
/*8   */                                      int c, int superblocktype_2_3,                                                  // (1) 0.09375
/*10  */                                      int cm_table_select)                                                            // (5) 0.08398
/*12  */ {                                                                                                                    // (17) 0.001959
/*14  */     int ch, sb, j;                                                                                                   // (15) 0.02148
/*16  */     int tmp, acc, esp_40, comp;                                                                                      // (12) 0.02735
/*18  */     int add1, add2, add3, add4;                                                                                      // (11) 0.03125
/*20  */     int64_t multres;                                                                                                 // (16) 0.01953
/*24  */     if (!superblocktype_2_3) {                                                                                       // (13) 0.02734
/*26  */         /* This case is untested, no samples available */                                                            // (10) 0.03516
/*28  */         SAMPLES_NEEDED                                                                                               // (14) 0.02734
/*30  */         for (ch = 0; ch < nb_channels; ch++)                                                                         // (9) 0.04492
/*32  */             for (sb = 0; sb < 30; sb++) {                                                                            // (7) 0.05078
/*34  */                 for (j = 1; j < 63; j++) {  // The loop only iterates to 63 so the code doesn't overflow the buffer  // (3) 0.08789
/*36  */                     add1 = tone_level_idx[ch][sb][j] - 10;                                                           // (6) 0.07422
/*38  */                     if (add1 < 0)                                                                                    // 0.0
/*40  */                         add1 = 0;                                                                                    // 0.0
/*42  */                     add2 = add3 = add4 = 0;                                                                          // 0.0
/*44  */                     if (sb > 1) {                                                                                    // 0.0
/*46  */                         add2 = tone_level_idx[ch][sb - 2][j] + tone_level_idx_offset_table[sb][0] - 6;               // 0.0
/*48  */                         if (add2 < 0)                                                                                // 0.0
/*50  */                             add2 = 0;                                                                                // 0.0
/*52  */                     }                                                                                                // 0.0
/*54  */                     if (sb > 0) {                                                                                    // 0.0
/*56  */                         add3 = tone_level_idx[ch][sb - 1][j] + tone_level_idx_offset_table[sb][1] - 6;               // 0.0
/*58  */                         if (add3 < 0)                                                                                // 0.0
/*60  */                             add3 = 0;                                                                                // 0.0
/*62  */                     }                                                                                                // 0.0
/*64  */                     if (sb < 29) {                                                                                   // 0.0
/*66  */                         add4 = tone_level_idx[ch][sb + 1][j] + tone_level_idx_offset_table[sb][3] - 6;               // 0.0
/*68  */                         if (add4 < 0)                                                                                // 0.0
/*70  */                             add4 = 0;                                                                                // 0.0
/*72  */                     }                                                                                                // 0.0
/*74  */                     tmp = tone_level_idx[ch][sb][j + 1] * 2 - add4 - add3 - add2 - add1;                             // 0.0
/*76  */                     if (tmp < 0)                                                                                     // 0.0
/*78  */                         tmp = 0;                                                                                     // 0.0
/*80  */                     tone_level_idx_temp[ch][sb][j + 1] = tmp & 0xff;                                                 // 0.0
/*82  */                 }                                                                                                    // 0.0
/*84  */                 tone_level_idx_temp[ch][sb][0] = tone_level_idx_temp[ch][sb][1];                                     // 0.0
/*86  */             }                                                                                                        // 0.0
/*88  */             acc = 0;                                                                                                 // 0.0
/*90  */             for (ch = 0; ch < nb_channels; ch++)                                                                     // 0.0
/*92  */                 for (sb = 0; sb < 30; sb++)                                                                          // 0.0
/*94  */                     for (j = 0; j < 64; j++)                                                                         // 0.0
/*96  */                         acc += tone_level_idx_temp[ch][sb][j];                                                       // 0.0
/*100 */             multres = 0x66666667 * (acc * 10);                                                                       // 0.0
/*102 */             esp_40 = (multres >> 32) / 8 + ((multres & 0xffffffff) >> 31);                                           // 0.0
/*104 */             for (ch = 0;  ch < nb_channels; ch++)                                                                    // 0.0
/*106 */                 for (sb = 0; sb < 30; sb++)                                                                          // 0.0
/*108 */                     for (j = 0; j < 64; j++) {                                                                       // 0.0
/*110 */                         comp = tone_level_idx_temp[ch][sb][j]* esp_40 * 10;                                          // 0.0
/*112 */                         if (comp < 0)                                                                                // 0.0
/*114 */                             comp += 0xff;                                                                            // 0.0
/*116 */                         comp /= 256; // signed shift                                                                 // 0.0
/*118 */                         switch(sb) {                                                                                 // 0.0
/*120 */                             case 0:                                                                                  // 0.0
/*122 */                                 if (comp < 30)                                                                       // 0.0
/*124 */                                     comp = 30;                                                                       // 0.0
/*126 */                                 comp += 15;                                                                          // 0.0
/*128 */                                 break;                                                                               // 0.0
/*130 */                             case 1:                                                                                  // 0.0
/*132 */                                 if (comp < 24)                                                                       // 0.0
/*134 */                                     comp = 24;                                                                       // 0.0
/*136 */                                 comp += 10;                                                                          // 0.0
/*138 */                                 break;                                                                               // 0.0
/*140 */                             case 2:                                                                                  // 0.0
/*142 */                             case 3:                                                                                  // 0.0
/*144 */                             case 4:                                                                                  // 0.0
/*146 */                                 if (comp < 16)                                                                       // 0.0
/*148 */                                     comp = 16;                                                                       // 0.0
/*150 */                         }                                                                                            // 0.0
/*152 */                         if (comp <= 5)                                                                               // 0.0
/*154 */                             tmp = 0;                                                                                 // 0.0
/*156 */                         else if (comp <= 10)                                                                         // 0.0
/*158 */                             tmp = 10;                                                                                // 0.0
/*160 */                         else if (comp <= 16)                                                                         // 0.0
/*162 */                             tmp = 16;                                                                                // 0.0
/*164 */                         else if (comp <= 24)                                                                         // 0.0
/*166 */                             tmp = -1;                                                                                // 0.0
/*168 */                         else                                                                                         // 0.0
/*170 */                             tmp = 0;                                                                                 // 0.0
/*172 */                         coding_method[ch][sb][j] = ((tmp & 0xfffa) + 30 )& 0xff;                                     // 0.0
/*174 */                     }                                                                                                // 0.0
/*176 */             for (sb = 0; sb < 30; sb++)                                                                              // 0.0
/*178 */                 fix_coding_method_array(sb, nb_channels, coding_method);                                             // 0.0
/*180 */             for (ch = 0; ch < nb_channels; ch++)                                                                     // 0.0
/*182 */                 for (sb = 0; sb < 30; sb++)                                                                          // 0.0
/*184 */                     for (j = 0; j < 64; j++)                                                                         // 0.0
/*186 */                         if (sb >= 10) {                                                                              // 0.0
/*188 */                             if (coding_method[ch][sb][j] < 10)                                                       // 0.0
/*190 */                                 coding_method[ch][sb][j] = 10;                                                       // 0.0
/*192 */                         } else {                                                                                     // 0.0
/*194 */                             if (sb >= 2) {                                                                           // 0.0
/*196 */                                 if (coding_method[ch][sb][j] < 16)                                                   // 0.0
/*198 */                                     coding_method[ch][sb][j] = 16;                                                   // 0.0
/*200 */                             } else {                                                                                 // 0.0
/*202 */                                 if (coding_method[ch][sb][j] < 30)                                                   // 0.0
/*204 */                                     coding_method[ch][sb][j] = 30;                                                   // 0.0
/*206 */                             }                                                                                        // 0.0
/*208 */                         }                                                                                            // 0.0
/*210 */     } else { // superblocktype_2_3 != 0                                                                              // 0.0
/*212 */         for (ch = 0; ch < nb_channels; ch++)                                                                         // 0.0
/*214 */             for (sb = 0; sb < 30; sb++)                                                                              // 0.0
/*216 */                 for (j = 0; j < 64; j++)                                                                             // 0.0
/*218 */                     coding_method[ch][sb][j] = coding_method_table[cm_table_select][sb];                             // 0.0
/*220 */     }                                                                                                                // 0.0
/*222 */ }                                                                                                                    // 0.0
