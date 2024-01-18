// commit message qemu@fea7d77d3e (target=0, prob=0.0058054985, correct=True): target/sh4: fix FPU unorderered compare
/*0  */ void helper_fcmp_gt_DT(CPUSH4State *env, float64 t0, float64 t1)  // (0) 0.1646
/*2  */ {                                                                 // (9) 0.006098
/*4  */     int relation;                                                 // (6) 0.03659
/*8  */     set_float_exception_flags(0, &env->fp_status);                // (3) 0.128
/*10 */     relation = float64_compare(t0, t1, &env->fp_status);          // (1) 0.1463
/*12 */     if (unlikely(relation == float_relation_unordered)) {         // (4) 0.1098
/*14 */         update_fpscr(env, GETPC());                               // (5) 0.1037
/*16 */     } else {                                                      // (7) 0.03659
/*18 */         env->sr_t = (relation == float_relation_greater);         // (2) 0.1402
/*20 */     }                                                             // (8) 0.02439
/*22 */ }                                                                 // (10) 0.006098
