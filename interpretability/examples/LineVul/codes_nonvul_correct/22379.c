// commit message FFmpeg@87e8788680 (target=0, prob=0.010686006, correct=True): allocate 32 extra bytes at the end of the probe buffer and remove most probe buf_size checks
/*0  */ static int voc_probe(AVProbeData *p)                       // (5) 0.0765
/*2  */ {                                                          // (12) 0.005464
/*4  */     int version, check;                                    // (10) 0.04372
/*8  */     if (p->buf_size < 26)                                  // (6) 0.07104
/*10 */         return 0;                                          // (9) 0.05464
/*12 */     if (memcmp(p->buf, voc_magic, sizeof(voc_magic) - 1))  // (0) 0.1366
/*14 */         return 0;                                          // (8) 0.05464
/*16 */     version = p->buf[22] | (p->buf[23] << 8);              // (2) 0.1202
/*18 */     check = p->buf[24] | (p->buf[25] << 8);                // (1) 0.1202
/*20 */     if (~version + 0x1234 != check)                        // (4) 0.0765
/*22 */         return 10;                                         // (7) 0.05464
/*26 */     return AVPROBE_SCORE_MAX;                              // (3) 0.0765
/*28 */ }                                                          // (11) 0.005464
