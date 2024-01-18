// commit message qemu@b4854f1384 (target=0, prob=0.07117211, correct=True): target-i386: set G=1 in SMM big real mode selectors
/*0   */ void do_smm_enter(X86CPU *cpu)                                                   // (16) 0.02734
/*2   */ {                                                                                // (26) 0.001953
/*4   */     CPUX86State *env = &cpu->env;                                                // (15) 0.0293
/*6   */     CPUState *cs = CPU(cpu);                                                     // (17) 0.02344
/*8   */     target_ulong sm_state;                                                       // (19) 0.02148
/*10  */     SegmentCache *dt;                                                            // (21) 0.01758
/*12  */     int i, offset;                                                               // (22) 0.01562
/*16  */     qemu_log_mask(CPU_LOG_INT, "SMM: enter\n");                                  // (7) 0.04883
/*18  */     log_cpu_state_mask(CPU_LOG_INT, CPU(cpu), CPU_DUMP_CCOP);                    // (4) 0.05664
/*22  */     env->hflags |= HF_SMM_MASK;                                                  // (12) 0.0332
/*24  */     if (env->hflags2 & HF2_NMI_MASK) {                                           // (9) 0.04102
/*26  */         env->hflags2 |= HF2_SMM_INSIDE_NMI_MASK;                                 // (6) 0.05664
/*28  */     } else {                                                                     // (23) 0.01172
/*30  */         env->hflags2 |= HF2_NMI_MASK;                                            // (8) 0.04492
/*32  */     }                                                                            // (24) 0.007812
/*34  */     cpu_smm_update(env);                                                         // (18) 0.02344
/*38  */     sm_state = env->smbase + 0x8000;                                             // (13) 0.0332
/*42  */ #ifdef TARGET_X86_64                                                             // (20) 0.01953
/*44  */     for (i = 0; i < 6; i++) {                                                    // (14) 0.03125
/*46  */         dt = &env->segs[i];                                                      // (11) 0.03516
/*48  */         offset = 0x7e00 + i * 16;                                                // (10) 0.03711
/*50  */         x86_stw_phys(cs, sm_state + offset, dt->selector);                       // (5) 0.05664
/*52  */         x86_stw_phys(cs, sm_state + offset + 2, (dt->flags >> 8) & 0xf0ff);      // (0) 0.07422
/*54  */         x86_stl_phys(cs, sm_state + offset + 4, dt->limit);                      // (1) 0.05859
/*56  */         x86_stq_phys(cs, sm_state + offset + 8, dt->base);                       // (2) 0.05859
/*58  */     }                                                                            // (25) 0.007812
/*62  */     x86_stq_phys(cs, sm_state + 0x7e68, env->gdt.base);                          // (3) 0.05859
/*64  */     x86_stl_phys(cs, sm_state + 0x7e64, env->gdt.limit);                         // 0.0
/*68  */     x86_stw_phys(cs, sm_state + 0x7e70, env->ldt.selector);                      // 0.0
/*70  */     x86_stq_phys(cs, sm_state + 0x7e78, env->ldt.base);                          // 0.0
/*72  */     x86_stl_phys(cs, sm_state + 0x7e74, env->ldt.limit);                         // 0.0
/*74  */     x86_stw_phys(cs, sm_state + 0x7e72, (env->ldt.flags >> 8) & 0xf0ff);         // 0.0
/*78  */     x86_stq_phys(cs, sm_state + 0x7e88, env->idt.base);                          // 0.0
/*80  */     x86_stl_phys(cs, sm_state + 0x7e84, env->idt.limit);                         // 0.0
/*84  */     x86_stw_phys(cs, sm_state + 0x7e90, env->tr.selector);                       // 0.0
/*86  */     x86_stq_phys(cs, sm_state + 0x7e98, env->tr.base);                           // 0.0
/*88  */     x86_stl_phys(cs, sm_state + 0x7e94, env->tr.limit);                          // 0.0
/*90  */     x86_stw_phys(cs, sm_state + 0x7e92, (env->tr.flags >> 8) & 0xf0ff);          // 0.0
/*94  */     x86_stq_phys(cs, sm_state + 0x7ed0, env->efer);                              // 0.0
/*98  */     x86_stq_phys(cs, sm_state + 0x7ff8, env->regs[R_EAX]);                       // 0.0
/*100 */     x86_stq_phys(cs, sm_state + 0x7ff0, env->regs[R_ECX]);                       // 0.0
/*102 */     x86_stq_phys(cs, sm_state + 0x7fe8, env->regs[R_EDX]);                       // 0.0
/*104 */     x86_stq_phys(cs, sm_state + 0x7fe0, env->regs[R_EBX]);                       // 0.0
/*106 */     x86_stq_phys(cs, sm_state + 0x7fd8, env->regs[R_ESP]);                       // 0.0
/*108 */     x86_stq_phys(cs, sm_state + 0x7fd0, env->regs[R_EBP]);                       // 0.0
/*110 */     x86_stq_phys(cs, sm_state + 0x7fc8, env->regs[R_ESI]);                       // 0.0
/*112 */     x86_stq_phys(cs, sm_state + 0x7fc0, env->regs[R_EDI]);                       // 0.0
/*114 */     for (i = 8; i < 16; i++) {                                                   // 0.0
/*116 */         x86_stq_phys(cs, sm_state + 0x7ff8 - i * 8, env->regs[i]);               // 0.0
/*118 */     }                                                                            // 0.0
/*120 */     x86_stq_phys(cs, sm_state + 0x7f78, env->eip);                               // 0.0
/*122 */     x86_stl_phys(cs, sm_state + 0x7f70, cpu_compute_eflags(env));                // 0.0
/*124 */     x86_stl_phys(cs, sm_state + 0x7f68, env->dr[6]);                             // 0.0
/*126 */     x86_stl_phys(cs, sm_state + 0x7f60, env->dr[7]);                             // 0.0
/*130 */     x86_stl_phys(cs, sm_state + 0x7f48, env->cr[4]);                             // 0.0
/*132 */     x86_stq_phys(cs, sm_state + 0x7f50, env->cr[3]);                             // 0.0
/*134 */     x86_stl_phys(cs, sm_state + 0x7f58, env->cr[0]);                             // 0.0
/*138 */     x86_stl_phys(cs, sm_state + 0x7efc, SMM_REVISION_ID);                        // 0.0
/*140 */     x86_stl_phys(cs, sm_state + 0x7f00, env->smbase);                            // 0.0
/*142 */ #else                                                                            // 0.0
/*144 */     x86_stl_phys(cs, sm_state + 0x7ffc, env->cr[0]);                             // 0.0
/*146 */     x86_stl_phys(cs, sm_state + 0x7ff8, env->cr[3]);                             // 0.0
/*148 */     x86_stl_phys(cs, sm_state + 0x7ff4, cpu_compute_eflags(env));                // 0.0
/*150 */     x86_stl_phys(cs, sm_state + 0x7ff0, env->eip);                               // 0.0
/*152 */     x86_stl_phys(cs, sm_state + 0x7fec, env->regs[R_EDI]);                       // 0.0
/*154 */     x86_stl_phys(cs, sm_state + 0x7fe8, env->regs[R_ESI]);                       // 0.0
/*156 */     x86_stl_phys(cs, sm_state + 0x7fe4, env->regs[R_EBP]);                       // 0.0
/*158 */     x86_stl_phys(cs, sm_state + 0x7fe0, env->regs[R_ESP]);                       // 0.0
/*160 */     x86_stl_phys(cs, sm_state + 0x7fdc, env->regs[R_EBX]);                       // 0.0
/*162 */     x86_stl_phys(cs, sm_state + 0x7fd8, env->regs[R_EDX]);                       // 0.0
/*164 */     x86_stl_phys(cs, sm_state + 0x7fd4, env->regs[R_ECX]);                       // 0.0
/*166 */     x86_stl_phys(cs, sm_state + 0x7fd0, env->regs[R_EAX]);                       // 0.0
/*168 */     x86_stl_phys(cs, sm_state + 0x7fcc, env->dr[6]);                             // 0.0
/*170 */     x86_stl_phys(cs, sm_state + 0x7fc8, env->dr[7]);                             // 0.0
/*174 */     x86_stl_phys(cs, sm_state + 0x7fc4, env->tr.selector);                       // 0.0
/*176 */     x86_stl_phys(cs, sm_state + 0x7f64, env->tr.base);                           // 0.0
/*178 */     x86_stl_phys(cs, sm_state + 0x7f60, env->tr.limit);                          // 0.0
/*180 */     x86_stl_phys(cs, sm_state + 0x7f5c, (env->tr.flags >> 8) & 0xf0ff);          // 0.0
/*184 */     x86_stl_phys(cs, sm_state + 0x7fc0, env->ldt.selector);                      // 0.0
/*186 */     x86_stl_phys(cs, sm_state + 0x7f80, env->ldt.base);                          // 0.0
/*188 */     x86_stl_phys(cs, sm_state + 0x7f7c, env->ldt.limit);                         // 0.0
/*190 */     x86_stl_phys(cs, sm_state + 0x7f78, (env->ldt.flags >> 8) & 0xf0ff);         // 0.0
/*194 */     x86_stl_phys(cs, sm_state + 0x7f74, env->gdt.base);                          // 0.0
/*196 */     x86_stl_phys(cs, sm_state + 0x7f70, env->gdt.limit);                         // 0.0
/*200 */     x86_stl_phys(cs, sm_state + 0x7f58, env->idt.base);                          // 0.0
/*202 */     x86_stl_phys(cs, sm_state + 0x7f54, env->idt.limit);                         // 0.0
/*206 */     for (i = 0; i < 6; i++) {                                                    // 0.0
/*208 */         dt = &env->segs[i];                                                      // 0.0
/*210 */         if (i < 3) {                                                             // 0.0
/*212 */             offset = 0x7f84 + i * 12;                                            // 0.0
/*214 */         } else {                                                                 // 0.0
/*216 */             offset = 0x7f2c + (i - 3) * 12;                                      // 0.0
/*218 */         }                                                                        // 0.0
/*220 */         x86_stl_phys(cs, sm_state + 0x7fa8 + i * 4, dt->selector);               // 0.0
/*222 */         x86_stl_phys(cs, sm_state + offset + 8, dt->base);                       // 0.0
/*224 */         x86_stl_phys(cs, sm_state + offset + 4, dt->limit);                      // 0.0
/*226 */         x86_stl_phys(cs, sm_state + offset, (dt->flags >> 8) & 0xf0ff);          // 0.0
/*228 */     }                                                                            // 0.0
/*230 */     x86_stl_phys(cs, sm_state + 0x7f14, env->cr[4]);                             // 0.0
/*234 */     x86_stl_phys(cs, sm_state + 0x7efc, SMM_REVISION_ID);                        // 0.0
/*236 */     x86_stl_phys(cs, sm_state + 0x7ef8, env->smbase);                            // 0.0
/*238 */ #endif                                                                           // 0.0
/*240 */     /* init SMM cpu state */                                                     // 0.0
/*244 */ #ifdef TARGET_X86_64                                                             // 0.0
/*246 */     cpu_load_efer(env, 0);                                                       // 0.0
/*248 */ #endif                                                                           // 0.0
/*250 */     cpu_load_eflags(env, 0, ~(CC_O | CC_S | CC_Z | CC_A | CC_P | CC_C |          // 0.0
/*252 */                               DF_MASK));                                         // 0.0
/*254 */     env->eip = 0x00008000;                                                       // 0.0
/*256 */     cpu_x86_update_cr0(env,                                                      // 0.0
/*258 */                        env->cr[0] & ~(CR0_PE_MASK | CR0_EM_MASK | CR0_TS_MASK |  // 0.0
/*260 */                                       CR0_PG_MASK));                             // 0.0
/*262 */     cpu_x86_update_cr4(env, 0);                                                  // 0.0
/*264 */     env->dr[7] = 0x00000400;                                                     // 0.0
/*268 */     cpu_x86_load_seg_cache(env, R_CS, (env->smbase >> 4) & 0xffff, env->smbase,  // 0.0
/*270 */                            0xffffffff,                                           // 0.0
/*272 */                            DESC_P_MASK | DESC_S_MASK | DESC_W_MASK |             // 0.0
/*274 */                            DESC_A_MASK);                                         // 0.0
/*276 */     cpu_x86_load_seg_cache(env, R_DS, 0, 0, 0xffffffff,                          // 0.0
/*278 */                            DESC_P_MASK | DESC_S_MASK | DESC_W_MASK |             // 0.0
/*280 */                            DESC_A_MASK);                                         // 0.0
/*282 */     cpu_x86_load_seg_cache(env, R_ES, 0, 0, 0xffffffff,                          // 0.0
/*284 */                            DESC_P_MASK | DESC_S_MASK | DESC_W_MASK |             // 0.0
/*286 */                            DESC_A_MASK);                                         // 0.0
/*288 */     cpu_x86_load_seg_cache(env, R_SS, 0, 0, 0xffffffff,                          // 0.0
/*290 */                            DESC_P_MASK | DESC_S_MASK | DESC_W_MASK |             // 0.0
/*292 */                            DESC_A_MASK);                                         // 0.0
/*294 */     cpu_x86_load_seg_cache(env, R_FS, 0, 0, 0xffffffff,                          // 0.0
/*296 */                            DESC_P_MASK | DESC_S_MASK | DESC_W_MASK |             // 0.0
/*298 */                            DESC_A_MASK);                                         // 0.0
/*300 */     cpu_x86_load_seg_cache(env, R_GS, 0, 0, 0xffffffff,                          // 0.0
/*302 */                            DESC_P_MASK | DESC_S_MASK | DESC_W_MASK |             // 0.0
/*304 */                            DESC_A_MASK);                                         // 0.0
/*306 */ }                                                                                // 0.0
