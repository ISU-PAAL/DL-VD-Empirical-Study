// commit message qemu@860643bc5a (target=0, prob=0.071255, correct=True): s390x/kvm: rework KVM synchronize to tracing for some ONEREGS
/*0   */ int kvm_arch_get_registers(CPUState *cs)                                   // (9) 0.03125
/*2   */ {                                                                          // (27) 0.001953
/*4   */     S390CPU *cpu = S390_CPU(cs);                                           // (10) 0.03125
/*6   */     CPUS390XState *env = &cpu->env;                                        // (11) 0.03125
/*8   */     struct kvm_one_reg reg;                                                // (15) 0.02344
/*10  */     struct kvm_sregs sregs;                                                // (12) 0.02734
/*12  */     struct kvm_regs regs;                                                  // (16) 0.02344
/*14  */     int i, r;                                                              // (21) 0.01562
/*18  */     /* get the PSW */                                                      // (19) 0.01758
/*20  */     env->psw.addr = cs->kvm_run->psw_addr;                                 // (6) 0.04297
/*22  */     env->psw.mask = cs->kvm_run->psw_mask;                                 // (5) 0.04297
/*26  */     /* the GPRS */                                                         // (20) 0.01758
/*28  */     if (cap_sync_regs && cs->kvm_run->kvm_valid_regs & KVM_SYNC_GPRS) {    // (0) 0.07422
/*30  */         for (i = 0; i < 16; i++) {                                         // (8) 0.03906
/*32  */             env->regs[i] = cs->kvm_run->s.regs.gprs[i];                    // (1) 0.07227
/*34  */         }                                                                  // (23) 0.01562
/*36  */     } else {                                                               // (25) 0.01172
/*38  */         r = kvm_vcpu_ioctl(cs, KVM_GET_REGS, &regs);                       // (2) 0.0625
/*40  */         if (r < 0) {                                                       // (13) 0.02734
/*42  */             return r;                                                      // (14) 0.02734
/*44  */         }                                                                  // (24) 0.01562
/*46  */          for (i = 0; i < 16; i++) {                                        // (7) 0.04102
/*48  */             env->regs[i] = regs.gprs[i];                                   // (4) 0.05469
/*50  */         }                                                                  // (22) 0.01562
/*52  */     }                                                                      // (26) 0.007812
/*56  */     /* The ACRS and CRS */                                                 // (18) 0.02148
/*58  */     if (cap_sync_regs &&                                                   // (17) 0.02344
/*60  */         cs->kvm_run->kvm_valid_regs & KVM_SYNC_ACRS &&                     // (3) 0.06055
/*62  */         cs->kvm_run->kvm_valid_regs & KVM_SYNC_CRS) {                      // 0.0
/*64  */         for (i = 0; i < 16; i++) {                                         // 0.0
/*66  */             env->aregs[i] = cs->kvm_run->s.regs.acrs[i];                   // 0.0
/*68  */             env->cregs[i] = cs->kvm_run->s.regs.crs[i];                    // 0.0
/*70  */         }                                                                  // 0.0
/*72  */     } else {                                                               // 0.0
/*74  */         r = kvm_vcpu_ioctl(cs, KVM_GET_SREGS, &sregs);                     // 0.0
/*76  */         if (r < 0) {                                                       // 0.0
/*78  */             return r;                                                      // 0.0
/*80  */         }                                                                  // 0.0
/*82  */          for (i = 0; i < 16; i++) {                                        // 0.0
/*84  */             env->aregs[i] = sregs.acrs[i];                                 // 0.0
/*86  */             env->cregs[i] = sregs.crs[i];                                  // 0.0
/*88  */         }                                                                  // 0.0
/*90  */     }                                                                      // 0.0
/*94  */     /* The prefix */                                                       // 0.0
/*96  */     if (cap_sync_regs && cs->kvm_run->kvm_valid_regs & KVM_SYNC_PREFIX) {  // 0.0
/*98  */         env->psa = cs->kvm_run->s.regs.prefix;                             // 0.0
/*100 */     }                                                                      // 0.0
/*104 */     /* One Regs */                                                         // 0.0
/*106 */     reg.id = KVM_REG_S390_CPU_TIMER;                                       // 0.0
/*108 */     reg.addr = (__u64)&(env->cputm);                                       // 0.0
/*110 */     r = kvm_vcpu_ioctl(cs, KVM_GET_ONE_REG, &reg);                         // 0.0
/*112 */     if (r < 0) {                                                           // 0.0
/*114 */         return r;                                                          // 0.0
/*116 */     }                                                                      // 0.0
/*120 */     reg.id = KVM_REG_S390_CLOCK_COMP;                                      // 0.0
/*122 */     reg.addr = (__u64)&(env->ckc);                                         // 0.0
/*124 */     r = kvm_vcpu_ioctl(cs, KVM_GET_ONE_REG, &reg);                         // 0.0
/*126 */     if (r < 0) {                                                           // 0.0
/*128 */         return r;                                                          // 0.0
/*130 */     }                                                                      // 0.0
/*134 */     reg.id = KVM_REG_S390_TODPR;                                           // 0.0
/*136 */     reg.addr = (__u64)&(env->todpr);                                       // 0.0
/*138 */     r = kvm_vcpu_ioctl(cs, KVM_GET_ONE_REG, &reg);                         // 0.0
/*140 */     if (r < 0) {                                                           // 0.0
/*142 */         return r;                                                          // 0.0
/*144 */     }                                                                      // 0.0
/*148 */     if (cap_async_pf) {                                                    // 0.0
/*150 */         reg.id = KVM_REG_S390_PFTOKEN;                                     // 0.0
/*152 */         reg.addr = (__u64)&(env->pfault_token);                            // 0.0
/*154 */         r = kvm_vcpu_ioctl(cs, KVM_GET_ONE_REG, &reg);                     // 0.0
/*156 */         if (r < 0) {                                                       // 0.0
/*158 */             return r;                                                      // 0.0
/*160 */         }                                                                  // 0.0
/*164 */         reg.id = KVM_REG_S390_PFCOMPARE;                                   // 0.0
/*166 */         reg.addr = (__u64)&(env->pfault_compare);                          // 0.0
/*168 */         r = kvm_vcpu_ioctl(cs, KVM_GET_ONE_REG, &reg);                     // 0.0
/*170 */         if (r < 0) {                                                       // 0.0
/*172 */             return r;                                                      // 0.0
/*174 */         }                                                                  // 0.0
/*178 */         reg.id = KVM_REG_S390_PFSELECT;                                    // 0.0
/*180 */         reg.addr = (__u64)&(env->pfault_select);                           // 0.0
/*182 */         r = kvm_vcpu_ioctl(cs, KVM_GET_ONE_REG, &reg);                     // 0.0
/*184 */         if (r < 0) {                                                       // 0.0
/*186 */             return r;                                                      // 0.0
/*188 */         }                                                                  // 0.0
/*190 */     }                                                                      // 0.0
/*194 */     return 0;                                                              // 0.0
/*196 */ }                                                                          // 0.0
