// commit message qemu@a426e12217 (target=0, prob=0.347065, correct=True): kvm: Fix coding style violations
/*0  */ int kvm_remove_breakpoint(CPUState *current_env, target_ulong addr,             // (7) 0.04339
/*2  */                           target_ulong len, int type)                           // (1) 0.06706
/*4  */ {                                                                               // (29) 0.001972
/*6  */     struct kvm_sw_breakpoint *bp;                                               // (13) 0.02761
/*8  */     CPUState *env;                                                              // (22) 0.01578
/*10 */     int err;                                                                    // (24) 0.01183
/*14 */     if (type == GDB_BREAKPOINT_SW) {                                            // (9) 0.0355
/*16 */         bp = kvm_find_sw_breakpoint(current_env, addr);                         // (4) 0.05128
/*18 */         if (!bp)                                                                // (18) 0.0217
/*20 */             return -ENOENT;                                                     // (11) 0.03353
/*24 */         if (bp->use_count > 1) {                                                // (10) 0.0355
/*26 */             bp->use_count--;                                                    // (8) 0.03748
/*28 */             return 0;                                                           // (14) 0.02761
/*30 */         }                                                                       // (23) 0.01578
/*34 */         err = kvm_arch_remove_sw_breakpoint(current_env, bp);                   // (2) 0.05523
/*36 */         if (err)                                                                // (19) 0.0217
/*38 */             return err;                                                         // (15) 0.02761
/*42 */         QTAILQ_REMOVE(&current_env->kvm_state->kvm_sw_breakpoints, bp, entry);  // (0) 0.07495
/*44 */         qemu_free(bp);                                                          // (12) 0.02959
/*46 */     } else {                                                                    // (25) 0.01183
/*48 */         err = kvm_arch_remove_hw_breakpoint(addr, len, type);                   // (3) 0.05325
/*50 */         if (err)                                                                // (20) 0.0217
/*52 */             return err;                                                         // (16) 0.02761
/*54 */     }                                                                           // (27) 0.00789
/*58 */     for (env = first_cpu; env != NULL; env = env->next_cpu) {                   // (5) 0.04734
/*60 */         err = kvm_update_guest_debug(env, 0);                                   // (6) 0.04536
/*62 */         if (err)                                                                // (21) 0.0217
/*64 */             return err;                                                         // (17) 0.02761
/*66 */     }                                                                           // (28) 0.00789
/*68 */     return 0;                                                                   // (26) 0.01183
/*70 */ }                                                                               // (30) 0.001972
