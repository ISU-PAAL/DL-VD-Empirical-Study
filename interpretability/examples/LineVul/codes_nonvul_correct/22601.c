// commit message FFmpeg@87e8788680 (target=0, prob=0.0069488245, correct=True): allocate 32 extra bytes at the end of the probe buffer and remove most probe buf_size checks
/*0  */ static int au_probe(AVProbeData *p)              // (3) 0.09459
/*2  */ {                                                // (9) 0.006757
/*4  */     /* check file header */                      // (7) 0.05405
/*6  */     if (p->buf_size <= 24)                       // (4) 0.08784
/*8  */         return 0;                                // (5) 0.06757
/*10 */     if (p->buf[0] == '.' && p->buf[1] == 's' &&  // (1) 0.1757
/*12 */         p->buf[2] == 'n' && p->buf[3] == 'd')    // (0) 0.1892
/*14 */         return AVPROBE_SCORE_MAX;                // (2) 0.1216
/*16 */     else                                         // (8) 0.02703
/*18 */         return 0;                                // (6) 0.06757
/*20 */ }                                                // (10) 0.006757
