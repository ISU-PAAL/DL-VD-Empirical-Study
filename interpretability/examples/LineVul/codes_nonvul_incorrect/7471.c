// commit message FFmpeg@1f28a991ef (target=0, prob=0.7171713, correct=False): libavcodec/h264_sei: Don't log random user data. This prevents terminal junk.
/*0  */ static int decode_unregistered_user_data(H264SEIUnregistered *h, GetBitContext *gb,  // (3) 0.05991
/*2  */                                          void *logctx, int size)                     // (0) 0.1106
/*4  */ {                                                                                    // (21) 0.002304
/*6  */     uint8_t *user_data;                                                              // (15) 0.02765
/*8  */     int e, build, i;                                                                 // (18) 0.02304
/*12 */     if (size < 16 || size >= INT_MAX - 16)                                           // (7) 0.03917
/*14 */         return AVERROR_INVALIDDATA;                                                  // (8) 0.03917
/*18 */     user_data = av_malloc(16 + size + 1);                                            // (6) 0.04147
/*20 */     if (!user_data)                                                                  // (19) 0.02074
/*22 */         return AVERROR(ENOMEM);                                                      // (11) 0.03687
/*26 */     for (i = 0; i < size + 16; i++)                                                  // (9) 0.03917
/*28 */         user_data[i] = get_bits(gb, 8);                                              // (5) 0.05069
/*32 */     user_data[i] = 0;                                                                // (16) 0.02765
/*34 */     e = sscanf(user_data + 16, "x264 - core %d", &build);                            // (4) 0.05991
/*36 */     if (e == 1 && build > 0)                                                         // (14) 0.02995
/*38 */         h->x264_build = build;                                                       // (12) 0.03687
/*40 */     if (e == 1 && build == 1 && !strncmp(user_data+16, "x264 - core 0000", 16))      // (2) 0.07604
/*42 */         h->x264_build = 67;                                                          // (13) 0.03687
/*46 */     if (strlen(user_data + 16) > 0)                                                  // (10) 0.03917
/*48 */         av_log(logctx, AV_LOG_DEBUG, "user data:\"%s\"\n", user_data + 16);          // (1) 0.08525
/*52 */     av_free(user_data);                                                              // (17) 0.02535
/*54 */     return 0;                                                                        // (20) 0.01382
/*56 */ }                                                                                    // (22) 0.002304
