// commit message qemu@0fbfbb59a9 (target=0, prob=0.012915706, correct=True): correctly check ppr priority during interrupt injection]
/*0  */ static void apic_update_irq(APICState *s)           // (4) 0.08333
/*2  */ {                                                   // (11) 0.005208
/*4  */     int irrv, ppr;                                  // (6) 0.05729
/*6  */     if (!(s->spurious_vec & APIC_SV_ENABLE))        // (2) 0.1146
/*8  */         return;                                     // (8) 0.04688
/*10 */     irrv = get_highest_priority_int(s->irr);        // (3) 0.1042
/*12 */     if (irrv < 0)                                   // (7) 0.05729
/*14 */         return;                                     // (9) 0.04688
/*16 */     ppr = apic_get_ppr(s);                          // (5) 0.08333
/*18 */     if (ppr && (irrv & 0xf0) <= (ppr & 0xf0))       // (0) 0.1354
/*20 */         return;                                     // (10) 0.04688
/*22 */     cpu_interrupt(s->cpu_env, CPU_INTERRUPT_HARD);  // (1) 0.125
/*24 */ }                                                   // (12) 0.005208
