// commit message qemu@7e39d3a2dd (target=1, prob=0.99922705, correct=True): blkverify: Fix BDS leak in .bdrv_open error path
/*0  */ static int blkverify_open(BlockDriverState *bs, QDict *options, int flags,   // (7) 0.04688
/*2  */                           Error **errp)                                      // (4) 0.05859
/*4  */ {                                                                            // (22) 0.001953
/*6  */     BDRVBlkverifyState *s = bs->opaque;                                      // (8) 0.03906
/*8  */     QemuOpts *opts;                                                          // (13) 0.02344
/*10 */     Error *local_err = NULL;                                                 // (14) 0.02148
/*12 */     int ret;                                                                 // (21) 0.01172
/*16 */     opts = qemu_opts_create(&runtime_opts, NULL, 0, &error_abort);           // (5) 0.05859
/*18 */     qemu_opts_absorb_qdict(opts, options, &local_err);                       // (6) 0.05078
/*20 */     if (local_err) {                                                         // (17) 0.01953
/*22 */         error_propagate(errp, local_err);                                    // (9) 0.03711
/*24 */         ret = -EINVAL;                                                       // (11) 0.02734
/*26 */         goto fail;                                                           // (16) 0.01953
/*31 */     /* Open the raw file */                                                  // (19) 0.01758
/*33 */     bs->file = bdrv_open_child(qemu_opt_get(opts, "x-raw"), options, "raw",  // (2) 0.07227
/*35 */                                bs, &child_file, false, &local_err);          // (1) 0.08789
/*37 */     if (local_err) {                                                         // (18) 0.01953
/*39 */         ret = -EINVAL;                                                       // (12) 0.02734
/*41 */         error_propagate(errp, local_err);                                    // (10) 0.03711
/*43 */         goto fail;                                                           // (15) 0.01953
/*48 */     /* Open the test file */                                                 // (20) 0.01758
/*50 */     s->test_file = bdrv_open_child(qemu_opt_get(opts, "x-image"), options,   // (3) 0.06836
/*52 */                                    "test", bs, &child_format, false,         // (0) 0.0918
/*54 */                                    &local_err);                              // 0.0
/*56 */     if (local_err) {                                                         // 0.0
/*58 */         ret = -EINVAL;                                                       // 0.0
/*60 */         error_propagate(errp, local_err);                                    // 0.0
/*62 */         goto fail;                                                           // 0.0
/*67 */     ret = 0;                                                                 // 0.0
/*69 */ fail:                                                                        // 0.0
/*74 */     qemu_opts_del(opts);                                                     // 0.0
/*76 */     return ret;                                                              // 0.0
