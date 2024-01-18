// commit message FFmpeg@ddbcc48b64 (target=0, prob=0.008058988, correct=True): ftp: enhanced error handling
/*0  */ static int ftp_restart(FTPContext *s, int64_t pos)                  // (2) 0.1449
/*2  */ {                                                                   // (7) 0.007246
/*4  */     char command[CONTROL_BUFFER_SIZE];                              // (3) 0.1087
/*6  */     const int rest_codes[] = {350, 0};                              // (4) 0.1087
/*10 */     snprintf(command, sizeof(command), "REST %"PRId64"\r\n", pos);  // (0) 0.2029
/*12 */     if (!ftp_send_command(s, command, rest_codes, NULL))            // (1) 0.1594
/*14 */         return AVERROR(EIO);                                        // (5) 0.1087
/*18 */     return 0;                                                       // (6) 0.04348
/*20 */ }                                                                   // (8) 0.007246
