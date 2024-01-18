// commit message qemu@5d39c799c3 (target=0, prob=0.14290836, correct=True): migration: Fix use of file after release
/*0  */ void do_migrate_set_speed(Monitor *mon, const QDict *qdict, QObject **ret_data)  // (0) 0.09898
/*2  */ {                                                                                // (22) 0.003413
/*4  */     double d;                                                                    // (17) 0.02048
/*6  */     char *ptr;                                                                   // (16) 0.02389
/*8  */     FdMigrationState *s;                                                         // (9) 0.03754
/*10 */     const char *value = qdict_get_str(qdict, "value");                           // (2) 0.07167
/*14 */     d = strtod(value, &ptr);                                                     // (5) 0.04778
/*16 */     switch (*ptr) {                                                              // (14) 0.0273
/*18 */     case 'G': case 'g':                                                          // (10) 0.03754
/*20 */         d *= 1024;                                                               // (6) 0.04096
/*22 */     case 'M': case 'm':                                                          // (11) 0.03754
/*24 */         d *= 1024;                                                               // (7) 0.04096
/*26 */     case 'K': case 'k':                                                          // (12) 0.03754
/*28 */         d *= 1024;                                                               // (8) 0.04096
/*30 */     default:                                                                     // (18) 0.01706
/*32 */         break;                                                                   // (13) 0.03072
/*34 */     }                                                                            // (19) 0.01365
/*38 */     max_throttle = (uint32_t)d;                                                  // (4) 0.05461
/*40 */     s = migrate_to_fms(current_migration);                                       // (3) 0.05802
/*44 */     if (s) {                                                                     // (15) 0.0273
/*46 */         qemu_file_set_rate_limit(s->file, max_throttle);                         // (1) 0.09556
/*48 */     }                                                                            // (20) 0.01365
/*50 */                                                                                  // (21) 0.01365
/*52 */ }                                                                                // (23) 0.003413
