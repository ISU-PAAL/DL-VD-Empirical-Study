// commit message qemu@72cf2d4f0e (target=0, prob=0.0051377346, correct=True): Fix sys-queue.h conflict for good
/*0  */ void qemu_register_reset(QEMUResetHandler *func, void *opaque)  // (1) 0.213
/*2  */ {                                                               // (5) 0.009259
/*4  */     QEMUResetEntry *re = qemu_mallocz(sizeof(QEMUResetEntry));  // (0) 0.2778
/*8  */     re->func = func;                                            // (4) 0.08333
/*10 */     re->opaque = opaque;                                        // (3) 0.09259
/*12 */     TAILQ_INSERT_TAIL(&reset_handlers, re, entry);              // (2) 0.2037
/*14 */ }                                                               // (6) 0.009259
