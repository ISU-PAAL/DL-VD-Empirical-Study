// commit message FFmpeg@87e8788680 (target=0, prob=0.007112628, correct=True): allocate 32 extra bytes at the end of the probe buffer and remove most probe buf_size checks
/*0  */ static int flv_probe(AVProbeData *p)                                         // (2) 0.09934
/*2  */ {                                                                            // (9) 0.006623
/*4  */     const uint8_t *d;                                                        // (4) 0.07285
/*8  */     if (p->buf_size < 6)                                                     // (3) 0.08609
/*10 */         return 0;                                                            // (5) 0.06623
/*12 */     d = p->buf;                                                              // (6) 0.0596
/*14 */     if (d[0] == 'F' && d[1] == 'L' && d[2] == 'V' && d[3] < 5 && d[5]==0) {  // (0) 0.3113
/*16 */         return AVPROBE_SCORE_MAX;                                            // (1) 0.1192
/*18 */     }                                                                        // (8) 0.02649
/*20 */     return 0;                                                                // (7) 0.03974
/*22 */ }                                                                            // (10) 0.006623
