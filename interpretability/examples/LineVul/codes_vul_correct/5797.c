// commit message qemu@4c4f0e4801 (target=1, prob=0.8206534, correct=True): openpic: fix debug prints
/*0  */ static uint64_t openpic_tmr_read(void *opaque, hwaddr addr, unsigned len)  // (2) 0.05372
/*2  */ {                                                                          // (31) 0.002066
/*4  */     OpenPICState *opp = opaque;                                            // (15) 0.02479
/*6  */     uint32_t retval = -1;                                                  // (14) 0.02686
/*8  */     int idx;                                                               // (25) 0.01446
/*12 */     DPRINTF("%s: addr %08x\n", __func__, addr);                            // (4) 0.04752
/*14 */     if (addr & 0xF) {                                                      // (16) 0.02479
/*16 */         goto out;                                                          // (19) 0.02066
/*18 */     }                                                                      // (27) 0.008264
/*20 */     idx = (addr >> 6) & 0x3;                                               // (11) 0.03306
/*22 */     if (addr == 0x0) {                                                     // (17) 0.02479
/*24 */         /* TIFR (TFRR) */                                                  // (12) 0.03306
/*26 */         retval = opp->tifr;                                                // (13) 0.03099
/*28 */         goto out;                                                          // (20) 0.02066
/*30 */     }                                                                      // (28) 0.008264
/*32 */     switch (addr & 0x30) {                                                 // (18) 0.02479
/*34 */     case 0x00: /* TICC (GTCCR) */                                          // (7) 0.03719
/*36 */         retval = opp->timers[idx].ticc;                                    // (6) 0.04339
/*38 */         break;                                                             // (21) 0.0186
/*40 */     case 0x10: /* TIBC (GTBCR) */                                          // (9) 0.03512
/*42 */         retval = opp->timers[idx].tibc;                                    // (5) 0.04545
/*44 */         break;                                                             // (22) 0.0186
/*46 */     case 0x20: /* TIPV (TIPV) */                                           // (8) 0.03719
/*48 */         retval = read_IRQreg_ipvp(opp, opp->irq_tim0 + idx);               // (0) 0.06612
/*50 */         break;                                                             // (23) 0.0186
/*52 */     case 0x30: /* TIDE (TIDR) */                                           // (10) 0.03512
/*54 */         retval = read_IRQreg_ide(opp, opp->irq_tim0 + idx);                // (1) 0.06405
/*56 */         break;                                                             // (24) 0.0186
/*58 */     }                                                                      // (29) 0.008264
/*62 */ out:                                                                       // (30) 0.004132
/*64 */     DPRINTF("%s: => %08x\n", __func__, retval);                            // (3) 0.04959
/*68 */     return retval;                                                         // (26) 0.01446
/*70 */ }                                                                          // (32) 0.002066
