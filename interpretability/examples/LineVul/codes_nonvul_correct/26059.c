// commit message qemu@2fb50a3340 (target=0, prob=0.04906295, correct=True): nvic: Make set_pending and clear_pending take a secure parameter
/*0  */ static void armv7m_nvic_clear_pending(void *opaque, int irq)  // (2) 0.1311
/*2  */ {                                                             // (10) 0.005464
/*4  */     NVICState *s = (NVICState *)opaque;                       // (3) 0.0929
/*6  */     VecInfo *vec;                                             // (8) 0.04372
/*10 */     assert(irq > ARMV7M_EXCP_RESET && irq < s->num_irq);      // (0) 0.1585
/*14 */     vec = &s->vectors[irq];                                   // (5) 0.0765
/*16 */     trace_nvic_clear_pending(irq, vec->enabled, vec->prio);   // (1) 0.1366
/*18 */     if (vec->pending) {                                       // (7) 0.06011
/*20 */         vec->pending = 0;                                     // (6) 0.0765
/*22 */         nvic_irq_update(s);                                   // (4) 0.0929
/*24 */     }                                                         // (9) 0.02186
/*26 */ }                                                             // (11) 0.005464
