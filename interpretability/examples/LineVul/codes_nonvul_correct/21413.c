// commit message qemu@01fa559826 (target=0, prob=0.2740492, correct=True): migration: Use JSON null instead of "" to reset parameter to default
/*0   */ static void migrate_params_test_apply(MigrateSetParameters *params,     // (11) 0.0332
/*2   */                                       MigrationParameters *dest)        // (0) 0.08203
/*4   */ {                                                                       // (28) 0.001953
/*6   */     *dest = migrate_get_current()->parameters;                          // (15) 0.03125
/*10  */     /* TODO use QAPI_CLONE() instead of duplicating it inline */        // (9) 0.03906
/*14  */     if (params->has_compress_level) {                                   // (18) 0.0293
/*16  */         dest->compress_level = params->compress_level;                  // (7) 0.04102
/*18  */     }                                                                   // (22) 0.007812
/*22  */     if (params->has_compress_threads) {                                 // (16) 0.03125
/*24  */         dest->compress_threads = params->compress_threads;              // (6) 0.04492
/*26  */     }                                                                   // (23) 0.007812
/*30  */     if (params->has_decompress_threads) {                               // (13) 0.0332
/*32  */         dest->decompress_threads = params->decompress_threads;          // (4) 0.04883
/*34  */     }                                                                   // (24) 0.007812
/*38  */     if (params->has_cpu_throttle_initial) {                             // (14) 0.0332
/*40  */         dest->cpu_throttle_initial = params->cpu_throttle_initial;      // (5) 0.04883
/*42  */     }                                                                   // (21) 0.007812
/*46  */     if (params->has_cpu_throttle_increment) {                           // (10) 0.03516
/*48  */         dest->cpu_throttle_increment = params->cpu_throttle_increment;  // (3) 0.05273
/*50  */     }                                                                   // (25) 0.007812
/*54  */     if (params->has_tls_creds) {                                        // (12) 0.0332
/*56  */         dest->tls_creds = g_strdup(params->tls_creds);                  // (1) 0.06055
/*58  */     }                                                                   // (26) 0.007812
/*62  */     if (params->has_tls_hostname) {                                     // (17) 0.03125
/*64  */         dest->tls_hostname = g_strdup(params->tls_hostname);            // (2) 0.05664
/*66  */     }                                                                   // (27) 0.007812
/*70  */     if (params->has_max_bandwidth) {                                    // (19) 0.0293
/*72  */         dest->max_bandwidth = params->max_bandwidth;                    // (8) 0.04102
/*74  */     }                                                                   // (20) 0.007812
/*78  */     if (params->has_downtime_limit) {                                   // 0.0
/*80  */         dest->downtime_limit = params->downtime_limit;                  // 0.0
/*82  */     }                                                                   // 0.0
/*86  */     if (params->has_x_checkpoint_delay) {                               // 0.0
/*88  */         dest->x_checkpoint_delay = params->x_checkpoint_delay;          // 0.0
/*90  */     }                                                                   // 0.0
/*94  */     if (params->has_block_incremental) {                                // 0.0
/*96  */         dest->block_incremental = params->block_incremental;            // 0.0
/*98  */     }                                                                   // 0.0
/*100 */ }                                                                       // 0.0
