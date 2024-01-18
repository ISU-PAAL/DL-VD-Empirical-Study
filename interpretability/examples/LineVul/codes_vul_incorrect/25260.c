// commit message qemu@af7e9e74c6 (target=1, prob=0.41118094, correct=False): openpic: fix coding style issues
/*0   */ static void openpic_update_irq(OpenPICState *opp, int n_IRQ)         // (5) 0.04492
/*2   */ {                                                                    // (31) 0.001953
/*4   */     IRQ_src_t *src;                                                  // (16) 0.02344
/*6   */     int i;                                                           // (25) 0.01172
/*10  */     src = &opp->src[n_IRQ];                                          // (11) 0.0293
/*14  */     if (!src->pending) {                                             // (18) 0.02148
/*16  */         /* no irq pending */                                         // (13) 0.02539
/*18  */         DPRINTF("%s: IRQ %d is not pending\n", __func__, n_IRQ);     // (0) 0.06445
/*20  */         return;                                                      // (20) 0.01758
/*22  */     }                                                                // (26) 0.007812
/*24  */     if (src->ipvp & IPVP_MASK_MASK) {                                // (8) 0.03906
/*26  */         /* Interrupt source is disabled */                           // (12) 0.02734
/*28  */         DPRINTF("%s: IRQ %d is disabled\n", __func__, n_IRQ);        // (4) 0.0625
/*30  */         return;                                                      // (21) 0.01758
/*32  */     }                                                                // (27) 0.007812
/*34  */     if (IPVP_PRIORITY(src->ipvp) == 0) {                             // (6) 0.04102
/*36  */         /* Priority set to zero */                                   // (14) 0.02539
/*38  */         DPRINTF("%s: IRQ %d has 0 priority\n", __func__, n_IRQ);     // (1) 0.06445
/*40  */         return;                                                      // (22) 0.01758
/*42  */     }                                                                // (28) 0.007812
/*44  */     if (src->ipvp & IPVP_ACTIVITY_MASK) {                            // (7) 0.04102
/*46  */         /* IRQ already active */                                     // (15) 0.02539
/*48  */         DPRINTF("%s: IRQ %d is already active\n", __func__, n_IRQ);  // (2) 0.06445
/*50  */         return;                                                      // (23) 0.01758
/*52  */     }                                                                // (29) 0.007812
/*54  */     if (src->ide == 0) {                                             // (17) 0.02344
/*56  */         /* No target */                                              // (19) 0.02148
/*58  */         DPRINTF("%s: IRQ %d has no target\n", __func__, n_IRQ);      // (3) 0.06445
/*60  */         return;                                                      // (24) 0.01758
/*62  */     }                                                                // (30) 0.007812
/*66  */     if (src->ide == (1 << src->last_cpu)) {                          // (10) 0.03711
/*68  */         /* Only one CPU is allowed to receive this IRQ */            // (9) 0.03711
/*70  */         IRQ_local_pipe(opp, src->last_cpu, n_IRQ);                   // 0.0
/*72  */     } else if (!(src->ipvp & IPVP_MODE_MASK)) {                      // 0.0
/*74  */         /* Directed delivery mode */                                 // 0.0
/*76  */         for (i = 0; i < opp->nb_cpus; i++) {                         // 0.0
/*78  */             if (src->ide & (1 << i)) {                               // 0.0
/*80  */                 IRQ_local_pipe(opp, i, n_IRQ);                       // 0.0
/*82  */             }                                                        // 0.0
/*84  */         }                                                            // 0.0
/*86  */     } else {                                                         // 0.0
/*88  */         /* Distributed delivery mode */                              // 0.0
/*90  */         for (i = src->last_cpu + 1; i != src->last_cpu; i++) {       // 0.0
/*92  */             if (i == opp->nb_cpus)                                   // 0.0
/*94  */                 i = 0;                                               // 0.0
/*96  */             if (src->ide & (1 << i)) {                               // 0.0
/*98  */                 IRQ_local_pipe(opp, i, n_IRQ);                       // 0.0
/*100 */                 src->last_cpu = i;                                   // 0.0
/*102 */                 break;                                               // 0.0
/*104 */             }                                                        // 0.0
/*106 */         }                                                            // 0.0
/*108 */     }                                                                // 0.0
/*110 */ }                                                                    // 0.0
