// commit message qemu@d279279e2b (target=1, prob=0.56319463, correct=True): target-mips: implement UserLocal Register
/*0  */ static void gen_rdhwr(DisasContext *ctx, int rt, int rd)                    // (4) 0.04297
/*2  */ {                                                                           // (31) 0.001953
/*4  */     TCGv t0;                                                                // (19) 0.01758
/*8  */ #if !defined(CONFIG_USER_ONLY)                                              // (16) 0.02539
/*10 */     /* The Linux kernel will emulate rdhwr if it's not supported natively.  // (5) 0.03906
/*12 */        Therefore only check the ISA in system mode.  */                     // (11) 0.03516
/*14 */     check_insn(ctx, ISA_MIPS32R2);                                          // (10) 0.03711
/*16 */ #endif                                                                      // (30) 0.003906
/*18 */     t0 = tcg_temp_new();                                                    // (17) 0.02539
/*22 */     switch (rd) {                                                           // (24) 0.01562
/*24 */     case 0:                                                                 // (25) 0.01172
/*26 */         save_cpu_state(ctx, 1);                                             // (12) 0.0332
/*28 */         gen_helper_rdhwr_cpunum(t0, cpu_env);                               // (1) 0.05273
/*30 */         gen_store_gpr(t0, rt);                                              // (6) 0.03906
/*32 */         break;                                                              // (20) 0.01758
/*34 */     case 1:                                                                 // (26) 0.01172
/*36 */         save_cpu_state(ctx, 1);                                             // (13) 0.0332
/*38 */         gen_helper_rdhwr_synci_step(t0, cpu_env);                           // (0) 0.05469
/*40 */         gen_store_gpr(t0, rt);                                              // (7) 0.03906
/*42 */         break;                                                              // (21) 0.01758
/*44 */     case 2:                                                                 // (27) 0.01172
/*46 */         save_cpu_state(ctx, 1);                                             // (14) 0.0332
/*48 */         gen_helper_rdhwr_cc(t0, cpu_env);                                   // (3) 0.04883
/*50 */         gen_store_gpr(t0, rt);                                              // (8) 0.03906
/*52 */         break;                                                              // (22) 0.01758
/*54 */     case 3:                                                                 // (28) 0.01172
/*56 */         save_cpu_state(ctx, 1);                                             // (15) 0.0332
/*58 */         gen_helper_rdhwr_ccres(t0, cpu_env);                                // (2) 0.05078
/*60 */         gen_store_gpr(t0, rt);                                              // (9) 0.03906
/*62 */         break;                                                              // (23) 0.01758
/*64 */     case 29:                                                                // (29) 0.01172
/*66 */ #if defined(CONFIG_USER_ONLY)                                               // (18) 0.02344
/*68 */         tcg_gen_ld_tl(t0, cpu_env, offsetof(CPUMIPSState, tls_value));      // 0.0
/*70 */         gen_store_gpr(t0, rt);                                              // 0.0
/*72 */         break;                                                              // 0.0
/*74 */ #else                                                                       // 0.0
/*76 */         /* XXX: Some CPUs implement this in hardware.                       // 0.0
/*78 */            Not supported yet. */                                            // 0.0
/*80 */ #endif                                                                      // 0.0
/*82 */     default:            /* Invalid */                                       // 0.0
/*84 */         MIPS_INVAL("rdhwr");                                                // 0.0
/*86 */         generate_exception(ctx, EXCP_RI);                                   // 0.0
/*88 */         break;                                                              // 0.0
/*90 */     }                                                                       // 0.0
/*92 */     tcg_temp_free(t0);                                                      // 0.0
/*94 */ }                                                                           // 0.0
