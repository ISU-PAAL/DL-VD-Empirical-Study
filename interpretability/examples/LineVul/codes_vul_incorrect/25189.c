// commit message qemu@5c32be5baf (target=1, prob=0.3267769, correct=False): tcg/sparc: Zero extend address argument to ld/st helpers
/*0   */ static void tcg_out_qemu_st(TCGContext *s, TCGReg data, TCGReg addr,             // (4) 0.05664
/*2   */                             TCGMemOpIdx oi)                                      // (3) 0.07031
/*4   */ {                                                                                // (21) 0.001953
/*6   */     TCGMemOp memop = get_memop(oi);                                              // (11) 0.0332
/*8   */ #ifdef CONFIG_SOFTMMU                                                            // (19) 0.01758
/*10  */     unsigned memi = get_mmuidx(oi);                                              // (12) 0.0293
/*12  */     TCGReg addrz, param;                                                         // (17) 0.02148
/*14  */     tcg_insn_unit *func;                                                         // (14) 0.02539
/*16  */     tcg_insn_unit *label_ptr;                                                    // (13) 0.0293
/*20  */     addrz = tcg_out_tlb_load(s, addr, memi, memop,                               // (8) 0.05078
/*22  */                              offsetof(CPUTLBEntry, addr_write));                 // (2) 0.08203
/*26  */     /* The fast path is exactly one insn.  Thus we can perform the entire        // (9) 0.03906
/*28  */        TLB Hit in the (annulled) delay slot of the branch over TLB Miss.  */     // (5) 0.05469
/*30  */     /* beq,a,pt %[xi]cc, label0 */                                               // (10) 0.03711
/*32  */     label_ptr = s->code_ptr;                                                     // (15) 0.02539
/*34  */     tcg_out_bpcc0(s, COND_E, BPCC_A | BPCC_PT                                    // (7) 0.05469
/*36  */                   | (TARGET_LONG_BITS == 64 ? BPCC_XCC : BPCC_ICC), 0);          // (0) 0.08594
/*38  */     /* delay slot */                                                             // (20) 0.01367
/*40  */     tcg_out_ldst_rr(s, data, addrz, TCG_REG_O1,                                  // (6) 0.05469
/*42  */                     qemu_st_opc[memop & (MO_BSWAP | MO_SIZE)]);                  // (1) 0.08398
/*46  */     /* TLB Miss.  */                                                             // (18) 0.01953
/*50  */     param = TCG_REG_O1;                                                          // (16) 0.02539
/*52  */     if (!SPARC64 && TARGET_LONG_BITS == 64) {                                    // 0.0
/*54  */         /* Skip the high-part; we'll perform the extract in the trampoline.  */  // 0.0
/*56  */         param++;                                                                 // 0.0
/*58  */     }                                                                            // 0.0
/*60  */     tcg_out_mov(s, TCG_TYPE_REG, param++, addr);                                 // 0.0
/*62  */     if (!SPARC64 && (memop & MO_SIZE) == MO_64) {                                // 0.0
/*64  */         /* Skip the high-part; we'll perform the extract in the trampoline.  */  // 0.0
/*66  */         param++;                                                                 // 0.0
/*68  */     }                                                                            // 0.0
/*70  */     tcg_out_mov(s, TCG_TYPE_REG, param++, data);                                 // 0.0
/*74  */     func = qemu_st_trampoline[memop & (MO_BSWAP | MO_SIZE)];                     // 0.0
/*76  */     tcg_debug_assert(func != NULL);                                              // 0.0
/*78  */     tcg_out_call_nodelay(s, func);                                               // 0.0
/*80  */     /* delay slot */                                                             // 0.0
/*82  */     tcg_out_movi(s, TCG_TYPE_I32, param, oi);                                    // 0.0
/*86  */     *label_ptr |= INSN_OFF19(tcg_ptr_byte_diff(s->code_ptr, label_ptr));         // 0.0
/*88  */ #else                                                                            // 0.0
/*90  */     if (SPARC64 && TARGET_LONG_BITS == 32) {                                     // 0.0
/*92  */         tcg_out_arithi(s, TCG_REG_T1, addr, 0, SHIFT_SRL);                       // 0.0
/*94  */         addr = TCG_REG_T1;                                                       // 0.0
/*96  */     }                                                                            // 0.0
/*98  */     tcg_out_ldst_rr(s, data, addr,                                               // 0.0
/*100 */                     (guest_base ? TCG_GUEST_BASE_REG : TCG_REG_G0),              // 0.0
/*102 */                     qemu_st_opc[memop & (MO_BSWAP | MO_SIZE)]);                  // 0.0
/*104 */ #endif /* CONFIG_SOFTMMU */                                                      // 0.0
/*106 */ }                                                                                // 0.0
