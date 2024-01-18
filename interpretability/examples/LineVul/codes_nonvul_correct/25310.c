// commit message qemu@554b614765 (target=0, prob=0.3627958, correct=True): block: Add QMP support for streaming to an intermediate layer
/*0   */ void qmp_block_stream(bool has_job_id, const char *job_id, const char *device,    // (5) 0.05273
/*2   */                       bool has_base, const char *base,                            // (4) 0.06055
/*4   */                       bool has_backing_file, const char *backing_file,            // (0) 0.07227
/*6   */                       bool has_speed, int64_t speed,                              // (3) 0.0625
/*8   */                       bool has_on_error, BlockdevOnError on_error,                // (1) 0.07031
/*10  */                       Error **errp)                                               // (6) 0.05078
/*12  */ {                                                                                 // (26) 0.001953
/*14  */     BlockDriverState *bs;                                                         // (20) 0.01758
/*16  */     BlockDriverState *base_bs = NULL;                                             // (13) 0.02539
/*18  */     AioContext *aio_context;                                                      // (16) 0.02344
/*20  */     Error *local_err = NULL;                                                      // (17) 0.02148
/*22  */     const char *base_name = NULL;                                                 // (15) 0.02344
/*26  */     if (!has_on_error) {                                                          // (14) 0.02344
/*28  */         on_error = BLOCKDEV_ON_ERROR_REPORT;                                      // (8) 0.04297
/*30  */     }                                                                             // (23) 0.007812
/*34  */     bs = qmp_get_root_bs(device, errp);                                           // (10) 0.03906
/*36  */     if (!bs) {                                                                    // (22) 0.01562
/*38  */         return;                                                                   // (21) 0.01758
/*40  */     }                                                                             // (25) 0.007812
/*44  */     aio_context = bdrv_get_aio_context(bs);                                       // (9) 0.04102
/*46  */     aio_context_acquire(aio_context);                                             // (11) 0.03125
/*50  */     if (bdrv_op_is_blocked(bs, BLOCK_OP_TYPE_STREAM, errp)) {                     // (2) 0.0625
/*52  */         goto out;                                                                 // (18) 0.01953
/*54  */     }                                                                             // (24) 0.007812
/*58  */     if (has_base) {                                                               // (19) 0.01953
/*60  */         base_bs = bdrv_find_backing_image(bs, base);                              // (7) 0.05078
/*62  */         if (base_bs == NULL) {                                                    // (12) 0.03125
/*64  */             error_setg(errp, QERR_BASE_NOT_FOUND, base);                          // 0.0
/*66  */             goto out;                                                             // 0.0
/*68  */         }                                                                         // 0.0
/*70  */         assert(bdrv_get_aio_context(base_bs) == aio_context);                     // 0.0
/*72  */         base_name = base;                                                         // 0.0
/*74  */     }                                                                             // 0.0
/*78  */     /* if we are streaming the entire chain, the result will have no backing      // 0.0
/*80  */      * file, and specifying one is therefore an error */                          // 0.0
/*82  */     if (base_bs == NULL && has_backing_file) {                                    // 0.0
/*84  */         error_setg(errp, "backing file specified, but streaming the "             // 0.0
/*86  */                          "entire chain");                                         // 0.0
/*88  */         goto out;                                                                 // 0.0
/*90  */     }                                                                             // 0.0
/*94  */     /* backing_file string overrides base bs filename */                          // 0.0
/*96  */     base_name = has_backing_file ? backing_file : base_name;                      // 0.0
/*100 */     stream_start(has_job_id ? job_id : NULL, bs, base_bs, base_name,              // 0.0
/*102 */                  has_speed ? speed : 0, on_error, block_job_cb, bs, &local_err);  // 0.0
/*104 */     if (local_err) {                                                              // 0.0
/*106 */         error_propagate(errp, local_err);                                         // 0.0
/*108 */         goto out;                                                                 // 0.0
/*110 */     }                                                                             // 0.0
/*114 */     trace_qmp_block_stream(bs, bs->job);                                          // 0.0
/*118 */ out:                                                                              // 0.0
/*120 */     aio_context_release(aio_context);                                             // 0.0
/*122 */ }                                                                                 // 0.0
