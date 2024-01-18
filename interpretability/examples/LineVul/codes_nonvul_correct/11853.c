// commit message qemu@621ff94d50 (target=0, prob=0.0663275, correct=True): error: Remove NULL checks on error_propagate() calls
/*0  */ static void coroutine_fn bdrv_create_co_entry(void *opaque)             // (1) 0.1329
/*2  */ {                                                                       // (10) 0.006329
/*4  */     Error *local_err = NULL;                                            // (3) 0.06962
/*6  */     int ret;                                                            // (8) 0.03797
/*10 */     CreateCo *cco = opaque;                                             // (4) 0.06962
/*12 */     assert(cco->drv);                                                   // (5) 0.06962
/*16 */     ret = cco->drv->bdrv_create(cco->filename, cco->opts, &local_err);  // (0) 0.2089
/*18 */     if (local_err) {                                                    // (6) 0.06329
/*20 */         error_propagate(&cco->err, local_err);                          // (2) 0.1329
/*22 */     }                                                                   // (9) 0.02532
/*24 */     cco->ret = ret;                                                     // (7) 0.06329
/*26 */ }                                                                       // (11) 0.006329
