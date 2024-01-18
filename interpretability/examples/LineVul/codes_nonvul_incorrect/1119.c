// commit message qemu@e1f8c729fa (target=0, prob=0.8750463, correct=False): pxa2xx_pic: update to use qdev
/*0   */ PXA2xxState *pxa255_init(unsigned int sdram_size)                                 // (10) 0.03906
/*2   */ {                                                                                 // (19) 0.001953
/*4   */     PXA2xxState *s;                                                               // (12) 0.02344
/*6   */     int iomemtype, i;                                                             // (14) 0.02148
/*8   */     DriveInfo *dinfo;                                                             // (17) 0.01758
/*12  */     s = (PXA2xxState *) qemu_mallocz(sizeof(PXA2xxState));                        // (5) 0.06055
/*16  */     s->env = cpu_init("pxa255");                                                  // (11) 0.0293
/*18  */     if (!s->env) {                                                                // (16) 0.01953
/*20  */         fprintf(stderr, "Unable to find CPU definition\n");                       // (9) 0.04687
/*22  */         exit(1);                                                                  // (15) 0.02148
/*24  */     }                                                                             // (18) 0.007812
/*26  */     s->reset = qemu_allocate_irqs(pxa2xx_reset, s, 1)[0];                         // (6) 0.05859
/*30  */     /* SDRAM & Internal Memory Storage */                                         // (13) 0.02344
/*32  */     cpu_register_physical_memory(PXA2XX_SDRAM_BASE, sdram_size,                   // (7) 0.05664
/*34  */                     qemu_ram_alloc(NULL, "pxa255.sdram",                          // (2) 0.07227
/*36  */                                    sdram_size) | IO_MEM_RAM);                     // (1) 0.0918
/*38  */     cpu_register_physical_memory(PXA2XX_INTERNAL_BASE, PXA2XX_INTERNAL_SIZE,      // (3) 0.07031
/*40  */                     qemu_ram_alloc(NULL, "pxa255.internal",                       // (4) 0.07031
/*42  */                                    PXA2XX_INTERNAL_SIZE) | IO_MEM_RAM);           // (0) 0.1055
/*46  */     s->pic = pxa2xx_pic_init(0x40d00000, s->env);                                 // (8) 0.05078
/*50  */     s->dma = pxa255_dma_init(0x40000000, s->pic[PXA2XX_PIC_DMA]);                 // 0.0
/*54  */     pxa25x_timer_init(0x40a00000, &s->pic[PXA2XX_PIC_OST_0]);                     // 0.0
/*58  */     s->gpio = pxa2xx_gpio_init(0x40e00000, s->env, s->pic, 85);                   // 0.0
/*62  */     dinfo = drive_get(IF_SD, 0, 0);                                               // 0.0
/*64  */     if (!dinfo) {                                                                 // 0.0
/*66  */         fprintf(stderr, "qemu: missing SecureDigital device\n");                  // 0.0
/*68  */         exit(1);                                                                  // 0.0
/*70  */     }                                                                             // 0.0
/*72  */     s->mmc = pxa2xx_mmci_init(0x41100000, dinfo->bdrv,                            // 0.0
/*74  */                               s->pic[PXA2XX_PIC_MMC], s->dma);                    // 0.0
/*78  */     for (i = 0; pxa255_serial[i].io_base; i ++)                                   // 0.0
/*80  */         if (serial_hds[i]) {                                                      // 0.0
/*82  */ #ifdef TARGET_WORDS_BIGENDIAN                                                     // 0.0
/*84  */             serial_mm_init(pxa255_serial[i].io_base, 2,                           // 0.0
/*86  */                            s->pic[pxa255_serial[i].irqn], 14745600/16,            // 0.0
/*88  */                            serial_hds[i], 1, 1);                                  // 0.0
/*90  */ #else                                                                             // 0.0
/*92  */             serial_mm_init(pxa255_serial[i].io_base, 2,                           // 0.0
/*94  */                            s->pic[pxa255_serial[i].irqn], 14745600/16,            // 0.0
/*96  */                            serial_hds[i], 1, 0);                                  // 0.0
/*98  */ #endif                                                                            // 0.0
/*100 */         } else {                                                                  // 0.0
/*102 */             break;                                                                // 0.0
/*104 */         }                                                                         // 0.0
/*106 */     if (serial_hds[i])                                                            // 0.0
/*108 */         s->fir = pxa2xx_fir_init(0x40800000, s->pic[PXA2XX_PIC_ICP],              // 0.0
/*110 */                         s->dma, serial_hds[i]);                                   // 0.0
/*114 */     s->lcd = pxa2xx_lcdc_init(0x44000000, s->pic[PXA2XX_PIC_LCD]);                // 0.0
/*118 */     s->cm_base = 0x41300000;                                                      // 0.0
/*120 */     s->cm_regs[CCCR >> 2] = 0x02000210;	/* 416.0 MHz */                           // 0.0
/*122 */     s->clkcfg = 0x00000009;		/* Turbo mode active */                              // 0.0
/*124 */     iomemtype = cpu_register_io_memory(pxa2xx_cm_readfn,                          // 0.0
/*126 */                     pxa2xx_cm_writefn, s, DEVICE_NATIVE_ENDIAN);                  // 0.0
/*128 */     cpu_register_physical_memory(s->cm_base, 0x1000, iomemtype);                  // 0.0
/*130 */     register_savevm(NULL, "pxa2xx_cm", 0, 0, pxa2xx_cm_save, pxa2xx_cm_load, s);  // 0.0
/*134 */     cpu_arm_set_cp_io(s->env, 14, pxa2xx_cp14_read, pxa2xx_cp14_write, s);        // 0.0
/*138 */     s->mm_base = 0x48000000;                                                      // 0.0
/*140 */     s->mm_regs[MDMRS >> 2] = 0x00020002;                                          // 0.0
/*142 */     s->mm_regs[MDREFR >> 2] = 0x03ca4000;                                         // 0.0
/*144 */     s->mm_regs[MECR >> 2] = 0x00000001;	/* Two PC Card sockets */                 // 0.0
/*146 */     iomemtype = cpu_register_io_memory(pxa2xx_mm_readfn,                          // 0.0
/*148 */                     pxa2xx_mm_writefn, s, DEVICE_NATIVE_ENDIAN);                  // 0.0
/*150 */     cpu_register_physical_memory(s->mm_base, 0x1000, iomemtype);                  // 0.0
/*152 */     register_savevm(NULL, "pxa2xx_mm", 0, 0, pxa2xx_mm_save, pxa2xx_mm_load, s);  // 0.0
/*156 */     s->pm_base = 0x40f00000;                                                      // 0.0
/*158 */     iomemtype = cpu_register_io_memory(pxa2xx_pm_readfn,                          // 0.0
/*160 */                     pxa2xx_pm_writefn, s, DEVICE_NATIVE_ENDIAN);                  // 0.0
/*162 */     cpu_register_physical_memory(s->pm_base, 0x100, iomemtype);                   // 0.0
/*164 */     register_savevm(NULL, "pxa2xx_pm", 0, 0, pxa2xx_pm_save, pxa2xx_pm_load, s);  // 0.0
/*168 */     for (i = 0; pxa255_ssp[i].io_base; i ++);                                     // 0.0
/*170 */     s->ssp = (SSIBus **)qemu_mallocz(sizeof(SSIBus *) * i);                       // 0.0
/*172 */     for (i = 0; pxa255_ssp[i].io_base; i ++) {                                    // 0.0
/*174 */         DeviceState *dev;                                                         // 0.0
/*176 */         dev = sysbus_create_simple("pxa2xx-ssp", pxa255_ssp[i].io_base,           // 0.0
/*178 */                                    s->pic[pxa255_ssp[i].irqn]);                   // 0.0
/*180 */         s->ssp[i] = (SSIBus *)qdev_get_child_bus(dev, "ssi");                     // 0.0
/*182 */     }                                                                             // 0.0
/*186 */     if (usb_enabled) {                                                            // 0.0
/*188 */         sysbus_create_simple("sysbus-ohci", 0x4c000000,                           // 0.0
/*190 */                              s->pic[PXA2XX_PIC_USBH1]);                           // 0.0
/*192 */     }                                                                             // 0.0
/*196 */     s->pcmcia[0] = pxa2xx_pcmcia_init(0x20000000);                                // 0.0
/*198 */     s->pcmcia[1] = pxa2xx_pcmcia_init(0x30000000);                                // 0.0
/*202 */     s->rtc_base = 0x40900000;                                                     // 0.0
/*204 */     iomemtype = cpu_register_io_memory(pxa2xx_rtc_readfn,                         // 0.0
/*206 */                     pxa2xx_rtc_writefn, s, DEVICE_NATIVE_ENDIAN);                 // 0.0
/*208 */     cpu_register_physical_memory(s->rtc_base, 0x1000, iomemtype);                 // 0.0
/*210 */     pxa2xx_rtc_init(s);                                                           // 0.0
/*212 */     register_savevm(NULL, "pxa2xx_rtc", 0, 0, pxa2xx_rtc_save,                    // 0.0
/*214 */                     pxa2xx_rtc_load, s);                                          // 0.0
/*218 */     s->i2c[0] = pxa2xx_i2c_init(0x40301600, s->pic[PXA2XX_PIC_I2C], 0xffff);      // 0.0
/*220 */     s->i2c[1] = pxa2xx_i2c_init(0x40f00100, s->pic[PXA2XX_PIC_PWRI2C], 0xff);     // 0.0
/*224 */     s->i2s = pxa2xx_i2s_init(0x40400000, s->pic[PXA2XX_PIC_I2S], s->dma);         // 0.0
/*228 */     /* GPIO1 resets the processor */                                              // 0.0
/*230 */     /* The handler can be overridden by board-specific code */                    // 0.0
/*232 */     qdev_connect_gpio_out(s->gpio, 1, s->reset);                                  // 0.0
/*234 */     return s;                                                                     // 0.0
/*236 */ }                                                                                 // 0.0
