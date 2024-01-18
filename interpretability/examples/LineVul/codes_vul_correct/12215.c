// commit message qemu@60fe637bf0 (target=1, prob=0.9886779, correct=True): Start migrating migration code into a migration directory
/*0  */ void qemu_put_be32(QEMUFile *f, unsigned int v)  // (0) 0.21
/*2  */ {                                                // (6) 0.01
/*4  */     qemu_put_byte(f, v >> 24);                   // (2) 0.17
/*6  */     qemu_put_byte(f, v >> 16);                   // (3) 0.17
/*8  */     qemu_put_byte(f, v >> 8);                    // (1) 0.17
/*10 */     qemu_put_byte(f, v);                         // (4) 0.15
/*12 */ }                                                // (5) 0.01
