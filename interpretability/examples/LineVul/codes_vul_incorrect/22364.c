// commit message qemu@60fe637bf0 (target=1, prob=0.35479397, correct=False): Start migrating migration code into a migration directory
/*0   */ MigrationInfo *qmp_query_migrate(Error **errp)                      // (12) 0.0332
/*2   */ {                                                                   // (28) 0.001953
/*4   */     MigrationInfo *info = g_malloc0(sizeof(*info));                 // (5) 0.03711
/*6   */     MigrationState *s = migrate_get_current();                      // (19) 0.02734
/*10  */     switch (s->state) {                                             // (25) 0.01953
/*12  */     case MIG_STATE_NONE:                                            // (22) 0.02344
/*14  */         /* no migration has happened ever */                        // (20) 0.02734
/*16  */         break;                                                      // (26) 0.01758
/*18  */     case MIG_STATE_SETUP:                                           // (23) 0.02344
/*20  */         info->has_status = true;                                    // (17) 0.0293
/*22  */         info->status = g_strdup("setup");                           // (6) 0.03711
/*24  */         info->has_total_time = false;                               // (13) 0.0332
/*26  */         break;                                                      // (27) 0.01758
/*28  */     case MIG_STATE_ACTIVE:                                          // (24) 0.02344
/*30  */     case MIG_STATE_CANCELLING:                                      // (21) 0.02734
/*32  */         info->has_status = true;                                    // (18) 0.0293
/*34  */         info->status = g_strdup("active");                          // (8) 0.03711
/*36  */         info->has_total_time = true;                                // (14) 0.0332
/*38  */         info->total_time = qemu_clock_get_ms(QEMU_CLOCK_REALTIME)   // (0) 0.06641
/*40  */             - s->total_time;                                        // (11) 0.03516
/*42  */         info->has_expected_downtime = true;                         // (9) 0.03711
/*44  */         info->expected_downtime = s->expected_downtime;             // (2) 0.04492
/*46  */         info->has_setup_time = true;                                // (15) 0.0332
/*48  */         info->setup_time = s->setup_time;                           // (10) 0.03711
/*52  */         info->has_ram = true;                                       // (16) 0.0293
/*54  */         info->ram = g_malloc0(sizeof(*info->ram));                  // (1) 0.04687
/*56  */         info->ram->transferred = ram_bytes_transferred();           // (3) 0.04102
/*58  */         info->ram->remaining = ram_bytes_remaining();               // (4) 0.04102
/*60  */         info->ram->total = ram_bytes_total();                       // (7) 0.03711
/*62  */         info->ram->duplicate = dup_mig_pages_transferred();         // 0.0
/*64  */         info->ram->skipped = skipped_mig_pages_transferred();       // 0.0
/*66  */         info->ram->normal = norm_mig_pages_transferred();           // 0.0
/*68  */         info->ram->normal_bytes = norm_mig_bytes_transferred();     // 0.0
/*70  */         info->ram->dirty_pages_rate = s->dirty_pages_rate;          // 0.0
/*72  */         info->ram->mbps = s->mbps;                                  // 0.0
/*74  */         info->ram->dirty_sync_count = s->dirty_sync_count;          // 0.0
/*78  */         if (blk_mig_active()) {                                     // 0.0
/*80  */             info->has_disk = true;                                  // 0.0
/*82  */             info->disk = g_malloc0(sizeof(*info->disk));            // 0.0
/*84  */             info->disk->transferred = blk_mig_bytes_transferred();  // 0.0
/*86  */             info->disk->remaining = blk_mig_bytes_remaining();      // 0.0
/*88  */             info->disk->total = blk_mig_bytes_total();              // 0.0
/*90  */         }                                                           // 0.0
/*94  */         get_xbzrle_cache_stats(info);                               // 0.0
/*96  */         break;                                                      // 0.0
/*98  */     case MIG_STATE_COMPLETED:                                       // 0.0
/*100 */         get_xbzrle_cache_stats(info);                               // 0.0
/*104 */         info->has_status = true;                                    // 0.0
/*106 */         info->status = g_strdup("completed");                       // 0.0
/*108 */         info->has_total_time = true;                                // 0.0
/*110 */         info->total_time = s->total_time;                           // 0.0
/*112 */         info->has_downtime = true;                                  // 0.0
/*114 */         info->downtime = s->downtime;                               // 0.0
/*116 */         info->has_setup_time = true;                                // 0.0
/*118 */         info->setup_time = s->setup_time;                           // 0.0
/*122 */         info->has_ram = true;                                       // 0.0
/*124 */         info->ram = g_malloc0(sizeof(*info->ram));                  // 0.0
/*126 */         info->ram->transferred = ram_bytes_transferred();           // 0.0
/*128 */         info->ram->remaining = 0;                                   // 0.0
/*130 */         info->ram->total = ram_bytes_total();                       // 0.0
/*132 */         info->ram->duplicate = dup_mig_pages_transferred();         // 0.0
/*134 */         info->ram->skipped = skipped_mig_pages_transferred();       // 0.0
/*136 */         info->ram->normal = norm_mig_pages_transferred();           // 0.0
/*138 */         info->ram->normal_bytes = norm_mig_bytes_transferred();     // 0.0
/*140 */         info->ram->mbps = s->mbps;                                  // 0.0
/*142 */         info->ram->dirty_sync_count = s->dirty_sync_count;          // 0.0
/*144 */         break;                                                      // 0.0
/*146 */     case MIG_STATE_ERROR:                                           // 0.0
/*148 */         info->has_status = true;                                    // 0.0
/*150 */         info->status = g_strdup("failed");                          // 0.0
/*152 */         break;                                                      // 0.0
/*154 */     case MIG_STATE_CANCELLED:                                       // 0.0
/*156 */         info->has_status = true;                                    // 0.0
/*158 */         info->status = g_strdup("cancelled");                       // 0.0
/*160 */         break;                                                      // 0.0
/*162 */     }                                                               // 0.0
/*166 */     return info;                                                    // 0.0
/*168 */ }                                                                   // 0.0
