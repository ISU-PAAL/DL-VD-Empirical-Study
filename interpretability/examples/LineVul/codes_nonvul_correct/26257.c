// commit message qemu@e57ca75ce3 (target=0, prob=0.29816464, correct=True): target/ppc: Manage external HPT via virtual hypervisor
/*0   */ static int kvmppc_get_books_sregs(PowerPCCPU *cpu)                     // (7) 0.04297
/*2   */ {                                                                      // (31) 0.001953
/*4   */     CPUPPCState *env = &cpu->env;                                      // (12) 0.0293
/*6   */     struct kvm_sregs sregs;                                            // (13) 0.02734
/*8   */     int ret;                                                           // (24) 0.01172
/*10  */     int i;                                                             // (25) 0.01172
/*14  */     ret = kvm_vcpu_ioctl(CPU(cpu), KVM_GET_SREGS, &sregs);             // (3) 0.0625
/*16  */     if (ret < 0) {                                                     // (16) 0.01953
/*18  */         return ret;                                                    // (17) 0.01953
/*20  */     }                                                                  // (27) 0.007812
/*24  */     if (!env->external_htab) {                                         // (14) 0.02539
/*26  */         ppc_store_sdr1(env, sregs.u.s.sdr1);                           // (4) 0.05859
/*28  */     }                                                                  // (28) 0.007812
/*32  */     /* Sync SLB */                                                     // (20) 0.01562
/*34  */ #ifdef TARGET_PPC64                                                    // (18) 0.01758
/*36  */     /*                                                                 // (29) 0.007812
/*38  */      * The packed SLB array we get from KVM_GET_SREGS only contains    // (6) 0.04492
/*40  */      * information about valid entries. So we flush our internal copy  // (11) 0.03125
/*42  */      * to get rid of stale ones, then put all valid SLB entries back   // (8) 0.03906
/*44  */      * in.                                                             // (23) 0.01367
/*46  */      */                                                                // (26) 0.009766
/*48  */     memset(env->slb, 0, sizeof(env->slb));                             // (9) 0.03906
/*50  */     for (i = 0; i < ARRAY_SIZE(env->slb); i++) {                       // (5) 0.04688
/*52  */         target_ulong rb = sregs.u.s.ppc64.slb[i].slbe;                 // (1) 0.06641
/*54  */         target_ulong rs = sregs.u.s.ppc64.slb[i].slbv;                 // (2) 0.06641
/*56  */         /*                                                             // (21) 0.01562
/*58  */          * Only restore valid entries                                  // (15) 0.02539
/*60  */          */                                                            // (19) 0.01758
/*62  */         if (rb & SLB_ESID_V) {                                         // (10) 0.03906
/*64  */             ppc_store_slb(cpu, rb & 0xfff, rb & ~0xfffULL, rs);        // (0) 0.07617
/*66  */         }                                                              // (22) 0.01562
/*68  */     }                                                                  // (30) 0.007812
/*70  */ #endif                                                                 // 0.0
/*74  */     /* Sync SRs */                                                     // 0.0
/*76  */     for (i = 0; i < 16; i++) {                                         // 0.0
/*78  */         env->sr[i] = sregs.u.s.ppc32.sr[i];                            // 0.0
/*80  */     }                                                                  // 0.0
/*84  */     /* Sync BATs */                                                    // 0.0
/*86  */     for (i = 0; i < 8; i++) {                                          // 0.0
/*88  */         env->DBAT[0][i] = sregs.u.s.ppc32.dbat[i] & 0xffffffff;        // 0.0
/*90  */         env->DBAT[1][i] = sregs.u.s.ppc32.dbat[i] >> 32;               // 0.0
/*92  */         env->IBAT[0][i] = sregs.u.s.ppc32.ibat[i] & 0xffffffff;        // 0.0
/*94  */         env->IBAT[1][i] = sregs.u.s.ppc32.ibat[i] >> 32;               // 0.0
/*96  */     }                                                                  // 0.0
/*100 */     return 0;                                                          // 0.0
/*102 */ }                                                                      // 0.0
