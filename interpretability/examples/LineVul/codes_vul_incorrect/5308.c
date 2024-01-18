// commit message FFmpeg@428098165d (target=1, prob=0.4102131, correct=False): cosmetics attack, part III: Remove all tabs and prettyprint/reindent the code.
/*0   */ SwsFunc yuv2rgb_get_func_ptr (SwsContext *c)                                    // (9) 0.04297
/*2   */ {                                                                               // (34) 0.001953
/*4   */ #if defined(HAVE_MMX2) || defined(HAVE_MMX)                                     // (13) 0.03906
/*6   */     if(c->flags & SWS_CPU_CAPS_MMX2){                                           // (12) 0.04102
/*8   */ 	switch(c->dstFormat){                                                          // (17) 0.01758
/*10  */ 	case PIX_FMT_RGB32: return yuv420_rgb32_MMX2;                                  // (4) 0.04688
/*12  */ 	case PIX_FMT_BGR24: return yuv420_rgb24_MMX2;                                  // (1) 0.04883
/*14  */ 	case PIX_FMT_BGR565: return yuv420_rgb16_MMX2;                                 // (2) 0.04883
/*16  */ 	case PIX_FMT_BGR555: return yuv420_rgb15_MMX2;                                 // (3) 0.04883
/*18  */ 	}                                                                              // (30) 0.003906
/*20  */     }                                                                           // (23) 0.007812
/*22  */     if(c->flags & SWS_CPU_CAPS_MMX){                                            // (14) 0.03906
/*24  */ 	switch(c->dstFormat){                                                          // (18) 0.01758
/*26  */ 	case PIX_FMT_RGB32: return yuv420_rgb32_MMX;                                   // (8) 0.04492
/*28  */ 	case PIX_FMT_BGR24: return yuv420_rgb24_MMX;                                   // (5) 0.04688
/*30  */ 	case PIX_FMT_BGR565: return yuv420_rgb16_MMX;                                  // (6) 0.04688
/*32  */ 	case PIX_FMT_BGR555: return yuv420_rgb15_MMX;                                  // (7) 0.04688
/*34  */ 	}                                                                              // (31) 0.003906
/*36  */     }                                                                           // (24) 0.007812
/*38  */ #endif                                                                          // (32) 0.003906
/*40  */ #ifdef HAVE_MLIB                                                                // (22) 0.01367
/*42  */     {                                                                           // (25) 0.007812
/*44  */ 	SwsFunc t= yuv2rgb_init_mlib(c);                                               // (15) 0.03906
/*46  */ 	if(t) return t;                                                                // (20) 0.01562
/*48  */     }                                                                           // (26) 0.007812
/*50  */ #endif                                                                          // (33) 0.003906
/*52  */ #ifdef HAVE_ALTIVEC                                                             // (19) 0.01563
/*54  */     if (c->flags & SWS_CPU_CAPS_ALTIVEC)                                        // (10) 0.04102
/*56  */     {                                                                           // (27) 0.007812
/*58  */ 	SwsFunc t = yuv2rgb_init_altivec(c);                                           // (11) 0.04102
/*60  */ 	if(t) return t;                                                                // (21) 0.01562
/*62  */     }                                                                           // (28) 0.007812
/*64  */ #endif                                                                          // (29) 0.003906
/*68  */     av_log(c, AV_LOG_WARNING, "No accelerated colorspace conversion found\n");  // (0) 0.04883
/*72  */     switch(c->dstFormat){                                                       // (16) 0.02148
/*74  */     case PIX_FMT_BGR32:                                                         // 0.0
/*76  */     case PIX_FMT_RGB32: return yuv2rgb_c_32;                                    // 0.0
/*78  */     case PIX_FMT_RGB24: return yuv2rgb_c_24_rgb;                                // 0.0
/*80  */     case PIX_FMT_BGR24: return yuv2rgb_c_24_bgr;                                // 0.0
/*82  */     case PIX_FMT_RGB565:                                                        // 0.0
/*84  */     case PIX_FMT_BGR565:                                                        // 0.0
/*86  */     case PIX_FMT_RGB555:                                                        // 0.0
/*88  */     case PIX_FMT_BGR555: return yuv2rgb_c_16;                                   // 0.0
/*90  */     case PIX_FMT_RGB8:                                                          // 0.0
/*92  */     case PIX_FMT_BGR8:  return yuv2rgb_c_8_ordered_dither;                      // 0.0
/*94  */     case PIX_FMT_RGB4:                                                          // 0.0
/*96  */     case PIX_FMT_BGR4:  return yuv2rgb_c_4_ordered_dither;                      // 0.0
/*98  */     case PIX_FMT_RGB4_BYTE:                                                     // 0.0
/*100 */     case PIX_FMT_BGR4_BYTE:  return yuv2rgb_c_4b_ordered_dither;                // 0.0
/*102 */     case PIX_FMT_MONOBLACK:  return yuv2rgb_c_1_ordered_dither;                 // 0.0
/*104 */     default:                                                                    // 0.0
/*106 */     	assert(0);                                                                 // 0.0
/*108 */     }                                                                           // 0.0
/*110 */     return NULL;                                                                // 0.0
/*112 */ }                                                                               // 0.0
