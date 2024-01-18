// commit message FFmpeg@f354f30836 (target=0, prob=0.55682033, correct=False): error resilience: check error_concealment, not err_recognition.
/*0  */ void ff_er_frame_start(ERContext *s)                                   // (4) 0.09524
/*2  */ {                                                                      // (7) 0.006803
/*4  */     if (!s->avctx->err_recognition)                                    // (3) 0.102
/*6  */         return;                                                        // (6) 0.06122
/*10 */     memset(s->error_status_table, ER_MB_ERROR | VP_START | ER_MB_END,  // (0) 0.2109
/*12 */            s->mb_stride * s->mb_height * sizeof(uint8_t));             // (1) 0.2041
/*14 */     s->error_count    = 3 * s->mb_num;                                 // (2) 0.1361
/*16 */     s->error_occurred = 0;                                             // (5) 0.08163
/*18 */ }                                                                      // (8) 0.006803
