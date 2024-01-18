// commit message qemu@c88305027d (target=1, prob=0.08575746, correct=False): target/ppc: Change tlbie invalid fields for POWER9 support
/*0   */ POWERPC_FAMILY(POWER9)(ObjectClass *oc, void *data)                             // (8) 0.04102
/*2   */ {                                                                               // (18) 0.001953
/*4   */     DeviceClass *dc = DEVICE_CLASS(oc);                                         // (15) 0.0293
/*6   */     PowerPCCPUClass *pcc = POWERPC_CPU_CLASS(oc);                               // (9) 0.04102
/*8   */     CPUClass *cc = CPU_CLASS(oc);                                               // (16) 0.02734
/*12  */     dc->fw_name = "PowerPC,POWER9";                                             // (13) 0.0332
/*14  */     dc->desc = "POWER9";                                                        // (17) 0.02344
/*16  */     dc->props = powerpc_servercpu_properties;                                   // (14) 0.03125
/*18  */     pcc->pvr_match = ppc_pvr_match_power9;                                      // (7) 0.04297
/*20  */     pcc->pcr_mask = PCR_COMPAT_2_05 | PCR_COMPAT_2_06 | PCR_COMPAT_2_07;        // (2) 0.08008
/*22  */     pcc->pcr_supported = PCR_COMPAT_3_00 | PCR_COMPAT_2_07 | PCR_COMPAT_2_06 |  // (3) 0.08008
/*24  */                          PCR_COMPAT_2_05;                                       // (6) 0.06641
/*26  */     pcc->init_proc = init_proc_POWER9;                                          // (12) 0.03516
/*28  */     pcc->check_pow = check_pow_nocheck;                                         // (10) 0.03906
/*30  */     cc->has_work = cpu_has_work_POWER9;                                         // (11) 0.03711
/*32  */     pcc->insns_flags = PPC_INSNS_BASE | PPC_ISEL | PPC_STRING | PPC_MFTB |      // (4) 0.07617
/*34  */                        PPC_FLOAT | PPC_FLOAT_FSEL | PPC_FLOAT_FRES |            // (0) 0.0957
/*36  */                        PPC_FLOAT_FSQRT | PPC_FLOAT_FRSQRTE |                    // (1) 0.08984
/*38  */                        PPC_FLOAT_FRSQRTES |                                     // (5) 0.06836
/*40  */                        PPC_FLOAT_STFIWX |                                       // 0.0
/*42  */                        PPC_FLOAT_EXT |                                          // 0.0
/*44  */                        PPC_CACHE | PPC_CACHE_ICBI | PPC_CACHE_DCBZ |            // 0.0
/*46  */                        PPC_MEM_SYNC | PPC_MEM_EIEIO |                           // 0.0
/*48  */                        PPC_MEM_TLBIE | PPC_MEM_TLBSYNC |                        // 0.0
/*50  */                        PPC_64B | PPC_64BX | PPC_ALTIVEC |                       // 0.0
/*52  */                        PPC_SEGMENT_64B | PPC_SLBI |                             // 0.0
/*54  */                        PPC_POPCNTB | PPC_POPCNTWD |                             // 0.0
/*56  */                        PPC_CILDST;                                              // 0.0
/*58  */     pcc->insns_flags2 = PPC2_VSX | PPC2_VSX207 | PPC2_DFP | PPC2_DBRX |         // 0.0
/*60  */                         PPC2_PERM_ISA206 | PPC2_DIVE_ISA206 |                   // 0.0
/*62  */                         PPC2_ATOMIC_ISA206 | PPC2_FP_CVT_ISA206 |               // 0.0
/*64  */                         PPC2_FP_TST_ISA206 | PPC2_BCTAR_ISA207 |                // 0.0
/*66  */                         PPC2_LSQ_ISA207 | PPC2_ALTIVEC_207 |                    // 0.0
/*68  */                         PPC2_ISA205 | PPC2_ISA207S | PPC2_FP_CVT_S64 |          // 0.0
/*70  */                         PPC2_TM | PPC2_PM_ISA206 | PPC2_ISA300;                 // 0.0
/*72  */     pcc->msr_mask = (1ull << MSR_SF) |                                          // 0.0
/*74  */                     (1ull << MSR_TM) |                                          // 0.0
/*76  */                     (1ull << MSR_VR) |                                          // 0.0
/*78  */                     (1ull << MSR_VSX) |                                         // 0.0
/*80  */                     (1ull << MSR_EE) |                                          // 0.0
/*82  */                     (1ull << MSR_PR) |                                          // 0.0
/*84  */                     (1ull << MSR_FP) |                                          // 0.0
/*86  */                     (1ull << MSR_ME) |                                          // 0.0
/*88  */                     (1ull << MSR_FE0) |                                         // 0.0
/*90  */                     (1ull << MSR_SE) |                                          // 0.0
/*92  */                     (1ull << MSR_DE) |                                          // 0.0
/*94  */                     (1ull << MSR_FE1) |                                         // 0.0
/*96  */                     (1ull << MSR_IR) |                                          // 0.0
/*98  */                     (1ull << MSR_DR) |                                          // 0.0
/*100 */                     (1ull << MSR_PMM) |                                         // 0.0
/*102 */                     (1ull << MSR_RI) |                                          // 0.0
/*104 */                     (1ull << MSR_LE);                                           // 0.0
/*106 */     pcc->mmu_model = POWERPC_MMU_3_00;                                          // 0.0
/*108 */ #if defined(CONFIG_SOFTMMU)                                                     // 0.0
/*110 */     pcc->handle_mmu_fault = ppc64_v3_handle_mmu_fault;                          // 0.0
/*112 */     /* segment page size remain the same */                                     // 0.0
/*114 */     pcc->sps = &POWER7_POWER8_sps;                                              // 0.0
/*116 */     pcc->radix_page_info = &POWER9_radix_page_info;                             // 0.0
/*118 */ #endif                                                                          // 0.0
/*120 */     pcc->excp_model = POWERPC_EXCP_POWER8;                                      // 0.0
/*122 */     pcc->bus_model = PPC_FLAGS_INPUT_POWER7;                                    // 0.0
/*124 */     pcc->bfd_mach = bfd_mach_ppc64;                                             // 0.0
/*126 */     pcc->flags = POWERPC_FLAG_VRE | POWERPC_FLAG_SE |                           // 0.0
/*128 */                  POWERPC_FLAG_BE | POWERPC_FLAG_PMM |                           // 0.0
/*130 */                  POWERPC_FLAG_BUS_CLK | POWERPC_FLAG_CFAR |                     // 0.0
/*132 */                  POWERPC_FLAG_VSX | POWERPC_FLAG_TM;                            // 0.0
/*134 */     pcc->l1_dcache_size = 0x8000;                                               // 0.0
/*136 */     pcc->l1_icache_size = 0x8000;                                               // 0.0
/*138 */     pcc->interrupts_big_endian = ppc_cpu_interrupts_big_endian_lpcr;            // 0.0
/*140 */ }                                                                               // 0.0
