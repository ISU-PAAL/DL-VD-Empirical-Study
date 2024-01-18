// commit message FFmpeg@bd8ae4885b (target=0, prob=0.4376037, correct=True): Oops, my last commit broke compilation...
/*0  */ AVFilterFormats *avfilter_all_colorspaces(void)                         // (11) 0.03125
/*2  */ {                                                                       // (13) 0.001953
/*4  */     return avfilter_make_format_list(35,                                // (12) 0.0293
/*6  */                 PIX_FMT_YUV444P,  PIX_FMT_YUV422P,  PIX_FMT_YUV420P,    // (2) 0.09766
/*8  */                 PIX_FMT_YUV411P,  PIX_FMT_YUV410P,                      // (5) 0.07422
/*10 */                 PIX_FMT_YUYV422,  PIX_FMT_UYVY422,  PIX_FMT_UYYVYY411,  // (0) 0.1035
/*12 */                 PIX_FMT_YUVJ444P, PIX_FMT_YUVJ422P, PIX_FMT_YUVJ420P,   // (1) 0.09961
/*14 */                 PIX_FMT_YUV440P,  PIX_FMT_YUVJ440P,                     // (3) 0.07617
/*16 */                 PIX_FMT_RGB32,    PIX_FMT_BGR32,                        // (7) 0.07227
/*18 */                 PIX_FMT_RGB32_1,  PIX_FMT_BGR32_1,                      // (4) 0.07617
/*20 */                 PIX_FMT_RGB24,    PIX_FMT_BGR24,                        // (8) 0.07227
/*22 */                 PIX_FMT_RGB565,   PIX_FMT_BGR565,                       // (9) 0.07031
/*24 */                 PIX_FMT_RGB555,   PIX_FMT_BGR555,                       // (10) 0.07031
/*26 */                 PIX_FMT_RGB8,     PIX_FMT_BGR8,                         // (6) 0.07422
/*28 */                 PIX_FMT_RGB4_BYTE,PIX_FMT_BGR4_BYTE,                    // 0.0
/*30 */                 PIX_FMT_GRAY16BE, PIX_FMT_GRAY16LE,                     // 0.0
/*32 */                 PIX_FMT_GRAY8,    PIX_FMT_PAL8,                         // 0.0
/*34 */                 PIX_FMT_MONOWHITE,PIX_FMT_MONOBLACK                     // 0.0
/*36 */                 PIX_FMT_NV12,     PIX_FMT_NV21);                        // 0.0
/*38 */ }                                                                       // 0.0
