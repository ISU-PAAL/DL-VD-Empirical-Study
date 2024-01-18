// commit message qemu@60fe637bf0 (target=1, prob=0.51797336, correct=True): Start migrating migration code into a migration directory
/*0  */ static void get_xbzrle_cache_stats(MigrationInfo *info)                      // (8) 0.0609
/*2  */ {                                                                            // (11) 0.003205
/*4  */     if (migrate_use_xbzrle()) {                                              // (9) 0.05128
/*6  */         info->has_xbzrle_cache = true;                                       // (7) 0.0641
/*8  */         info->xbzrle_cache = g_malloc0(sizeof(*info->xbzrle_cache));         // (2) 0.109
/*10 */         info->xbzrle_cache->cache_size = migrate_xbzrle_cache_size();        // (6) 0.09936
/*12 */         info->xbzrle_cache->bytes = xbzrle_mig_bytes_transferred();          // (4) 0.1026
/*14 */         info->xbzrle_cache->pages = xbzrle_mig_pages_transferred();          // (5) 0.1026
/*16 */         info->xbzrle_cache->cache_miss = xbzrle_mig_pages_cache_miss();      // (1) 0.1122
/*18 */         info->xbzrle_cache->cache_miss_rate = xbzrle_mig_cache_miss_rate();  // (0) 0.1186
/*20 */         info->xbzrle_cache->overflow = xbzrle_mig_pages_overflow();          // (3) 0.1058
/*22 */     }                                                                        // (10) 0.01282
/*24 */ }                                                                            // (12) 0.003205
