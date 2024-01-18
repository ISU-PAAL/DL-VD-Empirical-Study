// commit message qemu@e0ef439588 (target=1, prob=0.99906284, correct=True): blkdebug: Sanity check block layer guarantees
/*0  */ blkdebug_co_preadv(BlockDriverState *bs, uint64_t offset, uint64_t bytes,  // (1) 0.09747
/*1  */                    QEMUIOVector *qiov, int flags)                          // (0) 0.1083
/*2  */ {                                                                          // (13) 0.00361
/*3  */     BDRVBlkdebugState *s = bs->opaque;                                     // (6) 0.06859
/*4  */     BlkdebugRule *rule = NULL;                                             // (11) 0.04332
/*5  */     QSIMPLEQ_FOREACH(rule, &s->active_rules, active_next) {                // (4) 0.09025
/*6  */         uint64_t inject_offset = rule->options.inject.offset;              // (5) 0.08664
/*7  */         if (inject_offset == -1 ||                                         // (8) 0.06137
/*8  */             (inject_offset >= offset && inject_offset < offset + bytes))   // (2) 0.09747
/*9  */         {                                                                  // (12) 0.02888
/*10 */             break;                                                         // (10) 0.04693
/*11 */     if (rule && rule->options.inject.error) {                              // (7) 0.06137
/*12 */         return inject_error(bs, rule);                                     // (9) 0.05776
/*13 */     return bdrv_co_preadv(bs->file, offset, bytes, qiov, flags);           // (3) 0.09386
