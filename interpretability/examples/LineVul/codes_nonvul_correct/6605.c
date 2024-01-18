// commit message qemu@64d7e9a421 (target=0, prob=0.32705903, correct=True): i8254: convert to qdev
/*0   */ static void ppc_prep_init (ram_addr_t ram_size,                                  // (8) 0.03516
/*2   */                            const char *boot_device,                              // (3) 0.06444
/*4   */                            const char *kernel_filename,                          // (4) 0.06444
/*6   */                            const char *kernel_cmdline,                           // (1) 0.06639
/*8   */                            const char *initrd_filename,                          // (0) 0.06639
/*10  */                            const char *cpu_model)                                // (2) 0.06445
/*12  */ {                                                                                // (26) 0.001976
/*14  */     CPUState *env = NULL;                                                        // (23) 0.01953
/*16  */     char *filename;                                                              // (25) 0.01367
/*18  */     nvram_t nvram;                                                               // (17) 0.02344
/*20  */     M48t59State *m48t59;                                                         // (12) 0.02734
/*22  */     int PPC_io_memory;                                                           // (20) 0.02149
/*24  */     int linux_boot, i, nb_nics1, bios_size;                                      // (6) 0.04102
/*26  */     ram_addr_t ram_offset, bios_offset;                                          // (10) 0.03125
/*28  */     uint32_t kernel_base, initrd_base;                                           // (11) 0.03125
/*30  */     long kernel_size, initrd_size;                                               // (16) 0.02539
/*32  */     PCIBus *pci_bus;                                                             // (19) 0.02343
/*34  */     qemu_irq *i8259;                                                             // (14) 0.02734
/*36  */     qemu_irq *cpu_exit_irq;                                                      // (9) 0.0332
/*38  */     int ppc_boot_device;                                                         // (21) 0.02148
/*40  */     DriveInfo *hd[MAX_IDE_BUS * MAX_IDE_DEVS];                                   // (7) 0.04101
/*42  */     DriveInfo *fd[MAX_FD];                                                       // (18) 0.02344
/*46  */     sysctrl = qemu_mallocz(sizeof(sysctrl_t));                                   // (5) 0.04296
/*50  */     linux_boot = (kernel_filename != NULL);                                      // (13) 0.02734
/*54  */     /* init CPUs */                                                              // (24) 0.01367
/*56  */     if (cpu_model == NULL)                                                       // (22) 0.02148
/*58  */         cpu_model = "602";                                                       // (15) 0.02734
/*60  */     for (i = 0; i < smp_cpus; i++) {                                             // 0.0
/*62  */         env = cpu_init(cpu_model);                                               // 0.0
/*64  */         if (!env) {                                                              // 0.0
/*66  */             fprintf(stderr, "Unable to find PowerPC CPU definition\n");          // 0.0
/*68  */             exit(1);                                                             // 0.0
/*70  */         }                                                                        // 0.0
/*72  */         if (env->flags & POWERPC_FLAG_RTC_CLK) {                                 // 0.0
/*74  */             /* POWER / PowerPC 601 RTC clock frequency is 7.8125 MHz */          // 0.0
/*76  */             cpu_ppc_tb_init(env, 7812500UL);                                     // 0.0
/*78  */         } else {                                                                 // 0.0
/*80  */             /* Set time-base frequency to 100 Mhz */                             // 0.0
/*82  */             cpu_ppc_tb_init(env, 100UL * 1000UL * 1000UL);                       // 0.0
/*84  */         }                                                                        // 0.0
/*86  */         qemu_register_reset((QEMUResetHandler*)&cpu_reset, env);                 // 0.0
/*88  */     }                                                                            // 0.0
/*92  */     /* allocate RAM */                                                           // 0.0
/*94  */     ram_offset = qemu_ram_alloc(NULL, "ppc_prep.ram", ram_size);                 // 0.0
/*96  */     cpu_register_physical_memory(0, ram_size, ram_offset);                       // 0.0
/*100 */     /* allocate and load BIOS */                                                 // 0.0
/*102 */     bios_offset = qemu_ram_alloc(NULL, "ppc_prep.bios", BIOS_SIZE);              // 0.0
/*104 */     if (bios_name == NULL)                                                       // 0.0
/*106 */         bios_name = BIOS_FILENAME;                                               // 0.0
/*108 */     filename = qemu_find_file(QEMU_FILE_TYPE_BIOS, bios_name);                   // 0.0
/*110 */     if (filename) {                                                              // 0.0
/*112 */         bios_size = get_image_size(filename);                                    // 0.0
/*114 */     } else {                                                                     // 0.0
/*116 */         bios_size = -1;                                                          // 0.0
/*118 */     }                                                                            // 0.0
/*120 */     if (bios_size > 0 && bios_size <= BIOS_SIZE) {                               // 0.0
/*122 */         target_phys_addr_t bios_addr;                                            // 0.0
/*124 */         bios_size = (bios_size + 0xfff) & ~0xfff;                                // 0.0
/*126 */         bios_addr = (uint32_t)(-bios_size);                                      // 0.0
/*128 */         cpu_register_physical_memory(bios_addr, bios_size,                       // 0.0
/*130 */                                      bios_offset | IO_MEM_ROM);                  // 0.0
/*132 */         bios_size = load_image_targphys(filename, bios_addr, bios_size);         // 0.0
/*134 */     }                                                                            // 0.0
/*136 */     if (bios_size < 0 || bios_size > BIOS_SIZE) {                                // 0.0
/*138 */         hw_error("qemu: could not load PPC PREP bios '%s'\n", bios_name);        // 0.0
/*140 */     }                                                                            // 0.0
/*142 */     if (filename) {                                                              // 0.0
/*144 */         qemu_free(filename);                                                     // 0.0
/*146 */     }                                                                            // 0.0
/*150 */     if (linux_boot) {                                                            // 0.0
/*152 */         kernel_base = KERNEL_LOAD_ADDR;                                          // 0.0
/*154 */         /* now we can load the kernel */                                         // 0.0
/*156 */         kernel_size = load_image_targphys(kernel_filename, kernel_base,          // 0.0
/*158 */                                           ram_size - kernel_base);               // 0.0
/*160 */         if (kernel_size < 0) {                                                   // 0.0
/*162 */             hw_error("qemu: could not load kernel '%s'\n", kernel_filename);     // 0.0
/*164 */             exit(1);                                                             // 0.0
/*166 */         }                                                                        // 0.0
/*168 */         /* load initrd */                                                        // 0.0
/*170 */         if (initrd_filename) {                                                   // 0.0
/*172 */             initrd_base = INITRD_LOAD_ADDR;                                      // 0.0
/*174 */             initrd_size = load_image_targphys(initrd_filename, initrd_base,      // 0.0
/*176 */                                               ram_size - initrd_base);           // 0.0
/*178 */             if (initrd_size < 0) {                                               // 0.0
/*180 */                 hw_error("qemu: could not load initial ram disk '%s'\n",         // 0.0
/*182 */                           initrd_filename);                                      // 0.0
/*184 */             }                                                                    // 0.0
/*186 */         } else {                                                                 // 0.0
/*188 */             initrd_base = 0;                                                     // 0.0
/*190 */             initrd_size = 0;                                                     // 0.0
/*192 */         }                                                                        // 0.0
/*194 */         ppc_boot_device = 'm';                                                   // 0.0
/*196 */     } else {                                                                     // 0.0
/*198 */         kernel_base = 0;                                                         // 0.0
/*200 */         kernel_size = 0;                                                         // 0.0
/*202 */         initrd_base = 0;                                                         // 0.0
/*204 */         initrd_size = 0;                                                         // 0.0
/*206 */         ppc_boot_device = '\0';                                                  // 0.0
/*208 */         /* For now, OHW cannot boot from the network. */                         // 0.0
/*210 */         for (i = 0; boot_device[i] != '\0'; i++) {                               // 0.0
/*212 */             if (boot_device[i] >= 'a' && boot_device[i] <= 'f') {                // 0.0
/*214 */                 ppc_boot_device = boot_device[i];                                // 0.0
/*216 */                 break;                                                           // 0.0
/*218 */             }                                                                    // 0.0
/*220 */         }                                                                        // 0.0
/*222 */         if (ppc_boot_device == '\0') {                                           // 0.0
/*224 */             fprintf(stderr, "No valid boot device for Mac99 machine\n");         // 0.0
/*226 */             exit(1);                                                             // 0.0
/*228 */         }                                                                        // 0.0
/*230 */     }                                                                            // 0.0
/*234 */     isa_mem_base = 0xc0000000;                                                   // 0.0
/*236 */     if (PPC_INPUT(env) != PPC_FLAGS_INPUT_6xx) {                                 // 0.0
/*238 */         hw_error("Only 6xx bus is supported on PREP machine\n");                 // 0.0
/*240 */     }                                                                            // 0.0
/*242 */     i8259 = i8259_init(first_cpu->irq_inputs[PPC6xx_INPUT_INT]);                 // 0.0
/*244 */     pci_bus = pci_prep_init(i8259);                                              // 0.0
/*246 */     /* Hmm, prep has no pci-isa bridge ??? */                                    // 0.0
/*248 */     isa_bus_new(NULL);                                                           // 0.0
/*250 */     isa_bus_irqs(i8259);                                                         // 0.0
/*252 */     //    pci_bus = i440fx_init();                                               // 0.0
/*254 */     /* Register 8 MB of ISA IO space (needed for non-contiguous map) */          // 0.0
/*256 */     PPC_io_memory = cpu_register_io_memory(PPC_prep_io_read,                     // 0.0
/*258 */                                            PPC_prep_io_write, sysctrl,           // 0.0
/*260 */                                            DEVICE_LITTLE_ENDIAN);                // 0.0
/*262 */     cpu_register_physical_memory(0x80000000, 0x00800000, PPC_io_memory);         // 0.0
/*266 */     /* init basic PC hardware */                                                 // 0.0
/*268 */     pci_vga_init(pci_bus);                                                       // 0.0
/*270 */     //    openpic = openpic_init(0x00000000, 0xF0000000, 1);                     // 0.0
/*272 */     //    pit = pit_init(0x40, i8259[0]);                                        // 0.0
/*274 */     rtc_init(2000, NULL);                                                        // 0.0
/*278 */     if (serial_hds[0])                                                           // 0.0
/*280 */         serial_isa_init(0, serial_hds[0]);                                       // 0.0
/*282 */     nb_nics1 = nb_nics;                                                          // 0.0
/*284 */     if (nb_nics1 > NE2000_NB_MAX)                                                // 0.0
/*286 */         nb_nics1 = NE2000_NB_MAX;                                                // 0.0
/*288 */     for(i = 0; i < nb_nics1; i++) {                                              // 0.0
/*290 */         if (nd_table[i].model == NULL) {                                         // 0.0
/*292 */ 	    nd_table[i].model = qemu_strdup("ne2k_isa");                                // 0.0
/*294 */         }                                                                        // 0.0
/*296 */         if (strcmp(nd_table[i].model, "ne2k_isa") == 0) {                        // 0.0
/*298 */             isa_ne2000_init(ne2000_io[i], ne2000_irq[i], &nd_table[i]);          // 0.0
/*300 */         } else {                                                                 // 0.0
/*302 */             pci_nic_init_nofail(&nd_table[i], "ne2k_pci", NULL);                 // 0.0
/*304 */         }                                                                        // 0.0
/*306 */     }                                                                            // 0.0
/*310 */     if (drive_get_max_bus(IF_IDE) >= MAX_IDE_BUS) {                              // 0.0
/*312 */         fprintf(stderr, "qemu: too many IDE bus\n");                             // 0.0
/*314 */         exit(1);                                                                 // 0.0
/*316 */     }                                                                            // 0.0
/*320 */     for(i = 0; i < MAX_IDE_BUS * MAX_IDE_DEVS; i++) {                            // 0.0
/*322 */         hd[i] = drive_get(IF_IDE, i / MAX_IDE_DEVS, i % MAX_IDE_DEVS);           // 0.0
/*324 */     }                                                                            // 0.0
/*328 */     for(i = 0; i < 1/*MAX_IDE_BUS*/; i++) {                                      // 0.0
/*330 */         isa_ide_init(ide_iobase[i], ide_iobase2[i], ide_irq[i],                  // 0.0
/*332 */                      hd[2 * i],                                                  // 0.0
/*334 */ 		     hd[2 * i + 1]);                                                           // 0.0
/*336 */     }                                                                            // 0.0
/*338 */     isa_create_simple("i8042");                                                  // 0.0
/*342 */     cpu_exit_irq = qemu_allocate_irqs(cpu_request_exit, NULL, 1);                // 0.0
/*344 */     DMA_init(1, cpu_exit_irq);                                                   // 0.0
/*348 */     //    SB16_init();                                                           // 0.0
/*352 */     for(i = 0; i < MAX_FD; i++) {                                                // 0.0
/*354 */         fd[i] = drive_get(IF_FLOPPY, 0, i);                                      // 0.0
/*356 */     }                                                                            // 0.0
/*358 */     fdctrl_init_isa(fd);                                                         // 0.0
/*362 */     /* Register speaker port */                                                  // 0.0
/*364 */     register_ioport_read(0x61, 1, 1, speaker_ioport_read, NULL);                 // 0.0
/*366 */     register_ioport_write(0x61, 1, 1, speaker_ioport_write, NULL);               // 0.0
/*368 */     /* Register fake IO ports for PREP */                                        // 0.0
/*370 */     sysctrl->reset_irq = first_cpu->irq_inputs[PPC6xx_INPUT_HRESET];             // 0.0
/*372 */     register_ioport_read(0x398, 2, 1, &PREP_io_read, sysctrl);                   // 0.0
/*374 */     register_ioport_write(0x398, 2, 1, &PREP_io_write, sysctrl);                 // 0.0
/*376 */     /* System control ports */                                                   // 0.0
/*378 */     register_ioport_read(0x0092, 0x01, 1, &PREP_io_800_readb, sysctrl);          // 0.0
/*380 */     register_ioport_write(0x0092, 0x01, 1, &PREP_io_800_writeb, sysctrl);        // 0.0
/*382 */     register_ioport_read(0x0800, 0x52, 1, &PREP_io_800_readb, sysctrl);          // 0.0
/*384 */     register_ioport_write(0x0800, 0x52, 1, &PREP_io_800_writeb, sysctrl);        // 0.0
/*386 */     /* PCI intack location */                                                    // 0.0
/*388 */     PPC_io_memory = cpu_register_io_memory(PPC_intack_read,                      // 0.0
/*390 */                                            PPC_intack_write, NULL,               // 0.0
/*392 */                                            DEVICE_LITTLE_ENDIAN);                // 0.0
/*394 */     cpu_register_physical_memory(0xBFFFFFF0, 0x4, PPC_io_memory);                // 0.0
/*396 */     /* PowerPC control and status register group */                              // 0.0
/*398 */ #if 0                                                                            // 0.0
/*400 */     PPC_io_memory = cpu_register_io_memory(PPC_XCSR_read, PPC_XCSR_write,        // 0.0
/*402 */                                            NULL, DEVICE_LITTLE_ENDIAN);          // 0.0
/*404 */     cpu_register_physical_memory(0xFEFF0000, 0x1000, PPC_io_memory);             // 0.0
/*406 */ #endif                                                                           // 0.0
/*410 */     if (usb_enabled) {                                                           // 0.0
/*412 */         usb_ohci_init_pci(pci_bus, -1);                                          // 0.0
/*414 */     }                                                                            // 0.0
/*418 */     m48t59 = m48t59_init(i8259[8], 0, 0x0074, NVRAM_SIZE, 59);                   // 0.0
/*420 */     if (m48t59 == NULL)                                                          // 0.0
/*422 */         return;                                                                  // 0.0
/*424 */     sysctrl->nvram = m48t59;                                                     // 0.0
/*428 */     /* Initialise NVRAM */                                                       // 0.0
/*430 */     nvram.opaque = m48t59;                                                       // 0.0
/*432 */     nvram.read_fn = &m48t59_read;                                                // 0.0
/*434 */     nvram.write_fn = &m48t59_write;                                              // 0.0
/*436 */     PPC_NVRAM_set_params(&nvram, NVRAM_SIZE, "PREP", ram_size, ppc_boot_device,  // 0.0
/*438 */                          kernel_base, kernel_size,                               // 0.0
/*440 */                          kernel_cmdline,                                         // 0.0
/*442 */                          initrd_base, initrd_size,                               // 0.0
/*444 */                          /* XXX: need an option to load a NVRAM image */         // 0.0
/*446 */                          0,                                                      // 0.0
/*448 */                          graphic_width, graphic_height, graphic_depth);          // 0.0
/*452 */     /* Special port to get debug messages from Open-Firmware */                  // 0.0
/*454 */     register_ioport_write(0x0F00, 4, 1, &PPC_debug_write, NULL);                 // 0.0
/*456 */ }                                                                                // 0.0
