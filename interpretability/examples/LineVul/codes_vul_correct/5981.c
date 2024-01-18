// commit message FFmpeg@009f829dde (target=1, prob=0.5893694, correct=True): swscale: fix crash in bilinear scaling.
/*0  */ static inline void RENAME(yuv2rgb555_2)(SwsContext *c, const uint16_t *buf0,           // (7) 0.06055
/*2  */                                         const uint16_t *buf1, const uint16_t *ubuf0,   // (2) 0.1133
/*4  */                                         const uint16_t *ubuf1, const uint16_t *vbuf0,  // (0) 0.1152
/*6  */                                         const uint16_t *vbuf1, const uint16_t *abuf0,  // (1) 0.1152
/*8  */                                         const uint16_t *abuf1, uint8_t *dest,          // (3) 0.1094
/*10 */                                         int dstW, int yalpha, int uvalpha, int y)      // (4) 0.1074
/*12 */ {                                                                                      // (11) 0.001953
/*14 */     x86_reg uv_off = c->uv_off << 1;                                                   // (9) 0.03906
/*18 */     //Note 8280 == DSTW_OFFSET but the preprocessor can't handle that there :(         // (8) 0.04687
/*20 */     __asm__ volatile(                                                                  // (10) 0.01562
/*22 */         "mov %%"REG_b", "ESP_OFFSET"(%5)        \n\t"                                  // (6) 0.07422
/*24 */         "mov        %4, %%"REG_b"               \n\t"                                  // (5) 0.08789
/*26 */         "push %%"REG_BP"                        \n\t"                                  // 0.0
/*28 */         YSCALEYUV2RGB(%%REGBP, %5, %6)                                                 // 0.0
/*30 */         "pxor    %%mm7, %%mm7                   \n\t"                                  // 0.0
/*32 */         /* mm2=B, %%mm4=G, %%mm5=R, %%mm7=0 */                                         // 0.0
/*34 */ #ifdef DITHER1XBPP                                                                     // 0.0
/*36 */         "paddusb "BLUE_DITHER"(%5), %%mm2      \n\t"                                   // 0.0
/*38 */         "paddusb "GREEN_DITHER"(%5), %%mm4      \n\t"                                  // 0.0
/*40 */         "paddusb "RED_DITHER"(%5), %%mm5      \n\t"                                    // 0.0
/*42 */ #endif                                                                                 // 0.0
/*44 */         WRITERGB15(%%REGb, 8280(%5), %%REGBP)                                          // 0.0
/*46 */         "pop %%"REG_BP"                         \n\t"                                  // 0.0
/*48 */         "mov "ESP_OFFSET"(%5), %%"REG_b"        \n\t"                                  // 0.0
/*50 */         :: "c" (buf0), "d" (buf1), "S" (ubuf0), "D" (ubuf1), "m" (dest),               // 0.0
/*52 */            "a" (&c->redDither), "m"(uv_off)                                            // 0.0
/*54 */     );                                                                                 // 0.0
/*56 */ }                                                                                      // 0.0
