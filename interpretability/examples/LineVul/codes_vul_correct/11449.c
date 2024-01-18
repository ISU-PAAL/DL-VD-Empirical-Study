// commit message qemu@60fe637bf0 (target=1, prob=0.5837734, correct=True): Start migrating migration code into a migration directory
/*0 */ void qmp_migrate_cancel(Error **errp)          // (1) 0.3571
/*2 */ {                                              // (2) 0.02381
/*4 */     migrate_fd_cancel(migrate_get_current());  // (0) 0.4048
/*6 */ }                                              // (3) 0.02381
