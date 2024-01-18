// commit message qemu@e3af7c788b (target=0, prob=0.029541437, correct=True): target/i386: introduce x86_ld*_code
/*0  */ static inline uint32_t insn_get(CPUX86State *env, DisasContext *s, TCGMemOp ot)  // (0) 0.106
/*2  */ {                                                                                // (22) 0.003534
/*4  */     uint32_t ret;                                                                // (9) 0.0318
/*8  */     switch (ot) {                                                                // (13) 0.02827
/*10 */     case MO_8:                                                                   // (14) 0.02827
/*12 */         ret = cpu_ldub_code(env, s->pc);                                         // (2) 0.07774
/*14 */         s->pc++;                                                                 // (7) 0.03887
/*16 */         break;                                                                   // (10) 0.0318
/*18 */     case MO_16:                                                                  // (15) 0.02827
/*20 */         ret = cpu_lduw_code(env, s->pc);                                         // (1) 0.08127
/*22 */         s->pc += 2;                                                              // (4) 0.04594
/*24 */         break;                                                                   // (11) 0.0318
/*26 */     case MO_32:                                                                  // (16) 0.02827
/*28 */ #ifdef TARGET_X86_64                                                             // (8) 0.03534
/*30 */     case MO_64:                                                                  // (17) 0.02827
/*32 */ #endif                                                                           // (21) 0.007067
/*34 */         ret = cpu_ldl_code(env, s->pc);                                          // (3) 0.07774
/*36 */         s->pc += 4;                                                              // (5) 0.04594
/*38 */         break;                                                                   // (12) 0.0318
/*40 */     default:                                                                     // (19) 0.01767
/*42 */         tcg_abort();                                                             // (6) 0.04594
/*44 */     }                                                                            // (20) 0.01413
/*46 */     return ret;                                                                  // (18) 0.0212
/*48 */ }                                                                                // (23) 0.003534
