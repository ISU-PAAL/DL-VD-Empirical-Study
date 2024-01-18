// commit message qemu@2c80e42395 (target=0, prob=0.39817166, correct=True): Replace remaining gcc format attributes by macro GCC_FMT_ATTR (format checking)
/*0  */ dprint(int level, const char *fmt, ...)  // (2) 0.1414
/*2  */ {                                        // (7) 0.0101
/*4  */     va_list args;                        // (5) 0.08081
/*8  */     if (level <= debug) {                // (4) 0.101
/*10 */         va_start(args, fmt);             // (1) 0.1515
/*12 */         vfprintf(stderr, fmt, args);     // (0) 0.1919
/*14 */         va_end(args);                    // (3) 0.1313
/*16 */     }                                    // (6) 0.0404
/*18 */ }                                        // (8) 0.0101
