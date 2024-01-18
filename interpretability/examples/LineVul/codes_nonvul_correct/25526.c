// commit message FFmpeg@f929ab0569 (target=0, prob=0.014603314, correct=True): cosmetics: Write NULL pointer equality checks more compactly
/*0  */ AVFrame *avcodec_alloc_frame(void)                 // (2) 0.1111
/*2  */ {                                                  // (9) 0.008544
/*4  */     AVFrame *frame = av_mallocz(sizeof(AVFrame));  // (0) 0.1709
/*8  */     if (frame == NULL)                             // (6) 0.07689
/*10 */         return NULL;                               // (5) 0.08543
/*14 */ FF_DISABLE_DEPRECATION_WARNINGS                    // (3) 0.09413
/*16 */     avcodec_get_frame_defaults(frame);             // (1) 0.1367
/*18 */ FF_ENABLE_DEPRECATION_WARNINGS                     // (4) 0.09403
/*22 */     return frame;                                  // (7) 0.05126
/*24 */ }                                                  // (8) 0.008544
