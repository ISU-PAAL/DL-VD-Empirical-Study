// commit message qemu@e8ede0a8bb (target=0, prob=0.012499139, correct=True): unicore32: Split UniCore-F64 instruction helpers from helper.c
/*0  */ static inline float64 ucf64_itod(uint64_t i)  // (0) 0.2
/*2  */ {                                             // (7) 0.01176
/*4  */     union {                                   // (6) 0.05882
/*6  */         uint64_t i;                           // (1) 0.1529
/*8  */         float64 d;                            // (2) 0.1294
/*10 */     } v;                                      // (5) 0.07059
/*14 */     v.i = i;                                  // (3) 0.1059
/*16 */     return v.d;                               // (4) 0.09412
/*18 */ }                                             // (8) 0.01176
