// commit message FFmpeg@229843aa35 (target=0, prob=0.035796154, correct=True): Replace av_dlog with ff_dlog.
/*0  */ static int ftp_passive_mode_epsv(FTPContext *s)                           // (4) 0.03733
/*2  */ {                                                                         // (33) 0.001965
/*4  */     char *res = NULL, *start = NULL, *end = NULL;                         // (5) 0.03733
/*6  */     int i;                                                                // (29) 0.01179
/*8  */     static const char d = '|';                                            // (18) 0.02161
/*10 */     static const char *command = "EPSV\r\n";                              // (7) 0.03536
/*12 */     static const int epsv_codes[] = {229, 0};                             // (8) 0.03536
/*16 */     if (ftp_send_command(s, command, epsv_codes, &res) != 229 || !res)    // (1) 0.0609
/*18 */         goto fail;                                                        // (19) 0.01965
/*22 */     for (i = 0; res[i]; ++i) {                                            // (10) 0.0334
/*24 */         if (res[i] == '(') {                                              // (9) 0.03536
/*26 */             start = res + i + 1;                                          // (6) 0.03733
/*28 */         } else if (res[i] == ')') {                                       // (3) 0.03929
/*30 */             end = res + i;                                                // (11) 0.0334
/*32 */             break;                                                        // (14) 0.02554
/*34 */         }                                                                 // (27) 0.01572
/*36 */     }                                                                     // (31) 0.007859
/*38 */     if (!start || !end)                                                   // (20) 0.01965
/*40 */         goto fail;                                                        // (21) 0.01965
/*44 */     *end = '\0';                                                          // (22) 0.01965
/*46 */     if (strlen(start) < 5)                                                // (15) 0.02554
/*48 */         goto fail;                                                        // (23) 0.01965
/*50 */     if (start[0] != d || start[1] != d || start[2] != d || end[-1] != d)  // (0) 0.0668
/*52 */         goto fail;                                                        // (24) 0.01965
/*54 */     start += 3;                                                           // (28) 0.01375
/*56 */     end[-1] = '\0';                                                       // (16) 0.02554
/*60 */     s->server_data_port = atoi(start);                                    // (12) 0.03143
/*62 */     av_dlog(s, "Server data port: %d\n", s->server_data_port);            // (2) 0.05501
/*66 */     av_free(res);                                                         // (25) 0.01768
/*68 */     return 0;                                                             // (30) 0.01179
/*72 */   fail:                                                                   // (32) 0.005894
/*74 */     av_free(res);                                                         // (26) 0.01768
/*76 */     s->server_data_port = -1;                                             // (13) 0.0275
/*78 */     return AVERROR(ENOSYS);                                               // (17) 0.02358
/*80 */ }                                                                         // (34) 0.001965
