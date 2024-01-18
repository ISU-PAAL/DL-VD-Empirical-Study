// commit message qemu@3ddf3efefa (target=0, prob=0.05861374, correct=True): block: Use block_job_get() in find_block_job()
/*0  */ static BlockJob *find_block_job(const char *device, AioContext **aio_context,  // (2) 0.06061
/*2  */                                 Error **errp)                                  // (0) 0.09091
/*4  */ {                                                                              // (27) 0.002525
/*6  */     BlockBackend *blk;                                                         // (16) 0.02525
/*8  */     BlockDriverState *bs;                                                      // (18) 0.02273
/*12 */     *aio_context = NULL;                                                       // (11) 0.02778
/*16 */     blk = blk_by_name(device);                                                 // (8) 0.03788
/*18 */     if (!blk) {                                                                // (19) 0.02273
/*20 */         goto notfound;                                                         // (12) 0.02778
/*22 */     }                                                                          // (22) 0.0101
/*26 */     *aio_context = blk_get_aio_context(blk);                                   // (3) 0.05556
/*28 */     aio_context_acquire(*aio_context);                                         // (6) 0.0404
/*32 */     if (!blk_is_available(blk)) {                                              // (7) 0.0404
/*34 */         goto notfound;                                                         // (13) 0.02778
/*36 */     }                                                                          // (23) 0.0101
/*38 */     bs = blk_bs(blk);                                                          // (10) 0.03535
/*42 */     if (!bs->job) {                                                            // (17) 0.02525
/*44 */         goto notfound;                                                         // (14) 0.02778
/*46 */     }                                                                          // (24) 0.0101
/*50 */     return bs->job;                                                            // (20) 0.02273
/*54 */ notfound:                                                                      // (26) 0.007576
/*56 */     error_set(errp, ERROR_CLASS_DEVICE_NOT_ACTIVE,                             // (4) 0.05556
/*58 */               "No active block job on device '%s'", device);                   // (1) 0.06818
/*60 */     if (*aio_context) {                                                        // (15) 0.02778
/*62 */         aio_context_release(*aio_context);                                     // (5) 0.04798
/*64 */         *aio_context = NULL;                                                   // (9) 0.03788
/*66 */     }                                                                          // (25) 0.0101
/*68 */     return NULL;                                                               // (21) 0.01515
/*70 */ }                                                                              // (28) 0.002525
