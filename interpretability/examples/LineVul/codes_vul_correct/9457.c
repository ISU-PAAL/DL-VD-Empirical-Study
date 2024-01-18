// commit message qemu@c73860803f (target=1, prob=0.9990169, correct=True): target-ppc: Fix and enable fri[mnpz]
/*0  */ POWERPC_FAMILY(POWER8)(ObjectClass *oc, void *data)                      // (9) 0.04102
/*2  */ {                                                                        // (16) 0.001953
/*4  */     DeviceClass *dc = DEVICE_CLASS(oc);                                  // (14) 0.0293
/*6  */     PowerPCCPUClass *pcc = POWERPC_CPU_CLASS(oc);                        // (10) 0.04102
/*10 */     dc->fw_name = "PowerPC,POWER8";                                      // (13) 0.0332
/*12 */     dc->desc = "POWER8";                                                 // (15) 0.02344
/*14 */     pcc->pvr = CPU_POWERPC_POWER8_BASE;                                  // (8) 0.04297
/*16 */     pcc->pvr_mask = CPU_POWERPC_POWER8_MASK;                             // (7) 0.04687
/*18 */     pcc->init_proc = init_proc_POWER7;                                   // (12) 0.03516
/*20 */     pcc->check_pow = check_pow_nocheck;                                  // (11) 0.03906
/*22 */     pcc->insns_flags = PPC_INSNS_BASE | PPC_STRING | PPC_MFTB |          // (6) 0.06445
/*24 */                        PPC_FLOAT | PPC_FLOAT_FSEL | PPC_FLOAT_FRES |     // (1) 0.0957
/*26 */                        PPC_FLOAT_FSQRT | PPC_FLOAT_FRSQRTE |             // (2) 0.08984
/*28 */                        PPC_FLOAT_STFIWX |                                // (5) 0.06641
/*31 */                        PPC_CACHE | PPC_CACHE_ICBI | PPC_CACHE_DCBZ |     // (0) 0.09766
/*33 */                        PPC_MEM_SYNC | PPC_MEM_EIEIO |                    // (4) 0.08008
/*35 */                        PPC_MEM_TLBIE | PPC_MEM_TLBSYNC |                 // (3) 0.08398
/*37 */                        PPC_64B | PPC_ALTIVEC |                           // 0.0
/*39 */                        PPC_SEGMENT_64B | PPC_SLBI |                      // 0.0
/*41 */                        PPC_POPCNTB | PPC_POPCNTWD;                       // 0.0
/*43 */     pcc->insns_flags2 = PPC2_VSX | PPC2_VSX207 | PPC2_DFP | PPC2_DBRX |  // 0.0
/*45 */                         PPC2_PERM_ISA206 | PPC2_DIVE_ISA206 |            // 0.0
/*47 */                         PPC2_ATOMIC_ISA206 | PPC2_FP_CVT_ISA206;         // 0.0
/*49 */     pcc->msr_mask = 0x800000000284FF36ULL;                               // 0.0
/*51 */     pcc->mmu_model = POWERPC_MMU_2_06;                                   // 0.0
/*53 */ #if defined(CONFIG_SOFTMMU)                                              // 0.0
/*55 */     pcc->handle_mmu_fault = ppc_hash64_handle_mmu_fault;                 // 0.0
/*57 */ #endif                                                                   // 0.0
/*59 */     pcc->excp_model = POWERPC_EXCP_POWER7;                               // 0.0
/*61 */     pcc->bus_model = PPC_FLAGS_INPUT_POWER7;                             // 0.0
/*63 */     pcc->bfd_mach = bfd_mach_ppc64;                                      // 0.0
/*65 */     pcc->flags = POWERPC_FLAG_VRE | POWERPC_FLAG_SE |                    // 0.0
/*67 */                  POWERPC_FLAG_BE | POWERPC_FLAG_PMM |                    // 0.0
/*69 */                  POWERPC_FLAG_BUS_CLK | POWERPC_FLAG_CFAR |              // 0.0
/*71 */                  POWERPC_FLAG_VSX;                                       // 0.0
/*73 */     pcc->l1_dcache_size = 0x8000;                                        // 0.0
/*75 */     pcc->l1_icache_size = 0x8000;                                        // 0.0
/*77 */ }                                                                        // 0.0
