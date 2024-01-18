// commit message qemu@0ae18ceeaa (target=0, prob=0.16793191, correct=True): Check NIC model in some NIC init functions (Mark McLoughlin)
/*0   */ static void realview_init(ram_addr_t ram_size, int vga_ram_size,                // (5) 0.04687
/*2   */                      const char *boot_device, DisplayState *ds,                 // (2) 0.0625
/*4   */                      const char *kernel_filename, const char *kernel_cmdline,   // (1) 0.06836
/*6   */                      const char *initrd_filename, const char *cpu_model)        // (0) 0.06836
/*8   */ {                                                                               // (30) 0.001957
/*10  */     CPUState *env;                                                              // (23) 0.01562
/*12  */     qemu_irq *pic;                                                              // (15) 0.02344
/*14  */     void *scsi_hba;                                                             // (19) 0.02148
/*16  */     PCIBus *pci_bus;                                                            // (14) 0.02344
/*18  */     NICInfo *nd;                                                                // (22) 0.01562
/*20  */     int n;                                                                      // (27) 0.01172
/*22  */     int done_smc = 0;                                                           // (20) 0.02148
/*24  */     qemu_irq cpu_irq[4];                                                        // (11) 0.03125
/*26  */     int ncpu;                                                                   // (25) 0.01367
/*28  */     int index;                                                                  // (26) 0.01172
/*32  */     if (!cpu_model)                                                             // (21) 0.01758
/*34  */         cpu_model = "arm926";                                                   // (12) 0.03125
/*36  */     /* FIXME: obey smp_cpus.  */                                                // (10) 0.03125
/*38  */     if (strcmp(cpu_model, "arm11mpcore") == 0) {                                // (6) 0.04297
/*40  */         ncpu = 4;                                                               // (16) 0.02344
/*42  */     } else {                                                                    // (28) 0.01172
/*44  */         ncpu = 1;                                                               // (18) 0.02344
/*46  */     }                                                                           // (29) 0.007812
/*50  */     for (n = 0; n < ncpu; n++) {                                                // (9) 0.0332
/*52  */         env = cpu_init(cpu_model);                                              // (8) 0.0332
/*54  */         if (!env) {                                                             // (17) 0.02344
/*56  */             fprintf(stderr, "Unable to find CPU definition\n");                 // (3) 0.05468
/*58  */             exit(1);                                                            // (13) 0.0293
/*60  */         }                                                                       // (24) 0.01562
/*62  */         pic = arm_pic_init_cpu(env);                                            // (7) 0.03711
/*64  */         cpu_irq[n] = pic[ARM_PIC_CPU_IRQ];                                      // (4) 0.05273
/*66  */         if (n > 0) {                                                            // 0.0
/*68  */             /* Set entry point for secondary CPUs.  This assumes we're using    // 0.0
/*70  */                the init code from arm_boot.c.  Real hardware resets all CPUs    // 0.0
/*72  */                the same.  */                                                    // 0.0
/*74  */             env->regs[15] = 0x80000000;                                         // 0.0
/*76  */         }                                                                       // 0.0
/*78  */     }                                                                           // 0.0
/*82  */     /* ??? RAM should repeat to fill physical memory space.  */                 // 0.0
/*84  */     /* SDRAM at address zero.  */                                               // 0.0
/*86  */     cpu_register_physical_memory(0, ram_size, IO_MEM_RAM);                      // 0.0
/*90  */     arm_sysctl_init(0x10000000, 0xc1400400);                                    // 0.0
/*94  */     if (ncpu == 1) {                                                            // 0.0
/*96  */         /* ??? The documentation says GIC1 is nFIQ and either GIC2 or GIC3      // 0.0
/*98  */            is nIRQ (there are inconsistencies).  However Linux 2.6.17 expects   // 0.0
/*100 */            GIC1 to be nIRQ and ignores all the others, so do that for now.  */  // 0.0
/*102 */         pic = realview_gic_init(0x10040000, cpu_irq[0]);                        // 0.0
/*104 */     } else {                                                                    // 0.0
/*106 */         pic = mpcore_irq_init(cpu_irq);                                         // 0.0
/*108 */     }                                                                           // 0.0
/*112 */     pl050_init(0x10006000, pic[20], 0);                                         // 0.0
/*114 */     pl050_init(0x10007000, pic[21], 1);                                         // 0.0
/*118 */     pl011_init(0x10009000, pic[12], serial_hds[0], PL011_ARM);                  // 0.0
/*120 */     pl011_init(0x1000a000, pic[13], serial_hds[1], PL011_ARM);                  // 0.0
/*122 */     pl011_init(0x1000b000, pic[14], serial_hds[2], PL011_ARM);                  // 0.0
/*124 */     pl011_init(0x1000c000, pic[15], serial_hds[3], PL011_ARM);                  // 0.0
/*128 */     /* DMA controller is optional, apparently.  */                              // 0.0
/*130 */     pl080_init(0x10030000, pic[24], 2);                                         // 0.0
/*134 */     sp804_init(0x10011000, pic[4]);                                             // 0.0
/*136 */     sp804_init(0x10012000, pic[5]);                                             // 0.0
/*140 */     pl110_init(ds, 0x10020000, pic[23], 1);                                     // 0.0
/*144 */     index = drive_get_index(IF_SD, 0, 0);                                       // 0.0
/*146 */     if (index == -1) {                                                          // 0.0
/*148 */         fprintf(stderr, "qemu: missing SecureDigital card\n");                  // 0.0
/*150 */         exit(1);                                                                // 0.0
/*152 */     }                                                                           // 0.0
/*154 */     pl181_init(0x10005000, drives_table[index].bdrv, pic[17], pic[18]);         // 0.0
/*158 */     pl031_init(0x10017000, pic[10]);                                            // 0.0
/*162 */     pci_bus = pci_vpb_init(pic, 48, 1);                                         // 0.0
/*164 */     if (usb_enabled) {                                                          // 0.0
/*166 */         usb_ohci_init_pci(pci_bus, 3, -1);                                      // 0.0
/*168 */     }                                                                           // 0.0
/*170 */     if (drive_get_max_bus(IF_SCSI) > 0) {                                       // 0.0
/*172 */         fprintf(stderr, "qemu: too many SCSI bus\n");                           // 0.0
/*174 */         exit(1);                                                                // 0.0
/*176 */     }                                                                           // 0.0
/*178 */     scsi_hba = lsi_scsi_init(pci_bus, -1);                                      // 0.0
/*180 */     for (n = 0; n < LSI_MAX_DEVS; n++) {                                        // 0.0
/*182 */         index = drive_get_index(IF_SCSI, 0, n);                                 // 0.0
/*184 */         if (index == -1)                                                        // 0.0
/*186 */             continue;                                                           // 0.0
/*188 */         lsi_scsi_attach(scsi_hba, drives_table[index].bdrv, n);                 // 0.0
/*190 */     }                                                                           // 0.0
/*192 */     for(n = 0; n < nb_nics; n++) {                                              // 0.0
/*194 */         nd = &nd_table[n];                                                      // 0.0
/*196 */         if (!nd->model)                                                         // 0.0
/*198 */             nd->model = done_smc ? "rtl8139" : "smc91c111";                     // 0.0
/*200 */         if (strcmp(nd->model, "smc91c111") == 0) {                              // 0.0
/*202 */             smc91c111_init(nd, 0x4e000000, pic[28]);                            // 0.0
/*204 */         } else {                                                                // 0.0
/*206 */             pci_nic_init(pci_bus, nd, -1);                                      // 0.0
/*208 */         }                                                                       // 0.0
/*210 */     }                                                                           // 0.0
/*214 */     /* Memory map for RealView Emulation Baseboard:  */                         // 0.0
/*216 */     /* 0x10000000 System registers.  */                                         // 0.0
/*218 */     /*  0x10001000 System controller.  */                                       // 0.0
/*220 */     /*  0x10002000 Two-Wire Serial Bus.  */                                     // 0.0
/*222 */     /* 0x10003000 Reserved.  */                                                 // 0.0
/*224 */     /*  0x10004000 AACI.  */                                                    // 0.0
/*226 */     /*  0x10005000 MCI.  */                                                     // 0.0
/*228 */     /* 0x10006000 KMI0.  */                                                     // 0.0
/*230 */     /* 0x10007000 KMI1.  */                                                     // 0.0
/*232 */     /*  0x10008000 Character LCD.  */                                           // 0.0
/*234 */     /* 0x10009000 UART0.  */                                                    // 0.0
/*236 */     /* 0x1000a000 UART1.  */                                                    // 0.0
/*238 */     /* 0x1000b000 UART2.  */                                                    // 0.0
/*240 */     /* 0x1000c000 UART3.  */                                                    // 0.0
/*242 */     /*  0x1000d000 SSPI.  */                                                    // 0.0
/*244 */     /*  0x1000e000 SCI.  */                                                     // 0.0
/*246 */     /* 0x1000f000 Reserved.  */                                                 // 0.0
/*248 */     /*  0x10010000 Watchdog.  */                                                // 0.0
/*250 */     /* 0x10011000 Timer 0+1.  */                                                // 0.0
/*252 */     /* 0x10012000 Timer 2+3.  */                                                // 0.0
/*254 */     /*  0x10013000 GPIO 0.  */                                                  // 0.0
/*256 */     /*  0x10014000 GPIO 1.  */                                                  // 0.0
/*258 */     /*  0x10015000 GPIO 2.  */                                                  // 0.0
/*260 */     /* 0x10016000 Reserved.  */                                                 // 0.0
/*262 */     /* 0x10017000 RTC.  */                                                      // 0.0
/*264 */     /*  0x10018000 DMC.  */                                                     // 0.0
/*266 */     /*  0x10019000 PCI controller config.  */                                   // 0.0
/*268 */     /*  0x10020000 CLCD.  */                                                    // 0.0
/*270 */     /* 0x10030000 DMA Controller.  */                                           // 0.0
/*272 */     /* 0x10040000 GIC1.  */                                                     // 0.0
/*274 */     /* 0x10050000 GIC2.  */                                                     // 0.0
/*276 */     /* 0x10060000 GIC3.  */                                                     // 0.0
/*278 */     /* 0x10070000 GIC4.  */                                                     // 0.0
/*280 */     /*  0x10080000 SMC.  */                                                     // 0.0
/*282 */     /*  0x40000000 NOR flash.  */                                               // 0.0
/*284 */     /*  0x44000000 DoC flash.  */                                               // 0.0
/*286 */     /*  0x48000000 SRAM.  */                                                    // 0.0
/*288 */     /*  0x4c000000 Configuration flash.  */                                     // 0.0
/*290 */     /* 0x4e000000 Ethernet.  */                                                 // 0.0
/*292 */     /*  0x4f000000 USB.  */                                                     // 0.0
/*294 */     /*  0x50000000 PISMO.  */                                                   // 0.0
/*296 */     /*  0x54000000 PISMO.  */                                                   // 0.0
/*298 */     /*  0x58000000 PISMO.  */                                                   // 0.0
/*300 */     /*  0x5c000000 PISMO.  */                                                   // 0.0
/*302 */     /* 0x60000000 PCI.  */                                                      // 0.0
/*304 */     /* 0x61000000 PCI Self Config.  */                                          // 0.0
/*306 */     /* 0x62000000 PCI Config.  */                                               // 0.0
/*308 */     /* 0x63000000 PCI IO.  */                                                   // 0.0
/*310 */     /* 0x64000000 PCI mem 0.  */                                                // 0.0
/*312 */     /* 0x68000000 PCI mem 1.  */                                                // 0.0
/*314 */     /* 0x6c000000 PCI mem 2.  */                                                // 0.0
/*318 */     realview_binfo.ram_size = ram_size;                                         // 0.0
/*320 */     realview_binfo.kernel_filename = kernel_filename;                           // 0.0
/*322 */     realview_binfo.kernel_cmdline = kernel_cmdline;                             // 0.0
/*324 */     realview_binfo.initrd_filename = initrd_filename;                           // 0.0
/*326 */     realview_binfo.nb_cpus = ncpu;                                              // 0.0
/*328 */     arm_load_kernel(first_cpu, &realview_binfo);                                // 0.0
/*332 */     /* ??? Hack to map an additional page of ram for the secondary CPU          // 0.0
/*334 */        startup code.  I guess this works on real hardware because the           // 0.0
/*336 */        BootROM happens to be in ROM/flash or in memory that isn't clobbered     // 0.0
/*338 */        until after Linux boots the secondary CPUs.  */                          // 0.0
/*340 */     cpu_register_physical_memory(0x80000000, 0x1000, IO_MEM_RAM + ram_size);    // 0.0
/*342 */ }                                                                               // 0.0
