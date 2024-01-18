// commit message qemu@f53f4da9c6 (target=1, prob=0.2536513, correct=False): block: simplify path_is_absolute
/*0  */ int path_is_absolute(const char *path)            // (4) 0.0663
/*2  */ {                                                 // (17) 0.005525
/*4  */     const char *p;                                // (9) 0.0442
/*6  */ #ifdef _WIN32                                     // (11) 0.03315
/*8  */     /* specific case for names like: "\\.\d:" */  // (0) 0.09392
/*10 */     if (*path == '/' || *path == '\\')            // (1) 0.0884
/*12 */         return 1;                                 // (6) 0.05525
/*14 */ #endif                                            // (14) 0.01105
/*16 */     p = strchr(path, ':');                        // (3) 0.07735
/*18 */     if (p)                                        // (10) 0.03867
/*20 */         p++;                                      // (8) 0.04972
/*22 */     else                                          // (13) 0.0221
/*24 */         p = path;                                 // (5) 0.06077
/*26 */ #ifdef _WIN32                                     // (12) 0.03315
/*28 */     return (*p == '/' || *p == '\\');             // (2) 0.0884
/*30 */ #else                                             // (15) 0.01105
/*32 */     return (*p == '/');                           // (7) 0.04972
/*34 */ #endif                                            // (16) 0.01105
/*36 */ }                                                 // (18) 0.005525
