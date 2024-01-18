// commit message qemu@e155494cf0 (target=1, prob=0.15096912, correct=False): io: some fixes to handling of /dev/null when running commands
/*0  */ static void qio_channel_command_finalize(Object *obj)   // (2) 0.07547
/*2  */ {                                                       // (15) 0.004717
/*4  */     QIOChannelCommand *ioc = QIO_CHANNEL_COMMAND(obj);  // (0) 0.1132
/*6  */     if (ioc->readfd != -1) {                            // (5) 0.07075
/*8  */         close(ioc->readfd);                             // (6) 0.07075
/*10 */         ioc->readfd = -1;                               // (3) 0.07547
/*12 */     }                                                   // (11) 0.01887
/*14 */     if (ioc->writefd != -1) {                           // (7) 0.07075
/*16 */         close(ioc->writefd);                            // (8) 0.07075
/*18 */         ioc->writefd = -1;                              // (4) 0.07547
/*20 */     }                                                   // (12) 0.01887
/*22 */     if (ioc->pid > 0) {                                 // (9) 0.06132
/*24 */ #ifndef WIN32                                           // (10) 0.0283
/*26 */         qio_channel_command_abort(ioc, NULL);           // (1) 0.1038
/*28 */ #endif                                                  // (14) 0.009434
/*30 */     }                                                   // (13) 0.01887
/*32 */ }                                                       // (16) 0.004717
