// commit message qemu@60fe637bf0 (target=1, prob=0.32241574, correct=False): Start migrating migration code into a migration directory
/*0  */ void qemu_file_set_error(QEMUFile *f, int ret)  // (0) 0.3182
/*2  */ {                                               // (4) 0.01515
/*4  */     if (f->last_error == 0) {                   // (2) 0.2121
/*6  */         f->last_error = ret;                    // (1) 0.2273
/*8  */     }                                           // (3) 0.06061
/*10 */ }                                               // (5) 0.01515
