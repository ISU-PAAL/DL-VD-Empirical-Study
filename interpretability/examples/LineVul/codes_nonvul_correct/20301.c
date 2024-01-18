// commit message qemu@c0462f6d75 (target=0, prob=0.036696695, correct=True): qemu-option: Pair g_malloc() with g_free(), not free()
/*0  */ bool is_valid_option_list(const char *param)  // (7) 0.05447
/*2  */ {                                             // (19) 0.003891
/*4  */     size_t buflen = strlen(param) + 1;        // (2) 0.07004
/*6  */     char *buf = g_malloc(buflen);             // (4) 0.06226
/*8  */     const char *p = param;                    // (10) 0.03891
/*10 */     bool result = true;                       // (12) 0.03113
/*14 */     while (*p) {                              // (11) 0.03113
/*16 */         p = get_opt_value(buf, buflen, p);    // (0) 0.08949
/*18 */         if (*p && !*++p) {                    // (3) 0.06615
/*20 */             result = false;                   // (5) 0.05837
/*22 */             goto out;                         // (8) 0.05447
/*24 */         }                                     // (13) 0.03113
/*28 */         if (!*buf || *buf == ',') {           // (1) 0.07393
/*30 */             result = false;                   // (6) 0.05837
/*32 */             goto out;                         // (9) 0.05447
/*34 */         }                                     // (14) 0.03113
/*36 */     }                                         // (17) 0.01556
/*40 */ out:                                          // (18) 0.007782
/*42 */     free(buf);                                // (15) 0.02724
/*44 */     return result;                            // (16) 0.02335
/*46 */ }                                             // (20) 0.003891
