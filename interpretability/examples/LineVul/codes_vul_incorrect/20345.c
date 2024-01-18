// commit message qemu@4e47e39ab0 (target=1, prob=0.31037647, correct=False): target-i386: Fix SSE status flag corruption
/*0   */ int x86_cpu_gdb_write_register(CPUState *cs, uint8_t *mem_buf, int n)     // (5) 0.05859
/*2   */ {                                                                         // (22) 0.001953
/*4   */     X86CPU *cpu = X86_CPU(cs);                                            // (13) 0.03125
/*6   */     CPUX86State *env = &cpu->env;                                         // (14) 0.0293
/*8   */     uint32_t tmp;                                                         // (19) 0.01758
/*12  */     if (n < CPU_NB_REGS) {                                                // (15) 0.0293
/*14  */         if (TARGET_LONG_BITS == 64 && env->hflags & HF_CS64_MASK) {       // (2) 0.06641
/*16  */             env->regs[gpr_map[n]] = ldtul_p(mem_buf);                     // (3) 0.06641
/*18  */             return sizeof(target_ulong);                                  // (11) 0.03711
/*20  */         } else if (n < CPU_NB_REGS32) {                                   // (9) 0.04297
/*22  */             n = gpr_map32[n];                                             // (10) 0.04102
/*24  */             env->regs[n] &= ~0xffffffffUL;                                // (7) 0.05273
/*26  */             env->regs[n] |= (uint32_t)ldl_p(mem_buf);                     // (1) 0.06836
/*28  */             return 4;                                                     // (16) 0.02734
/*30  */         }                                                                 // (20) 0.01562
/*32  */     } else if (n >= IDX_FP_REGS && n < IDX_FP_REGS + 8) {                 // (6) 0.05859
/*34  */ #ifdef USE_X86LDOUBLE                                                     // (17) 0.01953
/*36  */         /* FIXME: byteswap float values - after fixing fpregs layout. */  // (8) 0.05078
/*38  */         memcpy(&env->fpregs[n - IDX_FP_REGS], mem_buf, 10);               // (4) 0.06445
/*40  */ #endif                                                                    // (21) 0.003906
/*42  */         return 10;                                                        // (18) 0.01953
/*44  */     } else if (n >= IDX_XMM_REGS && n < IDX_XMM_REGS + CPU_NB_REGS) {     // (0) 0.07227
/*46  */         n -= IDX_XMM_REGS;                                                // (12) 0.03516
/*48  */         if (n < CPU_NB_REGS32 ||                                          // 0.0
/*50  */             (TARGET_LONG_BITS == 64 && env->hflags & HF_CS64_MASK)) {     // 0.0
/*52  */             env->xmm_regs[n].XMM_Q(0) = ldq_p(mem_buf);                   // 0.0
/*54  */             env->xmm_regs[n].XMM_Q(1) = ldq_p(mem_buf + 8);               // 0.0
/*56  */             return 16;                                                    // 0.0
/*58  */         }                                                                 // 0.0
/*60  */     } else {                                                              // 0.0
/*62  */         switch (n) {                                                      // 0.0
/*64  */         case IDX_IP_REG:                                                  // 0.0
/*66  */             if (TARGET_LONG_BITS == 64 && env->hflags & HF_CS64_MASK) {   // 0.0
/*68  */                 env->eip = ldq_p(mem_buf);                                // 0.0
/*70  */                 return 8;                                                 // 0.0
/*72  */             } else {                                                      // 0.0
/*74  */                 env->eip &= ~0xffffffffUL;                                // 0.0
/*76  */                 env->eip |= (uint32_t)ldl_p(mem_buf);                     // 0.0
/*78  */                 return 4;                                                 // 0.0
/*80  */             }                                                             // 0.0
/*82  */         case IDX_FLAGS_REG:                                               // 0.0
/*84  */             env->eflags = ldl_p(mem_buf);                                 // 0.0
/*86  */             return 4;                                                     // 0.0
/*90  */         case IDX_SEG_REGS:                                                // 0.0
/*92  */             return x86_cpu_gdb_load_seg(cpu, R_CS, mem_buf);              // 0.0
/*94  */         case IDX_SEG_REGS + 1:                                            // 0.0
/*96  */             return x86_cpu_gdb_load_seg(cpu, R_SS, mem_buf);              // 0.0
/*98  */         case IDX_SEG_REGS + 2:                                            // 0.0
/*100 */             return x86_cpu_gdb_load_seg(cpu, R_DS, mem_buf);              // 0.0
/*102 */         case IDX_SEG_REGS + 3:                                            // 0.0
/*104 */             return x86_cpu_gdb_load_seg(cpu, R_ES, mem_buf);              // 0.0
/*106 */         case IDX_SEG_REGS + 4:                                            // 0.0
/*108 */             return x86_cpu_gdb_load_seg(cpu, R_FS, mem_buf);              // 0.0
/*110 */         case IDX_SEG_REGS + 5:                                            // 0.0
/*112 */             return x86_cpu_gdb_load_seg(cpu, R_GS, mem_buf);              // 0.0
/*116 */         case IDX_FP_REGS + 8:                                             // 0.0
/*118 */             env->fpuc = ldl_p(mem_buf);                                   // 0.0
/*120 */             return 4;                                                     // 0.0
/*122 */         case IDX_FP_REGS + 9:                                             // 0.0
/*124 */             tmp = ldl_p(mem_buf);                                         // 0.0
/*126 */             env->fpstt = (tmp >> 11) & 7;                                 // 0.0
/*128 */             env->fpus = tmp & ~0x3800;                                    // 0.0
/*130 */             return 4;                                                     // 0.0
/*132 */         case IDX_FP_REGS + 10: /* ftag */                                 // 0.0
/*134 */             return 4;                                                     // 0.0
/*136 */         case IDX_FP_REGS + 11: /* fiseg */                                // 0.0
/*138 */             return 4;                                                     // 0.0
/*140 */         case IDX_FP_REGS + 12: /* fioff */                                // 0.0
/*142 */             return 4;                                                     // 0.0
/*144 */         case IDX_FP_REGS + 13: /* foseg */                                // 0.0
/*146 */             return 4;                                                     // 0.0
/*148 */         case IDX_FP_REGS + 14: /* fooff */                                // 0.0
/*150 */             return 4;                                                     // 0.0
/*152 */         case IDX_FP_REGS + 15: /* fop */                                  // 0.0
/*154 */             return 4;                                                     // 0.0
/*158 */         case IDX_MXCSR_REG:                                               // 0.0
/*160 */             env->mxcsr = ldl_p(mem_buf);                                  // 0.0
/*162 */             return 4;                                                     // 0.0
/*164 */         }                                                                 // 0.0
/*166 */     }                                                                     // 0.0
/*168 */     /* Unrecognised register.  */                                         // 0.0
/*170 */     return 0;                                                             // 0.0
/*172 */ }                                                                         // 0.0
