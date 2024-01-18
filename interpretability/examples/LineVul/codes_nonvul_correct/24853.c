// commit message qemu@94ad5b00a3 (target=0, prob=0.034447554, correct=True): always qemu_cpu_kick after unhalting a cpu
/*0  */ static void cpu_set_irq(void *opaque, int irq, int level)  // (3) 0.09767
/*2  */ {                                                          // (12) 0.004651
/*4  */     CPUState *env = opaque;                                // (8) 0.04651
/*8  */     if (level) {                                           // (9) 0.03721
/*10 */         CPUIRQ_DPRINTF("Raise CPU IRQ %d\n", irq);         // (0) 0.1349
/*12 */         env->halted = 0;                                   // (7) 0.06512
/*14 */         env->pil_in |= 1 << irq;                           // (4) 0.09302
/*16 */         cpu_check_irqs(env);                               // (5) 0.07442
/*18 */     } else {                                               // (10) 0.02791
/*20 */         CPUIRQ_DPRINTF("Lower CPU IRQ %d\n", irq);         // (1) 0.1302
/*22 */         env->pil_in &= ~(1 << irq);                        // (2) 0.1023
/*24 */         cpu_check_irqs(env);                               // (6) 0.07442
/*26 */     }                                                      // (11) 0.0186
/*28 */ }                                                          // (13) 0.004651
