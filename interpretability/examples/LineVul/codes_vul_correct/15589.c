// commit message FFmpeg@ae4c9ddebc (target=1, prob=0.8856489, correct=True): vf_psnr: sse2 optimizations for sum-squared-error.
/*0  */ void compute_images_mse_16bit(PSNRContext *s,                                      // (16) 0.0332
/*2  */                         const uint8_t *main_data[4], const int main_linesizes[4],  // (0) 0.08594
/*4  */                         const uint8_t *ref_data[4], const int ref_linesizes[4],    // (1) 0.08594
/*6  */                         int w, int h, double mse[4])                               // (2) 0.06836
/*8  */ {                                                                                  // (21) 0.001953
/*10 */     int i, c, j;                                                                   // (18) 0.01953
/*14 */     for (c = 0; c < s->nb_components; c++) {                                       // (10) 0.04102
/*16 */         const int outw = s->planewidth[c];                                         // (12) 0.03906
/*18 */         const int outh = s->planeheight[c];                                        // (15) 0.03711
/*20 */         const uint16_t *main_line = (uint16_t *)main_data[c];                      // (4) 0.05664
/*22 */         const uint16_t *ref_line = (uint16_t *)ref_data[c];                        // (5) 0.05664
/*24 */         const int ref_linesize = ref_linesizes[c] / 2;                             // (7) 0.04688
/*26 */         const int main_linesize = main_linesizes[c] / 2;                           // (8) 0.04688
/*28 */         uint64_t m = 0;                                                            // (17) 0.0293
/*32 */         for (i = 0; i < outh; i++) {                                               // (11) 0.04102
/*34 */             for (j = 0; j < outw; j++)                                             // (9) 0.04688
/*36 */                 m += pow2(main_line[j] - ref_line[j]);                             // (3) 0.06445
/*38 */             ref_line += ref_linesize;                                              // (13) 0.03906
/*40 */             main_line += main_linesize;                                            // (14) 0.03906
/*42 */         }                                                                          // (19) 0.01562
/*44 */         mse[c] = m / (double)(outw * outh);                                        // (6) 0.04688
/*46 */     }                                                                              // (20) 0.007813
/*48 */ }                                                                                  // 0.0
