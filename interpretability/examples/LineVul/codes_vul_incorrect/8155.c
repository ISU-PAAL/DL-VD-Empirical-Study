// commit message qemu@fb6971c110 (target=1, prob=0.44387498, correct=False): hw/ppc/ppc405_uc.c: Avoid integer overflows
/*0   */ static void ppc405ep_compute_clocks (ppc405ep_cpc_t *cpc)                    // (9) 0.05078
/*2   */ {                                                                            // (21) 0.001953
/*4   */     uint32_t CPU_clk, PLB_clk, OPB_clk, EBC_clk, MAL_clk, PCI_clk;           // (2) 0.08008
/*6   */     uint32_t UART0_clk, UART1_clk;                                           // (11) 0.04102
/*8   */     uint64_t VCO_out, PLL_out;                                               // (13) 0.0332
/*10  */     int M, D;                                                                // (17) 0.01562
/*14  */     VCO_out = 0;                                                             // (14) 0.01953
/*16  */     if ((cpc->pllmr[1] & 0x80000000) && !(cpc->pllmr[1] & 0x40000000)) {     // (3) 0.07617
/*18  */         M = (((cpc->pllmr[1] >> 20) - 1) & 0xF) + 1; /* FBMUL */             // (4) 0.07617
/*20  */ #ifdef DEBUG_CLOCKS_LL                                                       // (15) 0.01953
/*22  */         printf("FBMUL %01" PRIx32 " %d\n", (cpc->pllmr[1] >> 20) & 0xF, M);  // (0) 0.08789
/*24  */ #endif                                                                       // (19) 0.003906
/*26  */         D = 8 - ((cpc->pllmr[1] >> 16) & 0x7); /* FWDA */                    // (5) 0.06445
/*28  */ #ifdef DEBUG_CLOCKS_LL                                                       // (16) 0.01953
/*30  */         printf("FWDA %01" PRIx32 " %d\n", (cpc->pllmr[1] >> 16) & 0x7, D);   // (1) 0.08594
/*32  */ #endif                                                                       // (20) 0.003906
/*34  */         VCO_out = cpc->sysclk * M * D;                                       // (10) 0.04492
/*36  */         if (VCO_out < 500000000UL || VCO_out > 1000000000UL) {               // (7) 0.05469
/*38  */             /* Error - unlock the PLL */                                     // (12) 0.03711
/*40  */             printf("VCO out of range %" PRIu64 "\n", VCO_out);               // (6) 0.0625
/*42  */ #if 0                                                                        // (18) 0.005859
/*44  */             cpc->pllmr[1] &= ~0x80000000;                                    // (8) 0.05469
/*46  */             goto pll_bypass;                                                 // 0.0
/*48  */ #endif                                                                       // 0.0
/*50  */         }                                                                    // 0.0
/*52  */         PLL_out = VCO_out / D;                                               // 0.0
/*54  */         /* Pretend the PLL is locked */                                      // 0.0
/*56  */         cpc->boot |= 0x00000001;                                             // 0.0
/*58  */     } else {                                                                 // 0.0
/*60  */ #if 0                                                                        // 0.0
/*62  */     pll_bypass:                                                              // 0.0
/*64  */ #endif                                                                       // 0.0
/*66  */         PLL_out = cpc->sysclk;                                               // 0.0
/*68  */         if (cpc->pllmr[1] & 0x40000000) {                                    // 0.0
/*70  */             /* Pretend the PLL is not locked */                              // 0.0
/*72  */             cpc->boot &= ~0x00000001;                                        // 0.0
/*74  */         }                                                                    // 0.0
/*76  */     }                                                                        // 0.0
/*78  */     /* Now, compute all other clocks */                                      // 0.0
/*80  */     D = ((cpc->pllmr[0] >> 20) & 0x3) + 1; /* CCDV */                        // 0.0
/*82  */ #ifdef DEBUG_CLOCKS_LL                                                       // 0.0
/*84  */     printf("CCDV %01" PRIx32 " %d\n", (cpc->pllmr[0] >> 20) & 0x3, D);       // 0.0
/*86  */ #endif                                                                       // 0.0
/*88  */     CPU_clk = PLL_out / D;                                                   // 0.0
/*90  */     D = ((cpc->pllmr[0] >> 16) & 0x3) + 1; /* CBDV */                        // 0.0
/*92  */ #ifdef DEBUG_CLOCKS_LL                                                       // 0.0
/*94  */     printf("CBDV %01" PRIx32 " %d\n", (cpc->pllmr[0] >> 16) & 0x3, D);       // 0.0
/*96  */ #endif                                                                       // 0.0
/*98  */     PLB_clk = CPU_clk / D;                                                   // 0.0
/*100 */     D = ((cpc->pllmr[0] >> 12) & 0x3) + 1; /* OPDV */                        // 0.0
/*102 */ #ifdef DEBUG_CLOCKS_LL                                                       // 0.0
/*104 */     printf("OPDV %01" PRIx32 " %d\n", (cpc->pllmr[0] >> 12) & 0x3, D);       // 0.0
/*106 */ #endif                                                                       // 0.0
/*108 */     OPB_clk = PLB_clk / D;                                                   // 0.0
/*110 */     D = ((cpc->pllmr[0] >> 8) & 0x3) + 2; /* EPDV */                         // 0.0
/*112 */ #ifdef DEBUG_CLOCKS_LL                                                       // 0.0
/*114 */     printf("EPDV %01" PRIx32 " %d\n", (cpc->pllmr[0] >> 8) & 0x3, D);        // 0.0
/*116 */ #endif                                                                       // 0.0
/*118 */     EBC_clk = PLB_clk / D;                                                   // 0.0
/*120 */     D = ((cpc->pllmr[0] >> 4) & 0x3) + 1; /* MPDV */                         // 0.0
/*122 */ #ifdef DEBUG_CLOCKS_LL                                                       // 0.0
/*124 */     printf("MPDV %01" PRIx32 " %d\n", (cpc->pllmr[0] >> 4) & 0x3, D);        // 0.0
/*126 */ #endif                                                                       // 0.0
/*128 */     MAL_clk = PLB_clk / D;                                                   // 0.0
/*130 */     D = (cpc->pllmr[0] & 0x3) + 1; /* PPDV */                                // 0.0
/*132 */ #ifdef DEBUG_CLOCKS_LL                                                       // 0.0
/*134 */     printf("PPDV %01" PRIx32 " %d\n", cpc->pllmr[0] & 0x3, D);               // 0.0
/*136 */ #endif                                                                       // 0.0
/*138 */     PCI_clk = PLB_clk / D;                                                   // 0.0
/*140 */     D = ((cpc->ucr - 1) & 0x7F) + 1; /* U0DIV */                             // 0.0
/*142 */ #ifdef DEBUG_CLOCKS_LL                                                       // 0.0
/*144 */     printf("U0DIV %01" PRIx32 " %d\n", cpc->ucr & 0x7F, D);                  // 0.0
/*146 */ #endif                                                                       // 0.0
/*148 */     UART0_clk = PLL_out / D;                                                 // 0.0
/*150 */     D = (((cpc->ucr >> 8) - 1) & 0x7F) + 1; /* U1DIV */                      // 0.0
/*152 */ #ifdef DEBUG_CLOCKS_LL                                                       // 0.0
/*154 */     printf("U1DIV %01" PRIx32 " %d\n", (cpc->ucr >> 8) & 0x7F, D);           // 0.0
/*156 */ #endif                                                                       // 0.0
/*158 */     UART1_clk = PLL_out / D;                                                 // 0.0
/*160 */ #ifdef DEBUG_CLOCKS                                                          // 0.0
/*162 */     printf("Setup PPC405EP clocks - sysclk %" PRIu32 " VCO %" PRIu64         // 0.0
/*164 */            " PLL out %" PRIu64 " Hz\n", cpc->sysclk, VCO_out, PLL_out);      // 0.0
/*166 */     printf("CPU %" PRIu32 " PLB %" PRIu32 " OPB %" PRIu32 " EBC %" PRIu32    // 0.0
/*168 */            " MAL %" PRIu32 " PCI %" PRIu32 " UART0 %" PRIu32                 // 0.0
/*170 */            " UART1 %" PRIu32 "\n",                                           // 0.0
/*172 */            CPU_clk, PLB_clk, OPB_clk, EBC_clk, MAL_clk, PCI_clk,             // 0.0
/*174 */            UART0_clk, UART1_clk);                                            // 0.0
/*176 */ #endif                                                                       // 0.0
/*178 */     /* Setup CPU clocks */                                                   // 0.0
/*180 */     clk_setup(&cpc->clk_setup[PPC405EP_CPU_CLK], CPU_clk);                   // 0.0
/*182 */     /* Setup PLB clock */                                                    // 0.0
/*184 */     clk_setup(&cpc->clk_setup[PPC405EP_PLB_CLK], PLB_clk);                   // 0.0
/*186 */     /* Setup OPB clock */                                                    // 0.0
/*188 */     clk_setup(&cpc->clk_setup[PPC405EP_OPB_CLK], OPB_clk);                   // 0.0
/*190 */     /* Setup external clock */                                               // 0.0
/*192 */     clk_setup(&cpc->clk_setup[PPC405EP_EBC_CLK], EBC_clk);                   // 0.0
/*194 */     /* Setup MAL clock */                                                    // 0.0
/*196 */     clk_setup(&cpc->clk_setup[PPC405EP_MAL_CLK], MAL_clk);                   // 0.0
/*198 */     /* Setup PCI clock */                                                    // 0.0
/*200 */     clk_setup(&cpc->clk_setup[PPC405EP_PCI_CLK], PCI_clk);                   // 0.0
/*202 */     /* Setup UART0 clock */                                                  // 0.0
/*204 */     clk_setup(&cpc->clk_setup[PPC405EP_UART0_CLK], UART0_clk);               // 0.0
/*206 */     /* Setup UART1 clock */                                                  // 0.0
/*208 */     clk_setup(&cpc->clk_setup[PPC405EP_UART1_CLK], UART1_clk);               // 0.0
/*210 */ }                                                                            // 0.0
