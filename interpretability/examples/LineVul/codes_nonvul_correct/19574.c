// commit message qemu@2ff3025797 (target=0, prob=0.42265514, correct=True): migrate: move max-bandwidth and downtime-limit to migrate_set_parameter
/*0   */ static void *migration_thread(void *opaque)                                       // (14) 0.02539
/*2   */ {                                                                                 // (25) 0.001953
/*4   */     MigrationState *s = opaque;                                                   // (21) 0.01953
/*6   */     /* Used by the bandwidth calcs, updated later */                              // (13) 0.02734
/*8   */     int64_t initial_time = qemu_clock_get_ms(QEMU_CLOCK_REALTIME);                // (0) 0.0625
/*10  */     int64_t setup_start = qemu_clock_get_ms(QEMU_CLOCK_HOST);                     // (2) 0.06055
/*12  */     int64_t initial_bytes = 0;                                                    // (15) 0.02539
/*14  */     int64_t max_size = 0;                                                         // (16) 0.02539
/*16  */     int64_t start_time = initial_time;                                            // (11) 0.0293
/*18  */     int64_t end_time;                                                             // (19) 0.02148
/*20  */     bool old_vm_running = false;                                                  // (17) 0.02344
/*22  */     bool entered_postcopy = false;                                                // (18) 0.02148
/*24  */     /* The active state we expect to be in; ACTIVE or POSTCOPY_ACTIVE */          // (6) 0.04687
/*26  */     enum MigrationStatus current_active_state = MIGRATION_STATUS_ACTIVE;          // (7) 0.04492
/*30  */     rcu_register_thread();                                                        // (22) 0.01953
/*34  */     qemu_savevm_state_header(s->to_dst_file);                                     // (8) 0.04492
/*38  */     if (migrate_postcopy_ram()) {                                                 // (12) 0.02734
/*40  */         /* Now tell the dest that it should open its end so it can reply */       // (9) 0.04492
/*42  */         qemu_savevm_send_open_return_path(s->to_dst_file);                        // (1) 0.06055
/*46  */         /* And do a ping that will make stuff easier to debug */                  // (10) 0.03906
/*48  */         qemu_savevm_send_ping(s->to_dst_file, 1);                                 // (3) 0.05664
/*52  */         /*                                                                        // (24) 0.01562
/*54  */          * Tell the destination that we *might* want to do postcopy later;        // (5) 0.04687
/*56  */          * if the other end can't do postcopy it should fail now, nice and        // (4) 0.04883
/*58  */          * early.                                                                 // (20) 0.02148
/*60  */          */                                                                       // (23) 0.01758
/*62  */         qemu_savevm_send_postcopy_advise(s->to_dst_file);                         // 0.0
/*64  */     }                                                                             // 0.0
/*68  */     qemu_savevm_state_begin(s->to_dst_file, &s->params);                          // 0.0
/*72  */     s->setup_time = qemu_clock_get_ms(QEMU_CLOCK_HOST) - setup_start;             // 0.0
/*74  */     current_active_state = MIGRATION_STATUS_ACTIVE;                               // 0.0
/*76  */     migrate_set_state(&s->state, MIGRATION_STATUS_SETUP,                          // 0.0
/*78  */                       MIGRATION_STATUS_ACTIVE);                                   // 0.0
/*82  */     trace_migration_thread_setup_complete();                                      // 0.0
/*86  */     while (s->state == MIGRATION_STATUS_ACTIVE ||                                 // 0.0
/*88  */            s->state == MIGRATION_STATUS_POSTCOPY_ACTIVE) {                        // 0.0
/*90  */         int64_t current_time;                                                     // 0.0
/*92  */         uint64_t pending_size;                                                    // 0.0
/*96  */         if (!qemu_file_rate_limit(s->to_dst_file)) {                              // 0.0
/*98  */             uint64_t pend_post, pend_nonpost;                                     // 0.0
/*102 */             qemu_savevm_state_pending(s->to_dst_file, max_size, &pend_nonpost,    // 0.0
/*104 */                                       &pend_post);                                // 0.0
/*106 */             pending_size = pend_nonpost + pend_post;                              // 0.0
/*108 */             trace_migrate_pending(pending_size, max_size,                         // 0.0
/*110 */                                   pend_post, pend_nonpost);                       // 0.0
/*112 */             if (pending_size && pending_size >= max_size) {                       // 0.0
/*114 */                 /* Still a significant amount to transfer */                      // 0.0
/*118 */                 if (migrate_postcopy_ram() &&                                     // 0.0
/*120 */                     s->state != MIGRATION_STATUS_POSTCOPY_ACTIVE &&               // 0.0
/*122 */                     pend_nonpost <= max_size &&                                   // 0.0
/*124 */                     atomic_read(&s->start_postcopy)) {                            // 0.0
/*128 */                     if (!postcopy_start(s, &old_vm_running)) {                    // 0.0
/*130 */                         current_active_state = MIGRATION_STATUS_POSTCOPY_ACTIVE;  // 0.0
/*132 */                         entered_postcopy = true;                                  // 0.0
/*134 */                     }                                                             // 0.0
/*138 */                     continue;                                                     // 0.0
/*140 */                 }                                                                 // 0.0
/*142 */                 /* Just another iteration step */                                 // 0.0
/*144 */                 qemu_savevm_state_iterate(s->to_dst_file, entered_postcopy);      // 0.0
/*146 */             } else {                                                              // 0.0
/*148 */                 trace_migration_thread_low_pending(pending_size);                 // 0.0
/*150 */                 migration_completion(s, current_active_state,                     // 0.0
/*152 */                                      &old_vm_running, &start_time);               // 0.0
/*154 */                 break;                                                            // 0.0
/*156 */             }                                                                     // 0.0
/*158 */         }                                                                         // 0.0
/*162 */         if (qemu_file_get_error(s->to_dst_file)) {                                // 0.0
/*164 */             migrate_set_state(&s->state, current_active_state,                    // 0.0
/*166 */                               MIGRATION_STATUS_FAILED);                           // 0.0
/*168 */             trace_migration_thread_file_err();                                    // 0.0
/*170 */             break;                                                                // 0.0
/*172 */         }                                                                         // 0.0
/*174 */         current_time = qemu_clock_get_ms(QEMU_CLOCK_REALTIME);                    // 0.0
/*176 */         if (current_time >= initial_time + BUFFER_DELAY) {                        // 0.0
/*178 */             uint64_t transferred_bytes = qemu_ftell(s->to_dst_file) -             // 0.0
/*180 */                                          initial_bytes;                           // 0.0
/*182 */             uint64_t time_spent = current_time - initial_time;                    // 0.0
/*184 */             double bandwidth = (double)transferred_bytes / time_spent;            // 0.0
/*186 */             max_size = bandwidth * migrate_max_downtime() / 1000000;              // 0.0
/*190 */             s->mbps = (((double) transferred_bytes * 8.0) /                       // 0.0
/*192 */                     ((double) time_spent / 1000.0)) / 1000.0 / 1000.0;            // 0.0
/*196 */             trace_migrate_transferred(transferred_bytes, time_spent,              // 0.0
/*198 */                                       bandwidth, max_size);                       // 0.0
/*200 */             /* if we haven't sent anything, we don't want to recalculate          // 0.0
/*202 */                10000 is a small enough number for our purposes */                 // 0.0
/*204 */             if (s->dirty_bytes_rate && transferred_bytes > 10000) {               // 0.0
/*206 */                 s->expected_downtime = s->dirty_bytes_rate / bandwidth;           // 0.0
/*208 */             }                                                                     // 0.0
/*212 */             qemu_file_reset_rate_limit(s->to_dst_file);                           // 0.0
/*214 */             initial_time = current_time;                                          // 0.0
/*216 */             initial_bytes = qemu_ftell(s->to_dst_file);                           // 0.0
/*218 */         }                                                                         // 0.0
/*220 */         if (qemu_file_rate_limit(s->to_dst_file)) {                               // 0.0
/*222 */             /* usleep expects microseconds */                                     // 0.0
/*224 */             g_usleep((initial_time + BUFFER_DELAY - current_time)*1000);          // 0.0
/*226 */         }                                                                         // 0.0
/*228 */     }                                                                             // 0.0
/*232 */     trace_migration_thread_after_loop();                                          // 0.0
/*234 */     /* If we enabled cpu throttling for auto-converge, turn it off. */            // 0.0
/*236 */     cpu_throttle_stop();                                                          // 0.0
/*238 */     end_time = qemu_clock_get_ms(QEMU_CLOCK_REALTIME);                            // 0.0
/*242 */     qemu_mutex_lock_iothread();                                                   // 0.0
/*244 */     qemu_savevm_state_cleanup();                                                  // 0.0
/*246 */     if (s->state == MIGRATION_STATUS_COMPLETED) {                                 // 0.0
/*248 */         uint64_t transferred_bytes = qemu_ftell(s->to_dst_file);                  // 0.0
/*250 */         s->total_time = end_time - s->total_time;                                 // 0.0
/*252 */         if (!entered_postcopy) {                                                  // 0.0
/*254 */             s->downtime = end_time - start_time;                                  // 0.0
/*256 */         }                                                                         // 0.0
/*258 */         if (s->total_time) {                                                      // 0.0
/*260 */             s->mbps = (((double) transferred_bytes * 8.0) /                       // 0.0
/*262 */                        ((double) s->total_time)) / 1000;                          // 0.0
/*264 */         }                                                                         // 0.0
/*266 */         runstate_set(RUN_STATE_POSTMIGRATE);                                      // 0.0
/*268 */     } else {                                                                      // 0.0
/*270 */         if (old_vm_running && !entered_postcopy) {                                // 0.0
/*272 */             vm_start();                                                           // 0.0
/*274 */         } else {                                                                  // 0.0
/*276 */             if (runstate_check(RUN_STATE_FINISH_MIGRATE)) {                       // 0.0
/*278 */                 runstate_set(RUN_STATE_POSTMIGRATE);                              // 0.0
/*280 */             }                                                                     // 0.0
/*282 */         }                                                                         // 0.0
/*284 */     }                                                                             // 0.0
/*286 */     qemu_bh_schedule(s->cleanup_bh);                                              // 0.0
/*288 */     qemu_mutex_unlock_iothread();                                                 // 0.0
/*292 */     rcu_unregister_thread();                                                      // 0.0
/*294 */     return NULL;                                                                  // 0.0
/*296 */ }                                                                                 // 0.0
