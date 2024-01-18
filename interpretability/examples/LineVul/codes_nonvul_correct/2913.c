// commit message qemu@ff1d1977ff (target=0, prob=0.14127827, correct=True): gdbstub: add MIPS16 support
/*0  */ static int cpu_gdb_write_register(CPUState *env, uint8_t *mem_buf, int n)  // (5) 0.05469
/*2  */ {                                                                          // (26) 0.001953
/*4  */     target_ulong tmp;                                                      // (22) 0.01758
/*8  */     tmp = ldtul_p(mem_buf);                                                // (14) 0.0293
/*12 */     if (n < 32) {                                                          // (20) 0.01953
/*14 */         env->active_tc.gpr[n] = tmp;                                       // (8) 0.04102
/*16 */         return sizeof(target_ulong);                                       // (13) 0.0293
/*18 */     }                                                                      // (24) 0.007812
/*20 */     if (env->CP0_Config1 & (1 << CP0C1_FP)                                 // (7) 0.04492
/*22 */             && n >= 38 && n < 73) {                                        // (9) 0.04102
/*24 */         if (n < 70) {                                                      // (15) 0.02734
/*26 */             if (env->CP0_Status & (1 << CP0St_FR))                         // (4) 0.05664
/*28 */               env->active_fpu.fpr[n - 38].d = tmp;                         // (1) 0.06055
/*30 */             else                                                           // (17) 0.02344
/*32 */               env->active_fpu.fpr[n - 38].w[FP_ENDIAN_IDX] = tmp;          // (0) 0.07812
/*34 */         }                                                                  // (23) 0.01562
/*36 */         switch (n) {                                                       // (18) 0.02344
/*38 */         case 70:                                                           // (21) 0.01953
/*40 */             env->active_fpu.fcr31 = tmp & 0xFF83FFFF;                      // (3) 0.05859
/*42 */             /* set rounding mode */                                        // (12) 0.03125
/*44 */             RESTORE_ROUNDING_MODE;                                         // (11) 0.03906
/*46 */ #ifndef CONFIG_SOFTFLOAT                                                   // (19) 0.02148
/*48 */             /* no floating point exception for native float */             // (10) 0.03906
/*50 */             SET_FP_ENABLE(env->active_fpu.fcr31, 0);                       // (2) 0.06055
/*52 */ #endif                                                                     // (25) 0.003906
/*54 */             break;                                                         // (16) 0.02539
/*56 */         case 71: env->active_fpu.fcr0 = tmp; break;                        // (6) 0.04883
/*58 */         }                                                                  // 0.0
/*60 */         return sizeof(target_ulong);                                       // 0.0
/*62 */     }                                                                      // 0.0
/*64 */     switch (n) {                                                           // 0.0
/*66 */     case 32: env->CP0_Status = tmp; break;                                 // 0.0
/*68 */     case 33: env->active_tc.LO[0] = tmp; break;                            // 0.0
/*70 */     case 34: env->active_tc.HI[0] = tmp; break;                            // 0.0
/*72 */     case 35: env->CP0_BadVAddr = tmp; break;                               // 0.0
/*74 */     case 36: env->CP0_Cause = tmp; break;                                  // 0.0
/*76 */     case 37: env->active_tc.PC = tmp; break;                               // 0.0
/*78 */     case 72: /* fp, ignored */ break;                                      // 0.0
/*80 */     default:                                                               // 0.0
/*82 */ 	if (n > 89)                                                               // 0.0
/*84 */ 	    return 0;                                                             // 0.0
/*86 */ 	/* Other registers are readonly.  Ignore writes.  */                      // 0.0
/*88 */ 	break;                                                                    // 0.0
/*90 */     }                                                                      // 0.0
/*94 */     return sizeof(target_ulong);                                           // 0.0
/*96 */ }                                                                          // 0.0
