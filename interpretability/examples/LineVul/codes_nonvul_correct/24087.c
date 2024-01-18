// commit message qemu@245f7b51c0 (target=0, prob=0.24106434, correct=True): vnc: rename vnc-encoding-* vnc-enc-*
/*0  */ void *vnc_zlib_zalloc(void *x, unsigned items, unsigned size)        // (1) 0.1981
/*2  */ {                                                                    // (6) 0.009434
/*4  */     void *p;                                                         // (4) 0.06604
/*8  */     size *= items;                                                   // (3) 0.07547
/*10 */     size = (size + ZALLOC_ALIGNMENT - 1) & ~(ZALLOC_ALIGNMENT - 1);  // (0) 0.2925
/*14 */     p = qemu_mallocz(size);                                          // (2) 0.1415
/*18 */     return (p);                                                      // (5) 0.06604
/*20 */ }                                                                    // (7) 0.009434
