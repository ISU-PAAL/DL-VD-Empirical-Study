// commit message qemu@5c32be5baf (target=1, prob=0.29035148, correct=False): tcg/sparc: Zero extend address argument to ld/st helpers
/*0   */ static void tcg_out_qemu_ld(TCGContext *s, TCGReg data, TCGReg addr,             // (4) 0.05664
/*2   */                             TCGMemOpIdx oi, bool is_64)                          // (3) 0.08008
/*4   */ {                                                                                // (22) 0.001953
/*6   */     TCGMemOp memop = get_memop(oi);                                              // (11) 0.0332
/*8   */ #ifdef CONFIG_SOFTMMU                                                            // (20) 0.01758
/*10  */     unsigned memi = get_mmuidx(oi);                                              // (12) 0.0293
/*12  */     TCGReg addrz, param;                                                         // (18) 0.02148
/*14  */     tcg_insn_unit *func;                                                         // (15) 0.02539
/*16  */     tcg_insn_unit *label_ptr;                                                    // (13) 0.0293
/*20  */     addrz = tcg_out_tlb_load(s, addr, memi, memop,                               // (7) 0.05078
/*22  */                              offsetof(CPUTLBEntry, addr_read));                  // (2) 0.08203
/*26  */     /* The fast path is exactly one insn.  Thus we can perform the               // (9) 0.03711
/*28  */        entire TLB Hit in the (annulled) delay slot of the branch                 // (8) 0.04297
/*30  */        over the TLB Miss case.  */                                               // (14) 0.0293
/*34  */     /* beq,a,pt %[xi]cc, label0 */                                               // (10) 0.03711
/*36  */     label_ptr = s->code_ptr;                                                     // (16) 0.02539
/*38  */     tcg_out_bpcc0(s, COND_E, BPCC_A | BPCC_PT                                    // (5) 0.05469
/*40  */                   | (TARGET_LONG_BITS == 64 ? BPCC_XCC : BPCC_ICC), 0);          // (0) 0.08594
/*42  */     /* delay slot */                                                             // (21) 0.01367
/*44  */     tcg_out_ldst_rr(s, data, addrz, TCG_REG_O1,                                  // (6) 0.05469
/*46  */                     qemu_ld_opc[memop & (MO_BSWAP | MO_SSIZE)]);                 // (1) 0.08594
/*50  */     /* TLB Miss.  */                                                             // (19) 0.01953
/*54  */     param = TCG_REG_O1;                                                          // (17) 0.02539
/*56  */     if (!SPARC64 && TARGET_LONG_BITS == 64) {                                    // 0.0
/*58  */         /* Skip the high-part; we'll perform the extract in the trampoline.  */  // 0.0
/*60  */         param++;                                                                 // 0.0
/*62  */     }                                                                            // 0.0
/*64  */     tcg_out_mov(s, TCG_TYPE_REG, param++, addr);                                 // 0.0
/*68  */     /* We use the helpers to extend SB and SW data, leaving the case             // 0.0
/*70  */        of SL needing explicit extending below.  */                               // 0.0
/*72  */     if ((memop & MO_SSIZE) == MO_SL) {                                           // 0.0
/*74  */         func = qemu_ld_trampoline[memop & (MO_BSWAP | MO_SIZE)];                 // 0.0
/*76  */     } else {                                                                     // 0.0
/*78  */         func = qemu_ld_trampoline[memop & (MO_BSWAP | MO_SSIZE)];                // 0.0
/*80  */     }                                                                            // 0.0
/*82  */     tcg_debug_assert(func != NULL);                                              // 0.0
/*84  */     tcg_out_call_nodelay(s, func);                                               // 0.0
/*86  */     /* delay slot */                                                             // 0.0
/*88  */     tcg_out_movi(s, TCG_TYPE_I32, param, oi);                                    // 0.0
/*92  */     /* Recall that all of the helpers return 64-bit results.                     // 0.0
/*94  */        Which complicates things for sparcv8plus.  */                             // 0.0
/*96  */     if (SPARC64) {                                                               // 0.0
/*98  */         /* We let the helper sign-extend SB and SW, but leave SL for here.  */   // 0.0
/*100 */         if (is_64 && (memop & MO_SSIZE) == MO_SL) {                              // 0.0
/*102 */             tcg_out_arithi(s, data, TCG_REG_O0, 0, SHIFT_SRA);                   // 0.0
/*104 */         } else {                                                                 // 0.0
/*106 */             tcg_out_mov(s, TCG_TYPE_REG, data, TCG_REG_O0);                      // 0.0
/*108 */         }                                                                        // 0.0
/*110 */     } else {                                                                     // 0.0
/*112 */         if ((memop & MO_SIZE) == MO_64) {                                        // 0.0
/*114 */             tcg_out_arithi(s, TCG_REG_O0, TCG_REG_O0, 32, SHIFT_SLLX);           // 0.0
/*116 */             tcg_out_arithi(s, TCG_REG_O1, TCG_REG_O1, 0, SHIFT_SRL);             // 0.0
/*118 */             tcg_out_arith(s, data, TCG_REG_O0, TCG_REG_O1, ARITH_OR);            // 0.0
/*120 */         } else if (is_64) {                                                      // 0.0
/*122 */             /* Re-extend from 32-bit rather than reassembling when we            // 0.0
/*124 */                know the high register must be an extension.  */                  // 0.0
/*126 */             tcg_out_arithi(s, data, TCG_REG_O1, 0,                               // 0.0
/*128 */                            memop & MO_SIGN ? SHIFT_SRA : SHIFT_SRL);             // 0.0
/*130 */         } else {                                                                 // 0.0
/*132 */             tcg_out_mov(s, TCG_TYPE_I32, data, TCG_REG_O1);                      // 0.0
/*134 */         }                                                                        // 0.0
/*136 */     }                                                                            // 0.0
/*140 */     *label_ptr |= INSN_OFF19(tcg_ptr_byte_diff(s->code_ptr, label_ptr));         // 0.0
/*142 */ #else                                                                            // 0.0
/*144 */     if (SPARC64 && TARGET_LONG_BITS == 32) {                                     // 0.0
/*146 */         tcg_out_arithi(s, TCG_REG_T1, addr, 0, SHIFT_SRL);                       // 0.0
/*148 */         addr = TCG_REG_T1;                                                       // 0.0
/*150 */     }                                                                            // 0.0
/*152 */     tcg_out_ldst_rr(s, data, addr,                                               // 0.0
/*154 */                     (guest_base ? TCG_GUEST_BASE_REG : TCG_REG_G0),              // 0.0
/*156 */                     qemu_ld_opc[memop & (MO_BSWAP | MO_SSIZE)]);                 // 0.0
/*158 */ #endif /* CONFIG_SOFTMMU */                                                      // 0.0
/*160 */ }                                                                                // 0.0
