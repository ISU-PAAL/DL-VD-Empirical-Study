// commit message qemu@68d45bb61c (target=1, prob=0.31266662, correct=False): tcg/ppc: Improve unaligned load/store handling on 64-bit backend
/*0   */ static void tcg_out_qemu_ld(TCGContext *s, const TCGArg *args, bool is_64)   // (3) 0.06055
/*2   */ {                                                                            // (26) 0.001953
/*4   */     TCGReg datalo, datahi, addrlo, rbase;                                    // (8) 0.03516
/*6   */     TCGReg addrhi __attribute__((unused));                                   // (9) 0.0293
/*8   */     TCGMemOpIdx oi;                                                          // (18) 0.02344
/*10  */     TCGMemOp opc, s_bits;                                                    // (12) 0.02734
/*12  */ #ifdef CONFIG_SOFTMMU                                                        // (19) 0.01758
/*14  */     int mem_index;                                                           // (24) 0.01562
/*16  */     tcg_insn_unit *label_ptr;                                                // (10) 0.0293
/*18  */ #endif                                                                       // (25) 0.003906
/*22  */     datalo = *args++;                                                        // (20) 0.01758
/*24  */     datahi = (TCG_TARGET_REG_BITS == 32 && is_64 ? *args++ : 0);             // (4) 0.05859
/*26  */     addrlo = *args++;                                                        // (21) 0.01758
/*28  */     addrhi = (TCG_TARGET_REG_BITS < TARGET_LONG_BITS ? *args++ : 0);         // (2) 0.06445
/*30  */     oi = *args++;                                                            // (22) 0.01758
/*32  */     opc = get_memop(oi);                                                     // (15) 0.02539
/*34  */     s_bits = opc & MO_SIZE;                                                  // (13) 0.02734
/*38  */ #ifdef CONFIG_SOFTMMU                                                        // (23) 0.01758
/*40  */     mem_index = get_mmuidx(oi);                                              // (11) 0.0293
/*42  */     addrlo = tcg_out_tlb_read(s, s_bits, addrlo, addrhi, mem_index, true);   // (1) 0.06641
/*46  */     /* Load a pointer into the current opcode w/conditional branch-link. */  // (7) 0.04102
/*48  */     label_ptr = s->code_ptr;                                                 // (16) 0.02539
/*50  */     tcg_out_bc_noaddr(s, BC | BI(7, CR_EQ) | BO_COND_FALSE | LK);            // (0) 0.07617
/*54  */     rbase = TCG_REG_R3;                                                      // (14) 0.02734
/*56  */ #else  /* !CONFIG_SOFTMMU */                                                 // (17) 0.02539
/*58  */     rbase = GUEST_BASE ? TCG_GUEST_BASE_REG : 0;                             // (6) 0.04883
/*60  */     if (TCG_TARGET_REG_BITS > TARGET_LONG_BITS) {                            // (5) 0.05078
/*62  */         tcg_out_ext32u(s, TCG_REG_TMP1, addrlo);                             // 0.0
/*64  */         addrlo = TCG_REG_TMP1;                                               // 0.0
/*66  */     }                                                                        // 0.0
/*68  */ #endif                                                                       // 0.0
/*72  */     if (TCG_TARGET_REG_BITS == 32 && s_bits == MO_64) {                      // 0.0
/*74  */         if (opc & MO_BSWAP) {                                                // 0.0
/*76  */             tcg_out32(s, ADDI | TAI(TCG_REG_R0, addrlo, 4));                 // 0.0
/*78  */             tcg_out32(s, LWBRX | TAB(datalo, rbase, addrlo));                // 0.0
/*80  */             tcg_out32(s, LWBRX | TAB(datahi, rbase, TCG_REG_R0));            // 0.0
/*82  */         } else if (rbase != 0) {                                             // 0.0
/*84  */             tcg_out32(s, ADDI | TAI(TCG_REG_R0, addrlo, 4));                 // 0.0
/*86  */             tcg_out32(s, LWZX | TAB(datahi, rbase, addrlo));                 // 0.0
/*88  */             tcg_out32(s, LWZX | TAB(datalo, rbase, TCG_REG_R0));             // 0.0
/*90  */         } else if (addrlo == datahi) {                                       // 0.0
/*92  */             tcg_out32(s, LWZ | TAI(datalo, addrlo, 4));                      // 0.0
/*94  */             tcg_out32(s, LWZ | TAI(datahi, addrlo, 0));                      // 0.0
/*96  */         } else {                                                             // 0.0
/*98  */             tcg_out32(s, LWZ | TAI(datahi, addrlo, 0));                      // 0.0
/*100 */             tcg_out32(s, LWZ | TAI(datalo, addrlo, 4));                      // 0.0
/*102 */         }                                                                    // 0.0
/*104 */     } else {                                                                 // 0.0
/*106 */         uint32_t insn = qemu_ldx_opc[opc & (MO_BSWAP | MO_SSIZE)];           // 0.0
/*108 */         if (!HAVE_ISA_2_06 && insn == LDBRX) {                               // 0.0
/*110 */             tcg_out32(s, ADDI | TAI(TCG_REG_R0, addrlo, 4));                 // 0.0
/*112 */             tcg_out32(s, LWBRX | TAB(datalo, rbase, addrlo));                // 0.0
/*114 */             tcg_out32(s, LWBRX | TAB(TCG_REG_R0, rbase, TCG_REG_R0));        // 0.0
/*116 */             tcg_out_rld(s, RLDIMI, datalo, TCG_REG_R0, 32, 0);               // 0.0
/*118 */         } else if (insn) {                                                   // 0.0
/*120 */             tcg_out32(s, insn | TAB(datalo, rbase, addrlo));                 // 0.0
/*122 */         } else {                                                             // 0.0
/*124 */             insn = qemu_ldx_opc[opc & (MO_SIZE | MO_BSWAP)];                 // 0.0
/*126 */             tcg_out32(s, insn | TAB(datalo, rbase, addrlo));                 // 0.0
/*128 */             insn = qemu_exts_opc[s_bits];                                    // 0.0
/*130 */             tcg_out32(s, insn | RA(datalo) | RS(datalo));                    // 0.0
/*132 */         }                                                                    // 0.0
/*134 */     }                                                                        // 0.0
/*138 */ #ifdef CONFIG_SOFTMMU                                                        // 0.0
/*140 */     add_qemu_ldst_label(s, true, oi, datalo, datahi, addrlo, addrhi,         // 0.0
/*142 */                         s->code_ptr, label_ptr);                             // 0.0
/*144 */ #endif                                                                       // 0.0
/*146 */ }                                                                            // 0.0
