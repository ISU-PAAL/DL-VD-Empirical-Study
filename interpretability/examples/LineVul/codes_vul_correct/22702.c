// commit message FFmpeg@90fc00a623 (target=1, prob=0.89057016, correct=True): avformat/subtitles: add a next line jumper and use it.
/*0  */ static int srt_probe(AVProbeData *p)                                                          // (8) 0.04902
/*2  */ {                                                                                             // (15) 0.003268
/*4  */     const unsigned char *ptr = p->buf;                                                        // (10) 0.04248
/*6  */     int i, v, num = 0;                                                                        // (11) 0.03922
/*10 */     if (AV_RB24(ptr) == 0xEFBBBF)                                                             // (4) 0.06209
/*12 */         ptr += 3;  /* skip UTF-8 BOM */                                                       // (3) 0.06536
/*16 */     while (*ptr == '\r' || *ptr == '\n')                                                      // (5) 0.06209
/*18 */         ptr++;                                                                                // (12) 0.02941
/*20 */     for (i=0; i<2; i++) {                                                                     // (7) 0.05229
/*22 */         if ((num == i || num + 1 == i)                                                        // (6) 0.06209
/*24 */             && sscanf(ptr, "%*d:%*2d:%*2d%*1[,.]%*3d --> %*d:%*2d:%*2d%*1[,.]%3d", &v) == 1)  // (0) 0.232
/*26 */             return AVPROBE_SCORE_MAX;                                                         // (1) 0.0719
/*28 */         num = atoi(ptr);                                                                      // (9) 0.04575
/*30 */         ptr += strcspn(ptr, "\n") + 1;                                                        // (2) 0.0719
/*32 */     }                                                                                         // (14) 0.01307
/*34 */     return 0;                                                                                 // (13) 0.01961
/*36 */ }                                                                                             // (16) 0.003268
