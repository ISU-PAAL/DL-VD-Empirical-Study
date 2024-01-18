// commit message qemu@c91e681a55 (target=0, prob=0.37972116, correct=True): Add check for cache size smaller than page size
/*0  */ void qmp_migrate_set_cache_size(int64_t value, Error **errp)         // (2) 0.1348
/*2  */ {                                                                    // (9) 0.005618
/*4  */     MigrationState *s = migrate_get_current();                       // (5) 0.07865
/*8  */     /* Check for truncation */                                       // (6) 0.05056
/*10 */     if (value != (size_t)value) {                                    // (4) 0.08427
/*12 */         error_set(errp, QERR_INVALID_PARAMETER_VALUE, "cache size",  // (0) 0.1854
/*14 */                   "exceeding address space");                        // (3) 0.1348
/*16 */         return;                                                      // (7) 0.05056
/*18 */     }                                                                // (8) 0.02247
/*22 */     s->xbzrle_cache_size = xbzrle_cache_resize(value);               // (1) 0.1517
/*24 */ }                                                                    // (10) 0.005618
