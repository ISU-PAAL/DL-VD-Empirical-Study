// commit message qemu@e9ebead2b5 (target=1, prob=0.2278386, correct=False): Fix uninitialized variable warning
/*0   */ static void pc_init1(ram_addr_t ram_size, int vga_ram_size,                                // (6) 0.04687
/*2   */                      const char *boot_device, DisplayState *ds,                            // (1) 0.0625
/*4   */                      const char *kernel_filename, const char *kernel_cmdline,              // (0) 0.06835
/*6   */                      const char *initrd_filename,                                          // (5) 0.05468
/*8   */                      int pci_enabled, const char *cpu_model)                               // (2) 0.06249
/*10  */ {                                                                                          // (26) 0.001971
/*12  */     char buf[1024];                                                                        // (20) 0.01562
/*14  */     int ret, linux_boot, i;                                                                // (18) 0.02344
/*16  */     ram_addr_t ram_addr, vga_ram_addr, bios_offset, vga_bios_offset;                       // (3) 0.06054
/*18  */     ram_addr_t below_4g_mem_size, above_4g_mem_size = 0;                                   // (4) 0.05468
/*20  */     int bios_size, isa_bios_size, vga_bios_size;                                           // (8) 0.04687
/*22  */     PCIBus *pci_bus;                                                                       // (19) 0.02344
/*24  */     int piix3_devfn = -1;                                                                  // (15) 0.02734
/*26  */     CPUState *env;                                                                         // (21) 0.01562
/*28  */     qemu_irq *cpu_irq;                                                                     // (12) 0.02929
/*30  */     qemu_irq *i8259;                                                                       // (16) 0.02734
/*32  */     int index;                                                                             // (23) 0.01172
/*34  */     BlockDriverState *hd[MAX_IDE_BUS * MAX_IDE_DEVS];                                      // (9) 0.04297
/*36  */     BlockDriverState *fd[MAX_FD];                                                          // (17) 0.02539
/*40  */     if (ram_size >= 0xe0000000 ) {                                                         // (13) 0.02735
/*42  */         above_4g_mem_size = ram_size - 0xe0000000;                                         // (7) 0.04687
/*44  */         below_4g_mem_size = 0xe0000000;                                                    // (11) 0.03906
/*46  */     } else {                                                                               // (24) 0.01172
/*48  */         below_4g_mem_size = ram_size;                                                      // (10) 0.03906
/*50  */     }                                                                                      // (25) 0.007812
/*54  */     linux_boot = (kernel_filename != NULL);                                                // (14) 0.02735
/*58  */     /* init CPUs */                                                                        // (22) 0.01367
/*60  */     if (cpu_model == NULL) {                                                               // 0.0
/*62  */ #ifdef TARGET_X86_64                                                                       // 0.0
/*64  */         cpu_model = "qemu64";                                                              // 0.0
/*66  */ #else                                                                                      // 0.0
/*68  */         cpu_model = "qemu32";                                                              // 0.0
/*70  */ #endif                                                                                     // 0.0
/*72  */     }                                                                                      // 0.0
/*74  */                                                                                            // 0.0
/*76  */     for(i = 0; i < smp_cpus; i++) {                                                        // 0.0
/*78  */         env = cpu_init(cpu_model);                                                         // 0.0
/*80  */         if (!env) {                                                                        // 0.0
/*82  */             fprintf(stderr, "Unable to find x86 CPU definition\n");                        // 0.0
/*84  */             exit(1);                                                                       // 0.0
/*86  */         }                                                                                  // 0.0
/*88  */         if (i != 0)                                                                        // 0.0
/*90  */             env->halted = 1;                                                               // 0.0
/*92  */         if (smp_cpus > 1) {                                                                // 0.0
/*94  */             /* XXX: enable it in all cases */                                              // 0.0
/*96  */             env->cpuid_features |= CPUID_APIC;                                             // 0.0
/*98  */         }                                                                                  // 0.0
/*100 */         qemu_register_reset(main_cpu_reset, env);                                          // 0.0
/*102 */         if (pci_enabled) {                                                                 // 0.0
/*104 */             apic_init(env);                                                                // 0.0
/*106 */         }                                                                                  // 0.0
/*108 */     }                                                                                      // 0.0
/*112 */     vmport_init();                                                                         // 0.0
/*116 */     /* allocate RAM */                                                                     // 0.0
/*118 */     ram_addr = qemu_ram_alloc(0xa0000);                                                    // 0.0
/*120 */     cpu_register_physical_memory(0, 0xa0000, ram_addr);                                    // 0.0
/*124 */     /* Allocate, even though we won't register, so we don't break the                      // 0.0
/*126 */      * phys_ram_base + PA assumption. This range includes vga (0xa0000 - 0xc0000),         // 0.0
/*128 */      * and some bios areas, which will be registered later                                 // 0.0
/*130 */      */                                                                                    // 0.0
/*132 */     ram_addr = qemu_ram_alloc(0x100000 - 0xa0000);                                         // 0.0
/*134 */     ram_addr = qemu_ram_alloc(below_4g_mem_size - 0x100000);                               // 0.0
/*136 */     cpu_register_physical_memory(0x100000,                                                 // 0.0
/*138 */                  below_4g_mem_size - 0x100000,                                             // 0.0
/*140 */                  ram_addr);                                                                // 0.0
/*144 */     /* above 4giga memory allocation */                                                    // 0.0
/*146 */     if (above_4g_mem_size > 0) {                                                           // 0.0
/*148 */         ram_addr = qemu_ram_alloc(above_4g_mem_size);                                      // 0.0
/*150 */         cpu_register_physical_memory(0x100000000ULL,                                       // 0.0
/*152 */                                      above_4g_mem_size,                                    // 0.0
/*154 */                                      ram_addr);                                            // 0.0
/*156 */     }                                                                                      // 0.0
/*162 */     /* allocate VGA RAM */                                                                 // 0.0
/*164 */     vga_ram_addr = qemu_ram_alloc(vga_ram_size);                                           // 0.0
/*168 */     /* BIOS load */                                                                        // 0.0
/*170 */     if (bios_name == NULL)                                                                 // 0.0
/*172 */         bios_name = BIOS_FILENAME;                                                         // 0.0
/*174 */     snprintf(buf, sizeof(buf), "%s/%s", bios_dir, bios_name);                              // 0.0
/*176 */     bios_size = get_image_size(buf);                                                       // 0.0
/*178 */     if (bios_size <= 0 ||                                                                  // 0.0
/*180 */         (bios_size % 65536) != 0) {                                                        // 0.0
/*182 */         goto bios_error;                                                                   // 0.0
/*184 */     }                                                                                      // 0.0
/*186 */     bios_offset = qemu_ram_alloc(bios_size);                                               // 0.0
/*188 */     ret = load_image(buf, phys_ram_base + bios_offset);                                    // 0.0
/*190 */     if (ret != bios_size) {                                                                // 0.0
/*192 */     bios_error:                                                                            // 0.0
/*194 */         fprintf(stderr, "qemu: could not load PC BIOS '%s'\n", buf);                       // 0.0
/*196 */         exit(1);                                                                           // 0.0
/*198 */     }                                                                                      // 0.0
/*202 */     if (cirrus_vga_enabled || std_vga_enabled || vmsvga_enabled) {                         // 0.0
/*204 */         /* VGA BIOS load */                                                                // 0.0
/*206 */         if (cirrus_vga_enabled) {                                                          // 0.0
/*208 */             snprintf(buf, sizeof(buf), "%s/%s", bios_dir, VGABIOS_CIRRUS_FILENAME);        // 0.0
/*210 */         } else {                                                                           // 0.0
/*212 */             snprintf(buf, sizeof(buf), "%s/%s", bios_dir, VGABIOS_FILENAME);               // 0.0
/*214 */         }                                                                                  // 0.0
/*216 */         vga_bios_size = get_image_size(buf);                                               // 0.0
/*218 */         if (vga_bios_size <= 0 || vga_bios_size > 65536)                                   // 0.0
/*220 */             goto vga_bios_error;                                                           // 0.0
/*222 */         vga_bios_offset = qemu_ram_alloc(65536);                                           // 0.0
/*226 */         ret = load_image(buf, phys_ram_base + vga_bios_offset);                            // 0.0
/*228 */         if (ret != vga_bios_size) {                                                        // 0.0
/*230 */ vga_bios_error:                                                                            // 0.0
/*232 */             fprintf(stderr, "qemu: could not load VGA BIOS '%s'\n", buf);                  // 0.0
/*234 */             exit(1);                                                                       // 0.0
/*236 */         }                                                                                  // 0.0
/*238 */     }                                                                                      // 0.0
/*242 */     /* setup basic memory access */                                                        // 0.0
/*244 */     cpu_register_physical_memory(0xc0000, 0x10000,                                         // 0.0
/*246 */                                  vga_bios_offset | IO_MEM_ROM);                            // 0.0
/*250 */     /* map the last 128KB of the BIOS in ISA space */                                      // 0.0
/*252 */     isa_bios_size = bios_size;                                                             // 0.0
/*254 */     if (isa_bios_size > (128 * 1024))                                                      // 0.0
/*256 */         isa_bios_size = 128 * 1024;                                                        // 0.0
/*258 */     cpu_register_physical_memory(0x100000 - isa_bios_size,                                 // 0.0
/*260 */                                  isa_bios_size,                                            // 0.0
/*262 */                                  (bios_offset + bios_size - isa_bios_size) | IO_MEM_ROM);  // 0.0
/*266 */     {                                                                                      // 0.0
/*268 */         ram_addr_t option_rom_offset;                                                      // 0.0
/*270 */         int size, offset;                                                                  // 0.0
/*274 */         offset = 0;                                                                        // 0.0
/*276 */         if (linux_boot) {                                                                  // 0.0
/*278 */             option_rom_offset = qemu_ram_alloc(TARGET_PAGE_SIZE);                          // 0.0
/*280 */             load_linux(phys_ram_base + option_rom_offset,                                  // 0.0
/*282 */                        kernel_filename, initrd_filename, kernel_cmdline);                  // 0.0
/*284 */             cpu_register_physical_memory(0xd0000, TARGET_PAGE_SIZE,                        // 0.0
/*286 */                                          option_rom_offset | IO_MEM_ROM);                  // 0.0
/*288 */             offset = TARGET_PAGE_SIZE;                                                     // 0.0
/*290 */         }                                                                                  // 0.0
/*294 */         for (i = 0; i < nb_option_roms; i++) {                                             // 0.0
/*296 */             size = get_image_size(option_rom[i]);                                          // 0.0
/*298 */             if (size < 0) {                                                                // 0.0
/*300 */                 fprintf(stderr, "Could not load option rom '%s'\n",                        // 0.0
/*302 */                         option_rom[i]);                                                    // 0.0
/*304 */                 exit(1);                                                                   // 0.0
/*306 */             }                                                                              // 0.0
/*308 */             if (size > (0x10000 - offset))                                                 // 0.0
/*310 */                 goto option_rom_error;                                                     // 0.0
/*312 */             option_rom_offset = qemu_ram_alloc(size);                                      // 0.0
/*314 */             ret = load_image(option_rom[i], phys_ram_base + option_rom_offset);            // 0.0
/*316 */             if (ret != size) {                                                             // 0.0
/*318 */             option_rom_error:                                                              // 0.0
/*320 */                 fprintf(stderr, "Too many option ROMS\n");                                 // 0.0
/*322 */                 exit(1);                                                                   // 0.0
/*324 */             }                                                                              // 0.0
/*326 */             size = (size + 4095) & ~4095;                                                  // 0.0
/*328 */             cpu_register_physical_memory(0xd0000 + offset,                                 // 0.0
/*330 */                                          size, option_rom_offset | IO_MEM_ROM);            // 0.0
/*332 */             offset += size;                                                                // 0.0
/*334 */         }                                                                                  // 0.0
/*336 */     }                                                                                      // 0.0
/*340 */     /* map all the bios at the top of memory */                                            // 0.0
/*342 */     cpu_register_physical_memory((uint32_t)(-bios_size),                                   // 0.0
/*344 */                                  bios_size, bios_offset | IO_MEM_ROM);                     // 0.0
/*348 */     bochs_bios_init();                                                                     // 0.0
/*352 */     cpu_irq = qemu_allocate_irqs(pic_irq_request, NULL, 1);                                // 0.0
/*354 */     i8259 = i8259_init(cpu_irq[0]);                                                        // 0.0
/*356 */     ferr_irq = i8259[13];                                                                  // 0.0
/*360 */     if (pci_enabled) {                                                                     // 0.0
/*362 */         pci_bus = i440fx_init(&i440fx_state, i8259);                                       // 0.0
/*364 */         piix3_devfn = piix3_init(pci_bus, -1);                                             // 0.0
/*366 */     } else {                                                                               // 0.0
/*368 */         pci_bus = NULL;                                                                    // 0.0
/*370 */     }                                                                                      // 0.0
/*374 */     /* init basic PC hardware */                                                           // 0.0
/*376 */     register_ioport_write(0x80, 1, 1, ioport80_write, NULL);                               // 0.0
/*380 */     register_ioport_write(0xf0, 1, 1, ioportF0_write, NULL);                               // 0.0
/*384 */     if (cirrus_vga_enabled) {                                                              // 0.0
/*386 */         if (pci_enabled) {                                                                 // 0.0
/*388 */             pci_cirrus_vga_init(pci_bus,                                                   // 0.0
/*390 */                                 ds, phys_ram_base + vga_ram_addr,                          // 0.0
/*392 */                                 vga_ram_addr, vga_ram_size);                               // 0.0
/*394 */         } else {                                                                           // 0.0
/*396 */             isa_cirrus_vga_init(ds, phys_ram_base + vga_ram_addr,                          // 0.0
/*398 */                                 vga_ram_addr, vga_ram_size);                               // 0.0
/*400 */         }                                                                                  // 0.0
/*402 */     } else if (vmsvga_enabled) {                                                           // 0.0
/*404 */         if (pci_enabled)                                                                   // 0.0
/*406 */             pci_vmsvga_init(pci_bus, ds, phys_ram_base + vga_ram_addr,                     // 0.0
/*408 */                             vga_ram_addr, vga_ram_size);                                   // 0.0
/*410 */         else                                                                               // 0.0
/*412 */             fprintf(stderr, "%s: vmware_vga: no PCI bus\n", __FUNCTION__);                 // 0.0
/*414 */     } else if (std_vga_enabled) {                                                          // 0.0
/*416 */         if (pci_enabled) {                                                                 // 0.0
/*418 */             pci_vga_init(pci_bus, ds, phys_ram_base + vga_ram_addr,                        // 0.0
/*420 */                          vga_ram_addr, vga_ram_size, 0, 0);                                // 0.0
/*422 */         } else {                                                                           // 0.0
/*424 */             isa_vga_init(ds, phys_ram_base + vga_ram_addr,                                 // 0.0
/*426 */                          vga_ram_addr, vga_ram_size);                                      // 0.0
/*428 */         }                                                                                  // 0.0
/*430 */     }                                                                                      // 0.0
/*434 */     rtc_state = rtc_init(0x70, i8259[8]);                                                  // 0.0
/*438 */     qemu_register_boot_set(pc_boot_set, rtc_state);                                        // 0.0
/*442 */     register_ioport_read(0x92, 1, 1, ioport92_read, NULL);                                 // 0.0
/*444 */     register_ioport_write(0x92, 1, 1, ioport92_write, NULL);                               // 0.0
/*448 */     if (pci_enabled) {                                                                     // 0.0
/*450 */         ioapic = ioapic_init();                                                            // 0.0
/*452 */     }                                                                                      // 0.0
/*454 */     pit = pit_init(0x40, i8259[0]);                                                        // 0.0
/*456 */     pcspk_init(pit);                                                                       // 0.0
/*458 */     if (!no_hpet) {                                                                        // 0.0
/*460 */         hpet_init(i8259);                                                                  // 0.0
/*462 */     }                                                                                      // 0.0
/*464 */     if (pci_enabled) {                                                                     // 0.0
/*466 */         pic_set_alt_irq_func(isa_pic, ioapic_set_irq, ioapic);                             // 0.0
/*468 */     }                                                                                      // 0.0
/*472 */     for(i = 0; i < MAX_SERIAL_PORTS; i++) {                                                // 0.0
/*474 */         if (serial_hds[i]) {                                                               // 0.0
/*476 */             serial_init(serial_io[i], i8259[serial_irq[i]], 115200,                        // 0.0
/*478 */                         serial_hds[i]);                                                    // 0.0
/*480 */         }                                                                                  // 0.0
/*482 */     }                                                                                      // 0.0
/*486 */     for(i = 0; i < MAX_PARALLEL_PORTS; i++) {                                              // 0.0
/*488 */         if (parallel_hds[i]) {                                                             // 0.0
/*490 */             parallel_init(parallel_io[i], i8259[parallel_irq[i]],                          // 0.0
/*492 */                           parallel_hds[i]);                                                // 0.0
/*494 */         }                                                                                  // 0.0
/*496 */     }                                                                                      // 0.0
/*500 */     for(i = 0; i < nb_nics; i++) {                                                         // 0.0
/*502 */         NICInfo *nd = &nd_table[i];                                                        // 0.0
/*506 */         if (!pci_enabled || (nd->model && strcmp(nd->model, "ne2k_isa") == 0))             // 0.0
/*508 */             pc_init_ne2k_isa(nd, i8259);                                                   // 0.0
/*510 */         else                                                                               // 0.0
/*512 */             pci_nic_init(pci_bus, nd, -1, "ne2k_pci");                                     // 0.0
/*514 */     }                                                                                      // 0.0
/*518 */     if (drive_get_max_bus(IF_IDE) >= MAX_IDE_BUS) {                                        // 0.0
/*520 */         fprintf(stderr, "qemu: too many IDE bus\n");                                       // 0.0
/*522 */         exit(1);                                                                           // 0.0
/*524 */     }                                                                                      // 0.0
/*528 */     for(i = 0; i < MAX_IDE_BUS * MAX_IDE_DEVS; i++) {                                      // 0.0
/*530 */         index = drive_get_index(IF_IDE, i / MAX_IDE_DEVS, i % MAX_IDE_DEVS);               // 0.0
/*532 */ 	if (index != -1)                                                                          // 0.0
/*534 */ 	    hd[i] = drives_table[index].bdrv;                                                     // 0.0
/*536 */ 	else                                                                                      // 0.0
/*538 */ 	    hd[i] = NULL;                                                                         // 0.0
/*540 */     }                                                                                      // 0.0
/*544 */     if (pci_enabled) {                                                                     // 0.0
/*546 */         pci_piix3_ide_init(pci_bus, hd, piix3_devfn + 1, i8259);                           // 0.0
/*548 */     } else {                                                                               // 0.0
/*550 */         for(i = 0; i < MAX_IDE_BUS; i++) {                                                 // 0.0
/*552 */             isa_ide_init(ide_iobase[i], ide_iobase2[i], i8259[ide_irq[i]],                 // 0.0
/*554 */ 	                 hd[MAX_IDE_DEVS * i], hd[MAX_IDE_DEVS * i + 1]);                         // 0.0
/*556 */         }                                                                                  // 0.0
/*558 */     }                                                                                      // 0.0
/*562 */     i8042_init(i8259[1], i8259[12], 0x60);                                                 // 0.0
/*564 */     DMA_init(0);                                                                           // 0.0
/*566 */ #ifdef HAS_AUDIO                                                                           // 0.0
/*568 */     audio_init(pci_enabled ? pci_bus : NULL, i8259);                                       // 0.0
/*570 */ #endif                                                                                     // 0.0
/*574 */     for(i = 0; i < MAX_FD; i++) {                                                          // 0.0
/*576 */         index = drive_get_index(IF_FLOPPY, 0, i);                                          // 0.0
/*578 */ 	if (index != -1)                                                                          // 0.0
/*580 */ 	    fd[i] = drives_table[index].bdrv;                                                     // 0.0
/*582 */ 	else                                                                                      // 0.0
/*584 */ 	    fd[i] = NULL;                                                                         // 0.0
/*586 */     }                                                                                      // 0.0
/*588 */     floppy_controller = fdctrl_init(i8259[6], 2, 0, 0x3f0, fd);                            // 0.0
/*592 */     cmos_init(below_4g_mem_size, above_4g_mem_size, boot_device, hd);                      // 0.0
/*596 */     if (pci_enabled && usb_enabled) {                                                      // 0.0
/*598 */         usb_uhci_piix3_init(pci_bus, piix3_devfn + 2);                                     // 0.0
/*600 */     }                                                                                      // 0.0
/*604 */     if (pci_enabled && acpi_enabled) {                                                     // 0.0
/*606 */         uint8_t *eeprom_buf = qemu_mallocz(8 * 256); /* XXX: make this persistent */       // 0.0
/*608 */         i2c_bus *smbus;                                                                    // 0.0
/*612 */         /* TODO: Populate SPD eeprom data.  */                                             // 0.0
/*614 */         smbus = piix4_pm_init(pci_bus, piix3_devfn + 3, 0xb100, i8259[9]);                 // 0.0
/*616 */         for (i = 0; i < 8; i++) {                                                          // 0.0
/*618 */             smbus_eeprom_device_init(smbus, 0x50 + i, eeprom_buf + (i * 256));             // 0.0
/*620 */         }                                                                                  // 0.0
/*622 */     }                                                                                      // 0.0
/*626 */     if (i440fx_state) {                                                                    // 0.0
/*628 */         i440fx_init_memory_mappings(i440fx_state);                                         // 0.0
/*630 */     }                                                                                      // 0.0
/*634 */     if (pci_enabled) {                                                                     // 0.0
/*636 */ 	int max_bus;                                                                              // 0.0
/*638 */         int bus, unit;                                                                     // 0.0
/*640 */         void *scsi;                                                                        // 0.0
/*644 */         max_bus = drive_get_max_bus(IF_SCSI);                                              // 0.0
/*648 */ 	for (bus = 0; bus <= max_bus; bus++) {                                                    // 0.0
/*650 */             scsi = lsi_scsi_init(pci_bus, -1);                                             // 0.0
/*652 */             for (unit = 0; unit < LSI_MAX_DEVS; unit++) {                                  // 0.0
/*654 */ 	        index = drive_get_index(IF_SCSI, bus, unit);                                      // 0.0
/*656 */ 		if (index == -1)                                                                         // 0.0
/*658 */ 		    continue;                                                                            // 0.0
/*660 */ 		lsi_scsi_attach(scsi, drives_table[index].bdrv, unit);                                   // 0.0
/*662 */ 	    }                                                                                     // 0.0
/*664 */         }                                                                                  // 0.0
/*666 */     }                                                                                      // 0.0
/*670 */     /* Add virtio block devices */                                                         // 0.0
/*672 */     if (pci_enabled) {                                                                     // 0.0
/*674 */         int index;                                                                         // 0.0
/*676 */         int unit_id = 0;                                                                   // 0.0
/*680 */         while ((index = drive_get_index(IF_VIRTIO, 0, unit_id)) != -1) {                   // 0.0
/*682 */             virtio_blk_init(pci_bus, drives_table[index].bdrv);                            // 0.0
/*684 */             unit_id++;                                                                     // 0.0
/*686 */         }                                                                                  // 0.0
/*688 */     }                                                                                      // 0.0
/*692 */     /* Add virtio balloon device */                                                        // 0.0
/*694 */     if (pci_enabled)                                                                       // 0.0
/*696 */         virtio_balloon_init(pci_bus);                                                      // 0.0
/*700 */     /* Add virtio console devices */                                                       // 0.0
/*702 */     if (pci_enabled) {                                                                     // 0.0
/*704 */         for(i = 0; i < MAX_VIRTIO_CONSOLES; i++) {                                         // 0.0
/*706 */             if (virtcon_hds[i])                                                            // 0.0
/*708 */                 virtio_console_init(pci_bus, virtcon_hds[i]);                              // 0.0
/*710 */         }                                                                                  // 0.0
/*712 */     }                                                                                      // 0.0
/*714 */ }                                                                                          // 0.0
