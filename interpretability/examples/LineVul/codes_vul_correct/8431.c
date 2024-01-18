// commit message qemu@60fe637bf0 (target=1, prob=0.9954579, correct=True): Start migrating migration code into a migration directory
/*0 */ static void put_uint8(QEMUFile *f, void *pv, size_t size)  // (0) 0.375
/*2 */ {                                                          // (3) 0.01562
/*4 */     uint8_t *v = pv;                                       // (2) 0.2031
/*6 */     qemu_put_8s(f, v);                                     // (1) 0.25
/*8 */ }                                                          // (4) 0.01562
