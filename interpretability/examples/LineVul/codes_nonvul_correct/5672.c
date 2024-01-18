// commit message qemu@c878da3b27 (target=0, prob=0.09604081, correct=True): tcg/ppc32: Use trampolines to trim the code size for mmu slow path accessors
/*0   */ static void tcg_out_qemu_ld_slow_path (TCGContext *s, TCGLabelQemuLdst *label)  // (0) 0.06836
/*2   */ {                                                                               // (28) 0.001953
/*4   */     int s_bits;                                                                 // (19) 0.01562
/*6   */     int ir;                                                                     // (24) 0.01172
/*8   */     int opc = label->opc;                                                       // (16) 0.02344
/*10  */     int mem_index = label->mem_index;                                           // (15) 0.02734
/*12  */     int data_reg = label->datalo_reg;                                           // (12) 0.0293
/*14  */     int data_reg2 = label->datahi_reg;                                          // (10) 0.03125
/*16  */     int addr_reg = label->addrlo_reg;                                           // (13) 0.0293
/*18  */     uint8_t *raddr = label->raddr;                                              // (11) 0.03125
/*20  */     uint8_t **label_ptr = &label->label_ptr[0];                                 // (8) 0.04102
/*24  */     s_bits = opc & 3;                                                           // (17) 0.02344
/*28  */     /* resolve label address */                                                 // (20) 0.01562
/*30  */     reloc_pc14 (label_ptr[0], (tcg_target_long) s->code_ptr);                   // (4) 0.05664
/*34  */     /* slow path */                                                             // (22) 0.01367
/*36  */     ir = 3;                                                                     // (23) 0.01367
/*38  */     tcg_out_mov (s, TCG_TYPE_I32, ir++, TCG_AREG0);                             // (2) 0.06055
/*40  */ #if TARGET_LONG_BITS == 32                                                      // (18) 0.02344
/*42  */     tcg_out_mov (s, TCG_TYPE_I32, ir++, addr_reg);                              // (5) 0.05469
/*44  */ #else                                                                           // (25) 0.003906
/*46  */ #ifdef TCG_TARGET_CALL_ALIGN_ARGS                                               // (9) 0.0332
/*48  */     ir |= 1;                                                                    // (21) 0.01562
/*50  */ #endif                                                                          // (26) 0.003906
/*52  */     tcg_out_mov (s, TCG_TYPE_I32, ir++, label->addrhi_reg);                     // (3) 0.06055
/*54  */     tcg_out_mov (s, TCG_TYPE_I32, ir++, addr_reg);                              // (6) 0.05469
/*56  */ #endif                                                                          // (27) 0.003906
/*58  */     tcg_out_movi (s, TCG_TYPE_I32, ir, mem_index);                              // (7) 0.05273
/*60  */     tcg_out_call (s, (tcg_target_long) qemu_ld_helpers[s_bits], 1);             // (1) 0.06836
/*62  */     tcg_out32 (s, B | 8);                                                       // (14) 0.0293
/*64  */     tcg_out32 (s, (tcg_target_long) raddr);                                     // 0.0
/*66  */     switch (opc) {                                                              // 0.0
/*68  */     case 0|4:                                                                   // 0.0
/*70  */         tcg_out32 (s, EXTSB | RA (data_reg) | RS (3));                          // 0.0
/*72  */         break;                                                                  // 0.0
/*74  */     case 1|4:                                                                   // 0.0
/*76  */         tcg_out32 (s, EXTSH | RA (data_reg) | RS (3));                          // 0.0
/*78  */         break;                                                                  // 0.0
/*80  */     case 0:                                                                     // 0.0
/*82  */     case 1:                                                                     // 0.0
/*84  */     case 2:                                                                     // 0.0
/*86  */         if (data_reg != 3)                                                      // 0.0
/*88  */             tcg_out_mov (s, TCG_TYPE_I32, data_reg, 3);                         // 0.0
/*90  */         break;                                                                  // 0.0
/*92  */     case 3:                                                                     // 0.0
/*94  */         if (data_reg == 3) {                                                    // 0.0
/*96  */             if (data_reg2 == 4) {                                               // 0.0
/*98  */                 tcg_out_mov (s, TCG_TYPE_I32, 0, 4);                            // 0.0
/*100 */                 tcg_out_mov (s, TCG_TYPE_I32, 4, 3);                            // 0.0
/*102 */                 tcg_out_mov (s, TCG_TYPE_I32, 3, 0);                            // 0.0
/*104 */             }                                                                   // 0.0
/*106 */             else {                                                              // 0.0
/*108 */                 tcg_out_mov (s, TCG_TYPE_I32, data_reg2, 3);                    // 0.0
/*110 */                 tcg_out_mov (s, TCG_TYPE_I32, 3, 4);                            // 0.0
/*112 */             }                                                                   // 0.0
/*114 */         }                                                                       // 0.0
/*116 */         else {                                                                  // 0.0
/*118 */             if (data_reg != 4) tcg_out_mov (s, TCG_TYPE_I32, data_reg, 4);      // 0.0
/*120 */             if (data_reg2 != 3) tcg_out_mov (s, TCG_TYPE_I32, data_reg2, 3);    // 0.0
/*122 */         }                                                                       // 0.0
/*124 */         break;                                                                  // 0.0
/*126 */     }                                                                           // 0.0
/*128 */     /* Jump to the code corresponding to next IR of qemu_st */                  // 0.0
/*130 */     tcg_out_b (s, 0, (tcg_target_long) raddr);                                  // 0.0
/*132 */ }                                                                               // 0.0
