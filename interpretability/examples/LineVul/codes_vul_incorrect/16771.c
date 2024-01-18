// commit message qemu@94a8d39afd (target=1, prob=0.08030669, correct=False): kvm: Consolidate must-have capability checks
/*0   */ uint32_t kvm_arch_get_supported_cpuid(CPUState *env, uint32_t function,            // (6) 0.05273
/*2   */                                       uint32_t index, int reg)                     // (0) 0.08984
/*4   */ {                                                                                  // (25) 0.001953
/*6   */     struct kvm_cpuid2 *cpuid;                                                      // (17) 0.02734
/*8   */     int i, max;                                                                    // (21) 0.01562
/*10  */     uint32_t ret = 0;                                                              // (20) 0.02148
/*12  */     uint32_t cpuid_1_edx;                                                          // (16) 0.0293
/*16  */     if (!kvm_check_extension(env->kvm_state, KVM_CAP_EXT_CPUID)) {                 // (1) 0.06055
/*18  */         return -1U;                                                                // (18) 0.02344
/*20  */     }                                                                              // (23) 0.007812
/*24  */     max = 1;                                                                       // (22) 0.01367
/*26  */     while ((cpuid = try_get_cpuid(env->kvm_state, max)) == NULL) {                 // (2) 0.05469
/*28  */         max *= 2;                                                                  // (19) 0.02344
/*30  */     }                                                                              // (24) 0.007812
/*34  */     for (i = 0; i < cpuid->nent; ++i) {                                            // (8) 0.04102
/*36  */         if (cpuid->entries[i].function == function &&                              // (9) 0.04102
/*38  */             cpuid->entries[i].index == index) {                                    // (7) 0.04688
/*40  */             switch (reg) {                                                         // (15) 0.03125
/*42  */             case R_EAX:                                                            // (10) 0.0332
/*44  */                 ret = cpuid->entries[i].eax;                                       // (3) 0.05469
/*46  */                 break;                                                             // (11) 0.0332
/*48  */             case R_EBX:                                                            // (12) 0.0332
/*50  */                 ret = cpuid->entries[i].ebx;                                       // (4) 0.05469
/*52  */                 break;                                                             // (13) 0.0332
/*54  */             case R_ECX:                                                            // (14) 0.0332
/*56  */                 ret = cpuid->entries[i].ecx;                                       // (5) 0.05469
/*58  */                 break;                                                             // 0.0
/*60  */             case R_EDX:                                                            // 0.0
/*62  */                 ret = cpuid->entries[i].edx;                                       // 0.0
/*64  */                 switch (function) {                                                // 0.0
/*66  */                 case 1:                                                            // 0.0
/*68  */                     /* KVM before 2.6.30 misreports the following features */      // 0.0
/*70  */                     ret |= CPUID_MTRR | CPUID_PAT | CPUID_MCE | CPUID_MCA;         // 0.0
/*72  */                     break;                                                         // 0.0
/*74  */                 case 0x80000001:                                                   // 0.0
/*76  */                     /* On Intel, kvm returns cpuid according to the Intel spec,    // 0.0
/*78  */                      * so add missing bits according to the AMD spec:              // 0.0
/*80  */                      */                                                            // 0.0
/*82  */                     cpuid_1_edx = kvm_arch_get_supported_cpuid(env, 1, 0, R_EDX);  // 0.0
/*84  */                     ret |= cpuid_1_edx & 0x183f7ff;                                // 0.0
/*86  */                     break;                                                         // 0.0
/*88  */                 }                                                                  // 0.0
/*90  */                 break;                                                             // 0.0
/*92  */             }                                                                      // 0.0
/*94  */         }                                                                          // 0.0
/*96  */     }                                                                              // 0.0
/*100 */     qemu_free(cpuid);                                                              // 0.0
/*104 */     return ret;                                                                    // 0.0
/*106 */ }                                                                                  // 0.0
