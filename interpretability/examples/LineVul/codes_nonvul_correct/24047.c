// commit message qemu@72cf2d4f0e (target=0, prob=0.008176681, correct=True): Fix sys-queue.h conflict for good
/*0  */ int qemu_opts_foreach(QemuOptsList *list, qemu_opts_loopfunc func, void *opaque,  // (0) 0.1925
/*2  */                       int abort_on_failure)                                       // (1) 0.1551
/*4  */ {                                                                                 // (10) 0.005348
/*6  */     QemuOpts *opts;                                                               // (6) 0.06417
/*8  */     int rc = 0;                                                                   // (7) 0.04278
/*12 */     TAILQ_FOREACH(opts, &list->head, next) {                                      // (3) 0.1123
/*14 */         rc = func(opts, opaque);                                                  // (4) 0.08556
/*16 */         if (abort_on_failure  &&  rc != 0)                                        // (2) 0.123
/*18 */             break;                                                                // (5) 0.06952
/*20 */     }                                                                             // (9) 0.02139
/*22 */     return rc;                                                                    // (8) 0.03209
/*24 */ }                                                                                 // (11) 0.005348
