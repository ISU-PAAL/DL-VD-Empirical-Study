// commit message qemu@2531088f6c (target=1, prob=0.16787246, correct=False): hw/intc/arm_gic: add tracepoints
/*0  */ static void gic_set_irq(void *opaque, int irq, int level)               // (6) 0.04297
/*2  */ {                                                                       // (29) 0.001953
/*4  */     /* Meaning of the 'irq' parameter:                                  // (18) 0.02539
/*6  */      *  [0..N-1] : external interrupts                                  // (14) 0.03125
/*8  */      *  [N..N+31] : PPI (internal) interrupts for CPU 0                 // (5) 0.04492
/*10 */      *  [N+32..N+63] : PPI (internal interrupts for CPU 1               // (3) 0.04688
/*12 */      *  ...                                                             // (23) 0.01367
/*14 */      */                                                                 // (26) 0.009766
/*16 */     GICState *s = (GICState *)opaque;                                   // (12) 0.0332
/*18 */     int cm, target;                                                     // (22) 0.01562
/*20 */     if (irq < (s->num_irq - GIC_INTERNAL)) {                            // (4) 0.04688
/*22 */         /* The first external input line is internal interrupt 32.  */  // (8) 0.03906
/*24 */         cm = ALL_CPU_MASK;                                              // (15) 0.03125
/*26 */         irq += GIC_INTERNAL;                                            // (13) 0.0332
/*28 */         target = GIC_TARGET(irq);                                       // (10) 0.03516
/*30 */     } else {                                                            // (24) 0.01172
/*32 */         int cpu;                                                        // (20) 0.01953
/*34 */         irq -= (s->num_irq - GIC_INTERNAL);                             // (2) 0.04883
/*36 */         cpu = irq / GIC_INTERNAL;                                       // (9) 0.03711
/*38 */         irq %= GIC_INTERNAL;                                            // (11) 0.03516
/*40 */         cm = 1 << cpu;                                                  // (17) 0.02539
/*42 */         target = cm;                                                    // (19) 0.02148
/*44 */     }                                                                   // (27) 0.007812
/*48 */     assert(irq >= GIC_NR_SGIS);                                         // (16) 0.03125
/*52 */     if (level == GIC_TEST_LEVEL(irq, cm)) {                             // (7) 0.04297
/*54 */         return;                                                         // (21) 0.01758
/*56 */     }                                                                   // (28) 0.007812
/*60 */     if (s->revision == REV_11MPCORE || s->revision == REV_NVIC) {       // (0) 0.05859
/*62 */         gic_set_irq_11mpcore(s, irq, level, cm, target);                // (1) 0.05859
/*64 */     } else {                                                            // (25) 0.01172
/*66 */         gic_set_irq_generic(s, irq, level, cm, target);                 // 0.0
/*68 */     }                                                                   // 0.0
/*73 */     gic_update(s);                                                      // 0.0
/*75 */ }                                                                       // 0.0
