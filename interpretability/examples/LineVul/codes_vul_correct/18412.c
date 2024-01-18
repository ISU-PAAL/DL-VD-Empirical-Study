// commit message qemu@ccbcfedd17 (target=1, prob=0.51547736, correct=True): device tree: dont fail operations
/*0  */ int qemu_devtree_setprop_string(void *fdt, const char *node_path,          // (1) 0.1689
/*2  */                                 const char *property, const char *string)  // (0) 0.277
/*4  */ {                                                                          // (7) 0.006757
/*6  */     int offset;                                                            // (6) 0.04054
/*10 */     offset = fdt_path_offset(fdt, node_path);                              // (3) 0.1284
/*12 */     if (offset < 0)                                                        // (5) 0.06081
/*14 */         return offset;                                                     // (4) 0.06757
/*18 */     return fdt_setprop_string(fdt, offset, property, string);              // (2) 0.1419
/*20 */ }                                                                          // (8) 0.006757
