// commit message FFmpeg@e1fb3143bb (target=1, prob=0.0415932, correct=False): avformat/ftp: fix possible deadlock
/*0  */ static int ftp_abort(URLContext *h)                                                 // (20) 0.02539
/*2  */ {                                                                                   // (30) 0.001953
/*4  */     static const char *command = "ABOR\r\n";                                        // (13) 0.0332
/*6  */     int err;                                                                        // (24) 0.01172
/*8  */     static const int abor_codes[] = {225, 226, 0};                                  // (8) 0.03711
/*10 */     FTPContext *s = h->priv_data;                                                   // (16) 0.02734
/*14 */     /* According to RCF 959:                                                        // (21) 0.02148
/*16 */        "ABOR command tells the server to abort the previous FTP                     // (11) 0.03516
/*18 */        service command and any associated transfer of data."                        // (14) 0.0293
/*22 */        There are FTP server implementations that don't response                     // (15) 0.0293
/*24 */        to any commands during data transfer in passive mode (including ABOR).       // (7) 0.03906
/*28 */        This implementation closes data connection by force.                         // (17) 0.02734
/*30 */     */                                                                              // (27) 0.007812
/*34 */     if (ftp_send_command(s, command, NULL, NULL) < 0) {                             // (4) 0.04688
/*36 */         ftp_close_both_connections(s);                                              // (9) 0.03711
/*38 */         if ((err = ftp_connect_control_connection(h)) < 0) {                        // (2) 0.05078
/*40 */             av_log(h, AV_LOG_ERROR, "Reconnect failed.\n");                         // (0) 0.0625
/*42 */             return err;                                                             // (18) 0.02734
/*44 */         }                                                                           // (22) 0.01562
/*46 */     } else {                                                                        // (25) 0.01172
/*48 */         ftp_close_data_connection(s);                                               // (12) 0.03516
/*50 */     }                                                                               // (28) 0.007812
/*54 */     if (ftp_status(s, NULL, abor_codes) < 225) {                                    // (5) 0.04492
/*56 */         /* wu-ftpd also closes control connection after data connection closing */  // (6) 0.04297
/*58 */         ffurl_closep(&s->conn_control);                                             // (10) 0.03711
/*60 */         if ((err = ftp_connect_control_connection(h)) < 0) {                        // (3) 0.05078
/*62 */             av_log(h, AV_LOG_ERROR, "Reconnect failed.\n");                         // (1) 0.0625
/*64 */             return err;                                                             // (19) 0.02734
/*66 */         }                                                                           // (23) 0.01562
/*68 */     }                                                                               // (29) 0.007812
/*72 */     return 0;                                                                       // (26) 0.01172
/*74 */ }                                                                                   // 0.0
