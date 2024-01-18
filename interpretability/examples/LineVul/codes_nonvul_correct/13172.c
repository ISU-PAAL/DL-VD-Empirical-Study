// commit message qemu@97f90cbfe8 (target=0, prob=0.3187316, correct=True): microblaze: HW Exception fixes.
/*0  */ void do_unassigned_access(target_phys_addr_t addr, int is_write, int is_exec,  // (6) 0.05882
/*2  */                           int is_asi, int size)                                // (3) 0.06933
/*4  */ {                                                                              // (23) 0.002101
/*6  */     CPUState *saved_env;                                                       // (12) 0.02311
/*8  */     /* XXX: hack to restore env in all cases, even if not called from          // (11) 0.03992
/*10 */        generated code */                                                       // (15) 0.01891
/*12 */     saved_env = env;                                                           // (16) 0.01891
/*14 */     env = cpu_single_env;                                                      // (13) 0.02311
/*16 */     qemu_log("Unassigned " TARGET_FMT_plx " wr=%d exe=%d\n",                   // (2) 0.07143
/*18 */              addr, is_write, is_exec);                                         // (10) 0.04622
/*20 */     if (!(env->sregs[SR_MSR] & MSR_EE)) {                                      // (9) 0.05042
/*22 */         return;                                                                // (17) 0.01891
/*24 */     }                                                                          // (21) 0.008403
/*28 */     if (is_exec) {                                                             // (14) 0.02101
/*30 */         if (!(env->pvr.regs[2] & PVR2_IOPB_BUS_EXC_MASK)) {                    // (0) 0.07983
/*32 */             env->sregs[SR_ESR] = ESR_EC_INSN_BUS;                              // (4) 0.06933
/*34 */             helper_raise_exception(EXCP_HW_EXCP);                              // (7) 0.05672
/*36 */         }                                                                      // (18) 0.01681
/*38 */     } else {                                                                   // (20) 0.01261
/*40 */         if (!(env->pvr.regs[2] & PVR2_DOPB_BUS_EXC_MASK)) {                    // (1) 0.07983
/*42 */             env->sregs[SR_ESR] = ESR_EC_DATA_BUS;                              // (5) 0.06723
/*44 */             helper_raise_exception(EXCP_HW_EXCP);                              // (8) 0.05672
/*46 */         }                                                                      // (19) 0.01681
/*48 */     }                                                                          // (22) 0.008403
/*50 */ }                                                                              // (24) 0.002101
