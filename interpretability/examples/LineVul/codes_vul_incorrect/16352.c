// commit message qemu@cca1af8c4d (target=1, prob=0.080214694, correct=False): tcg/mips: fix crash in tcg_out_qemu_ld()
/*0   */ static void tcg_out_qemu_ld(TCGContext *s, const TCGArg *args,                                       // (1) 0.05078
/*2   */                             int opc)                                                                 // (0) 0.06055
/*4   */ {                                                                                                    // (36) 0.001953
/*6   */     int addr_regl, addr_reg1, addr_meml;                                                             // (3) 0.03711
/*8   */     int data_regl, data_regh, data_reg1, data_reg2;                                                  // (2) 0.04687
/*10  */     int mem_index, s_bits;                                                                           // (17) 0.02344
/*12  */ #if defined(CONFIG_SOFTMMU)                                                                          // (18) 0.02344
/*14  */     void *label1_ptr, *label2_ptr;                                                                   // (11) 0.03125
/*16  */     int sp_args;                                                                                     // (27) 0.01562
/*18  */ #endif                                                                                               // (30) 0.003906
/*20  */ #if TARGET_LONG_BITS == 64                                                                           // (15) 0.02344
/*22  */ # if defined(CONFIG_SOFTMMU)                                                                         // (19) 0.02344
/*24  */     uint8_t *label3_ptr;                                                                             // (14) 0.02539
/*26  */ # endif                                                                                              // (32) 0.003906
/*28  */     int addr_regh, addr_reg2, addr_memh;                                                             // (4) 0.03711
/*30  */ #endif                                                                                               // (31) 0.003906
/*32  */     data_regl = *args++;                                                                             // (22) 0.02148
/*34  */     if (opc == 3)                                                                                    // (25) 0.01953
/*36  */         data_regh = *args++;                                                                         // (12) 0.0293
/*38  */     else                                                                                             // (29) 0.007812
/*40  */         data_regh = 0;                                                                               // (13) 0.02734
/*42  */     addr_regl = *args++;                                                                             // (23) 0.02148
/*44  */ #if TARGET_LONG_BITS == 64                                                                           // (20) 0.02344
/*46  */     addr_regh = *args++;                                                                             // (24) 0.02148
/*48  */ #endif                                                                                               // (33) 0.003906
/*50  */     mem_index = *args;                                                                               // (26) 0.01953
/*52  */     s_bits = opc & 3;                                                                                // (16) 0.02344
/*56  */     if (opc == 3) {                                                                                  // (21) 0.02148
/*58  */ #if defined(TCG_TARGET_WORDS_BIGENDIAN)                                                              // (5) 0.03516
/*60  */         data_reg1 = data_regh;                                                                       // (6) 0.0332
/*62  */         data_reg2 = data_regl;                                                                       // (7) 0.0332
/*64  */ #else                                                                                                // (34) 0.003906
/*66  */         data_reg1 = data_regl;                                                                       // (8) 0.0332
/*68  */         data_reg2 = data_regh;                                                                       // (9) 0.0332
/*70  */ #endif                                                                                               // (35) 0.003906
/*72  */     } else {                                                                                         // (28) 0.01172
/*74  */         data_reg1 = data_regl;                                                                       // (10) 0.0332
/*76  */         data_reg2 = 0;                                                                               // 0.0
/*78  */     }                                                                                                // 0.0
/*80  */ #if TARGET_LONG_BITS == 64                                                                           // 0.0
/*82  */ # if defined(TCG_TARGET_WORDS_BIGENDIAN)                                                             // 0.0
/*84  */     addr_reg1 = addr_regh;                                                                           // 0.0
/*86  */     addr_reg2 = addr_regl;                                                                           // 0.0
/*88  */     addr_memh = 0;                                                                                   // 0.0
/*90  */     addr_meml = 4;                                                                                   // 0.0
/*92  */ # else                                                                                               // 0.0
/*94  */     addr_reg1 = addr_regl;                                                                           // 0.0
/*96  */     addr_reg2 = addr_regh;                                                                           // 0.0
/*98  */     addr_memh = 4;                                                                                   // 0.0
/*100 */     addr_meml = 0;                                                                                   // 0.0
/*102 */ # endif                                                                                              // 0.0
/*104 */ #else                                                                                                // 0.0
/*106 */     addr_reg1 = addr_regl;                                                                           // 0.0
/*108 */     addr_meml = 0;                                                                                   // 0.0
/*110 */ #endif                                                                                               // 0.0
/*114 */ #if defined(CONFIG_SOFTMMU)                                                                          // 0.0
/*116 */     tcg_out_opc_sa(s, OPC_SRL, TCG_REG_A0, addr_regl, TARGET_PAGE_BITS - CPU_TLB_ENTRY_BITS);        // 0.0
/*118 */     tcg_out_opc_imm(s, OPC_ANDI, TCG_REG_A0, TCG_REG_A0, (CPU_TLB_SIZE - 1) << CPU_TLB_ENTRY_BITS);  // 0.0
/*120 */     tcg_out_opc_reg(s, OPC_ADDU, TCG_REG_A0, TCG_REG_A0, TCG_AREG0);                                 // 0.0
/*122 */     tcg_out_opc_imm(s, OPC_LW, TCG_REG_AT, TCG_REG_A0,                                               // 0.0
/*124 */                     offsetof(CPUState, tlb_table[mem_index][0].addr_read) + addr_meml);              // 0.0
/*126 */     tcg_out_movi(s, TCG_TYPE_I32, TCG_REG_T0, TARGET_PAGE_MASK | ((1 << s_bits) - 1));               // 0.0
/*128 */     tcg_out_opc_reg(s, OPC_AND, TCG_REG_T0, TCG_REG_T0, addr_regl);                                  // 0.0
/*132 */ # if TARGET_LONG_BITS == 64                                                                          // 0.0
/*134 */     label3_ptr = s->code_ptr;                                                                        // 0.0
/*136 */     tcg_out_opc_imm(s, OPC_BNE, TCG_REG_T0, TCG_REG_AT, 0);                                          // 0.0
/*138 */     tcg_out_nop(s);                                                                                  // 0.0
/*142 */     tcg_out_opc_imm(s, OPC_LW, TCG_REG_AT, TCG_REG_A0,                                               // 0.0
/*144 */                     offsetof(CPUState, tlb_table[mem_index][0].addr_read) + addr_memh);              // 0.0
/*148 */     label1_ptr = s->code_ptr;                                                                        // 0.0
/*150 */     tcg_out_opc_imm(s, OPC_BEQ, addr_regh, TCG_REG_AT, 0);                                           // 0.0
/*152 */     tcg_out_nop(s);                                                                                  // 0.0
/*156 */     reloc_pc16(label3_ptr, (tcg_target_long) s->code_ptr);                                           // 0.0
/*158 */ # else                                                                                               // 0.0
/*160 */     label1_ptr = s->code_ptr;                                                                        // 0.0
/*162 */     tcg_out_opc_imm(s, OPC_BEQ, TCG_REG_T0, TCG_REG_AT, 0);                                          // 0.0
/*164 */     tcg_out_nop(s);                                                                                  // 0.0
/*166 */ # endif                                                                                              // 0.0
/*170 */     /* slow path */                                                                                  // 0.0
/*172 */     sp_args = TCG_REG_A0;                                                                            // 0.0
/*174 */     tcg_out_mov(s, sp_args++, addr_reg1);                                                            // 0.0
/*176 */ # if TARGET_LONG_BITS == 64                                                                          // 0.0
/*178 */     tcg_out_mov(s, sp_args++, addr_reg2);                                                            // 0.0
/*180 */ # endif                                                                                              // 0.0
/*182 */     tcg_out_movi(s, TCG_TYPE_I32, sp_args++, mem_index);                                             // 0.0
/*184 */     tcg_out_movi(s, TCG_TYPE_I32, TCG_REG_T9, (tcg_target_long)qemu_ld_helpers[s_bits]);             // 0.0
/*186 */     tcg_out_opc_reg(s, OPC_JALR, TCG_REG_RA, TCG_REG_T9, 0);                                         // 0.0
/*188 */     tcg_out_nop(s);                                                                                  // 0.0
/*192 */     switch(opc) {                                                                                    // 0.0
/*194 */     case 0:                                                                                          // 0.0
/*196 */         tcg_out_opc_imm(s, OPC_ANDI, data_reg1, TCG_REG_V0, 0xff);                                   // 0.0
/*198 */         break;                                                                                       // 0.0
/*200 */     case 0 | 4:                                                                                      // 0.0
/*202 */         tcg_out_opc_sa(s, OPC_SLL, TCG_REG_V0, TCG_REG_V0, 24);                                      // 0.0
/*204 */         tcg_out_opc_sa(s, OPC_SRA, data_reg1, TCG_REG_V0, 24);                                       // 0.0
/*206 */         break;                                                                                       // 0.0
/*208 */     case 1:                                                                                          // 0.0
/*210 */         tcg_out_opc_imm(s, OPC_ANDI, data_reg1, TCG_REG_V0, 0xffff);                                 // 0.0
/*212 */         break;                                                                                       // 0.0
/*214 */     case 1 | 4:                                                                                      // 0.0
/*216 */         tcg_out_opc_sa(s, OPC_SLL, TCG_REG_V0, TCG_REG_V0, 16);                                      // 0.0
/*218 */         tcg_out_opc_sa(s, OPC_SRA, data_reg1, TCG_REG_V0, 16);                                       // 0.0
/*220 */         break;                                                                                       // 0.0
/*222 */     case 2:                                                                                          // 0.0
/*224 */         tcg_out_mov(s, data_reg1, TCG_REG_V0);                                                       // 0.0
/*226 */         break;                                                                                       // 0.0
/*228 */     case 3:                                                                                          // 0.0
/*230 */         tcg_out_mov(s, data_reg2, TCG_REG_V1);                                                       // 0.0
/*232 */         tcg_out_mov(s, data_reg1, TCG_REG_V0);                                                       // 0.0
/*234 */         break;                                                                                       // 0.0
/*236 */     default:                                                                                         // 0.0
/*238 */         tcg_abort();                                                                                 // 0.0
/*240 */     }                                                                                                // 0.0
/*244 */     label2_ptr = s->code_ptr;                                                                        // 0.0
/*246 */     tcg_out_opc_imm(s, OPC_BEQ, TCG_REG_ZERO, TCG_REG_ZERO, 0);                                      // 0.0
/*248 */     tcg_out_nop(s);                                                                                  // 0.0
/*252 */     /* label1: fast path */                                                                          // 0.0
/*254 */     reloc_pc16(label1_ptr, (tcg_target_long) s->code_ptr);                                           // 0.0
/*258 */     tcg_out_opc_imm(s, OPC_LW, TCG_REG_V0, TCG_REG_A0,                                               // 0.0
/*260 */                     offsetof(CPUState, tlb_table[mem_index][0].addend) + addr_meml);                 // 0.0
/*262 */     tcg_out_opc_reg(s, OPC_ADDU, TCG_REG_V0, TCG_REG_V0, addr_regl);                                 // 0.0
/*266 */     addr_reg1 = TCG_REG_V0;                                                                          // 0.0
/*268 */ #endif                                                                                               // 0.0
/*272 */     switch(opc) {                                                                                    // 0.0
/*274 */     case 0:                                                                                          // 0.0
/*276 */         tcg_out_opc_imm(s, OPC_LBU, data_reg1, addr_reg1, 0);                                        // 0.0
/*278 */         break;                                                                                       // 0.0
/*280 */     case 0 | 4:                                                                                      // 0.0
/*282 */         tcg_out_opc_imm(s, OPC_LB, data_reg1, addr_reg1, 0);                                         // 0.0
/*284 */         break;                                                                                       // 0.0
/*286 */     case 1:                                                                                          // 0.0
/*288 */         if (TCG_NEED_BSWAP) {                                                                        // 0.0
/*290 */             tcg_out_opc_imm(s, OPC_LHU, TCG_REG_T0, addr_reg1, 0);                                   // 0.0
/*292 */             tcg_out_bswap16(s, data_reg1, TCG_REG_T0);                                               // 0.0
/*294 */         } else {                                                                                     // 0.0
/*296 */             tcg_out_opc_imm(s, OPC_LHU, data_reg1, addr_reg1, 0);                                    // 0.0
/*298 */         }                                                                                            // 0.0
/*300 */         break;                                                                                       // 0.0
/*302 */     case 1 | 4:                                                                                      // 0.0
/*304 */         if (TCG_NEED_BSWAP) {                                                                        // 0.0
/*306 */             tcg_out_opc_imm(s, OPC_LHU, TCG_REG_T0, addr_reg1, 0);                                   // 0.0
/*308 */             tcg_out_bswap16s(s, data_reg1, TCG_REG_T0);                                              // 0.0
/*310 */         } else {                                                                                     // 0.0
/*312 */             tcg_out_opc_imm(s, OPC_LH, data_reg1, addr_reg1, 0);                                     // 0.0
/*314 */         }                                                                                            // 0.0
/*316 */         break;                                                                                       // 0.0
/*318 */     case 2:                                                                                          // 0.0
/*320 */         if (TCG_NEED_BSWAP) {                                                                        // 0.0
/*322 */             tcg_out_opc_imm(s, OPC_LW, TCG_REG_T0, addr_reg1, 0);                                    // 0.0
/*324 */             tcg_out_bswap32(s, data_reg1, TCG_REG_T0);                                               // 0.0
/*326 */         } else {                                                                                     // 0.0
/*328 */             tcg_out_opc_imm(s, OPC_LW, data_reg1, addr_reg1, 0);                                     // 0.0
/*330 */         }                                                                                            // 0.0
/*332 */         break;                                                                                       // 0.0
/*334 */     case 3:                                                                                          // 0.0
/*336 */ #if !defined(CONFIG_SOFTMMU)                                                                         // 0.0
/*338 */         tcg_out_mov(s, TCG_REG_V0, addr_reg1);                                                       // 0.0
/*340 */         addr_reg1 = TCG_REG_V0;                                                                      // 0.0
/*342 */ #endif                                                                                               // 0.0
/*344 */         if (TCG_NEED_BSWAP) {                                                                        // 0.0
/*346 */             tcg_out_opc_imm(s, OPC_LW, TCG_REG_T0, addr_reg1, 4);                                    // 0.0
/*348 */             tcg_out_bswap32(s, data_reg1, TCG_REG_T0);                                               // 0.0
/*350 */             tcg_out_opc_imm(s, OPC_LW, TCG_REG_T0, addr_reg1, 0);                                    // 0.0
/*352 */             tcg_out_bswap32(s, data_reg2, TCG_REG_T0);                                               // 0.0
/*354 */         } else {                                                                                     // 0.0
/*356 */             tcg_out_opc_imm(s, OPC_LW, data_reg1, addr_reg1, 0);                                     // 0.0
/*358 */             tcg_out_opc_imm(s, OPC_LW, data_reg2, addr_reg1, 4);                                     // 0.0
/*360 */         }                                                                                            // 0.0
/*362 */         break;                                                                                       // 0.0
/*364 */     default:                                                                                         // 0.0
/*366 */         tcg_abort();                                                                                 // 0.0
/*368 */     }                                                                                                // 0.0
/*372 */ #if defined(CONFIG_SOFTMMU)                                                                          // 0.0
/*374 */     reloc_pc16(label2_ptr, (tcg_target_long) s->code_ptr);                                           // 0.0
/*376 */ #endif                                                                                               // 0.0
/*378 */ }                                                                                                    // 0.0
