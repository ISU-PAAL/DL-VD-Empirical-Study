// commit message qemu@85d604af5f (target=1, prob=0.9950482, correct=True): target-tricore: split up suov32 into suov32_pos and suov32_neg
/*0  */ target_ulong helper_mul_suov(CPUTriCoreState *env, target_ulong r1,  // (1) 0.1875
/*2  */                              target_ulong r2)                        // (0) 0.2431
/*4  */ {                                                                    // (6) 0.006944
/*6  */     int64_t t1 = extract64(r1, 0, 32);                               // (2) 0.1389
/*8  */     int64_t t2 = extract64(r2, 0, 32);                               // (3) 0.1389
/*10 */     int64_t result = t1 * t2;                                        // (4) 0.1042
/*14 */     return suov32(env, result);                                      // (5) 0.08333
/*16 */ }                                                                    // (7) 0.006944
