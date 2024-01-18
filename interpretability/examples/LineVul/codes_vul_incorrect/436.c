// commit message FFmpeg@c8d0d8bc76 (target=1, prob=0.43674007, correct=False): crypto: Use av_freep instead of av_free
/*0  */ static int crypto_open(URLContext *h, const char *uri, int flags)             // (9) 0.03711
/*2  */ {                                                                             // (29) 0.001953
/*4  */     const char *nested_url;                                                   // (16) 0.02148
/*6  */     int ret;                                                                  // (23) 0.01172
/*8  */     CryptoContext *c = h->priv_data;                                          // (15) 0.02734
/*12 */     if (!av_strstart(uri, "crypto+", &nested_url) &&                          // (6) 0.04687
/*14 */         !av_strstart(uri, "crypto:", &nested_url)) {                          // (5) 0.05273
/*16 */         av_log(h, AV_LOG_ERROR, "Unsupported url %s\n", uri);                 // (1) 0.06055
/*18 */         ret = AVERROR(EINVAL);                                                // (10) 0.0332
/*20 */         goto err;                                                             // (19) 0.01953
/*22 */     }                                                                         // (24) 0.007812
/*26 */     if (c->keylen < BLOCKSIZE || c->ivlen < BLOCKSIZE) {                      // (7) 0.04687
/*28 */         av_log(h, AV_LOG_ERROR, "Key or IV not set\n");                       // (4) 0.05469
/*30 */         ret = AVERROR(EINVAL);                                                // (13) 0.0332
/*32 */         goto err;                                                             // (20) 0.01953
/*34 */     }                                                                         // (27) 0.007812
/*36 */     if (flags & AVIO_FLAG_WRITE) {                                            // (14) 0.03125
/*38 */         av_log(h, AV_LOG_ERROR, "Only decryption is supported currently\n");  // (2) 0.05664
/*40 */         ret = AVERROR(ENOSYS);                                                // (11) 0.0332
/*42 */         goto err;                                                             // (22) 0.01953
/*44 */     }                                                                         // (28) 0.007812
/*46 */     if ((ret = ffurl_open(&c->hd, nested_url, AVIO_FLAG_READ)) < 0) {         // (0) 0.06055
/*48 */         av_log(h, AV_LOG_ERROR, "Unable to open input\n");                    // (3) 0.05469
/*50 */         goto err;                                                             // (21) 0.01953
/*52 */     }                                                                         // (25) 0.007812
/*54 */     c->aes = av_mallocz(av_aes_size);                                         // (8) 0.04102
/*56 */     if (!c->aes) {                                                            // (17) 0.02148
/*58 */         ret = AVERROR(ENOMEM);                                                // (12) 0.0332
/*60 */         goto err;                                                             // (18) 0.01953
/*62 */     }                                                                         // (26) 0.007812
/*66 */     av_aes_init(c->aes, c->key, 128, 1);                                      // 0.0
/*70 */     h->is_streamed = 1;                                                       // 0.0
/*74 */     return 0;                                                                 // 0.0
/*76 */ err:                                                                          // 0.0
/*78 */     av_free(c->key);                                                          // 0.0
/*80 */     av_free(c->iv);                                                           // 0.0
/*82 */     return ret;                                                               // 0.0
/*84 */ }                                                                             // 0.0
