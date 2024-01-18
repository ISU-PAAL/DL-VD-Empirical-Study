// commit message FFmpeg@1dba8371d9 (target=0, prob=0.10630455, correct=True): avformat: add protocol_whitelist
/*0  */ int ffurl_connect(URLContext *uc, AVDictionary **options)                  // (9) 0.04116
/*2  */ {                                                                          // (16) 0.002421
/*4  */     int err =                                                              // (14) 0.01453
/*6  */         uc->prot->url_open2 ? uc->prot->url_open2(uc,                      // (5) 0.07022
/*8  */                                                   uc->filename,            // (0) 0.1308
/*10 */                                                   uc->flags,               // (1) 0.1308
/*12 */                                                   options) :               // (2) 0.1259
/*14 */         uc->prot->url_open(uc, uc->filename, uc->flags);                   // (6) 0.0678
/*16 */     if (err)                                                               // (13) 0.01695
/*18 */         return err;                                                        // (11) 0.02421
/*20 */     uc->is_connected = 1;                                                  // (10) 0.02906
/*22 */     /* We must be careful here as ffurl_seek() could be slow,              // (8) 0.046
/*24 */      * for example for http */                                             // (12) 0.02421
/*26 */     if ((uc->flags & AVIO_FLAG_WRITE) || !strcmp(uc->prot->name, "file"))  // (4) 0.07506
/*28 */         if (!uc->is_streamed && ffurl_seek(uc, 0, SEEK_SET) < 0)           // (3) 0.0799
/*30 */             uc->is_streamed = 1;                                           // (7) 0.05085
/*32 */     return 0;                                                              // (15) 0.01453
/*34 */ }                                                                          // (17) 0.002421
