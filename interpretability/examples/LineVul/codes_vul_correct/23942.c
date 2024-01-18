// commit message qemu@9ed415b28b (target=1, prob=0.9991528, correct=True): initialize struct sigevent before timer_create
/*0  */ static int dynticks_start_timer(struct qemu_alarm_timer *t)  // (1) 0.07166
/*2  */ {                                                            // (19) 0.003257
/*4  */     struct sigevent ev;                                      // (15) 0.02932
/*6  */     timer_t host_timer;                                      // (14) 0.03257
/*8  */     struct sigaction act;                                    // (16) 0.02606
/*12 */     sigfillset(&act.sa_mask);                                // (9) 0.0456
/*14 */     act.sa_flags = 0;                                        // (12) 0.03583
/*16 */     act.sa_handler = host_alarm_handler;                     // (6) 0.05212
/*20 */     sigaction(SIGALRM, &act, NULL);                          // (7) 0.05212
/*29 */     ev.sigev_value.sival_int = 0;                            // (3) 0.05863
/*31 */     ev.sigev_notify = SIGEV_SIGNAL;                          // (4) 0.05863
/*33 */     ev.sigev_signo = SIGALRM;                                // (8) 0.05212
/*37 */     if (timer_create(CLOCK_REALTIME, &ev, &host_timer)) {    // (0) 0.08143
/*39 */         perror("timer_create");                              // (10) 0.0456
/*43 */         /* disable dynticks */                               // (11) 0.04235
/*45 */         fprintf(stderr, "Dynamic Ticks disabled\n");         // (2) 0.07166
/*49 */         return -1;                                           // (13) 0.03583
/*51 */     }                                                        // (18) 0.01303
/*55 */     t->priv = (void *)(long)host_timer;                      // (5) 0.05537
/*59 */     return 0;                                                // (17) 0.01954
/*61 */ }                                                            // (20) 0.003257
