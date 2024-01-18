// commit message qemu@9ef91a6771 (target=0, prob=0.0074108806, correct=True): raw-posix: refactor AIO support
/*0  */ int qemu_paio_init(struct qemu_paioinit *aioinit)                       // (2) 0.1373
/*2  */ {                                                                       // (8) 0.006536
/*4  */     int ret;                                                            // (6) 0.03922
/*8  */     ret = pthread_attr_init(&attr);                                     // (5) 0.0915
/*10 */     if (ret) die2(ret, "pthread_attr_init");                            // (3) 0.1307
/*14 */     ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);  // (0) 0.1895
/*16 */     if (ret) die2(ret, "pthread_attr_setdetachstate");                  // (1) 0.1503
/*20 */     TAILQ_INIT(&request_list);                                          // (4) 0.0915
/*24 */     return 0;                                                           // (7) 0.03922
/*26 */ }                                                                       // (9) 0.006536
