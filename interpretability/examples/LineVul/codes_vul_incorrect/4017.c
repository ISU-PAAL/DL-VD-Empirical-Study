// commit message qemu@84593a0807 (target=1, prob=0.4655224, correct=False): migration: clean up xbzrle cache init/destroy
/*0   */ static int ram_init_all(RAMState **rsp)                                   // (19) 0.02734
/*2   */ {                                                                         // (24) 0.001953
/*4   */     Error *local_err = NULL;                                              // (20) 0.02148
/*8   */     if (ram_state_init(rsp)) {                                            // (17) 0.0293
/*10  */         return -1;                                                        // (21) 0.02148
/*12  */     }                                                                     // (23) 0.007813
/*16  */     if (migrate_use_xbzrle()) {                                           // (16) 0.03125
/*18  */         XBZRLE_cache_lock();                                              // (13) 0.0332
/*20  */         XBZRLE.zero_target_page = g_malloc0(TARGET_PAGE_SIZE);            // (2) 0.06445
/*22  */         XBZRLE.cache = cache_init(migrate_xbzrle_cache_size(),            // (3) 0.06055
/*24  */                                   TARGET_PAGE_SIZE, &local_err);          // (0) 0.08984
/*26  */         if (!XBZRLE.cache) {                                              // (10) 0.03516
/*28  */             XBZRLE_cache_unlock();                                        // (4) 0.04297
/*30  */             error_report_err(local_err);                                  // (6) 0.04102
/*32  */             g_free(*rsp);                                                 // (11) 0.03516
/*34  */             *rsp = NULL;                                                  // (14) 0.0332
/*36  */             return -1;                                                    // (18) 0.0293
/*38  */         }                                                                 // (22) 0.01562
/*40  */         XBZRLE_cache_unlock();                                            // (9) 0.03516
/*44  */         /* We prefer not to abort if there is no memory */                // (8) 0.03711
/*46  */         XBZRLE.encoded_buf = g_try_malloc0(TARGET_PAGE_SIZE);             // (1) 0.06641
/*48  */         if (!XBZRLE.encoded_buf) {                                        // (7) 0.04102
/*50  */             error_report("Error allocating encoded_buf");                 // (5) 0.04297
/*52  */             g_free(*rsp);                                                 // (12) 0.03516
/*54  */             *rsp = NULL;                                                  // (15) 0.0332
/*56  */             return -1;                                                    // 0.0
/*58  */         }                                                                 // 0.0
/*62  */         XBZRLE.current_buf = g_try_malloc(TARGET_PAGE_SIZE);              // 0.0
/*64  */         if (!XBZRLE.current_buf) {                                        // 0.0
/*66  */             error_report("Error allocating current_buf");                 // 0.0
/*68  */             g_free(XBZRLE.encoded_buf);                                   // 0.0
/*70  */             XBZRLE.encoded_buf = NULL;                                    // 0.0
/*72  */             g_free(*rsp);                                                 // 0.0
/*74  */             *rsp = NULL;                                                  // 0.0
/*76  */             return -1;                                                    // 0.0
/*78  */         }                                                                 // 0.0
/*80  */     }                                                                     // 0.0
/*84  */     /* For memory_global_dirty_log_start below.  */                       // 0.0
/*86  */     qemu_mutex_lock_iothread();                                           // 0.0
/*90  */     qemu_mutex_lock_ramlist();                                            // 0.0
/*92  */     rcu_read_lock();                                                      // 0.0
/*96  */     /* Skip setting bitmap if there is no RAM */                          // 0.0
/*98  */     if (ram_bytes_total()) {                                              // 0.0
/*100 */         RAMBlock *block;                                                  // 0.0
/*104 */         QLIST_FOREACH_RCU(block, &ram_list.blocks, next) {                // 0.0
/*106 */             unsigned long pages = block->max_length >> TARGET_PAGE_BITS;  // 0.0
/*110 */             block->bmap = bitmap_new(pages);                              // 0.0
/*112 */             bitmap_set(block->bmap, 0, pages);                            // 0.0
/*114 */             if (migrate_postcopy_ram()) {                                 // 0.0
/*116 */                 block->unsentmap = bitmap_new(pages);                     // 0.0
/*118 */                 bitmap_set(block->unsentmap, 0, pages);                   // 0.0
/*120 */             }                                                             // 0.0
/*122 */         }                                                                 // 0.0
/*124 */     }                                                                     // 0.0
/*128 */     memory_global_dirty_log_start();                                      // 0.0
/*130 */     migration_bitmap_sync(*rsp);                                          // 0.0
/*132 */     qemu_mutex_unlock_ramlist();                                          // 0.0
/*134 */     qemu_mutex_unlock_iothread();                                         // 0.0
/*136 */     rcu_read_unlock();                                                    // 0.0
/*140 */     return 0;                                                             // 0.0
/*142 */ }                                                                         // 0.0
