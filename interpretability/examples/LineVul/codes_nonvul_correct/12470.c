// commit message qemu@d7651f150d (target=0, prob=0.24841622, correct=True): migration: pass MigrationIncomingState* into migration check functions
/*0  */ static bool migrate_caps_check(bool *cap_list,                                // (16) 0.02734
/*2  */                                MigrationCapabilityStatusList *params,         // (0) 0.07422
/*4  */                                Error **errp)                                  // (1) 0.06836
/*6  */ {                                                                             // (23) 0.001953
/*8  */     MigrationCapabilityStatusList *cap;                                       // (17) 0.02148
/*10 */     bool old_postcopy_cap;                                                    // (18) 0.02148
/*14 */     old_postcopy_cap = cap_list[MIGRATION_CAPABILITY_POSTCOPY_RAM];           // (4) 0.05859
/*18 */     for (cap = params; cap; cap = cap->next) {                                // (14) 0.03516
/*20 */         cap_list[cap->value->capability] = cap->value->state;                 // (8) 0.04883
/*22 */     }                                                                         // (20) 0.007812
/*26 */ #ifndef CONFIG_LIVE_BLOCK_MIGRATION                                           // (15) 0.03125
/*28 */     if (cap_list[MIGRATION_CAPABILITY_BLOCK]) {                               // (9) 0.04297
/*30 */         error_setg(errp, "QEMU compiled without old-style (blk/-b, inc/-i) "  // (2) 0.06836
/*32 */                    "block migration");                                        // (10) 0.04297
/*34 */         error_append_hint(errp, "Use drive_mirror+NBD instead.\n");           // (3) 0.06055
/*36 */         return false;                                                         // (19) 0.01953
/*38 */     }                                                                         // (21) 0.007812
/*40 */ #endif                                                                        // (22) 0.003906
/*44 */     if (cap_list[MIGRATION_CAPABILITY_POSTCOPY_RAM]) {                        // (6) 0.05078
/*46 */         if (cap_list[MIGRATION_CAPABILITY_COMPRESS]) {                        // (7) 0.05078
/*48 */             /* The decompression threads asynchronously write into RAM        // (11) 0.04297
/*50 */              * rather than use the atomic copies needed to avoid              // (12) 0.04297
/*52 */              * userfaulting.  It should be possible to fix the decompression  // (5) 0.05469
/*54 */              * threads for compatibility in future.                           // (13) 0.03711
/*56 */              */                                                               // 0.0
/*58 */             error_setg(errp, "Postcopy is not currently compatible "          // 0.0
/*60 */                        "with compression");                                   // 0.0
/*62 */             return false;                                                     // 0.0
/*64 */         }                                                                     // 0.0
/*68 */         /* This check is reasonably expensive, so only when it's being        // 0.0
/*70 */          * set the first time, also it's only the destination that needs      // 0.0
/*72 */          * special support.                                                   // 0.0
/*74 */          */                                                                   // 0.0
/*76 */         if (!old_postcopy_cap && runstate_check(RUN_STATE_INMIGRATE) &&       // 0.0
/*78 */             !postcopy_ram_supported_by_host()) {                              // 0.0
/*80 */             /* postcopy_ram_supported_by_host will have emitted a more        // 0.0
/*82 */              * detailed message                                               // 0.0
/*84 */              */                                                               // 0.0
/*86 */             error_setg(errp, "Postcopy is not supported");                    // 0.0
/*88 */             return false;                                                     // 0.0
/*90 */         }                                                                     // 0.0
/*92 */     }                                                                         // 0.0
/*96 */     return true;                                                              // 0.0
/*98 */ }                                                                             // 0.0
