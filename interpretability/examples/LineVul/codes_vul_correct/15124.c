// commit message FFmpeg@252c0bfdc0 (target=1, prob=0.7295864, correct=True): lavc: Fix msvc compilation of utils.c with -WX (warnings treated as errors)
/*0 */ int avcodec_default_reget_buffer(AVCodecContext *s, AVFrame *pic)  // (0) 0.5581
/*2 */ {                                                                  // (2) 0.02326
/*4 */     av_assert0(0);                                                 // (1) 0.2326
/*7 */ }                                                                  // (3) 0.02326
