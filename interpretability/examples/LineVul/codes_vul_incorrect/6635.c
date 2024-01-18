// commit message qemu@9cb805fd26 (target=1, prob=0.038622454, correct=False): cpus: Define callback for QEMU "nmi" command
/*0  */ void qmp_inject_nmi(Error **errp)                           // (10) 0.03546
/*2  */ {                                                           // (27) 0.002364
/*4  */ #if defined(TARGET_I386)                                    // (16) 0.02364
/*6  */     CPUState *cs;                                           // (19) 0.01891
/*10 */     CPU_FOREACH(cs) {                                       // (14) 0.026
/*12 */         X86CPU *cpu = X86_CPU(cs);                          // (5) 0.04728
/*16 */         if (!cpu->apic_state) {                             // (7) 0.04019
/*18 */             cpu_interrupt(cs, CPU_INTERRUPT_NMI);           // (2) 0.06619
/*20 */         } else {                                            // (17) 0.02364
/*22 */             apic_deliver_nmi(cpu->apic_state);              // (3) 0.06383
/*24 */         }                                                   // (20) 0.01891
/*26 */     }                                                       // (23) 0.009456
/*28 */ #elif defined(TARGET_S390X)                                 // (12) 0.02837
/*30 */     CPUState *cs;                                           // (21) 0.01891
/*32 */     S390CPU *cpu;                                           // (18) 0.02128
/*36 */     CPU_FOREACH(cs) {                                       // (15) 0.026
/*38 */         cpu = S390_CPU(cs);                                 // (9) 0.03783
/*40 */         if (cpu->env.cpu_num == monitor_get_cpu_index()) {  // (4) 0.06147
/*42 */             if (s390_cpu_restart(S390_CPU(cs)) == -1) {     // (0) 0.07801
/*44 */                 error_set(errp, QERR_UNSUPPORTED);          // (1) 0.07329
/*46 */                 return;                                     // (8) 0.04019
/*48 */             }                                               // (13) 0.02837
/*50 */             break;                                          // (11) 0.03073
/*52 */         }                                                   // (22) 0.01891
/*54 */     }                                                       // (24) 0.009456
/*56 */ #else                                                       // (25) 0.004728
/*58 */     error_set(errp, QERR_UNSUPPORTED);                      // (6) 0.04492
/*60 */ #endif                                                      // (26) 0.004728
/*62 */ }                                                           // (28) 0.002364
