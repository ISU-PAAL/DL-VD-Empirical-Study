// commit message FFmpeg@ddbcc48b64 (target=0, prob=0.03875458, correct=True): ftp: enhanced error handling
/*0  */ static int ftp_current_dir(FTPContext *s)                // (13) 0.03538
/*2  */ {                                                        // (29) 0.002358
/*4  */     char *res = NULL, *start = NULL, *end = NULL;        // (3) 0.04481
/*6  */     int i;                                               // (24) 0.01415
/*8  */     const char *command = "PWD\r\n";                     // (10) 0.03774
/*10 */     const int pwd_codes[] = {257, 0};                    // (11) 0.03774
/*14 */     if (!ftp_send_command(s, command, pwd_codes, &res))  // (0) 0.0566
/*16 */         goto fail;                                       // (18) 0.02358
/*20 */     for (i = 0; res[i]; ++i) {                           // (6) 0.04009
/*22 */         if (res[i] == '"') {                             // (4) 0.04245
/*24 */             if (!start) {                                // (12) 0.03774
/*26 */                 start = res + i + 1;                     // (1) 0.05425
/*28 */                 continue;                                // (7) 0.04009
/*30 */             }                                            // (16) 0.0283
/*32 */             end = res + i;                               // (8) 0.04009
/*34 */             break;                                       // (15) 0.03066
/*36 */         }                                                // (22) 0.01887
/*38 */     }                                                    // (27) 0.009434
/*42 */     if (!end)                                            // (23) 0.01651
/*44 */         goto fail;                                       // (19) 0.02358
/*48 */     if (end > res && end[-1] == '/') {                   // (5) 0.04245
/*50 */         end[-1] = '\0';                                  // (9) 0.04009
/*52 */     } else                                               // (26) 0.01179
/*54 */         *end = '\0';                                     // (14) 0.03302
/*56 */     av_strlcpy(s->path, start, sizeof(s->path));         // (2) 0.04953
/*60 */     av_free(res);                                        // (20) 0.02123
/*62 */     return 0;                                            // (25) 0.01415
/*66 */   fail:                                                  // (28) 0.007075
/*68 */     av_free(res);                                        // (21) 0.02123
/*70 */     return AVERROR(EIO);                                 // (17) 0.02594
/*72 */ }                                                        // (30) 0.002358
