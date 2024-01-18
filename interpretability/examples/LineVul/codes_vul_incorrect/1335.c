// commit message qemu@f3e4ce4af3 (target=1, prob=0.31515846, correct=False): blockjob: Track job ratelimits via bytes, not sectors
/*0  */ static void commit_set_speed(BlockJob *job, int64_t speed, Error **errp)   // (2) 0.1644
/*2  */ {                                                                          // (7) 0.006849
/*4  */     CommitBlockJob *s = container_of(job, CommitBlockJob, common);         // (3) 0.1438
/*8  */     if (speed < 0) {                                                       // (4) 0.06849
/*10 */         error_setg(errp, QERR_INVALID_PARAMETER, "speed");                 // (0) 0.2123
/*12 */         return;                                                            // (5) 0.06164
/*14 */     }                                                                      // (6) 0.0274
/*16 */     ratelimit_set_speed(&s->limit, speed / BDRV_SECTOR_SIZE, SLICE_TIME);  // (1) 0.2123
/*18 */ }                                                                          // (8) 0.006849
