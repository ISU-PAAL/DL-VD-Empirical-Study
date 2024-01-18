// commit message qemu@60fe637bf0 (target=1, prob=0.5483343, correct=True): Start migrating migration code into a migration directory
/*0  */ MigrationState *migrate_get_current(void)                 // (4) 0.09353
/*2  */ {                                                         // (8) 0.007194
/*4  */     static MigrationState current_migration = {           // (5) 0.08633
/*6  */         .state = MIG_STATE_NONE,                          // (2) 0.1295
/*8  */         .bandwidth_limit = MAX_THROTTLE,                  // (1) 0.1439
/*10 */         .xbzrle_cache_size = DEFAULT_MIGRATE_CACHE_SIZE,  // (0) 0.223
/*12 */         .mbps = -1,                                       // (3) 0.1007
/*14 */     };                                                    // (7) 0.02878
/*18 */     return &current_migration;                            // (6) 0.07194
/*20 */ }                                                         // (9) 0.007194
