// commit message qemu@b3f7f0c5e6 (target=1, prob=0.99907327, correct=True): COLO: Implement the process of failover for primary VM
/*0  */ static void colo_process_checkpoint(MigrationState *s)                           // (12) 0.03126
/*1  */ {                                                                                // (26) 0.001953
/*2  */     QIOChannelBuffer *bioc;                                                      // (17) 0.02148
/*3  */     QEMUFile *fb = NULL;                                                         // (16) 0.02344
/*4  */     int64_t current_time, checkpoint_time = qemu_clock_get_ms(QEMU_CLOCK_HOST);  // (2) 0.06838
/*5  */     Error *local_err = NULL;                                                     // (18) 0.02148
/*6  */     int ret;                                                                     // (23) 0.01172
/*7  */     failover_init_state();                                                       // (19) 0.01953
/*8  */     s->rp_state.from_dst_file = qemu_file_get_return_path(s->to_dst_file);       // (1) 0.07421
/*9  */     if (!s->rp_state.from_dst_file) {                                            // (9) 0.03906
/*10 */         error_report("Open QEMUFile from_dst_file failed");                      // (7) 0.04688
/*11 */     /*                                                                           // (25) 0.007812
/*12 */      * Wait for Secondary finish loading VM states and enter COLO                // (13) 0.03125
/*13 */      * restore.                                                                  // (22) 0.01367
/*14 */      */                                                                          // (24) 0.009769
/*15 */     colo_receive_check_message(s->rp_state.from_dst_file,                        // (4) 0.05273
/*16 */                        COLO_MESSAGE_CHECKPOINT_READY, &local_err);               // (0) 0.08203
/*17 */     if (local_err) {                                                             // (20) 0.01953
/*18 */     bioc = qio_channel_buffer_new(COLO_BUFFER_BASE_SIZE);                        // (6) 0.05078
/*19 */     fb = qemu_fopen_channel_output(QIO_CHANNEL(bioc));                           // (5) 0.05273
/*20 */     object_unref(OBJECT(bioc));                                                  // (15) 0.02734
/*21 */     qemu_mutex_lock_iothread();                                                  // (14) 0.03125
/*22 */     vm_start();                                                                  // (21) 0.01367
/*23 */     qemu_mutex_unlock_iothread();                                                // (11) 0.0332
/*24 */     trace_colo_vm_state_change("stop", "run");                                   // (10) 0.03517
/*25 */     while (s->state == MIGRATION_STATUS_COLO) {                                  // (8) 0.04101
/*26 */         current_time = qemu_clock_get_ms(QEMU_CLOCK_HOST);                       // (3) 0.06054
/*27 */         if (current_time - checkpoint_time <                                     // 0.0
/*28 */             s->parameters.x_checkpoint_delay) {                                  // 0.0
/*29 */             int64_t delay_ms;                                                    // 0.0
/*30 */             delay_ms = s->parameters.x_checkpoint_delay -                        // 0.0
/*31 */                        (current_time - checkpoint_time);                         // 0.0
/*32 */             g_usleep(delay_ms * 1000);                                           // 0.0
/*33 */         ret = colo_do_checkpoint_transaction(s, bioc, fb);                       // 0.0
/*34 */         if (ret < 0) {                                                           // 0.0
/*35 */         checkpoint_time = qemu_clock_get_ms(QEMU_CLOCK_HOST);                    // 0.0
/*36 */ out:                                                                             // 0.0
/*37 */     /* Throw the unreported error message after exited from loop */              // 0.0
/*38 */     if (local_err) {                                                             // 0.0
/*39 */         error_report_err(local_err);                                             // 0.0
/*40 */     if (fb) {                                                                    // 0.0
/*41 */         qemu_fclose(fb);                                                         // 0.0
/*42 */     if (s->rp_state.from_dst_file) {                                             // 0.0
/*43 */         qemu_fclose(s->rp_state.from_dst_file);                                  // 0.0
