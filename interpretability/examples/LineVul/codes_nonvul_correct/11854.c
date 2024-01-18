// commit message qemu@9658e4c342 (target=0, prob=0.22232854, correct=True): target/mips: Weaken TLB flush on UX,SX,KX,ASID changes
/*0  */ void helper_mtc0_entryhi(CPUMIPSState *env, target_ulong arg1)         // (5) 0.04688
/*2  */ {                                                                      // (26) 0.001953
/*4  */     target_ulong old, val, mask;                                       // (15) 0.02539
/*6  */     mask = (TARGET_PAGE_MASK << 1) | env->CP0_EntryHi_ASID_mask;       // (2) 0.06055
/*8  */     if (((env->CP0_Config4 >> CP0C4_IE) & 0x3) >= 2) {                 // (3) 0.05859
/*10 */         mask |= 1 << CP0EnHi_EHINV;                                    // (12) 0.04102
/*12 */     }                                                                  // (22) 0.007812
/*16 */     /* 1k pages not implemented */                                     // (20) 0.01953
/*18 */ #if defined(TARGET_MIPS64)                                             // (19) 0.02148
/*20 */     if (env->insn_flags & ISA_MIPS32R6) {                              // (11) 0.04297
/*22 */         int entryhi_r = extract64(arg1, 62, 2);                        // (9) 0.04492
/*24 */         int config0_at = extract32(env->CP0_Config0, 13, 2);           // (4) 0.05469
/*26 */         bool no_supervisor = (env->CP0_Status_rw_bitmask & 0x8) == 0;  // (0) 0.06445
/*28 */         if ((entryhi_r == 2) ||                                        // (14) 0.0332
/*30 */             (entryhi_r == 1 && (no_supervisor || config0_at == 1))) {  // (1) 0.06445
/*32 */             /* skip EntryHi.R field if new value is reserved */        // (6) 0.04688
/*34 */             mask &= ~(0x3ull << 62);                                   // (10) 0.04492
/*36 */         }                                                              // (21) 0.01562
/*38 */     }                                                                  // (23) 0.007812
/*40 */     mask &= env->SEGMask;                                              // (18) 0.02344
/*42 */ #endif                                                                 // (25) 0.003906
/*44 */     old = env->CP0_EntryHi;                                            // (16) 0.02539
/*46 */     val = (arg1 & mask) | (old & ~mask);                               // (13) 0.03516
/*48 */     env->CP0_EntryHi = val;                                            // (17) 0.02539
/*50 */     if (env->CP0_Config3 & (1 << CP0C3_MT)) {                          // (7) 0.04688
/*52 */         sync_c0_entryhi(env, env->current_tc);                         // (8) 0.04492
/*54 */     }                                                                  // (24) 0.007812
/*56 */     /* If the ASID changes, flush qemu's TLB.  */                      // 0.0
/*58 */     if ((old & env->CP0_EntryHi_ASID_mask) !=                          // 0.0
/*60 */         (val & env->CP0_EntryHi_ASID_mask)) {                          // 0.0
/*62 */         cpu_mips_tlb_flush(env);                                       // 0.0
/*64 */     }                                                                  // 0.0
/*66 */ }                                                                      // 0.0
