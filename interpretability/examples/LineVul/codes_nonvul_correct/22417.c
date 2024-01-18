// commit message qemu@c34d440a72 (target=0, prob=0.35049292, correct=True): kvm: x86: Consolidate TCG and KVM MCE injection code
/*0  */ static void kvm_inject_x86_mce_on(CPUState *env, struct kvm_x86_mce *mce,  // (1) 0.1399
/*2  */                                   int flag)                                // (0) 0.1481
/*4  */ {                                                                          // (12) 0.004115
/*6  */     struct kvm_x86_mce_data data = {                                       // (5) 0.06996
/*8  */         .env = env,                                                        // (8) 0.04938
/*10 */         .mce = mce,                                                        // (6) 0.05761
/*12 */         .abort_on_error = (flag & ABORT_ON_ERROR),                         // (4) 0.1029
/*14 */     };                                                                     // (10) 0.01646
/*18 */     if (!env->mcg_cap) {                                                   // (7) 0.0535
/*20 */         fprintf(stderr, "MCE support is not enabled!\n");                  // (3) 0.1029
/*22 */         return;                                                            // (9) 0.03704
/*24 */     }                                                                      // (11) 0.01646
/*28 */     run_on_cpu(env, kvm_do_inject_x86_mce, &data);                         // (2) 0.1152
/*30 */ }                                                                          // (13) 0.004115
