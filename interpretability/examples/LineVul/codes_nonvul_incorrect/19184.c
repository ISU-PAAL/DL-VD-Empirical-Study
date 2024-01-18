// commit message qemu@d157ed5f72 (target=0, prob=0.50527424, correct=False): blkdebug: Refactor error injection
/*0  */ static int inject_error(BlockDriverState *bs, BlkdebugRule *rule)                // (2) 0.0819
/*2  */ {                                                                                // (13) 0.00431
/*4  */     BDRVBlkdebugState *s = bs->opaque;                                           // (3) 0.0819
/*6  */     int error = rule->options.inject.error;                                      // (6) 0.06466
/*8  */     bool immediately = rule->options.inject.immediately;                         // (5) 0.06897
/*12 */     if (rule->options.inject.once) {                                             // (7) 0.06466
/*14 */         QSIMPLEQ_REMOVE(&s->active_rules, rule, BlkdebugRule, active_next);      // (1) 0.1422
/*16 */         remove_rule(rule);                                                       // (8) 0.05603
/*18 */     }                                                                            // (11) 0.01724
/*22 */     if (!immediately) {                                                          // (9) 0.03879
/*24 */         aio_co_schedule(qemu_get_current_aio_context(), qemu_coroutine_self());  // (0) 0.1595
/*26 */         qemu_coroutine_yield();                                                  // (4) 0.07328
/*28 */     }                                                                            // (12) 0.01724
/*32 */     return -error;                                                               // (10) 0.03017
/*34 */ }                                                                                // (14) 0.00431
