// commit message qemu@3d948cdf37 (target=0, prob=0.045852356, correct=True): block: acquire AioContext in generic blockjob QMP commands
/*0  */ void qmp_block_job_set_speed(const char *device, int64_t speed, Error **errp)  // (1) 0.2137
/*2  */ {                                                                              // (7) 0.007634
/*4  */     BlockJob *job = find_block_job(device);                                    // (3) 0.1221
/*8  */     if (!job) {                                                                // (5) 0.06107
/*10 */         error_set(errp, QERR_BLOCK_JOB_NOT_ACTIVE, device);                    // (0) 0.2366
/*12 */         return;                                                                // (4) 0.0687
/*14 */     }                                                                          // (6) 0.03053
/*18 */     block_job_set_speed(job, speed, errp);                                     // (2) 0.1374
/*20 */ }                                                                              // (8) 0.007634
