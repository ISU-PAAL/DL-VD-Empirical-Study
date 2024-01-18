// commit message qemu@430b26a82d (target=0, prob=0.43617117, correct=True): blkdebug: Add ability to override unmap geometries
/*0   */ static int blkdebug_open(BlockDriverState *bs, QDict *options, int flags,        // (6) 0.04492
/*2   */                          Error **errp)                                           // (4) 0.05664
/*4   */ {                                                                                // (29) 0.001953
/*6   */     BDRVBlkdebugState *s = bs->opaque;                                           // (8) 0.03711
/*8   */     QemuOpts *opts;                                                              // (14) 0.02344
/*10  */     Error *local_err = NULL;                                                     // (15) 0.02148
/*12  */     int ret;                                                                     // (25) 0.01172
/*16  */     opts = qemu_opts_create(&runtime_opts, NULL, 0, &error_abort);               // (2) 0.05859
/*18  */     qemu_opts_absorb_qdict(opts, options, &local_err);                           // (5) 0.05078
/*20  */     if (local_err) {                                                             // (16) 0.01953
/*22  */         error_propagate(errp, local_err);                                        // (9) 0.03711
/*24  */         ret = -EINVAL;                                                           // (12) 0.02734
/*26  */         goto out;                                                                // (17) 0.01953
/*28  */     }                                                                            // (26) 0.007812
/*32  */     /* Read rules from config file or command line options */                    // (11) 0.02734
/*34  */     s->config_file = g_strdup(qemu_opt_get(opts, "config"));                     // (3) 0.05859
/*36  */     ret = read_config(s, s->config_file, options, errp);                         // (7) 0.04297
/*38  */     if (ret) {                                                                   // (23) 0.01562
/*40  */         goto out;                                                                // (18) 0.01953
/*42  */     }                                                                            // (27) 0.007812
/*46  */     /* Set initial state */                                                      // (24) 0.01562
/*48  */     s->state = 1;                                                                // (22) 0.01758
/*52  */     /* Open the image file */                                                    // (21) 0.01758
/*54  */     bs->file = bdrv_open_child(qemu_opt_get(opts, "x-image"), options, "image",  // (1) 0.07227
/*56  */                                bs, &child_file, false, &local_err);              // (0) 0.08789
/*58  */     if (local_err) {                                                             // (19) 0.01953
/*60  */         ret = -EINVAL;                                                           // (13) 0.02734
/*62  */         error_propagate(errp, local_err);                                        // (10) 0.03711
/*64  */         goto out;                                                                // (20) 0.01953
/*66  */     }                                                                            // (28) 0.007812
/*70  */     bs->supported_write_flags = BDRV_REQ_FUA &                                   // 0.0
/*72  */         bs->file->bs->supported_write_flags;                                     // 0.0
/*74  */     bs->supported_zero_flags = (BDRV_REQ_FUA | BDRV_REQ_MAY_UNMAP) &             // 0.0
/*76  */         bs->file->bs->supported_zero_flags;                                      // 0.0
/*78  */     ret = -EINVAL;                                                               // 0.0
/*82  */     /* Set request alignment */                                                  // 0.0
/*84  */     s->align = qemu_opt_get_size(opts, "align", 0);                              // 0.0
/*86  */     if (s->align && (s->align >= INT_MAX || !is_power_of_2(s->align))) {         // 0.0
/*88  */         error_setg(errp, "Cannot meet constraints with align %" PRIu64,          // 0.0
/*90  */                    s->align);                                                    // 0.0
/*92  */         goto out;                                                                // 0.0
/*94  */     }                                                                            // 0.0
/*98  */     ret = 0;                                                                     // 0.0
/*100 */ out:                                                                             // 0.0
/*102 */     if (ret < 0) {                                                               // 0.0
/*104 */         g_free(s->config_file);                                                  // 0.0
/*106 */     }                                                                            // 0.0
/*108 */     qemu_opts_del(opts);                                                         // 0.0
/*110 */     return ret;                                                                  // 0.0
/*112 */ }                                                                                // 0.0
