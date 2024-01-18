// commit message qemu@1453e6627d (target=0, prob=0.038360275, correct=True): cpus: call the core nmi injection function
/*0  */ void qmp_inject_nmi(Error **errp)                       // (5) 0.07143
/*2  */ {                                                       // (14) 0.004762
/*4  */ #if defined(TARGET_I386)                                // (7) 0.04762
/*6  */     CPUState *cs;                                       // (9) 0.0381
/*10 */     CPU_FOREACH(cs) {                                   // (6) 0.05238
/*12 */         X86CPU *cpu = X86_CPU(cs);                      // (3) 0.09524
/*16 */         if (!cpu->apic_state) {                         // (4) 0.08095
/*18 */             cpu_interrupt(cs, CPU_INTERRUPT_NMI);       // (0) 0.1333
/*20 */         } else {                                        // (8) 0.04762
/*22 */             apic_deliver_nmi(cpu->apic_state);          // (1) 0.1286
/*24 */         }                                               // (10) 0.0381
/*26 */     }                                                   // (11) 0.01905
/*28 */ #else                                                   // (12) 0.009524
/*30 */     nmi_monitor_handle(monitor_get_cpu_index(), errp);  // (2) 0.1
/*32 */ #endif                                                  // (13) 0.009524
/*34 */ }                                                       // (15) 0.004762
