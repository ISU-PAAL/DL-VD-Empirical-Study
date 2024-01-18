// commit message qemu@96c9cff0ab (target=0, prob=0.25850624, correct=True): target-ppc/kvm: Add a wrapper function to check for KVM-PR
/*0   */ static void kvm_get_fallback_smmu_info(PowerPCCPU *cpu,                   // (6) 0.04492
/*2   */                                        struct kvm_ppc_smmu_info *info)    // (0) 0.1035
/*4   */ {                                                                         // (25) 0.001953
/*6   */     CPUPPCState *env = &cpu->env;                                         // (15) 0.0293
/*8   */     CPUState *cs = CPU(cpu);                                              // (19) 0.02344
/*12  */     memset(info, 0, sizeof(*info));                                       // (17) 0.02734
/*16  */     /* We don't have the new KVM_PPC_GET_SMMU_INFO ioctl, so              // (3) 0.05273
/*18  */      * need to "guess" what the supported page sizes are.                 // (12) 0.03516
/*20  */      *                                                                    // (21) 0.009766
/*22  */      * For that to work we make a few assumptions:                        // (16) 0.0293
/*24  */      *                                                                    // (22) 0.009766
/*26  */      * - If KVM_CAP_PPC_GET_PVINFO is supported we are running "PR"       // (1) 0.05469
/*28  */      *   KVM which only supports 4K and 16M pages, but supports them      // (7) 0.04297
/*30  */      *   regardless of the backing store characteritics. We also don't    // (11) 0.03906
/*32  */      *   support 1T segments.                                             // (20) 0.02344
/*34  */      *                                                                    // (23) 0.009766
/*36  */      *   This is safe as if HV KVM ever supports that capability or PR    // (8) 0.04297
/*38  */      *   KVM grows supports for more page/segment sizes, those versions   // (9) 0.04102
/*40  */      *   will have implemented KVM_CAP_PPC_GET_SMMU_INFO and thus we      // (2) 0.05469
/*42  */      *   will not hit this fallback                                       // (18) 0.02539
/*44  */      *                                                                    // (24) 0.009766
/*46  */      * - Else we are running HV KVM. This means we only support page      // (10) 0.04102
/*48  */      *   sizes that fit in the backing store. Additionally we only        // (13) 0.03516
/*50  */      *   advertize 64K pages if the processor is ARCH 2.06 and we assume  // (5) 0.04688
/*52  */      *   P7 encodings for the SLB and hash table. Here too, we assume     // (4) 0.04883
/*54  */      *   support for any newer processor will mean a kernel that          // (14) 0.0332
/*56  */      *   implements KVM_CAP_PPC_GET_SMMU_INFO and thus doesn't hit        // 0.0
/*58  */      *   this fallback.                                                   // 0.0
/*60  */      */                                                                   // 0.0
/*62  */     if (kvm_check_extension(cs->kvm_state, KVM_CAP_PPC_GET_PVINFO)) {     // 0.0
/*64  */         /* No flags */                                                    // 0.0
/*66  */         info->flags = 0;                                                  // 0.0
/*68  */         info->slb_size = 64;                                              // 0.0
/*72  */         /* Standard 4k base page size segment */                          // 0.0
/*74  */         info->sps[0].page_shift = 12;                                     // 0.0
/*76  */         info->sps[0].slb_enc = 0;                                         // 0.0
/*78  */         info->sps[0].enc[0].page_shift = 12;                              // 0.0
/*80  */         info->sps[0].enc[0].pte_enc = 0;                                  // 0.0
/*84  */         /* Standard 16M large page size segment */                        // 0.0
/*86  */         info->sps[1].page_shift = 24;                                     // 0.0
/*88  */         info->sps[1].slb_enc = SLB_VSID_L;                                // 0.0
/*90  */         info->sps[1].enc[0].page_shift = 24;                              // 0.0
/*92  */         info->sps[1].enc[0].pte_enc = 0;                                  // 0.0
/*94  */     } else {                                                              // 0.0
/*96  */         int i = 0;                                                        // 0.0
/*100 */         /* HV KVM has backing store size restrictions */                  // 0.0
/*102 */         info->flags = KVM_PPC_PAGE_SIZES_REAL;                            // 0.0
/*106 */         if (env->mmu_model & POWERPC_MMU_1TSEG) {                         // 0.0
/*108 */             info->flags |= KVM_PPC_1T_SEGMENTS;                           // 0.0
/*110 */         }                                                                 // 0.0
/*114 */         if (env->mmu_model == POWERPC_MMU_2_06 ||                         // 0.0
/*116 */             env->mmu_model == POWERPC_MMU_2_07) {                         // 0.0
/*118 */             info->slb_size = 32;                                          // 0.0
/*120 */         } else {                                                          // 0.0
/*122 */             info->slb_size = 64;                                          // 0.0
/*124 */         }                                                                 // 0.0
/*128 */         /* Standard 4k base page size segment */                          // 0.0
/*130 */         info->sps[i].page_shift = 12;                                     // 0.0
/*132 */         info->sps[i].slb_enc = 0;                                         // 0.0
/*134 */         info->sps[i].enc[0].page_shift = 12;                              // 0.0
/*136 */         info->sps[i].enc[0].pte_enc = 0;                                  // 0.0
/*138 */         i++;                                                              // 0.0
/*142 */         /* 64K on MMU 2.06 and later */                                   // 0.0
/*144 */         if (env->mmu_model == POWERPC_MMU_2_06 ||                         // 0.0
/*146 */             env->mmu_model == POWERPC_MMU_2_07) {                         // 0.0
/*148 */             info->sps[i].page_shift = 16;                                 // 0.0
/*150 */             info->sps[i].slb_enc = 0x110;                                 // 0.0
/*152 */             info->sps[i].enc[0].page_shift = 16;                          // 0.0
/*154 */             info->sps[i].enc[0].pte_enc = 1;                              // 0.0
/*156 */             i++;                                                          // 0.0
/*158 */         }                                                                 // 0.0
/*162 */         /* Standard 16M large page size segment */                        // 0.0
/*164 */         info->sps[i].page_shift = 24;                                     // 0.0
/*166 */         info->sps[i].slb_enc = SLB_VSID_L;                                // 0.0
/*168 */         info->sps[i].enc[0].page_shift = 24;                              // 0.0
/*170 */         info->sps[i].enc[0].pte_enc = 0;                                  // 0.0
/*172 */     }                                                                     // 0.0
/*174 */ }                                                                         // 0.0
