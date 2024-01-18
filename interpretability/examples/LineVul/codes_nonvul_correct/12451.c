// commit message qemu@fb9fb69231 (target=0, prob=0.26517448, correct=True): cris: Prepare for CRISv10.
/*0   */ int cpu_exec(CPUState *env1)                                                                                     // (18) 0.02149
/*2   */ {                                                                                                                // (32) 0.001953
/*4   */ #define DECLARE_HOST_REGS 1                                                                                      // (11) 0.02344
/*6   */ #include "hostregs_helper.h"                                                                                     // (13) 0.02344
/*8   */     int ret, interrupt_request;                                                                                  // (25) 0.01955
/*10  */     TranslationBlock *tb;                                                                                        // (30) 0.01758
/*12  */     uint8_t *tc_ptr;                                                                                             // (10) 0.02344
/*14  */     unsigned long next_tb;                                                                                       // (26) 0.01953
/*18  */     if (cpu_halted(env1) == EXCP_HALTED)                                                                         // (3) 0.04102
/*20  */         return EXCP_HALTED;                                                                                      // (7) 0.0293
/*24  */     cpu_single_env = env1;                                                                                       // (12) 0.02344
/*28  */     /* first we save global registers */                                                                         // (28) 0.01953
/*30  */ #define SAVE_HOST_REGS 1                                                                                         // (19) 0.02148
/*32  */ #include "hostregs_helper.h"                                                                                     // (15) 0.02344
/*34  */     env = env1;                                                                                                  // (31) 0.01562
/*38  */ #if defined(TARGET_I386)                                                                                         // (27) 0.01953
/*40  */     /* put eflags in CPU temporary format */                                                                     // (14) 0.02344
/*42  */     CC_SRC = env->eflags & (CC_O | CC_S | CC_Z | CC_A | CC_P | CC_C);                                            // (1) 0.07617
/*44  */     DF = 1 - (2 * ((env->eflags >> 10) & 1));                                                                    // (2) 0.04297
/*46  */     CC_OP = CC_OP_EFLAGS;                                                                                        // (8) 0.0293
/*48  */     env->eflags &= ~(DF_MASK | CC_O | CC_S | CC_Z | CC_A | CC_P | CC_C);                                         // (0) 0.08007
/*50  */ #elif defined(TARGET_SPARC)                                                                                      // (21) 0.02148
/*52  */ #elif defined(TARGET_M68K)                                                                                       // (17) 0.02344
/*54  */     env->cc_op = CC_OP_FLAGS;                                                                                    // (6) 0.03125
/*56  */     env->cc_dest = env->sr & 0xf;                                                                                // (5) 0.03125
/*58  */     env->cc_x = (env->sr >> 4) & 1;                                                                              // (4) 0.03711
/*60  */ #elif defined(TARGET_ALPHA)                                                                                      // (16) 0.02344
/*62  */ #elif defined(TARGET_ARM)                                                                                        // (29) 0.01953
/*64  */ #elif defined(TARGET_PPC)                                                                                        // (24) 0.02148
/*66  */ #elif defined(TARGET_MICROBLAZE)                                                                                 // (9) 0.02734
/*68  */ #elif defined(TARGET_MIPS)                                                                                       // (20) 0.02148
/*70  */ #elif defined(TARGET_SH4)                                                                                        // (23) 0.02148
/*72  */ #elif defined(TARGET_CRIS)                                                                                       // (22) 0.02148
/*74  */ #elif defined(TARGET_S390X)                                                                                      // 0.0
/*76  */     /* XXXXX */                                                                                                  // 0.0
/*78  */ #else                                                                                                            // 0.0
/*80  */ #error unsupported target CPU                                                                                    // 0.0
/*82  */ #endif                                                                                                           // 0.0
/*84  */     env->exception_index = -1;                                                                                   // 0.0
/*88  */     /* prepare setjmp context for exception handling */                                                          // 0.0
/*90  */     for(;;) {                                                                                                    // 0.0
/*92  */         if (setjmp(env->jmp_env) == 0) {                                                                         // 0.0
/*94  */ #if defined(__sparc__) && !defined(CONFIG_SOLARIS)                                                               // 0.0
/*96  */ #undef env                                                                                                       // 0.0
/*98  */                     env = cpu_single_env;                                                                        // 0.0
/*100 */ #define env cpu_single_env                                                                                       // 0.0
/*102 */ #endif                                                                                                           // 0.0
/*104 */             /* if an exception is pending, we execute it here */                                                 // 0.0
/*106 */             if (env->exception_index >= 0) {                                                                     // 0.0
/*108 */                 if (env->exception_index >= EXCP_INTERRUPT) {                                                    // 0.0
/*110 */                     /* exit request from the cpu execution loop */                                               // 0.0
/*112 */                     ret = env->exception_index;                                                                  // 0.0
/*114 */                     if (ret == EXCP_DEBUG)                                                                       // 0.0
/*116 */                         cpu_handle_debug_exception(env);                                                         // 0.0
/*118 */                     break;                                                                                       // 0.0
/*120 */                 } else {                                                                                         // 0.0
/*122 */ #if defined(CONFIG_USER_ONLY)                                                                                    // 0.0
/*124 */                     /* if user mode only, we simulate a fake exception                                           // 0.0
/*126 */                        which will be handled outside the cpu execution                                           // 0.0
/*128 */                        loop */                                                                                   // 0.0
/*130 */ #if defined(TARGET_I386)                                                                                         // 0.0
/*132 */                     do_interrupt_user(env->exception_index,                                                      // 0.0
/*134 */                                       env->exception_is_int,                                                     // 0.0
/*136 */                                       env->error_code,                                                           // 0.0
/*138 */                                       env->exception_next_eip);                                                  // 0.0
/*140 */                     /* successfully delivered */                                                                 // 0.0
/*142 */                     env->old_exception = -1;                                                                     // 0.0
/*144 */ #endif                                                                                                           // 0.0
/*146 */                     ret = env->exception_index;                                                                  // 0.0
/*148 */                     break;                                                                                       // 0.0
/*150 */ #else                                                                                                            // 0.0
/*152 */ #if defined(TARGET_I386)                                                                                         // 0.0
/*154 */                     /* simulate a real cpu exception. On i386, it can                                            // 0.0
/*156 */                        trigger new exceptions, but we do not handle                                              // 0.0
/*158 */                        double or triple faults yet. */                                                           // 0.0
/*160 */                     do_interrupt(env->exception_index,                                                           // 0.0
/*162 */                                  env->exception_is_int,                                                          // 0.0
/*164 */                                  env->error_code,                                                                // 0.0
/*166 */                                  env->exception_next_eip, 0);                                                    // 0.0
/*168 */                     /* successfully delivered */                                                                 // 0.0
/*170 */                     env->old_exception = -1;                                                                     // 0.0
/*172 */ #elif defined(TARGET_PPC)                                                                                        // 0.0
/*174 */                     do_interrupt(env);                                                                           // 0.0
/*176 */ #elif defined(TARGET_MICROBLAZE)                                                                                 // 0.0
/*178 */                     do_interrupt(env);                                                                           // 0.0
/*180 */ #elif defined(TARGET_MIPS)                                                                                       // 0.0
/*182 */                     do_interrupt(env);                                                                           // 0.0
/*184 */ #elif defined(TARGET_SPARC)                                                                                      // 0.0
/*186 */                     do_interrupt(env);                                                                           // 0.0
/*188 */ #elif defined(TARGET_ARM)                                                                                        // 0.0
/*190 */                     do_interrupt(env);                                                                           // 0.0
/*192 */ #elif defined(TARGET_SH4)                                                                                        // 0.0
/*194 */ 		    do_interrupt(env);                                                                                         // 0.0
/*196 */ #elif defined(TARGET_ALPHA)                                                                                      // 0.0
/*198 */                     do_interrupt(env);                                                                           // 0.0
/*200 */ #elif defined(TARGET_CRIS)                                                                                       // 0.0
/*202 */                     do_interrupt(env);                                                                           // 0.0
/*204 */ #elif defined(TARGET_M68K)                                                                                       // 0.0
/*206 */                     do_interrupt(0);                                                                             // 0.0
/*208 */ #endif                                                                                                           // 0.0
/*210 */                     env->exception_index = -1;                                                                   // 0.0
/*212 */ #endif                                                                                                           // 0.0
/*214 */                 }                                                                                                // 0.0
/*216 */             }                                                                                                    // 0.0
/*220 */             if (kvm_enabled()) {                                                                                 // 0.0
/*222 */                 kvm_cpu_exec(env);                                                                               // 0.0
/*224 */                 longjmp(env->jmp_env, 1);                                                                        // 0.0
/*226 */             }                                                                                                    // 0.0
/*230 */             next_tb = 0; /* force lookup of first TB */                                                          // 0.0
/*232 */             for(;;) {                                                                                            // 0.0
/*234 */                 interrupt_request = env->interrupt_request;                                                      // 0.0
/*236 */                 if (unlikely(interrupt_request)) {                                                               // 0.0
/*238 */                     if (unlikely(env->singlestep_enabled & SSTEP_NOIRQ)) {                                       // 0.0
/*240 */                         /* Mask out external interrupts for this step. */                                        // 0.0
/*242 */                         interrupt_request &= ~(CPU_INTERRUPT_HARD |                                              // 0.0
/*244 */                                                CPU_INTERRUPT_FIQ |                                               // 0.0
/*246 */                                                CPU_INTERRUPT_SMI |                                               // 0.0
/*248 */                                                CPU_INTERRUPT_NMI);                                               // 0.0
/*250 */                     }                                                                                            // 0.0
/*252 */                     if (interrupt_request & CPU_INTERRUPT_DEBUG) {                                               // 0.0
/*254 */                         env->interrupt_request &= ~CPU_INTERRUPT_DEBUG;                                          // 0.0
/*256 */                         env->exception_index = EXCP_DEBUG;                                                       // 0.0
/*258 */                         cpu_loop_exit();                                                                         // 0.0
/*260 */                     }                                                                                            // 0.0
/*262 */ #if defined(TARGET_ARM) || defined(TARGET_SPARC) || defined(TARGET_MIPS) || \                                    // 0.0
/*264 */     defined(TARGET_PPC) || defined(TARGET_ALPHA) || defined(TARGET_CRIS) || \                                    // 0.0
/*266 */     defined(TARGET_MICROBLAZE)                                                                                   // 0.0
/*268 */                     if (interrupt_request & CPU_INTERRUPT_HALT) {                                                // 0.0
/*270 */                         env->interrupt_request &= ~CPU_INTERRUPT_HALT;                                           // 0.0
/*272 */                         env->halted = 1;                                                                         // 0.0
/*274 */                         env->exception_index = EXCP_HLT;                                                         // 0.0
/*276 */                         cpu_loop_exit();                                                                         // 0.0
/*278 */                     }                                                                                            // 0.0
/*280 */ #endif                                                                                                           // 0.0
/*282 */ #if defined(TARGET_I386)                                                                                         // 0.0
/*284 */                     if (interrupt_request & CPU_INTERRUPT_INIT) {                                                // 0.0
/*286 */                             svm_check_intercept(SVM_EXIT_INIT);                                                  // 0.0
/*288 */                             do_cpu_init(env);                                                                    // 0.0
/*290 */                             env->exception_index = EXCP_HALTED;                                                  // 0.0
/*292 */                             cpu_loop_exit();                                                                     // 0.0
/*294 */                     } else if (interrupt_request & CPU_INTERRUPT_SIPI) {                                         // 0.0
/*296 */                             do_cpu_sipi(env);                                                                    // 0.0
/*298 */                     } else if (env->hflags2 & HF2_GIF_MASK) {                                                    // 0.0
/*300 */                         if ((interrupt_request & CPU_INTERRUPT_SMI) &&                                           // 0.0
/*302 */                             !(env->hflags & HF_SMM_MASK)) {                                                      // 0.0
/*304 */                             svm_check_intercept(SVM_EXIT_SMI);                                                   // 0.0
/*306 */                             env->interrupt_request &= ~CPU_INTERRUPT_SMI;                                        // 0.0
/*308 */                             do_smm_enter();                                                                      // 0.0
/*310 */                             next_tb = 0;                                                                         // 0.0
/*312 */                         } else if ((interrupt_request & CPU_INTERRUPT_NMI) &&                                    // 0.0
/*314 */                                    !(env->hflags2 & HF2_NMI_MASK)) {                                             // 0.0
/*316 */                             env->interrupt_request &= ~CPU_INTERRUPT_NMI;                                        // 0.0
/*318 */                             env->hflags2 |= HF2_NMI_MASK;                                                        // 0.0
/*320 */                             do_interrupt(EXCP02_NMI, 0, 0, 0, 1);                                                // 0.0
/*322 */                             next_tb = 0;                                                                         // 0.0
/*324 */ 			} else if (interrupt_request & CPU_INTERRUPT_MCE) {                                                           // 0.0
/*326 */                             env->interrupt_request &= ~CPU_INTERRUPT_MCE;                                        // 0.0
/*328 */                             do_interrupt(EXCP12_MCHK, 0, 0, 0, 0);                                               // 0.0
/*330 */                             next_tb = 0;                                                                         // 0.0
/*332 */                         } else if ((interrupt_request & CPU_INTERRUPT_HARD) &&                                   // 0.0
/*334 */                                    (((env->hflags2 & HF2_VINTR_MASK) &&                                          // 0.0
/*336 */                                      (env->hflags2 & HF2_HIF_MASK)) ||                                           // 0.0
/*338 */                                     (!(env->hflags2 & HF2_VINTR_MASK) &&                                         // 0.0
/*340 */                                      (env->eflags & IF_MASK &&                                                   // 0.0
/*342 */                                       !(env->hflags & HF_INHIBIT_IRQ_MASK))))) {                                 // 0.0
/*344 */                             int intno;                                                                           // 0.0
/*346 */                             svm_check_intercept(SVM_EXIT_INTR);                                                  // 0.0
/*348 */                             env->interrupt_request &= ~(CPU_INTERRUPT_HARD | CPU_INTERRUPT_VIRQ);                // 0.0
/*350 */                             intno = cpu_get_pic_interrupt(env);                                                  // 0.0
/*352 */                             qemu_log_mask(CPU_LOG_TB_IN_ASM, "Servicing hardware INT=0x%02x\n", intno);          // 0.0
/*354 */ #if defined(__sparc__) && !defined(CONFIG_SOLARIS)                                                               // 0.0
/*356 */ #undef env                                                                                                       // 0.0
/*358 */                     env = cpu_single_env;                                                                        // 0.0
/*360 */ #define env cpu_single_env                                                                                       // 0.0
/*362 */ #endif                                                                                                           // 0.0
/*364 */                             do_interrupt(intno, 0, 0, 0, 1);                                                     // 0.0
/*366 */                             /* ensure that no TB jump will be modified as                                        // 0.0
/*368 */                                the program flow was changed */                                                   // 0.0
/*370 */                             next_tb = 0;                                                                         // 0.0
/*372 */ #if !defined(CONFIG_USER_ONLY)                                                                                   // 0.0
/*374 */                         } else if ((interrupt_request & CPU_INTERRUPT_VIRQ) &&                                   // 0.0
/*376 */                                    (env->eflags & IF_MASK) &&                                                    // 0.0
/*378 */                                    !(env->hflags & HF_INHIBIT_IRQ_MASK)) {                                       // 0.0
/*380 */                             int intno;                                                                           // 0.0
/*382 */                             /* FIXME: this should respect TPR */                                                 // 0.0
/*384 */                             svm_check_intercept(SVM_EXIT_VINTR);                                                 // 0.0
/*386 */                             intno = ldl_phys(env->vm_vmcb + offsetof(struct vmcb, control.int_vector));          // 0.0
/*388 */                             qemu_log_mask(CPU_LOG_TB_IN_ASM, "Servicing virtual hardware INT=0x%02x\n", intno);  // 0.0
/*390 */                             do_interrupt(intno, 0, 0, 0, 1);                                                     // 0.0
/*392 */                             env->interrupt_request &= ~CPU_INTERRUPT_VIRQ;                                       // 0.0
/*394 */                             next_tb = 0;                                                                         // 0.0
/*396 */ #endif                                                                                                           // 0.0
/*398 */                         }                                                                                        // 0.0
/*400 */                     }                                                                                            // 0.0
/*402 */ #elif defined(TARGET_PPC)                                                                                        // 0.0
/*404 */ #if 0                                                                                                            // 0.0
/*406 */                     if ((interrupt_request & CPU_INTERRUPT_RESET)) {                                             // 0.0
/*408 */                         cpu_reset(env);                                                                          // 0.0
/*410 */                     }                                                                                            // 0.0
/*412 */ #endif                                                                                                           // 0.0
/*414 */                     if (interrupt_request & CPU_INTERRUPT_HARD) {                                                // 0.0
/*416 */                         ppc_hw_interrupt(env);                                                                   // 0.0
/*418 */                         if (env->pending_interrupts == 0)                                                        // 0.0
/*420 */                             env->interrupt_request &= ~CPU_INTERRUPT_HARD;                                       // 0.0
/*422 */                         next_tb = 0;                                                                             // 0.0
/*424 */                     }                                                                                            // 0.0
/*426 */ #elif defined(TARGET_MICROBLAZE)                                                                                 // 0.0
/*428 */                     if ((interrupt_request & CPU_INTERRUPT_HARD)                                                 // 0.0
/*430 */                         && (env->sregs[SR_MSR] & MSR_IE)                                                         // 0.0
/*432 */                         && !(env->sregs[SR_MSR] & (MSR_EIP | MSR_BIP))                                           // 0.0
/*434 */                         && !(env->iflags & (D_FLAG | IMM_FLAG))) {                                               // 0.0
/*436 */                         env->exception_index = EXCP_IRQ;                                                         // 0.0
/*438 */                         do_interrupt(env);                                                                       // 0.0
/*440 */                         next_tb = 0;                                                                             // 0.0
/*442 */                     }                                                                                            // 0.0
/*444 */ #elif defined(TARGET_MIPS)                                                                                       // 0.0
/*446 */                     if ((interrupt_request & CPU_INTERRUPT_HARD) &&                                              // 0.0
/*448 */                         (env->CP0_Status & env->CP0_Cause & CP0Ca_IP_mask) &&                                    // 0.0
/*450 */                         (env->CP0_Status & (1 << CP0St_IE)) &&                                                   // 0.0
/*452 */                         !(env->CP0_Status & (1 << CP0St_EXL)) &&                                                 // 0.0
/*454 */                         !(env->CP0_Status & (1 << CP0St_ERL)) &&                                                 // 0.0
/*456 */                         !(env->hflags & MIPS_HFLAG_DM)) {                                                        // 0.0
/*458 */                         /* Raise it */                                                                           // 0.0
/*460 */                         env->exception_index = EXCP_EXT_INTERRUPT;                                               // 0.0
/*462 */                         env->error_code = 0;                                                                     // 0.0
/*464 */                         do_interrupt(env);                                                                       // 0.0
/*466 */                         next_tb = 0;                                                                             // 0.0
/*468 */                     }                                                                                            // 0.0
/*470 */ #elif defined(TARGET_SPARC)                                                                                      // 0.0
/*472 */                     if (interrupt_request & CPU_INTERRUPT_HARD) {                                                // 0.0
/*474 */                         if (cpu_interrupts_enabled(env) &&                                                       // 0.0
/*476 */                             env->interrupt_index > 0) {                                                          // 0.0
/*478 */                             int pil = env->interrupt_index & 0xf;                                                // 0.0
/*480 */                             int type = env->interrupt_index & 0xf0;                                              // 0.0
/*484 */                             if (((type == TT_EXTINT) &&                                                          // 0.0
/*486 */                                   cpu_pil_allowed(env, pil)) ||                                                  // 0.0
/*488 */                                   type != TT_EXTINT) {                                                           // 0.0
/*490 */                                 env->exception_index = env->interrupt_index;                                     // 0.0
/*492 */                                 do_interrupt(env);                                                               // 0.0
/*494 */                                 next_tb = 0;                                                                     // 0.0
/*496 */                             }                                                                                    // 0.0
/*498 */                         }                                                                                        // 0.0
/*500 */ 		    } else if (interrupt_request & CPU_INTERRUPT_TIMER) {                                                      // 0.0
/*502 */ 			//do_interrupt(0, 0, 0, 0, 0);                                                                                // 0.0
/*504 */ 			env->interrupt_request &= ~CPU_INTERRUPT_TIMER;                                                               // 0.0
/*506 */ 		    }                                                                                                          // 0.0
/*508 */ #elif defined(TARGET_ARM)                                                                                        // 0.0
/*510 */                     if (interrupt_request & CPU_INTERRUPT_FIQ                                                    // 0.0
/*512 */                         && !(env->uncached_cpsr & CPSR_F)) {                                                     // 0.0
/*514 */                         env->exception_index = EXCP_FIQ;                                                         // 0.0
/*516 */                         do_interrupt(env);                                                                       // 0.0
/*518 */                         next_tb = 0;                                                                             // 0.0
/*520 */                     }                                                                                            // 0.0
/*522 */                     /* ARMv7-M interrupt return works by loading a magic value                                   // 0.0
/*524 */                        into the PC.  On real hardware the load causes the                                        // 0.0
/*526 */                        return to occur.  The qemu implementation performs the                                    // 0.0
/*528 */                        jump normally, then does the exception return when the                                    // 0.0
/*530 */                        CPU tries to execute code at the magic address.                                           // 0.0
/*532 */                        This will cause the magic PC value to be pushed to                                        // 0.0
/*534 */                        the stack if an interrupt occured at the wrong time.                                      // 0.0
/*536 */                        We avoid this by disabling interrupts when                                                // 0.0
/*538 */                        pc contains a magic address.  */                                                          // 0.0
/*540 */                     if (interrupt_request & CPU_INTERRUPT_HARD                                                   // 0.0
/*542 */                         && ((IS_M(env) && env->regs[15] < 0xfffffff0)                                            // 0.0
/*544 */                             || !(env->uncached_cpsr & CPSR_I))) {                                                // 0.0
/*546 */                         env->exception_index = EXCP_IRQ;                                                         // 0.0
/*548 */                         do_interrupt(env);                                                                       // 0.0
/*550 */                         next_tb = 0;                                                                             // 0.0
/*552 */                     }                                                                                            // 0.0
/*554 */ #elif defined(TARGET_SH4)                                                                                        // 0.0
/*556 */                     if (interrupt_request & CPU_INTERRUPT_HARD) {                                                // 0.0
/*558 */                         do_interrupt(env);                                                                       // 0.0
/*560 */                         next_tb = 0;                                                                             // 0.0
/*562 */                     }                                                                                            // 0.0
/*564 */ #elif defined(TARGET_ALPHA)                                                                                      // 0.0
/*566 */                     if (interrupt_request & CPU_INTERRUPT_HARD) {                                                // 0.0
/*568 */                         do_interrupt(env);                                                                       // 0.0
/*570 */                         next_tb = 0;                                                                             // 0.0
/*572 */                     }                                                                                            // 0.0
/*574 */ #elif defined(TARGET_CRIS)                                                                                       // 0.0
/*576 */                     if (interrupt_request & CPU_INTERRUPT_HARD                                                   // 0.0
/*578 */                         && (env->pregs[PR_CCS] & I_FLAG)) {                                                      // 0.0
/*580 */                         env->exception_index = EXCP_IRQ;                                                         // 0.0
/*582 */                         do_interrupt(env);                                                                       // 0.0
/*584 */                         next_tb = 0;                                                                             // 0.0
/*586 */                     }                                                                                            // 0.0
/*588 */                     if (interrupt_request & CPU_INTERRUPT_NMI                                                    // 0.0
/*590 */                         && (env->pregs[PR_CCS] & M_FLAG)) {                                                      // 0.0
/*592 */                         env->exception_index = EXCP_NMI;                                                         // 0.0
/*594 */                         do_interrupt(env);                                                                       // 0.0
/*596 */                         next_tb = 0;                                                                             // 0.0
/*598 */                     }                                                                                            // 0.0
/*600 */ #elif defined(TARGET_M68K)                                                                                       // 0.0
/*602 */                     if (interrupt_request & CPU_INTERRUPT_HARD                                                   // 0.0
/*604 */                         && ((env->sr & SR_I) >> SR_I_SHIFT)                                                      // 0.0
/*606 */                             < env->pending_level) {                                                              // 0.0
/*608 */                         /* Real hardware gets the interrupt vector via an                                        // 0.0
/*610 */                            IACK cycle at this point.  Current emulated                                           // 0.0
/*612 */                            hardware doesn't rely on this, so we                                                  // 0.0
/*614 */                            provide/save the vector when the interrupt is                                         // 0.0
/*616 */                            first signalled.  */                                                                  // 0.0
/*618 */                         env->exception_index = env->pending_vector;                                              // 0.0
/*620 */                         do_interrupt(1);                                                                         // 0.0
/*622 */                         next_tb = 0;                                                                             // 0.0
/*624 */                     }                                                                                            // 0.0
/*626 */ #endif                                                                                                           // 0.0
/*628 */                    /* Don't use the cached interupt_request value,                                               // 0.0
/*630 */                       do_interrupt may have updated the EXITTB flag. */                                          // 0.0
/*632 */                     if (env->interrupt_request & CPU_INTERRUPT_EXITTB) {                                         // 0.0
/*634 */                         env->interrupt_request &= ~CPU_INTERRUPT_EXITTB;                                         // 0.0
/*636 */                         /* ensure that no TB jump will be modified as                                            // 0.0
/*638 */                            the program flow was changed */                                                       // 0.0
/*640 */                         next_tb = 0;                                                                             // 0.0
/*642 */                     }                                                                                            // 0.0
/*644 */                 }                                                                                                // 0.0
/*646 */                 if (unlikely(env->exit_request)) {                                                               // 0.0
/*648 */                     env->exit_request = 0;                                                                       // 0.0
/*650 */                     env->exception_index = EXCP_INTERRUPT;                                                       // 0.0
/*652 */                     cpu_loop_exit();                                                                             // 0.0
/*654 */                 }                                                                                                // 0.0
/*656 */ #ifdef CONFIG_DEBUG_EXEC                                                                                         // 0.0
/*658 */                 if (qemu_loglevel_mask(CPU_LOG_TB_CPU)) {                                                        // 0.0
/*660 */                     /* restore flags in standard format */                                                       // 0.0
/*662 */ #if defined(TARGET_I386)                                                                                         // 0.0
/*664 */                     env->eflags = env->eflags | helper_cc_compute_all(CC_OP) | (DF & DF_MASK);                   // 0.0
/*666 */                     log_cpu_state(env, X86_DUMP_CCOP);                                                           // 0.0
/*668 */                     env->eflags &= ~(DF_MASK | CC_O | CC_S | CC_Z | CC_A | CC_P | CC_C);                         // 0.0
/*670 */ #elif defined(TARGET_ARM)                                                                                        // 0.0
/*672 */                     log_cpu_state(env, 0);                                                                       // 0.0
/*674 */ #elif defined(TARGET_SPARC)                                                                                      // 0.0
/*676 */                     log_cpu_state(env, 0);                                                                       // 0.0
/*678 */ #elif defined(TARGET_PPC)                                                                                        // 0.0
/*680 */                     log_cpu_state(env, 0);                                                                       // 0.0
/*682 */ #elif defined(TARGET_M68K)                                                                                       // 0.0
/*684 */                     cpu_m68k_flush_flags(env, env->cc_op);                                                       // 0.0
/*686 */                     env->cc_op = CC_OP_FLAGS;                                                                    // 0.0
/*688 */                     env->sr = (env->sr & 0xffe0)                                                                 // 0.0
/*690 */                               | env->cc_dest | (env->cc_x << 4);                                                 // 0.0
/*692 */                     log_cpu_state(env, 0);                                                                       // 0.0
/*694 */ #elif defined(TARGET_MICROBLAZE)                                                                                 // 0.0
/*696 */                     log_cpu_state(env, 0);                                                                       // 0.0
/*698 */ #elif defined(TARGET_MIPS)                                                                                       // 0.0
/*700 */                     log_cpu_state(env, 0);                                                                       // 0.0
/*702 */ #elif defined(TARGET_SH4)                                                                                        // 0.0
/*704 */ 		    log_cpu_state(env, 0);                                                                                     // 0.0
/*706 */ #elif defined(TARGET_ALPHA)                                                                                      // 0.0
/*708 */                     log_cpu_state(env, 0);                                                                       // 0.0
/*710 */ #elif defined(TARGET_CRIS)                                                                                       // 0.0
/*712 */                     log_cpu_state(env, 0);                                                                       // 0.0
/*714 */ #else                                                                                                            // 0.0
/*716 */ #error unsupported target CPU                                                                                    // 0.0
/*718 */ #endif                                                                                                           // 0.0
/*720 */                 }                                                                                                // 0.0
/*722 */ #endif                                                                                                           // 0.0
/*724 */                 spin_lock(&tb_lock);                                                                             // 0.0
/*726 */                 tb = tb_find_fast();                                                                             // 0.0
/*728 */                 /* Note: we do it here to avoid a gcc bug on Mac OS X when                                       // 0.0
/*730 */                    doing it in tb_find_slow */                                                                   // 0.0
/*732 */                 if (tb_invalidated_flag) {                                                                       // 0.0
/*734 */                     /* as some TB could have been invalidated because                                            // 0.0
/*736 */                        of memory exceptions while generating the code, we                                        // 0.0
/*738 */                        must recompute the hash index here */                                                     // 0.0
/*740 */                     next_tb = 0;                                                                                 // 0.0
/*742 */                     tb_invalidated_flag = 0;                                                                     // 0.0
/*744 */                 }                                                                                                // 0.0
/*746 */ #ifdef CONFIG_DEBUG_EXEC                                                                                         // 0.0
/*748 */                 qemu_log_mask(CPU_LOG_EXEC, "Trace 0x%08lx [" TARGET_FMT_lx "] %s\n",                            // 0.0
/*750 */                              (long)tb->tc_ptr, tb->pc,                                                           // 0.0
/*752 */                              lookup_symbol(tb->pc));                                                             // 0.0
/*754 */ #endif                                                                                                           // 0.0
/*756 */                 /* see if we can patch the calling TB. When the TB                                               // 0.0
/*758 */                    spans two pages, we cannot safely do a direct                                                 // 0.0
/*760 */                    jump. */                                                                                      // 0.0
/*762 */                 if (next_tb != 0 && tb->page_addr[1] == -1) {                                                    // 0.0
/*764 */                     tb_add_jump((TranslationBlock *)(next_tb & ~3), next_tb & 3, tb);                            // 0.0
/*766 */                 }                                                                                                // 0.0
/*768 */                 spin_unlock(&tb_lock);                                                                           // 0.0
/*772 */                 /* cpu_interrupt might be called while translating the                                           // 0.0
/*774 */                    TB, but before it is linked into a potentially                                                // 0.0
/*776 */                    infinite loop and becomes env->current_tb. Avoid                                              // 0.0
/*778 */                    starting execution if there is a pending interrupt. */                                        // 0.0
/*780 */                 if (!unlikely (env->exit_request)) {                                                             // 0.0
/*782 */                     env->current_tb = tb;                                                                        // 0.0
/*784 */                     tc_ptr = tb->tc_ptr;                                                                         // 0.0
/*786 */                 /* execute the generated code */                                                                 // 0.0
/*788 */ #if defined(__sparc__) && !defined(CONFIG_SOLARIS)                                                               // 0.0
/*790 */ #undef env                                                                                                       // 0.0
/*792 */                     env = cpu_single_env;                                                                        // 0.0
/*794 */ #define env cpu_single_env                                                                                       // 0.0
/*796 */ #endif                                                                                                           // 0.0
/*798 */                     next_tb = tcg_qemu_tb_exec(tc_ptr);                                                          // 0.0
/*800 */                     env->current_tb = NULL;                                                                      // 0.0
/*802 */                     if ((next_tb & 3) == 2) {                                                                    // 0.0
/*804 */                         /* Instruction counter expired.  */                                                      // 0.0
/*806 */                         int insns_left;                                                                          // 0.0
/*808 */                         tb = (TranslationBlock *)(long)(next_tb & ~3);                                           // 0.0
/*810 */                         /* Restore PC.  */                                                                       // 0.0
/*812 */                         cpu_pc_from_tb(env, tb);                                                                 // 0.0
/*814 */                         insns_left = env->icount_decr.u32;                                                       // 0.0
/*816 */                         if (env->icount_extra && insns_left >= 0) {                                              // 0.0
/*818 */                             /* Refill decrementer and continue execution.  */                                    // 0.0
/*820 */                             env->icount_extra += insns_left;                                                     // 0.0
/*822 */                             if (env->icount_extra > 0xffff) {                                                    // 0.0
/*824 */                                 insns_left = 0xffff;                                                             // 0.0
/*826 */                             } else {                                                                             // 0.0
/*828 */                                 insns_left = env->icount_extra;                                                  // 0.0
/*830 */                             }                                                                                    // 0.0
/*832 */                             env->icount_extra -= insns_left;                                                     // 0.0
/*834 */                             env->icount_decr.u16.low = insns_left;                                               // 0.0
/*836 */                         } else {                                                                                 // 0.0
/*838 */                             if (insns_left > 0) {                                                                // 0.0
/*840 */                                 /* Execute remaining instructions.  */                                           // 0.0
/*842 */                                 cpu_exec_nocache(insns_left, tb);                                                // 0.0
/*844 */                             }                                                                                    // 0.0
/*846 */                             env->exception_index = EXCP_INTERRUPT;                                               // 0.0
/*848 */                             next_tb = 0;                                                                         // 0.0
/*850 */                             cpu_loop_exit();                                                                     // 0.0
/*852 */                         }                                                                                        // 0.0
/*854 */                     }                                                                                            // 0.0
/*856 */                 }                                                                                                // 0.0
/*858 */                 /* reset soft MMU for next block (it can currently                                               // 0.0
/*860 */                    only be set by a memory fault) */                                                             // 0.0
/*862 */             } /* for(;;) */                                                                                      // 0.0
/*864 */         }                                                                                                        // 0.0
/*866 */     } /* for(;;) */                                                                                              // 0.0
/*872 */ #if defined(TARGET_I386)                                                                                         // 0.0
/*874 */     /* restore flags in standard format */                                                                       // 0.0
/*876 */     env->eflags = env->eflags | helper_cc_compute_all(CC_OP) | (DF & DF_MASK);                                   // 0.0
/*878 */ #elif defined(TARGET_ARM)                                                                                        // 0.0
/*880 */     /* XXX: Save/restore host fpu exception state?.  */                                                          // 0.0
/*882 */ #elif defined(TARGET_SPARC)                                                                                      // 0.0
/*884 */ #elif defined(TARGET_PPC)                                                                                        // 0.0
/*886 */ #elif defined(TARGET_M68K)                                                                                       // 0.0
/*888 */     cpu_m68k_flush_flags(env, env->cc_op);                                                                       // 0.0
/*890 */     env->cc_op = CC_OP_FLAGS;                                                                                    // 0.0
/*892 */     env->sr = (env->sr & 0xffe0)                                                                                 // 0.0
/*894 */               | env->cc_dest | (env->cc_x << 4);                                                                 // 0.0
/*896 */ #elif defined(TARGET_MICROBLAZE)                                                                                 // 0.0
/*898 */ #elif defined(TARGET_MIPS)                                                                                       // 0.0
/*900 */ #elif defined(TARGET_SH4)                                                                                        // 0.0
/*902 */ #elif defined(TARGET_ALPHA)                                                                                      // 0.0
/*904 */ #elif defined(TARGET_CRIS)                                                                                       // 0.0
/*906 */ #elif defined(TARGET_S390X)                                                                                      // 0.0
/*908 */     /* XXXXX */                                                                                                  // 0.0
/*910 */ #else                                                                                                            // 0.0
/*912 */ #error unsupported target CPU                                                                                    // 0.0
/*914 */ #endif                                                                                                           // 0.0
/*918 */     /* restore global registers */                                                                               // 0.0
/*920 */ #include "hostregs_helper.h"                                                                                     // 0.0
/*924 */     /* fail safe : never use cpu_single_env outside cpu_exec() */                                                // 0.0
/*926 */     cpu_single_env = NULL;                                                                                       // 0.0
/*928 */     return ret;                                                                                                  // 0.0
/*930 */ }                                                                                                                // 0.0
