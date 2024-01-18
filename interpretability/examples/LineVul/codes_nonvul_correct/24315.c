// commit message qemu@1a9353d258 (target=0, prob=0.10882364, correct=True): added loop/xadd/cmpxchg support
/*0   */ int cpu_x86_gen_code(uint8_t *gen_code_buf, int max_code_size,         // (3) 0.05664
/*2   */                      int *gen_code_size_ptr, uint8_t *pc_start,        // (0) 0.07812
/*4   */                      int flags)                                        // (8) 0.04492
/*6   */ {                                                                      // (25) 0.001953
/*8   */     DisasContext dc1, *dc = &dc1;                                      // (13) 0.03125
/*10  */     uint8_t *gen_code_end, *pc_ptr;                                    // (11) 0.03711
/*12  */     long ret;                                                          // (22) 0.01172
/*14  */ #ifdef DEBUG_DISAS                                                     // (20) 0.01367
/*16  */     struct disassemble_info disasm_info;                               // (17) 0.02734
/*18  */ #endif                                                                 // (24) 0.003906
/*20  */     dc->code32 = (flags >> GEN_FLAG_CODE32_SHIFT) & 1;                 // (6) 0.04883
/*22  */     dc->addseg = (flags >> GEN_FLAG_ADDSEG_SHIFT) & 1;                 // (4) 0.05078
/*24  */     dc->f_st = (flags >> GEN_FLAG_ST_SHIFT) & 7;                       // (7) 0.04687
/*26  */     dc->cc_op = CC_OP_DYNAMIC;                                         // (12) 0.03516
/*28  */     gen_code_ptr = gen_code_buf;                                       // (15) 0.0293
/*30  */     gen_code_end = gen_code_buf + max_code_size - 4096;                // (9) 0.04492
/*32  */     gen_start();                                                       // (21) 0.01367
/*36  */     dc->is_jmp = 0;                                                    // (18) 0.02344
/*38  */     pc_ptr = pc_start;                                                 // (19) 0.02148
/*40  */     do {                                                               // (23) 0.009766
/*42  */         ret = disas_insn(dc, pc_ptr);                                  // (10) 0.04102
/*44  */         if (ret == -1)                                                 // (16) 0.0293
/*46  */             error("unknown instruction at PC=0x%x B=%02x %02x",        // (2) 0.0625
/*48  */                   pc_ptr, pc_ptr[0], pc_ptr[1]);                       // (1) 0.06445
/*50  */         pc_ptr = (void *)ret;                                          // (14) 0.03125
/*52  */     } while (!dc->is_jmp && gen_code_ptr < gen_code_end);              // (5) 0.04883
/*54  */     /* we must store the eflags state if it is not already done */     // 0.0
/*56  */     if (dc->cc_op != CC_OP_DYNAMIC)                                    // 0.0
/*58  */         gen_op_set_cc_op(dc->cc_op);                                   // 0.0
/*60  */     if (dc->is_jmp != 1) {                                             // 0.0
/*62  */         /* we add an additionnal jmp to update the simulated PC */     // 0.0
/*64  */         gen_op_jmp_im(ret);                                            // 0.0
/*66  */     }                                                                  // 0.0
/*68  */     gen_end();                                                         // 0.0
/*70  */     *gen_code_size_ptr = gen_code_ptr - gen_code_buf;                  // 0.0
/*74  */ #ifdef DEBUG_DISAS                                                     // 0.0
/*76  */     if (loglevel) {                                                    // 0.0
/*78  */         uint8_t *pc;                                                   // 0.0
/*80  */         int count;                                                     // 0.0
/*84  */         INIT_DISASSEMBLE_INFO(disasm_info, logfile, fprintf);          // 0.0
/*86  */ #if 0                                                                  // 0.0
/*88  */         disasm_info.flavour = bfd_get_flavour (abfd);                  // 0.0
/*90  */         disasm_info.arch = bfd_get_arch (abfd);                        // 0.0
/*92  */         disasm_info.mach = bfd_get_mach (abfd);                        // 0.0
/*94  */ #endif                                                                 // 0.0
/*96  */ #ifdef WORDS_BIGENDIAN                                                 // 0.0
/*98  */         disasm_info.endian = BFD_ENDIAN_BIG;                           // 0.0
/*100 */ #else                                                                  // 0.0
/*102 */         disasm_info.endian = BFD_ENDIAN_LITTLE;                        // 0.0
/*104 */ #endif                                                                 // 0.0
/*106 */         fprintf(logfile, "IN:\n");                                     // 0.0
/*108 */         disasm_info.buffer = pc_start;                                 // 0.0
/*110 */         disasm_info.buffer_vma = (unsigned long)pc_start;              // 0.0
/*112 */         disasm_info.buffer_length = pc_ptr - pc_start;                 // 0.0
/*114 */         pc = pc_start;                                                 // 0.0
/*116 */         while (pc < pc_ptr) {                                          // 0.0
/*118 */             fprintf(logfile, "0x%08lx:  ", (long)pc);                  // 0.0
/*120 */             count = print_insn_i386((unsigned long)pc, &disasm_info);  // 0.0
/*122 */             fprintf(logfile, "\n");                                    // 0.0
/*124 */             pc += count;                                               // 0.0
/*126 */         }                                                              // 0.0
/*128 */         fprintf(logfile, "\n");                                        // 0.0
/*130 */                                                                        // 0.0
/*132 */         pc = gen_code_buf;                                             // 0.0
/*134 */         disasm_info.buffer = pc;                                       // 0.0
/*136 */         disasm_info.buffer_vma = (unsigned long)pc;                    // 0.0
/*138 */         disasm_info.buffer_length = *gen_code_size_ptr;                // 0.0
/*140 */         fprintf(logfile, "OUT: [size=%d]\n", *gen_code_size_ptr);      // 0.0
/*142 */         while (pc < gen_code_ptr) {                                    // 0.0
/*144 */             fprintf(logfile, "0x%08lx:  ", (long)pc);                  // 0.0
/*146 */             count = print_insn_i386((unsigned long)pc, &disasm_info);  // 0.0
/*148 */             fprintf(logfile, "\n");                                    // 0.0
/*150 */             pc += count;                                               // 0.0
/*152 */         }                                                              // 0.0
/*154 */         fprintf(logfile, "\n");                                        // 0.0
/*156 */     }                                                                  // 0.0
/*158 */ #endif                                                                 // 0.0
/*160 */     return 0;                                                          // 0.0
/*162 */ }                                                                      // 0.0
