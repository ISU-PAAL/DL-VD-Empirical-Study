// commit message qemu@016d2e1dfa (target=1, prob=0.03942885, correct=False): signal/all: remove return value from restore_sigcontext
/*0  */ restore_sigcontext(CPUMIPSState *regs, struct target_sigcontext *sc)  // (10) 0.04752
/*2  */ {                                                                     // (24) 0.00198
/*4  */     int err = 0;                                                      // (17) 0.01584
/*6  */     int i;                                                            // (19) 0.01188
/*10 */     __get_user(regs->CP0_EPC, &sc->sc_pc);                            // (11) 0.04752
/*14 */     __get_user(regs->active_tc.HI[0], &sc->sc_mdhi);                  // (2) 0.05347
/*16 */     __get_user(regs->active_tc.LO[0], &sc->sc_mdlo);                  // (3) 0.05347
/*20 */     for (i = 1; i < 32; ++i) {                                        // (14) 0.03366
/*22 */         __get_user(regs->active_tc.gpr[i], &sc->sc_regs[i]);          // (1) 0.06733
/*24 */     }                                                                 // (20) 0.007921
/*28 */     __get_user(regs->active_tc.HI[1], &sc->sc_hi1);                   // (4) 0.05347
/*30 */     __get_user(regs->active_tc.HI[2], &sc->sc_hi2);                   // (5) 0.05347
/*32 */     __get_user(regs->active_tc.HI[3], &sc->sc_hi3);                   // (6) 0.05347
/*34 */     __get_user(regs->active_tc.LO[1], &sc->sc_lo1);                   // (7) 0.05347
/*36 */     __get_user(regs->active_tc.LO[2], &sc->sc_lo2);                   // (8) 0.05347
/*38 */     __get_user(regs->active_tc.LO[3], &sc->sc_lo3);                   // (9) 0.05347
/*40 */     {                                                                 // (21) 0.007921
/*42 */         uint32_t dsp;                                                 // (16) 0.02772
/*44 */         __get_user(dsp, &sc->sc_dsp);                                 // (13) 0.04554
/*46 */         cpu_wrdsp(dsp, 0x3ff, regs);                                  // (12) 0.04752
/*48 */     }                                                                 // (22) 0.007921
/*52 */     for (i = 0; i < 32; ++i) {                                        // (15) 0.03366
/*54 */         __get_user(regs->active_fpu.fpr[i].d, &sc->sc_fpregs[i]);     // (0) 0.07525
/*56 */     }                                                                 // (23) 0.007921
/*60 */     return err;                                                       // (18) 0.01188
/*62 */ }                                                                     // (25) 0.00198
