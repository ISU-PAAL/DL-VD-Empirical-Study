// commit message qemu@6b33f3ae8b (target=0, prob=0.48149842, correct=True): qemu-img: Improve commit invalid base message
/*0   */ static int img_commit(int argc, char **argv)                                      // (10) 0.0293
/*2   */ {                                                                                 // (32) 0.001954
/*4   */     int c, ret, flags;                                                            // (25) 0.01953
/*6   */     const char *filename, *fmt, *cache, *base;                                    // (6) 0.03516
/*8   */     BlockBackend *blk;                                                            // (24) 0.01953
/*10  */     BlockDriverState *bs, *base_bs;                                               // (12) 0.02734
/*12  */     bool progress = false, quiet = false, drop = false;                           // (8) 0.03125
/*14  */     bool writethrough;                                                            // (26) 0.01563
/*16  */     Error *local_err = NULL;                                                      // (18) 0.02149
/*18  */     CommonBlockJobCBInfo cbi;                                                     // (19) 0.02149
/*20  */     bool image_opts = false;                                                      // (20) 0.02148
/*22  */     AioContext *aio_context;                                                      // (16) 0.02344
/*26  */     fmt = NULL;                                                                   // (31) 0.01367
/*28  */     cache = BDRV_DEFAULT_CACHE;                                                   // (9) 0.03125
/*30  */     base = NULL;                                                                  // (30) 0.01367
/*32  */     for(;;) {                                                                     // (27) 0.01562
/*34  */         static const struct option long_options[] = {                             // (7) 0.0332
/*36  */             {"help", no_argument, 0, 'h'},                                        // (4) 0.04687
/*38  */             {"object", required_argument, 0, OPTION_OBJECT},                      // (3) 0.05078
/*40  */             {"image-opts", no_argument, 0, OPTION_IMAGE_OPTS},                    // (0) 0.0625
/*42  */             {0, 0, 0, 0}                                                          // (5) 0.03906
/*44  */         };                                                                        // (29) 0.01562
/*46  */         c = getopt_long(argc, argv, "f:ht:b:dpq",                                 // (1) 0.05859
/*48  */                         long_options, NULL);                                      // (2) 0.05664
/*50  */         if (c == -1) {                                                            // (11) 0.0293
/*52  */             break;                                                                // (15) 0.02539
/*54  */         }                                                                         // (28) 0.01562
/*56  */         switch(c) {                                                               // (17) 0.02344
/*58  */         case '?':                                                                 // (21) 0.02148
/*60  */         case 'h':                                                                 // (22) 0.02148
/*62  */             help();                                                               // (13) 0.02539
/*64  */             break;                                                                // (14) 0.02539
/*66  */         case 'f':                                                                 // (23) 0.02148
/*68  */             fmt = optarg;                                                         // 0.0
/*70  */             break;                                                                // 0.0
/*72  */         case 't':                                                                 // 0.0
/*74  */             cache = optarg;                                                       // 0.0
/*76  */             break;                                                                // 0.0
/*78  */         case 'b':                                                                 // 0.0
/*80  */             base = optarg;                                                        // 0.0
/*82  */             /* -b implies -d */                                                   // 0.0
/*84  */             drop = true;                                                          // 0.0
/*86  */             break;                                                                // 0.0
/*88  */         case 'd':                                                                 // 0.0
/*90  */             drop = true;                                                          // 0.0
/*92  */             break;                                                                // 0.0
/*94  */         case 'p':                                                                 // 0.0
/*96  */             progress = true;                                                      // 0.0
/*98  */             break;                                                                // 0.0
/*100 */         case 'q':                                                                 // 0.0
/*102 */             quiet = true;                                                         // 0.0
/*104 */             break;                                                                // 0.0
/*106 */         case OPTION_OBJECT: {                                                     // 0.0
/*108 */             QemuOpts *opts;                                                       // 0.0
/*110 */             opts = qemu_opts_parse_noisily(&qemu_object_opts,                     // 0.0
/*112 */                                            optarg, true);                         // 0.0
/*114 */             if (!opts) {                                                          // 0.0
/*116 */                 return 1;                                                         // 0.0
/*118 */             }                                                                     // 0.0
/*120 */         }   break;                                                                // 0.0
/*122 */         case OPTION_IMAGE_OPTS:                                                   // 0.0
/*124 */             image_opts = true;                                                    // 0.0
/*126 */             break;                                                                // 0.0
/*128 */         }                                                                         // 0.0
/*130 */     }                                                                             // 0.0
/*134 */     /* Progress is not shown in Quiet mode */                                     // 0.0
/*136 */     if (quiet) {                                                                  // 0.0
/*138 */         progress = false;                                                         // 0.0
/*140 */     }                                                                             // 0.0
/*144 */     if (optind != argc - 1) {                                                     // 0.0
/*146 */         error_exit("Expecting one image file name");                              // 0.0
/*148 */     }                                                                             // 0.0
/*150 */     filename = argv[optind++];                                                    // 0.0
/*154 */     if (qemu_opts_foreach(&qemu_object_opts,                                      // 0.0
/*156 */                           user_creatable_add_opts_foreach,                        // 0.0
/*158 */                           NULL, NULL)) {                                          // 0.0
/*160 */         return 1;                                                                 // 0.0
/*162 */     }                                                                             // 0.0
/*166 */     flags = BDRV_O_RDWR | BDRV_O_UNMAP;                                           // 0.0
/*168 */     ret = bdrv_parse_cache_mode(cache, &flags, &writethrough);                    // 0.0
/*170 */     if (ret < 0) {                                                                // 0.0
/*172 */         error_report("Invalid cache option: %s", cache);                          // 0.0
/*174 */         return 1;                                                                 // 0.0
/*176 */     }                                                                             // 0.0
/*180 */     blk = img_open(image_opts, filename, fmt, flags, writethrough, quiet);        // 0.0
/*182 */     if (!blk) {                                                                   // 0.0
/*184 */         return 1;                                                                 // 0.0
/*186 */     }                                                                             // 0.0
/*188 */     bs = blk_bs(blk);                                                             // 0.0
/*192 */     qemu_progress_init(progress, 1.f);                                            // 0.0
/*194 */     qemu_progress_print(0.f, 100);                                                // 0.0
/*198 */     if (base) {                                                                   // 0.0
/*200 */         base_bs = bdrv_find_backing_image(bs, base);                              // 0.0
/*202 */         if (!base_bs) {                                                           // 0.0
/*204 */             error_setg(&local_err, QERR_BASE_NOT_FOUND, base);                    // 0.0
/*206 */             goto done;                                                            // 0.0
/*208 */         }                                                                         // 0.0
/*210 */     } else {                                                                      // 0.0
/*212 */         /* This is different from QMP, which by default uses the deepest file in  // 0.0
/*214 */          * the backing chain (i.e., the very base); however, the traditional      // 0.0
/*216 */          * behavior of qemu-img commit is using the immediate backing file. */    // 0.0
/*218 */         base_bs = backing_bs(bs);                                                 // 0.0
/*220 */         if (!base_bs) {                                                           // 0.0
/*222 */             error_setg(&local_err, "Image does not have a backing file");         // 0.0
/*224 */             goto done;                                                            // 0.0
/*226 */         }                                                                         // 0.0
/*228 */     }                                                                             // 0.0
/*232 */     cbi = (CommonBlockJobCBInfo){                                                 // 0.0
/*234 */         .errp = &local_err,                                                       // 0.0
/*236 */         .bs   = bs,                                                               // 0.0
/*238 */     };                                                                            // 0.0
/*242 */     aio_context = bdrv_get_aio_context(bs);                                       // 0.0
/*244 */     aio_context_acquire(aio_context);                                             // 0.0
/*246 */     commit_active_start("commit", bs, base_bs, BLOCK_JOB_DEFAULT, 0,              // 0.0
/*248 */                         BLOCKDEV_ON_ERROR_REPORT, common_block_job_cb, &cbi,      // 0.0
/*250 */                         &local_err, false);                                       // 0.0
/*252 */     aio_context_release(aio_context);                                             // 0.0
/*254 */     if (local_err) {                                                              // 0.0
/*256 */         goto done;                                                                // 0.0
/*258 */     }                                                                             // 0.0
/*262 */     /* When the block job completes, the BlockBackend reference will point to     // 0.0
/*264 */      * the old backing file. In order to avoid that the top image is already      // 0.0
/*266 */      * deleted, so we can still empty it afterwards, increment the reference      // 0.0
/*268 */      * counter here preemptively. */                                              // 0.0
/*270 */     if (!drop) {                                                                  // 0.0
/*272 */         bdrv_ref(bs);                                                             // 0.0
/*274 */     }                                                                             // 0.0
/*278 */     run_block_job(bs->job, &local_err);                                           // 0.0
/*280 */     if (local_err) {                                                              // 0.0
/*282 */         goto unref_backing;                                                       // 0.0
/*284 */     }                                                                             // 0.0
/*288 */     if (!drop && bs->drv->bdrv_make_empty) {                                      // 0.0
/*290 */         ret = bs->drv->bdrv_make_empty(bs);                                       // 0.0
/*292 */         if (ret) {                                                                // 0.0
/*294 */             error_setg_errno(&local_err, -ret, "Could not empty %s",              // 0.0
/*296 */                              filename);                                           // 0.0
/*298 */             goto unref_backing;                                                   // 0.0
/*300 */         }                                                                         // 0.0
/*302 */     }                                                                             // 0.0
/*306 */ unref_backing:                                                                    // 0.0
/*308 */     if (!drop) {                                                                  // 0.0
/*310 */         bdrv_unref(bs);                                                           // 0.0
/*312 */     }                                                                             // 0.0
/*316 */ done:                                                                             // 0.0
/*318 */     qemu_progress_end();                                                          // 0.0
/*322 */     blk_unref(blk);                                                               // 0.0
/*326 */     if (local_err) {                                                              // 0.0
/*328 */         error_report_err(local_err);                                              // 0.0
/*330 */         return 1;                                                                 // 0.0
/*332 */     }                                                                             // 0.0
/*336 */     qprintf(quiet, "Image committed.\n");                                         // 0.0
/*338 */     return 0;                                                                     // 0.0
/*340 */ }                                                                                 // 0.0
