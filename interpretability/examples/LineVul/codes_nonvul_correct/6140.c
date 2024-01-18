// commit message FFmpeg@dcc39ee10e (target=0, prob=0.10882202, correct=True): lavc: Remove deprecated XvMC support hacks
/*0  */ void ff_mpv_frame_end(MpegEncContext *s)                                     // (3) 0.07556
/*2  */ {                                                                            // (14) 0.004444
/*4  */ #if FF_API_XVMC                                                              // (10) 0.04
/*6  */ FF_DISABLE_DEPRECATION_WARNINGS                                              // (7) 0.04889
/*8  */     /* redraw edges for the frame if decoding didn't complete */             // (4) 0.07111
/*10 */     // just to make sure that all data is rendered.                          // (5) 0.06222
/*12 */     if (CONFIG_MPEG_XVMC_DECODER && s->avctx->xvmc_acceleration) {           // (0) 0.1467
/*14 */         ff_xvmc_field_end(s);                                                // (2) 0.08444
/*16 */     } else                                                                   // (12) 0.02222
/*18 */ FF_ENABLE_DEPRECATION_WARNINGS                                               // (8) 0.04889
/*20 */ #endif /* FF_API_XVMC */                                                     // (9) 0.04889
/*24 */     emms_c();                                                                // (11) 0.03556
/*28 */     if (s->current_picture.reference)                                        // (6) 0.05778
/*30 */         ff_thread_report_progress(&s->current_picture_ptr->tf, INT_MAX, 0);  // (1) 0.1378
/*32 */ }                                                                            // (13) 0.004444
