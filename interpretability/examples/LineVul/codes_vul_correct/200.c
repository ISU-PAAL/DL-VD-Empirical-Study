// commit message qemu@40365552c2 (target=1, prob=0.9992667, correct=True): mirror: Error out when a BDS would get two BBs
/*0   */ static void mirror_start_job(BlockDriverState *bs, BlockDriverState *target,  // (12) 0.03906
/*2   */                              const char *replaces,                            // (8) 0.06641
/*4   */                              int64_t speed, uint32_t granularity,             // (1) 0.08008
/*6   */                              int64_t buf_size,                                // (6) 0.07031
/*8   */                              BlockdevOnError on_source_error,                 // (3) 0.07422
/*10  */                              BlockdevOnError on_target_error,                 // (4) 0.07422
/*12  */                              bool unmap,                                      // (9) 0.0625
/*14  */                              BlockCompletionFunc *cb,                         // (5) 0.07031
/*16  */                              void *opaque, Error **errp,                      // (2) 0.07422
/*18  */                              const BlockJobDriver *driver,                    // (7) 0.06836
/*20  */                              bool is_none_mode, BlockDriverState *base)       // (0) 0.08008
/*22  */ {                                                                             // (17) 0.001953
/*24  */     MirrorBlockJob *s;                                                        // (15) 0.01758
/*29  */     if (granularity == 0) {                                                   // (14) 0.02148
/*31  */         granularity = bdrv_get_default_bitmap_granularity(target);            // (10) 0.05078
/*33  */     }                                                                         // (16) 0.007812
/*37  */     assert ((granularity & (granularity - 1)) == 0);                          // (13) 0.0332
/*41  */     if ((on_source_error == BLOCKDEV_ON_ERROR_STOP ||                         // (11) 0.04297
/*43  */          on_source_error == BLOCKDEV_ON_ERROR_ENOSPC) &&                      // 0.0
/*45  */         (!bs->blk || !blk_iostatus_is_enabled(bs->blk))) {                    // 0.0
/*47  */         error_setg(errp, QERR_INVALID_PARAMETER, "on-source-error");          // 0.0
/*49  */         return;                                                               // 0.0
/*51  */     }                                                                         // 0.0
/*55  */     if (buf_size < 0) {                                                       // 0.0
/*57  */         error_setg(errp, "Invalid parameter 'buf-size'");                     // 0.0
/*59  */         return;                                                               // 0.0
/*61  */     }                                                                         // 0.0
/*65  */     if (buf_size == 0) {                                                      // 0.0
/*67  */         buf_size = DEFAULT_MIRROR_BUF_SIZE;                                   // 0.0
/*69  */     }                                                                         // 0.0
/*73  */     /* We can't support this case as long as the block layer can't handle     // 0.0
/*75  */      * multiple BlockBackends per BlockDriverState. */                        // 0.0
/*77  */     if (replaces) {                                                           // 0.0
/*79  */         replaced_bs = bdrv_lookup_bs(replaces, replaces, errp);               // 0.0
/*81  */         if (replaced_bs == NULL) {                                            // 0.0
/*83  */             return;                                                           // 0.0
/*85  */         }                                                                     // 0.0
/*87  */     } else {                                                                  // 0.0
/*89  */         replaced_bs = bs;                                                     // 0.0
/*91  */     }                                                                         // 0.0
/*93  */     if (replaced_bs->blk && target->blk) {                                    // 0.0
/*95  */         error_setg(errp, "Can't create node with two BlockBackends");         // 0.0
/*97  */         return;                                                               // 0.0
/*99  */     }                                                                         // 0.0
/*103 */     s = block_job_create(driver, bs, speed, cb, opaque, errp);                // 0.0
/*105 */     if (!s) {                                                                 // 0.0
/*107 */         return;                                                               // 0.0
/*109 */     }                                                                         // 0.0
/*113 */     s->replaces = g_strdup(replaces);                                         // 0.0
/*115 */     s->on_source_error = on_source_error;                                     // 0.0
/*117 */     s->on_target_error = on_target_error;                                     // 0.0
/*119 */     s->target = target;                                                       // 0.0
/*121 */     s->is_none_mode = is_none_mode;                                           // 0.0
/*123 */     s->base = base;                                                           // 0.0
/*125 */     s->granularity = granularity;                                             // 0.0
/*127 */     s->buf_size = ROUND_UP(buf_size, granularity);                            // 0.0
/*129 */     s->unmap = unmap;                                                         // 0.0
/*133 */     s->dirty_bitmap = bdrv_create_dirty_bitmap(bs, granularity, NULL, errp);  // 0.0
/*135 */     if (!s->dirty_bitmap) {                                                   // 0.0
/*137 */         g_free(s->replaces);                                                  // 0.0
/*139 */         block_job_unref(&s->common);                                          // 0.0
/*141 */         return;                                                               // 0.0
/*143 */     }                                                                         // 0.0
/*147 */     bdrv_op_block_all(s->target, s->common.blocker);                          // 0.0
/*151 */     bdrv_set_enable_write_cache(s->target, true);                             // 0.0
/*153 */     if (s->target->blk) {                                                     // 0.0
/*155 */         blk_set_on_error(s->target->blk, on_target_error, on_target_error);   // 0.0
/*157 */         blk_iostatus_enable(s->target->blk);                                  // 0.0
/*159 */     }                                                                         // 0.0
/*161 */     s->common.co = qemu_coroutine_create(mirror_run);                         // 0.0
/*163 */     trace_mirror_start(bs, s, s->common.co, opaque);                          // 0.0
/*165 */     qemu_coroutine_enter(s->common.co, s);                                    // 0.0
/*167 */ }                                                                             // 0.0
