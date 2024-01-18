// commit message FFmpeg@f3ace37a3b (target=1, prob=0.067715466, correct=False): lavf/ftp: fix possible crash
/*0  */ static int ftp_status(FTPContext *s, char **line, const int response_codes[])  // (5) 0.04688
/*2  */ {                                                                              // (25) 0.001953
/*4  */     int err, i, dash = 0, result = 0, code_found = 0;                          // (7) 0.04297
/*6  */     char buf[CONTROL_BUFFER_SIZE];                                             // (16) 0.0293
/*8  */     AVBPrint line_buffer;                                                      // (21) 0.01953
/*12 */     if (line)                                                                  // (24) 0.01367
/*14 */         av_bprint_init(&line_buffer, 0, AV_BPRINT_SIZE_AUTOMATIC);             // (0) 0.06445
/*18 */     while (!code_found || dash) {                                              // (19) 0.02344
/*20 */         if ((err = ftp_get_line(s, buf, sizeof(buf))) < 0) {                   // (1) 0.05859
/*22 */             av_bprint_finalize(&line_buffer, NULL);                            // (4) 0.04883
/*24 */             return err;                                                        // (17) 0.02734
/*26 */         }                                                                      // (22) 0.01563
/*30 */         av_log(s, AV_LOG_DEBUG, "%s\n", buf);                                  // (3) 0.05078
/*34 */         if (strlen(buf) < 4)                                                   // (13) 0.0332
/*36 */             continue;                                                          // (18) 0.02539
/*40 */         err = 0;                                                               // (20) 0.02148
/*42 */         for (i = 0; i < 3; ++i) {                                              // (9) 0.04102
/*44 */             if (buf[i] < '0' || buf[i] > '9')                                  // (2) 0.05859
/*46 */                 continue;                                                      // (14) 0.0332
/*48 */             err *= 10;                                                         // (15) 0.03125
/*50 */             err += buf[i] - '0';                                               // (10) 0.04102
/*52 */         }                                                                      // (23) 0.01562
/*54 */         dash = !!(buf[3] == '-');                                              // (11) 0.03711
/*58 */         for (i = 0; response_codes[i]; ++i) {                                  // (6) 0.04492
/*60 */             if (err == response_codes[i]) {                                    // (8) 0.04297
/*62 */                 if (line)                                                      // (12) 0.03711
/*64 */                     av_bprintf(&line_buffer, "%s", buf);                       // 0.0
/*66 */                 code_found = 1;                                                // 0.0
/*68 */                 result = err;                                                  // 0.0
/*70 */                 break;                                                         // 0.0
/*72 */             }                                                                  // 0.0
/*74 */         }                                                                      // 0.0
/*76 */     }                                                                          // 0.0
/*80 */     if (line)                                                                  // 0.0
/*82 */         av_bprint_finalize(&line_buffer, line);                                // 0.0
/*84 */     return result;                                                             // 0.0
/*86 */ }                                                                              // 0.0
