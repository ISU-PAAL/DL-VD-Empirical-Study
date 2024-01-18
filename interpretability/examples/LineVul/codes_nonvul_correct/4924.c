// commit message qemu@42a268c241 (target=0, prob=0.3887943, correct=True): tcg: Change translator-side labels to a pointer
/*0   */ static void gen_trap (DisasContext *ctx, uint32_t opc,    // (5) 0.03711
/*2   */                       int rs, int rt, int16_t imm)        // (0) 0.06641
/*4   */ {                                                         // (35) 0.001953
/*6   */     int cond;                                             // (33) 0.01172
/*8   */     TCGv t0 = tcg_temp_new();                             // (7) 0.03125
/*10  */     TCGv t1 = tcg_temp_new();                             // (8) 0.03125
/*14  */     cond = 0;                                             // (32) 0.01367
/*16  */     /* Load needed operands */                            // (26) 0.01758
/*18  */     switch (opc) {                                        // (27) 0.01758
/*20  */     case OPC_TEQ:                                         // (21) 0.01953
/*22  */     case OPC_TGE:                                         // (22) 0.01953
/*24  */     case OPC_TGEU:                                        // (15) 0.02148
/*26  */     case OPC_TLT:                                         // (23) 0.01953
/*28  */     case OPC_TLTU:                                        // (14) 0.02148
/*30  */     case OPC_TNE:                                         // (24) 0.01953
/*32  */         /* Compare two registers */                       // (13) 0.02344
/*34  */         if (rs != rt) {                                   // (9) 0.0293
/*36  */             gen_load_gpr(t0, rs);                         // (3) 0.04492
/*38  */             gen_load_gpr(t1, rt);                         // (2) 0.04688
/*40  */             cond = 1;                                     // (10) 0.0293
/*42  */         }                                                 // (30) 0.01562
/*44  */         break;                                            // (28) 0.01758
/*46  */     case OPC_TEQI:                                        // (16) 0.02148
/*48  */     case OPC_TGEI:                                        // (17) 0.02148
/*50  */     case OPC_TGEIU:                                       // (18) 0.02148
/*52  */     case OPC_TLTI:                                        // (25) 0.01953
/*54  */     case OPC_TLTIU:                                       // (19) 0.02148
/*56  */     case OPC_TNEI:                                        // (20) 0.02148
/*58  */         /* Compare register to immediate */               // (12) 0.02539
/*60  */         if (rs != 0 || imm != 0) {                        // (6) 0.03516
/*62  */             gen_load_gpr(t0, rs);                         // (4) 0.04492
/*64  */             tcg_gen_movi_tl(t1, (int32_t)imm);            // (1) 0.0625
/*66  */             cond = 1;                                     // (11) 0.0293
/*68  */         }                                                 // (31) 0.01562
/*70  */         break;                                            // (29) 0.01758
/*72  */     }                                                     // (34) 0.007812
/*74  */     if (cond == 0) {                                      // 0.0
/*76  */         switch (opc) {                                    // 0.0
/*78  */         case OPC_TEQ:   /* rs == rs */                    // 0.0
/*80  */         case OPC_TEQI:  /* r0 == 0  */                    // 0.0
/*82  */         case OPC_TGE:   /* rs >= rs */                    // 0.0
/*84  */         case OPC_TGEI:  /* r0 >= 0  */                    // 0.0
/*86  */         case OPC_TGEU:  /* rs >= rs unsigned */           // 0.0
/*88  */         case OPC_TGEIU: /* r0 >= 0  unsigned */           // 0.0
/*90  */             /* Always trap */                             // 0.0
/*92  */             generate_exception(ctx, EXCP_TRAP);           // 0.0
/*94  */             break;                                        // 0.0
/*96  */         case OPC_TLT:   /* rs < rs           */           // 0.0
/*98  */         case OPC_TLTI:  /* r0 < 0            */           // 0.0
/*100 */         case OPC_TLTU:  /* rs < rs unsigned  */           // 0.0
/*102 */         case OPC_TLTIU: /* r0 < 0  unsigned  */           // 0.0
/*104 */         case OPC_TNE:   /* rs != rs          */           // 0.0
/*106 */         case OPC_TNEI:  /* r0 != 0           */           // 0.0
/*108 */             /* Never trap: treat as NOP. */               // 0.0
/*110 */             break;                                        // 0.0
/*112 */         }                                                 // 0.0
/*114 */     } else {                                              // 0.0
/*116 */         int l1 = gen_new_label();                         // 0.0
/*120 */         switch (opc) {                                    // 0.0
/*122 */         case OPC_TEQ:                                     // 0.0
/*124 */         case OPC_TEQI:                                    // 0.0
/*126 */             tcg_gen_brcond_tl(TCG_COND_NE, t0, t1, l1);   // 0.0
/*128 */             break;                                        // 0.0
/*130 */         case OPC_TGE:                                     // 0.0
/*132 */         case OPC_TGEI:                                    // 0.0
/*134 */             tcg_gen_brcond_tl(TCG_COND_LT, t0, t1, l1);   // 0.0
/*136 */             break;                                        // 0.0
/*138 */         case OPC_TGEU:                                    // 0.0
/*140 */         case OPC_TGEIU:                                   // 0.0
/*142 */             tcg_gen_brcond_tl(TCG_COND_LTU, t0, t1, l1);  // 0.0
/*144 */             break;                                        // 0.0
/*146 */         case OPC_TLT:                                     // 0.0
/*148 */         case OPC_TLTI:                                    // 0.0
/*150 */             tcg_gen_brcond_tl(TCG_COND_GE, t0, t1, l1);   // 0.0
/*152 */             break;                                        // 0.0
/*154 */         case OPC_TLTU:                                    // 0.0
/*156 */         case OPC_TLTIU:                                   // 0.0
/*158 */             tcg_gen_brcond_tl(TCG_COND_GEU, t0, t1, l1);  // 0.0
/*160 */             break;                                        // 0.0
/*162 */         case OPC_TNE:                                     // 0.0
/*164 */         case OPC_TNEI:                                    // 0.0
/*166 */             tcg_gen_brcond_tl(TCG_COND_EQ, t0, t1, l1);   // 0.0
/*168 */             break;                                        // 0.0
/*170 */         }                                                 // 0.0
/*172 */         generate_exception(ctx, EXCP_TRAP);               // 0.0
/*174 */         gen_set_label(l1);                                // 0.0
/*176 */     }                                                     // 0.0
/*178 */     tcg_temp_free(t0);                                    // 0.0
/*180 */     tcg_temp_free(t1);                                    // 0.0
/*182 */ }                                                         // 0.0
