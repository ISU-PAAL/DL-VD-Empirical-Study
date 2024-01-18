// commit message qemu@9a78eead0c (target=0, prob=0.037583135, correct=True): target-xxx: Use fprintf_function (format checking)
/*0  */ static void print_features(FILE *f,                                            // (7) 0.04098
/*2  */                            int (*cpu_fprintf)(FILE *f, const char *fmt, ...),  // (0) 0.1844
/*4  */                            uint32_t features, const char *prefix)              // (1) 0.1516
/*6  */ {                                                                              // (10) 0.004098
/*8  */     unsigned int i;                                                            // (9) 0.02869
/*12 */     for (i = 0; i < ARRAY_SIZE(feature_name); i++)                             // (5) 0.09016
/*14 */         if (feature_name[i] && (features & (1 << i))) {                        // (4) 0.1025
/*16 */             if (prefix)                                                        // (6) 0.06148
/*18 */                 (*cpu_fprintf)(f, "%s", prefix);                               // (2) 0.1148
/*20 */             (*cpu_fprintf)(f, "%s ", feature_name[i]);                         // (3) 0.1148
/*22 */         }                                                                      // (8) 0.03279
/*24 */ }                                                                              // (11) 0.004098
