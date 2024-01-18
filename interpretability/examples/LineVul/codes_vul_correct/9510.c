// commit message qemu@9e472e101f (target=1, prob=0.565597, correct=True): Fix IO performance regression in sparc
/*0  */ static int qemu_signalfd_compat(const sigset_t *mask)             // (2) 0.06885
/*2  */ {                                                                 // (21) 0.003279
/*4  */     pthread_attr_t attr;                                          // (8) 0.03934
/*6  */     pthread_t tid;                                                // (16) 0.02951
/*8  */     struct sigfd_compat_info *info;                               // (5) 0.0459
/*10 */     int fds[2];                                                   // (17) 0.02951
/*14 */     info = malloc(sizeof(*info));                                 // (7) 0.04262
/*16 */     if (info == NULL) {                                           // (15) 0.03279
/*18 */         errno = ENOMEM;                                           // (6) 0.0459
/*20 */         return -1;                                                // (12) 0.03607
/*22 */     }                                                             // (19) 0.01311
/*26 */     if (pipe(fds) == -1) {                                        // (4) 0.04918
/*28 */         free(info);                                               // (13) 0.03607
/*30 */         return -1;                                                // (14) 0.03607
/*32 */     }                                                             // (20) 0.01311
/*36 */     memcpy(&info->mask, mask, sizeof(*mask));                     // (3) 0.05574
/*38 */     info->fd = fds[1];                                            // (9) 0.03934
/*42 */     pthread_attr_init(&attr);                                     // (10) 0.03934
/*44 */     pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);  // (0) 0.08852
/*48 */     pthread_create(&tid, &attr, sigwait_compat, info);            // (1) 0.07213
/*52 */     pthread_attr_destroy(&attr);                                  // (11) 0.03934
/*56 */     return fds[0];                                                // (18) 0.02951
/*58 */ }                                                                 // (22) 0.003279
