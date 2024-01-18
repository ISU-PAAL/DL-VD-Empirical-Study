// commit message qemu@1e577cc7cf (target=0, prob=0.36909696, correct=True): target/arm: Add state field, feature bit and migration for v8M secure state
/*0   */ void arm_cpu_dump_state(CPUState *cs, FILE *f, fprintf_function cpu_fprintf,  // (3) 0.05273
/*2   */                         int flags)                                            // (4) 0.05078
/*4   */ {                                                                             // (27) 0.001953
/*6   */     ARMCPU *cpu = ARM_CPU(cs);                                                // (15) 0.0293
/*8   */     CPUARMState *env = &cpu->env;                                             // (16) 0.02734
/*10  */     int i;                                                                    // (24) 0.01172
/*14  */     if (is_a64(env)) {                                                        // (18) 0.02539
/*16  */         aarch64_cpu_dump_state(cs, f, cpu_fprintf, flags);                    // (2) 0.05469
/*18  */         return;                                                               // (22) 0.01758
/*20  */     }                                                                         // (25) 0.007812
/*24  */     for(i=0;i<16;i++) {                                                       // (12) 0.03125
/*26  */         cpu_fprintf(f, "R%02d=%08x", i, env->regs[i]);                        // (1) 0.06445
/*28  */         if ((i % 4) == 3)                                                     // (13) 0.03125
/*30  */             cpu_fprintf(f, "\n");                                             // (8) 0.04102
/*32  */         else                                                                  // (23) 0.01562
/*34  */             cpu_fprintf(f, " ");                                              // (9) 0.04102
/*36  */     }                                                                         // (26) 0.007812
/*40  */     if (arm_feature(env, ARM_FEATURE_M)) {                                    // (11) 0.03711
/*42  */         uint32_t xpsr = xpsr_read(env);                                       // (5) 0.04492
/*44  */         const char *mode;                                                     // (19) 0.02344
/*48  */         if (xpsr & XPSR_EXCP) {                                               // (10) 0.04102
/*50  */             mode = "handler";                                                 // (14) 0.03125
/*52  */         } else {                                                              // (21) 0.01953
/*54  */             if (env->v7m.control & R_V7M_CONTROL_NPRIV_MASK) {                // (0) 0.07422
/*56  */                 mode = "unpriv-thread";                                       // (6) 0.04492
/*58  */             } else {                                                          // (17) 0.02734
/*60  */                 mode = "priv-thread";                                         // (7) 0.04297
/*62  */             }                                                                 // (20) 0.02344
/*64  */         }                                                                     // 0.0
/*68  */         cpu_fprintf(f, "XPSR=%08x %c%c%c%c %c %s\n",                          // 0.0
/*70  */                     xpsr,                                                     // 0.0
/*72  */                     xpsr & XPSR_N ? 'N' : '-',                                // 0.0
/*74  */                     xpsr & XPSR_Z ? 'Z' : '-',                                // 0.0
/*76  */                     xpsr & XPSR_C ? 'C' : '-',                                // 0.0
/*78  */                     xpsr & XPSR_V ? 'V' : '-',                                // 0.0
/*80  */                     xpsr & XPSR_T ? 'T' : 'A',                                // 0.0
/*82  */                     mode);                                                    // 0.0
/*84  */     } else {                                                                  // 0.0
/*86  */         uint32_t psr = cpsr_read(env);                                        // 0.0
/*88  */         const char *ns_status = "";                                           // 0.0
/*92  */         if (arm_feature(env, ARM_FEATURE_EL3) &&                              // 0.0
/*94  */             (psr & CPSR_M) != ARM_CPU_MODE_MON) {                             // 0.0
/*96  */             ns_status = env->cp15.scr_el3 & SCR_NS ? "NS " : "S ";            // 0.0
/*98  */         }                                                                     // 0.0
/*102 */         cpu_fprintf(f, "PSR=%08x %c%c%c%c %c %s%s%d\n",                       // 0.0
/*104 */                     psr,                                                      // 0.0
/*106 */                     psr & CPSR_N ? 'N' : '-',                                 // 0.0
/*108 */                     psr & CPSR_Z ? 'Z' : '-',                                 // 0.0
/*110 */                     psr & CPSR_C ? 'C' : '-',                                 // 0.0
/*112 */                     psr & CPSR_V ? 'V' : '-',                                 // 0.0
/*114 */                     psr & CPSR_T ? 'T' : 'A',                                 // 0.0
/*116 */                     ns_status,                                                // 0.0
/*118 */                     cpu_mode_names[psr & 0xf], (psr & 0x10) ? 32 : 26);       // 0.0
/*120 */     }                                                                         // 0.0
/*124 */     if (flags & CPU_DUMP_FPU) {                                               // 0.0
/*126 */         int numvfpregs = 0;                                                   // 0.0
/*128 */         if (arm_feature(env, ARM_FEATURE_VFP)) {                              // 0.0
/*130 */             numvfpregs += 16;                                                 // 0.0
/*132 */         }                                                                     // 0.0
/*134 */         if (arm_feature(env, ARM_FEATURE_VFP3)) {                             // 0.0
/*136 */             numvfpregs += 16;                                                 // 0.0
/*138 */         }                                                                     // 0.0
/*140 */         for (i = 0; i < numvfpregs; i++) {                                    // 0.0
/*142 */             uint64_t v = float64_val(env->vfp.regs[i]);                       // 0.0
/*144 */             cpu_fprintf(f, "s%02d=%08x s%02d=%08x d%02d=%016" PRIx64 "\n",    // 0.0
/*146 */                         i * 2, (uint32_t)v,                                   // 0.0
/*148 */                         i * 2 + 1, (uint32_t)(v >> 32),                       // 0.0
/*150 */                         i, v);                                                // 0.0
/*152 */         }                                                                     // 0.0
/*154 */         cpu_fprintf(f, "FPSCR: %08x\n", (int)env->vfp.xregs[ARM_VFP_FPSCR]);  // 0.0
/*156 */     }                                                                         // 0.0
/*158 */ }                                                                             // 0.0
