// commit message qemu@591b320ad0 (target=1, prob=0.32566646, correct=False): util/hbitmap.c: Use ctpopl rather than reimplementing a local equivalent
/*0 */ static inline int popcountl(unsigned long l)               // (1) 0.22
/*2 */ {                                                          // (3) 0.02
/*4 */     return BITS_PER_LONG == 32 ? ctpop32(l) : ctpop64(l);  // (0) 0.58
/*6 */ }                                                          // (2) 0.02
