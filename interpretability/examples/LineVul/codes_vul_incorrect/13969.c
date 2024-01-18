// commit message FFmpeg@ec4c483976 (target=1, prob=0.03153649, correct=False): lavf: add a protocol whitelist/blacklist for file opened internally
/*0  */ static void *ff_avio_child_next(void *obj, void *prev)  // (0) 0.2899
/*2  */ {                                                       // (4) 0.01449
/*4  */     AVIOContext *s = obj;                               // (3) 0.1594
/*6  */     AVIOInternal *internal = s->opaque;                 // (1) 0.2029
/*8  */     return prev ? NULL : internal->h;                   // (2) 0.1739
/*10 */ }                                                       // (5) 0.01449
