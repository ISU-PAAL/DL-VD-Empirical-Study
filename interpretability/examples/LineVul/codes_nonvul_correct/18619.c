// commit message qemu@e1833e1f96 (target=0, prob=0.13959448, correct=True): Rework PowerPC exceptions model to make it more versatile: * don't use exception vectors as the exception number.   Use vectors numbers as defined in the PowerPC embedded specification instead   and extend this model to cover all emulated PowerPC variants exceptions. * add some missing exceptions definitions, from PowerPC 2.04 specification   and actual PowerPC implementations. * add code provision for hypervisor exceptions handling. * define exception vectors and prefix in CPUPPCState to emulate BookE exception   vectors without any hacks. * define per CPU model valid exception vectors. * handle all known exceptions in user-mode only emulations. * fix hardware interrupts priorities in most cases. * change RET_EXCP macros name into GEN_EXCP as they don't return. * do not stop translation on most instructions that are not defined as   context-synchronizing in PowerPC specification. * fix PowerPC 64 jump targets and link register update when in 32 bits mode. * Fix PowerPC 464 and 464F definitions.
/*0   */ void ppc_hw_interrupt (CPUPPCState *env)                                    // (12) 0.03125
/*2   */ {                                                                           // (27) 0.001953
/*4   */     int raised = 0;                                                         // (19) 0.01562
/*8   */ #if 1                                                                       // (25) 0.005859
/*10  */     if (loglevel & CPU_LOG_INT) {                                           // (13) 0.03125
/*12  */         fprintf(logfile, "%s: %p pending %08x req %08x me %d ee %d\n",      // (0) 0.07031
/*14  */                 __func__, env, env->pending_interrupts,                     // (5) 0.05859
/*16  */                 env->interrupt_request, msr_me, msr_ee);                    // (3) 0.0625
/*18  */     }                                                                       // (22) 0.007812
/*20  */ #endif                                                                      // (26) 0.003906
/*22  */     /* Raise it */                                                          // (21) 0.01367
/*24  */     if (env->pending_interrupts & (1 << PPC_INTERRUPT_RESET)) {             // (6) 0.05664
/*26  */         /* External reset / critical input */                               // (15) 0.02734
/*28  */         /* XXX: critical input should be handled another way.               // (10) 0.03516
/*30  */          *      This code is not correct !                                  // (8) 0.03906
/*32  */          */                                                                 // (18) 0.01758
/*34  */         env->exception_index = EXCP_RESET;                                  // (9) 0.03906
/*36  */         env->pending_interrupts &= ~(1 << PPC_INTERRUPT_RESET);             // (4) 0.0625
/*38  */         raised = 1;                                                         // (17) 0.02148
/*40  */     }                                                                       // (23) 0.007812
/*42  */     if (raised == 0 && msr_me != 0) {                                       // (11) 0.0332
/*44  */         /* Machine check exception */                                       // (16) 0.02344
/*46  */         if (env->pending_interrupts & (1 << PPC_INTERRUPT_MCK)) {           // (2) 0.06445
/*48  */             env->exception_index = EXCP_MACHINE_CHECK;                      // (7) 0.05273
/*50  */             env->pending_interrupts &= ~(1 << PPC_INTERRUPT_MCK);           // (1) 0.07031
/*52  */             raised = 1;                                                     // (14) 0.0293
/*54  */         }                                                                   // (20) 0.01562
/*56  */     }                                                                       // (24) 0.007812
/*58  */     if (raised == 0 && msr_ee != 0) {                                       // 0.0
/*60  */ #if defined(TARGET_PPC64H) /* PowerPC 64 with hypervisor mode support */    // 0.0
/*62  */         /* Hypervisor decrementer exception */                              // 0.0
/*64  */         if (env->pending_interrupts & (1 << PPC_INTERRUPT_HDECR)) {         // 0.0
/*66  */             env->exception_index = EXCP_HDECR;                              // 0.0
/*68  */             env->pending_interrupts &= ~(1 << PPC_INTERRUPT_HDECR);         // 0.0
/*70  */             raised = 1;                                                     // 0.0
/*72  */         } else                                                              // 0.0
/*74  */ #endif                                                                      // 0.0
/*76  */         /* Decrementer exception */                                         // 0.0
/*78  */         if (env->pending_interrupts & (1 << PPC_INTERRUPT_DECR)) {          // 0.0
/*80  */             env->exception_index = EXCP_DECR;                               // 0.0
/*82  */             env->pending_interrupts &= ~(1 << PPC_INTERRUPT_DECR);          // 0.0
/*84  */             raised = 1;                                                     // 0.0
/*86  */         /* Programmable interval timer on embedded PowerPC */               // 0.0
/*88  */         } else if (env->pending_interrupts & (1 << PPC_INTERRUPT_PIT)) {    // 0.0
/*90  */             env->exception_index = EXCP_40x_PIT;                            // 0.0
/*92  */             env->pending_interrupts &= ~(1 << PPC_INTERRUPT_PIT);           // 0.0
/*94  */             raised = 1;                                                     // 0.0
/*96  */         /* Fixed interval timer on embedded PowerPC */                      // 0.0
/*98  */         } else if (env->pending_interrupts & (1 << PPC_INTERRUPT_FIT)) {    // 0.0
/*100 */             env->exception_index = EXCP_40x_FIT;                            // 0.0
/*102 */             env->pending_interrupts &= ~(1 << PPC_INTERRUPT_FIT);           // 0.0
/*104 */             raised = 1;                                                     // 0.0
/*106 */         /* Watchdog timer on embedded PowerPC */                            // 0.0
/*108 */         } else if (env->pending_interrupts & (1 << PPC_INTERRUPT_WDT)) {    // 0.0
/*110 */             env->exception_index = EXCP_40x_WATCHDOG;                       // 0.0
/*112 */             env->pending_interrupts &= ~(1 << PPC_INTERRUPT_WDT);           // 0.0
/*114 */             raised = 1;                                                     // 0.0
/*116 */         /* External interrupt */                                            // 0.0
/*118 */         } else if (env->pending_interrupts & (1 << PPC_INTERRUPT_EXT)) {    // 0.0
/*120 */             env->exception_index = EXCP_EXTERNAL;                           // 0.0
/*122 */             /* Taking an external interrupt does not clear the external     // 0.0
/*124 */              * interrupt status                                             // 0.0
/*126 */              */                                                             // 0.0
/*128 */ #if 0                                                                       // 0.0
/*130 */             env->pending_interrupts &= ~(1 << PPC_INTERRUPT_EXT);           // 0.0
/*132 */ #endif                                                                      // 0.0
/*134 */             raised = 1;                                                     // 0.0
/*136 */ #if 0 // TODO                                                               // 0.0
/*138 */         /* Thermal interrupt */                                             // 0.0
/*140 */         } else if (env->pending_interrupts & (1 << PPC_INTERRUPT_THERM)) {  // 0.0
/*142 */             env->exception_index = EXCP_970_THRM;                           // 0.0
/*144 */             env->pending_interrupts &= ~(1 << PPC_INTERRUPT_THERM);         // 0.0
/*146 */             raised = 1;                                                     // 0.0
/*148 */ #endif                                                                      // 0.0
/*150 */         }                                                                   // 0.0
/*152 */ #if 0 // TODO                                                               // 0.0
/*154 */     /* External debug exception */                                          // 0.0
/*156 */     } else if (env->pending_interrupts & (1 << PPC_INTERRUPT_DEBUG)) {      // 0.0
/*158 */         env->exception_index = EXCP_xxx;                                    // 0.0
/*160 */         env->pending_interrupts &= ~(1 << PPC_INTERRUPT_DEBUG);             // 0.0
/*162 */         raised = 1;                                                         // 0.0
/*164 */ #endif                                                                      // 0.0
/*166 */     }                                                                       // 0.0
/*168 */     if (raised != 0) {                                                      // 0.0
/*170 */         env->error_code = 0;                                                // 0.0
/*172 */         do_interrupt(env);                                                  // 0.0
/*174 */     }                                                                       // 0.0
/*176 */ }                                                                           // 0.0
