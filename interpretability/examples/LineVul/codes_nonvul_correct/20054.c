// commit message qemu@a8170e5e97 (target=0, prob=0.012619351, correct=True): Rename target_phys_addr_t to hwaddr
/*0   */ static uint64_t gt64120_readl (void *opaque,                                  // (7) 0.03516
/*2   */                                target_phys_addr_t addr, unsigned size)        // (0) 0.08203
/*4   */ {                                                                             // (32) 0.001953
/*6   */     GT64120State *s = opaque;                                                 // (18) 0.02344
/*8   */     PCIHostState *phb = PCI_HOST_BRIDGE(s);                                   // (2) 0.04102
/*10  */     uint32_t val;                                                             // (24) 0.01758
/*12  */     uint32_t saddr;                                                           // (22) 0.01953
/*16  */     saddr = (addr & 0xfff) >> 2;                                              // (10) 0.03125
/*18  */     switch (saddr) {                                                          // (25) 0.01758
/*22  */     /* CPU Configuration */                                                   // (31) 0.01367
/*24  */     case GT_MULTI:                                                            // (23) 0.01953
/*26  */         /* Only one GT64xxx is present on the CPU bus, return                 // (3) 0.04102
/*28  */            the initial value */                                               // (12) 0.02734
/*30  */         val = s->regs[saddr];                                                 // (8) 0.0332
/*32  */         break;                                                                // (26) 0.01758
/*36  */     /* CPU Error Report */                                                    // (29) 0.01562
/*38  */     case GT_CPUERR_ADDRLO:                                                    // (13) 0.02734
/*40  */     case GT_CPUERR_ADDRHI:                                                    // (14) 0.02734
/*42  */     case GT_CPUERR_DATALO:                                                    // (11) 0.0293
/*44  */     case GT_CPUERR_DATAHI:                                                    // (16) 0.02539
/*46  */     case GT_CPUERR_PARITY:                                                    // (17) 0.02539
/*48  */         /* Emulated memory has no error, always return the initial            // (5) 0.03711
/*50  */            values */                                                          // (19) 0.02344
/*52  */         val = s->regs[saddr];                                                 // (9) 0.0332
/*54  */         break;                                                                // (27) 0.01758
/*58  */     /* CPU Sync Barrier */                                                    // (30) 0.01562
/*60  */     case GT_PCI0SYNC:                                                         // (20) 0.02344
/*62  */     case GT_PCI1SYNC:                                                         // (21) 0.02344
/*64  */         /* Reading those register should empty all FIFO on the PCI            // (4) 0.03906
/*66  */            bus, which are not emulated. The return value should be            // (1) 0.04492
/*68  */            a random value that should be ignored. */                          // (6) 0.03711
/*70  */         val = 0xc000ffee;                                                     // (15) 0.02734
/*72  */         break;                                                                // (28) 0.01758
/*76  */     /* ECC */                                                                 // 0.0
/*78  */     case GT_ECC_ERRDATALO:                                                    // 0.0
/*80  */     case GT_ECC_ERRDATAHI:                                                    // 0.0
/*82  */     case GT_ECC_MEM:                                                          // 0.0
/*84  */     case GT_ECC_CALC:                                                         // 0.0
/*86  */     case GT_ECC_ERRADDR:                                                      // 0.0
/*88  */         /* Emulated memory has no error, always return the initial            // 0.0
/*90  */            values */                                                          // 0.0
/*92  */         val = s->regs[saddr];                                                 // 0.0
/*94  */         break;                                                                // 0.0
/*98  */     case GT_CPU:                                                              // 0.0
/*100 */     case GT_SCS10LD:                                                          // 0.0
/*102 */     case GT_SCS10HD:                                                          // 0.0
/*104 */     case GT_SCS32LD:                                                          // 0.0
/*106 */     case GT_SCS32HD:                                                          // 0.0
/*108 */     case GT_CS20LD:                                                           // 0.0
/*110 */     case GT_CS20HD:                                                           // 0.0
/*112 */     case GT_CS3BOOTLD:                                                        // 0.0
/*114 */     case GT_CS3BOOTHD:                                                        // 0.0
/*116 */     case GT_SCS10AR:                                                          // 0.0
/*118 */     case GT_SCS32AR:                                                          // 0.0
/*120 */     case GT_CS20R:                                                            // 0.0
/*122 */     case GT_CS3BOOTR:                                                         // 0.0
/*124 */     case GT_PCI0IOLD:                                                         // 0.0
/*126 */     case GT_PCI0M0LD:                                                         // 0.0
/*128 */     case GT_PCI0M1LD:                                                         // 0.0
/*130 */     case GT_PCI1IOLD:                                                         // 0.0
/*132 */     case GT_PCI1M0LD:                                                         // 0.0
/*134 */     case GT_PCI1M1LD:                                                         // 0.0
/*136 */     case GT_PCI0IOHD:                                                         // 0.0
/*138 */     case GT_PCI0M0HD:                                                         // 0.0
/*140 */     case GT_PCI0M1HD:                                                         // 0.0
/*142 */     case GT_PCI1IOHD:                                                         // 0.0
/*144 */     case GT_PCI1M0HD:                                                         // 0.0
/*146 */     case GT_PCI1M1HD:                                                         // 0.0
/*148 */     case GT_PCI0IOREMAP:                                                      // 0.0
/*150 */     case GT_PCI0M0REMAP:                                                      // 0.0
/*152 */     case GT_PCI0M1REMAP:                                                      // 0.0
/*154 */     case GT_PCI1IOREMAP:                                                      // 0.0
/*156 */     case GT_PCI1M0REMAP:                                                      // 0.0
/*158 */     case GT_PCI1M1REMAP:                                                      // 0.0
/*160 */     case GT_ISD:                                                              // 0.0
/*162 */         val = s->regs[saddr];                                                 // 0.0
/*164 */         break;                                                                // 0.0
/*166 */     case GT_PCI0_IACK:                                                        // 0.0
/*168 */         /* Read the IRQ number */                                             // 0.0
/*170 */         val = pic_read_irq(isa_pic);                                          // 0.0
/*172 */         break;                                                                // 0.0
/*176 */     /* SDRAM and Device Address Decode */                                     // 0.0
/*178 */     case GT_SCS0LD:                                                           // 0.0
/*180 */     case GT_SCS0HD:                                                           // 0.0
/*182 */     case GT_SCS1LD:                                                           // 0.0
/*184 */     case GT_SCS1HD:                                                           // 0.0
/*186 */     case GT_SCS2LD:                                                           // 0.0
/*188 */     case GT_SCS2HD:                                                           // 0.0
/*190 */     case GT_SCS3LD:                                                           // 0.0
/*192 */     case GT_SCS3HD:                                                           // 0.0
/*194 */     case GT_CS0LD:                                                            // 0.0
/*196 */     case GT_CS0HD:                                                            // 0.0
/*198 */     case GT_CS1LD:                                                            // 0.0
/*200 */     case GT_CS1HD:                                                            // 0.0
/*202 */     case GT_CS2LD:                                                            // 0.0
/*204 */     case GT_CS2HD:                                                            // 0.0
/*206 */     case GT_CS3LD:                                                            // 0.0
/*208 */     case GT_CS3HD:                                                            // 0.0
/*210 */     case GT_BOOTLD:                                                           // 0.0
/*212 */     case GT_BOOTHD:                                                           // 0.0
/*214 */     case GT_ADERR:                                                            // 0.0
/*216 */         val = s->regs[saddr];                                                 // 0.0
/*218 */         break;                                                                // 0.0
/*222 */     /* SDRAM Configuration */                                                 // 0.0
/*224 */     case GT_SDRAM_CFG:                                                        // 0.0
/*226 */     case GT_SDRAM_OPMODE:                                                     // 0.0
/*228 */     case GT_SDRAM_BM:                                                         // 0.0
/*230 */     case GT_SDRAM_ADDRDECODE:                                                 // 0.0
/*232 */         val = s->regs[saddr];                                                 // 0.0
/*234 */         break;                                                                // 0.0
/*238 */     /* SDRAM Parameters */                                                    // 0.0
/*240 */     case GT_SDRAM_B0:                                                         // 0.0
/*242 */     case GT_SDRAM_B1:                                                         // 0.0
/*244 */     case GT_SDRAM_B2:                                                         // 0.0
/*246 */     case GT_SDRAM_B3:                                                         // 0.0
/*248 */         /* We don't simulate electrical parameters of the SDRAM.              // 0.0
/*250 */            Just return the last written value. */                             // 0.0
/*252 */         val = s->regs[saddr];                                                 // 0.0
/*254 */         break;                                                                // 0.0
/*258 */     /* Device Parameters */                                                   // 0.0
/*260 */     case GT_DEV_B0:                                                           // 0.0
/*262 */     case GT_DEV_B1:                                                           // 0.0
/*264 */     case GT_DEV_B2:                                                           // 0.0
/*266 */     case GT_DEV_B3:                                                           // 0.0
/*268 */     case GT_DEV_BOOT:                                                         // 0.0
/*270 */         val = s->regs[saddr];                                                 // 0.0
/*272 */         break;                                                                // 0.0
/*276 */     /* DMA Record */                                                          // 0.0
/*278 */     case GT_DMA0_CNT:                                                         // 0.0
/*280 */     case GT_DMA1_CNT:                                                         // 0.0
/*282 */     case GT_DMA2_CNT:                                                         // 0.0
/*284 */     case GT_DMA3_CNT:                                                         // 0.0
/*286 */     case GT_DMA0_SA:                                                          // 0.0
/*288 */     case GT_DMA1_SA:                                                          // 0.0
/*290 */     case GT_DMA2_SA:                                                          // 0.0
/*292 */     case GT_DMA3_SA:                                                          // 0.0
/*294 */     case GT_DMA0_DA:                                                          // 0.0
/*296 */     case GT_DMA1_DA:                                                          // 0.0
/*298 */     case GT_DMA2_DA:                                                          // 0.0
/*300 */     case GT_DMA3_DA:                                                          // 0.0
/*302 */     case GT_DMA0_NEXT:                                                        // 0.0
/*304 */     case GT_DMA1_NEXT:                                                        // 0.0
/*306 */     case GT_DMA2_NEXT:                                                        // 0.0
/*308 */     case GT_DMA3_NEXT:                                                        // 0.0
/*310 */     case GT_DMA0_CUR:                                                         // 0.0
/*312 */     case GT_DMA1_CUR:                                                         // 0.0
/*314 */     case GT_DMA2_CUR:                                                         // 0.0
/*316 */     case GT_DMA3_CUR:                                                         // 0.0
/*318 */         val = s->regs[saddr];                                                 // 0.0
/*320 */         break;                                                                // 0.0
/*324 */     /* DMA Channel Control */                                                 // 0.0
/*326 */     case GT_DMA0_CTRL:                                                        // 0.0
/*328 */     case GT_DMA1_CTRL:                                                        // 0.0
/*330 */     case GT_DMA2_CTRL:                                                        // 0.0
/*332 */     case GT_DMA3_CTRL:                                                        // 0.0
/*334 */         val = s->regs[saddr];                                                 // 0.0
/*336 */         break;                                                                // 0.0
/*340 */     /* DMA Arbiter */                                                         // 0.0
/*342 */     case GT_DMA_ARB:                                                          // 0.0
/*344 */         val = s->regs[saddr];                                                 // 0.0
/*346 */         break;                                                                // 0.0
/*350 */     /* Timer/Counter */                                                       // 0.0
/*352 */     case GT_TC0:                                                              // 0.0
/*354 */     case GT_TC1:                                                              // 0.0
/*356 */     case GT_TC2:                                                              // 0.0
/*358 */     case GT_TC3:                                                              // 0.0
/*360 */     case GT_TC_CONTROL:                                                       // 0.0
/*362 */         val = s->regs[saddr];                                                 // 0.0
/*364 */         break;                                                                // 0.0
/*368 */     /* PCI Internal */                                                        // 0.0
/*370 */     case GT_PCI0_CFGADDR:                                                     // 0.0
/*372 */         val = phb->config_reg;                                                // 0.0
/*374 */         break;                                                                // 0.0
/*376 */     case GT_PCI0_CFGDATA:                                                     // 0.0
/*378 */         if (!(phb->config_reg & (1 << 31))) {                                 // 0.0
/*380 */             val = 0xffffffff;                                                 // 0.0
/*382 */         } else {                                                              // 0.0
/*384 */             val = pci_data_read(phb->bus, phb->config_reg, 4);                // 0.0
/*386 */         }                                                                     // 0.0
/*388 */         if (!(s->regs[GT_PCI0_CMD] & 1) && (phb->config_reg & 0x00fff800)) {  // 0.0
/*390 */             val = bswap32(val);                                               // 0.0
/*392 */         }                                                                     // 0.0
/*394 */         break;                                                                // 0.0
/*398 */     case GT_PCI0_CMD:                                                         // 0.0
/*400 */     case GT_PCI0_TOR:                                                         // 0.0
/*402 */     case GT_PCI0_BS_SCS10:                                                    // 0.0
/*404 */     case GT_PCI0_BS_SCS32:                                                    // 0.0
/*406 */     case GT_PCI0_BS_CS20:                                                     // 0.0
/*408 */     case GT_PCI0_BS_CS3BT:                                                    // 0.0
/*410 */     case GT_PCI1_IACK:                                                        // 0.0
/*412 */     case GT_PCI0_BARE:                                                        // 0.0
/*414 */     case GT_PCI0_PREFMBR:                                                     // 0.0
/*416 */     case GT_PCI0_SCS10_BAR:                                                   // 0.0
/*418 */     case GT_PCI0_SCS32_BAR:                                                   // 0.0
/*420 */     case GT_PCI0_CS20_BAR:                                                    // 0.0
/*422 */     case GT_PCI0_CS3BT_BAR:                                                   // 0.0
/*424 */     case GT_PCI0_SSCS10_BAR:                                                  // 0.0
/*426 */     case GT_PCI0_SSCS32_BAR:                                                  // 0.0
/*428 */     case GT_PCI0_SCS3BT_BAR:                                                  // 0.0
/*430 */     case GT_PCI1_CMD:                                                         // 0.0
/*432 */     case GT_PCI1_TOR:                                                         // 0.0
/*434 */     case GT_PCI1_BS_SCS10:                                                    // 0.0
/*436 */     case GT_PCI1_BS_SCS32:                                                    // 0.0
/*438 */     case GT_PCI1_BS_CS20:                                                     // 0.0
/*440 */     case GT_PCI1_BS_CS3BT:                                                    // 0.0
/*442 */     case GT_PCI1_BARE:                                                        // 0.0
/*444 */     case GT_PCI1_PREFMBR:                                                     // 0.0
/*446 */     case GT_PCI1_SCS10_BAR:                                                   // 0.0
/*448 */     case GT_PCI1_SCS32_BAR:                                                   // 0.0
/*450 */     case GT_PCI1_CS20_BAR:                                                    // 0.0
/*452 */     case GT_PCI1_CS3BT_BAR:                                                   // 0.0
/*454 */     case GT_PCI1_SSCS10_BAR:                                                  // 0.0
/*456 */     case GT_PCI1_SSCS32_BAR:                                                  // 0.0
/*458 */     case GT_PCI1_SCS3BT_BAR:                                                  // 0.0
/*460 */     case GT_PCI1_CFGADDR:                                                     // 0.0
/*462 */     case GT_PCI1_CFGDATA:                                                     // 0.0
/*464 */         val = s->regs[saddr];                                                 // 0.0
/*466 */         break;                                                                // 0.0
/*470 */     /* Interrupts */                                                          // 0.0
/*472 */     case GT_INTRCAUSE:                                                        // 0.0
/*474 */         val = s->regs[saddr];                                                 // 0.0
/*476 */         DPRINTF("INTRCAUSE %x\n", val);                                       // 0.0
/*478 */         break;                                                                // 0.0
/*480 */     case GT_INTRMASK:                                                         // 0.0
/*482 */         val = s->regs[saddr];                                                 // 0.0
/*484 */         DPRINTF("INTRMASK %x\n", val);                                        // 0.0
/*486 */         break;                                                                // 0.0
/*488 */     case GT_PCI0_ICMASK:                                                      // 0.0
/*490 */         val = s->regs[saddr];                                                 // 0.0
/*492 */         DPRINTF("ICMASK %x\n", val);                                          // 0.0
/*494 */         break;                                                                // 0.0
/*496 */     case GT_PCI0_SERR0MASK:                                                   // 0.0
/*498 */         val = s->regs[saddr];                                                 // 0.0
/*500 */         DPRINTF("SERR0MASK %x\n", val);                                       // 0.0
/*502 */         break;                                                                // 0.0
/*506 */     /* Reserved when only PCI_0 is configured. */                             // 0.0
/*508 */     case GT_HINTRCAUSE:                                                       // 0.0
/*510 */     case GT_CPU_INTSEL:                                                       // 0.0
/*512 */     case GT_PCI0_INTSEL:                                                      // 0.0
/*514 */     case GT_HINTRMASK:                                                        // 0.0
/*516 */     case GT_PCI0_HICMASK:                                                     // 0.0
/*518 */     case GT_PCI1_SERR1MASK:                                                   // 0.0
/*520 */         val = s->regs[saddr];                                                 // 0.0
/*522 */         break;                                                                // 0.0
/*526 */     default:                                                                  // 0.0
/*528 */         val = s->regs[saddr];                                                 // 0.0
/*530 */         DPRINTF ("Bad register offset 0x%x\n", (int)addr);                    // 0.0
/*532 */         break;                                                                // 0.0
/*534 */     }                                                                         // 0.0
/*538 */     if (!(s->regs[GT_CPU] & 0x00001000))                                      // 0.0
/*540 */         val = bswap32(val);                                                   // 0.0
/*544 */     return val;                                                               // 0.0
/*546 */ }                                                                             // 0.0
