// commit message qemu@f74990a5d0 (target=0, prob=0.08871878, correct=True): s390x/tcg: refactor stfl(e) to use s390_get_feat_block()
/*0  */ static unsigned do_stfle(CPUS390XState *env, uint64_t words[MAX_STFL_WORDS])  // (1) 0.06067
/*2  */ {                                                                             // (24) 0.002092
/*4  */     S390CPU *cpu = s390_env_get_cpu(env);                                     // (10) 0.04184
/*6  */     const unsigned long *features = cpu->model->features;                     // (16) 0.03138
/*8  */     unsigned max_bit = 0;                                                     // (18) 0.02092
/*10 */     S390Feat feat;                                                            // (20) 0.01883
/*14 */     memset(words, 0, sizeof(uint64_t) * MAX_STFL_WORDS);                      // (3) 0.05439
/*18 */     if (test_bit(S390_FEAT_ZARCH, features)) {                                // (8) 0.04393
/*20 */         /* z/Architecture is always active if around */                       // (13) 0.03975
/*22 */         words[0] = 1ull << (63 - 2);                                          // (11) 0.04184
/*24 */     }                                                                         // (22) 0.008368
/*28 */     for (feat = find_first_bit(features, S390_FEAT_MAX);                      // (7) 0.04812
/*30 */          feat < S390_FEAT_MAX;                                                // (14) 0.03766
/*32 */          feat = find_next_bit(features, S390_FEAT_MAX, feat + 1)) {           // (0) 0.06485
/*34 */         const S390FeatDef *def = s390_feat_def(feat);                         // (4) 0.0523
/*36 */         if (def->type == S390_FEAT_TYPE_STFL) {                               // (5) 0.0523
/*38 */             unsigned bit = def->bit;                                          // (15) 0.03766
/*40 */             if (bit > max_bit) {                                              // (12) 0.04184
/*42 */                 max_bit = bit;                                                // (9) 0.04393
/*44 */             }                                                                 // (17) 0.0251
/*46 */             assert(bit / 64 < MAX_STFL_WORDS);                                // (6) 0.0523
/*48 */             words[bit / 64] |= 1ULL << (63 - bit % 64);                       // (2) 0.06067
/*50 */         }                                                                     // (21) 0.01674
/*52 */     }                                                                         // (23) 0.008368
/*56 */     return max_bit / 64;                                                      // (19) 0.02092
/*58 */ }                                                                             // (25) 0.002092
