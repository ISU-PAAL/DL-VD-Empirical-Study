// commit message qemu@a3fa1d78cb (target=0, prob=0.5574819, correct=False): migration: do not nest flushing of device data
/*0  */ static void migrate_fd_completed(MigrationState *s)       // (4) 0.1064
/*2  */ {                                                         // (8) 0.007092
/*4  */     DPRINTF("setting completed state\n");                 // (5) 0.0922
/*6  */     migrate_fd_cleanup(s);                                // (6) 0.08511
/*8  */     if (s->state == MIG_STATE_ACTIVE) {                   // (3) 0.1277
/*10 */         s->state = MIG_STATE_COMPLETED;                   // (2) 0.1348
/*12 */         runstate_set(RUN_STATE_POSTMIGRATE);              // (0) 0.1631
/*14 */     }                                                     // (7) 0.02837
/*16 */     notifier_list_notify(&migration_state_notifiers, s);  // (1) 0.1489
/*18 */ }                                                         // (9) 0.007092
