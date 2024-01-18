// commit message qemu@3d5d319e12 (target=1, prob=0.052558262, correct=False): blockjob: Make block_job_pause_all() keep a reference to the jobs
/*0  */ void block_job_resume_all(void)                                   // (5) 0.08276
/*2  */ {                                                                 // (8) 0.006897
/*4  */     BlockJob *job = NULL;                                         // (6) 0.06897
/*6  */     while ((job = block_job_next(job))) {                         // (4) 0.1103
/*8  */         AioContext *aio_context = blk_get_aio_context(job->blk);  // (0) 0.2138
/*12 */         aio_context_acquire(aio_context);                         // (1) 0.1379
/*14 */         block_job_resume(job);                                    // (3) 0.1103
/*16 */         aio_context_release(aio_context);                         // (2) 0.131
/*18 */     }                                                             // (7) 0.02759
/*20 */ }                                                                 // (9) 0.006897
