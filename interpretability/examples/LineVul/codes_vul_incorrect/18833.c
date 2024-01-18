// commit message qemu@9287ac271d (target=1, prob=0.36462584, correct=False): migration: notify migration state before starting thread
/*0  */ void migrate_fd_connect(MigrationState *s)                            // (10) 0.04745
/*2  */ {                                                                     // (11) 0.00365
/*4  */     s->state = MIG_STATE_SETUP;                                       // (9) 0.05474
/*6  */     trace_migrate_set_state(MIG_STATE_SETUP);                         // (5) 0.07299
/*10 */     /* This is a best 1st approximation. ns to ms */                  // (8) 0.05839
/*12 */     s->expected_downtime = max_downtime/1000000;                      // (6) 0.07299
/*14 */     s->cleanup_bh = qemu_bh_new(migrate_fd_cleanup, s);               // (2) 0.1022
/*18 */     qemu_file_set_rate_limit(s->file,                                 // (7) 0.06934
/*20 */                              s->bandwidth_limit / XFER_LIMIT_RATIO);  // (0) 0.1679
/*24 */     qemu_thread_create(&s->thread, migration_thread, s,               // (3) 0.07664
/*26 */                        QEMU_THREAD_JOINABLE);                         // (1) 0.1204
/*28 */     notifier_list_notify(&migration_state_notifiers, s);              // (4) 0.07664
/*30 */ }                                                                     // (12) 0.00365
