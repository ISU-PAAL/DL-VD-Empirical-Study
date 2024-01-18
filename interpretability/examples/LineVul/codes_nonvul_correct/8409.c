// commit message qemu@442773cef1 (target=0, prob=0.43815222, correct=True): migration: small changes around rate-limiting
/*0  */ void qmp_migrate_set_speed(int64_t value, Error **errp)     // (1) 0.1803
/*2  */ {                                                           // (8) 0.008197
/*4  */     MigrationState *s;                                      // (6) 0.06557
/*8  */     if (value < 0) {                                        // (5) 0.08197
/*10 */         value = 0;                                          // (4) 0.09016
/*12 */     }                                                       // (7) 0.03279
/*16 */     s = migrate_get_current();                              // (3) 0.09016
/*18 */     s->bandwidth_limit = value;                             // (2) 0.09836
/*20 */     qemu_file_set_rate_limit(s->file, s->bandwidth_limit);  // (0) 0.2131
/*22 */ }                                                           // (9) 0.008197
