// commit message qemu@9cbaacf999 (target=0, prob=0.072925024, correct=True): main-loop: drop rfds/wfds/xfds for good
/*0  */ static void gpollfds_from_select(void)                // (11) 0.03485
/*2  */ {                                                     // (21) 0.002681
/*4  */     int fd;                                           // (19) 0.01877
/*6  */     for (fd = 0; fd <= nfds; fd++) {                  // (8) 0.05362
/*8  */         int events = 0;                               // (12) 0.03217
/*10 */         if (FD_ISSET(fd, &rfds)) {                    // (4) 0.0563
/*12 */             events |= G_IO_IN | G_IO_HUP | G_IO_ERR;  // (0) 0.09115
/*14 */         }                                             // (15) 0.02145
/*16 */         if (FD_ISSET(fd, &wfds)) {                    // (3) 0.05898
/*18 */             events |= G_IO_OUT | G_IO_ERR;            // (2) 0.07239
/*20 */         }                                             // (16) 0.02145
/*22 */         if (FD_ISSET(fd, &xfds)) {                    // (5) 0.0563
/*24 */             events |= G_IO_PRI;                       // (6) 0.0563
/*26 */         }                                             // (17) 0.02145
/*28 */         if (events) {                                 // (13) 0.03217
/*30 */             GPollFD pfd = {                           // (10) 0.04826
/*32 */                 .fd = fd,                             // (7) 0.0563
/*34 */                 .events = events,                     // (9) 0.05362
/*36 */             };                                        // (14) 0.03217
/*38 */             g_array_append_val(gpollfds, pfd);        // (1) 0.07239
/*40 */         }                                             // (18) 0.02145
/*42 */     }                                                 // (20) 0.01072
/*44 */ }                                                     // (22) 0.002681
