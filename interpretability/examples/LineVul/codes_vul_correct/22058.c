// commit message qemu@9bbd4843c0 (target=1, prob=0.6606773, correct=True): target-tricore: fix msub32_q producing the wrong overflow bit
/*0   */ gen_msub32_q(TCGv ret, TCGv arg1, TCGv arg2, TCGv arg3, uint32_t n,  // (0) 0.07227
/*2   */              uint32_t up_shift, CPUTriCoreState *env)                // (3) 0.05469
/*4   */ {                                                                    // (21) 0.001953
/*6   */     TCGv temp = tcg_temp_new();                                      // (19) 0.0293
/*8   */     TCGv temp2 = tcg_temp_new();                                     // (17) 0.03125
/*10  */     TCGv temp3 = tcg_temp_new();                                     // (18) 0.03125
/*12  */     TCGv_i64 t1 = tcg_temp_new_i64();                                // (7) 0.04297
/*14  */     TCGv_i64 t2 = tcg_temp_new_i64();                                // (8) 0.04297
/*16  */     TCGv_i64 t3 = tcg_temp_new_i64();                                // (9) 0.04297
/*18  */     TCGv_i64 t4 = tcg_temp_new_i64();                                // (10) 0.04297
/*22  */     tcg_gen_ext_i32_i64(t2, arg2);                                   // (11) 0.04297
/*24  */     tcg_gen_ext_i32_i64(t3, arg3);                                   // (12) 0.04297
/*28  */     tcg_gen_mul_i64(t2, t2, t3);                                     // (5) 0.04492
/*32  */     tcg_gen_ext_i32_i64(t1, arg1);                                   // (13) 0.04297
/*34  */     /* if we shift part of the fraction out, we need to round up */  // (16) 0.03711
/*36  */     tcg_gen_andi_i64(t4, t2, (1ll << (up_shift - n)) - 1);           // (1) 0.06445
/*38  */     tcg_gen_setcondi_i64(TCG_COND_NE, t4, t4, 0);                    // (2) 0.06055
/*40  */     tcg_gen_sari_i64(t2, t2, up_shift - n);                          // (4) 0.05078
/*42  */     tcg_gen_add_i64(t2, t2, t4);                                     // (14) 0.04297
/*46  */     tcg_gen_sub_i64(t3, t1, t2);                                     // (15) 0.04297
/*48  */     tcg_gen_trunc_i64_i32(temp3, t3);                                // (6) 0.04492
/*50  */     /* calc v bit */                                                 // (20) 0.01562
/*52  */     tcg_gen_setcondi_i64(TCG_COND_GT, t1, t3, 0x7fffffffLL);         // 0.0
/*54  */     tcg_gen_setcondi_i64(TCG_COND_LT, t2, t3, -0x80000000LL);        // 0.0
/*56  */     tcg_gen_or_i64(t1, t1, t2);                                      // 0.0
/*58  */     tcg_gen_trunc_i64_i32(cpu_PSW_V, t1);                            // 0.0
/*60  */     tcg_gen_shli_tl(cpu_PSW_V, cpu_PSW_V, 31);                       // 0.0
/*62  */     /* We produce an overflow on the host if the mul before was      // 0.0
/*64  */        (0x80000000 * 0x80000000) << 1). If this is the               // 0.0
/*66  */        case, we negate the ovf. */                                   // 0.0
/*68  */     if (n == 1) {                                                    // 0.0
/*70  */         tcg_gen_setcondi_tl(TCG_COND_EQ, temp, arg2, 0x80000000);    // 0.0
/*72  */         tcg_gen_setcond_tl(TCG_COND_EQ, temp2, arg2, arg3);          // 0.0
/*74  */         tcg_gen_and_tl(temp, temp, temp2);                           // 0.0
/*76  */         tcg_gen_shli_tl(temp, temp, 31);                             // 0.0
/*78  */         /* negate v bit, if special condition */                     // 0.0
/*80  */         tcg_gen_xor_tl(cpu_PSW_V, cpu_PSW_V, temp);                  // 0.0
/*82  */     }                                                                // 0.0
/*84  */     /* Calc SV bit */                                                // 0.0
/*86  */     tcg_gen_or_tl(cpu_PSW_SV, cpu_PSW_SV, cpu_PSW_V);                // 0.0
/*88  */     /* Calc AV/SAV bits */                                           // 0.0
/*90  */     tcg_gen_add_tl(cpu_PSW_AV, temp3, temp3);                        // 0.0
/*92  */     tcg_gen_xor_tl(cpu_PSW_AV, temp3, cpu_PSW_AV);                   // 0.0
/*94  */     /* calc SAV */                                                   // 0.0
/*96  */     tcg_gen_or_tl(cpu_PSW_SAV, cpu_PSW_SAV, cpu_PSW_AV);             // 0.0
/*98  */     /* write back result */                                          // 0.0
/*100 */     tcg_gen_mov_tl(ret, temp3);                                      // 0.0
/*104 */     tcg_temp_free(temp);                                             // 0.0
/*106 */     tcg_temp_free(temp2);                                            // 0.0
/*108 */     tcg_temp_free(temp3);                                            // 0.0
/*110 */     tcg_temp_free_i64(t1);                                           // 0.0
/*112 */     tcg_temp_free_i64(t2);                                           // 0.0
/*114 */     tcg_temp_free_i64(t3);                                           // 0.0
/*116 */     tcg_temp_free_i64(t4);                                           // 0.0
/*118 */ }                                                                    // 0.0
