// commit message qemu@42a268c241 (target=0, prob=0.63326764, correct=False): tcg: Change translator-side labels to a pointer
/*0   */ static void gen_loongson_integer(DisasContext *ctx, uint32_t opc,  // (1) 0.04492
/*2   */                                  int rd, int rs, int rt)           // (0) 0.08398
/*4   */ {                                                                  // (33) 0.001953
/*6   */     const char *opn = "loongson";                                  // (19) 0.02734
/*8   */     TCGv t0, t1;                                                   // (21) 0.02344
/*12  */     if (rd == 0) {                                                 // (23) 0.01953
/*14  */         /* Treat as NOP. */                                        // (20) 0.02734
/*16  */         MIPS_DEBUG("NOP");                                         // (11) 0.0293
/*18  */         return;                                                    // (24) 0.01758
/*20  */     }                                                              // (30) 0.007812
/*24  */     switch (opc) {                                                 // (25) 0.01758
/*26  */     case OPC_MULT_G_2E:                                            // (12) 0.0293
/*28  */     case OPC_MULT_G_2F:                                            // (13) 0.0293
/*30  */     case OPC_MULTU_G_2E:                                           // (6) 0.03125
/*32  */     case OPC_MULTU_G_2F:                                           // (7) 0.03125
/*34  */ #if defined(TARGET_MIPS64)                                         // (22) 0.02148
/*36  */     case OPC_DMULT_G_2E:                                           // (14) 0.0293
/*38  */     case OPC_DMULT_G_2F:                                           // (15) 0.0293
/*40  */     case OPC_DMULTU_G_2E:                                          // (8) 0.03125
/*42  */     case OPC_DMULTU_G_2F:                                          // (9) 0.03125
/*44  */ #endif                                                             // (32) 0.003906
/*46  */         t0 = tcg_temp_new();                                       // (4) 0.0332
/*48  */         t1 = tcg_temp_new();                                       // (5) 0.0332
/*50  */         break;                                                     // (26) 0.01758
/*52  */     default:                                                       // (29) 0.009766
/*54  */         t0 = tcg_temp_local_new();                                 // (2) 0.03711
/*56  */         t1 = tcg_temp_local_new();                                 // (3) 0.03711
/*58  */         break;                                                     // (27) 0.01758
/*60  */     }                                                              // (31) 0.007812
/*64  */     gen_load_gpr(t0, rs);                                          // (16) 0.0293
/*66  */     gen_load_gpr(t1, rt);                                          // (10) 0.03125
/*70  */     switch (opc) {                                                 // (28) 0.01758
/*72  */     case OPC_MULT_G_2E:                                            // (17) 0.0293
/*74  */     case OPC_MULT_G_2F:                                            // (18) 0.0293
/*76  */         tcg_gen_mul_tl(cpu_gpr[rd], t0, t1);                       // 0.0
/*78  */         tcg_gen_ext32s_tl(cpu_gpr[rd], cpu_gpr[rd]);               // 0.0
/*80  */         opn = "mult.g";                                            // 0.0
/*82  */         break;                                                     // 0.0
/*84  */     case OPC_MULTU_G_2E:                                           // 0.0
/*86  */     case OPC_MULTU_G_2F:                                           // 0.0
/*88  */         tcg_gen_ext32u_tl(t0, t0);                                 // 0.0
/*90  */         tcg_gen_ext32u_tl(t1, t1);                                 // 0.0
/*92  */         tcg_gen_mul_tl(cpu_gpr[rd], t0, t1);                       // 0.0
/*94  */         tcg_gen_ext32s_tl(cpu_gpr[rd], cpu_gpr[rd]);               // 0.0
/*96  */         opn = "multu.g";                                           // 0.0
/*98  */         break;                                                     // 0.0
/*100 */     case OPC_DIV_G_2E:                                             // 0.0
/*102 */     case OPC_DIV_G_2F:                                             // 0.0
/*104 */         {                                                          // 0.0
/*106 */             int l1 = gen_new_label();                              // 0.0
/*108 */             int l2 = gen_new_label();                              // 0.0
/*110 */             int l3 = gen_new_label();                              // 0.0
/*112 */             tcg_gen_ext32s_tl(t0, t0);                             // 0.0
/*114 */             tcg_gen_ext32s_tl(t1, t1);                             // 0.0
/*116 */             tcg_gen_brcondi_tl(TCG_COND_NE, t1, 0, l1);            // 0.0
/*118 */             tcg_gen_movi_tl(cpu_gpr[rd], 0);                       // 0.0
/*120 */             tcg_gen_br(l3);                                        // 0.0
/*122 */             gen_set_label(l1);                                     // 0.0
/*124 */             tcg_gen_brcondi_tl(TCG_COND_NE, t0, INT_MIN, l2);      // 0.0
/*126 */             tcg_gen_brcondi_tl(TCG_COND_NE, t1, -1, l2);           // 0.0
/*128 */             tcg_gen_mov_tl(cpu_gpr[rd], t0);                       // 0.0
/*130 */             tcg_gen_br(l3);                                        // 0.0
/*132 */             gen_set_label(l2);                                     // 0.0
/*134 */             tcg_gen_div_tl(cpu_gpr[rd], t0, t1);                   // 0.0
/*136 */             tcg_gen_ext32s_tl(cpu_gpr[rd], cpu_gpr[rd]);           // 0.0
/*138 */             gen_set_label(l3);                                     // 0.0
/*140 */         }                                                          // 0.0
/*142 */         opn = "div.g";                                             // 0.0
/*144 */         break;                                                     // 0.0
/*146 */     case OPC_DIVU_G_2E:                                            // 0.0
/*148 */     case OPC_DIVU_G_2F:                                            // 0.0
/*150 */         {                                                          // 0.0
/*152 */             int l1 = gen_new_label();                              // 0.0
/*154 */             int l2 = gen_new_label();                              // 0.0
/*156 */             tcg_gen_ext32u_tl(t0, t0);                             // 0.0
/*158 */             tcg_gen_ext32u_tl(t1, t1);                             // 0.0
/*160 */             tcg_gen_brcondi_tl(TCG_COND_NE, t1, 0, l1);            // 0.0
/*162 */             tcg_gen_movi_tl(cpu_gpr[rd], 0);                       // 0.0
/*164 */             tcg_gen_br(l2);                                        // 0.0
/*166 */             gen_set_label(l1);                                     // 0.0
/*168 */             tcg_gen_divu_tl(cpu_gpr[rd], t0, t1);                  // 0.0
/*170 */             tcg_gen_ext32s_tl(cpu_gpr[rd], cpu_gpr[rd]);           // 0.0
/*172 */             gen_set_label(l2);                                     // 0.0
/*174 */         }                                                          // 0.0
/*176 */         opn = "divu.g";                                            // 0.0
/*178 */         break;                                                     // 0.0
/*180 */     case OPC_MOD_G_2E:                                             // 0.0
/*182 */     case OPC_MOD_G_2F:                                             // 0.0
/*184 */         {                                                          // 0.0
/*186 */             int l1 = gen_new_label();                              // 0.0
/*188 */             int l2 = gen_new_label();                              // 0.0
/*190 */             int l3 = gen_new_label();                              // 0.0
/*192 */             tcg_gen_ext32u_tl(t0, t0);                             // 0.0
/*194 */             tcg_gen_ext32u_tl(t1, t1);                             // 0.0
/*196 */             tcg_gen_brcondi_tl(TCG_COND_EQ, t1, 0, l1);            // 0.0
/*198 */             tcg_gen_brcondi_tl(TCG_COND_NE, t0, INT_MIN, l2);      // 0.0
/*200 */             tcg_gen_brcondi_tl(TCG_COND_NE, t1, -1, l2);           // 0.0
/*202 */             gen_set_label(l1);                                     // 0.0
/*204 */             tcg_gen_movi_tl(cpu_gpr[rd], 0);                       // 0.0
/*206 */             tcg_gen_br(l3);                                        // 0.0
/*208 */             gen_set_label(l2);                                     // 0.0
/*210 */             tcg_gen_rem_tl(cpu_gpr[rd], t0, t1);                   // 0.0
/*212 */             tcg_gen_ext32s_tl(cpu_gpr[rd], cpu_gpr[rd]);           // 0.0
/*214 */             gen_set_label(l3);                                     // 0.0
/*216 */         }                                                          // 0.0
/*218 */         opn = "mod.g";                                             // 0.0
/*220 */         break;                                                     // 0.0
/*222 */     case OPC_MODU_G_2E:                                            // 0.0
/*224 */     case OPC_MODU_G_2F:                                            // 0.0
/*226 */         {                                                          // 0.0
/*228 */             int l1 = gen_new_label();                              // 0.0
/*230 */             int l2 = gen_new_label();                              // 0.0
/*232 */             tcg_gen_ext32u_tl(t0, t0);                             // 0.0
/*234 */             tcg_gen_ext32u_tl(t1, t1);                             // 0.0
/*236 */             tcg_gen_brcondi_tl(TCG_COND_NE, t1, 0, l1);            // 0.0
/*238 */             tcg_gen_movi_tl(cpu_gpr[rd], 0);                       // 0.0
/*240 */             tcg_gen_br(l2);                                        // 0.0
/*242 */             gen_set_label(l1);                                     // 0.0
/*244 */             tcg_gen_remu_tl(cpu_gpr[rd], t0, t1);                  // 0.0
/*246 */             tcg_gen_ext32s_tl(cpu_gpr[rd], cpu_gpr[rd]);           // 0.0
/*248 */             gen_set_label(l2);                                     // 0.0
/*250 */         }                                                          // 0.0
/*252 */         opn = "modu.g";                                            // 0.0
/*254 */         break;                                                     // 0.0
/*256 */ #if defined(TARGET_MIPS64)                                         // 0.0
/*258 */     case OPC_DMULT_G_2E:                                           // 0.0
/*260 */     case OPC_DMULT_G_2F:                                           // 0.0
/*262 */         tcg_gen_mul_tl(cpu_gpr[rd], t0, t1);                       // 0.0
/*264 */         opn = "dmult.g";                                           // 0.0
/*266 */         break;                                                     // 0.0
/*268 */     case OPC_DMULTU_G_2E:                                          // 0.0
/*270 */     case OPC_DMULTU_G_2F:                                          // 0.0
/*272 */         tcg_gen_mul_tl(cpu_gpr[rd], t0, t1);                       // 0.0
/*274 */         opn = "dmultu.g";                                          // 0.0
/*276 */         break;                                                     // 0.0
/*278 */     case OPC_DDIV_G_2E:                                            // 0.0
/*280 */     case OPC_DDIV_G_2F:                                            // 0.0
/*282 */         {                                                          // 0.0
/*284 */             int l1 = gen_new_label();                              // 0.0
/*286 */             int l2 = gen_new_label();                              // 0.0
/*288 */             int l3 = gen_new_label();                              // 0.0
/*290 */             tcg_gen_brcondi_tl(TCG_COND_NE, t1, 0, l1);            // 0.0
/*292 */             tcg_gen_movi_tl(cpu_gpr[rd], 0);                       // 0.0
/*294 */             tcg_gen_br(l3);                                        // 0.0
/*296 */             gen_set_label(l1);                                     // 0.0
/*298 */             tcg_gen_brcondi_tl(TCG_COND_NE, t0, -1LL << 63, l2);   // 0.0
/*300 */             tcg_gen_brcondi_tl(TCG_COND_NE, t1, -1LL, l2);         // 0.0
/*302 */             tcg_gen_mov_tl(cpu_gpr[rd], t0);                       // 0.0
/*304 */             tcg_gen_br(l3);                                        // 0.0
/*306 */             gen_set_label(l2);                                     // 0.0
/*308 */             tcg_gen_div_tl(cpu_gpr[rd], t0, t1);                   // 0.0
/*310 */             gen_set_label(l3);                                     // 0.0
/*312 */         }                                                          // 0.0
/*314 */         opn = "ddiv.g";                                            // 0.0
/*316 */         break;                                                     // 0.0
/*318 */     case OPC_DDIVU_G_2E:                                           // 0.0
/*320 */     case OPC_DDIVU_G_2F:                                           // 0.0
/*322 */         {                                                          // 0.0
/*324 */             int l1 = gen_new_label();                              // 0.0
/*326 */             int l2 = gen_new_label();                              // 0.0
/*328 */             tcg_gen_brcondi_tl(TCG_COND_NE, t1, 0, l1);            // 0.0
/*330 */             tcg_gen_movi_tl(cpu_gpr[rd], 0);                       // 0.0
/*332 */             tcg_gen_br(l2);                                        // 0.0
/*334 */             gen_set_label(l1);                                     // 0.0
/*336 */             tcg_gen_divu_tl(cpu_gpr[rd], t0, t1);                  // 0.0
/*338 */             gen_set_label(l2);                                     // 0.0
/*340 */         }                                                          // 0.0
/*342 */         opn = "ddivu.g";                                           // 0.0
/*344 */         break;                                                     // 0.0
/*346 */     case OPC_DMOD_G_2E:                                            // 0.0
/*348 */     case OPC_DMOD_G_2F:                                            // 0.0
/*350 */         {                                                          // 0.0
/*352 */             int l1 = gen_new_label();                              // 0.0
/*354 */             int l2 = gen_new_label();                              // 0.0
/*356 */             int l3 = gen_new_label();                              // 0.0
/*358 */             tcg_gen_brcondi_tl(TCG_COND_EQ, t1, 0, l1);            // 0.0
/*360 */             tcg_gen_brcondi_tl(TCG_COND_NE, t0, -1LL << 63, l2);   // 0.0
/*362 */             tcg_gen_brcondi_tl(TCG_COND_NE, t1, -1LL, l2);         // 0.0
/*364 */             gen_set_label(l1);                                     // 0.0
/*366 */             tcg_gen_movi_tl(cpu_gpr[rd], 0);                       // 0.0
/*368 */             tcg_gen_br(l3);                                        // 0.0
/*370 */             gen_set_label(l2);                                     // 0.0
/*372 */             tcg_gen_rem_tl(cpu_gpr[rd], t0, t1);                   // 0.0
/*374 */             gen_set_label(l3);                                     // 0.0
/*376 */         }                                                          // 0.0
/*378 */         opn = "dmod.g";                                            // 0.0
/*380 */         break;                                                     // 0.0
/*382 */     case OPC_DMODU_G_2E:                                           // 0.0
/*384 */     case OPC_DMODU_G_2F:                                           // 0.0
/*386 */         {                                                          // 0.0
/*388 */             int l1 = gen_new_label();                              // 0.0
/*390 */             int l2 = gen_new_label();                              // 0.0
/*392 */             tcg_gen_brcondi_tl(TCG_COND_NE, t1, 0, l1);            // 0.0
/*394 */             tcg_gen_movi_tl(cpu_gpr[rd], 0);                       // 0.0
/*396 */             tcg_gen_br(l2);                                        // 0.0
/*398 */             gen_set_label(l1);                                     // 0.0
/*400 */             tcg_gen_remu_tl(cpu_gpr[rd], t0, t1);                  // 0.0
/*402 */             gen_set_label(l2);                                     // 0.0
/*404 */         }                                                          // 0.0
/*406 */         opn = "dmodu.g";                                           // 0.0
/*408 */         break;                                                     // 0.0
/*410 */ #endif                                                             // 0.0
/*412 */     }                                                              // 0.0
/*416 */     (void)opn; /* avoid a compiler warning */                      // 0.0
/*418 */     MIPS_DEBUG("%s %s, %s", opn, regnames[rd], regnames[rs]);      // 0.0
/*420 */     tcg_temp_free(t0);                                             // 0.0
/*422 */     tcg_temp_free(t1);                                             // 0.0
/*424 */ }                                                                  // 0.0
