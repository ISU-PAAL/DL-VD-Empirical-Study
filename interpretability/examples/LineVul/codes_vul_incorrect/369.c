// commit message qemu@0b8b8753e4 (target=1, prob=0.34444577, correct=False): coroutine: move entry argument to qemu_coroutine_create
/*0  */ void stream_start(const char *job_id, BlockDriverState *bs,              // (9) 0.05217
/*2  */                   BlockDriverState *base, const char *backing_file_str,  // (1) 0.09565
/*4  */                   int64_t speed, BlockdevOnError on_error,               // (3) 0.08986
/*6  */                   BlockCompletionFunc *cb, void *opaque, Error **errp)   // (0) 0.1014
/*8  */ {                                                                        // (16) 0.002899
/*10 */     StreamBlockJob *s;                                                   // (11) 0.02609
/*14 */     s = block_job_create(job_id, &stream_job_driver, bs, speed,          // (4) 0.07826
/*16 */                          cb, opaque, errp);                              // (2) 0.09275
/*18 */     if (!s) {                                                            // (14) 0.02319
/*20 */         return;                                                          // (12) 0.02609
/*22 */     }                                                                    // (15) 0.01159
/*26 */     s->base = base;                                                      // (13) 0.02609
/*28 */     s->backing_file_str = g_strdup(backing_file_str);                    // (5) 0.07246
/*32 */     s->on_error = on_error;                                              // (10) 0.03768
/*34 */     s->common.co = qemu_coroutine_create(stream_run);                    // (7) 0.06377
/*36 */     trace_stream_start(bs, base, s, s->common.co, opaque);               // (6) 0.06667
/*38 */     qemu_coroutine_enter(s->common.co, s);                               // (8) 0.05797
/*40 */ }                                                                        // (17) 0.002899
