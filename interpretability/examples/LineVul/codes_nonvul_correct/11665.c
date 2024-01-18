// commit message FFmpeg@30e256430e (target=0, prob=0.25792706, correct=True): lavc/pthread: remove obsolete checks
/*0  */ int ff_thread_init(AVCodecContext *avctx)                                                    // (6) 0.0566
/*2  */ {                                                                                            // (16) 0.003774
/*4  */     if (avctx->thread_opaque) {                                                              // (7) 0.05283
/*6  */         av_log(avctx, AV_LOG_ERROR, "avcodec_thread_init is ignored after avcodec_open\n");  // (0) 0.1472
/*8  */         return -1;                                                                           // (9) 0.04151
/*10 */     }                                                                                        // (13) 0.01509
/*14 */ #if HAVE_W32THREADS                                                                          // (10) 0.03396
/*16 */     w32thread_init();                                                                        // (11) 0.03396
/*18 */ #endif                                                                                       // (15) 0.007547
/*22 */     if (avctx->codec) {                                                                      // (8) 0.04528
/*24 */         validate_thread_parameters(avctx);                                                   // (5) 0.06415
/*28 */         if (avctx->active_thread_type&FF_THREAD_SLICE)                                       // (2) 0.09811
/*30 */             return thread_init(avctx);                                                       // (4) 0.0717
/*32 */         else if (avctx->active_thread_type&FF_THREAD_FRAME)                                  // (1) 0.1019
/*34 */             return frame_thread_init(avctx);                                                 // (3) 0.07925
/*36 */     }                                                                                        // (14) 0.01509
/*40 */     return 0;                                                                                // (12) 0.02264
/*42 */ }                                                                                            // (17) 0.003774
