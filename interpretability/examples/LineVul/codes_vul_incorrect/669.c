// commit message qemu@e95e9b88ba (target=1, prob=0.04322188, correct=False): target/i386: fix interrupt CPL error when using ist in x86-64
/*0   */ static void do_interrupt64(CPUX86State *env, int intno, int is_int,             // (2) 0.04687
/*2   */                            int error_code, target_ulong next_eip, int is_hw)    // (0) 0.08787
/*4   */ {                                                                               // (32) 0.00196
/*6   */     SegmentCache *dt;                                                           // (22) 0.01767
/*8   */     target_ulong ptr;                                                           // (23) 0.01758
/*10  */     int type, dpl, selector, cpl, ist;                                          // (9) 0.03327
/*12  */     int has_error_code, new_stack;                                              // (16) 0.02734
/*14  */     uint32_t e1, e2, e3, ss;                                                    // (8) 0.03515
/*16  */     target_ulong old_eip, esp, offset;                                          // (13) 0.03124
/*20  */     has_error_code = 0;                                                         // (20) 0.02148
/*22  */     if (!is_int && !is_hw) {                                                    // (15) 0.02929
/*24  */         has_error_code = exception_has_error_code(intno);                       // (3) 0.04687
/*26  */     }                                                                           // (29) 0.007811
/*28  */     if (is_int) {                                                               // (21) 0.01953
/*30  */         old_eip = next_eip;                                                     // (12) 0.0332
/*32  */     } else {                                                                    // (27) 0.01172
/*34  */         old_eip = env->eip;                                                     // (11) 0.0332
/*36  */     }                                                                           // (30) 0.007811
/*40  */     dt = &env->idt;                                                             // (17) 0.02343
/*42  */     if (intno * 16 + 15 > dt->limit) {                                          // (7) 0.03515
/*44  */         raise_exception_err(env, EXCP0D_GPF, intno * 16 + 2);                   // (1) 0.06053
/*46  */     }                                                                           // (31) 0.007811
/*48  */     ptr = dt->base + intno * 16;                                                // (14) 0.02929
/*50  */     e1 = cpu_ldl_kernel(env, ptr);                                              // (10) 0.0332
/*52  */     e2 = cpu_ldl_kernel(env, ptr + 4);                                          // (6) 0.0371
/*54  */     e3 = cpu_ldl_kernel(env, ptr + 8);                                          // (5) 0.0371
/*56  */     /* check gate type */                                                       // (25) 0.01562
/*58  */     type = (e2 >> DESC_TYPE_SHIFT) & 0x1f;                                      // (4) 0.04491
/*60  */     switch (type) {                                                             // (26) 0.01562
/*62  */     case 14: /* 386 interrupt gate */                                           // (18) 0.02148
/*64  */     case 15: /* 386 trap gate */                                                // (19) 0.02148
/*66  */         break;                                                                  // (24) 0.01757
/*68  */     default:                                                                    // (28) 0.009763
/*70  */         raise_exception_err(env, EXCP0D_GPF, intno * 16 + 2);                   // 0.0
/*72  */         break;                                                                  // 0.0
/*74  */     }                                                                           // 0.0
/*76  */     dpl = (e2 >> DESC_DPL_SHIFT) & 3;                                           // 0.0
/*78  */     cpl = env->hflags & HF_CPL_MASK;                                            // 0.0
/*80  */     /* check privilege if software int */                                       // 0.0
/*82  */     if (is_int && dpl < cpl) {                                                  // 0.0
/*84  */         raise_exception_err(env, EXCP0D_GPF, intno * 16 + 2);                   // 0.0
/*86  */     }                                                                           // 0.0
/*88  */     /* check valid bit */                                                       // 0.0
/*90  */     if (!(e2 & DESC_P_MASK)) {                                                  // 0.0
/*92  */         raise_exception_err(env, EXCP0B_NOSEG, intno * 16 + 2);                 // 0.0
/*94  */     }                                                                           // 0.0
/*96  */     selector = e1 >> 16;                                                        // 0.0
/*98  */     offset = ((target_ulong)e3 << 32) | (e2 & 0xffff0000) | (e1 & 0x0000ffff);  // 0.0
/*100 */     ist = e2 & 7;                                                               // 0.0
/*102 */     if ((selector & 0xfffc) == 0) {                                             // 0.0
/*104 */         raise_exception_err(env, EXCP0D_GPF, 0);                                // 0.0
/*106 */     }                                                                           // 0.0
/*110 */     if (load_segment(env, &e1, &e2, selector) != 0) {                           // 0.0
/*112 */         raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);                // 0.0
/*114 */     }                                                                           // 0.0
/*116 */     if (!(e2 & DESC_S_MASK) || !(e2 & (DESC_CS_MASK))) {                        // 0.0
/*118 */         raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);                // 0.0
/*120 */     }                                                                           // 0.0
/*122 */     dpl = (e2 >> DESC_DPL_SHIFT) & 3;                                           // 0.0
/*124 */     if (dpl > cpl) {                                                            // 0.0
/*126 */         raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);                // 0.0
/*128 */     }                                                                           // 0.0
/*130 */     if (!(e2 & DESC_P_MASK)) {                                                  // 0.0
/*132 */         raise_exception_err(env, EXCP0B_NOSEG, selector & 0xfffc);              // 0.0
/*134 */     }                                                                           // 0.0
/*136 */     if (!(e2 & DESC_L_MASK) || (e2 & DESC_B_MASK)) {                            // 0.0
/*138 */         raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);                // 0.0
/*140 */     }                                                                           // 0.0
/*142 */     if ((!(e2 & DESC_C_MASK) && dpl < cpl) || ist != 0) {                       // 0.0
/*144 */         /* to inner privilege */                                                // 0.0
/*146 */         new_stack = 1;                                                          // 0.0
/*148 */         esp = get_rsp_from_tss(env, ist != 0 ? ist + 3 : dpl);                  // 0.0
/*150 */         ss = 0;                                                                 // 0.0
/*152 */     } else if ((e2 & DESC_C_MASK) || dpl == cpl) {                              // 0.0
/*154 */         /* to same privilege */                                                 // 0.0
/*156 */         if (env->eflags & VM_MASK) {                                            // 0.0
/*158 */             raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);            // 0.0
/*160 */         }                                                                       // 0.0
/*162 */         new_stack = 0;                                                          // 0.0
/*164 */         esp = env->regs[R_ESP];                                                 // 0.0
/*166 */         dpl = cpl;                                                              // 0.0
/*168 */     } else {                                                                    // 0.0
/*170 */         raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);                // 0.0
/*172 */         new_stack = 0; /* avoid warning */                                      // 0.0
/*174 */         esp = 0; /* avoid warning */                                            // 0.0
/*176 */     }                                                                           // 0.0
/*178 */     esp &= ~0xfLL; /* align stack */                                            // 0.0
/*182 */     PUSHQ(esp, env->segs[R_SS].selector);                                       // 0.0
/*184 */     PUSHQ(esp, env->regs[R_ESP]);                                               // 0.0
/*186 */     PUSHQ(esp, cpu_compute_eflags(env));                                        // 0.0
/*188 */     PUSHQ(esp, env->segs[R_CS].selector);                                       // 0.0
/*190 */     PUSHQ(esp, old_eip);                                                        // 0.0
/*192 */     if (has_error_code) {                                                       // 0.0
/*194 */         PUSHQ(esp, error_code);                                                 // 0.0
/*196 */     }                                                                           // 0.0
/*200 */     /* interrupt gate clear IF mask */                                          // 0.0
/*202 */     if ((type & 1) == 0) {                                                      // 0.0
/*204 */         env->eflags &= ~IF_MASK;                                                // 0.0
/*206 */     }                                                                           // 0.0
/*208 */     env->eflags &= ~(TF_MASK | VM_MASK | RF_MASK | NT_MASK);                    // 0.0
/*212 */     if (new_stack) {                                                            // 0.0
/*214 */         ss = 0 | dpl;                                                           // 0.0
/*216 */         cpu_x86_load_seg_cache(env, R_SS, ss, 0, 0, 0);                         // 0.0
/*218 */     }                                                                           // 0.0
/*220 */     env->regs[R_ESP] = esp;                                                     // 0.0
/*224 */     selector = (selector & ~3) | dpl;                                           // 0.0
/*226 */     cpu_x86_load_seg_cache(env, R_CS, selector,                                 // 0.0
/*228 */                    get_seg_base(e1, e2),                                        // 0.0
/*230 */                    get_seg_limit(e1, e2),                                       // 0.0
/*232 */                    e2);                                                         // 0.0
/*234 */     env->eip = offset;                                                          // 0.0
/*236 */ }                                                                               // 0.0
