// commit message qemu@72cf2d4f0e (target=0, prob=0.005374131, correct=True): Fix sys-queue.h conflict for good
/*0  */ void vmstate_unregister(const VMStateDescription *vmsd, void *opaque)  // (3) 0.125
/*2  */ {                                                                      // (8) 0.005952
/*4  */     SaveStateEntry *se, *new_se;                                       // (5) 0.08333
/*8  */     TAILQ_FOREACH_SAFE(se, &savevm_handlers, entry, new_se) {          // (0) 0.1726
/*10 */         if (se->vmsd == vmsd && se->opaque == opaque) {                // (2) 0.1607
/*12 */             TAILQ_REMOVE(&savevm_handlers, se, entry);                 // (1) 0.1726
/*14 */             qemu_free(se);                                             // (4) 0.1131
/*16 */         }                                                              // (6) 0.04762
/*18 */     }                                                                  // (7) 0.02381
/*20 */ }                                                                      // (9) 0.005952
