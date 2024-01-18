// commit message qemu@15c2f669e3 (target=1, prob=0.18690616, correct=False): qapi: Split visit_end_struct() into pieces
/*0  */ opts_end_struct(Visitor *v, Error **errp)                            // (9) 0.04521
/*2  */ {                                                                    // (22) 0.00266
/*4  */     OptsVisitor *ov = to_ov(v);                                      // (10) 0.04255
/*6  */     GHashTableIter iter;                                             // (16) 0.02394
/*8  */     GQueue *any;                                                     // (18) 0.02128
/*12 */     if (--ov->depth > 0) {                                           // (14) 0.03457
/*14 */         return;                                                      // (17) 0.02394
/*16 */     }                                                                // (19) 0.01064
/*20 */     /* we should have processed all (distinct) QemuOpt instances */  // (7) 0.05053
/*22 */     g_hash_table_iter_init(&iter, ov->unprocessed_opts);             // (2) 0.06383
/*24 */     if (g_hash_table_iter_next(&iter, NULL, (void **)&any)) {        // (1) 0.07181
/*26 */         const QemuOpt *first;                                        // (11) 0.03989
/*30 */         first = g_queue_peek_head(any);                              // (5) 0.05319
/*32 */         error_setg(errp, QERR_INVALID_PARAMETER, first->name);       // (0) 0.08511
/*34 */     }                                                                // (20) 0.01064
/*36 */     g_hash_table_destroy(ov->unprocessed_opts);                      // (6) 0.05319
/*38 */     ov->unprocessed_opts = NULL;                                     // (12) 0.03723
/*40 */     if (ov->fake_id_opt) {                                           // (13) 0.03723
/*42 */         g_free(ov->fake_id_opt->name);                               // (3) 0.05585
/*44 */         g_free(ov->fake_id_opt->str);                                // (4) 0.05585
/*46 */         g_free(ov->fake_id_opt);                                     // (8) 0.05053
/*48 */     }                                                                // (21) 0.01064
/*50 */     ov->fake_id_opt = NULL;                                          // (15) 0.03457
/*52 */ }                                                                    // (23) 0.00266
