// commit message qemu@356f59b875 (target=1, prob=0.27931494, correct=False): blockjob: introduce block_job_do_yield
/*0  */ void coroutine_fn block_job_pause_point(BlockJob *job)                  // (2) 0.05844
/*2  */ {                                                                       // (22) 0.003247
/*4  */     assert(job && block_job_started(job));                              // (6) 0.0487
/*8  */     if (!block_job_should_pause(job)) {                                 // (5) 0.05195
/*10 */         return;                                                         // (14) 0.02922
/*12 */     }                                                                   // (17) 0.01299
/*14 */     if (block_job_is_cancelled(job)) {                                  // (3) 0.05844
/*16 */         return;                                                         // (15) 0.02922
/*18 */     }                                                                   // (18) 0.01299
/*22 */     if (job->driver->pause) {                                           // (13) 0.03896
/*24 */         job->driver->pause(job);                                        // (7) 0.0487
/*26 */     }                                                                   // (19) 0.01299
/*30 */     if (block_job_should_pause(job) && !block_job_is_cancelled(job)) {  // (0) 0.0974
/*32 */         job->paused = true;                                             // (8) 0.04545
/*34 */         job->busy = false;                                              // (10) 0.04545
/*36 */         qemu_coroutine_yield(); /* wait for block_job_resume() */       // (1) 0.09091
/*38 */         job->busy = true;                                               // (11) 0.04545
/*40 */         job->paused = false;                                            // (9) 0.04545
/*42 */     }                                                                   // (20) 0.01299
/*46 */     if (job->driver->resume) {                                          // (12) 0.04221
/*48 */         job->driver->resume(job);                                       // (4) 0.05195
/*50 */     }                                                                   // (16) 0.01299
/*52 */ }                                                                       // (21) 0.003247
