// commit message FFmpeg@03931ecf71 (target=0, prob=0.93935484, correct=False): vf_ssim: remove another obscure double loop.
/*0  */ static float ssim_plane(uint8_t *main, int main_stride,                         // (9) 0.04228
/*2  */                         uint8_t *ref, int ref_stride,                           // (3) 0.07611
/*4  */                         int width, int height, void *temp)                      // (4) 0.06977
/*6  */ {                                                                               // (22) 0.002114
/*8  */     int z = 0;                                                                  // (15) 0.01691
/*10 */     int x, y;                                                                   // (16) 0.01691
/*12 */     float ssim = 0.0;                                                           // (14) 0.02326
/*14 */     int (*sum0)[4] = temp;                                                      // (13) 0.02748
/*16 */     int (*sum1)[4] = sum0 + (width >> 2) + 3;                                   // (8) 0.04651
/*20 */     width >>= 2;                                                                // (17) 0.01691
/*22 */     height >>= 2;                                                               // (18) 0.01691
/*26 */     for (y = 1; y < height; y++) {                                              // (12) 0.03383
/*28 */         for (; z <= y; z++) {                                                   // (11) 0.03594
/*30 */             FFSWAP(void*, sum0, sum1);                                          // (7) 0.05074
/*32 */             for (x = 0; x < width; x+=2)                                        // (6) 0.05285
/*34 */                 ssim_4x4x2_core(&main[4 * (x + z * main_stride)], main_stride,  // (1) 0.09725
/*36 */                                 &ref[4 * (x + z * ref_stride)], ref_stride,     // (0) 0.1099
/*38 */                                 &sum0[x]);                                      // (2) 0.07822
/*40 */         }                                                                       // (19) 0.01691
/*44 */         ssim += ssim_endn(sum0, sum1, width - 1);                               // (5) 0.05497
/*46 */     }                                                                           // (20) 0.008457
/*50 */     return ssim / ((height - 1) * (width - 1));                                 // (10) 0.03805
/*52 */ }                                                                               // (21) 0.002114
