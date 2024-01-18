// commit message qemu@240ce26a05 (target=1, prob=0.20562288, correct=False): target-mips: fix branch in likely delay slot tcg assert
/*0   */ static void gen_pool16c_insn(DisasContext *ctx, int *is_branch)                   // (5) 0.04688
/*2   */ {                                                                                 // (35) 0.001953
/*4   */     int rd = mmreg((ctx->opcode >> 3) & 0x7);                                     // (6) 0.04297
/*6   */     int rs = mmreg(ctx->opcode & 0x7);                                            // (8) 0.03516
/*8   */     int opc;                                                                      // (34) 0.01367
/*12  */     switch (((ctx->opcode) >> 4) & 0x3f) {                                        // (7) 0.04102
/*14  */     case NOT16 + 0:                                                               // (17) 0.01758
/*16  */     case NOT16 + 1:                                                               // (18) 0.01758
/*18  */     case NOT16 + 2:                                                               // (19) 0.01758
/*20  */     case NOT16 + 3:                                                               // (20) 0.01758
/*22  */         gen_logic(ctx, OPC_NOR, rd, rs, 0);                                       // (4) 0.05078
/*24  */         break;                                                                    // (21) 0.01758
/*26  */     case XOR16 + 0:                                                               // (9) 0.01953
/*28  */     case XOR16 + 1:                                                               // (10) 0.01953
/*30  */     case XOR16 + 2:                                                               // (11) 0.01953
/*32  */     case XOR16 + 3:                                                               // (12) 0.01953
/*34  */         gen_logic(ctx, OPC_XOR, rd, rd, rs);                                      // (1) 0.05469
/*36  */         break;                                                                    // (22) 0.01758
/*38  */     case AND16 + 0:                                                               // (23) 0.01758
/*40  */     case AND16 + 1:                                                               // (24) 0.01758
/*42  */     case AND16 + 2:                                                               // (25) 0.01758
/*44  */     case AND16 + 3:                                                               // (26) 0.01758
/*46  */         gen_logic(ctx, OPC_AND, rd, rd, rs);                                      // (2) 0.05273
/*48  */         break;                                                                    // (27) 0.01758
/*50  */     case OR16 + 0:                                                                // (28) 0.01758
/*52  */     case OR16 + 1:                                                                // (29) 0.01758
/*54  */     case OR16 + 2:                                                                // (30) 0.01758
/*56  */     case OR16 + 3:                                                                // (31) 0.01758
/*58  */         gen_logic(ctx, OPC_OR, rd, rd, rs);                                       // (3) 0.05273
/*60  */         break;                                                                    // (32) 0.01758
/*62  */     case LWM16 + 0:                                                               // (13) 0.01953
/*64  */     case LWM16 + 1:                                                               // (14) 0.01953
/*66  */     case LWM16 + 2:                                                               // (15) 0.01953
/*68  */     case LWM16 + 3:                                                               // (16) 0.01953
/*70  */         {                                                                         // (33) 0.01562
/*72  */             static const int lwm_convert[] = { 0x11, 0x12, 0x13, 0x14 };          // (0) 0.07422
/*74  */             int offset = ZIMM(ctx->opcode, 0, 4);                                 // 0.0
/*78  */             gen_ldst_multiple(ctx, LWM32, lwm_convert[(ctx->opcode >> 4) & 0x3],  // 0.0
/*80  */                               29, offset << 2);                                   // 0.0
/*82  */         }                                                                         // 0.0
/*84  */         break;                                                                    // 0.0
/*86  */     case SWM16 + 0:                                                               // 0.0
/*88  */     case SWM16 + 1:                                                               // 0.0
/*90  */     case SWM16 + 2:                                                               // 0.0
/*92  */     case SWM16 + 3:                                                               // 0.0
/*94  */         {                                                                         // 0.0
/*96  */             static const int swm_convert[] = { 0x11, 0x12, 0x13, 0x14 };          // 0.0
/*98  */             int offset = ZIMM(ctx->opcode, 0, 4);                                 // 0.0
/*102 */             gen_ldst_multiple(ctx, SWM32, swm_convert[(ctx->opcode >> 4) & 0x3],  // 0.0
/*104 */                               29, offset << 2);                                   // 0.0
/*106 */         }                                                                         // 0.0
/*108 */         break;                                                                    // 0.0
/*110 */     case JR16 + 0:                                                                // 0.0
/*112 */     case JR16 + 1:                                                                // 0.0
/*114 */         {                                                                         // 0.0
/*116 */             int reg = ctx->opcode & 0x1f;                                         // 0.0
/*120 */             gen_compute_branch(ctx, OPC_JR, 2, reg, 0, 0);                        // 0.0
/*122 */         }                                                                         // 0.0
/*124 */         *is_branch = 1;                                                           // 0.0
/*126 */         break;                                                                    // 0.0
/*128 */     case JRC16 + 0:                                                               // 0.0
/*130 */     case JRC16 + 1:                                                               // 0.0
/*132 */         {                                                                         // 0.0
/*134 */             int reg = ctx->opcode & 0x1f;                                         // 0.0
/*138 */             gen_compute_branch(ctx, OPC_JR, 2, reg, 0, 0);                        // 0.0
/*140 */             /* Let normal delay slot handling in our caller take us               // 0.0
/*142 */                to the branch target.  */                                          // 0.0
/*144 */         }                                                                         // 0.0
/*146 */         break;                                                                    // 0.0
/*148 */     case JALR16 + 0:                                                              // 0.0
/*150 */     case JALR16 + 1:                                                              // 0.0
/*152 */         opc = OPC_JALR;                                                           // 0.0
/*154 */         goto do_jalr;                                                             // 0.0
/*156 */     case JALR16S + 0:                                                             // 0.0
/*158 */     case JALR16S + 1:                                                             // 0.0
/*160 */         opc = OPC_JALRS;                                                          // 0.0
/*162 */     do_jalr:                                                                      // 0.0
/*164 */         {                                                                         // 0.0
/*166 */             int reg = ctx->opcode & 0x1f;                                         // 0.0
/*170 */             gen_compute_branch(ctx, opc, 2, reg, 31, 0);                          // 0.0
/*172 */         }                                                                         // 0.0
/*174 */         *is_branch = 1;                                                           // 0.0
/*176 */         break;                                                                    // 0.0
/*178 */     case MFHI16 + 0:                                                              // 0.0
/*180 */     case MFHI16 + 1:                                                              // 0.0
/*182 */         gen_HILO(ctx, OPC_MFHI, 0, uMIPS_RS5(ctx->opcode));                       // 0.0
/*184 */         break;                                                                    // 0.0
/*186 */     case MFLO16 + 0:                                                              // 0.0
/*188 */     case MFLO16 + 1:                                                              // 0.0
/*190 */         gen_HILO(ctx, OPC_MFLO, 0, uMIPS_RS5(ctx->opcode));                       // 0.0
/*192 */         break;                                                                    // 0.0
/*194 */     case BREAK16:                                                                 // 0.0
/*196 */         generate_exception(ctx, EXCP_BREAK);                                      // 0.0
/*198 */         break;                                                                    // 0.0
/*200 */     case SDBBP16:                                                                 // 0.0
/*202 */         /* XXX: not clear which exception should be raised                        // 0.0
/*204 */          *      when in debug mode...                                             // 0.0
/*206 */          */                                                                       // 0.0
/*208 */         check_insn(ctx, ISA_MIPS32);                                              // 0.0
/*210 */         if (!(ctx->hflags & MIPS_HFLAG_DM)) {                                     // 0.0
/*212 */             generate_exception(ctx, EXCP_DBp);                                    // 0.0
/*214 */         } else {                                                                  // 0.0
/*216 */             generate_exception(ctx, EXCP_DBp);                                    // 0.0
/*218 */         }                                                                         // 0.0
/*220 */         break;                                                                    // 0.0
/*222 */     case JRADDIUSP + 0:                                                           // 0.0
/*224 */     case JRADDIUSP + 1:                                                           // 0.0
/*226 */         {                                                                         // 0.0
/*228 */             int imm = ZIMM(ctx->opcode, 0, 5);                                    // 0.0
/*232 */             gen_compute_branch(ctx, OPC_JR, 2, 31, 0, 0);                         // 0.0
/*234 */             gen_arith_imm(ctx, OPC_ADDIU, 29, 29, imm << 2);                      // 0.0
/*236 */             /* Let normal delay slot handling in our caller take us               // 0.0
/*238 */                to the branch target.  */                                          // 0.0
/*240 */         }                                                                         // 0.0
/*242 */         break;                                                                    // 0.0
/*244 */     default:                                                                      // 0.0
/*246 */         generate_exception(ctx, EXCP_RI);                                         // 0.0
/*248 */         break;                                                                    // 0.0
/*250 */     }                                                                             // 0.0
/*252 */ }                                                                                 // 0.0
