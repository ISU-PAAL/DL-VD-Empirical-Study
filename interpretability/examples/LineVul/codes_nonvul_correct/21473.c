// commit message qemu@96193c22ab (target=0, prob=0.022632945, correct=True): target-i386: Move xsave component mask to features array
/*0  */ static void x86_cpu_enable_xsave_components(X86CPU *cpu)                     // (8) 0.05147
/*2  */ {                                                                            // (20) 0.002451
/*4  */     CPUX86State *env = &cpu->env;                                            // (11) 0.03676
/*6  */     int i;                                                                   // (16) 0.01471
/*10 */     if (!(env->features[FEAT_1_ECX] & CPUID_EXT_XSAVE)) {                    // (2) 0.07108
/*12 */         return;                                                              // (14) 0.02206
/*14 */     }                                                                        // (17) 0.009804
/*18 */     env->xsave_components = (XSTATE_FP_MASK | XSTATE_SSE_MASK);              // (3) 0.07108
/*20 */     for (i = 2; i < ARRAY_SIZE(x86_ext_save_areas); i++) {                   // (4) 0.07108
/*22 */         const ExtSaveArea *esa = &x86_ext_save_areas[i];                     // (5) 0.06618
/*24 */         if (env->features[esa->feature] & esa->bits) {                       // (7) 0.05882
/*26 */             env->xsave_components |= (1ULL << i);                            // (6) 0.06373
/*28 */         }                                                                    // (15) 0.01961
/*30 */     }                                                                        // (18) 0.009804
/*34 */     if (kvm_enabled()) {                                                     // (13) 0.02696
/*36 */         KVMState *s = kvm_state;                                             // (10) 0.04412
/*38 */         uint64_t kvm_mask = kvm_arch_get_supported_cpuid(s, 0xd, 0, R_EDX);  // (0) 0.09804
/*40 */         kvm_mask <<= 32;                                                     // (12) 0.03676
/*42 */         kvm_mask |= kvm_arch_get_supported_cpuid(s, 0xd, 0, R_EAX);          // (1) 0.09069
/*44 */         env->xsave_components &= kvm_mask;                                   // (9) 0.05147
/*46 */     }                                                                        // (19) 0.009804
/*48 */ }                                                                            // (21) 0.002451
