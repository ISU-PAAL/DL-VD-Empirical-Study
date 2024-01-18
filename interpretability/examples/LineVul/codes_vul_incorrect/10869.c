// commit message FFmpeg@09ce5519f3 (target=1, prob=0.13917331, correct=False): fate/checkasm: fix use of uninitialized memory on hevc_add_res tests
/*0  */ static void check_add_res(HEVCDSPContext h, int bit_depth)                                               // (11) 0.03906
/*2  */ {                                                                                                        // (20) 0.001953
/*4  */     int i;                                                                                               // (19) 0.01172
/*6  */     LOCAL_ALIGNED_32(int16_t, res0, [32 * 32]);                                                          // (4) 0.04883
/*8  */     LOCAL_ALIGNED_32(int16_t, res1, [32 * 32]);                                                          // (5) 0.04883
/*10 */     LOCAL_ALIGNED_32(uint8_t, dst0, [32 * 32 * 2]);                                                      // (2) 0.05273
/*12 */     LOCAL_ALIGNED_32(uint8_t, dst1, [32 * 32 * 2]);                                                      // (3) 0.05273
/*16 */     for (i = 2; i <= 5; i++) {                                                                           // (18) 0.03125
/*18 */         int block_size = 1 << i;                                                                         // (17) 0.03125
/*20 */         int size = block_size * block_size;                                                              // (14) 0.03516
/*22 */         ptrdiff_t stride = block_size << (bit_depth > 8);                                                // (8) 0.04688
/*24 */         declare_func_emms(AV_CPU_FLAG_MMX, void, uint8_t *dst, int16_t *res, ptrdiff_t stride);          // (1) 0.08984
/*28 */         randomize_buffers(res0, size);                                                                   // (15) 0.03516
/*30 */         randomize_buffers2(dst0, size);                                                                  // (12) 0.03906
/*32 */         memcpy(res1, res0, sizeof(*res0) * size);                                                        // (6) 0.04883
/*34 */         memcpy(dst1, dst0, size);                                                                        // (13) 0.03906
/*38 */         if (check_func(h.add_residual[i - 2], "add_res_%dx%d_%d", block_size, block_size, bit_depth)) {  // (0) 0.09961
/*40 */             call_ref(dst0, res0, stride);                                                                // (9) 0.04688
/*42 */             call_new(dst1, res1, stride);                                                                // (10) 0.04688
/*44 */             if (memcmp(dst0, dst1, size))                                                                // (7) 0.04883
/*46 */                 fail();                                                                                  // (16) 0.0332
/*48 */             bench_new(dst1, res1, stride);                                                               // 0.0
/*50 */         }                                                                                                // 0.0
/*52 */     }                                                                                                    // 0.0
/*54 */ }                                                                                                        // 0.0
