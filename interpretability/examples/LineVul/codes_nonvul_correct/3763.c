// commit message qemu@4fb588e95b (target=0, prob=0.28121457, correct=True): blockjob: reorganize block_job_completed_txn_abort
/*0  */ static void block_job_completed_txn_abort(BlockJob *job)                         // (9) 0.03906
/*2  */ {                                                                                // (29) 0.001953
/*4  */     AioContext *ctx;                                                             // (21) 0.01758
/*6  */     BlockJobTxn *txn = job->txn;                                                 // (13) 0.03125
/*8  */     BlockJob *other_job, *next;                                                  // (16) 0.02539
/*12 */     if (txn->aborting) {                                                         // (18) 0.02344
/*14 */         /*                                                                       // (24) 0.01562
/*16 */          * We are cancelled by another job, which will handle everything.        // (8) 0.04102
/*18 */          */                                                                      // (22) 0.01758
/*20 */         return;                                                                  // (23) 0.01758
/*22 */     }                                                                            // (26) 0.007812
/*24 */     txn->aborting = true;                                                        // (20) 0.02148
/*26 */     /* We are the first failed job. Cancel other jobs. */                        // (14) 0.03125
/*28 */     QLIST_FOREACH(other_job, &txn->jobs, txn_list) {                             // (4) 0.04883
/*30 */         ctx = blk_get_aio_context(other_job->blk);                               // (2) 0.05273
/*32 */         aio_context_acquire(ctx);                                                // (12) 0.0332
/*34 */     }                                                                            // (27) 0.007812
/*36 */     QLIST_FOREACH(other_job, &txn->jobs, txn_list) {                             // (5) 0.04883
/*38 */         if (other_job == job || other_job->completed) {                          // (6) 0.04492
/*40 */             /* Other jobs are "effectively" cancelled by us, set the status for  // (3) 0.05273
/*42 */              * them; this job, however, may or may not be cancelled, depending   // (1) 0.05469
/*44 */              * on the caller, so leave it. */                                    // (7) 0.04297
/*46 */             if (other_job != job) {                                              // (10) 0.03906
/*48 */                 block_job_cancel_async(other_job);                               // (0) 0.05664
/*50 */             }                                                                    // (19) 0.02344
/*52 */             continue;                                                            // (17) 0.02539
/*54 */         }                                                                        // (25) 0.01562
/*56 */         block_job_cancel_sync(other_job);                                        // (11) 0.03906
/*58 */         assert(other_job->completed);                                            // (15) 0.03125
/*60 */     }                                                                            // (28) 0.007812
/*62 */     QLIST_FOREACH_SAFE(other_job, &txn->jobs, txn_list, next) {                  // 0.0
/*64 */         ctx = blk_get_aio_context(other_job->blk);                               // 0.0
/*66 */         block_job_completed_single(other_job);                                   // 0.0
/*68 */         aio_context_release(ctx);                                                // 0.0
/*70 */     }                                                                            // 0.0
/*72 */ }                                                                                // 0.0
