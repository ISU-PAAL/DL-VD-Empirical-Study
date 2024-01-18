// commit message qemu@60fe637bf0 (target=1, prob=0.9951438, correct=True): Start migrating migration code into a migration directory
/*0 */ static void put_uint64(QEMUFile *f, void *pv, size_t size)  // (0) 0.3692
/*2 */ {                                                           // (3) 0.01538
/*4 */     uint64_t *v = pv;                                       // (2) 0.2
/*6 */     qemu_put_be64s(f, v);                                   // (1) 0.2615
/*8 */ }                                                           // (4) 0.01538
