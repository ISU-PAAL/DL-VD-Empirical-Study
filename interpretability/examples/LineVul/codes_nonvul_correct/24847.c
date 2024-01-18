// commit message qemu@736d120af4 (target=0, prob=0.11984339, correct=True): target-mips: add user-mode FR switch support for MIPS32r5
/*0  */ void helper_ctc1(CPUMIPSState *env, target_ulong arg1, uint32_t reg)                            // (5) 0.05273
/*2  */ {                                                                                               // (28) 0.001953
/*4  */     switch(reg) {                                                                               // (21) 0.01562
/*6  */     case 25:                                                                                    // (23) 0.01172
/*8  */         if (arg1 & 0xffffff00)                                                                  // (7) 0.03516
/*10 */             return;                                                                             // (11) 0.02539
/*12 */         env->active_fpu.fcr31 = (env->active_fpu.fcr31 & 0x017fffff) | ((arg1 & 0xfe) << 24) |  // (1) 0.0957
/*14 */                      ((arg1 & 0x1) << 23);                                                      // (3) 0.06055
/*16 */         break;                                                                                  // (16) 0.01758
/*18 */     case 26:                                                                                    // (24) 0.01172
/*20 */         if (arg1 & 0x007c0000)                                                                  // (8) 0.03516
/*22 */             return;                                                                             // (12) 0.02539
/*24 */         env->active_fpu.fcr31 = (env->active_fpu.fcr31 & 0xfffc0f83) | (arg1 & 0x0003f07c);     // (0) 0.09766
/*26 */         break;                                                                                  // (17) 0.01758
/*28 */     case 28:                                                                                    // (22) 0.01172
/*30 */         if (arg1 & 0x007c0000)                                                                  // (9) 0.03516
/*32 */             return;                                                                             // (13) 0.02539
/*34 */         env->active_fpu.fcr31 = (env->active_fpu.fcr31 & 0xfefff07c) | (arg1 & 0x00000f83) |    // (2) 0.0957
/*36 */                      ((arg1 & 0x4) << 22);                                                      // (4) 0.06055
/*38 */         break;                                                                                  // (15) 0.01758
/*40 */     case 31:                                                                                    // (25) 0.01172
/*42 */         if (arg1 & 0x007c0000)                                                                  // (10) 0.03516
/*44 */             return;                                                                             // (14) 0.02539
/*46 */         env->active_fpu.fcr31 = arg1;                                                           // (6) 0.04102
/*48 */         break;                                                                                  // (18) 0.01758
/*50 */     default:                                                                                    // (26) 0.009766
/*52 */         return;                                                                                 // (19) 0.01758
/*54 */     }                                                                                           // (27) 0.007812
/*56 */     /* set rounding mode */                                                                     // (20) 0.01563
/*58 */     restore_rounding_mode(env);                                                                 // 0.0
/*60 */     /* set flush-to-zero mode */                                                                // 0.0
/*62 */     restore_flush_mode(env);                                                                    // 0.0
/*64 */     set_float_exception_flags(0, &env->active_fpu.fp_status);                                   // 0.0
/*66 */     if ((GET_FP_ENABLE(env->active_fpu.fcr31) | 0x20) & GET_FP_CAUSE(env->active_fpu.fcr31))    // 0.0
/*68 */         do_raise_exception(env, EXCP_FPE, GETPC());                                             // 0.0
/*70 */ }                                                                                               // 0.0
