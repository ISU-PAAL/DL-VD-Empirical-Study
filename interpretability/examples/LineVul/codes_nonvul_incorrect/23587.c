// commit message qemu@e1833e1f96 (target=0, prob=0.99760866, correct=False): Rework PowerPC exceptions model to make it more versatile: * don't use exception vectors as the exception number.   Use vectors numbers as defined in the PowerPC embedded specification instead   and extend this model to cover all emulated PowerPC variants exceptions. * add some missing exceptions definitions, from PowerPC 2.04 specification   and actual PowerPC implementations. * add code provision for hypervisor exceptions handling. * define exception vectors and prefix in CPUPPCState to emulate BookE exception   vectors without any hacks. * define per CPU model valid exception vectors. * handle all known exceptions in user-mode only emulations. * fix hardware interrupts priorities in most cases. * change RET_EXCP macros name into GEN_EXCP as they don't return. * do not stop translation on most instructions that are not defined as   context-synchronizing in PowerPC specification. * fix PowerPC 64 jump targets and link register update when in 32 bits mode. * Fix PowerPC 464 and 464F definitions.
/*0  */ void do_load_dcr (void)                                                       // (9) 0.03247
/*2  */ {                                                                             // (15) 0.003247
/*4  */     target_ulong val;                                                         // (10) 0.02922
/*8  */     if (unlikely(env->dcr_env == NULL)) {                                     // (5) 0.05844
/*10 */         if (loglevel != 0) {                                                  // (6) 0.05195
/*12 */             fprintf(logfile, "No DCR environment\n");                         // (4) 0.08117
/*14 */         }                                                                     // (11) 0.02597
/*16 */         do_raise_exception_err(EXCP_PROGRAM, EXCP_INVAL | EXCP_INVAL_INVAL);  // (1) 0.1234
/*18 */     } else if (unlikely(ppc_dcr_read(env->dcr_env, T0, &val) != 0)) {         // (3) 0.1136
/*20 */         if (loglevel != 0) {                                                  // (7) 0.05195
/*22 */             fprintf(logfile, "DCR read error %d %03x\n", (int)T0, (int)T0);   // (0) 0.1364
/*24 */         }                                                                     // (12) 0.02597
/*26 */         do_raise_exception_err(EXCP_PROGRAM, EXCP_INVAL | EXCP_PRIV_REG);     // (2) 0.1201
/*28 */     } else {                                                                  // (13) 0.01948
/*30 */         T0 = val;                                                             // (8) 0.03896
/*32 */     }                                                                         // (14) 0.01299
/*34 */ }                                                                             // (16) 0.003247
