// commit message qemu@62deb62d99 (target=0, prob=0.029796092, correct=True): s390x/kvm: enable guarded storage
/*0  */ static void sigp_store_adtl_status(CPUState *cs, run_on_cpu_data arg)  // (5) 0.06295
/*2  */ {                                                                      // (23) 0.002421
/*4  */     S390CPU *cpu = S390_CPU(cs);                                       // (9) 0.03874
/*6  */     SigpInfo *si = arg.host_ptr;                                       // (10) 0.03632
/*10 */     if (!s390_has_feat(S390_FEAT_VECTOR)) {                            // (7) 0.05569
/*12 */         set_sigp_status(si, SIGP_STAT_INVALID_ORDER);                  // (2) 0.07022
/*14 */         return;                                                        // (15) 0.02179
/*16 */     }                                                                  // (19) 0.009685
/*20 */     /* cpu has to be stopped */                                        // (14) 0.02421
/*22 */     if (s390_cpu_get_state(cpu) != CPU_STATE_STOPPED) {                // (4) 0.06538
/*24 */         set_sigp_status(si, SIGP_STAT_INCORRECT_STATE);                // (3) 0.0678
/*26 */         return;                                                        // (16) 0.02179
/*28 */     }                                                                  // (20) 0.009685
/*32 */     /* parameter must be aligned to 1024-byte boundary */              // (12) 0.0339
/*34 */     if (si->param & 0x3ff) {                                           // (11) 0.03632
/*36 */         set_sigp_status(si, SIGP_STAT_INVALID_PARAMETER);              // (0) 0.07506
/*38 */         return;                                                        // (17) 0.02179
/*40 */     }                                                                  // (21) 0.009685
/*44 */     cpu_synchronize_state(cs);                                         // (13) 0.03148
/*48 */     if (kvm_s390_store_adtl_status(cpu, si->param)) {                  // (6) 0.06053
/*50 */         set_sigp_status(si, SIGP_STAT_INVALID_PARAMETER);              // (1) 0.07506
/*52 */         return;                                                        // (18) 0.02179
/*54 */     }                                                                  // (22) 0.009685
/*56 */     si->cc = SIGP_CC_ORDER_CODE_ACCEPTED;                              // (8) 0.05327
/*58 */ }                                                                      // (24) 0.002421
