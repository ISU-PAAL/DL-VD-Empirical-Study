// commit message FFmpeg@e7843db3df (target=1, prob=0.20777495, correct=False): swscale: fix invalid conversions and memory problems.
/*0   */ void ff_get_unscaled_swscale(SwsContext *c)                                   // (12) 0.03516
/*2   */ {                                                                             // (23) 0.001953
/*4   */     const enum PixelFormat srcFormat = c->srcFormat;                          // (15) 0.0293
/*6   */     const enum PixelFormat dstFormat = c->dstFormat;                          // (14) 0.03125
/*8   */     const int flags = c->flags;                                               // (18) 0.02148
/*10  */     const int dstH = c->dstH;                                                 // (16) 0.02734
/*12  */     int needsDither;                                                          // (20) 0.01563
/*16  */     needsDither = isAnyRGB(dstFormat) &&                                      // (13) 0.03125
/*18  */             c->dstFormatBpp < 24 &&                                           // (9) 0.04102
/*20  */            (c->dstFormatBpp < c->srcFormatBpp || (!isAnyRGB(srcFormat)));     // (1) 0.06836
/*24  */     /* yv12_to_nv12 */                                                        // (17) 0.02539
/*26  */     if ((srcFormat == PIX_FMT_YUV420P || srcFormat == PIX_FMT_YUVA420P) &&    // (2) 0.06836
/*28  */         (dstFormat == PIX_FMT_NV12 || dstFormat == PIX_FMT_NV21)) {           // (3) 0.06641
/*30  */         c->swScale = planarToNv12Wrapper;                                     // (8) 0.04102
/*32  */     }                                                                         // (21) 0.007812
/*34  */     /* yuv2bgr */                                                             // (19) 0.01953
/*36  */     if ((srcFormat == PIX_FMT_YUV420P || srcFormat == PIX_FMT_YUV422P ||      // (4) 0.06445
/*38  */          srcFormat == PIX_FMT_YUVA420P) && isAnyRGB(dstFormat) &&             // (5) 0.06445
/*40  */         !(flags & SWS_ACCURATE_RND) && !(dstH & 1)) {                         // (6) 0.06055
/*42  */         c->swScale = ff_yuv2rgb_get_func_ptr(c);                              // (7) 0.05469
/*44  */     }                                                                         // (22) 0.007812
/*48  */     if (srcFormat == PIX_FMT_YUV410P &&                                       // (10) 0.03711
/*50  */         (dstFormat == PIX_FMT_YUV420P || dstFormat == PIX_FMT_YUVA420P) &&    // (0) 0.07617
/*52  */         !(flags & SWS_BITEXACT)) {                                            // (11) 0.03711
/*54  */         c->swScale = yvu9ToYv12Wrapper;                                       // 0.0
/*56  */     }                                                                         // 0.0
/*60  */     /* bgr24toYV12 */                                                         // 0.0
/*62  */     if (srcFormat == PIX_FMT_BGR24 &&                                         // 0.0
/*64  */         (dstFormat == PIX_FMT_YUV420P || dstFormat == PIX_FMT_YUVA420P) &&    // 0.0
/*66  */         !(flags & SWS_ACCURATE_RND))                                          // 0.0
/*68  */         c->swScale = bgr24ToYv12Wrapper;                                      // 0.0
/*72  */     /* RGB/BGR -> RGB/BGR (no dither needed forms) */                         // 0.0
/*74  */     if (   isAnyRGB(srcFormat)                                                // 0.0
/*76  */         && isAnyRGB(dstFormat)                                                // 0.0
/*78  */         && srcFormat != PIX_FMT_BGR8      && dstFormat != PIX_FMT_BGR8        // 0.0
/*80  */         && srcFormat != PIX_FMT_RGB8      && dstFormat != PIX_FMT_RGB8        // 0.0
/*82  */         && srcFormat != PIX_FMT_BGR4      && dstFormat != PIX_FMT_BGR4        // 0.0
/*84  */         && srcFormat != PIX_FMT_RGB4      && dstFormat != PIX_FMT_RGB4        // 0.0
/*86  */         && srcFormat != PIX_FMT_BGR4_BYTE && dstFormat != PIX_FMT_BGR4_BYTE   // 0.0
/*88  */         && srcFormat != PIX_FMT_RGB4_BYTE && dstFormat != PIX_FMT_RGB4_BYTE   // 0.0
/*90  */         && srcFormat != PIX_FMT_MONOBLACK && dstFormat != PIX_FMT_MONOBLACK   // 0.0
/*92  */         && srcFormat != PIX_FMT_MONOWHITE && dstFormat != PIX_FMT_MONOWHITE   // 0.0
/*94  */         && srcFormat != PIX_FMT_RGB48LE   && dstFormat != PIX_FMT_RGB48LE     // 0.0
/*96  */         && srcFormat != PIX_FMT_RGB48BE   && dstFormat != PIX_FMT_RGB48BE     // 0.0
/*98  */         && srcFormat != PIX_FMT_BGR48LE   && dstFormat != PIX_FMT_BGR48LE     // 0.0
/*100 */         && srcFormat != PIX_FMT_BGR48BE   && dstFormat != PIX_FMT_BGR48BE     // 0.0
/*102 */         && (!needsDither || (c->flags&(SWS_FAST_BILINEAR|SWS_POINT))))        // 0.0
/*104 */         c->swScale= rgbToRgbWrapper;                                          // 0.0
/*108 */     /* bswap 16 bits per pixel/component packed formats */                    // 0.0
/*110 */     if (IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, PIX_FMT_BGR444) ||       // 0.0
/*112 */         IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, PIX_FMT_BGR48)  ||       // 0.0
/*114 */         IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, PIX_FMT_BGR555) ||       // 0.0
/*116 */         IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, PIX_FMT_BGR565) ||       // 0.0
/*118 */         IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, PIX_FMT_GRAY16) ||       // 0.0
/*120 */         IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, PIX_FMT_RGB444) ||       // 0.0
/*122 */         IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, PIX_FMT_RGB48)  ||       // 0.0
/*124 */         IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, PIX_FMT_RGB555) ||       // 0.0
/*126 */         IS_DIFFERENT_ENDIANESS(srcFormat, dstFormat, PIX_FMT_RGB565))         // 0.0
/*128 */         c->swScale = packed_16bpc_bswap;                                      // 0.0
/*132 */     if ((usePal(srcFormat) && (                                               // 0.0
/*134 */         dstFormat == PIX_FMT_RGB32   ||                                       // 0.0
/*136 */         dstFormat == PIX_FMT_RGB32_1 ||                                       // 0.0
/*138 */         dstFormat == PIX_FMT_RGB24   ||                                       // 0.0
/*140 */         dstFormat == PIX_FMT_BGR32   ||                                       // 0.0
/*142 */         dstFormat == PIX_FMT_BGR32_1 ||                                       // 0.0
/*144 */         dstFormat == PIX_FMT_BGR24)))                                         // 0.0
/*146 */         c->swScale = palToRgbWrapper;                                         // 0.0
/*150 */     if (srcFormat == PIX_FMT_YUV422P) {                                       // 0.0
/*152 */         if (dstFormat == PIX_FMT_YUYV422)                                     // 0.0
/*154 */             c->swScale = yuv422pToYuy2Wrapper;                                // 0.0
/*156 */         else if (dstFormat == PIX_FMT_UYVY422)                                // 0.0
/*158 */             c->swScale = yuv422pToUyvyWrapper;                                // 0.0
/*160 */     }                                                                         // 0.0
/*164 */     /* LQ converters if -sws 0 or -sws 4*/                                    // 0.0
/*166 */     if (c->flags&(SWS_FAST_BILINEAR|SWS_POINT)) {                             // 0.0
/*168 */         /* yv12_to_yuy2 */                                                    // 0.0
/*170 */         if (srcFormat == PIX_FMT_YUV420P || srcFormat == PIX_FMT_YUVA420P) {  // 0.0
/*172 */             if (dstFormat == PIX_FMT_YUYV422)                                 // 0.0
/*174 */                 c->swScale = planarToYuy2Wrapper;                             // 0.0
/*176 */             else if (dstFormat == PIX_FMT_UYVY422)                            // 0.0
/*178 */                 c->swScale = planarToUyvyWrapper;                             // 0.0
/*180 */         }                                                                     // 0.0
/*182 */     }                                                                         // 0.0
/*184 */     if (srcFormat == PIX_FMT_YUYV422 &&                                       // 0.0
/*186 */        (dstFormat == PIX_FMT_YUV420P || dstFormat == PIX_FMT_YUVA420P))       // 0.0
/*188 */         c->swScale = yuyvToYuv420Wrapper;                                     // 0.0
/*190 */     if (srcFormat == PIX_FMT_UYVY422 &&                                       // 0.0
/*192 */        (dstFormat == PIX_FMT_YUV420P || dstFormat == PIX_FMT_YUVA420P))       // 0.0
/*194 */         c->swScale = uyvyToYuv420Wrapper;                                     // 0.0
/*196 */     if (srcFormat == PIX_FMT_YUYV422 && dstFormat == PIX_FMT_YUV422P)         // 0.0
/*198 */         c->swScale = yuyvToYuv422Wrapper;                                     // 0.0
/*200 */     if (srcFormat == PIX_FMT_UYVY422 && dstFormat == PIX_FMT_YUV422P)         // 0.0
/*202 */         c->swScale = uyvyToYuv422Wrapper;                                     // 0.0
/*206 */     /* simple copy */                                                         // 0.0
/*208 */     if ( srcFormat == dstFormat ||                                            // 0.0
/*210 */         (srcFormat == PIX_FMT_YUVA420P && dstFormat == PIX_FMT_YUV420P) ||    // 0.0
/*212 */         (srcFormat == PIX_FMT_YUV420P && dstFormat == PIX_FMT_YUVA420P) ||    // 0.0
/*214 */         (isPlanarYUV(srcFormat) && isGray(dstFormat)) ||                      // 0.0
/*216 */         (isPlanarYUV(dstFormat) && isGray(srcFormat)) ||                      // 0.0
/*218 */         (isGray(dstFormat) && isGray(srcFormat)) ||                           // 0.0
/*220 */         (isPlanarYUV(srcFormat) && isPlanarYUV(dstFormat) &&                  // 0.0
/*222 */          c->chrDstHSubSample == c->chrSrcHSubSample &&                        // 0.0
/*224 */          c->chrDstVSubSample == c->chrSrcVSubSample &&                        // 0.0
/*226 */          dstFormat != PIX_FMT_NV12 && dstFormat != PIX_FMT_NV21 &&            // 0.0
/*228 */          srcFormat != PIX_FMT_NV12 && srcFormat != PIX_FMT_NV21))             // 0.0
/*230 */     {                                                                         // 0.0
/*232 */         if (isPacked(c->srcFormat))                                           // 0.0
/*234 */             c->swScale = packedCopyWrapper;                                   // 0.0
/*236 */         else /* Planar YUV or gray */                                         // 0.0
/*238 */             c->swScale = planarCopyWrapper;                                   // 0.0
/*240 */     }                                                                         // 0.0
/*244 */     if (ARCH_BFIN)                                                            // 0.0
/*246 */         ff_bfin_get_unscaled_swscale(c);                                      // 0.0
/*248 */     if (HAVE_ALTIVEC)                                                         // 0.0
/*250 */         ff_swscale_get_unscaled_altivec(c);                                   // 0.0
/*252 */ }                                                                             // 0.0
