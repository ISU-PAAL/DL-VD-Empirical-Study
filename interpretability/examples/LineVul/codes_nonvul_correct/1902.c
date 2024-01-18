// commit message qemu@fc89efe693 (target=0, prob=0.077582225, correct=True): target-s390x: mvc_fast_memset: access memory through softmmu
/*0  */ void HELPER(mvc)(CPUS390XState *env, uint32_t l, uint64_t dest, uint64_t src)  // (4) 0.06445
/*2  */ {                                                                              // (24) 0.001953
/*4  */     int i = 0;                                                                 // (20) 0.01562
/*6  */     int x = 0;                                                                 // (19) 0.01563
/*8  */     uint32_t l_64 = (l + 1) / 8;                                               // (11) 0.03711
/*12 */     HELPER_LOG("%s l %d dest %" PRIx64 " src %" PRIx64 "\n",                   // (5) 0.06055
/*14 */                __func__, l, dest, src);                                        // (8) 0.04688
/*18 */ #ifndef CONFIG_USER_ONLY                                                       // (17) 0.01953
/*20 */     if ((l > 32) &&                                                            // (16) 0.01953
/*22 */         (src & TARGET_PAGE_MASK) == ((src + l) & TARGET_PAGE_MASK) &&          // (2) 0.07031
/*24 */         (dest & TARGET_PAGE_MASK) == ((dest + l) & TARGET_PAGE_MASK)) {        // (1) 0.07031
/*26 */         if (dest == (src + 1)) {                                               // (12) 0.0332
/*28 */             mvc_fast_memset(env, l + 1, dest, cpu_ldub_data(env, src));        // (0) 0.07422
/*30 */             return;                                                            // (15) 0.02539
/*32 */         } else if ((src & TARGET_PAGE_MASK) != (dest & TARGET_PAGE_MASK)) {    // (3) 0.07031
/*34 */             mvc_fast_memmove(env, l + 1, dest, src);                           // (7) 0.05664
/*36 */             return;                                                            // (14) 0.02539
/*38 */         }                                                                      // (21) 0.01562
/*40 */     }                                                                          // (22) 0.007812
/*42 */ #else                                                                          // (23) 0.003906
/*44 */     if (dest == (src + 1)) {                                                   // (13) 0.02539
/*46 */         memset(g2h(dest), cpu_ldub_data(env, src), l + 1);                     // (6) 0.06055
/*48 */         return;                                                                // (18) 0.01758
/*50 */     /* mvc and memmove do not behave the same when areas overlap! */           // (10) 0.03711
/*52 */     } else if ((dest < src) || (src + l < dest)) {                             // (9) 0.03906
/*54 */         memmove(g2h(dest), g2h(src), l + 1);                                   // 0.0
/*56 */         return;                                                                // 0.0
/*58 */     }                                                                          // 0.0
/*60 */ #endif                                                                         // 0.0
/*64 */     /* handle the parts that fit into 8-byte loads/stores */                   // 0.0
/*66 */     if ((dest + 8 <= src) || (src + 8 <= dest)) {                              // 0.0
/*68 */         for (i = 0; i < l_64; i++) {                                           // 0.0
/*70 */             cpu_stq_data(env, dest + x, cpu_ldq_data(env, src + x));           // 0.0
/*72 */             x += 8;                                                            // 0.0
/*74 */         }                                                                      // 0.0
/*76 */     }                                                                          // 0.0
/*80 */     /* slow version with byte accesses which always work */                    // 0.0
/*82 */     for (i = x; i <= l; i++) {                                                 // 0.0
/*84 */         cpu_stb_data(env, dest + i, cpu_ldub_data(env, src + i));              // 0.0
/*86 */     }                                                                          // 0.0
/*88 */ }                                                                              // 0.0
