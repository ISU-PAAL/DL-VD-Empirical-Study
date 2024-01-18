// commit message qemu@2b48e10f88 (target=0, prob=0.51147795, correct=False): translate-all: consolidate tb init in tb_gen_code
/*0  */ static TranslationBlock *tb_alloc(target_ulong pc)                        // (6) 0.05396
/*2  */ {                                                                         // (18) 0.003597
/*4  */     TranslationBlock *tb;                                                 // (14) 0.03237
/*6  */     TBContext *ctx;                                                       // (10) 0.03597
/*10 */     assert_tb_locked();                                                   // (11) 0.03597
/*14 */     tb = tcg_tb_alloc(&tcg_ctx);                                          // (3) 0.06835
/*16 */     if (unlikely(tb == NULL)) {                                           // (7) 0.05036
/*18 */         return NULL;                                                      // (12) 0.03597
/*20 */     }                                                                     // (16) 0.01439
/*22 */     ctx = &tcg_ctx.tb_ctx;                                                // (5) 0.06115
/*24 */     if (unlikely(ctx->nb_tbs == ctx->tbs_size)) {                         // (1) 0.08633
/*26 */         ctx->tbs_size *= 2;                                               // (4) 0.06475
/*28 */         ctx->tbs = g_renew(TranslationBlock *, ctx->tbs, ctx->tbs_size);  // (0) 0.1295
/*30 */     }                                                                     // (17) 0.01439
/*32 */     ctx->tbs[ctx->nb_tbs++] = tb;                                         // (2) 0.07554
/*34 */     tb->pc = pc;                                                          // (13) 0.03597
/*36 */     tb->cflags = 0;                                                       // (8) 0.03957
/*38 */     tb->invalid = false;                                                  // (9) 0.03957
/*40 */     return tb;                                                            // (15) 0.02518
/*42 */ }                                                                         // (19) 0.003597
