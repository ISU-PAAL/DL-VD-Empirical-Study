// commit message qemu@9d6f1b73f8 (target=0, prob=0.63028216, correct=False): qemu-ga: ga_open_pidfile(): add new line to pidfile
/*0  */ static bool ga_open_pidfile(const char *pidfile)                   // (9) 0.04065
/*2  */ {                                                                  // (25) 0.00271
/*4  */     int pidfd;                                                     // (17) 0.01897
/*6  */     char pidstr[32];                                               // (14) 0.02439
/*10 */     pidfd = open(pidfile, O_CREAT|O_WRONLY, S_IRUSR|S_IWUSR);      // (0) 0.09485
/*12 */     if (pidfd == -1 || lockf(pidfd, F_TLOCK, 0)) {                 // (4) 0.06775
/*14 */         g_critical("Cannot lock pid file, %s", strerror(errno));   // (2) 0.07317
/*16 */         if (pidfd != -1) {                                         // (7) 0.04336
/*18 */             close(pidfd);                                          // (8) 0.04336
/*20 */         }                                                          // (16) 0.02168
/*22 */         return false;                                              // (13) 0.0271
/*24 */     }                                                              // (20) 0.01084
/*28 */     if (ftruncate(pidfd, 0) || lseek(pidfd, 0, SEEK_SET)) {        // (1) 0.0813
/*30 */         g_critical("Failed to truncate pid file");                 // (5) 0.05149
/*32 */         goto fail;                                                 // (11) 0.0271
/*34 */     }                                                              // (22) 0.01084
/*36 */     sprintf(pidstr, "%d", getpid());                               // (10) 0.04065
/*38 */     if (write(pidfd, pidstr, strlen(pidstr)) != strlen(pidstr)) {  // (3) 0.07317
/*40 */         g_critical("Failed to write pid file");                    // (6) 0.04878
/*42 */         goto fail;                                                 // (12) 0.0271
/*44 */     }                                                              // (21) 0.01084
/*48 */     return true;                                                   // (19) 0.01626
/*52 */ fail:                                                              // (23) 0.00542
/*54 */     unlink(pidfile);                                               // (15) 0.02439
/*56 */     return false;                                                  // (18) 0.01626
/*58 */ }                                                                  // (24) 0.00271
