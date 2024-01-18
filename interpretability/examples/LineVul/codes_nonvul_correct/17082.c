// commit message qemu@bd79255d25 (target=0, prob=0.25891927, correct=True): translate: check cflags instead of use_icount global
/*0   */ static void handle_sys(DisasContext *s, uint32_t insn, bool isread,            // (7) 0.04492
/*2   */                        unsigned int op0, unsigned int op1, unsigned int op2,   // (5) 0.07227
/*4   */                        unsigned int crn, unsigned int crm, unsigned int rt)    // (4) 0.07227
/*6   */ {                                                                              // (19) 0.001953
/*8   */     const ARMCPRegInfo *ri;                                                    // (13) 0.02344
/*10  */     TCGv_i64 tcg_rt;                                                           // (11) 0.02734
/*14  */     ri = get_arm_cp_reginfo(s->cp_regs,                                        // (8) 0.04492
/*16  */                             ENCODE_AA64_CP_REG(CP_REG_ARM64_SYSREG_CP,         // (2) 0.09961
/*18  */                                                crn, crm, op0, op1, op2));      // (0) 0.1191
/*22  */     if (!ri) {                                                                 // (17) 0.01562
/*24  */         /* Unknown register; this might be a guest error or a QEMU             // (9) 0.04297
/*26  */          * unimplemented feature.                                              // (12) 0.02734
/*28  */          */                                                                    // (15) 0.01758
/*30  */         qemu_log_mask(LOG_UNIMP, "%s access to unsupported AArch64 "           // (6) 0.05859
/*32  */                       "system register op0:%d op1:%d crn:%d crm:%d op2:%d\n",  // (1) 0.1016
/*34  */                       isread ? "read" : "write", op0, op1, crn, crm, op2);     // (3) 0.08984
/*36  */         unallocated_encoding(s);                                               // (10) 0.03125
/*38  */         return;                                                                // (14) 0.01758
/*40  */     }                                                                          // (18) 0.007813
/*44  */     /* Check access permissions */                                             // (16) 0.01562
/*46  */     if (!cp_access_ok(s->current_el, ri, isread)) {                            // 0.0
/*48  */         unallocated_encoding(s);                                               // 0.0
/*50  */         return;                                                                // 0.0
/*52  */     }                                                                          // 0.0
/*56  */     if (ri->accessfn) {                                                        // 0.0
/*58  */         /* Emit code to perform further access permissions checks at           // 0.0
/*60  */          * runtime; this may result in an exception.                           // 0.0
/*62  */          */                                                                    // 0.0
/*64  */         TCGv_ptr tmpptr;                                                       // 0.0
/*66  */         TCGv_i32 tcg_syn;                                                      // 0.0
/*68  */         uint32_t syndrome;                                                     // 0.0
/*72  */         gen_a64_set_pc_im(s->pc - 4);                                          // 0.0
/*74  */         tmpptr = tcg_const_ptr(ri);                                            // 0.0
/*76  */         syndrome = syn_aa64_sysregtrap(op0, op1, op2, crn, crm, rt, isread);   // 0.0
/*78  */         tcg_syn = tcg_const_i32(syndrome);                                     // 0.0
/*80  */         gen_helper_access_check_cp_reg(cpu_env, tmpptr, tcg_syn);              // 0.0
/*82  */         tcg_temp_free_ptr(tmpptr);                                             // 0.0
/*84  */         tcg_temp_free_i32(tcg_syn);                                            // 0.0
/*86  */     }                                                                          // 0.0
/*90  */     /* Handle special cases first */                                           // 0.0
/*92  */     switch (ri->type & ~(ARM_CP_FLAG_MASK & ~ARM_CP_SPECIAL)) {                // 0.0
/*94  */     case ARM_CP_NOP:                                                           // 0.0
/*96  */         return;                                                                // 0.0
/*98  */     case ARM_CP_NZCV:                                                          // 0.0
/*100 */         tcg_rt = cpu_reg(s, rt);                                               // 0.0
/*102 */         if (isread) {                                                          // 0.0
/*104 */             gen_get_nzcv(tcg_rt);                                              // 0.0
/*106 */         } else {                                                               // 0.0
/*108 */             gen_set_nzcv(tcg_rt);                                              // 0.0
/*110 */         }                                                                      // 0.0
/*112 */         return;                                                                // 0.0
/*114 */     case ARM_CP_CURRENTEL:                                                     // 0.0
/*116 */         /* Reads as current EL value from pstate, which is                     // 0.0
/*118 */          * guaranteed to be constant by the tb flags.                          // 0.0
/*120 */          */                                                                    // 0.0
/*122 */         tcg_rt = cpu_reg(s, rt);                                               // 0.0
/*124 */         tcg_gen_movi_i64(tcg_rt, s->current_el << 2);                          // 0.0
/*126 */         return;                                                                // 0.0
/*128 */     case ARM_CP_DC_ZVA:                                                        // 0.0
/*130 */         /* Writes clear the aligned block of memory which rt points into. */   // 0.0
/*132 */         tcg_rt = cpu_reg(s, rt);                                               // 0.0
/*134 */         gen_helper_dc_zva(cpu_env, tcg_rt);                                    // 0.0
/*136 */         return;                                                                // 0.0
/*138 */     default:                                                                   // 0.0
/*140 */         break;                                                                 // 0.0
/*142 */     }                                                                          // 0.0
/*146 */     if (use_icount && (ri->type & ARM_CP_IO)) {                                // 0.0
/*148 */         gen_io_start();                                                        // 0.0
/*150 */     }                                                                          // 0.0
/*154 */     tcg_rt = cpu_reg(s, rt);                                                   // 0.0
/*158 */     if (isread) {                                                              // 0.0
/*160 */         if (ri->type & ARM_CP_CONST) {                                         // 0.0
/*162 */             tcg_gen_movi_i64(tcg_rt, ri->resetvalue);                          // 0.0
/*164 */         } else if (ri->readfn) {                                               // 0.0
/*166 */             TCGv_ptr tmpptr;                                                   // 0.0
/*168 */             tmpptr = tcg_const_ptr(ri);                                        // 0.0
/*170 */             gen_helper_get_cp_reg64(tcg_rt, cpu_env, tmpptr);                  // 0.0
/*172 */             tcg_temp_free_ptr(tmpptr);                                         // 0.0
/*174 */         } else {                                                               // 0.0
/*176 */             tcg_gen_ld_i64(tcg_rt, cpu_env, ri->fieldoffset);                  // 0.0
/*178 */         }                                                                      // 0.0
/*180 */     } else {                                                                   // 0.0
/*182 */         if (ri->type & ARM_CP_CONST) {                                         // 0.0
/*184 */             /* If not forbidden by access permissions, treat as WI */          // 0.0
/*186 */             return;                                                            // 0.0
/*188 */         } else if (ri->writefn) {                                              // 0.0
/*190 */             TCGv_ptr tmpptr;                                                   // 0.0
/*192 */             tmpptr = tcg_const_ptr(ri);                                        // 0.0
/*194 */             gen_helper_set_cp_reg64(cpu_env, tmpptr, tcg_rt);                  // 0.0
/*196 */             tcg_temp_free_ptr(tmpptr);                                         // 0.0
/*198 */         } else {                                                               // 0.0
/*200 */             tcg_gen_st_i64(tcg_rt, cpu_env, ri->fieldoffset);                  // 0.0
/*202 */         }                                                                      // 0.0
/*204 */     }                                                                          // 0.0
/*208 */     if (use_icount && (ri->type & ARM_CP_IO)) {                                // 0.0
/*210 */         /* I/O operations must end the TB here (whether read or write) */      // 0.0
/*212 */         gen_io_end();                                                          // 0.0
/*214 */         s->is_jmp = DISAS_UPDATE;                                              // 0.0
/*216 */     } else if (!isread && !(ri->type & ARM_CP_SUPPRESS_TB_END)) {              // 0.0
/*218 */         /* We default to ending the TB on a coprocessor register write,        // 0.0
/*220 */          * but allow this to be suppressed by the register definition          // 0.0
/*222 */          * (usually only necessary to work around guest bugs).                 // 0.0
/*224 */          */                                                                    // 0.0
/*226 */         s->is_jmp = DISAS_UPDATE;                                              // 0.0
/*228 */     }                                                                          // 0.0
/*230 */ }                                                                              // 0.0
