// commit message qemu@70976a7926 (target=1, prob=0.017857593, correct=False): Fix off-by-one errors for Altivec and SPE registers
/*0  */ static int gdb_set_avr_reg(CPUState *env, uint8_t *mem_buf, int n)  // (3) 0.08841
/*2  */ {                                                                   // (20) 0.003049
/*4  */     if (n < 32) {                                                   // (7) 0.03049
/*6  */ #ifdef WORDS_BIGENDIAN                                              // (8) 0.03049
/*8  */         env->avr[n].u64[0] = ldq_p(mem_buf);                        // (4) 0.08841
/*10 */         env->avr[n].u64[1] = ldq_p(mem_buf+8);                      // (1) 0.09451
/*12 */ #else                                                               // (18) 0.006098
/*14 */         env->avr[n].u64[1] = ldq_p(mem_buf);                        // (5) 0.08841
/*16 */         env->avr[n].u64[0] = ldq_p(mem_buf+8);                      // (2) 0.09451
/*18 */ #endif                                                              // (19) 0.006098
/*20 */         return 16;                                                  // (9) 0.03049
/*22 */     }                                                               // (15) 0.0122
/*24 */     if (n == 33) {                                                  // (10) 0.03049
/*26 */         env->vscr = ldl_p(mem_buf);                                 // (6) 0.06707
/*28 */         return 4;                                                   // (11) 0.03049
/*30 */     }                                                               // (16) 0.0122
/*32 */     if (n == 34) {                                                  // (12) 0.03049
/*34 */         env->spr[SPR_VRSAVE] = (target_ulong)ldl_p(mem_buf);        // (0) 0.1037
/*36 */         return 4;                                                   // (13) 0.03049
/*38 */     }                                                               // (17) 0.0122
/*40 */     return 0;                                                       // (14) 0.01829
/*42 */ }                                                                   // (21) 0.003049
