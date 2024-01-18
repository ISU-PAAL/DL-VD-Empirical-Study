// commit message FFmpeg@a6d6b8a200 (target=1, prob=0.09929994, correct=False): lavu/opt: fix crash in av_opt_next() in case the class has no options
/*0  */ const AVOption *av_opt_next(void *obj, const AVOption *last)   // (1) 0.1961
/*2  */ {                                                              // (5) 0.009804
/*4  */     AVClass *class = *(AVClass**)obj;                          // (3) 0.1569
/*6  */     if (!last && class->option[0].name) return class->option;  // (2) 0.1961
/*8  */     if (last && last[1].name)           return ++last;         // (0) 0.2647
/*10 */     return NULL;                                               // (4) 0.05882
/*12 */ }                                                              // (6) 0.009804
