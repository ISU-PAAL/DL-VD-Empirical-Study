// commit message qemu@b4548fcc03 (target=1, prob=0.037623636, correct=False): trace: Remove %s in grlib trace events
/*0   */ static uint32_t grlib_irqmp_readl(void *opaque, target_phys_addr_t addr)   // (0) 0.05664
/*2   */ {                                                                          // (35) 0.001953
/*4   */     IRQMP      *irqmp = opaque;                                            // (8) 0.03516
/*6   */     IRQMPState *state;                                                     // (21) 0.01953
/*10  */     assert(irqmp != NULL);                                                 // (18) 0.02148
/*12  */     state = irqmp->state;                                                  // (16) 0.02148
/*14  */     assert(state != NULL);                                                 // (25) 0.01758
/*18  */     addr &= 0xff;                                                          // (24) 0.01758
/*22  */     /* global registers */                                                 // (29) 0.01367
/*24  */     switch (addr) {                                                        // (28) 0.01562
/*26  */     case LEVEL_OFFSET:                                                     // (26) 0.01758
/*28  */         return state->level;                                               // (15) 0.02344
/*32  */     case PENDING_OFFSET:                                                   // (17) 0.02148
/*34  */         return state->pending;                                             // (11) 0.02539
/*38  */     case FORCE0_OFFSET:                                                    // (19) 0.02148
/*40  */         /* This register is an "alias" for the force register of CPU 0 */  // (1) 0.04492
/*42  */         return state->force[0];                                            // (10) 0.02734
/*46  */     case CLEAR_OFFSET:                                                     // (22) 0.01953
/*48  */     case MP_STATUS_OFFSET:                                                 // (14) 0.02344
/*50  */         /* Always read as 0 */                                             // (13) 0.02539
/*52  */         return 0;                                                          // (23) 0.01953
/*56  */     case BROADCAST_OFFSET:                                                 // (20) 0.02148
/*58  */         return state->broadcast;                                           // (12) 0.02539
/*62  */     default:                                                               // (32) 0.009766
/*64  */         break;                                                             // (27) 0.01758
/*66  */     }                                                                      // (33) 0.007812
/*70  */     /* mask registers */                                                   // (30) 0.01367
/*72  */     if (addr >= MASK_OFFSET && addr < FORCE_OFFSET) {                      // (4) 0.04297
/*74  */         int cpu = (addr - MASK_OFFSET) / 4;                                // (5) 0.04297
/*76  */         assert(cpu >= 0 && cpu < IRQMP_MAX_CPU);                           // (2) 0.04492
/*80  */         return state->mask[cpu];                                           // (9) 0.02734
/*82  */     }                                                                      // (34) 0.007812
/*86  */     /* force registers */                                                  // (31) 0.01367
/*88  */     if (addr >= FORCE_OFFSET && addr < EXTENDED_OFFSET) {                  // (6) 0.04297
/*90  */         int cpu = (addr - FORCE_OFFSET) / 4;                               // (7) 0.04297
/*92  */         assert(cpu >= 0 && cpu < IRQMP_MAX_CPU);                           // (3) 0.04492
/*96  */         return state->force[cpu];                                          // 0.0
/*98  */     }                                                                      // 0.0
/*102 */     /* extended (not supported) */                                         // 0.0
/*104 */     if (addr >= EXTENDED_OFFSET && addr < IRQMP_REG_SIZE) {                // 0.0
/*106 */         int cpu = (addr - EXTENDED_OFFSET) / 4;                            // 0.0
/*108 */         assert(cpu >= 0 && cpu < IRQMP_MAX_CPU);                           // 0.0
/*112 */         return state->extended[cpu];                                       // 0.0
/*114 */     }                                                                      // 0.0
/*118 */     trace_grlib_irqmp_unknown_register("read", addr);                      // 0.0
/*120 */     return 0;                                                              // 0.0
/*122 */ }                                                                          // 0.0
