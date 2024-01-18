// commit message qemu@5e755519ac (target=0, prob=0.20676585, correct=True): Don't check the FPU state for each FPU instruction, use hflags to handle this per-tb.
/*0  */ void cpu_dump_state (CPUState *env, FILE *f,                                                                               // (9) 0.0332
/*2  */                      int (*cpu_fprintf)(FILE *f, const char *fmt, ...),                                                    // (3) 0.07617
/*4  */                      int flags)                                                                                            // (7) 0.04492
/*6  */ {                                                                                                                          // (18) 0.001953
/*8  */     uint32_t c0_status;                                                                                                    // (14) 0.02344
/*10 */     int i;                                                                                                                 // (15) 0.01172
/*12 */                                                                                                                            // (16) 0.007812
/*14 */     cpu_fprintf(f, "pc=0x" TARGET_FMT_lx " HI=0x" TARGET_FMT_lx " LO=0x" TARGET_FMT_lx " ds %04x " TARGET_FMT_lx " %d\n",  // (0) 0.1426
/*16 */                 env->PC, env->HI, env->LO, env->hflags, env->btarget, env->bcond);                                         // (2) 0.08203
/*18 */     for (i = 0; i < 32; i++) {                                                                                             // (10) 0.03125
/*20 */         if ((i & 3) == 0)                                                                                                  // (11) 0.03125
/*22 */             cpu_fprintf(f, "GPR%02d:", i);                                                                                 // (6) 0.05469
/*24 */         cpu_fprintf(f, " %s " TARGET_FMT_lx, regnames[i], env->gpr[i]);                                                    // (4) 0.07617
/*26 */         if ((i & 3) == 3)                                                                                                  // (12) 0.03125
/*28 */             cpu_fprintf(f, "\n");                                                                                          // (8) 0.04102
/*30 */     }                                                                                                                      // (17) 0.007812
/*34 */     c0_status = env->CP0_Status;                                                                                           // (13) 0.0293
/*38 */     cpu_fprintf(f, "CP0 Status  0x%08x Cause   0x%08x EPC    0x" TARGET_FMT_lx "\n",                                       // (1) 0.0918
/*40 */                 c0_status, env->CP0_Cause, env->CP0_EPC);                                                                  // (5) 0.06836
/*42 */     cpu_fprintf(f, "    Config0 0x%08x Config1 0x%08x LLAddr 0x" TARGET_FMT_lx "\n",                                       // 0.0
/*44 */                 env->CP0_Config0, env->CP0_Config1, env->CP0_LLAddr);                                                      // 0.0
/*46 */     if (c0_status & (1 << CP0St_CU1))                                                                                      // 0.0
/*48 */         fpu_dump_state(env, f, cpu_fprintf, flags);                                                                        // 0.0
/*50 */ #if defined(TARGET_MIPS64) && defined(MIPS_DEBUG_SIGN_EXTENSIONS)                                                          // 0.0
/*52 */     cpu_mips_check_sign_extensions(env, f, cpu_fprintf, flags);                                                            // 0.0
/*54 */ #endif                                                                                                                     // 0.0
/*56 */ }                                                                                                                          // 0.0
