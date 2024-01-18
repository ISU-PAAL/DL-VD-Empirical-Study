// commit message FFmpeg@89d4d7d759 (target=1, prob=0.99914575, correct=True): doc/examples/http_multiclient: Fix resource leak
/*0   */ static void process_client(AVIOContext *client, const char *in_uri)                              // (8) 0.03667
/*2   */ {                                                                                                // (28) 0.001936
/*4   */     AVIOContext *input = NULL;                                                                   // (17) 0.02109
/*6   */     uint8_t buf[1024];                                                                           // (18) 0.02106
/*8   */     int ret, n, reply_code;                                                                      // (15) 0.02296
/*10  */     uint8_t *resource = NULL;                                                                    // (16) 0.02295
/*12  */     while ((ret = avio_handshake(client)) > 0) {                                                 // (9) 0.03636
/*14  */         av_opt_get(client, "resource", AV_OPT_SEARCH_CHILDREN, &resource);                       // (2) 0.06628
/*16  */         // check for strlen(resource) is necessary, because av_opt_get()                         // (3) 0.0609
/*18  */         // may return empty string.                                                              // (12) 0.02756
/*20  */         if (resource && strlen(resource))                                                        // (11) 0.03078
/*22  */             break;                                                                               // (13) 0.02488
/*25  */     }                                                                                            // (25) 0.007663
/*27  */     if (ret < 0)                                                                                 // (22) 0.0172
/*29  */         goto end;                                                                                // (20) 0.0196
/*31  */     av_log(client, AV_LOG_TRACE, "resource=%p\n", resource);                                     // (6) 0.04969
/*33  */     if (resource && resource[0] == '/' && !strcmp((resource + 1), in_uri)) {                     // (5) 0.05354
/*35  */         reply_code = 200;                                                                        // (14) 0.02484
/*37  */     } else {                                                                                     // (24) 0.01146
/*39  */         reply_code = AVERROR_HTTP_NOT_FOUND;                                                     // (7) 0.04202
/*41  */     }                                                                                            // (27) 0.007649
/*43  */     if ((ret = av_opt_set_int(client, "reply_code", reply_code, AV_OPT_SEARCH_CHILDREN)) < 0) {  // (0) 0.08216
/*45  */         av_log(client, AV_LOG_ERROR, "Failed to set reply_code: %s.\n", av_err2str(ret));        // (1) 0.08029
/*47  */         goto end;                                                                                // (21) 0.01934
/*49  */     }                                                                                            // (26) 0.007649
/*51  */     av_log(client, AV_LOG_TRACE, "Set reply code to %d\n", reply_code);                          // (4) 0.05734
/*55  */     while ((ret = avio_handshake(client)) > 0);                                                  // (10) 0.03442
/*59  */     if (ret < 0)                                                                                 // (23) 0.01719
/*61  */         goto end;                                                                                // (19) 0.01962
/*65  */     fprintf(stderr, "Handshake performed.\n");                                                   // 0.0
/*67  */     if (reply_code != 200)                                                                       // 0.0
/*69  */         goto end;                                                                                // 0.0
/*71  */     fprintf(stderr, "Opening input file.\n");                                                    // 0.0
/*73  */     if ((ret = avio_open2(&input, in_uri, AVIO_FLAG_READ, NULL, NULL)) < 0) {                    // 0.0
/*75  */         av_log(input, AV_LOG_ERROR, "Failed to open input: %s: %s.\n", in_uri,                   // 0.0
/*77  */                av_err2str(ret));                                                                 // 0.0
/*79  */         goto end;                                                                                // 0.0
/*81  */     }                                                                                            // 0.0
/*83  */     for(;;) {                                                                                    // 0.0
/*85  */         n = avio_read(input, buf, sizeof(buf));                                                  // 0.0
/*87  */         if (n < 0) {                                                                             // 0.0
/*89  */             if (n == AVERROR_EOF)                                                                // 0.0
/*91  */                 break;                                                                           // 0.0
/*93  */             av_log(input, AV_LOG_ERROR, "Error reading from input: %s.\n",                       // 0.0
/*95  */                    av_err2str(n));                                                               // 0.0
/*97  */             break;                                                                               // 0.0
/*99  */         }                                                                                        // 0.0
/*101 */         avio_write(client, buf, n);                                                              // 0.0
/*103 */         avio_flush(client);                                                                      // 0.0
/*105 */     }                                                                                            // 0.0
/*107 */ end:                                                                                             // 0.0
/*109 */     fprintf(stderr, "Flushing client\n");                                                        // 0.0
/*111 */     avio_flush(client);                                                                          // 0.0
/*113 */     fprintf(stderr, "Closing client\n");                                                         // 0.0
/*115 */     avio_close(client);                                                                          // 0.0
/*117 */     fprintf(stderr, "Closing input\n");                                                          // 0.0
/*119 */     avio_close(input);                                                                           // 0.0
/*122 */ }                                                                                                // 0.0
