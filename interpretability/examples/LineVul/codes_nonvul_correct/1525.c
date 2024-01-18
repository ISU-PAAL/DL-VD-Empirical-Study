// commit message FFmpeg@ddbcc48b64 (target=0, prob=0.008129909, correct=True): ftp: enhanced error handling
/*0  */ static int ftp_file_size(FTPContext *s)                          // (3) 0.06849
/*2  */ {                                                                // (14) 0.004566
/*4  */     char command[CONTROL_BUFFER_SIZE];                           // (5) 0.06849
/*6  */     char *res = NULL;                                            // (9) 0.0411
/*8  */     const int size_codes[] = {213, 0};                           // (6) 0.06849
/*12 */     snprintf(command, sizeof(command), "SIZE %s\r\n", s->path);  // (0) 0.1142
/*14 */     if (ftp_send_command(s, command, size_codes, &res)) {        // (1) 0.1096
/*16 */         s->filesize = strtoll(&res[4], NULL, 10);                // (2) 0.1096
/*18 */     } else {                                                     // (11) 0.0274
/*20 */         s->filesize = -1;                                        // (7) 0.06849
/*22 */         av_free(res);                                            // (8) 0.05936
/*24 */         return AVERROR(EIO);                                     // (4) 0.06849
/*26 */     }                                                            // (13) 0.01826
/*30 */     av_free(res);                                                // (10) 0.0411
/*32 */     return 0;                                                    // (12) 0.0274
/*34 */ }                                                                // (15) 0.004566
