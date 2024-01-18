// commit message qemu@84aa07f109 (target=0, prob=0.009664884, correct=True): target/s390x: fix COMPARE LOGICAL LONG EXTENDED
/*0  */ uint32_t HELPER(clcle)(CPUS390XState *env, uint32_t r1, uint64_t a2,   // (3) 0.0625
/*2  */                        uint32_t r3)                                    // (4) 0.05664
/*4  */ {                                                                      // (26) 0.001953
/*6  */     uintptr_t ra = GETPC();                                            // (19) 0.02344
/*8  */     uint64_t destlen = get_length(env, r1 + 1);                        // (8) 0.04102
/*10 */     uint64_t dest = get_address(env, r1);                              // (11) 0.03516
/*12 */     uint64_t srclen = get_length(env, r3 + 1);                         // (7) 0.04297
/*14 */     uint64_t src = get_address(env, r3);                               // (10) 0.03516
/*16 */     uint8_t pad = a2 & 0xff;                                           // (14) 0.0293
/*18 */     uint32_t cc = 0;                                                   // (20) 0.02148
/*22 */     if (!(destlen || srclen)) {                                        // (15) 0.02734
/*24 */         return cc;                                                     // (21) 0.01953
/*26 */     }                                                                  // (24) 0.007812
/*30 */     if (srclen > destlen) {                                            // (17) 0.02539
/*32 */         srclen = destlen;                                              // (16) 0.02734
/*34 */     }                                                                  // (25) 0.007812
/*38 */     for (; destlen || srclen; src++, dest++, destlen--, srclen--) {    // (5) 0.05664
/*40 */         uint8_t v1 = srclen ? cpu_ldub_data_ra(env, src, ra) : pad;    // (0) 0.07031
/*42 */         uint8_t v2 = destlen ? cpu_ldub_data_ra(env, dest, ra) : pad;  // (1) 0.06836
/*44 */         if (v1 != v2) {                                                // (13) 0.03125
/*46 */             cc = (v1 < v2) ? 1 : 2;                                    // (6) 0.04883
/*48 */             break;                                                     // (18) 0.02539
/*50 */         }                                                              // (22) 0.01562
/*52 */     }                                                                  // (23) 0.007813
/*56 */     set_length(env, r1 + 1, destlen);                                  // (12) 0.0332
/*58 */     /* can't use srclen here, we trunc'ed it */                        // (9) 0.03516
/*60 */     set_length(env, r3 + 1, env->regs[r3 + 1] - src - env->regs[r3]);  // (2) 0.06836
/*62 */     set_address(env, r1, dest);                                        // 0.0
/*64 */     set_address(env, r3, src);                                         // 0.0
/*68 */     return cc;                                                         // 0.0
/*70 */ }                                                                      // 0.0
