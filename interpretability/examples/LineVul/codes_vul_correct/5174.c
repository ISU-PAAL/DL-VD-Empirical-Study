// commit message qemu@5ee5993001 (target=1, prob=0.9990602, correct=True): sparc/sparc64: grab BQL before calling cpu_check_irqs
/*0  */ static bool do_modify_softint(CPUSPARCState *env, uint32_t value)  // (0) 0.1538
/*2  */ {                                                                  // (11) 0.00641
/*4  */     if (env->softint != value) {                                   // (5) 0.08333
/*6  */         env->softint = value;                                      // (3) 0.08974
/*8  */ #if !defined(CONFIG_USER_ONLY)                                     // (4) 0.08333
/*10 */         if (cpu_interrupts_enabled(env)) {                         // (1) 0.1282
/*13 */             cpu_check_irqs(env);                                   // (2) 0.1282
/*16 */         }                                                          // (7) 0.05128
/*18 */ #endif                                                             // (10) 0.01282
/*20 */         return true;                                               // (6) 0.0641
/*22 */     }                                                              // (9) 0.02564
/*24 */     return false;                                                  // (8) 0.03846
/*26 */ }                                                                  // (12) 0.00641
