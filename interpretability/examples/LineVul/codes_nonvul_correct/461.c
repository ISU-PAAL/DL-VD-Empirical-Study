// commit message qemu@7d55273fcd (target=0, prob=0.35316852, correct=True): sparc64: really initialize irq
/*0   */ static void sun4uv_init(ram_addr_t RAM_size,                                      // (11) 0.02723
/*2   */                         const char *boot_devices,                                 // (6) 0.03465
/*4   */                         const char *kernel_filename, const char *kernel_cmdline,  // (4) 0.0439
/*6   */                         const char *initrd_filename, const char *cpu_model,       // (3) 0.04398
/*8   */                         const struct hwdef *hwdef)                                // (5) 0.03875
/*10  */ {                                                                                 // (30) 0.003159
/*12  */     CPUState *env;                                                                // (25) 0.01009
/*14  */     char *filename;                                                               // (28) 0.008357
/*16  */     m48t59_t *nvram;                                                              // (17) 0.01594
/*18  */     int ret, linux_boot;                                                          // (22) 0.01309
/*20  */     unsigned int i;                                                               // (27) 0.00836
/*22  */     ram_addr_t ram_offset, prom_offset;                                           // (15) 0.0191
/*24  */     long initrd_size, kernel_size;                                                // (14) 0.02099
/*26  */     PCIBus *pci_bus, *pci_bus2, *pci_bus3;                                        // (9) 0.03313
/*28  */     QEMUBH *bh;                                                                   // (20) 0.01413
/*30  */     qemu_irq *irq;                                                                // (18) 0.01594
/*32  */     int drive_index;                                                              // (24) 0.01055
/*34  */     BlockDriverState *hd[MAX_IDE_BUS * MAX_IDE_DEVS];                             // (1) 0.0541
/*36  */     BlockDriverState *fd[MAX_FD];                                                 // (8) 0.03314
/*38  */     void *fw_cfg;                                                                 // (2) 0.04838
/*40  */     ResetData *reset_info;                                                        // (0) 0.2451
/*44  */     linux_boot = (kernel_filename != NULL);                                       // (13) 0.02397
/*48  */     /* init CPUs */                                                               // (19) 0.01513
/*50  */     if (!cpu_model)                                                               // (23) 0.01108
/*52  */         cpu_model = hwdef->default_cpu_model;                                     // (12) 0.025
/*56  */     env = cpu_init(cpu_model);                                                    // (16) 0.01596
/*58  */     if (!env) {                                                                   // (26) 0.009615
/*60  */         fprintf(stderr, "Unable to find Sparc CPU definition\n");                 // (7) 0.03433
/*62  */         exit(1);                                                                  // (21) 0.0137
/*64  */     }                                                                             // (29) 0.005276
/*66  */     bh = qemu_bh_new(tick_irq, env);                                              // (10) 0.02801
/*68  */     env->tick = ptimer_init(bh);                                                  // 0.0
/*70  */     ptimer_set_period(env->tick, 1ULL);                                           // 0.0
/*74  */     bh = qemu_bh_new(stick_irq, env);                                             // 0.0
/*76  */     env->stick = ptimer_init(bh);                                                 // 0.0
/*78  */     ptimer_set_period(env->stick, 1ULL);                                          // 0.0
/*82  */     bh = qemu_bh_new(hstick_irq, env);                                            // 0.0
/*84  */     env->hstick = ptimer_init(bh);                                                // 0.0
/*86  */     ptimer_set_period(env->hstick, 1ULL);                                         // 0.0
/*90  */     reset_info = qemu_mallocz(sizeof(ResetData));                                 // 0.0
/*92  */     reset_info->env = env;                                                        // 0.0
/*94  */     reset_info->reset_addr = hwdef->prom_addr + 0x40ULL;                          // 0.0
/*96  */     qemu_register_reset(main_cpu_reset, reset_info);                              // 0.0
/*98  */     main_cpu_reset(reset_info);                                                   // 0.0
/*100 */     // Override warm reset address with cold start address                        // 0.0
/*102 */     env->pc = hwdef->prom_addr + 0x20ULL;                                         // 0.0
/*104 */     env->npc = env->pc + 4;                                                       // 0.0
/*108 */     /* allocate RAM */                                                            // 0.0
/*110 */     ram_offset = qemu_ram_alloc(RAM_size);                                        // 0.0
/*112 */     cpu_register_physical_memory(0, RAM_size, ram_offset);                        // 0.0
/*116 */     prom_offset = qemu_ram_alloc(PROM_SIZE_MAX);                                  // 0.0
/*118 */     cpu_register_physical_memory(hwdef->prom_addr,                                // 0.0
/*120 */                                  (PROM_SIZE_MAX + TARGET_PAGE_SIZE) &             // 0.0
/*122 */                                  TARGET_PAGE_MASK,                                // 0.0
/*124 */                                  prom_offset | IO_MEM_ROM);                       // 0.0
/*128 */     if (bios_name == NULL)                                                        // 0.0
/*130 */         bios_name = PROM_FILENAME;                                                // 0.0
/*132 */     filename = qemu_find_file(QEMU_FILE_TYPE_BIOS, bios_name);                    // 0.0
/*134 */     if (filename) {                                                               // 0.0
/*136 */         ret = load_elf(filename, hwdef->prom_addr - PROM_VADDR,                   // 0.0
/*138 */                        NULL, NULL, NULL);                                         // 0.0
/*140 */         if (ret < 0) {                                                            // 0.0
/*142 */             ret = load_image_targphys(filename, hwdef->prom_addr,                 // 0.0
/*144 */                                       (PROM_SIZE_MAX + TARGET_PAGE_SIZE) &        // 0.0
/*146 */                                   TARGET_PAGE_MASK);                              // 0.0
/*148 */         }                                                                         // 0.0
/*150 */         qemu_free(filename);                                                      // 0.0
/*152 */     } else {                                                                      // 0.0
/*154 */         ret = -1;                                                                 // 0.0
/*156 */     }                                                                             // 0.0
/*158 */     if (ret < 0) {                                                                // 0.0
/*160 */         fprintf(stderr, "qemu: could not load prom '%s'\n",                       // 0.0
/*162 */                 bios_name);                                                       // 0.0
/*164 */         exit(1);                                                                  // 0.0
/*166 */     }                                                                             // 0.0
/*170 */     kernel_size = 0;                                                              // 0.0
/*172 */     initrd_size = 0;                                                              // 0.0
/*174 */     if (linux_boot) {                                                             // 0.0
/*176 */         /* XXX: put correct offset */                                             // 0.0
/*178 */         kernel_size = load_elf(kernel_filename, 0, NULL, NULL, NULL);             // 0.0
/*180 */         if (kernel_size < 0)                                                      // 0.0
/*182 */             kernel_size = load_aout(kernel_filename, KERNEL_LOAD_ADDR,            // 0.0
/*184 */                                     ram_size - KERNEL_LOAD_ADDR);                 // 0.0
/*186 */         if (kernel_size < 0)                                                      // 0.0
/*188 */             kernel_size = load_image_targphys(kernel_filename,                    // 0.0
/*190 */                                               KERNEL_LOAD_ADDR,                   // 0.0
/*192 */                                               ram_size - KERNEL_LOAD_ADDR);       // 0.0
/*194 */         if (kernel_size < 0) {                                                    // 0.0
/*196 */             fprintf(stderr, "qemu: could not load kernel '%s'\n",                 // 0.0
/*198 */                     kernel_filename);                                             // 0.0
/*200 */             exit(1);                                                              // 0.0
/*202 */         }                                                                         // 0.0
/*206 */         /* load initrd */                                                         // 0.0
/*208 */         if (initrd_filename) {                                                    // 0.0
/*210 */             initrd_size = load_image_targphys(initrd_filename,                    // 0.0
/*212 */                                               INITRD_LOAD_ADDR,                   // 0.0
/*214 */                                               ram_size - INITRD_LOAD_ADDR);       // 0.0
/*216 */             if (initrd_size < 0) {                                                // 0.0
/*218 */                 fprintf(stderr, "qemu: could not load initial ram disk '%s'\n",   // 0.0
/*220 */                         initrd_filename);                                         // 0.0
/*222 */                 exit(1);                                                          // 0.0
/*224 */             }                                                                     // 0.0
/*226 */         }                                                                         // 0.0
/*228 */         if (initrd_size > 0) {                                                    // 0.0
/*230 */             for (i = 0; i < 64 * TARGET_PAGE_SIZE; i += TARGET_PAGE_SIZE) {       // 0.0
/*232 */                 if (ldl_phys(KERNEL_LOAD_ADDR + i) == 0x48647253) { // HdrS       // 0.0
/*234 */                     stl_phys(KERNEL_LOAD_ADDR + i + 16, INITRD_LOAD_ADDR);        // 0.0
/*236 */                     stl_phys(KERNEL_LOAD_ADDR + i + 20, initrd_size);             // 0.0
/*238 */                     break;                                                        // 0.0
/*240 */                 }                                                                 // 0.0
/*242 */             }                                                                     // 0.0
/*244 */         }                                                                         // 0.0
/*246 */     }                                                                             // 0.0
/*248 */     pci_bus = pci_apb_init(APB_SPECIAL_BASE, APB_MEM_BASE, NULL, &pci_bus2,       // 0.0
/*250 */                            &pci_bus3);                                            // 0.0
/*252 */     isa_mem_base = VGA_BASE;                                                      // 0.0
/*254 */     pci_vga_init(pci_bus, 0, 0);                                                  // 0.0
/*258 */     // XXX Should be pci_bus3                                                     // 0.0
/*260 */     pci_ebus_init(pci_bus, -1);                                                   // 0.0
/*264 */     i = 0;                                                                        // 0.0
/*266 */     if (hwdef->console_serial_base) {                                             // 0.0
/*268 */         serial_mm_init(hwdef->console_serial_base, 0, NULL, 115200,               // 0.0
/*270 */                        serial_hds[i], 1);                                         // 0.0
/*272 */         i++;                                                                      // 0.0
/*274 */     }                                                                             // 0.0
/*276 */     for(; i < MAX_SERIAL_PORTS; i++) {                                            // 0.0
/*278 */         if (serial_hds[i]) {                                                      // 0.0
/*280 */             serial_init(serial_io[i], NULL/*serial_irq[i]*/, 115200,              // 0.0
/*282 */                         serial_hds[i]);                                           // 0.0
/*284 */         }                                                                         // 0.0
/*286 */     }                                                                             // 0.0
/*290 */     for(i = 0; i < MAX_PARALLEL_PORTS; i++) {                                     // 0.0
/*292 */         if (parallel_hds[i]) {                                                    // 0.0
/*294 */             parallel_init(parallel_io[i], NULL/*parallel_irq[i]*/,                // 0.0
/*296 */                           parallel_hds[i]);                                       // 0.0
/*298 */         }                                                                         // 0.0
/*300 */     }                                                                             // 0.0
/*304 */     for(i = 0; i < nb_nics; i++)                                                  // 0.0
/*306 */         pci_nic_init(&nd_table[i], "ne2k_pci", NULL);                             // 0.0
/*310 */     irq = qemu_allocate_irqs(cpu_set_irq, env, MAX_PILS);                         // 0.0
/*312 */     if (drive_get_max_bus(IF_IDE) >= MAX_IDE_BUS) {                               // 0.0
/*314 */         fprintf(stderr, "qemu: too many IDE bus\n");                              // 0.0
/*316 */         exit(1);                                                                  // 0.0
/*318 */     }                                                                             // 0.0
/*320 */     for(i = 0; i < MAX_IDE_BUS * MAX_IDE_DEVS; i++) {                             // 0.0
/*322 */         drive_index = drive_get_index(IF_IDE, i / MAX_IDE_DEVS,                   // 0.0
/*324 */                                       i % MAX_IDE_DEVS);                          // 0.0
/*326 */        if (drive_index != -1)                                                     // 0.0
/*328 */            hd[i] = drives_table[drive_index].bdrv;                                // 0.0
/*330 */        else                                                                       // 0.0
/*332 */            hd[i] = NULL;                                                          // 0.0
/*334 */     }                                                                             // 0.0
/*338 */     pci_cmd646_ide_init(pci_bus, hd, 1);                                          // 0.0
/*342 */     /* FIXME: wire up interrupts.  */                                             // 0.0
/*344 */     i8042_init(NULL/*1*/, NULL/*12*/, 0x60);                                      // 0.0
/*346 */     for(i = 0; i < MAX_FD; i++) {                                                 // 0.0
/*348 */         drive_index = drive_get_index(IF_FLOPPY, 0, i);                           // 0.0
/*350 */        if (drive_index != -1)                                                     // 0.0
/*352 */            fd[i] = drives_table[drive_index].bdrv;                                // 0.0
/*354 */        else                                                                       // 0.0
/*356 */            fd[i] = NULL;                                                          // 0.0
/*358 */     }                                                                             // 0.0
/*360 */     floppy_controller = fdctrl_init(NULL/*6*/, 2, 0, 0x3f0, fd);                  // 0.0
/*362 */     nvram = m48t59_init(NULL/*8*/, 0, 0x0074, NVRAM_SIZE, 59);                    // 0.0
/*364 */     sun4u_NVRAM_set_params(nvram, NVRAM_SIZE, "Sun4u", RAM_size, boot_devices,    // 0.0
/*366 */                            KERNEL_LOAD_ADDR, kernel_size,                         // 0.0
/*368 */                            kernel_cmdline,                                        // 0.0
/*370 */                            INITRD_LOAD_ADDR, initrd_size,                         // 0.0
/*372 */                            /* XXX: need an option to load a NVRAM image */        // 0.0
/*374 */                            0,                                                     // 0.0
/*376 */                            graphic_width, graphic_height, graphic_depth,          // 0.0
/*378 */                            (uint8_t *)&nd_table[0].macaddr);                      // 0.0
/*382 */     fw_cfg = fw_cfg_init(BIOS_CFG_IOPORT, BIOS_CFG_IOPORT + 1, 0, 0);             // 0.0
/*384 */     fw_cfg_add_i32(fw_cfg, FW_CFG_ID, 1);                                         // 0.0
/*386 */     fw_cfg_add_i64(fw_cfg, FW_CFG_RAM_SIZE, (uint64_t)ram_size);                  // 0.0
/*388 */     fw_cfg_add_i16(fw_cfg, FW_CFG_MACHINE_ID, hwdef->machine_id);                 // 0.0
/*390 */     fw_cfg_add_i32(fw_cfg, FW_CFG_KERNEL_ADDR, KERNEL_LOAD_ADDR);                 // 0.0
/*392 */     fw_cfg_add_i32(fw_cfg, FW_CFG_KERNEL_SIZE, kernel_size);                      // 0.0
/*394 */     if (kernel_cmdline) {                                                         // 0.0
/*396 */         fw_cfg_add_i32(fw_cfg, FW_CFG_KERNEL_CMDLINE, CMDLINE_ADDR);              // 0.0
/*398 */         pstrcpy_targphys(CMDLINE_ADDR, TARGET_PAGE_SIZE, kernel_cmdline);         // 0.0
/*400 */     } else {                                                                      // 0.0
/*402 */         fw_cfg_add_i32(fw_cfg, FW_CFG_KERNEL_CMDLINE, 0);                         // 0.0
/*404 */     }                                                                             // 0.0
/*406 */     fw_cfg_add_i32(fw_cfg, FW_CFG_INITRD_ADDR, INITRD_LOAD_ADDR);                 // 0.0
/*408 */     fw_cfg_add_i32(fw_cfg, FW_CFG_INITRD_SIZE, initrd_size);                      // 0.0
/*410 */     fw_cfg_add_i16(fw_cfg, FW_CFG_BOOT_DEVICE, boot_devices[0]);                  // 0.0
/*412 */     qemu_register_boot_set(fw_cfg_boot_set, fw_cfg);                              // 0.0
/*414 */ }                                                                                 // 0.0
