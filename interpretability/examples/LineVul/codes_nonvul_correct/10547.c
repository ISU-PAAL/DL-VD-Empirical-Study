// commit message FFmpeg@ff486c0f7f (target=0, prob=0.48125926, correct=True): hevc: Do not right shift a negative value in get_pcm
/*0  */ static int get_pcm(HEVCContext *s, int x, int y)           // (6) 0.08837
/*2  */ {                                                          // (8) 0.004651
/*4  */     int log2_min_pu_size = s->sps->log2_min_pu_size;       // (3) 0.1256
/*6  */     int x_pu             = x >> log2_min_pu_size;          // (0) 0.1442
/*8  */     int y_pu             = y >> log2_min_pu_size;          // (1) 0.1442
/*12 */     if (x < 0 || x_pu >= s->sps->min_pu_width ||           // (5) 0.1116
/*14 */         y < 0 || y_pu >= s->sps->min_pu_height)            // (4) 0.1209
/*16 */         return 2;                                          // (7) 0.04651
/*18 */     return s->is_pcm[y_pu * s->sps->min_pu_width + x_pu];  // (2) 0.1395
/*20 */ }                                                          // (9) 0.004651
