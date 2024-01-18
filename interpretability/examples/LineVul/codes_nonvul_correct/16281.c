// commit message qemu@41ecc72ba5 (target=0, prob=0.07116443, correct=True): signal/all: remove return value from setup_sigcontext
/*0  */ static int setup_sigcontext(struct target_sigcontext *sc,           // (13) 0.03602
/*2  */                             CPUSH4State *regs, unsigned long mask)  // (0) 0.08263
/*4  */ {                                                                   // (25) 0.002119
/*6  */     int err = 0;                                                    // (20) 0.01695
/*8  */     int i;                                                          // (22) 0.01271
/*12 */ #define COPY(x)         __put_user(regs->x, &sc->sc_##x)            // (1) 0.06992
/*14 */     COPY(gregs[0]); COPY(gregs[1]);                                 // (5) 0.04025
/*16 */     COPY(gregs[2]); COPY(gregs[3]);                                 // (6) 0.04025
/*18 */     COPY(gregs[4]); COPY(gregs[5]);                                 // (7) 0.04025
/*20 */     COPY(gregs[6]); COPY(gregs[7]);                                 // (8) 0.04025
/*22 */     COPY(gregs[8]); COPY(gregs[9]);                                 // (9) 0.04025
/*24 */     COPY(gregs[10]); COPY(gregs[11]);                               // (10) 0.04025
/*26 */     COPY(gregs[12]); COPY(gregs[13]);                               // (11) 0.04025
/*28 */     COPY(gregs[14]); COPY(gregs[15]);                               // (12) 0.04025
/*30 */     COPY(gbr); COPY(mach);                                          // (16) 0.03178
/*32 */     COPY(macl); COPY(pr);                                           // (17) 0.02966
/*34 */     COPY(sr); COPY(pc);                                             // (19) 0.02754
/*36 */ #undef COPY                                                         // (23) 0.01059
/*40 */     for (i=0; i<16; i++) {                                          // (15) 0.0339
/*42 */         __put_user(regs->fregs[i], &sc->sc_fpregs[i]);              // (2) 0.0678
/*44 */     }                                                               // (24) 0.008475
/*46 */     __put_user(regs->fpscr, &sc->sc_fpscr);                         // (4) 0.04661
/*48 */     __put_user(regs->fpul, &sc->sc_fpul);                           // (3) 0.04661
/*52 */     /* non-iBCS2 extensions.. */                                    // (18) 0.02754
/*54 */     __put_user(mask, &sc->oldmask);                                 // (14) 0.0339
/*58 */     return err;                                                     // (21) 0.01271
/*60 */ }                                                                   // (26) 0.002119
