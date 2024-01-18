// commit message qemu@093209cd68 (target=0, prob=0.33021542, correct=True): Check for errors during BIOS or kernel load
/*0   */ static void ppc_core99_init (ram_addr_t ram_size,                                     // (9) 0.03709
/*2   */                              const char *boot_device,                                 // (2) 0.0683
/*4   */                              const char *kernel_filename,                             // (4) 0.06775
/*6   */                              const char *kernel_cmdline,                              // (0) 0.06969
/*8   */                              const char *initrd_filename,                             // (1) 0.06969
/*10  */                              const char *cpu_model)                                   // (3) 0.06789
/*12  */ {                                                                                     // (25) 0.001972
/*14  */     CPUState *env = NULL, *envs[MAX_CPUS];                                            // (10) 0.03699
/*16  */     char *filename;                                                                   // (24) 0.01356
/*18  */     qemu_irq *pic, **openpic_irqs;                                                    // (11) 0.0369
/*20  */     int unin_memory;                                                                  // (23) 0.01553
/*22  */     int linux_boot, i;                                                                // (19) 0.01969
/*24  */     ram_addr_t ram_offset, bios_offset, vga_bios_offset;                              // (7) 0.04654
/*26  */     uint32_t kernel_base, kernel_size, initrd_base, initrd_size;                      // (6) 0.04845
/*28  */     PCIBus *pci_bus;                                                                  // (16) 0.0233
/*30  */     MacIONVRAMState *nvr;                                                             // (17) 0.02329
/*32  */     int nvram_mem_index;                                                              // (18) 0.02325
/*34  */     int vga_bios_size, bios_size;                                                     // (13) 0.031
/*36  */     int pic_mem_index, dbdma_mem_index, cuda_mem_index, escc_mem_index;               // (5) 0.06212
/*38  */     int ide_mem_index[3];                                                             // (15) 0.02344
/*40  */     int ppc_boot_device;                                                              // (14) 0.02511
/*42  */     DriveInfo *hd[MAX_IDE_BUS * MAX_IDE_DEVS];                                        // (8) 0.0414
/*44  */     void *fw_cfg;                                                                     // (20) 0.01749
/*46  */     void *dbdma;                                                                      // (21) 0.01747
/*48  */     uint8_t *vga_bios_ptr;                                                            // (12) 0.03109
/*50  */     int machine_arch;                                                                 // (22) 0.01642
/*54  */     linux_boot = (kernel_filename != NULL);                                           // 0.0
/*58  */     /* init CPUs */                                                                   // 0.0
/*60  */     if (cpu_model == NULL)                                                            // 0.0
/*62  */ #ifdef TARGET_PPC64                                                                   // 0.0
/*64  */         cpu_model = "970fx";                                                          // 0.0
/*66  */ #else                                                                                 // 0.0
/*68  */         cpu_model = "G4";                                                             // 0.0
/*70  */ #endif                                                                                // 0.0
/*72  */     for (i = 0; i < smp_cpus; i++) {                                                  // 0.0
/*74  */         env = cpu_init(cpu_model);                                                    // 0.0
/*76  */         if (!env) {                                                                   // 0.0
/*78  */             fprintf(stderr, "Unable to find PowerPC CPU definition\n");               // 0.0
/*80  */             exit(1);                                                                  // 0.0
/*82  */         }                                                                             // 0.0
/*84  */         /* Set time-base frequency to 100 Mhz */                                      // 0.0
/*86  */         cpu_ppc_tb_init(env, 100UL * 1000UL * 1000UL);                                // 0.0
/*88  */ #if 0                                                                                 // 0.0
/*90  */         env->osi_call = vga_osi_call;                                                 // 0.0
/*92  */ #endif                                                                                // 0.0
/*94  */         qemu_register_reset((QEMUResetHandler*)&cpu_reset, env);                      // 0.0
/*96  */         envs[i] = env;                                                                // 0.0
/*98  */     }                                                                                 // 0.0
/*102 */     /* allocate RAM */                                                                // 0.0
/*104 */     ram_offset = qemu_ram_alloc(NULL, "ppc_core99.ram", ram_size);                    // 0.0
/*106 */     cpu_register_physical_memory(0, ram_size, ram_offset);                            // 0.0
/*110 */     /* allocate and load BIOS */                                                      // 0.0
/*112 */     bios_offset = qemu_ram_alloc(NULL, "ppc_core99.bios", BIOS_SIZE);                 // 0.0
/*114 */     if (bios_name == NULL)                                                            // 0.0
/*116 */         bios_name = PROM_FILENAME;                                                    // 0.0
/*118 */     filename = qemu_find_file(QEMU_FILE_TYPE_BIOS, bios_name);                        // 0.0
/*120 */     cpu_register_physical_memory(PROM_ADDR, BIOS_SIZE, bios_offset | IO_MEM_ROM);     // 0.0
/*124 */     /* Load OpenBIOS (ELF) */                                                         // 0.0
/*126 */     if (filename) {                                                                   // 0.0
/*128 */         bios_size = load_elf(filename, NULL, NULL, NULL,                              // 0.0
/*130 */                              NULL, NULL, 1, ELF_MACHINE, 0);                          // 0.0
/*134 */         qemu_free(filename);                                                          // 0.0
/*136 */     } else {                                                                          // 0.0
/*138 */         bios_size = -1;                                                               // 0.0
/*140 */     }                                                                                 // 0.0
/*142 */     if (bios_size < 0 || bios_size > BIOS_SIZE) {                                     // 0.0
/*144 */         hw_error("qemu: could not load PowerPC bios '%s'\n", bios_name);              // 0.0
/*146 */         exit(1);                                                                      // 0.0
/*148 */     }                                                                                 // 0.0
/*152 */     /* allocate and load VGA BIOS */                                                  // 0.0
/*154 */     vga_bios_offset = qemu_ram_alloc(NULL, "ppc_core99.vbios", VGA_BIOS_SIZE);        // 0.0
/*156 */     vga_bios_ptr = qemu_get_ram_ptr(vga_bios_offset);                                 // 0.0
/*158 */     filename = qemu_find_file(QEMU_FILE_TYPE_BIOS, VGABIOS_FILENAME);                 // 0.0
/*160 */     if (filename) {                                                                   // 0.0
/*162 */         vga_bios_size = load_image(filename, vga_bios_ptr + 8);                       // 0.0
/*164 */         qemu_free(filename);                                                          // 0.0
/*166 */     } else {                                                                          // 0.0
/*168 */         vga_bios_size = -1;                                                           // 0.0
/*170 */     }                                                                                 // 0.0
/*172 */     if (vga_bios_size < 0) {                                                          // 0.0
/*174 */         /* if no bios is present, we can still work */                                // 0.0
/*176 */         fprintf(stderr, "qemu: warning: could not load VGA bios '%s'\n",              // 0.0
/*178 */                 VGABIOS_FILENAME);                                                    // 0.0
/*180 */         vga_bios_size = 0;                                                            // 0.0
/*182 */     } else {                                                                          // 0.0
/*184 */         /* set a specific header (XXX: find real Apple format for NDRV                // 0.0
/*186 */            drivers) */                                                                // 0.0
/*188 */         vga_bios_ptr[0] = 'N';                                                        // 0.0
/*190 */         vga_bios_ptr[1] = 'D';                                                        // 0.0
/*192 */         vga_bios_ptr[2] = 'R';                                                        // 0.0
/*194 */         vga_bios_ptr[3] = 'V';                                                        // 0.0
/*196 */         cpu_to_be32w((uint32_t *)(vga_bios_ptr + 4), vga_bios_size);                  // 0.0
/*198 */         vga_bios_size += 8;                                                           // 0.0
/*202 */         /* Round to page boundary */                                                  // 0.0
/*204 */         vga_bios_size = (vga_bios_size + TARGET_PAGE_SIZE - 1) &                      // 0.0
/*206 */             TARGET_PAGE_MASK;                                                         // 0.0
/*208 */     }                                                                                 // 0.0
/*212 */     if (linux_boot) {                                                                 // 0.0
/*214 */         uint64_t lowaddr = 0;                                                         // 0.0
/*216 */         int bswap_needed;                                                             // 0.0
/*220 */ #ifdef BSWAP_NEEDED                                                                   // 0.0
/*222 */         bswap_needed = 1;                                                             // 0.0
/*224 */ #else                                                                                 // 0.0
/*226 */         bswap_needed = 0;                                                             // 0.0
/*228 */ #endif                                                                                // 0.0
/*230 */         kernel_base = KERNEL_LOAD_ADDR;                                               // 0.0
/*234 */         kernel_size = load_elf(kernel_filename, translate_kernel_address, NULL,       // 0.0
/*236 */                                NULL, &lowaddr, NULL, 1, ELF_MACHINE, 0);              // 0.0
/*238 */         if (kernel_size < 0)                                                          // 0.0
/*240 */             kernel_size = load_aout(kernel_filename, kernel_base,                     // 0.0
/*242 */                                     ram_size - kernel_base, bswap_needed,             // 0.0
/*244 */                                     TARGET_PAGE_SIZE);                                // 0.0
/*246 */         if (kernel_size < 0)                                                          // 0.0
/*248 */             kernel_size = load_image_targphys(kernel_filename,                        // 0.0
/*250 */                                               kernel_base,                            // 0.0
/*252 */                                               ram_size - kernel_base);                // 0.0
/*254 */         if (kernel_size < 0) {                                                        // 0.0
/*256 */             hw_error("qemu: could not load kernel '%s'\n", kernel_filename);          // 0.0
/*258 */             exit(1);                                                                  // 0.0
/*260 */         }                                                                             // 0.0
/*262 */         /* load initrd */                                                             // 0.0
/*264 */         if (initrd_filename) {                                                        // 0.0
/*266 */             initrd_base = INITRD_LOAD_ADDR;                                           // 0.0
/*268 */             initrd_size = load_image_targphys(initrd_filename, initrd_base,           // 0.0
/*270 */                                               ram_size - initrd_base);                // 0.0
/*272 */             if (initrd_size < 0) {                                                    // 0.0
/*274 */                 hw_error("qemu: could not load initial ram disk '%s'\n",              // 0.0
/*276 */                          initrd_filename);                                            // 0.0
/*278 */                 exit(1);                                                              // 0.0
/*280 */             }                                                                         // 0.0
/*282 */         } else {                                                                      // 0.0
/*284 */             initrd_base = 0;                                                          // 0.0
/*286 */             initrd_size = 0;                                                          // 0.0
/*288 */         }                                                                             // 0.0
/*290 */         ppc_boot_device = 'm';                                                        // 0.0
/*292 */     } else {                                                                          // 0.0
/*294 */         kernel_base = 0;                                                              // 0.0
/*296 */         kernel_size = 0;                                                              // 0.0
/*298 */         initrd_base = 0;                                                              // 0.0
/*300 */         initrd_size = 0;                                                              // 0.0
/*302 */         ppc_boot_device = '\0';                                                       // 0.0
/*304 */         /* We consider that NewWorld PowerMac never have any floppy drive             // 0.0
/*306 */          * For now, OHW cannot boot from the network.                                 // 0.0
/*308 */          */                                                                           // 0.0
/*310 */         for (i = 0; boot_device[i] != '\0'; i++) {                                    // 0.0
/*312 */             if (boot_device[i] >= 'c' && boot_device[i] <= 'f') {                     // 0.0
/*314 */                 ppc_boot_device = boot_device[i];                                     // 0.0
/*316 */                 break;                                                                // 0.0
/*318 */             }                                                                         // 0.0
/*320 */         }                                                                             // 0.0
/*322 */         if (ppc_boot_device == '\0') {                                                // 0.0
/*324 */             fprintf(stderr, "No valid boot device for Mac99 machine\n");              // 0.0
/*326 */             exit(1);                                                                  // 0.0
/*328 */         }                                                                             // 0.0
/*330 */     }                                                                                 // 0.0
/*334 */     isa_mem_base = 0x80000000;                                                        // 0.0
/*338 */     /* Register 8 MB of ISA IO space */                                               // 0.0
/*340 */     isa_mmio_init(0xf2000000, 0x00800000, 1);                                         // 0.0
/*344 */     /* UniN init */                                                                   // 0.0
/*346 */     unin_memory = cpu_register_io_memory(unin_read, unin_write, NULL);                // 0.0
/*348 */     cpu_register_physical_memory(0xf8000000, 0x00001000, unin_memory);                // 0.0
/*352 */     openpic_irqs = qemu_mallocz(smp_cpus * sizeof(qemu_irq *));                       // 0.0
/*354 */     openpic_irqs[0] =                                                                 // 0.0
/*356 */         qemu_mallocz(smp_cpus * sizeof(qemu_irq) * OPENPIC_OUTPUT_NB);                // 0.0
/*358 */     for (i = 0; i < smp_cpus; i++) {                                                  // 0.0
/*360 */         /* Mac99 IRQ connection between OpenPIC outputs pins                          // 0.0
/*362 */          * and PowerPC input pins                                                     // 0.0
/*364 */          */                                                                           // 0.0
/*366 */         switch (PPC_INPUT(env)) {                                                     // 0.0
/*368 */         case PPC_FLAGS_INPUT_6xx:                                                     // 0.0
/*370 */             openpic_irqs[i] = openpic_irqs[0] + (i * OPENPIC_OUTPUT_NB);              // 0.0
/*372 */             openpic_irqs[i][OPENPIC_OUTPUT_INT] =                                     // 0.0
/*374 */                 ((qemu_irq *)env->irq_inputs)[PPC6xx_INPUT_INT];                      // 0.0
/*376 */             openpic_irqs[i][OPENPIC_OUTPUT_CINT] =                                    // 0.0
/*378 */                 ((qemu_irq *)env->irq_inputs)[PPC6xx_INPUT_INT];                      // 0.0
/*380 */             openpic_irqs[i][OPENPIC_OUTPUT_MCK] =                                     // 0.0
/*382 */                 ((qemu_irq *)env->irq_inputs)[PPC6xx_INPUT_MCP];                      // 0.0
/*384 */             /* Not connected ? */                                                     // 0.0
/*386 */             openpic_irqs[i][OPENPIC_OUTPUT_DEBUG] = NULL;                             // 0.0
/*388 */             /* Check this */                                                          // 0.0
/*390 */             openpic_irqs[i][OPENPIC_OUTPUT_RESET] =                                   // 0.0
/*392 */                 ((qemu_irq *)env->irq_inputs)[PPC6xx_INPUT_HRESET];                   // 0.0
/*394 */             break;                                                                    // 0.0
/*396 */ #if defined(TARGET_PPC64)                                                             // 0.0
/*398 */         case PPC_FLAGS_INPUT_970:                                                     // 0.0
/*400 */             openpic_irqs[i] = openpic_irqs[0] + (i * OPENPIC_OUTPUT_NB);              // 0.0
/*402 */             openpic_irqs[i][OPENPIC_OUTPUT_INT] =                                     // 0.0
/*404 */                 ((qemu_irq *)env->irq_inputs)[PPC970_INPUT_INT];                      // 0.0
/*406 */             openpic_irqs[i][OPENPIC_OUTPUT_CINT] =                                    // 0.0
/*408 */                 ((qemu_irq *)env->irq_inputs)[PPC970_INPUT_INT];                      // 0.0
/*410 */             openpic_irqs[i][OPENPIC_OUTPUT_MCK] =                                     // 0.0
/*412 */                 ((qemu_irq *)env->irq_inputs)[PPC970_INPUT_MCP];                      // 0.0
/*414 */             /* Not connected ? */                                                     // 0.0
/*416 */             openpic_irqs[i][OPENPIC_OUTPUT_DEBUG] = NULL;                             // 0.0
/*418 */             /* Check this */                                                          // 0.0
/*420 */             openpic_irqs[i][OPENPIC_OUTPUT_RESET] =                                   // 0.0
/*422 */                 ((qemu_irq *)env->irq_inputs)[PPC970_INPUT_HRESET];                   // 0.0
/*424 */             break;                                                                    // 0.0
/*426 */ #endif /* defined(TARGET_PPC64) */                                                    // 0.0
/*428 */         default:                                                                      // 0.0
/*430 */             hw_error("Bus model not supported on mac99 machine\n");                   // 0.0
/*432 */             exit(1);                                                                  // 0.0
/*434 */         }                                                                             // 0.0
/*436 */     }                                                                                 // 0.0
/*438 */     pic = openpic_init(NULL, &pic_mem_index, smp_cpus, openpic_irqs, NULL);           // 0.0
/*440 */     if (PPC_INPUT(env) == PPC_FLAGS_INPUT_970) {                                      // 0.0
/*442 */         /* 970 gets a U3 bus */                                                       // 0.0
/*444 */         pci_bus = pci_pmac_u3_init(pic);                                              // 0.0
/*446 */         machine_arch = ARCH_MAC99_U3;                                                 // 0.0
/*448 */     } else {                                                                          // 0.0
/*450 */         pci_bus = pci_pmac_init(pic);                                                 // 0.0
/*452 */         machine_arch = ARCH_MAC99;                                                    // 0.0
/*454 */     }                                                                                 // 0.0
/*456 */     /* init basic PC hardware */                                                      // 0.0
/*458 */     pci_vga_init(pci_bus, vga_bios_offset, vga_bios_size);                            // 0.0
/*462 */     escc_mem_index = escc_init(0x80013000, pic[0x25], pic[0x24],                      // 0.0
/*464 */                                serial_hds[0], serial_hds[1], ESCC_CLOCK, 4);          // 0.0
/*468 */     for(i = 0; i < nb_nics; i++)                                                      // 0.0
/*470 */         pci_nic_init_nofail(&nd_table[i], "ne2k_pci", NULL);                          // 0.0
/*474 */     if (drive_get_max_bus(IF_IDE) >= MAX_IDE_BUS) {                                   // 0.0
/*476 */         fprintf(stderr, "qemu: too many IDE bus\n");                                  // 0.0
/*478 */         exit(1);                                                                      // 0.0
/*480 */     }                                                                                 // 0.0
/*482 */     dbdma = DBDMA_init(&dbdma_mem_index);                                             // 0.0
/*486 */     /* We only emulate 2 out of 3 IDE controllers for now */                          // 0.0
/*488 */     ide_mem_index[0] = -1;                                                            // 0.0
/*490 */     hd[0] = drive_get(IF_IDE, 0, 0);                                                  // 0.0
/*492 */     hd[1] = drive_get(IF_IDE, 0, 1);                                                  // 0.0
/*494 */     ide_mem_index[1] = pmac_ide_init(hd, pic[0x0d], dbdma, 0x16, pic[0x02]);          // 0.0
/*496 */     hd[0] = drive_get(IF_IDE, 1, 0);                                                  // 0.0
/*498 */     hd[1] = drive_get(IF_IDE, 1, 1);                                                  // 0.0
/*500 */     ide_mem_index[2] = pmac_ide_init(hd, pic[0x0e], dbdma, 0x1a, pic[0x02]);          // 0.0
/*504 */     /* cuda also initialize ADB */                                                    // 0.0
/*506 */     if (machine_arch == ARCH_MAC99_U3) {                                              // 0.0
/*508 */         usb_enabled = 1;                                                              // 0.0
/*510 */     }                                                                                 // 0.0
/*512 */     cuda_init(&cuda_mem_index, pic[0x19]);                                            // 0.0
/*516 */     adb_kbd_init(&adb_bus);                                                           // 0.0
/*518 */     adb_mouse_init(&adb_bus);                                                         // 0.0
/*522 */     macio_init(pci_bus, PCI_DEVICE_ID_APPLE_UNI_N_KEYL, 0, pic_mem_index,             // 0.0
/*524 */                dbdma_mem_index, cuda_mem_index, NULL, 3, ide_mem_index,               // 0.0
/*526 */                escc_mem_index);                                                       // 0.0
/*530 */     if (usb_enabled) {                                                                // 0.0
/*532 */         usb_ohci_init_pci(pci_bus, -1);                                               // 0.0
/*534 */     }                                                                                 // 0.0
/*538 */     /* U3 needs to use USB for input because Linux doesn't support via-cuda           // 0.0
/*540 */        on PPC64 */                                                                    // 0.0
/*542 */     if (machine_arch == ARCH_MAC99_U3) {                                              // 0.0
/*544 */         usbdevice_create("keyboard");                                                 // 0.0
/*546 */         usbdevice_create("mouse");                                                    // 0.0
/*548 */     }                                                                                 // 0.0
/*552 */     if (graphic_depth != 15 && graphic_depth != 32 && graphic_depth != 8)             // 0.0
/*554 */         graphic_depth = 15;                                                           // 0.0
/*558 */     /* The NewWorld NVRAM is not located in the MacIO device */                       // 0.0
/*560 */     nvr = macio_nvram_init(&nvram_mem_index, 0x2000, 1);                              // 0.0
/*562 */     pmac_format_nvram_partition(nvr, 0x2000);                                         // 0.0
/*564 */     macio_nvram_map(nvr, 0xFFF04000);                                                 // 0.0
/*566 */     /* No PCI init: the BIOS will do it */                                            // 0.0
/*570 */     fw_cfg = fw_cfg_init(0, 0, CFG_ADDR, CFG_ADDR + 2);                               // 0.0
/*572 */     fw_cfg_add_i32(fw_cfg, FW_CFG_ID, 1);                                             // 0.0
/*574 */     fw_cfg_add_i64(fw_cfg, FW_CFG_RAM_SIZE, (uint64_t)ram_size);                      // 0.0
/*576 */     fw_cfg_add_i16(fw_cfg, FW_CFG_MACHINE_ID, machine_arch);                          // 0.0
/*578 */     fw_cfg_add_i32(fw_cfg, FW_CFG_KERNEL_ADDR, kernel_base);                          // 0.0
/*580 */     fw_cfg_add_i32(fw_cfg, FW_CFG_KERNEL_SIZE, kernel_size);                          // 0.0
/*582 */     if (kernel_cmdline) {                                                             // 0.0
/*584 */         fw_cfg_add_i32(fw_cfg, FW_CFG_KERNEL_CMDLINE, CMDLINE_ADDR);                  // 0.0
/*586 */         pstrcpy_targphys("cmdline", CMDLINE_ADDR, TARGET_PAGE_SIZE, kernel_cmdline);  // 0.0
/*588 */     } else {                                                                          // 0.0
/*590 */         fw_cfg_add_i32(fw_cfg, FW_CFG_KERNEL_CMDLINE, 0);                             // 0.0
/*592 */     }                                                                                 // 0.0
/*594 */     fw_cfg_add_i32(fw_cfg, FW_CFG_INITRD_ADDR, initrd_base);                          // 0.0
/*596 */     fw_cfg_add_i32(fw_cfg, FW_CFG_INITRD_SIZE, initrd_size);                          // 0.0
/*598 */     fw_cfg_add_i16(fw_cfg, FW_CFG_BOOT_DEVICE, ppc_boot_device);                      // 0.0
/*602 */     fw_cfg_add_i16(fw_cfg, FW_CFG_PPC_WIDTH, graphic_width);                          // 0.0
/*604 */     fw_cfg_add_i16(fw_cfg, FW_CFG_PPC_HEIGHT, graphic_height);                        // 0.0
/*606 */     fw_cfg_add_i16(fw_cfg, FW_CFG_PPC_DEPTH, graphic_depth);                          // 0.0
/*610 */     fw_cfg_add_i32(fw_cfg, FW_CFG_PPC_IS_KVM, kvm_enabled());                         // 0.0
/*612 */     if (kvm_enabled()) {                                                              // 0.0
/*614 */ #ifdef CONFIG_KVM                                                                     // 0.0
/*616 */         uint8_t *hypercall;                                                           // 0.0
/*620 */         fw_cfg_add_i32(fw_cfg, FW_CFG_PPC_TBFREQ, kvmppc_get_tbfreq());               // 0.0
/*622 */         hypercall = qemu_malloc(16);                                                  // 0.0
/*624 */         kvmppc_get_hypercall(env, hypercall, 16);                                     // 0.0
/*626 */         fw_cfg_add_bytes(fw_cfg, FW_CFG_PPC_KVM_HC, hypercall, 16);                   // 0.0
/*628 */         fw_cfg_add_i32(fw_cfg, FW_CFG_PPC_KVM_PID, getpid());                         // 0.0
/*630 */ #endif                                                                                // 0.0
/*632 */     } else {                                                                          // 0.0
/*634 */         fw_cfg_add_i32(fw_cfg, FW_CFG_PPC_TBFREQ, get_ticks_per_sec());               // 0.0
/*636 */     }                                                                                 // 0.0
/*640 */     qemu_register_boot_set(fw_cfg_boot_set, fw_cfg);                                  // 0.0
/*642 */ }                                                                                     // 0.0
