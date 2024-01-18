// commit message qemu@fb6971c110 (target=1, prob=0.36942813, correct=False): hw/ppc/ppc405_uc.c: Avoid integer overflows
/*0   */ static void ppc405cr_clk_setup (ppc405cr_cpc_t *cpc)                            // (5) 0.04883
/*2   */ {                                                                               // (24) 0.001953
/*4   */     uint64_t VCO_out, PLL_out;                                                  // (12) 0.0332
/*6   */     uint32_t CPU_clk, TMR_clk, SDRAM_clk, PLB_clk, OPB_clk, EXT_clk, UART_clk;  // (0) 0.09375
/*8   */     int M, D0, D1, D2;                                                          // (16) 0.0293
/*12  */     D0 = ((cpc->pllmr >> 26) & 0x3) + 1; /* CBDV */                             // (3) 0.05469
/*14  */     if (cpc->pllmr & 0x80000000) {                                              // (10) 0.03516
/*16  */         D1 = (((cpc->pllmr >> 20) - 1) & 0xF) + 1; /* FBDV */                   // (1) 0.07227
/*18  */         D2 = 8 - ((cpc->pllmr >> 16) & 0x7); /* FWDVA */                        // (2) 0.0625
/*20  */         M = D0 * D1 * D2;                                                       // (11) 0.03516
/*22  */         VCO_out = cpc->sysclk * M;                                              // (7) 0.04102
/*24  */         if (VCO_out < 400000000 || VCO_out > 800000000) {                       // (4) 0.05078
/*26  */             /* PLL cannot lock */                                               // (13) 0.0332
/*28  */             cpc->pllmr &= ~0x80000000;                                          // (6) 0.04883
/*30  */             goto bypass_pll;                                                    // (14) 0.0332
/*32  */         }                                                                       // (20) 0.01562
/*34  */         PLL_out = VCO_out / D2;                                                 // (9) 0.03906
/*36  */     } else {                                                                    // (22) 0.01172
/*38  */         /* Bypass PLL */                                                        // (17) 0.02539
/*40  */     bypass_pll:                                                                 // (21) 0.01562
/*42  */         M = D0;                                                                 // (19) 0.02344
/*44  */         PLL_out = cpc->sysclk * M;                                              // (8) 0.04102
/*46  */     }                                                                           // (23) 0.007812
/*48  */     CPU_clk = PLL_out;                                                          // (18) 0.02539
/*50  */     if (cpc->cr1 & 0x00800000)                                                  // (15) 0.0332
/*52  */         TMR_clk = cpc->sysclk; /* Should have a separate clock */               // 0.0
/*54  */     else                                                                        // 0.0
/*56  */         TMR_clk = CPU_clk;                                                      // 0.0
/*58  */     PLB_clk = CPU_clk / D0;                                                     // 0.0
/*60  */     SDRAM_clk = PLB_clk;                                                        // 0.0
/*62  */     D0 = ((cpc->pllmr >> 10) & 0x3) + 1;                                        // 0.0
/*64  */     OPB_clk = PLB_clk / D0;                                                     // 0.0
/*66  */     D0 = ((cpc->pllmr >> 24) & 0x3) + 2;                                        // 0.0
/*68  */     EXT_clk = PLB_clk / D0;                                                     // 0.0
/*70  */     D0 = ((cpc->cr0 >> 1) & 0x1F) + 1;                                          // 0.0
/*72  */     UART_clk = CPU_clk / D0;                                                    // 0.0
/*74  */     /* Setup CPU clocks */                                                      // 0.0
/*76  */     clk_setup(&cpc->clk_setup[PPC405CR_CPU_CLK], CPU_clk);                      // 0.0
/*78  */     /* Setup time-base clock */                                                 // 0.0
/*80  */     clk_setup(&cpc->clk_setup[PPC405CR_TMR_CLK], TMR_clk);                      // 0.0
/*82  */     /* Setup PLB clock */                                                       // 0.0
/*84  */     clk_setup(&cpc->clk_setup[PPC405CR_PLB_CLK], PLB_clk);                      // 0.0
/*86  */     /* Setup SDRAM clock */                                                     // 0.0
/*88  */     clk_setup(&cpc->clk_setup[PPC405CR_SDRAM_CLK], SDRAM_clk);                  // 0.0
/*90  */     /* Setup OPB clock */                                                       // 0.0
/*92  */     clk_setup(&cpc->clk_setup[PPC405CR_OPB_CLK], OPB_clk);                      // 0.0
/*94  */     /* Setup external clock */                                                  // 0.0
/*96  */     clk_setup(&cpc->clk_setup[PPC405CR_EXT_CLK], EXT_clk);                      // 0.0
/*98  */     /* Setup UART clock */                                                      // 0.0
/*100 */     clk_setup(&cpc->clk_setup[PPC405CR_UART_CLK], UART_clk);                    // 0.0
/*102 */ }                                                                               // 0.0
