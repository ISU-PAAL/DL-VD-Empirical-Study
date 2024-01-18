// commit message qemu@60fe637bf0 (target=1, prob=0.99272, correct=True): Start migrating migration code into a migration directory
/*0  */ static int get_int64(QEMUFile *f, void *pv, size_t size)  // (0) 0.3288
/*2  */ {                                                         // (4) 0.0137
/*4  */     int64_t *v = pv;                                      // (2) 0.1781
/*6  */     qemu_get_sbe64s(f, v);                                // (1) 0.2466
/*8  */     return 0;                                             // (3) 0.08219
/*10 */ }                                                         // (5) 0.0137
