// commit message qemu@ea375f9ab8 (target=1, prob=0.15071872, correct=False): KVM: Rework VCPU state writeback API
/*0  */ void qemu_system_reset(void)                                // (3) 0.1134
/*2  */ {                                                           // (6) 0.01031
/*4  */     QEMUResetEntry *re, *nre;                               // (2) 0.1649
/*8  */     /* reset all devices */                                 // (4) 0.08247
/*10 */     QTAILQ_FOREACH_SAFE(re, &reset_handlers, entry, nre) {  // (0) 0.2887
/*12 */         re->func(re->opaque);                               // (1) 0.1649
/*14 */     }                                                       // (5) 0.04124
/*17 */ }                                                           // (7) 0.01031
