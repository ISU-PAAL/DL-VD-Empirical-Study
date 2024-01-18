// commit message FFmpeg@be4dfbf7b7 (target=0, prob=0.015006879, correct=True): avformat/avio: check input URLContext value NULL
/*0  */ int ffurl_shutdown(URLContext *h, int flags)  // (2) 0.2027
/*2  */ {                                             // (4) 0.01351
/*4  */     if (!h->prot->url_shutdown)               // (3) 0.1892
/*6  */         return AVERROR(EINVAL);               // (1) 0.2162
/*8  */     return h->prot->url_shutdown(h, flags);   // (0) 0.2297
/*10 */ }                                             // (5) 0.01351
