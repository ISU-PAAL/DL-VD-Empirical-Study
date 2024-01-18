// commit message qemu@57be80f948 (target=1, prob=0.6075377, correct=True): powerpc/kvm: Fix a uninitialized bug (Liu Yu)
/*0  */ static int kvmppc_read_host_property(const char *node_path, const char *prop,    // (3) 0.06068
/*2  */                                      void *val, size_t len)                      // (0) 0.1092
/*4  */ {                                                                                // (30) 0.002427
/*6  */     char *path;                                                                  // (18) 0.01699
/*8  */     FILE *f;                                                                     // (19) 0.01699
/*10 */     int ret;                                                                     // (22) 0.01456
/*12 */     int pathlen;                                                                 // (20) 0.01699
/*16 */     pathlen = snprintf(NULL, 0, "%s/%s/%s", PROC_DEVTREE_PATH, node_path, prop)  // (1) 0.08738
/*18 */               + 1;                                                               // (4) 0.03883
/*20 */     path = qemu_malloc(pathlen);                                                 // (6) 0.03641
/*22 */     if (path == NULL) {                                                          // (11) 0.02427
/*24 */         ret = -ENOMEM;                                                           // (7) 0.03398
/*26 */         goto out;                                                                // (12) 0.02427
/*28 */     }                                                                            // (24) 0.009709
/*32 */     snprintf(path, pathlen, "%s/%s/%s", PROC_DEVTREE_PATH, node_path, prop);     // (2) 0.08252
/*36 */     f = fopen(path, "rb");                                                       // (9) 0.03155
/*38 */     if (f == NULL) {                                                             // (13) 0.02427
/*40 */         ret = errno;                                                             // (10) 0.02913
/*42 */         goto free;                                                               // (14) 0.02427
/*44 */     }                                                                            // (25) 0.009709
/*48 */     len = fread(val, len, 1, f);                                                 // (5) 0.03883
/*50 */     if (len != 1) {                                                              // (15) 0.02427
/*52 */         ret = ferror(f);                                                         // (8) 0.03398
/*54 */         goto close;                                                              // (16) 0.02427
/*56 */     }                                                                            // (26) 0.009709
/*60 */ close:                                                                           // (27) 0.004854
/*62 */     fclose(f);                                                                   // (17) 0.01942
/*64 */ free:                                                                            // (28) 0.004854
/*66 */     free(path);                                                                  // (21) 0.01699
/*68 */ out:                                                                             // (29) 0.004854
/*70 */     return ret;                                                                  // (23) 0.01456
/*72 */ }                                                                                // (31) 0.002427
