// commit message qemu@45bbbb466c (target=1, prob=0.9918902, correct=True): added overflow exceptions in divisions
/*0  */ void helper_idivl_EAX_T0(void)                                  // (3) 0.06849
/*2  */ {                                                               // (17) 0.004566
/*4  */     int den, q, r;                                              // (7) 0.04566
/*6  */     int64_t num;                                                // (11) 0.0411
/*8  */                                                                 // (13) 0.01826
/*10 */     num = ((uint32_t)EAX) | ((uint64_t)((uint32_t)EDX) << 32);  // (0) 0.1507
/*12 */     den = T0;                                                   // (12) 0.03653
/*14 */     if (den == 0) {                                             // (8) 0.04566
/*16 */         raise_exception(EXCP00_DIVZ);                           // (1) 0.08676
/*18 */     }                                                           // (14) 0.01826
/*20 */ #ifdef BUGGY_GCC_DIV64                                          // (6) 0.05479
/*22 */     r = idiv32(&q, num, den);                                   // (2) 0.06849
/*24 */ #else                                                           // (15) 0.009132
/*26 */     q = (num / den);                                            // (9) 0.04566
/*28 */     r = (num % den);                                            // (10) 0.04566
/*30 */ #endif                                                          // (16) 0.009132
/*32 */     EAX = (uint32_t)q;                                          // (4) 0.06393
/*34 */     EDX = (uint32_t)r;                                          // (5) 0.06393
/*36 */ }                                                               // (18) 0.004566
