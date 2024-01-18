// commit message qemu@60fe637bf0 (target=1, prob=0.95739096, correct=True): Start migrating migration code into a migration directory
/*0  */ static int get_uint16_equal(QEMUFile *f, void *pv, size_t size)  // (0) 0.2185
/*2  */ {                                                                // (8) 0.008403
/*4  */     uint16_t *v = pv;                                            // (2) 0.1092
/*6  */     uint16_t v2;                                                 // (4) 0.08403
/*8  */     qemu_get_be16s(f, &v2);                                      // (1) 0.1597
/*12 */     if (*v == v2) {                                              // (3) 0.09244
/*14 */         return 0;                                                // (5) 0.08403
/*16 */     }                                                            // (7) 0.03361
/*18 */     return -EINVAL;                                              // (6) 0.07563
/*20 */ }                                                                // (9) 0.008403
