// commit message FFmpeg@b2a8850969 (target=0, prob=0.6769447, correct=False): ffplay: only check external clock if current frame serial matches the displayed frame serial
/*0  */ static void update_video_pts(VideoState *is, double pts, int64_t pos, int serial) {  // (0) 0.1742
/*2  */     double time = av_gettime() / 1000000.0;                                          // (3) 0.1097
/*4  */     /* update current video pts */                                                   // (7) 0.05806
/*6  */     is->video_current_pts = pts;                                                     // (4) 0.09032
/*8  */     is->video_current_pts_drift = is->video_current_pts - time;                      // (1) 0.1677
/*10 */     is->video_current_pos = pos;                                                     // (6) 0.08387
/*12 */     is->frame_last_pts = pts;                                                        // (5) 0.09032
/*14 */     check_external_clock_sync(is, is->video_current_pts);                            // (2) 0.1419
/*16 */ }                                                                                    // (8) 0.006452
