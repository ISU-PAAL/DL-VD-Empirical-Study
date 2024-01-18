// commit message qemu@4be746345f (target=0, prob=0.89397097, correct=False): hw: Convert from BlockDriverState to BlockBackend, mostly
/*0   */ struct omap_mpu_state_s *omap310_mpu_init(MemoryRegion *system_memory,            // (5) 0.05274
/*2   */                 unsigned long sdram_size,                                         // (7) 0.04297
/*4   */                 const char *core)                                                 // (8) 0.03906
/*6   */ {                                                                                 // (27) 0.001953
/*8   */     int i;                                                                        // (24) 0.01172
/*10  */     struct omap_mpu_state_s *s = (struct omap_mpu_state_s *)                      // (4) 0.05469
/*12  */             g_malloc0(sizeof(struct omap_mpu_state_s));                           // (3) 0.06055
/*14  */     qemu_irq dma_irqs[6];                                                         // (11) 0.0332
/*16  */     DriveInfo *dinfo;                                                             // (21) 0.01758
/*18  */     SysBusDevice *busdev;                                                         // (18) 0.02148
/*22  */     if (!core)                                                                    // (23) 0.01367
/*24  */         core = "ti925t";                                                          // (15) 0.02734
/*28  */     /* Core */                                                                    // (25) 0.01172
/*30  */     s->mpu_model = omap310;                                                       // (14) 0.02734
/*32  */     s->cpu = cpu_arm_init(core);                                                  // (12) 0.0293
/*34  */     if (s->cpu == NULL) {                                                         // (17) 0.02344
/*36  */         fprintf(stderr, "Unable to find CPU definition\n");                       // (6) 0.04687
/*38  */         exit(1);                                                                  // (19) 0.02148
/*40  */     }                                                                             // (26) 0.007812
/*42  */     s->sdram_size = sdram_size;                                                   // (13) 0.0293
/*44  */     s->sram_size = OMAP15XX_SRAM_SIZE;                                            // (9) 0.03906
/*48  */     s->wakeup = qemu_allocate_irq(omap_mpu_wakeup, s, 0);                         // (2) 0.06055
/*52  */     /* Clocks */                                                                  // (22) 0.01367
/*54  */     omap_clk_init(s);                                                             // (16) 0.02539
/*58  */     /* Memory-mapped stuff */                                                     // (20) 0.01953
/*60  */     memory_region_init_ram(&s->emiff_ram, NULL, "omap1.dram", s->sdram_size,      // (0) 0.06836
/*62  */                            &error_abort);                                         // (1) 0.06251
/*64  */     vmstate_register_ram_global(&s->emiff_ram);                                   // (10) 0.03711
/*66  */     memory_region_add_subregion(system_memory, OMAP_EMIFF_BASE, &s->emiff_ram);   // 0.0
/*68  */     memory_region_init_ram(&s->imif_ram, NULL, "omap1.sram", s->sram_size,        // 0.0
/*70  */                            &error_abort);                                         // 0.0
/*72  */     vmstate_register_ram_global(&s->imif_ram);                                    // 0.0
/*74  */     memory_region_add_subregion(system_memory, OMAP_IMIF_BASE, &s->imif_ram);     // 0.0
/*78  */     omap_clkm_init(system_memory, 0xfffece00, 0xe1008000, s);                     // 0.0
/*82  */     s->ih[0] = qdev_create(NULL, "omap-intc");                                    // 0.0
/*84  */     qdev_prop_set_uint32(s->ih[0], "size", 0x100);                                // 0.0
/*86  */     qdev_prop_set_ptr(s->ih[0], "clk", omap_findclk(s, "arminth_ck"));            // 0.0
/*88  */     qdev_init_nofail(s->ih[0]);                                                   // 0.0
/*90  */     busdev = SYS_BUS_DEVICE(s->ih[0]);                                            // 0.0
/*92  */     sysbus_connect_irq(busdev, 0,                                                 // 0.0
/*94  */                        qdev_get_gpio_in(DEVICE(s->cpu), ARM_CPU_IRQ));            // 0.0
/*96  */     sysbus_connect_irq(busdev, 1,                                                 // 0.0
/*98  */                        qdev_get_gpio_in(DEVICE(s->cpu), ARM_CPU_FIQ));            // 0.0
/*100 */     sysbus_mmio_map(busdev, 0, 0xfffecb00);                                       // 0.0
/*102 */     s->ih[1] = qdev_create(NULL, "omap-intc");                                    // 0.0
/*104 */     qdev_prop_set_uint32(s->ih[1], "size", 0x800);                                // 0.0
/*106 */     qdev_prop_set_ptr(s->ih[1], "clk", omap_findclk(s, "arminth_ck"));            // 0.0
/*108 */     qdev_init_nofail(s->ih[1]);                                                   // 0.0
/*110 */     busdev = SYS_BUS_DEVICE(s->ih[1]);                                            // 0.0
/*112 */     sysbus_connect_irq(busdev, 0,                                                 // 0.0
/*114 */                        qdev_get_gpio_in(s->ih[0], OMAP_INT_15XX_IH2_IRQ));        // 0.0
/*116 */     /* The second interrupt controller's FIQ output is not wired up */            // 0.0
/*118 */     sysbus_mmio_map(busdev, 0, 0xfffe0000);                                       // 0.0
/*122 */     for (i = 0; i < 6; i++) {                                                     // 0.0
/*124 */         dma_irqs[i] = qdev_get_gpio_in(s->ih[omap1_dma_irq_map[i].ih],            // 0.0
/*126 */                                        omap1_dma_irq_map[i].intr);                // 0.0
/*128 */     }                                                                             // 0.0
/*130 */     s->dma = omap_dma_init(0xfffed800, dma_irqs, system_memory,                   // 0.0
/*132 */                            qdev_get_gpio_in(s->ih[0], OMAP_INT_DMA_LCD),          // 0.0
/*134 */                            s, omap_findclk(s, "dma_ck"), omap_dma_3_1);           // 0.0
/*138 */     s->port[emiff    ].addr_valid = omap_validate_emiff_addr;                     // 0.0
/*140 */     s->port[emifs    ].addr_valid = omap_validate_emifs_addr;                     // 0.0
/*142 */     s->port[imif     ].addr_valid = omap_validate_imif_addr;                      // 0.0
/*144 */     s->port[tipb     ].addr_valid = omap_validate_tipb_addr;                      // 0.0
/*146 */     s->port[local    ].addr_valid = omap_validate_local_addr;                     // 0.0
/*148 */     s->port[tipb_mpui].addr_valid = omap_validate_tipb_mpui_addr;                 // 0.0
/*152 */     /* Register SDRAM and SRAM DMA ports for fast transfers.  */                  // 0.0
/*154 */     soc_dma_port_add_mem(s->dma, memory_region_get_ram_ptr(&s->emiff_ram),        // 0.0
/*156 */                          OMAP_EMIFF_BASE, s->sdram_size);                         // 0.0
/*158 */     soc_dma_port_add_mem(s->dma, memory_region_get_ram_ptr(&s->imif_ram),         // 0.0
/*160 */                          OMAP_IMIF_BASE, s->sram_size);                           // 0.0
/*164 */     s->timer[0] = omap_mpu_timer_init(system_memory, 0xfffec500,                  // 0.0
/*166 */                     qdev_get_gpio_in(s->ih[0], OMAP_INT_TIMER1),                  // 0.0
/*168 */                     omap_findclk(s, "mputim_ck"));                                // 0.0
/*170 */     s->timer[1] = omap_mpu_timer_init(system_memory, 0xfffec600,                  // 0.0
/*172 */                     qdev_get_gpio_in(s->ih[0], OMAP_INT_TIMER2),                  // 0.0
/*174 */                     omap_findclk(s, "mputim_ck"));                                // 0.0
/*176 */     s->timer[2] = omap_mpu_timer_init(system_memory, 0xfffec700,                  // 0.0
/*178 */                     qdev_get_gpio_in(s->ih[0], OMAP_INT_TIMER3),                  // 0.0
/*180 */                     omap_findclk(s, "mputim_ck"));                                // 0.0
/*184 */     s->wdt = omap_wd_timer_init(system_memory, 0xfffec800,                        // 0.0
/*186 */                     qdev_get_gpio_in(s->ih[0], OMAP_INT_WD_TIMER),                // 0.0
/*188 */                     omap_findclk(s, "armwdt_ck"));                                // 0.0
/*192 */     s->os_timer = omap_os_timer_init(system_memory, 0xfffb9000,                   // 0.0
/*194 */                     qdev_get_gpio_in(s->ih[1], OMAP_INT_OS_TIMER),                // 0.0
/*196 */                     omap_findclk(s, "clk32-kHz"));                                // 0.0
/*200 */     s->lcd = omap_lcdc_init(system_memory, 0xfffec000,                            // 0.0
/*202 */                             qdev_get_gpio_in(s->ih[0], OMAP_INT_LCD_CTRL),        // 0.0
/*204 */                             omap_dma_get_lcdch(s->dma),                           // 0.0
/*206 */                             omap_findclk(s, "lcd_ck"));                           // 0.0
/*210 */     omap_ulpd_pm_init(system_memory, 0xfffe0800, s);                              // 0.0
/*212 */     omap_pin_cfg_init(system_memory, 0xfffe1000, s);                              // 0.0
/*214 */     omap_id_init(system_memory, s);                                               // 0.0
/*218 */     omap_mpui_init(system_memory, 0xfffec900, s);                                 // 0.0
/*222 */     s->private_tipb = omap_tipb_bridge_init(system_memory, 0xfffeca00,            // 0.0
/*224 */                     qdev_get_gpio_in(s->ih[0], OMAP_INT_BRIDGE_PRIV),             // 0.0
/*226 */                     omap_findclk(s, "tipb_ck"));                                  // 0.0
/*228 */     s->public_tipb = omap_tipb_bridge_init(system_memory, 0xfffed300,             // 0.0
/*230 */                     qdev_get_gpio_in(s->ih[0], OMAP_INT_BRIDGE_PUB),              // 0.0
/*232 */                     omap_findclk(s, "tipb_ck"));                                  // 0.0
/*236 */     omap_tcmi_init(system_memory, 0xfffecc00, s);                                 // 0.0
/*240 */     s->uart[0] = omap_uart_init(0xfffb0000,                                       // 0.0
/*242 */                                 qdev_get_gpio_in(s->ih[1], OMAP_INT_UART1),       // 0.0
/*244 */                     omap_findclk(s, "uart1_ck"),                                  // 0.0
/*246 */                     omap_findclk(s, "uart1_ck"),                                  // 0.0
/*248 */                     s->drq[OMAP_DMA_UART1_TX], s->drq[OMAP_DMA_UART1_RX],         // 0.0
/*250 */                     "uart1",                                                      // 0.0
/*252 */                     serial_hds[0]);                                               // 0.0
/*254 */     s->uart[1] = omap_uart_init(0xfffb0800,                                       // 0.0
/*256 */                                 qdev_get_gpio_in(s->ih[1], OMAP_INT_UART2),       // 0.0
/*258 */                     omap_findclk(s, "uart2_ck"),                                  // 0.0
/*260 */                     omap_findclk(s, "uart2_ck"),                                  // 0.0
/*262 */                     s->drq[OMAP_DMA_UART2_TX], s->drq[OMAP_DMA_UART2_RX],         // 0.0
/*264 */                     "uart2",                                                      // 0.0
/*266 */                     serial_hds[0] ? serial_hds[1] : NULL);                        // 0.0
/*268 */     s->uart[2] = omap_uart_init(0xfffb9800,                                       // 0.0
/*270 */                                 qdev_get_gpio_in(s->ih[0], OMAP_INT_UART3),       // 0.0
/*272 */                     omap_findclk(s, "uart3_ck"),                                  // 0.0
/*274 */                     omap_findclk(s, "uart3_ck"),                                  // 0.0
/*276 */                     s->drq[OMAP_DMA_UART3_TX], s->drq[OMAP_DMA_UART3_RX],         // 0.0
/*278 */                     "uart3",                                                      // 0.0
/*280 */                     serial_hds[0] && serial_hds[1] ? serial_hds[2] : NULL);       // 0.0
/*284 */     s->dpll[0] = omap_dpll_init(system_memory, 0xfffecf00,                        // 0.0
/*286 */                                 omap_findclk(s, "dpll1"));                        // 0.0
/*288 */     s->dpll[1] = omap_dpll_init(system_memory, 0xfffed000,                        // 0.0
/*290 */                                 omap_findclk(s, "dpll2"));                        // 0.0
/*292 */     s->dpll[2] = omap_dpll_init(system_memory, 0xfffed100,                        // 0.0
/*294 */                                 omap_findclk(s, "dpll3"));                        // 0.0
/*298 */     dinfo = drive_get(IF_SD, 0, 0);                                               // 0.0
/*300 */     if (!dinfo) {                                                                 // 0.0
/*302 */         fprintf(stderr, "qemu: missing SecureDigital device\n");                  // 0.0
/*304 */         exit(1);                                                                  // 0.0
/*306 */     }                                                                             // 0.0
/*308 */     s->mmc = omap_mmc_init(0xfffb7800, system_memory,                             // 0.0
/*310 */                            blk_bs(blk_by_legacy_dinfo(dinfo)),                    // 0.0
/*312 */                            qdev_get_gpio_in(s->ih[1], OMAP_INT_OQN),              // 0.0
/*314 */                            &s->drq[OMAP_DMA_MMC_TX],                              // 0.0
/*316 */                     omap_findclk(s, "mmc_ck"));                                   // 0.0
/*320 */     s->mpuio = omap_mpuio_init(system_memory, 0xfffb5000,                         // 0.0
/*322 */                                qdev_get_gpio_in(s->ih[1], OMAP_INT_KEYBOARD),     // 0.0
/*324 */                                qdev_get_gpio_in(s->ih[1], OMAP_INT_MPUIO),        // 0.0
/*326 */                                s->wakeup, omap_findclk(s, "clk32-kHz"));          // 0.0
/*330 */     s->gpio = qdev_create(NULL, "omap-gpio");                                     // 0.0
/*332 */     qdev_prop_set_int32(s->gpio, "mpu_model", s->mpu_model);                      // 0.0
/*334 */     qdev_prop_set_ptr(s->gpio, "clk", omap_findclk(s, "arm_gpio_ck"));            // 0.0
/*336 */     qdev_init_nofail(s->gpio);                                                    // 0.0
/*338 */     sysbus_connect_irq(SYS_BUS_DEVICE(s->gpio), 0,                                // 0.0
/*340 */                        qdev_get_gpio_in(s->ih[0], OMAP_INT_GPIO_BANK1));          // 0.0
/*342 */     sysbus_mmio_map(SYS_BUS_DEVICE(s->gpio), 0, 0xfffce000);                      // 0.0
/*346 */     s->microwire = omap_uwire_init(system_memory, 0xfffb3000,                     // 0.0
/*348 */                                    qdev_get_gpio_in(s->ih[1], OMAP_INT_uWireTX),  // 0.0
/*350 */                                    qdev_get_gpio_in(s->ih[1], OMAP_INT_uWireRX),  // 0.0
/*352 */                     s->drq[OMAP_DMA_UWIRE_TX], omap_findclk(s, "mpuper_ck"));     // 0.0
/*356 */     s->pwl = omap_pwl_init(system_memory, 0xfffb5800,                             // 0.0
/*358 */                            omap_findclk(s, "armxor_ck"));                         // 0.0
/*360 */     s->pwt = omap_pwt_init(system_memory, 0xfffb6000,                             // 0.0
/*362 */                            omap_findclk(s, "armxor_ck"));                         // 0.0
/*366 */     s->i2c[0] = qdev_create(NULL, "omap_i2c");                                    // 0.0
/*368 */     qdev_prop_set_uint8(s->i2c[0], "revision", 0x11);                             // 0.0
/*370 */     qdev_prop_set_ptr(s->i2c[0], "fclk", omap_findclk(s, "mpuper_ck"));           // 0.0
/*372 */     qdev_init_nofail(s->i2c[0]);                                                  // 0.0
/*374 */     busdev = SYS_BUS_DEVICE(s->i2c[0]);                                           // 0.0
/*376 */     sysbus_connect_irq(busdev, 0, qdev_get_gpio_in(s->ih[1], OMAP_INT_I2C));      // 0.0
/*378 */     sysbus_connect_irq(busdev, 1, s->drq[OMAP_DMA_I2C_TX]);                       // 0.0
/*380 */     sysbus_connect_irq(busdev, 2, s->drq[OMAP_DMA_I2C_RX]);                       // 0.0
/*382 */     sysbus_mmio_map(busdev, 0, 0xfffb3800);                                       // 0.0
/*386 */     s->rtc = omap_rtc_init(system_memory, 0xfffb4800,                             // 0.0
/*388 */                            qdev_get_gpio_in(s->ih[1], OMAP_INT_RTC_TIMER),        // 0.0
/*390 */                            qdev_get_gpio_in(s->ih[1], OMAP_INT_RTC_ALARM),        // 0.0
/*392 */                     omap_findclk(s, "clk32-kHz"));                                // 0.0
/*396 */     s->mcbsp1 = omap_mcbsp_init(system_memory, 0xfffb1800,                        // 0.0
/*398 */                                 qdev_get_gpio_in(s->ih[1], OMAP_INT_McBSP1TX),    // 0.0
/*400 */                                 qdev_get_gpio_in(s->ih[1], OMAP_INT_McBSP1RX),    // 0.0
/*402 */                     &s->drq[OMAP_DMA_MCBSP1_TX], omap_findclk(s, "dspxor_ck"));   // 0.0
/*404 */     s->mcbsp2 = omap_mcbsp_init(system_memory, 0xfffb1000,                        // 0.0
/*406 */                                 qdev_get_gpio_in(s->ih[0],                        // 0.0
/*408 */                                                  OMAP_INT_310_McBSP2_TX),         // 0.0
/*410 */                                 qdev_get_gpio_in(s->ih[0],                        // 0.0
/*412 */                                                  OMAP_INT_310_McBSP2_RX),         // 0.0
/*414 */                     &s->drq[OMAP_DMA_MCBSP2_TX], omap_findclk(s, "mpuper_ck"));   // 0.0
/*416 */     s->mcbsp3 = omap_mcbsp_init(system_memory, 0xfffb7000,                        // 0.0
/*418 */                                 qdev_get_gpio_in(s->ih[1], OMAP_INT_McBSP3TX),    // 0.0
/*420 */                                 qdev_get_gpio_in(s->ih[1], OMAP_INT_McBSP3RX),    // 0.0
/*422 */                     &s->drq[OMAP_DMA_MCBSP3_TX], omap_findclk(s, "dspxor_ck"));   // 0.0
/*426 */     s->led[0] = omap_lpg_init(system_memory,                                      // 0.0
/*428 */                               0xfffbd000, omap_findclk(s, "clk32-kHz"));          // 0.0
/*430 */     s->led[1] = omap_lpg_init(system_memory,                                      // 0.0
/*432 */                               0xfffbd800, omap_findclk(s, "clk32-kHz"));          // 0.0
/*436 */     /* Register mappings not currenlty implemented:                               // 0.0
/*438 */      * MCSI2 Comm	fffb2000 - fffb27ff (not mapped on OMAP310)                     // 0.0
/*440 */      * MCSI1 Bluetooth	fffb2800 - fffb2fff (not mapped on OMAP310)                // 0.0
/*442 */      * USB W2FC		fffb4000 - fffb47ff                                              // 0.0
/*444 */      * Camera Interface	fffb6800 - fffb6fff                                       // 0.0
/*446 */      * USB Host		fffba000 - fffba7ff                                              // 0.0
/*448 */      * FAC		fffba800 - fffbafff                                                   // 0.0
/*450 */      * HDQ/1-Wire	fffbc000 - fffbc7ff                                             // 0.0
/*452 */      * TIPB switches	fffbc800 - fffbcfff                                          // 0.0
/*454 */      * Mailbox		fffcf000 - fffcf7ff                                               // 0.0
/*456 */      * Local bus IF	fffec100 - fffec1ff                                           // 0.0
/*458 */      * Local bus MMU	fffec200 - fffec2ff                                          // 0.0
/*460 */      * DSP MMU		fffed200 - fffed2ff                                               // 0.0
/*462 */      */                                                                           // 0.0
/*466 */     omap_setup_dsp_mapping(system_memory, omap15xx_dsp_mm);                       // 0.0
/*468 */     omap_setup_mpui_io(system_memory, s);                                         // 0.0
/*472 */     qemu_register_reset(omap1_mpu_reset, s);                                      // 0.0
/*476 */     return s;                                                                     // 0.0
/*478 */ }                                                                                 // 0.0
