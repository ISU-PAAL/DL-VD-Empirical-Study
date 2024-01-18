// commit message FFmpeg@d59bfcd112 (target=1, prob=0.33870336, correct=False): avformat/mov: fix integer overflow
/*0  */ static void mov_update_dts_shift(MOVStreamContext *sc, int duration)  // (1) 0.3088
/*2  */ {                                                                     // (3) 0.01471
/*4  */     if (duration < 0) {                                               // (2) 0.1471
/*10 */         sc->dts_shift = FFMAX(sc->dts_shift, -duration);              // (0) 0.3971
