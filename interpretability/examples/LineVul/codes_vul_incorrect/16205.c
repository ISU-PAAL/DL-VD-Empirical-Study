// commit message FFmpeg@63d6a6b91e (target=1, prob=0.32091436, correct=False): Fixed a possible bug, checked against the assembly. No sample that used the code has been found though.
/*0  */ static void fix_coding_method_array (int sb, int channels, sb_int8_array coding_method)                 // (9) 0.05664
/*2  */ {                                                                                                       // (18) 0.001953
/*4  */     int j,k;                                                                                            // (16) 0.01562
/*6  */     int ch;                                                                                             // (17) 0.01172
/*8  */     int run, case_val;                                                                                  // (15) 0.01953
/*10 */     int switchtable[23] = {0,5,1,5,5,5,5,5,2,5,5,5,5,5,5,5,3,5,5,5,5,5,4};                              // (0) 0.1113
/*14 */     for (ch = 0; ch < channels; ch++) {                                                                 // (13) 0.03125
/*16 */         for (j = 0; j < 64; ) {                                                                         // (11) 0.03711
/*18 */             if((coding_method[ch][sb][j] - 8) > 22) {                                                   // (8) 0.06055
/*20 */                 run = 1;                                                                                // (12) 0.03711
/*22 */                 case_val = 8;                                                                           // (10) 0.04102
/*24 */             } else {                                                                                    // (14) 0.02734
/*26 */                 switch (switchtable[coding_method[ch][sb][j]]) {                                        // (7) 0.06445
/*28 */                     case 0: run = 10; case_val = 10; break;                                             // (1) 0.06641
/*30 */                     case 1: run = 1; case_val = 16; break;                                              // (2) 0.06641
/*32 */                     case 2: run = 5; case_val = 24; break;                                              // (3) 0.06641
/*34 */                     case 3: run = 3; case_val = 30; break;                                              // (4) 0.06641
/*36 */                     case 4: run = 1; case_val = 30; break;                                              // (5) 0.06641
/*38 */                     case 5: run = 1; case_val = 8; break;                                               // (6) 0.06641
/*40 */                     default: run = 1; case_val = 8; break;                                              // 0.0
/*42 */                 }                                                                                       // 0.0
/*44 */             }                                                                                           // 0.0
/*46 */             for (k = 0; k < run; k++)                                                                   // 0.0
/*48 */                 if (j + k < 128)                                                                        // 0.0
/*50 */                     if (coding_method[ch][sb + (j + k) / 64][(j + k) % 64] > coding_method[ch][sb][j])  // 0.0
/*52 */                         if (k > 0) {                                                                    // 0.0
/*54 */                            SAMPLES_NEEDED                                                               // 0.0
/*56 */                             //not debugged, almost never used                                           // 0.0
/*58 */                             memset(&coding_method[ch][sb][j + k], case_val, k * sizeof(int8_t));        // 0.0
/*60 */                             memset(&coding_method[ch][sb][j + k], case_val, 3 * sizeof(int8_t));        // 0.0
/*62 */                         }                                                                               // 0.0
/*64 */             j += run;                                                                                   // 0.0
/*66 */         }                                                                                               // 0.0
/*68 */     }                                                                                                   // 0.0
/*70 */ }                                                                                                       // 0.0
