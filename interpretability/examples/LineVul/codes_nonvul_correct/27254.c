// commit message qemu@e91e972ccf (target=0, prob=0.12967935, correct=True): s390x/ipl: drop reipl parameters on resets
/*0  */ int kvm_arch_handle_exit(CPUState *cs, struct kvm_run *run)               // (2) 0.05651
/*2  */ {                                                                         // (24) 0.002457
/*4  */     S390CPU *cpu = S390_CPU(cs);                                          // (10) 0.03931
/*6  */     int ret = 0;                                                          // (20) 0.01966
/*10 */     switch (run->exit_reason) {                                           // (17) 0.02948
/*12 */         case KVM_EXIT_S390_SIEIC:                                         // (3) 0.0516
/*14 */             ret = handle_intercept(cpu);                                  // (5) 0.04914
/*16 */             break;                                                        // (12) 0.03194
/*18 */         case KVM_EXIT_S390_RESET:                                         // (6) 0.04914
/*20 */             qemu_system_reset_request();                                  // (4) 0.0516
/*22 */             break;                                                        // (13) 0.03194
/*24 */         case KVM_EXIT_S390_TSCH:                                          // (7) 0.04914
/*26 */             ret = handle_tsch(cpu);                                       // (8) 0.04914
/*28 */             break;                                                        // (14) 0.03194
/*30 */         case KVM_EXIT_DEBUG:                                              // (11) 0.03931
/*32 */             ret = kvm_arch_handle_debug_exit(cpu);                        // (1) 0.06388
/*34 */             break;                                                        // (15) 0.03194
/*36 */         default:                                                          // (19) 0.02211
/*38 */             fprintf(stderr, "Unknown KVM exit: %d\n", run->exit_reason);  // (0) 0.086
/*40 */             break;                                                        // (16) 0.03194
/*42 */     }                                                                     // (22) 0.009828
/*46 */     if (ret == 0) {                                                       // (18) 0.02457
/*48 */         ret = EXCP_INTERRUPT;                                             // (9) 0.04177
/*50 */     }                                                                     // (23) 0.009828
/*52 */     return ret;                                                           // (21) 0.01474
/*54 */ }                                                                         // (25) 0.002457
