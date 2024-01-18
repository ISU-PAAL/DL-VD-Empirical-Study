// commit message qemu@1964a39706 (target=0, prob=0.027328055, correct=True): migration: move rate limiting to QEMUFile
/*0  */ static int64_t migration_set_rate_limit(void *opaque, int64_t new_rate)  // (0) 0.2241
/*2  */ {                                                                        // (8) 0.008621
/*4  */     MigrationState *s = opaque;                                          // (4) 0.08621
/*6  */     if (qemu_file_get_error(s->file)) {                                  // (1) 0.1724
/*8  */         goto out;                                                        // (5) 0.08621
/*10 */     }                                                                    // (6) 0.03448
/*14 */     s->xfer_limit = new_rate;                                            // (2) 0.1207
/*18 */ out:                                                                     // (7) 0.01724
/*20 */     return s->xfer_limit;                                                // (3) 0.09483
/*22 */ }                                                                        // (9) 0.008621
