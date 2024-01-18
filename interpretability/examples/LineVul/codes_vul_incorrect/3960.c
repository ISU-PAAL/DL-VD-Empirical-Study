// commit message qemu@b835e919f0 (target=1, prob=0.19685039, correct=False): target-mips: fix save_cpu_state() calls
/*0  */ static void gen_st_cond (DisasContext *ctx, uint32_t opc, int rt,            // (3) 0.05319
/*2  */                          int base, int16_t offset)                           // (1) 0.07021
/*4  */ {                                                                            // (28) 0.002128
/*6  */     const char *opn = "st_cond";                                             // (13) 0.02979
/*8  */     TCGv t0, t1;                                                             // (18) 0.02553
/*12 */     t0 = tcg_temp_local_new();                                               // (10) 0.03191
/*16 */     gen_base_offset_addr(ctx, t0, base, offset);                             // (5) 0.04255
/*18 */     /* Don't do NOP if destination is zero: we must perform the actual       // (6) 0.04043
/*20 */        memory access. */                                                     // (20) 0.02128
/*24 */     t1 = tcg_temp_local_new();                                               // (11) 0.03191
/*26 */     gen_load_gpr(t1, rt);                                                    // (9) 0.03404
/*28 */     switch (opc) {                                                           // (22) 0.01915
/*30 */ #if defined(TARGET_MIPS64)                                                   // (19) 0.0234
/*32 */     case OPC_SCD:                                                            // (21) 0.02128
/*34 */         save_cpu_state(ctx, 0);                                              // (7) 0.03617
/*36 */         op_st_scd(t1, t0, rt, ctx);                                          // (2) 0.05532
/*38 */         opn = "scd";                                                         // (14) 0.02979
/*40 */         break;                                                               // (23) 0.01915
/*42 */ #endif                                                                       // (27) 0.004255
/*44 */     case OPC_SC:                                                             // (24) 0.01915
/*46 */         save_cpu_state(ctx, 1);                                              // (8) 0.03617
/*48 */         op_st_sc(t1, t0, rt, ctx);                                           // (4) 0.05319
/*50 */         opn = "sc";                                                          // (15) 0.02766
/*52 */         break;                                                               // (25) 0.01915
/*54 */     }                                                                        // (26) 0.008511
/*56 */     (void)opn; /* avoid a compiler warning */                                // (12) 0.03191
/*58 */     MIPS_DEBUG("%s %s, %d(%s)", opn, regnames[rt], offset, regnames[base]);  // (0) 0.07234
/*60 */     tcg_temp_free(t1);                                                       // (16) 0.02766
/*62 */     tcg_temp_free(t0);                                                       // (17) 0.02766
/*64 */ }                                                                            // (29) 0.002128
