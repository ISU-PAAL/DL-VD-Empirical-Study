// commit message qemu@3db3659bf6 (target=0, prob=0.06488826, correct=True): apic: Resolve potential endless loop around apic_update_irq
/*0  */ static void apic_update_irq(APICCommonState *s)          // (6) 0.08416
/*2  */ {                                                        // (10) 0.00495
/*4  */     if (!(s->spurious_vec & APIC_SV_ENABLE)) {           // (4) 0.1139
/*6  */         return;                                          // (7) 0.04455
/*8  */     }                                                    // (8) 0.0198
/*10 */     if (apic_irq_pending(s) > 0) {                       // (5) 0.09901
/*12 */         cpu_interrupt(s->cpu_env, CPU_INTERRUPT_HARD);   // (0) 0.1386
/*14 */     } else if (apic_accept_pic_intr(&s->busdev.qdev) &&  // (2) 0.1287
/*16 */                pic_get_output(isa_pic)) {                // (3) 0.1238
/*18 */         apic_deliver_pic_intr(&s->busdev.qdev, 1);       // (1) 0.1386
/*20 */     }                                                    // (9) 0.0198
/*22 */ }                                                        // (11) 0.00495
