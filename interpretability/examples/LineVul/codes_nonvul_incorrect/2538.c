// commit message qemu@cc68890166 (target=0, prob=0.51965904, correct=False): target-arm: Don't decode old cp15 WFI instructions on v7 cores
/*0   */ static int disas_cp15_insn(CPUState *env, DisasContext *s, uint32_t insn)      // (0) 0.05664
/*2   */ {                                                                              // (32) 0.001953
/*4   */     uint32_t rd;                                                               // (20) 0.01953
/*6   */     TCGv tmp, tmp2;                                                            // (18) 0.02148
/*10  */     /* M profile cores use memory mapped registers instead of cp15.  */        // (8) 0.03516
/*12  */     if (arm_feature(env, ARM_FEATURE_M))                                       // (9) 0.03516
/*14  */ 	return 1;                                                                     // (27) 0.007812
/*18  */     if ((insn & (1 << 25)) == 0) {                                             // (11) 0.0332
/*20  */         if (insn & (1 << 20)) {                                                // (10) 0.03516
/*22  */             /* mrrc */                                                         // (14) 0.03125
/*24  */             return 1;                                                          // (17) 0.02734
/*26  */         }                                                                      // (26) 0.01562
/*28  */         /* mcrr.  Used for block cache operations, so implement as no-op.  */  // (2) 0.05469
/*30  */         return 0;                                                              // (21) 0.01953
/*32  */     }                                                                          // (28) 0.007812
/*34  */     if ((insn & (1 << 4)) == 0) {                                              // (12) 0.0332
/*36  */         /* cdp */                                                              // (19) 0.02148
/*38  */         return 1;                                                              // (22) 0.01953
/*40  */     }                                                                          // (29) 0.007812
/*42  */     if (IS_USER(s) && !cp15_user_ok(insn)) {                                   // (4) 0.04688
/*44  */         return 1;                                                              // (23) 0.01953
/*46  */     }                                                                          // (30) 0.007812
/*48  */     if ((insn & 0x0fff0fff) == 0x0e070f90                                      // (5) 0.04492
/*50  */         || (insn & 0x0fff0fff) == 0x0e070f58) {                                // (1) 0.05664
/*52  */         /* Wait for interrupt.  */                                             // (16) 0.02734
/*54  */         gen_set_pc_im(s->pc);                                                  // (7) 0.03711
/*56  */         s->is_jmp = DISAS_WFI;                                                 // (6) 0.03906
/*58  */         return 0;                                                              // (24) 0.01953
/*60  */     }                                                                          // (31) 0.007812
/*62  */     rd = (insn >> 12) & 0xf;                                                   // (15) 0.03125
/*66  */     if (cp15_tls_load_store(env, s, insn, rd))                                 // (3) 0.04883
/*68  */         return 0;                                                              // (25) 0.01953
/*72  */     tmp2 = tcg_const_i32(insn);                                                // (13) 0.0332
/*74  */     if (insn & ARM_CP_RW_BIT) {                                                // 0.0
/*76  */         tmp = new_tmp();                                                       // 0.0
/*78  */         gen_helper_get_cp15(tmp, cpu_env, tmp2);                               // 0.0
/*80  */         /* If the destination register is r15 then sets condition codes.  */   // 0.0
/*82  */         if (rd != 15)                                                          // 0.0
/*84  */             store_reg(s, rd, tmp);                                             // 0.0
/*86  */         else                                                                   // 0.0
/*88  */             dead_tmp(tmp);                                                     // 0.0
/*90  */     } else {                                                                   // 0.0
/*92  */         tmp = load_reg(s, rd);                                                 // 0.0
/*94  */         gen_helper_set_cp15(cpu_env, tmp2, tmp);                               // 0.0
/*96  */         dead_tmp(tmp);                                                         // 0.0
/*98  */         /* Normally we would always end the TB here, but Linux                 // 0.0
/*100 */          * arch/arm/mach-pxa/sleep.S expects two instructions following        // 0.0
/*102 */          * an MMU enable to execute from cache.  Imitate this behaviour.  */   // 0.0
/*104 */         if (!arm_feature(env, ARM_FEATURE_XSCALE) ||                           // 0.0
/*106 */                 (insn & 0x0fff0fff) != 0x0e010f10)                             // 0.0
/*108 */             gen_lookup_tb(s);                                                  // 0.0
/*110 */     }                                                                          // 0.0
/*112 */     tcg_temp_free_i32(tmp2);                                                   // 0.0
/*114 */     return 0;                                                                  // 0.0
/*116 */ }                                                                              // 0.0
