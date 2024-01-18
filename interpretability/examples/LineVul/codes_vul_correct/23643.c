// commit message FFmpeg@1bab6f852c (target=1, prob=0.83538526, correct=True): swscale: make access to filter data conditional on filter type.
/*0  */ static void RENAME(yuv2rgb565_1)(SwsContext *c, const int16_t *buf0,                                             // (8) 0.05859
/*2  */                                  const int16_t *ubuf[2], const int16_t *bguf[2],                                 // (0) 0.1055
/*4  */                                  const int16_t *abuf0, uint8_t *dest,                                            // (1) 0.0957
/*6  */                                  int dstW, int uvalpha, int y)                                                   // (5) 0.08594
/*8  */ {                                                                                                                // (13) 0.001953
/*10 */     const int16_t *ubuf0 = ubuf[0], *ubuf1 = ubuf[1];                                                            // (10) 0.05469
/*12 */     const int16_t *buf1= buf0; //FIXME needed for RGB1/BGR1                                                      // (11) 0.05078
/*16 */     if (uvalpha < 2048) { // note this is not correct (shifts chrominance by 0.5 pixels) but it is a bit faster  // (7) 0.06836
/*18 */         __asm__ volatile(                                                                                        // (12) 0.02344
/*20 */             "mov %%"REG_b", "ESP_OFFSET"(%5)        \n\t"                                                        // (6) 0.08203
/*22 */             "mov        %4, %%"REG_b"               \n\t"                                                        // (2) 0.0957
/*24 */             "push %%"REG_BP"                        \n\t"                                                        // (4) 0.0918
/*26 */             YSCALEYUV2RGB1(%%REGBP, %5)                                                                          // (9) 0.05469
/*28 */             "pxor    %%mm7, %%mm7                   \n\t"                                                        // (3) 0.0918
/*30 */             /* mm2=B, %%mm4=G, %%mm5=R, %%mm7=0 */                                                               // 0.0
/*32 */ #ifdef DITHER1XBPP                                                                                               // 0.0
/*34 */             "paddusb "BLUE_DITHER"(%5), %%mm2      \n\t"                                                         // 0.0
/*36 */             "paddusb "GREEN_DITHER"(%5), %%mm4      \n\t"                                                        // 0.0
/*38 */             "paddusb "RED_DITHER"(%5), %%mm5      \n\t"                                                          // 0.0
/*40 */ #endif                                                                                                           // 0.0
/*42 */             WRITERGB16(%%REGb, 8280(%5), %%REGBP)                                                                // 0.0
/*44 */             "pop %%"REG_BP"                         \n\t"                                                        // 0.0
/*46 */             "mov "ESP_OFFSET"(%5), %%"REG_b"        \n\t"                                                        // 0.0
/*48 */             :: "c" (buf0), "d" (buf1), "S" (ubuf0), "D" (ubuf1), "m" (dest),                                     // 0.0
/*50 */                "a" (&c->redDither)                                                                               // 0.0
/*52 */         );                                                                                                       // 0.0
/*54 */     } else {                                                                                                     // 0.0
/*56 */         __asm__ volatile(                                                                                        // 0.0
/*58 */             "mov %%"REG_b", "ESP_OFFSET"(%5)        \n\t"                                                        // 0.0
/*60 */             "mov        %4, %%"REG_b"               \n\t"                                                        // 0.0
/*62 */             "push %%"REG_BP"                        \n\t"                                                        // 0.0
/*64 */             YSCALEYUV2RGB1b(%%REGBP, %5)                                                                         // 0.0
/*66 */             "pxor    %%mm7, %%mm7                   \n\t"                                                        // 0.0
/*68 */             /* mm2=B, %%mm4=G, %%mm5=R, %%mm7=0 */                                                               // 0.0
/*70 */ #ifdef DITHER1XBPP                                                                                               // 0.0
/*72 */             "paddusb "BLUE_DITHER"(%5), %%mm2      \n\t"                                                         // 0.0
/*74 */             "paddusb "GREEN_DITHER"(%5), %%mm4      \n\t"                                                        // 0.0
/*76 */             "paddusb "RED_DITHER"(%5), %%mm5      \n\t"                                                          // 0.0
/*78 */ #endif                                                                                                           // 0.0
/*80 */             WRITERGB16(%%REGb, 8280(%5), %%REGBP)                                                                // 0.0
/*82 */             "pop %%"REG_BP"                         \n\t"                                                        // 0.0
/*84 */             "mov "ESP_OFFSET"(%5), %%"REG_b"        \n\t"                                                        // 0.0
/*86 */             :: "c" (buf0), "d" (buf1), "S" (ubuf0), "D" (ubuf1), "m" (dest),                                     // 0.0
/*88 */                "a" (&c->redDither)                                                                               // 0.0
/*90 */         );                                                                                                       // 0.0
/*92 */     }                                                                                                            // 0.0
/*94 */ }                                                                                                                // 0.0
