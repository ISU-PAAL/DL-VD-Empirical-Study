// commit message FFmpeg@bc7eb330e3 (target=0, prob=0.026333572, correct=True): Remove "frame size must be a multiple of 2" check. This check only caught explicitly set sizes from the cmd line and overriding the users wish seems silly, especially as it seems to work.
/*0  */ static void opt_frame_size(const char *arg)                                 // (4) 0.07784
/*2  */ {                                                                           // (9) 0.005988
/*4  */     if (av_parse_video_frame_size(&frame_width, &frame_height, arg) < 0) {  // (0) 0.1796
/*6  */         fprintf(stderr, "Incorrect frame size\n");                          // (3) 0.1317
/*8  */         av_exit(1);                                                         // (5) 0.07784
/*10 */     }                                                                       // (7) 0.02395
/*12 */     if ((frame_width % 2) != 0 || (frame_height % 2) != 0) {                // (2) 0.1497
/*14 */         fprintf(stderr, "Frame size must be a multiple of 2\n");            // (1) 0.1557
/*16 */         av_exit(1);                                                         // (6) 0.07784
/*18 */     }                                                                       // (8) 0.02395
/*20 */ }                                                                           // (10) 0.005988
