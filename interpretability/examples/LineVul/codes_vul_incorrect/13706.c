// commit message qemu@217bfb445b (target=1, prob=0.33381552, correct=False): hw/arm_gic.c: Ignore attempts to complete nonexistent IRQs
/*0  */ static void gic_complete_irq(gic_state * s, int cpu, int irq)                   // (6) 0.04688
/*2  */ {                                                                               // (24) 0.001953
/*4  */     int update = 0;                                                             // (21) 0.01562
/*6  */     int cm = 1 << cpu;                                                          // (20) 0.01953
/*8  */     DPRINTF("EOI %d\n", irq);                                                   // (13) 0.0332
/*10 */     if (s->running_irq[cpu] == 1023)                                            // (11) 0.03516
/*12 */         return; /* No active IRQ.  */                                           // (14) 0.0332
/*14 */     if (irq != 1023) {                                                          // (18) 0.02344
/*16 */         /* Mark level triggered interrupts as pending if they are still         // (10) 0.03516
/*18 */            raised.  */                                                          // (17) 0.02734
/*20 */         if (!GIC_TEST_TRIGGER(irq) && GIC_TEST_ENABLED(irq, cm)                 // (1) 0.07422
/*22 */                 && GIC_TEST_LEVEL(irq, cm) && (GIC_TARGET(irq) & cm) != 0) {    // (0) 0.09375
/*24 */             DPRINTF("Set %d pending mask %x\n", irq, cm);                       // (3) 0.05859
/*26 */             GIC_SET_PENDING(irq, cm);                                           // (5) 0.04883
/*28 */             update = 1;                                                         // (16) 0.0293
/*30 */         }                                                                       // (22) 0.01562
/*32 */     }                                                                           // (23) 0.007812
/*34 */     if (irq != s->running_irq[cpu]) {                                           // (12) 0.03516
/*36 */         /* Complete an IRQ that is not currently running.  */                   // (8) 0.03906
/*38 */         int tmp = s->running_irq[cpu];                                          // (9) 0.03711
/*40 */         while (s->last_active[tmp][cpu] != 1023) {                              // (7) 0.04688
/*42 */             if (s->last_active[tmp][cpu] == irq) {                              // (4) 0.05469
/*44 */                 s->last_active[tmp][cpu] = s->last_active[irq][cpu];            // (2) 0.07227
/*46 */                 break;                                                          // (15) 0.0332
/*48 */             }                                                                   // (19) 0.02344
/*50 */             tmp = s->last_active[tmp][cpu];                                     // 0.0
/*52 */         }                                                                       // 0.0
/*54 */         if (update) {                                                           // 0.0
/*56 */             gic_update(s);                                                      // 0.0
/*58 */         }                                                                       // 0.0
/*60 */     } else {                                                                    // 0.0
/*62 */         /* Complete the current running IRQ.  */                                // 0.0
/*64 */         gic_set_running_irq(s, cpu, s->last_active[s->running_irq[cpu]][cpu]);  // 0.0
/*66 */     }                                                                           // 0.0
/*68 */ }                                                                               // 0.0
