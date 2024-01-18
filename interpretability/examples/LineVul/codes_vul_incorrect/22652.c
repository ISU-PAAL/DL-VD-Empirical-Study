// commit message qemu@fa4478d5c8 (target=1, prob=0.30590785, correct=False): block: wait for job callback in block_job_cancel_sync
/*0  */ void stream_start(BlockDriverState *bs, BlockDriverState *base,            // (7) 0.05519
/*2  */                   const char *base_id, int64_t speed,                      // (2) 0.0974
/*4  */                   BlockDriverCompletionFunc *cb,                           // (4) 0.08442
/*6  */                   void *opaque, Error **errp)                              // (3) 0.08766
/*8  */ {                                                                          // (17) 0.003247
/*10 */     StreamBlockJob *s;                                                     // (10) 0.02922
/*12 */     Coroutine *co;                                                         // (13) 0.02597
/*16 */     s = block_job_create(&stream_job_type, bs, speed, cb, opaque, errp);   // (1) 0.0974
/*18 */     if (!s) {                                                              // (14) 0.02597
/*20 */         return;                                                            // (11) 0.02922
/*22 */     }                                                                      // (15) 0.01299
/*26 */     s->base = base;                                                        // (12) 0.02922
/*28 */     if (base_id) {                                                         // (9) 0.03247
/*30 */         pstrcpy(s->backing_file_id, sizeof(s->backing_file_id), base_id);  // (0) 0.1169
/*32 */     }                                                                      // (16) 0.01299
/*36 */     co = qemu_coroutine_create(stream_run);                                // (6) 0.05844
/*38 */     trace_stream_start(bs, base, s, co, opaque);                           // (5) 0.06169
/*40 */     qemu_coroutine_enter(co, s);                                           // (8) 0.05195
/*42 */ }                                                                          // (18) 0.003247
