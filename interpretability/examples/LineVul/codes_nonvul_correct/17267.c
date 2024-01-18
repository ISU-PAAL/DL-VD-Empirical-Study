// commit message qemu@ef1e1e0782 (target=0, prob=0.42796233, correct=True): maint: avoid useless "if (foo) free(foo)" pattern
/*0  */ void vmstate_unregister(DeviceState *dev, const VMStateDescription *vmsd,  // (5) 0.08108
/*2  */                         void *opaque)                                      // (2) 0.1081
/*4  */ {                                                                          // (13) 0.003861
/*6  */     SaveStateEntry *se, *new_se;                                           // (8) 0.05405
/*10 */     QTAILQ_FOREACH_SAFE(se, &savevm_state.handlers, entry, new_se) {       // (0) 0.1236
/*12 */         if (se->vmsd == vmsd && se->opaque == opaque) {                    // (3) 0.1042
/*14 */             QTAILQ_REMOVE(&savevm_state.handlers, se, entry);              // (1) 0.1236
/*16 */             if (se->compat) {                                              // (6) 0.07336
/*18 */                 g_free(se->compat);                                        // (4) 0.09266
/*20 */             }                                                              // (9) 0.04633
/*22 */             g_free(se);                                                    // (7) 0.06564
/*24 */         }                                                                  // (10) 0.03089
/*26 */     }                                                                      // (11) 0.01544
/*28 */ }                                                                          // (12) 0.003861
