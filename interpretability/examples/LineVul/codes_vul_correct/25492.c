// commit message qemu@60fe637bf0 (target=1, prob=0.69745535, correct=True): Start migrating migration code into a migration directory
/*0 */ int64_t qemu_ftell(QEMUFile *f)  // (0) 0.36
/*2 */ {                                // (3) 0.02
/*4 */     qemu_fflush(f);              // (1) 0.26
/*6 */     return f->pos;               // (2) 0.16
/*8 */ }                                // (4) 0.02
