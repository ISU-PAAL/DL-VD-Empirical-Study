// commit message qemu@60fe637bf0 (target=1, prob=0.26311842, correct=False): Start migrating migration code into a migration directory
/*0 */ void qemu_file_set_rate_limit(QEMUFile *f, int64_t limit)  // (0) 0.5417
/*2 */ {                                                          // (2) 0.02083
/*4 */     f->xfer_limit = limit;                                 // (1) 0.25
/*6 */ }                                                          // (3) 0.02083
