// commit message qemu@dde3a21840 (target=1, prob=0.2530356, correct=False): hmp: migrate command (without -d) now blocks correctly
/*0  */ static void hmp_migrate_status_cb(void *opaque)                                   // (9) 0.03753
/*2  */ {                                                                                 // (25) 0.002208
/*4  */     MigrationStatus *status = opaque;                                             // (19) 0.02208
/*6  */     MigrationInfo *info;                                                          // (20) 0.01766
/*10 */     info = qmp_query_migrate(NULL);                                               // (12) 0.03311
/*12 */     if (!info->has_status || strcmp(info->status, "active") == 0) {               // (3) 0.05519
/*14 */         if (info->has_disk) {                                                     // (10) 0.03532
/*16 */             int progress;                                                         // (14) 0.03091
/*20 */             if (info->disk->remaining) {                                          // (5) 0.04636
/*22 */                 progress = info->disk->transferred * 100 / info->disk->total;     // (1) 0.07064
/*24 */             } else {                                                              // (15) 0.03091
/*26 */                 progress = 100;                                                   // (6) 0.04194
/*28 */             }                                                                     // (18) 0.02649
/*32 */             monitor_printf(status->mon, "Completed %d %%\r", progress);           // (2) 0.06402
/*34 */             monitor_flush(status->mon);                                           // (7) 0.04194
/*36 */         }                                                                         // (21) 0.01766
/*40 */         timer_mod(status->timer, qemu_clock_get_ms(QEMU_CLOCK_REALTIME) + 1000);  // (0) 0.08609
/*42 */     } else {                                                                      // (23) 0.01325
/*44 */         if (status->is_block_migration) {                                         // (8) 0.04194
/*46 */             monitor_printf(status->mon, "\n");                                    // (4) 0.04857
/*48 */         }                                                                         // (22) 0.01766
/*50 */         monitor_resume(status->mon);                                              // (11) 0.03532
/*52 */         timer_del(status->timer);                                                 // (13) 0.03311
/*54 */         g_free(status);                                                           // (17) 0.0287
/*56 */     }                                                                             // (24) 0.00883
/*60 */     qapi_free_MigrationInfo(info);                                                // (16) 0.03091
/*62 */ }                                                                                 // (26) 0.002208
