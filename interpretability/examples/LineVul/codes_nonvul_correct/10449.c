// commit message FFmpeg@87e8788680 (target=0, prob=0.008263067, correct=True): allocate 32 extra bytes at the end of the probe buffer and remove most probe buf_size checks
/*0  */ static int film_probe(AVProbeData *p)     // (2) 0.1414
/*2  */ {                                         // (6) 0.0101
/*4  */     if (p->buf_size < 4)                  // (3) 0.1313
/*6  */         return 0;                         // (4) 0.101
/*10 */     if (AV_RB32(&p->buf[0]) != FILM_TAG)  // (0) 0.2222
/*12 */         return 0;                         // (5) 0.101
/*16 */     return AVPROBE_SCORE_MAX;             // (1) 0.1414
/*18 */ }                                         // (7) 0.0101
