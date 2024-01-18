// commit message qemu@88b062c203 (target=0, prob=0.4346808, correct=True): block: introduce BDRV_POLL_WHILE
/*0  */ int bdrv_pdiscard(BlockDriverState *bs, int64_t offset, int count)  // (2) 0.07122
/*2  */ {                                                                   // (20) 0.002967
/*4  */     Coroutine *co;                                                  // (15) 0.02374
/*6  */     DiscardCo rwco = {                                              // (13) 0.03264
/*8  */         .bs = bs,                                                   // (10) 0.03858
/*10 */         .offset = offset,                                           // (11) 0.03561
/*12 */         .count = count,                                             // (12) 0.03561
/*14 */         .ret = NOT_DONE,                                            // (8) 0.04451
/*16 */     };                                                              // (18) 0.01187
/*20 */     if (qemu_in_coroutine()) {                                      // (9) 0.04451
/*22 */         /* Fast-path if already in coroutine context */             // (6) 0.05341
/*24 */         bdrv_pdiscard_co_entry(&rwco);                              // (4) 0.06528
/*26 */     } else {                                                        // (17) 0.0178
/*28 */         AioContext *aio_context = bdrv_get_aio_context(bs);         // (1) 0.08605
/*32 */         co = qemu_coroutine_create(bdrv_pdiscard_co_entry, &rwco);  // (0) 0.1009
/*34 */         qemu_coroutine_enter(co);                                   // (7) 0.05341
/*36 */         while (rwco.ret == NOT_DONE) {                              // (5) 0.05935
/*38 */             aio_poll(aio_context, true);                            // (3) 0.06825
/*40 */         }                                                           // (16) 0.02374
/*42 */     }                                                               // (19) 0.01187
/*46 */     return rwco.ret;                                                // (14) 0.02967
/*48 */ }                                                                   // (21) 0.002967
