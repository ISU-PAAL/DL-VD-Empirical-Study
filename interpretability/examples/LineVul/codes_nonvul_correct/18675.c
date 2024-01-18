// commit message qemu@e1833e1f96 (target=0, prob=0.095695995, correct=True): Rework PowerPC exceptions model to make it more versatile: * don't use exception vectors as the exception number.   Use vectors numbers as defined in the PowerPC embedded specification instead   and extend this model to cover all emulated PowerPC variants exceptions. * add some missing exceptions definitions, from PowerPC 2.04 specification   and actual PowerPC implementations. * add code provision for hypervisor exceptions handling. * define exception vectors and prefix in CPUPPCState to emulate BookE exception   vectors without any hacks. * define per CPU model valid exception vectors. * handle all known exceptions in user-mode only emulations. * fix hardware interrupts priorities in most cases. * change RET_EXCP macros name into GEN_EXCP as they don't return. * do not stop translation on most instructions that are not defined as   context-synchronizing in PowerPC specification. * fix PowerPC 64 jump targets and link register update when in 32 bits mode. * Fix PowerPC 464 and 464F definitions.
/*0  */ void do_tw (int flags)                                                  // (6) 0.03019
/*2  */ {                                                                       // (8) 0.003774
/*4  */     if (!likely(!(((int32_t)T0 < (int32_t)T1 && (flags & 0x10)) ||      // (4) 0.1321
/*6  */                   ((int32_t)T0 > (int32_t)T1 && (flags & 0x08)) ||      // (1) 0.1623
/*8  */                   ((int32_t)T0 == (int32_t)T1 && (flags & 0x04)) ||     // (2) 0.1623
/*10 */                   ((uint32_t)T0 < (uint32_t)T1 && (flags & 0x02)) ||    // (3) 0.1623
/*12 */                   ((uint32_t)T0 > (uint32_t)T1 && (flags & 0x01))))) {  // (0) 0.166
/*14 */         do_raise_exception_err(EXCP_PROGRAM, EXCP_TRAP);                // (5) 0.1094
/*16 */     }                                                                   // (7) 0.01509
/*18 */ }                                                                       // (9) 0.003774
