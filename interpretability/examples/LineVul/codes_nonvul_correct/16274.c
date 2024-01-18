// commit message qemu@22d5cd82e9 (target=0, prob=0.019682752, correct=True): file-posix: Remove .bdrv_inactivate/invalidate_cache
/*0  */ static int raw_inactivate(BlockDriverState *bs)                          // (3) 0.08725
/*2  */ {                                                                        // (10) 0.006711
/*4  */     int ret;                                                             // (7) 0.04027
/*6  */     uint64_t perm = 0;                                                   // (4) 0.07383
/*8  */     uint64_t shared = BLK_PERM_ALL;                                      // (2) 0.1141
/*12 */     ret = raw_handle_perm_lock(bs, RAW_PL_PREPARE, perm, shared, NULL);  // (0) 0.1946
/*14 */     if (ret) {                                                           // (6) 0.05369
/*16 */         return ret;                                                      // (5) 0.06711
/*18 */     }                                                                    // (9) 0.02685
/*20 */     raw_handle_perm_lock(bs, RAW_PL_COMMIT, perm, shared, NULL);         // (1) 0.1745
/*22 */     return 0;                                                            // (8) 0.04027
/*24 */ }                                                                        // (11) 0.006711
