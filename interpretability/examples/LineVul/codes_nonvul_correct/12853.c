// commit message qemu@e6eef7c221 (target=0, prob=0.065098986, correct=True): valgrind/s390x: avoid false positives on KVM_SET_FPU ioctl
/*0   */ int kvm_arch_put_registers(CPUState *cs, int level)                             // (9) 0.03711
/*2   */ {                                                                               // (27) 0.001953
/*4   */     S390CPU *cpu = S390_CPU(cs);                                                // (10) 0.03125
/*6   */     CPUS390XState *env = &cpu->env;                                             // (11) 0.03125
/*8   */     struct kvm_sregs sregs;                                                     // (14) 0.02734
/*10  */     struct kvm_regs regs;                                                       // (18) 0.02344
/*12  */     struct kvm_fpu fpu;                                                         // (17) 0.02344
/*14  */     int r;                                                                      // (23) 0.01172
/*16  */     int i;                                                                      // (24) 0.01172
/*20  */     /* always save the PSW  and the GPRS*/                                      // (12) 0.03125
/*22  */     cs->kvm_run->psw_addr = env->psw.addr;                                      // (5) 0.04297
/*24  */     cs->kvm_run->psw_mask = env->psw.mask;                                      // (6) 0.04297
/*28  */     if (cap_sync_regs && cs->kvm_run->kvm_valid_regs & KVM_SYNC_GPRS) {         // (0) 0.07422
/*30  */         for (i = 0; i < 16; i++) {                                              // (7) 0.03906
/*32  */             cs->kvm_run->s.regs.gprs[i] = env->regs[i];                         // (2) 0.07227
/*34  */             cs->kvm_run->kvm_dirty_regs |= KVM_SYNC_GPRS;                       // (1) 0.07227
/*36  */         }                                                                       // (20) 0.01562
/*38  */     } else {                                                                    // (25) 0.01172
/*40  */         for (i = 0; i < 16; i++) {                                              // (8) 0.03906
/*42  */             regs.gprs[i] = env->regs[i];                                        // (4) 0.05469
/*44  */         }                                                                       // (21) 0.01562
/*46  */         r = kvm_vcpu_ioctl(cs, KVM_SET_REGS, &regs);                            // (3) 0.0625
/*48  */         if (r < 0) {                                                            // (16) 0.02734
/*50  */             return r;                                                           // (15) 0.02734
/*52  */         }                                                                       // (19) 0.01563
/*54  */     }                                                                           // (26) 0.007813
/*58  */     /* Floating point */                                                        // (22) 0.01367
/*60  */     for (i = 0; i < 16; i++) {                                                  // (13) 0.03125
/*62  */         fpu.fprs[i] = env->fregs[i].ll;                                         // 0.0
/*64  */     }                                                                           // 0.0
/*66  */     fpu.fpc = env->fpc;                                                         // 0.0
/*70  */     r = kvm_vcpu_ioctl(cs, KVM_SET_FPU, &fpu);                                  // 0.0
/*72  */     if (r < 0) {                                                                // 0.0
/*74  */         return r;                                                               // 0.0
/*76  */     }                                                                           // 0.0
/*80  */     /* Do we need to save more than that? */                                    // 0.0
/*82  */     if (level == KVM_PUT_RUNTIME_STATE) {                                       // 0.0
/*84  */         return 0;                                                               // 0.0
/*86  */     }                                                                           // 0.0
/*90  */     /*                                                                          // 0.0
/*92  */      * These ONE_REGS are not protected by a capability. As they are only       // 0.0
/*94  */      * necessary for migration we just trace a possible error, but don't        // 0.0
/*96  */      * return with an error return code.                                        // 0.0
/*98  */      */                                                                         // 0.0
/*100 */     kvm_set_one_reg(cs, KVM_REG_S390_CPU_TIMER, &env->cputm);                   // 0.0
/*102 */     kvm_set_one_reg(cs, KVM_REG_S390_CLOCK_COMP, &env->ckc);                    // 0.0
/*104 */     kvm_set_one_reg(cs, KVM_REG_S390_TODPR, &env->todpr);                       // 0.0
/*106 */     kvm_set_one_reg(cs, KVM_REG_S390_GBEA, &env->gbea);                         // 0.0
/*108 */     kvm_set_one_reg(cs, KVM_REG_S390_PP, &env->pp);                             // 0.0
/*112 */     if (cap_async_pf) {                                                         // 0.0
/*114 */         r = kvm_set_one_reg(cs, KVM_REG_S390_PFTOKEN, &env->pfault_token);      // 0.0
/*116 */         if (r < 0) {                                                            // 0.0
/*118 */             return r;                                                           // 0.0
/*120 */         }                                                                       // 0.0
/*122 */         r = kvm_set_one_reg(cs, KVM_REG_S390_PFCOMPARE, &env->pfault_compare);  // 0.0
/*124 */         if (r < 0) {                                                            // 0.0
/*126 */             return r;                                                           // 0.0
/*128 */         }                                                                       // 0.0
/*130 */         r = kvm_set_one_reg(cs, KVM_REG_S390_PFSELECT, &env->pfault_select);    // 0.0
/*132 */         if (r < 0) {                                                            // 0.0
/*134 */             return r;                                                           // 0.0
/*136 */         }                                                                       // 0.0
/*138 */     }                                                                           // 0.0
/*142 */     if (cap_sync_regs &&                                                        // 0.0
/*144 */         cs->kvm_run->kvm_valid_regs & KVM_SYNC_ACRS &&                          // 0.0
/*146 */         cs->kvm_run->kvm_valid_regs & KVM_SYNC_CRS) {                           // 0.0
/*148 */         for (i = 0; i < 16; i++) {                                              // 0.0
/*150 */             cs->kvm_run->s.regs.acrs[i] = env->aregs[i];                        // 0.0
/*152 */             cs->kvm_run->s.regs.crs[i] = env->cregs[i];                         // 0.0
/*154 */         }                                                                       // 0.0
/*156 */         cs->kvm_run->kvm_dirty_regs |= KVM_SYNC_ACRS;                           // 0.0
/*158 */         cs->kvm_run->kvm_dirty_regs |= KVM_SYNC_CRS;                            // 0.0
/*160 */     } else {                                                                    // 0.0
/*162 */         for (i = 0; i < 16; i++) {                                              // 0.0
/*164 */             sregs.acrs[i] = env->aregs[i];                                      // 0.0
/*166 */             sregs.crs[i] = env->cregs[i];                                       // 0.0
/*168 */         }                                                                       // 0.0
/*170 */         r = kvm_vcpu_ioctl(cs, KVM_SET_SREGS, &sregs);                          // 0.0
/*172 */         if (r < 0) {                                                            // 0.0
/*174 */             return r;                                                           // 0.0
/*176 */         }                                                                       // 0.0
/*178 */     }                                                                           // 0.0
/*182 */     /* Finally the prefix */                                                    // 0.0
/*184 */     if (cap_sync_regs && cs->kvm_run->kvm_valid_regs & KVM_SYNC_PREFIX) {       // 0.0
/*186 */         cs->kvm_run->s.regs.prefix = env->psa;                                  // 0.0
/*188 */         cs->kvm_run->kvm_dirty_regs |= KVM_SYNC_PREFIX;                         // 0.0
/*190 */     } else {                                                                    // 0.0
/*192 */         /* prefix is only supported via sync regs */                            // 0.0
/*194 */     }                                                                           // 0.0
/*196 */     return 0;                                                                   // 0.0
/*198 */ }                                                                               // 0.0
