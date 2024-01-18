// commit message qemu@60fe637bf0 (target=1, prob=0.6919825, correct=True): Start migrating migration code into a migration directory
/*0  */ static void unix_wait_for_connect(int fd, Error *err, void *opaque)     // (2) 0.127
/*2  */ {                                                                       // (11) 0.005291
/*4  */     MigrationState *s = opaque;                                         // (7) 0.05291
/*8  */     if (fd < 0) {                                                       // (8) 0.05291
/*10 */         DPRINTF("migrate connect error: %s\n", error_get_pretty(err));  // (0) 0.1534
/*12 */         s->file = NULL;                                                 // (6) 0.06878
/*14 */         migrate_fd_error(s);                                            // (4) 0.07937
/*16 */     } else {                                                            // (9) 0.03175
/*18 */         DPRINTF("migrate connect success\n");                           // (3) 0.09524
/*20 */         s->file = qemu_fopen_socket(fd, "wb");                          // (1) 0.1323
/*22 */         migrate_fd_connect(s);                                          // (5) 0.07937
/*24 */     }                                                                   // (10) 0.02116
/*26 */ }                                                                       // (12) 0.005291
