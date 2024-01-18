// commit message qemu@ab2b9f174d (target=1, prob=0.1766221, correct=False): lm32-dis: fix NULL pointer dereference
/*0   */ int print_insn_lm32(bfd_vma memaddr, struct disassemble_info *info)    // (1) 0.05273
/*2   */ {                                                                      // (26) 0.001953
/*4   */     fprintf_function fprintf_fn = info->fprintf_func;                  // (13) 0.03711
/*6   */     void *stream = info->stream;                                       // (19) 0.02148
/*8   */     int rc;                                                            // (24) 0.01172
/*10  */     uint8_t insn[4];                                                   // (17) 0.02344
/*12  */     const Lm32OpcodeInfo *opc_info;                                    // (15) 0.03125
/*14  */     uint32_t op;                                                       // (23) 0.01758
/*16  */     const char *args_fmt;                                              // (18) 0.02148
/*20  */     rc = info->read_memory_func(memaddr, insn, 4, info);               // (7) 0.04492
/*22  */     if (rc != 0) {                                                     // (22) 0.01953
/*24  */         info->memory_error_func(rc, memaddr, info);                    // (8) 0.04297
/*26  */         return -1;                                                     // (21) 0.02148
/*28  */     }                                                                  // (25) 0.007812
/*32  */     fprintf_fn(stream, "%02x %02x %02x %02x    ",                      // (3) 0.05078
/*34  */             insn[0], insn[1], insn[2], insn[3]);                       // (0) 0.06055
/*38  */     op = bfd_getb32(insn);                                             // (16) 0.0293
/*40  */     opc_info = find_opcode_info(op);                                   // (14) 0.0332
/*42  */     if (opc_info) {                                                    // (20) 0.02148
/*44  */         fprintf_fn(stream, "%-8s ", opc_info->name);                   // (5) 0.05078
/*46  */         args_fmt = opc_info->args_fmt;                                 // (9) 0.04297
/*48  */         while (args_fmt && *args_fmt) {                                // (11) 0.04102
/*50  */             if (*args_fmt == '%') {                                    // (10) 0.04297
/*52  */                 switch (*(++args_fmt)) {                               // (6) 0.04883
/*54  */                 case '0': {                                            // (12) 0.03906
/*56  */                     uint8_t r0;                                        // (4) 0.05078
/*58  */                     const char *r0_name;                               // (2) 0.05273
/*60  */                     r0 = (op >> 21) & 0x1f;                            // 0.0
/*62  */                     r0_name = find_reg_info(r0)->name;                 // 0.0
/*64  */                     fprintf_fn(stream, "%s", r0_name);                 // 0.0
/*66  */                     break;                                             // 0.0
/*68  */                 }                                                      // 0.0
/*70  */                 case '1': {                                            // 0.0
/*72  */                     uint8_t r1;                                        // 0.0
/*74  */                     const char *r1_name;                               // 0.0
/*76  */                     r1 = (op >> 16) & 0x1f;                            // 0.0
/*78  */                     r1_name = find_reg_info(r1)->name;                 // 0.0
/*80  */                     fprintf_fn(stream, "%s", r1_name);                 // 0.0
/*82  */                     break;                                             // 0.0
/*84  */                 }                                                      // 0.0
/*86  */                 case '2': {                                            // 0.0
/*88  */                     uint8_t r2;                                        // 0.0
/*90  */                     const char *r2_name;                               // 0.0
/*92  */                     r2 = (op >> 11) & 0x1f;                            // 0.0
/*94  */                     r2_name = find_reg_info(r2)->name;                 // 0.0
/*96  */                     fprintf_fn(stream, "%s", r2_name);                 // 0.0
/*98  */                     break;                                             // 0.0
/*100 */                 }                                                      // 0.0
/*102 */                 case 'c': {                                            // 0.0
/*104 */                     uint8_t csr;                                       // 0.0
/*106 */                     const char *csr_name;                              // 0.0
/*108 */                     csr = (op >> 21) & 0x1f;                           // 0.0
/*110 */                     csr_name = find_csr_info(csr)->name;               // 0.0
/*112 */                     if (csr_name) {                                    // 0.0
/*114 */                         fprintf_fn(stream, "%s", csr_name);            // 0.0
/*116 */                     } else {                                           // 0.0
/*118 */                         fprintf_fn(stream, "0x%x", csr);               // 0.0
/*120 */                     }                                                  // 0.0
/*122 */                     break;                                             // 0.0
/*124 */                 }                                                      // 0.0
/*126 */                 case 'u': {                                            // 0.0
/*128 */                     uint16_t u16;                                      // 0.0
/*130 */                     u16 = op & 0xffff;                                 // 0.0
/*132 */                     fprintf_fn(stream, "0x%x", u16);                   // 0.0
/*134 */                     break;                                             // 0.0
/*136 */                 }                                                      // 0.0
/*138 */                 case 's': {                                            // 0.0
/*140 */                     int16_t s16;                                       // 0.0
/*142 */                     s16 = (int16_t)(op & 0xffff);                      // 0.0
/*144 */                     fprintf_fn(stream, "%d", s16);                     // 0.0
/*146 */                     break;                                             // 0.0
/*148 */                 }                                                      // 0.0
/*150 */                 case 'r': {                                            // 0.0
/*152 */                     uint32_t rela;                                     // 0.0
/*154 */                     rela = memaddr + (((int16_t)(op & 0xffff)) << 2);  // 0.0
/*156 */                     fprintf_fn(stream, "%x", rela);                    // 0.0
/*158 */                     break;                                             // 0.0
/*160 */                 }                                                      // 0.0
/*162 */                 case 'R': {                                            // 0.0
/*164 */                     uint32_t rela;                                     // 0.0
/*166 */                     int32_t imm26;                                     // 0.0
/*168 */                     imm26 = (int32_t)((op & 0x3ffffff) << 6) >> 4;     // 0.0
/*170 */                     rela = memaddr + imm26;                            // 0.0
/*172 */                     fprintf_fn(stream, "%x", rela);                    // 0.0
/*174 */                     break;                                             // 0.0
/*176 */                 }                                                      // 0.0
/*178 */                 case 'h': {                                            // 0.0
/*180 */                     uint8_t u5;                                        // 0.0
/*182 */                     u5 = (op & 0x1f);                                  // 0.0
/*184 */                     fprintf_fn(stream, "%d", u5);                      // 0.0
/*186 */                     break;                                             // 0.0
/*188 */                 }                                                      // 0.0
/*190 */                 default:                                               // 0.0
/*192 */                     break;                                             // 0.0
/*194 */                 }                                                      // 0.0
/*196 */             } else {                                                   // 0.0
/*198 */                 fprintf_fn(stream, "%c", *args_fmt);                   // 0.0
/*200 */             }                                                          // 0.0
/*202 */             args_fmt++;                                                // 0.0
/*204 */         }                                                              // 0.0
/*206 */     } else {                                                           // 0.0
/*208 */         fprintf_fn(stream, ".word 0x%x", op);                          // 0.0
/*210 */     }                                                                  // 0.0
/*214 */     return 4;                                                          // 0.0
/*216 */ }                                                                      // 0.0
