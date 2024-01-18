// commit message qemu@8ae8e904fc (target=1, prob=0.074653685, correct=False): blockdev: Fail blockdev-add with encrypted images
/*0  */ void qmp_blockdev_add(BlockdevOptions *options, Error **errp)                   // (9) 0.03906
/*2  */ {                                                                               // (29) 0.001953
/*4  */     QmpOutputVisitor *ov = qmp_output_visitor_new();                            // (8) 0.04102
/*6  */     QObject *obj;                                                               // (23) 0.01563
/*8  */     QDict *qdict;                                                               // (19) 0.01953
/*10 */     Error *local_err = NULL;                                                    // (18) 0.02148
/*14 */     /* Require an ID in the top level */                                        // (15) 0.02539
/*16 */     if (!options->has_id) {                                                     // (16) 0.02344
/*18 */         error_setg(errp, "Block device needs an ID");                           // (6) 0.04297
/*20 */         goto fail;                                                              // (20) 0.01953
/*22 */     }                                                                           // (26) 0.007812
/*26 */     /* TODO Sort it out in raw-posix and drive_init: Reject aio=native with     // (3) 0.05078
/*28 */      * cache.direct=false instead of silently switching to aio=threads, except  // (7) 0.04297
/*30 */      * if called from drive_init.                                               // (17) 0.02344
/*32 */      *                                                                          // (25) 0.009766
/*34 */      * For now, simply forbidding the combination for all drivers will do. */   // (10) 0.03906
/*36 */     if (options->has_aio && options->aio == BLOCKDEV_AIO_OPTIONS_NATIVE) {      // (1) 0.0625
/*38 */         bool direct = options->cache->has_direct && options->cache->direct;     // (4) 0.04687
/*40 */         if (!options->has_cache && !direct) {                                   // (12) 0.03711
/*42 */             error_setg(errp, "aio=native requires cache.direct=true");          // (2) 0.06055
/*44 */             goto fail;                                                          // (14) 0.02734
/*46 */         }                                                                       // (24) 0.01562
/*48 */     }                                                                           // (27) 0.007812
/*52 */     visit_type_BlockdevOptions(qmp_output_get_visitor(ov),                      // (5) 0.04492
/*54 */                                &options, NULL, &local_err);                     // (0) 0.07812
/*56 */     if (local_err) {                                                            // (22) 0.01953
/*58 */         error_propagate(errp, local_err);                                       // (11) 0.03711
/*60 */         goto fail;                                                              // (21) 0.01953
/*62 */     }                                                                           // (28) 0.007812
/*66 */     obj = qmp_output_get_qobject(ov);                                           // (13) 0.0332
/*68 */     qdict = qobject_to_qdict(obj);                                              // 0.0
/*72 */     qdict_flatten(qdict);                                                       // 0.0
/*76 */     blockdev_init(NULL, qdict, &local_err);                                     // 0.0
/*78 */     if (local_err) {                                                            // 0.0
/*80 */         error_propagate(errp, local_err);                                       // 0.0
/*82 */         goto fail;                                                              // 0.0
/*84 */     }                                                                           // 0.0
/*88 */ fail:                                                                           // 0.0
/*90 */     qmp_output_visitor_cleanup(ov);                                             // 0.0
/*92 */ }                                                                               // 0.0
