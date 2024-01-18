// commit message qemu@323ad19bcc (target=1, prob=0.55100834, correct=True): target-ppc: introduce opc4 for Expanded Opcode
/*0   */ static void dump_ppc_insns (CPUPPCState *env)                                     // (13) 0.0332
/*2   */ {                                                                                 // (20) 0.001953
/*4   */     opc_handler_t **table, *handler;                                              // (14) 0.0293
/*6   */     const char *p, *q;                                                            // (19) 0.02148
/*8   */     uint8_t opc1, opc2, opc3;                                                     // (12) 0.03711
/*12  */     printf("Instructions set:\n");                                                // (18) 0.02148
/*14  */     /* opc1 is 6 bits long */                                                     // (17) 0.02344
/*16  */     for (opc1 = 0x00; opc1 < PPC_CPU_OPCODES_LEN; opc1++) {                       // (2) 0.06836
/*18  */         table = env->opcodes;                                                     // (16) 0.02734
/*20  */         handler = table[opc1];                                                    // (15) 0.0293
/*22  */         if (is_indirect_opcode(handler)) {                                        // (10) 0.03906
/*24  */             /* opc2 is 5 bits long */                                             // (11) 0.03906
/*26  */             for (opc2 = 0; opc2 < PPC_CPU_INDIRECT_OPCODES_LEN; opc2++) {         // (1) 0.08789
/*28  */                 table = env->opcodes;                                             // (9) 0.04297
/*30  */                 handler = env->opcodes[opc1];                                     // (6) 0.05078
/*32  */                 table = ind_table(handler);                                       // (7) 0.04492
/*34  */                 handler = table[opc2];                                            // (8) 0.04492
/*36  */                 if (is_indirect_opcode(handler)) {                                // (3) 0.05469
/*38  */                     table = ind_table(handler);                                   // (5) 0.05273
/*40  */                     /* opc3 is 5 bits long */                                     // (4) 0.05469
/*42  */                     for (opc3 = 0; opc3 < PPC_CPU_INDIRECT_OPCODES_LEN;           // (0) 0.09375
/*44  */                             opc3++) {                                             // 0.0
/*46  */                         handler = table[opc3];                                    // 0.0
/*48  */                         if (handler->handler != &gen_invalid) {                   // 0.0
/*50  */                             /* Special hack to properly dump SPE insns */         // 0.0
/*52  */                             p = strchr(handler->oname, '_');                      // 0.0
/*54  */                             if (p == NULL) {                                      // 0.0
/*56  */                                 printf("INSN: %02x %02x %02x (%02d %04d) : "      // 0.0
/*58  */                                        "%s\n",                                    // 0.0
/*60  */                                        opc1, opc2, opc3, opc1,                    // 0.0
/*62  */                                        (opc3 << 5) | opc2,                        // 0.0
/*64  */                                        handler->oname);                           // 0.0
/*66  */                             } else {                                              // 0.0
/*68  */                                 q = "speundef";                                   // 0.0
/*70  */                                 if ((p - handler->oname) != strlen(q) ||          // 0.0
/*72  */                                     memcmp(handler->oname, q, strlen(q)) != 0) {  // 0.0
/*74  */                                     /* First instruction */                       // 0.0
/*76  */                                     printf("INSN: %02x %02x %02x (%02d %04d) : "  // 0.0
/*78  */                                            "%.*s\n",                              // 0.0
/*80  */                                            opc1, opc2 << 1, opc3, opc1,           // 0.0
/*82  */                                            (opc3 << 6) | (opc2 << 1),             // 0.0
/*84  */                                            (int)(p - handler->oname),             // 0.0
/*86  */                                            handler->oname);                       // 0.0
/*88  */                                 }                                                 // 0.0
/*90  */                                 if (strcmp(p + 1, q) != 0) {                      // 0.0
/*92  */                                     /* Second instruction */                      // 0.0
/*94  */                                     printf("INSN: %02x %02x %02x (%02d %04d) : "  // 0.0
/*96  */                                            "%s\n",                                // 0.0
/*98  */                                            opc1, (opc2 << 1) | 1, opc3, opc1,     // 0.0
/*100 */                                            (opc3 << 6) | (opc2 << 1) | 1,         // 0.0
/*102 */                                            p + 1);                                // 0.0
/*104 */                                 }                                                 // 0.0
/*106 */                             }                                                     // 0.0
/*108 */                         }                                                         // 0.0
/*110 */                     }                                                             // 0.0
/*112 */                 } else {                                                          // 0.0
/*114 */                     if (handler->handler != &gen_invalid) {                       // 0.0
/*116 */                         printf("INSN: %02x %02x -- (%02d %04d) : %s\n",           // 0.0
/*118 */                                opc1, opc2, opc1, opc2, handler->oname);           // 0.0
/*120 */                     }                                                             // 0.0
/*122 */                 }                                                                 // 0.0
/*124 */             }                                                                     // 0.0
/*126 */         } else {                                                                  // 0.0
/*128 */             if (handler->handler != &gen_invalid) {                               // 0.0
/*130 */                 printf("INSN: %02x -- -- (%02d ----) : %s\n",                     // 0.0
/*132 */                        opc1, opc1, handler->oname);                               // 0.0
/*134 */             }                                                                     // 0.0
/*136 */         }                                                                         // 0.0
/*138 */     }                                                                             // 0.0
/*140 */ }                                                                                 // 0.0
