// commit message qemu@9745807191 (target=1, prob=0.5629086, correct=True): target/openrisc: Keep SR_CY and SR_OV in a separate variables
/*0  */ static void gen_mulu(DisasContext *dc, TCGv dest, TCGv srca, TCGv srcb)  // (2) 0.1596
/*2  */ {                                                                        // (7) 0.005319
/*4  */     TCGv sr_cy = tcg_temp_new();                                         // (4) 0.09043
/*8  */     tcg_gen_muls2_tl(dest, sr_cy, srca, srcb);                           // (3) 0.1383
/*10 */     tcg_gen_setcondi_tl(TCG_COND_NE, sr_cy, sr_cy, 0);                   // (1) 0.1702
/*14 */     tcg_gen_deposit_tl(cpu_sr, cpu_sr, sr_cy, ctz32(SR_CY), 1);          // (0) 0.1915
/*18 */     gen_ove_cy(dc, sr_cy);                                               // (5) 0.07979
/*20 */     tcg_temp_free(sr_cy);                                                // (6) 0.07447
/*22 */ }                                                                        // (8) 0.005319
