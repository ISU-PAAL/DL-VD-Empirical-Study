// commit message qemu@1110bfe6f5 (target=0, prob=0.066288464, correct=True): target/i386: simplify handling of conforming code segments on interrupt
/*0   */ static void do_interrupt_protected(CPUX86State *env, int intno, int is_int,  // (4) 0.04883
/*2   */                                    int error_code, unsigned int next_eip,    // (0) 0.08984
/*4   */                                    int is_hw)                                // (1) 0.07617
/*6   */ {                                                                            // (27) 0.001953
/*8   */     SegmentCache *dt;                                                        // (21) 0.01758
/*10  */     target_ulong ptr, ssp;                                                   // (17) 0.02344
/*12  */     int type, dpl, selector, ss_dpl, cpl;                                    // (6) 0.03711
/*14  */     int has_error_code, new_stack, shift;                                    // (13) 0.03125
/*16  */     uint32_t e1, e2, offset, ss = 0, esp, ss_e1 = 0, ss_e2 = 0;              // (2) 0.06836
/*18  */     uint32_t old_eip, sp_mask;                                               // (14) 0.03125
/*20  */     int vm86 = env->eflags & VM_MASK;                                        // (8) 0.03516
/*24  */     has_error_code = 0;                                                      // (19) 0.02148
/*26  */     if (!is_int && !is_hw) {                                                 // (16) 0.0293
/*28  */         has_error_code = exception_has_error_code(intno);                    // (5) 0.04687
/*30  */     }                                                                        // (24) 0.007812
/*32  */     if (is_int) {                                                            // (20) 0.01953
/*34  */         old_eip = next_eip;                                                  // (11) 0.0332
/*36  */     } else {                                                                 // (23) 0.01172
/*38  */         old_eip = env->eip;                                                  // (12) 0.0332
/*40  */     }                                                                        // (25) 0.007812
/*44  */     dt = &env->idt;                                                          // (18) 0.02344
/*46  */     if (intno * 8 + 7 > dt->limit) {                                         // (9) 0.03516
/*48  */         raise_exception_err(env, EXCP0D_GPF, intno * 8 + 2);                 // (3) 0.06055
/*50  */     }                                                                        // (26) 0.007812
/*52  */     ptr = dt->base + intno * 8;                                              // (15) 0.0293
/*54  */     e1 = cpu_ldl_kernel(env, ptr);                                           // (10) 0.0332
/*56  */     e2 = cpu_ldl_kernel(env, ptr + 4);                                       // (7) 0.03711
/*58  */     /* check gate type */                                                    // (22) 0.01563
/*60  */     type = (e2 >> DESC_TYPE_SHIFT) & 0x1f;                                   // 0.0
/*62  */     switch (type) {                                                          // 0.0
/*64  */     case 5: /* task gate */                                                  // 0.0
/*66  */         /* must do that check here to return the correct error code */       // 0.0
/*68  */         if (!(e2 & DESC_P_MASK)) {                                           // 0.0
/*70  */             raise_exception_err(env, EXCP0B_NOSEG, intno * 8 + 2);           // 0.0
/*72  */         }                                                                    // 0.0
/*74  */         switch_tss(env, intno * 8, e1, e2, SWITCH_TSS_CALL, old_eip);        // 0.0
/*76  */         if (has_error_code) {                                                // 0.0
/*78  */             int type;                                                        // 0.0
/*80  */             uint32_t mask;                                                   // 0.0
/*84  */             /* push the error code */                                        // 0.0
/*86  */             type = (env->tr.flags >> DESC_TYPE_SHIFT) & 0xf;                 // 0.0
/*88  */             shift = type >> 3;                                               // 0.0
/*90  */             if (env->segs[R_SS].flags & DESC_B_MASK) {                       // 0.0
/*92  */                 mask = 0xffffffff;                                           // 0.0
/*94  */             } else {                                                         // 0.0
/*96  */                 mask = 0xffff;                                               // 0.0
/*98  */             }                                                                // 0.0
/*100 */             esp = (env->regs[R_ESP] - (2 << shift)) & mask;                  // 0.0
/*102 */             ssp = env->segs[R_SS].base + esp;                                // 0.0
/*104 */             if (shift) {                                                     // 0.0
/*106 */                 cpu_stl_kernel(env, ssp, error_code);                        // 0.0
/*108 */             } else {                                                         // 0.0
/*110 */                 cpu_stw_kernel(env, ssp, error_code);                        // 0.0
/*112 */             }                                                                // 0.0
/*114 */             SET_ESP(esp, mask);                                              // 0.0
/*116 */         }                                                                    // 0.0
/*118 */         return;                                                              // 0.0
/*120 */     case 6: /* 286 interrupt gate */                                         // 0.0
/*122 */     case 7: /* 286 trap gate */                                              // 0.0
/*124 */     case 14: /* 386 interrupt gate */                                        // 0.0
/*126 */     case 15: /* 386 trap gate */                                             // 0.0
/*128 */         break;                                                               // 0.0
/*130 */     default:                                                                 // 0.0
/*132 */         raise_exception_err(env, EXCP0D_GPF, intno * 8 + 2);                 // 0.0
/*134 */         break;                                                               // 0.0
/*136 */     }                                                                        // 0.0
/*138 */     dpl = (e2 >> DESC_DPL_SHIFT) & 3;                                        // 0.0
/*140 */     cpl = env->hflags & HF_CPL_MASK;                                         // 0.0
/*142 */     /* check privilege if software int */                                    // 0.0
/*144 */     if (is_int && dpl < cpl) {                                               // 0.0
/*146 */         raise_exception_err(env, EXCP0D_GPF, intno * 8 + 2);                 // 0.0
/*148 */     }                                                                        // 0.0
/*150 */     /* check valid bit */                                                    // 0.0
/*152 */     if (!(e2 & DESC_P_MASK)) {                                               // 0.0
/*154 */         raise_exception_err(env, EXCP0B_NOSEG, intno * 8 + 2);               // 0.0
/*156 */     }                                                                        // 0.0
/*158 */     selector = e1 >> 16;                                                     // 0.0
/*160 */     offset = (e2 & 0xffff0000) | (e1 & 0x0000ffff);                          // 0.0
/*162 */     if ((selector & 0xfffc) == 0) {                                          // 0.0
/*164 */         raise_exception_err(env, EXCP0D_GPF, 0);                             // 0.0
/*166 */     }                                                                        // 0.0
/*168 */     if (load_segment(env, &e1, &e2, selector) != 0) {                        // 0.0
/*170 */         raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);             // 0.0
/*172 */     }                                                                        // 0.0
/*174 */     if (!(e2 & DESC_S_MASK) || !(e2 & (DESC_CS_MASK))) {                     // 0.0
/*176 */         raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);             // 0.0
/*178 */     }                                                                        // 0.0
/*180 */     dpl = (e2 >> DESC_DPL_SHIFT) & 3;                                        // 0.0
/*182 */     if (dpl > cpl) {                                                         // 0.0
/*184 */         raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);             // 0.0
/*186 */     }                                                                        // 0.0
/*188 */     if (!(e2 & DESC_P_MASK)) {                                               // 0.0
/*190 */         raise_exception_err(env, EXCP0B_NOSEG, selector & 0xfffc);           // 0.0
/*192 */     }                                                                        // 0.0
/*194 */     if (!(e2 & DESC_C_MASK) && dpl < cpl) {                                  // 0.0
/*196 */         /* to inner privilege */                                             // 0.0
/*198 */         get_ss_esp_from_tss(env, &ss, &esp, dpl, 0);                         // 0.0
/*200 */         if ((ss & 0xfffc) == 0) {                                            // 0.0
/*202 */             raise_exception_err(env, EXCP0A_TSS, ss & 0xfffc);               // 0.0
/*204 */         }                                                                    // 0.0
/*206 */         if ((ss & 3) != dpl) {                                               // 0.0
/*208 */             raise_exception_err(env, EXCP0A_TSS, ss & 0xfffc);               // 0.0
/*210 */         }                                                                    // 0.0
/*212 */         if (load_segment(env, &ss_e1, &ss_e2, ss) != 0) {                    // 0.0
/*214 */             raise_exception_err(env, EXCP0A_TSS, ss & 0xfffc);               // 0.0
/*216 */         }                                                                    // 0.0
/*218 */         ss_dpl = (ss_e2 >> DESC_DPL_SHIFT) & 3;                              // 0.0
/*220 */         if (ss_dpl != dpl) {                                                 // 0.0
/*222 */             raise_exception_err(env, EXCP0A_TSS, ss & 0xfffc);               // 0.0
/*224 */         }                                                                    // 0.0
/*226 */         if (!(ss_e2 & DESC_S_MASK) ||                                        // 0.0
/*228 */             (ss_e2 & DESC_CS_MASK) ||                                        // 0.0
/*230 */             !(ss_e2 & DESC_W_MASK)) {                                        // 0.0
/*232 */             raise_exception_err(env, EXCP0A_TSS, ss & 0xfffc);               // 0.0
/*234 */         }                                                                    // 0.0
/*236 */         if (!(ss_e2 & DESC_P_MASK)) {                                        // 0.0
/*238 */             raise_exception_err(env, EXCP0A_TSS, ss & 0xfffc);               // 0.0
/*240 */         }                                                                    // 0.0
/*242 */         new_stack = 1;                                                       // 0.0
/*244 */         sp_mask = get_sp_mask(ss_e2);                                        // 0.0
/*246 */         ssp = get_seg_base(ss_e1, ss_e2);                                    // 0.0
/*248 */     } else if ((e2 & DESC_C_MASK) || dpl == cpl) {                           // 0.0
/*250 */         /* to same privilege */                                              // 0.0
/*252 */         if (vm86) {                                                          // 0.0
/*254 */             raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);         // 0.0
/*256 */         }                                                                    // 0.0
/*258 */         new_stack = 0;                                                       // 0.0
/*260 */         sp_mask = get_sp_mask(env->segs[R_SS].flags);                        // 0.0
/*262 */         ssp = env->segs[R_SS].base;                                          // 0.0
/*264 */         esp = env->regs[R_ESP];                                              // 0.0
/*266 */         dpl = cpl;                                                           // 0.0
/*268 */     } else {                                                                 // 0.0
/*270 */         raise_exception_err(env, EXCP0D_GPF, selector & 0xfffc);             // 0.0
/*272 */         new_stack = 0; /* avoid warning */                                   // 0.0
/*274 */         sp_mask = 0; /* avoid warning */                                     // 0.0
/*276 */         ssp = 0; /* avoid warning */                                         // 0.0
/*278 */         esp = 0; /* avoid warning */                                         // 0.0
/*280 */     }                                                                        // 0.0
/*284 */     shift = type >> 3;                                                       // 0.0
/*288 */ #if 0                                                                        // 0.0
/*290 */     /* XXX: check that enough room is available */                           // 0.0
/*292 */     push_size = 6 + (new_stack << 2) + (has_error_code << 1);                // 0.0
/*294 */     if (vm86) {                                                              // 0.0
/*296 */         push_size += 8;                                                      // 0.0
/*298 */     }                                                                        // 0.0
/*300 */     push_size <<= shift;                                                     // 0.0
/*302 */ #endif                                                                       // 0.0
/*304 */     if (shift == 1) {                                                        // 0.0
/*306 */         if (new_stack) {                                                     // 0.0
/*308 */             if (vm86) {                                                      // 0.0
/*310 */                 PUSHL(ssp, esp, sp_mask, env->segs[R_GS].selector);          // 0.0
/*312 */                 PUSHL(ssp, esp, sp_mask, env->segs[R_FS].selector);          // 0.0
/*314 */                 PUSHL(ssp, esp, sp_mask, env->segs[R_DS].selector);          // 0.0
/*316 */                 PUSHL(ssp, esp, sp_mask, env->segs[R_ES].selector);          // 0.0
/*318 */             }                                                                // 0.0
/*320 */             PUSHL(ssp, esp, sp_mask, env->segs[R_SS].selector);              // 0.0
/*322 */             PUSHL(ssp, esp, sp_mask, env->regs[R_ESP]);                      // 0.0
/*324 */         }                                                                    // 0.0
/*326 */         PUSHL(ssp, esp, sp_mask, cpu_compute_eflags(env));                   // 0.0
/*328 */         PUSHL(ssp, esp, sp_mask, env->segs[R_CS].selector);                  // 0.0
/*330 */         PUSHL(ssp, esp, sp_mask, old_eip);                                   // 0.0
/*332 */         if (has_error_code) {                                                // 0.0
/*334 */             PUSHL(ssp, esp, sp_mask, error_code);                            // 0.0
/*336 */         }                                                                    // 0.0
/*338 */     } else {                                                                 // 0.0
/*340 */         if (new_stack) {                                                     // 0.0
/*342 */             if (vm86) {                                                      // 0.0
/*344 */                 PUSHW(ssp, esp, sp_mask, env->segs[R_GS].selector);          // 0.0
/*346 */                 PUSHW(ssp, esp, sp_mask, env->segs[R_FS].selector);          // 0.0
/*348 */                 PUSHW(ssp, esp, sp_mask, env->segs[R_DS].selector);          // 0.0
/*350 */                 PUSHW(ssp, esp, sp_mask, env->segs[R_ES].selector);          // 0.0
/*352 */             }                                                                // 0.0
/*354 */             PUSHW(ssp, esp, sp_mask, env->segs[R_SS].selector);              // 0.0
/*356 */             PUSHW(ssp, esp, sp_mask, env->regs[R_ESP]);                      // 0.0
/*358 */         }                                                                    // 0.0
/*360 */         PUSHW(ssp, esp, sp_mask, cpu_compute_eflags(env));                   // 0.0
/*362 */         PUSHW(ssp, esp, sp_mask, env->segs[R_CS].selector);                  // 0.0
/*364 */         PUSHW(ssp, esp, sp_mask, old_eip);                                   // 0.0
/*366 */         if (has_error_code) {                                                // 0.0
/*368 */             PUSHW(ssp, esp, sp_mask, error_code);                            // 0.0
/*370 */         }                                                                    // 0.0
/*372 */     }                                                                        // 0.0
/*376 */     /* interrupt gate clear IF mask */                                       // 0.0
/*378 */     if ((type & 1) == 0) {                                                   // 0.0
/*380 */         env->eflags &= ~IF_MASK;                                             // 0.0
/*382 */     }                                                                        // 0.0
/*384 */     env->eflags &= ~(TF_MASK | VM_MASK | RF_MASK | NT_MASK);                 // 0.0
/*388 */     if (new_stack) {                                                         // 0.0
/*390 */         if (vm86) {                                                          // 0.0
/*392 */             cpu_x86_load_seg_cache(env, R_ES, 0, 0, 0, 0);                   // 0.0
/*394 */             cpu_x86_load_seg_cache(env, R_DS, 0, 0, 0, 0);                   // 0.0
/*396 */             cpu_x86_load_seg_cache(env, R_FS, 0, 0, 0, 0);                   // 0.0
/*398 */             cpu_x86_load_seg_cache(env, R_GS, 0, 0, 0, 0);                   // 0.0
/*400 */         }                                                                    // 0.0
/*402 */         ss = (ss & ~3) | dpl;                                                // 0.0
/*404 */         cpu_x86_load_seg_cache(env, R_SS, ss,                                // 0.0
/*406 */                                ssp, get_seg_limit(ss_e1, ss_e2), ss_e2);     // 0.0
/*408 */     }                                                                        // 0.0
/*410 */     SET_ESP(esp, sp_mask);                                                   // 0.0
/*414 */     selector = (selector & ~3) | dpl;                                        // 0.0
/*416 */     cpu_x86_load_seg_cache(env, R_CS, selector,                              // 0.0
/*418 */                    get_seg_base(e1, e2),                                     // 0.0
/*420 */                    get_seg_limit(e1, e2),                                    // 0.0
/*422 */                    e2);                                                      // 0.0
/*424 */     env->eip = offset;                                                       // 0.0
/*426 */ }                                                                            // 0.0
