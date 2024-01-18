// commit message qemu@7ec1e5ea4b (target=0, prob=0.018179614, correct=True): target-sparc: Introduce get_asi
/*0  */ static void gen_ld_asi(DisasContext *dc, TCGv dst, TCGv addr,          // (5) 0.06417
/*2  */                        int insn, int size, int sign)                   // (2) 0.08556
/*4  */ {                                                                      // (19) 0.002674
/*6  */     TCGv_i32 r_asi, r_size, r_sign;                                    // (6) 0.05615
/*10 */     r_asi = gen_get_asi(dc, insn);                                     // (8) 0.04813
/*12 */     r_size = tcg_const_i32(size);                                      // (9) 0.04545
/*14 */     r_sign = tcg_const_i32(sign);                                      // (10) 0.04545
/*16 */ #ifdef TARGET_SPARC64                                                  // (14) 0.02406
/*18 */     gen_helper_ld_asi(dst, cpu_env, addr, r_asi, r_size, r_sign);      // (1) 0.08824
/*20 */ #else                                                                  // (17) 0.005348
/*22 */     {                                                                  // (15) 0.0107
/*24 */         TCGv_i64 t64 = tcg_temp_new_i64();                             // (4) 0.06952
/*26 */         gen_helper_ld_asi(t64, cpu_env, addr, r_asi, r_size, r_sign);  // (0) 0.09893
/*28 */         tcg_gen_trunc_i64_tl(dst, t64);                                // (3) 0.06952
/*30 */         tcg_temp_free_i64(t64);                                        // (7) 0.05348
/*32 */     }                                                                  // (16) 0.0107
/*34 */ #endif                                                                 // (18) 0.005348
/*36 */     tcg_temp_free_i32(r_sign);                                         // (11) 0.04545
/*38 */     tcg_temp_free_i32(r_size);                                         // (12) 0.04545
/*40 */     tcg_temp_free_i32(r_asi);                                          // (13) 0.04545
/*42 */ }                                                                      // (20) 0.002674
