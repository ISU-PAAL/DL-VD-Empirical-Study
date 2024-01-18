// commit message FFmpeg@87e8788680 (target=0, prob=0.011921565, correct=True): allocate 32 extra bytes at the end of the probe buffer and remove most probe buf_size checks
/*0  */ static int fourxm_probe(AVProbeData *p)       // (2) 0.1231
/*2  */ {                                             // (7) 0.007692
/*4  */     if (p->buf_size < 12)                     // (4) 0.1
/*6  */         return 0;                             // (5) 0.07692
/*10 */     if ((AV_RL32(&p->buf[0]) != RIFF_TAG) ||  // (1) 0.1769
/*12 */         (AV_RL32(&p->buf[8]) != _4XMV_TAG))   // (0) 0.2077
/*14 */         return 0;                             // (6) 0.07692
/*18 */     return AVPROBE_SCORE_MAX;                 // (3) 0.1077
/*20 */ }                                             // (8) 0.007692
