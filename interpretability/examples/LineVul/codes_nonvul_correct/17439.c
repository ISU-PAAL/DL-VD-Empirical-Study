// commit message FFmpeg@bc29acdc76 (target=0, prob=0.07769582, correct=True): ftp: explicit return code checks
/*0  */ static int ftp_connect_control_connection(URLContext *h)                               // (11) 0.03125
/*2  */ {                                                                                      // (23) 0.001953
/*4  */     char buf[CONTROL_BUFFER_SIZE], opts_format[20];                                    // (9) 0.04297
/*6  */     int err;                                                                           // (22) 0.01172
/*8  */     AVDictionary *opts = NULL;                                                         // (20) 0.02344
/*10 */     FTPContext *s = h->priv_data;                                                      // (15) 0.02734
/*12 */     const int connect_codes[] = {220, 0};                                              // (13) 0.0293
/*16 */     s->conn_control_block_flag = 0;                                                    // (14) 0.0293
/*20 */     if (!s->conn_control) {                                                            // (19) 0.02344
/*22 */         ff_url_join(buf, sizeof(buf), "tcp", NULL,                                     // (7) 0.04883
/*24 */                     s->hostname, s->server_control_port, NULL);                        // (2) 0.06641
/*26 */         if (s->rw_timeout != -1) {                                                     // (10) 0.03711
/*28 */             snprintf(opts_format, sizeof(opts_format), "%d", s->rw_timeout);           // (1) 0.06836
/*30 */             av_dict_set(&opts, "timeout", opts_format, 0);                             // (5) 0.05859
/*32 */         } /* if option is not given, don't pass it and let tcp use its own default */  // (6) 0.05273
/*34 */         err = ffurl_open(&s->conn_control, buf, AVIO_FLAG_READ_WRITE,                  // (4) 0.0625
/*36 */                          &s->conn_control_interrupt_cb, &opts);                        // (0) 0.07812
/*38 */         av_dict_free(&opts);                                                           // (12) 0.03125
/*40 */         if (err < 0) {                                                                 // (18) 0.02734
/*42 */             av_log(h, AV_LOG_ERROR, "Cannot open control connection\n");               // (3) 0.0625
/*44 */             return err;                                                                // (17) 0.02734
/*46 */         }                                                                              // (21) 0.01562
/*50 */         /* consume all messages from server */                                         // (16) 0.02734
/*52 */         if (!ftp_status(s, NULL, connect_codes)) {                                     // (8) 0.04492
/*54 */             av_log(h, AV_LOG_ERROR, "FTP server not ready for new users\n");           // 0.0
/*56 */             err = AVERROR(EACCES);                                                     // 0.0
/*58 */             return err;                                                                // 0.0
/*60 */         }                                                                              // 0.0
/*64 */         if ((err = ftp_auth(s)) < 0) {                                                 // 0.0
/*66 */             av_log(h, AV_LOG_ERROR, "FTP authentication failed\n");                    // 0.0
/*68 */             return err;                                                                // 0.0
/*70 */         }                                                                              // 0.0
/*74 */         if ((err = ftp_type(s)) < 0) {                                                 // 0.0
/*76 */             av_dlog(h, "Set content type failed\n");                                   // 0.0
/*78 */             return err;                                                                // 0.0
/*80 */         }                                                                              // 0.0
/*82 */     }                                                                                  // 0.0
/*84 */     return 0;                                                                          // 0.0
/*86 */ }                                                                                      // 0.0
