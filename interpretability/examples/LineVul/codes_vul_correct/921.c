// commit message qemu@8ad9fa5d8b (target=1, prob=0.99927586, correct=True): Fix brown-paper-bag bugs from live-migration patch (Charles Duffy)
/*0   */ MigrationState *exec_start_outgoing_migration(const char *command,           // (9) 0.03711
/*2   */                                              int64_t bandwidth_limit,        // (0) 0.1016
/*4   */                                              int async)                      // (1) 0.0918
/*6   */ {                                                                            // (28) 0.001953
/*8   */     FdMigrationState *s;                                                     // (19) 0.02148
/*10  */     FILE *f;                                                                 // (23) 0.01367
/*14  */     s = qemu_mallocz(sizeof(*s));                                            // (10) 0.03516
/*16  */     if (s == NULL) {                                                         // (22) 0.01953
/*18  */         dprintf("Unable to allocate FdMigrationState\n");                    // (5) 0.04297
/*20  */         goto err;                                                            // (20) 0.01953
/*22  */     }                                                                        // (25) 0.007812
/*26  */     f = popen(command, "w");                                                 // (15) 0.02539
/*28  */     if (f == NULL) {                                                         // (21) 0.01953
/*30  */         dprintf("Unable to popen exec target\n");                            // (8) 0.03906
/*32  */         goto err_after_alloc;                                                // (13) 0.02734
/*34  */     }                                                                        // (26) 0.007812
/*38  */     s->fd = fileno(f);                                                       // (17) 0.02344
/*40  */     if (s->fd == -1) {                                                       // (16) 0.02539
/*42  */         dprintf("Unable to retrieve file descriptor for popen'd handle\n");  // (3) 0.04687
/*44  */         goto err_after_open;                                                 // (14) 0.02734
/*46  */     }                                                                        // (27) 0.007812
/*50  */     if (fcntl(s->fd, F_SETFD, O_NONBLOCK) == -1) {                           // (2) 0.06055
/*52  */         dprintf("Unable to set nonblocking mode on file descriptor\n");      // (4) 0.04492
/*54  */         goto err_after_open;                                                 // (12) 0.02734
/*56  */     }                                                                        // (24) 0.007813
/*60  */     s->opaque = qemu_popen(f, "w");                                          // (6) 0.03906
/*65  */     s->get_error = file_errno;                                               // (11) 0.02734
/*67  */     s->write = file_write;                                                   // (18) 0.02148
/*69  */     s->mig_state.cancel = migrate_fd_cancel;                                 // (7) 0.03906
/*71  */     s->mig_state.get_status = migrate_fd_get_status;                         // 0.0
/*73  */     s->mig_state.release = migrate_fd_release;                               // 0.0
/*77  */     s->state = MIG_STATE_ACTIVE;                                             // 0.0
/*79  */     s->detach = !async;                                                      // 0.0
/*81  */     s->bandwidth_limit = bandwidth_limit;                                    // 0.0
/*85  */     if (s->detach == 1) {                                                    // 0.0
/*87  */         dprintf("detaching from monitor\n");                                 // 0.0
/*89  */         monitor_suspend();                                                   // 0.0
/*91  */         s->detach = 2;                                                       // 0.0
/*93  */     }                                                                        // 0.0
/*97  */     migrate_fd_connect(s);                                                   // 0.0
/*99  */     return &s->mig_state;                                                    // 0.0
/*103 */ err_after_open:                                                              // 0.0
/*105 */     pclose(f);                                                               // 0.0
/*107 */ err_after_alloc:                                                             // 0.0
/*109 */     qemu_free(s);                                                            // 0.0
/*111 */ err:                                                                         // 0.0
/*113 */     return NULL;                                                             // 0.0
/*115 */ }                                                                            // 0.0
