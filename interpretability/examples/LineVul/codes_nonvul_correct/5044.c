// commit message FFmpeg@aefdb735c3 (target=0, prob=0.12839894, correct=True): atrac3: simplify some loop indexing
/*0   */ static void reverse_matrixing(float *su1, float *su2, int *prev_code,  // (9) 0.04688
/*2   */                               int *curr_code)                          // (1) 0.07031
/*4   */ {                                                                      // (19) 0.001953
/*6   */     int i, nsample, band;                                              // (18) 0.02148
/*8   */     float mc1_l, mc1_r, mc2_l, mc2_r;                                  // (11) 0.04687
/*12  */     for (i = 0, band = 0; band < 4 * 256; band += 256, i++) {          // (8) 0.05078
/*14  */         int s1 = prev_code[i];                                         // (15) 0.0332
/*16  */         int s2 = curr_code[i];                                         // (14) 0.03516
/*18  */         nsample = 0;                                                   // (17) 0.02344
/*22  */         if (s1 != s2) {                                                // (16) 0.03125
/*24  */             /* Selector value changed, interpolation needed. */        // (13) 0.04297
/*26  */             mc1_l = matrix_coeffs[s1 * 2    ];                         // (2) 0.05859
/*28  */             mc1_r = matrix_coeffs[s1 * 2 + 1];                         // (4) 0.05664
/*30  */             mc2_l = matrix_coeffs[s2 * 2    ];                         // (3) 0.05859
/*32  */             mc2_r = matrix_coeffs[s2 * 2 + 1];                         // (5) 0.05664
/*36  */             /* Interpolation is done over the first eight samples. */  // (10) 0.04687
/*38  */             for (; nsample < 8; nsample++) {                           // (12) 0.04492
/*40  */                 float c1 = su1[band + nsample];                        // (7) 0.05273
/*42  */                 float c2 = su2[band + nsample];                        // (6) 0.05273
/*44  */                 c2 = c1 * INTERPOLATE(mc1_l, mc2_l, nsample) +         // (0) 0.07617
/*46  */                      c2 * INTERPOLATE(mc1_r, mc2_r, nsample);          // 0.0
/*48  */                 su1[band + nsample] = c2;                              // 0.0
/*50  */                 su2[band + nsample] = c1 * 2.0 - c2;                   // 0.0
/*52  */             }                                                          // 0.0
/*54  */         }                                                              // 0.0
/*58  */         /* Apply the matrix without interpolation. */                  // 0.0
/*60  */         switch (s2) {                                                  // 0.0
/*62  */         case 0:     /* M/S decoding */                                 // 0.0
/*64  */             for (; nsample < 256; nsample++) {                         // 0.0
/*66  */                 float c1 = su1[band + nsample];                        // 0.0
/*68  */                 float c2 = su2[band + nsample];                        // 0.0
/*70  */                 su1[band + nsample] =  c2       * 2.0;                 // 0.0
/*72  */                 su2[band + nsample] = (c1 - c2) * 2.0;                 // 0.0
/*74  */             }                                                          // 0.0
/*76  */             break;                                                     // 0.0
/*78  */         case 1:                                                        // 0.0
/*80  */             for (; nsample < 256; nsample++) {                         // 0.0
/*82  */                 float c1 = su1[band + nsample];                        // 0.0
/*84  */                 float c2 = su2[band + nsample];                        // 0.0
/*86  */                 su1[band + nsample] = (c1 + c2) *  2.0;                // 0.0
/*88  */                 su2[band + nsample] =  c2       * -2.0;                // 0.0
/*90  */             }                                                          // 0.0
/*92  */             break;                                                     // 0.0
/*94  */         case 2:                                                        // 0.0
/*96  */         case 3:                                                        // 0.0
/*98  */             for (; nsample < 256; nsample++) {                         // 0.0
/*100 */                 float c1 = su1[band + nsample];                        // 0.0
/*102 */                 float c2 = su2[band + nsample];                        // 0.0
/*104 */                 su1[band + nsample] = c1 + c2;                         // 0.0
/*106 */                 su2[band + nsample] = c1 - c2;                         // 0.0
/*108 */             }                                                          // 0.0
/*110 */             break;                                                     // 0.0
/*112 */         default:                                                       // 0.0
/*114 */             assert(0);                                                 // 0.0
/*116 */         }                                                              // 0.0
/*118 */     }                                                                  // 0.0
/*120 */ }                                                                      // 0.0
