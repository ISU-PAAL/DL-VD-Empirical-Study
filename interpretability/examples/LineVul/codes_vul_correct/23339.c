// commit message qemu@fc40787abc (target=1, prob=0.95911753, correct=True): target-mips: implement unaligned loads using TCG
/*0  */ target_ulong helper_ldl(CPUMIPSState *env, target_ulong arg1,  // (10) 0.04492
/*2  */                         target_ulong arg2, int mem_idx)        // (0) 0.07031
/*4  */ {                                                              // (22) 0.001953
/*6  */     uint64_t tmp;                                              // (17) 0.01758
/*10 */     tmp = do_lbu(env, arg2, mem_idx);                          // (11) 0.03906
/*12 */     arg1 = (arg1 & 0x00FFFFFFFFFFFFFFULL) | (tmp << 56);       // (9) 0.04883
/*16 */     if (GET_LMASK64(arg2) <= 6) {                              // (13) 0.03711
/*18 */         tmp = do_lbu(env, GET_OFFSET(arg2, 1), mem_idx);       // (1) 0.06055
/*20 */         arg1 = (arg1 & 0xFF00FFFFFFFFFFFFULL) | (tmp << 48);   // (5) 0.05664
/*22 */     }                                                          // (18) 0.007813
/*26 */     if (GET_LMASK64(arg2) <= 5) {                              // (14) 0.03711
/*28 */         tmp = do_lbu(env, GET_OFFSET(arg2, 2), mem_idx);       // (2) 0.06055
/*30 */         arg1 = (arg1 & 0xFFFF00FFFFFFFFFFULL) | (tmp << 40);   // (6) 0.05664
/*32 */     }                                                          // (19) 0.007812
/*36 */     if (GET_LMASK64(arg2) <= 4) {                              // (15) 0.03711
/*38 */         tmp = do_lbu(env, GET_OFFSET(arg2, 3), mem_idx);       // (3) 0.06055
/*40 */         arg1 = (arg1 & 0xFFFFFF00FFFFFFFFULL) | (tmp << 32);   // (7) 0.05664
/*42 */     }                                                          // (20) 0.007812
/*46 */     if (GET_LMASK64(arg2) <= 3) {                              // (12) 0.03711
/*48 */         tmp = do_lbu(env, GET_OFFSET(arg2, 4), mem_idx);       // (4) 0.06055
/*50 */         arg1 = (arg1 & 0xFFFFFFFF00FFFFFFULL) | (tmp << 24);   // (8) 0.05664
/*52 */     }                                                          // (21) 0.007812
/*56 */     if (GET_LMASK64(arg2) <= 2) {                              // (16) 0.03711
/*58 */         tmp = do_lbu(env, GET_OFFSET(arg2, 5), mem_idx);       // 0.0
/*60 */         arg1 = (arg1 & 0xFFFFFFFFFF00FFFFULL) | (tmp << 16);   // 0.0
/*62 */     }                                                          // 0.0
/*66 */     if (GET_LMASK64(arg2) <= 1) {                              // 0.0
/*68 */         tmp = do_lbu(env, GET_OFFSET(arg2, 6), mem_idx);       // 0.0
/*70 */         arg1 = (arg1 & 0xFFFFFFFFFFFF00FFULL) | (tmp << 8);    // 0.0
/*72 */     }                                                          // 0.0
/*76 */     if (GET_LMASK64(arg2) == 0) {                              // 0.0
/*78 */         tmp = do_lbu(env, GET_OFFSET(arg2, 7), mem_idx);       // 0.0
/*80 */         arg1 = (arg1 & 0xFFFFFFFFFFFFFF00ULL) | tmp;           // 0.0
/*82 */     }                                                          // 0.0
/*86 */     return arg1;                                               // 0.0
/*88 */ }                                                              // 0.0
