// commit message FFmpeg@1d16a1cf99 (target=0, prob=0.012012049, correct=True): Rename h264_idct_sse2.asm to h264_idct.asm; move inline IDCT asm from h264dsp_mmx.c to h264_idct.asm (as yasm code). Because the loops are now coded in asm instead of C, this is (depending on the function) up to 50% faster for cases where gcc didn't do a great job at looping.
/*0  */ static void ff_h264_idct8_add_sse2(uint8_t *dst, int16_t *block, int stride)                // (3) 0.06836
/*2  */ {                                                                                           // (14) 0.001953
/*4  */     __asm__ volatile(                                                                       // (13) 0.01562
/*6  */         "movdqa   0x10(%1), %%xmm1 \n"                                                      // (7) 0.05469
/*8  */         "movdqa   0x20(%1), %%xmm2 \n"                                                      // (8) 0.05469
/*10 */         "movdqa   0x30(%1), %%xmm3 \n"                                                      // (9) 0.05469
/*12 */         "movdqa   0x50(%1), %%xmm5 \n"                                                      // (10) 0.05469
/*14 */         "movdqa   0x60(%1), %%xmm6 \n"                                                      // (11) 0.05469
/*16 */         "movdqa   0x70(%1), %%xmm7 \n"                                                      // (12) 0.05469
/*18 */         H264_IDCT8_1D_SSE2(%%xmm0, %%xmm1, %%xmm2, %%xmm3, %%xmm4, %%xmm5, %%xmm6, %%xmm7)  // (0) 0.1191
/*20 */         TRANSPOSE8(%%xmm4, %%xmm1, %%xmm7, %%xmm3, %%xmm5, %%xmm0, %%xmm2, %%xmm6, (%1))    // (2) 0.1074
/*22 */         "paddw          %4, %%xmm4 \n"                                                      // (6) 0.05859
/*24 */         "movdqa     %%xmm4, 0x00(%1) \n"                                                    // (4) 0.06055
/*26 */         "movdqa     %%xmm2, 0x40(%1) \n"                                                    // (5) 0.06055
/*28 */         H264_IDCT8_1D_SSE2(%%xmm4, %%xmm0, %%xmm6, %%xmm3, %%xmm2, %%xmm5, %%xmm7, %%xmm1)  // (1) 0.1191
/*30 */         "movdqa     %%xmm6, 0x60(%1) \n"                                                    // 0.0
/*32 */         "movdqa     %%xmm7, 0x70(%1) \n"                                                    // 0.0
/*34 */         "pxor       %%xmm7, %%xmm7 \n"                                                      // 0.0
/*36 */         STORE_DIFF_8P(%%xmm2, (%0),      %%xmm6, %%xmm7)                                    // 0.0
/*38 */         STORE_DIFF_8P(%%xmm0, (%0,%2),   %%xmm6, %%xmm7)                                    // 0.0
/*40 */         STORE_DIFF_8P(%%xmm1, (%0,%2,2), %%xmm6, %%xmm7)                                    // 0.0
/*42 */         STORE_DIFF_8P(%%xmm3, (%0,%3),   %%xmm6, %%xmm7)                                    // 0.0
/*44 */         "lea     (%0,%2,4), %0 \n"                                                          // 0.0
/*46 */         STORE_DIFF_8P(%%xmm5, (%0),      %%xmm6, %%xmm7)                                    // 0.0
/*48 */         STORE_DIFF_8P(%%xmm4, (%0,%2),   %%xmm6, %%xmm7)                                    // 0.0
/*50 */         "movdqa   0x60(%1), %%xmm0 \n"                                                      // 0.0
/*52 */         "movdqa   0x70(%1), %%xmm1 \n"                                                      // 0.0
/*54 */         STORE_DIFF_8P(%%xmm0, (%0,%2,2), %%xmm6, %%xmm7)                                    // 0.0
/*56 */         STORE_DIFF_8P(%%xmm1, (%0,%3),   %%xmm6, %%xmm7)                                    // 0.0
/*58 */         :"+r"(dst)                                                                          // 0.0
/*60 */         :"r"(block), "r"((x86_reg)stride), "r"((x86_reg)3L*stride), "m"(ff_pw_32)           // 0.0
/*62 */     );                                                                                      // 0.0
/*64 */ }                                                                                           // 0.0
