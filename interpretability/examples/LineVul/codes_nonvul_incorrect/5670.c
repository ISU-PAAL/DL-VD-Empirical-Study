// commit message qemu@0919ac7876 (target=0, prob=0.9866916, correct=False): omap_intc: Qdevify
/*0   */ struct omap_mpu_state_s *omap2420_mpu_init(unsigned long sdram_size,             // (3) 0.05469
/*2   */                 const char *core)                                                // (8) 0.03906
/*4   */ {                                                                                // (26) 0.00196
/*6   */     struct omap_mpu_state_s *s = (struct omap_mpu_state_s *)                     // (5) 0.05468
/*8   */             g_malloc0(sizeof(struct omap_mpu_state_s));                          // (2) 0.06054
/*10  */     ram_addr_t sram_base, q2_base;                                               // (10) 0.03515
/*12  */     qemu_irq *cpu_irq;                                                           // (14) 0.02929
/*14  */     qemu_irq dma_irqs[4];                                                        // (11) 0.0332
/*16  */     DriveInfo *dinfo;                                                            // (21) 0.01762
/*18  */     int i;                                                                       // (24) 0.01172
/*20  */     SysBusDevice *busdev;                                                        // (17) 0.02148
/*22  */     struct omap_target_agent_s *ta;                                              // (12) 0.0293
/*26  */     /* Core */                                                                   // (23) 0.01178
/*28  */     s->mpu_model = omap2420;                                                     // (13) 0.02929
/*30  */     s->env = cpu_init(core ?: "arm1136-r2");                                     // (7) 0.04296
/*32  */     if (!s->env) {                                                               // (20) 0.01953
/*34  */         fprintf(stderr, "Unable to find CPU definition\n");                      // (6) 0.04687
/*36  */         exit(1);                                                                 // (18) 0.02148
/*38  */     }                                                                            // (25) 0.007811
/*40  */     s->sdram_size = sdram_size;                                                  // (15) 0.02929
/*42  */     s->sram_size = OMAP242X_SRAM_SIZE;                                           // (9) 0.03906
/*46  */     s->wakeup = qemu_allocate_irqs(omap_mpu_wakeup, s, 1)[0];                    // (1) 0.06444
/*50  */     /* Clocks */                                                                 // (22) 0.01367
/*52  */     omap_clk_init(s);                                                            // (16) 0.02539
/*56  */     /* Memory-mapped stuff */                                                    // (19) 0.01953
/*58  */     cpu_register_physical_memory(OMAP2_Q2_BASE, s->sdram_size,                   // (4) 0.05468
/*60  */                     (q2_base = qemu_ram_alloc(NULL, "omap2.dram",                // (0) 0.08397
/*62  */                                               s->sdram_size)) | IO_MEM_RAM);     // 0.0
/*64  */     cpu_register_physical_memory(OMAP2_SRAM_BASE, s->sram_size,                  // 0.0
/*66  */                     (sram_base = qemu_ram_alloc(NULL, "omap2.sram",              // 0.0
/*68  */                                                 s->sram_size)) | IO_MEM_RAM);    // 0.0
/*72  */     s->l4 = omap_l4_init(OMAP2_L4_BASE, 54);                                     // 0.0
/*76  */     /* Actually mapped at any 2K boundary in the ARM11 private-peripheral if */  // 0.0
/*78  */     cpu_irq = arm_pic_init_cpu(s->env);                                          // 0.0
/*80  */     s->ih[0] = omap2_inth_init(0x480fe000, 0x1000, 3, &s->irq[0],                // 0.0
/*82  */                     cpu_irq[ARM_PIC_CPU_IRQ], cpu_irq[ARM_PIC_CPU_FIQ],          // 0.0
/*84  */                     omap_findclk(s, "mpu_intc_fclk"),                            // 0.0
/*86  */                     omap_findclk(s, "mpu_intc_iclk"));                           // 0.0
/*90  */     s->prcm = omap_prcm_init(omap_l4tao(s->l4, 3),                               // 0.0
/*92  */                     s->irq[0][OMAP_INT_24XX_PRCM_MPU_IRQ], NULL, NULL, s);       // 0.0
/*96  */     s->sysc = omap_sysctl_init(omap_l4tao(s->l4, 1),                             // 0.0
/*98  */                     omap_findclk(s, "omapctrl_iclk"), s);                        // 0.0
/*102 */     for (i = 0; i < 4; i ++)                                                     // 0.0
/*104 */         dma_irqs[i] =                                                            // 0.0
/*106 */                 s->irq[omap2_dma_irq_map[i].ih][omap2_dma_irq_map[i].intr];      // 0.0
/*108 */     s->dma = omap_dma4_init(0x48056000, dma_irqs, s, 256, 32,                    // 0.0
/*110 */                     omap_findclk(s, "sdma_iclk"),                                // 0.0
/*112 */                     omap_findclk(s, "sdma_fclk"));                               // 0.0
/*114 */     s->port->addr_valid = omap2_validate_addr;                                   // 0.0
/*118 */     /* Register SDRAM and SRAM ports for fast DMA transfers.  */                 // 0.0
/*120 */     soc_dma_port_add_mem(s->dma, qemu_get_ram_ptr(q2_base),                      // 0.0
/*122 */                          OMAP2_Q2_BASE, s->sdram_size);                          // 0.0
/*124 */     soc_dma_port_add_mem(s->dma, qemu_get_ram_ptr(sram_base),                    // 0.0
/*126 */                          OMAP2_SRAM_BASE, s->sram_size);                         // 0.0
/*130 */     s->uart[0] = omap2_uart_init(omap_l4ta(s->l4, 19),                           // 0.0
/*132 */                     s->irq[0][OMAP_INT_24XX_UART1_IRQ],                          // 0.0
/*134 */                     omap_findclk(s, "uart1_fclk"),                               // 0.0
/*136 */                     omap_findclk(s, "uart1_iclk"),                               // 0.0
/*138 */                     s->drq[OMAP24XX_DMA_UART1_TX],                               // 0.0
/*140 */                     s->drq[OMAP24XX_DMA_UART1_RX],                               // 0.0
/*142 */                     "uart1",                                                     // 0.0
/*144 */                     serial_hds[0]);                                              // 0.0
/*146 */     s->uart[1] = omap2_uart_init(omap_l4ta(s->l4, 20),                           // 0.0
/*148 */                     s->irq[0][OMAP_INT_24XX_UART2_IRQ],                          // 0.0
/*150 */                     omap_findclk(s, "uart2_fclk"),                               // 0.0
/*152 */                     omap_findclk(s, "uart2_iclk"),                               // 0.0
/*154 */                     s->drq[OMAP24XX_DMA_UART2_TX],                               // 0.0
/*156 */                     s->drq[OMAP24XX_DMA_UART2_RX],                               // 0.0
/*158 */                     "uart2",                                                     // 0.0
/*160 */                     serial_hds[0] ? serial_hds[1] : NULL);                       // 0.0
/*162 */     s->uart[2] = omap2_uart_init(omap_l4ta(s->l4, 21),                           // 0.0
/*164 */                     s->irq[0][OMAP_INT_24XX_UART3_IRQ],                          // 0.0
/*166 */                     omap_findclk(s, "uart3_fclk"),                               // 0.0
/*168 */                     omap_findclk(s, "uart3_iclk"),                               // 0.0
/*170 */                     s->drq[OMAP24XX_DMA_UART3_TX],                               // 0.0
/*172 */                     s->drq[OMAP24XX_DMA_UART3_RX],                               // 0.0
/*174 */                     "uart3",                                                     // 0.0
/*176 */                     serial_hds[0] && serial_hds[1] ? serial_hds[2] : NULL);      // 0.0
/*180 */     s->gptimer[0] = omap_gp_timer_init(omap_l4ta(s->l4, 7),                      // 0.0
/*182 */                     s->irq[0][OMAP_INT_24XX_GPTIMER1],                           // 0.0
/*184 */                     omap_findclk(s, "wu_gpt1_clk"),                              // 0.0
/*186 */                     omap_findclk(s, "wu_l4_iclk"));                              // 0.0
/*188 */     s->gptimer[1] = omap_gp_timer_init(omap_l4ta(s->l4, 8),                      // 0.0
/*190 */                     s->irq[0][OMAP_INT_24XX_GPTIMER2],                           // 0.0
/*192 */                     omap_findclk(s, "core_gpt2_clk"),                            // 0.0
/*194 */                     omap_findclk(s, "core_l4_iclk"));                            // 0.0
/*196 */     s->gptimer[2] = omap_gp_timer_init(omap_l4ta(s->l4, 22),                     // 0.0
/*198 */                     s->irq[0][OMAP_INT_24XX_GPTIMER3],                           // 0.0
/*200 */                     omap_findclk(s, "core_gpt3_clk"),                            // 0.0
/*202 */                     omap_findclk(s, "core_l4_iclk"));                            // 0.0
/*204 */     s->gptimer[3] = omap_gp_timer_init(omap_l4ta(s->l4, 23),                     // 0.0
/*206 */                     s->irq[0][OMAP_INT_24XX_GPTIMER4],                           // 0.0
/*208 */                     omap_findclk(s, "core_gpt4_clk"),                            // 0.0
/*210 */                     omap_findclk(s, "core_l4_iclk"));                            // 0.0
/*212 */     s->gptimer[4] = omap_gp_timer_init(omap_l4ta(s->l4, 24),                     // 0.0
/*214 */                     s->irq[0][OMAP_INT_24XX_GPTIMER5],                           // 0.0
/*216 */                     omap_findclk(s, "core_gpt5_clk"),                            // 0.0
/*218 */                     omap_findclk(s, "core_l4_iclk"));                            // 0.0
/*220 */     s->gptimer[5] = omap_gp_timer_init(omap_l4ta(s->l4, 25),                     // 0.0
/*222 */                     s->irq[0][OMAP_INT_24XX_GPTIMER6],                           // 0.0
/*224 */                     omap_findclk(s, "core_gpt6_clk"),                            // 0.0
/*226 */                     omap_findclk(s, "core_l4_iclk"));                            // 0.0
/*228 */     s->gptimer[6] = omap_gp_timer_init(omap_l4ta(s->l4, 26),                     // 0.0
/*230 */                     s->irq[0][OMAP_INT_24XX_GPTIMER7],                           // 0.0
/*232 */                     omap_findclk(s, "core_gpt7_clk"),                            // 0.0
/*234 */                     omap_findclk(s, "core_l4_iclk"));                            // 0.0
/*236 */     s->gptimer[7] = omap_gp_timer_init(omap_l4ta(s->l4, 27),                     // 0.0
/*238 */                     s->irq[0][OMAP_INT_24XX_GPTIMER8],                           // 0.0
/*240 */                     omap_findclk(s, "core_gpt8_clk"),                            // 0.0
/*242 */                     omap_findclk(s, "core_l4_iclk"));                            // 0.0
/*244 */     s->gptimer[8] = omap_gp_timer_init(omap_l4ta(s->l4, 28),                     // 0.0
/*246 */                     s->irq[0][OMAP_INT_24XX_GPTIMER9],                           // 0.0
/*248 */                     omap_findclk(s, "core_gpt9_clk"),                            // 0.0
/*250 */                     omap_findclk(s, "core_l4_iclk"));                            // 0.0
/*252 */     s->gptimer[9] = omap_gp_timer_init(omap_l4ta(s->l4, 29),                     // 0.0
/*254 */                     s->irq[0][OMAP_INT_24XX_GPTIMER10],                          // 0.0
/*256 */                     omap_findclk(s, "core_gpt10_clk"),                           // 0.0
/*258 */                     omap_findclk(s, "core_l4_iclk"));                            // 0.0
/*260 */     s->gptimer[10] = omap_gp_timer_init(omap_l4ta(s->l4, 30),                    // 0.0
/*262 */                     s->irq[0][OMAP_INT_24XX_GPTIMER11],                          // 0.0
/*264 */                     omap_findclk(s, "core_gpt11_clk"),                           // 0.0
/*266 */                     omap_findclk(s, "core_l4_iclk"));                            // 0.0
/*268 */     s->gptimer[11] = omap_gp_timer_init(omap_l4ta(s->l4, 31),                    // 0.0
/*270 */                     s->irq[0][OMAP_INT_24XX_GPTIMER12],                          // 0.0
/*272 */                     omap_findclk(s, "core_gpt12_clk"),                           // 0.0
/*274 */                     omap_findclk(s, "core_l4_iclk"));                            // 0.0
/*278 */     omap_tap_init(omap_l4ta(s->l4, 2), s);                                       // 0.0
/*282 */     s->synctimer = omap_synctimer_init(omap_l4tao(s->l4, 2), s,                  // 0.0
/*284 */                     omap_findclk(s, "clk32-kHz"),                                // 0.0
/*286 */                     omap_findclk(s, "core_l4_iclk"));                            // 0.0
/*290 */     s->i2c[0] = omap2_i2c_init(omap_l4tao(s->l4, 5),                             // 0.0
/*292 */                     s->irq[0][OMAP_INT_24XX_I2C1_IRQ],                           // 0.0
/*294 */                     &s->drq[OMAP24XX_DMA_I2C1_TX],                               // 0.0
/*296 */                     omap_findclk(s, "i2c1.fclk"),                                // 0.0
/*298 */                     omap_findclk(s, "i2c1.iclk"));                               // 0.0
/*300 */     s->i2c[1] = omap2_i2c_init(omap_l4tao(s->l4, 6),                             // 0.0
/*302 */                     s->irq[0][OMAP_INT_24XX_I2C2_IRQ],                           // 0.0
/*304 */                     &s->drq[OMAP24XX_DMA_I2C2_TX],                               // 0.0
/*306 */                     omap_findclk(s, "i2c2.fclk"),                                // 0.0
/*308 */                     omap_findclk(s, "i2c2.iclk"));                               // 0.0
/*312 */     s->gpio = qdev_create(NULL, "omap2-gpio");                                   // 0.0
/*314 */     qdev_prop_set_int32(s->gpio, "mpu_model", s->mpu_model);                     // 0.0
/*316 */     qdev_prop_set_ptr(s->gpio, "iclk", omap_findclk(s, "gpio_iclk"));            // 0.0
/*318 */     qdev_prop_set_ptr(s->gpio, "fclk0", omap_findclk(s, "gpio1_dbclk"));         // 0.0
/*320 */     qdev_prop_set_ptr(s->gpio, "fclk1", omap_findclk(s, "gpio2_dbclk"));         // 0.0
/*322 */     qdev_prop_set_ptr(s->gpio, "fclk2", omap_findclk(s, "gpio3_dbclk"));         // 0.0
/*324 */     qdev_prop_set_ptr(s->gpio, "fclk3", omap_findclk(s, "gpio4_dbclk"));         // 0.0
/*326 */     if (s->mpu_model == omap2430) {                                              // 0.0
/*328 */         qdev_prop_set_ptr(s->gpio, "fclk4", omap_findclk(s, "gpio5_dbclk"));     // 0.0
/*330 */     }                                                                            // 0.0
/*332 */     qdev_init_nofail(s->gpio);                                                   // 0.0
/*334 */     busdev = sysbus_from_qdev(s->gpio);                                          // 0.0
/*336 */     sysbus_connect_irq(busdev, 0, s->irq[0][OMAP_INT_24XX_GPIO_BANK1]);          // 0.0
/*338 */     sysbus_connect_irq(busdev, 3, s->irq[0][OMAP_INT_24XX_GPIO_BANK2]);          // 0.0
/*340 */     sysbus_connect_irq(busdev, 6, s->irq[0][OMAP_INT_24XX_GPIO_BANK3]);          // 0.0
/*342 */     sysbus_connect_irq(busdev, 9, s->irq[0][OMAP_INT_24XX_GPIO_BANK4]);          // 0.0
/*344 */     ta = omap_l4ta(s->l4, 3);                                                    // 0.0
/*346 */     sysbus_mmio_map(busdev, 0, omap_l4_region_base(ta, 1));                      // 0.0
/*348 */     sysbus_mmio_map(busdev, 1, omap_l4_region_base(ta, 0));                      // 0.0
/*350 */     sysbus_mmio_map(busdev, 2, omap_l4_region_base(ta, 2));                      // 0.0
/*352 */     sysbus_mmio_map(busdev, 3, omap_l4_region_base(ta, 4));                      // 0.0
/*354 */     sysbus_mmio_map(busdev, 4, omap_l4_region_base(ta, 5));                      // 0.0
/*358 */     s->sdrc = omap_sdrc_init(0x68009000);                                        // 0.0
/*360 */     s->gpmc = omap_gpmc_init(s, 0x6800a000, s->irq[0][OMAP_INT_24XX_GPMC_IRQ],   // 0.0
/*362 */                              s->drq[OMAP24XX_DMA_GPMC]);                         // 0.0
/*366 */     dinfo = drive_get(IF_SD, 0, 0);                                              // 0.0
/*368 */     if (!dinfo) {                                                                // 0.0
/*370 */         fprintf(stderr, "qemu: missing SecureDigital device\n");                 // 0.0
/*372 */         exit(1);                                                                 // 0.0
/*374 */     }                                                                            // 0.0
/*376 */     s->mmc = omap2_mmc_init(omap_l4tao(s->l4, 9), dinfo->bdrv,                   // 0.0
/*378 */                     s->irq[0][OMAP_INT_24XX_MMC_IRQ],                            // 0.0
/*380 */                     &s->drq[OMAP24XX_DMA_MMC1_TX],                               // 0.0
/*382 */                     omap_findclk(s, "mmc_fclk"), omap_findclk(s, "mmc_iclk"));   // 0.0
/*386 */     s->mcspi[0] = omap_mcspi_init(omap_l4ta(s->l4, 35), 4,                       // 0.0
/*388 */                     s->irq[0][OMAP_INT_24XX_MCSPI1_IRQ],                         // 0.0
/*390 */                     &s->drq[OMAP24XX_DMA_SPI1_TX0],                              // 0.0
/*392 */                     omap_findclk(s, "spi1_fclk"),                                // 0.0
/*394 */                     omap_findclk(s, "spi1_iclk"));                               // 0.0
/*396 */     s->mcspi[1] = omap_mcspi_init(omap_l4ta(s->l4, 36), 2,                       // 0.0
/*398 */                     s->irq[0][OMAP_INT_24XX_MCSPI2_IRQ],                         // 0.0
/*400 */                     &s->drq[OMAP24XX_DMA_SPI2_TX0],                              // 0.0
/*402 */                     omap_findclk(s, "spi2_fclk"),                                // 0.0
/*404 */                     omap_findclk(s, "spi2_iclk"));                               // 0.0
/*408 */     s->dss = omap_dss_init(omap_l4ta(s->l4, 10), 0x68000800,                     // 0.0
/*410 */                     /* XXX wire M_IRQ_25, D_L2_IRQ_30 and I_IRQ_13 together */   // 0.0
/*412 */                     s->irq[0][OMAP_INT_24XX_DSS_IRQ], s->drq[OMAP24XX_DMA_DSS],  // 0.0
/*414 */                     omap_findclk(s, "dss_clk1"), omap_findclk(s, "dss_clk2"),    // 0.0
/*416 */                     omap_findclk(s, "dss_54m_clk"),                              // 0.0
/*418 */                     omap_findclk(s, "dss_l3_iclk"),                              // 0.0
/*420 */                     omap_findclk(s, "dss_l4_iclk"));                             // 0.0
/*424 */     omap_sti_init(omap_l4ta(s->l4, 18), 0x54000000,                              // 0.0
/*426 */                     s->irq[0][OMAP_INT_24XX_STI], omap_findclk(s, "emul_ck"),    // 0.0
/*428 */                     serial_hds[0] && serial_hds[1] && serial_hds[2] ?            // 0.0
/*430 */                     serial_hds[3] : NULL);                                       // 0.0
/*434 */     s->eac = omap_eac_init(omap_l4ta(s->l4, 32),                                 // 0.0
/*436 */                     s->irq[0][OMAP_INT_24XX_EAC_IRQ],                            // 0.0
/*438 */                     /* Ten consecutive lines */                                  // 0.0
/*440 */                     &s->drq[OMAP24XX_DMA_EAC_AC_RD],                             // 0.0
/*442 */                     omap_findclk(s, "func_96m_clk"),                             // 0.0
/*444 */                     omap_findclk(s, "core_l4_iclk"));                            // 0.0
/*448 */     /* All register mappings (includin those not currenlty implemented):         // 0.0
/*450 */      * SystemControlMod	48000000 - 48000fff                                      // 0.0
/*452 */      * SystemControlL4	48001000 - 48001fff                                       // 0.0
/*454 */      * 32kHz Timer Mod	48004000 - 48004fff                                       // 0.0
/*456 */      * 32kHz Timer L4	48005000 - 48005fff                                        // 0.0
/*458 */      * PRCM ModA	48008000 - 480087ff                                             // 0.0
/*460 */      * PRCM ModB	48008800 - 48008fff                                             // 0.0
/*462 */      * PRCM L4		48009000 - 48009fff                                              // 0.0
/*464 */      * TEST-BCM Mod	48012000 - 48012fff                                          // 0.0
/*466 */      * TEST-BCM L4	48013000 - 48013fff                                           // 0.0
/*468 */      * TEST-TAP Mod	48014000 - 48014fff                                          // 0.0
/*470 */      * TEST-TAP L4	48015000 - 48015fff                                           // 0.0
/*472 */      * GPIO1 Mod	48018000 - 48018fff                                             // 0.0
/*474 */      * GPIO Top		48019000 - 48019fff                                             // 0.0
/*476 */      * GPIO2 Mod	4801a000 - 4801afff                                             // 0.0
/*478 */      * GPIO L4		4801b000 - 4801bfff                                              // 0.0
/*480 */      * GPIO3 Mod	4801c000 - 4801cfff                                             // 0.0
/*482 */      * GPIO4 Mod	4801e000 - 4801efff                                             // 0.0
/*484 */      * WDTIMER1 Mod	48020000 - 48010fff                                          // 0.0
/*486 */      * WDTIMER Top	48021000 - 48011fff                                           // 0.0
/*488 */      * WDTIMER2 Mod	48022000 - 48012fff                                          // 0.0
/*490 */      * WDTIMER L4	48023000 - 48013fff                                            // 0.0
/*492 */      * WDTIMER3 Mod	48024000 - 48014fff                                          // 0.0
/*494 */      * WDTIMER3 L4	48025000 - 48015fff                                           // 0.0
/*496 */      * WDTIMER4 Mod	48026000 - 48016fff                                          // 0.0
/*498 */      * WDTIMER4 L4	48027000 - 48017fff                                           // 0.0
/*500 */      * GPTIMER1 Mod	48028000 - 48018fff                                          // 0.0
/*502 */      * GPTIMER1 L4	48029000 - 48019fff                                           // 0.0
/*504 */      * GPTIMER2 Mod	4802a000 - 4801afff                                          // 0.0
/*506 */      * GPTIMER2 L4	4802b000 - 4801bfff                                           // 0.0
/*508 */      * L4-Config AP	48040000 - 480407ff                                          // 0.0
/*510 */      * L4-Config IP	48040800 - 48040fff                                          // 0.0
/*512 */      * L4-Config LA	48041000 - 48041fff                                          // 0.0
/*514 */      * ARM11ETB Mod	48048000 - 48049fff                                          // 0.0
/*516 */      * ARM11ETB L4	4804a000 - 4804afff                                           // 0.0
/*518 */      * DISPLAY Top	48050000 - 480503ff                                           // 0.0
/*520 */      * DISPLAY DISPC	48050400 - 480507ff                                         // 0.0
/*522 */      * DISPLAY RFBI	48050800 - 48050bff                                          // 0.0
/*524 */      * DISPLAY VENC	48050c00 - 48050fff                                          // 0.0
/*526 */      * DISPLAY L4	48051000 - 48051fff                                            // 0.0
/*528 */      * CAMERA Top	48052000 - 480523ff                                            // 0.0
/*530 */      * CAMERA core	48052400 - 480527ff                                           // 0.0
/*532 */      * CAMERA DMA	48052800 - 48052bff                                            // 0.0
/*534 */      * CAMERA MMU	48052c00 - 48052fff                                            // 0.0
/*536 */      * CAMERA L4	48053000 - 48053fff                                             // 0.0
/*538 */      * SDMA Mod		48056000 - 48056fff                                             // 0.0
/*540 */      * SDMA L4		48057000 - 48057fff                                              // 0.0
/*542 */      * SSI Top		48058000 - 48058fff                                              // 0.0
/*544 */      * SSI GDD		48059000 - 48059fff                                              // 0.0
/*546 */      * SSI Port1	4805a000 - 4805afff                                             // 0.0
/*548 */      * SSI Port2	4805b000 - 4805bfff                                             // 0.0
/*550 */      * SSI L4		4805c000 - 4805cfff                                               // 0.0
/*552 */      * USB Mod		4805e000 - 480fefff                                              // 0.0
/*554 */      * USB L4		4805f000 - 480fffff                                               // 0.0
/*556 */      * WIN_TRACER1 Mod	48060000 - 48060fff                                       // 0.0
/*558 */      * WIN_TRACER1 L4	48061000 - 48061fff                                        // 0.0
/*560 */      * WIN_TRACER2 Mod	48062000 - 48062fff                                       // 0.0
/*562 */      * WIN_TRACER2 L4	48063000 - 48063fff                                        // 0.0
/*564 */      * WIN_TRACER3 Mod	48064000 - 48064fff                                       // 0.0
/*566 */      * WIN_TRACER3 L4	48065000 - 48065fff                                        // 0.0
/*568 */      * WIN_TRACER4 Top	48066000 - 480660ff                                       // 0.0
/*570 */      * WIN_TRACER4 ETT	48066100 - 480661ff                                       // 0.0
/*572 */      * WIN_TRACER4 WT	48066200 - 480662ff                                        // 0.0
/*574 */      * WIN_TRACER4 L4	48067000 - 48067fff                                        // 0.0
/*576 */      * XTI Mod		48068000 - 48068fff                                              // 0.0
/*578 */      * XTI L4		48069000 - 48069fff                                               // 0.0
/*580 */      * UART1 Mod	4806a000 - 4806afff                                             // 0.0
/*582 */      * UART1 L4		4806b000 - 4806bfff                                             // 0.0
/*584 */      * UART2 Mod	4806c000 - 4806cfff                                             // 0.0
/*586 */      * UART2 L4		4806d000 - 4806dfff                                             // 0.0
/*588 */      * UART3 Mod	4806e000 - 4806efff                                             // 0.0
/*590 */      * UART3 L4		4806f000 - 4806ffff                                             // 0.0
/*592 */      * I2C1 Mod		48070000 - 48070fff                                             // 0.0
/*594 */      * I2C1 L4		48071000 - 48071fff                                              // 0.0
/*596 */      * I2C2 Mod		48072000 - 48072fff                                             // 0.0
/*598 */      * I2C2 L4		48073000 - 48073fff                                              // 0.0
/*600 */      * McBSP1 Mod	48074000 - 48074fff                                            // 0.0
/*602 */      * McBSP1 L4	48075000 - 48075fff                                             // 0.0
/*604 */      * McBSP2 Mod	48076000 - 48076fff                                            // 0.0
/*606 */      * McBSP2 L4	48077000 - 48077fff                                             // 0.0
/*608 */      * GPTIMER3 Mod	48078000 - 48078fff                                          // 0.0
/*610 */      * GPTIMER3 L4	48079000 - 48079fff                                           // 0.0
/*612 */      * GPTIMER4 Mod	4807a000 - 4807afff                                          // 0.0
/*614 */      * GPTIMER4 L4	4807b000 - 4807bfff                                           // 0.0
/*616 */      * GPTIMER5 Mod	4807c000 - 4807cfff                                          // 0.0
/*618 */      * GPTIMER5 L4	4807d000 - 4807dfff                                           // 0.0
/*620 */      * GPTIMER6 Mod	4807e000 - 4807efff                                          // 0.0
/*622 */      * GPTIMER6 L4	4807f000 - 4807ffff                                           // 0.0
/*624 */      * GPTIMER7 Mod	48080000 - 48080fff                                          // 0.0
/*626 */      * GPTIMER7 L4	48081000 - 48081fff                                           // 0.0
/*628 */      * GPTIMER8 Mod	48082000 - 48082fff                                          // 0.0
/*630 */      * GPTIMER8 L4	48083000 - 48083fff                                           // 0.0
/*632 */      * GPTIMER9 Mod	48084000 - 48084fff                                          // 0.0
/*634 */      * GPTIMER9 L4	48085000 - 48085fff                                           // 0.0
/*636 */      * GPTIMER10 Mod	48086000 - 48086fff                                         // 0.0
/*638 */      * GPTIMER10 L4	48087000 - 48087fff                                          // 0.0
/*640 */      * GPTIMER11 Mod	48088000 - 48088fff                                         // 0.0
/*642 */      * GPTIMER11 L4	48089000 - 48089fff                                          // 0.0
/*644 */      * GPTIMER12 Mod	4808a000 - 4808afff                                         // 0.0
/*646 */      * GPTIMER12 L4	4808b000 - 4808bfff                                          // 0.0
/*648 */      * EAC Mod		48090000 - 48090fff                                              // 0.0
/*650 */      * EAC L4		48091000 - 48091fff                                               // 0.0
/*652 */      * FAC Mod		48092000 - 48092fff                                              // 0.0
/*654 */      * FAC L4		48093000 - 48093fff                                               // 0.0
/*656 */      * MAILBOX Mod	48094000 - 48094fff                                           // 0.0
/*658 */      * MAILBOX L4	48095000 - 48095fff                                            // 0.0
/*660 */      * SPI1 Mod		48098000 - 48098fff                                             // 0.0
/*662 */      * SPI1 L4		48099000 - 48099fff                                              // 0.0
/*664 */      * SPI2 Mod		4809a000 - 4809afff                                             // 0.0
/*666 */      * SPI2 L4		4809b000 - 4809bfff                                              // 0.0
/*668 */      * MMC/SDIO Mod	4809c000 - 4809cfff                                          // 0.0
/*670 */      * MMC/SDIO L4	4809d000 - 4809dfff                                           // 0.0
/*672 */      * MS_PRO Mod	4809e000 - 4809efff                                            // 0.0
/*674 */      * MS_PRO L4	4809f000 - 4809ffff                                             // 0.0
/*676 */      * RNG Mod		480a0000 - 480a0fff                                              // 0.0
/*678 */      * RNG L4		480a1000 - 480a1fff                                               // 0.0
/*680 */      * DES3DES Mod	480a2000 - 480a2fff                                           // 0.0
/*682 */      * DES3DES L4	480a3000 - 480a3fff                                            // 0.0
/*684 */      * SHA1MD5 Mod	480a4000 - 480a4fff                                           // 0.0
/*686 */      * SHA1MD5 L4	480a5000 - 480a5fff                                            // 0.0
/*688 */      * AES Mod		480a6000 - 480a6fff                                              // 0.0
/*690 */      * AES L4		480a7000 - 480a7fff                                               // 0.0
/*692 */      * PKA Mod		480a8000 - 480a9fff                                              // 0.0
/*694 */      * PKA L4		480aa000 - 480aafff                                               // 0.0
/*696 */      * MG Mod		480b0000 - 480b0fff                                               // 0.0
/*698 */      * MG L4		480b1000 - 480b1fff                                                // 0.0
/*700 */      * HDQ/1-wire Mod	480b2000 - 480b2fff                                        // 0.0
/*702 */      * HDQ/1-wire L4	480b3000 - 480b3fff                                         // 0.0
/*704 */      * MPU interrupt	480fe000 - 480fefff                                         // 0.0
/*706 */      * STI channel base	54000000 - 5400ffff                                      // 0.0
/*708 */      * IVA RAM		5c000000 - 5c01ffff                                              // 0.0
/*710 */      * IVA ROM		5c020000 - 5c027fff                                              // 0.0
/*712 */      * IMG_BUF_A	5c040000 - 5c040fff                                             // 0.0
/*714 */      * IMG_BUF_B	5c042000 - 5c042fff                                             // 0.0
/*716 */      * VLCDS		5c048000 - 5c0487ff                                                // 0.0
/*718 */      * IMX_COEF		5c049000 - 5c04afff                                             // 0.0
/*720 */      * IMX_CMD		5c051000 - 5c051fff                                              // 0.0
/*722 */      * VLCDQ		5c053000 - 5c0533ff                                                // 0.0
/*724 */      * VLCDH		5c054000 - 5c054fff                                                // 0.0
/*726 */      * SEQ_CMD		5c055000 - 5c055fff                                              // 0.0
/*728 */      * IMX_REG		5c056000 - 5c0560ff                                              // 0.0
/*730 */      * VLCD_REG		5c056100 - 5c0561ff                                             // 0.0
/*732 */      * SEQ_REG		5c056200 - 5c0562ff                                              // 0.0
/*734 */      * IMG_BUF_REG	5c056300 - 5c0563ff                                           // 0.0
/*736 */      * SEQIRQ_REG	5c056400 - 5c0564ff                                            // 0.0
/*738 */      * OCP_REG		5c060000 - 5c060fff                                              // 0.0
/*740 */      * SYSC_REG		5c070000 - 5c070fff                                             // 0.0
/*742 */      * MMU_REG		5d000000 - 5d000fff                                              // 0.0
/*744 */      * sDMA R		68000400 - 680005ff                                               // 0.0
/*746 */      * sDMA W		68000600 - 680007ff                                               // 0.0
/*748 */      * Display Control	68000800 - 680009ff                                       // 0.0
/*750 */      * DSP subsystem	68000a00 - 68000bff                                         // 0.0
/*752 */      * MPU subsystem	68000c00 - 68000dff                                         // 0.0
/*754 */      * IVA subsystem	68001000 - 680011ff                                         // 0.0
/*756 */      * USB		68001200 - 680013ff                                                  // 0.0
/*758 */      * Camera		68001400 - 680015ff                                               // 0.0
/*760 */      * VLYNQ (firewall)	68001800 - 68001bff                                      // 0.0
/*762 */      * VLYNQ		68001e00 - 68001fff                                                // 0.0
/*764 */      * SSI		68002000 - 680021ff                                                  // 0.0
/*766 */      * L4		68002400 - 680025ff                                                   // 0.0
/*768 */      * DSP (firewall)	68002800 - 68002bff                                        // 0.0
/*770 */      * DSP subsystem	68002e00 - 68002fff                                         // 0.0
/*772 */      * IVA (firewall)	68003000 - 680033ff                                        // 0.0
/*774 */      * IVA		68003600 - 680037ff                                                  // 0.0
/*776 */      * GFX		68003a00 - 68003bff                                                  // 0.0
/*778 */      * CMDWR emulation	68003c00 - 68003dff                                       // 0.0
/*780 */      * SMS		68004000 - 680041ff                                                  // 0.0
/*782 */      * OCM		68004200 - 680043ff                                                  // 0.0
/*784 */      * GPMC		68004400 - 680045ff                                                 // 0.0
/*786 */      * RAM (firewall)	68005000 - 680053ff                                        // 0.0
/*788 */      * RAM (err login)	68005400 - 680057ff                                       // 0.0
/*790 */      * ROM (firewall)	68005800 - 68005bff                                        // 0.0
/*792 */      * ROM (err login)	68005c00 - 68005fff                                       // 0.0
/*794 */      * GPMC (firewall)	68006000 - 680063ff                                       // 0.0
/*796 */      * GPMC (err login)	68006400 - 680067ff                                      // 0.0
/*798 */      * SMS (err login)	68006c00 - 68006fff                                       // 0.0
/*800 */      * SMS registers	68008000 - 68008fff                                         // 0.0
/*802 */      * SDRC registers	68009000 - 68009fff                                        // 0.0
/*804 */      * GPMC registers	6800a000   6800afff                                        // 0.0
/*806 */      */                                                                          // 0.0
/*810 */     qemu_register_reset(omap2_mpu_reset, s);                                     // 0.0
/*814 */     return s;                                                                    // 0.0
/*816 */ }                                                                                // 0.0
