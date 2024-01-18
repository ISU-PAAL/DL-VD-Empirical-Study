// commit message qemu@446f16a690 (target=1, prob=0.5412091, correct=True): machine: query kernel-irqchip property
/*0   */ void ppce500_init(MachineState *machine, PPCE500Params *params)                   // (4) 0.03906
/*2   */ {                                                                                 // (32) 0.001953
/*4   */     MemoryRegion *address_space_mem = get_system_memory();                        // (5) 0.03516
/*6   */     MemoryRegion *ram = g_new(MemoryRegion, 1);                                   // (7) 0.0332
/*8   */     PCIBus *pci_bus;                                                              // (15) 0.02344
/*10  */     CPUPPCState *env = NULL;                                                      // (16) 0.02344
/*12  */     uint64_t loadaddr;                                                            // (22) 0.01953
/*14  */     hwaddr kernel_base = -1LL;                                                    // (9) 0.02734
/*16  */     int kernel_size = 0;                                                          // (24) 0.01953
/*18  */     hwaddr dt_base = 0;                                                           // (14) 0.02539
/*20  */     hwaddr initrd_base = 0;                                                       // (13) 0.02539
/*22  */     int initrd_size = 0;                                                          // (20) 0.02148
/*24  */     hwaddr cur_base = 0;                                                          // (18) 0.02344
/*26  */     char *filename;                                                               // (29) 0.01367
/*28  */     hwaddr bios_entry = 0;                                                        // (19) 0.02344
/*30  */     target_long bios_size;                                                        // (23) 0.01953
/*32  */     struct boot_info *boot_info;                                                  // (17) 0.02344
/*34  */     int dt_size;                                                                  // (25) 0.01758
/*36  */     int i;                                                                        // (30) 0.01172
/*38  */     /* irq num for pin INTA, INTB, INTC and INTD is 1, 2, 3 and                   // (2) 0.05273
/*40  */      * 4 respectively */                                                          // (27) 0.01562
/*42  */     unsigned int pci_irq_nrs[PCI_NUM_PINS] = {1, 2, 3, 4};                        // (0) 0.06055
/*44  */     qemu_irq **irqs, *mpic;                                                       // (6) 0.0332
/*46  */     DeviceState *dev;                                                             // (26) 0.01563
/*48  */     CPUPPCState *firstenv = NULL;                                                 // (12) 0.02539
/*50  */     MemoryRegion *ccsr_addr_space;                                                // (11) 0.02539
/*52  */     SysBusDevice *s;                                                              // (21) 0.01953
/*54  */     PPCE500CCSRState *ccsr;                                                       // (10) 0.02539
/*58  */     /* Setup CPUs */                                                              // (28) 0.01367
/*60  */     if (machine->cpu_model == NULL) {                                             // (8) 0.02734
/*62  */         machine->cpu_model = "e500v2_v30";                                        // (3) 0.04297
/*64  */     }                                                                             // (31) 0.007812
/*68  */     irqs = g_malloc0(smp_cpus * sizeof(qemu_irq *));                              // (1) 0.05469
/*70  */     irqs[0] = g_malloc0(smp_cpus * sizeof(qemu_irq) * OPENPIC_OUTPUT_NB);         // 0.0
/*72  */     for (i = 0; i < smp_cpus; i++) {                                              // 0.0
/*74  */         PowerPCCPU *cpu;                                                          // 0.0
/*76  */         CPUState *cs;                                                             // 0.0
/*78  */         qemu_irq *input;                                                          // 0.0
/*82  */         cpu = cpu_ppc_init(machine->cpu_model);                                   // 0.0
/*84  */         if (cpu == NULL) {                                                        // 0.0
/*86  */             fprintf(stderr, "Unable to initialize CPU!\n");                       // 0.0
/*88  */             exit(1);                                                              // 0.0
/*90  */         }                                                                         // 0.0
/*92  */         env = &cpu->env;                                                          // 0.0
/*94  */         cs = CPU(cpu);                                                            // 0.0
/*98  */         if (!firstenv) {                                                          // 0.0
/*100 */             firstenv = env;                                                       // 0.0
/*102 */         }                                                                         // 0.0
/*106 */         irqs[i] = irqs[0] + (i * OPENPIC_OUTPUT_NB);                              // 0.0
/*108 */         input = (qemu_irq *)env->irq_inputs;                                      // 0.0
/*110 */         irqs[i][OPENPIC_OUTPUT_INT] = input[PPCE500_INPUT_INT];                   // 0.0
/*112 */         irqs[i][OPENPIC_OUTPUT_CINT] = input[PPCE500_INPUT_CINT];                 // 0.0
/*114 */         env->spr_cb[SPR_BOOKE_PIR].default_value = cs->cpu_index = i;             // 0.0
/*116 */         env->mpic_iack = params->ccsrbar_base +                                   // 0.0
/*118 */                          MPC8544_MPIC_REGS_OFFSET + 0xa0;                         // 0.0
/*122 */         ppc_booke_timers_init(cpu, 400000000, PPC_TIMER_E500);                    // 0.0
/*126 */         /* Register reset handler */                                              // 0.0
/*128 */         if (!i) {                                                                 // 0.0
/*130 */             /* Primary CPU */                                                     // 0.0
/*132 */             struct boot_info *boot_info;                                          // 0.0
/*134 */             boot_info = g_malloc0(sizeof(struct boot_info));                      // 0.0
/*136 */             qemu_register_reset(ppce500_cpu_reset, cpu);                          // 0.0
/*138 */             env->load_info = boot_info;                                           // 0.0
/*140 */         } else {                                                                  // 0.0
/*142 */             /* Secondary CPUs */                                                  // 0.0
/*144 */             qemu_register_reset(ppce500_cpu_reset_sec, cpu);                      // 0.0
/*146 */         }                                                                         // 0.0
/*148 */     }                                                                             // 0.0
/*152 */     env = firstenv;                                                               // 0.0
/*156 */     /* Fixup Memory size on a alignment boundary */                               // 0.0
/*158 */     ram_size &= ~(RAM_SIZES_ALIGN - 1);                                           // 0.0
/*160 */     machine->ram_size = ram_size;                                                 // 0.0
/*164 */     /* Register Memory */                                                         // 0.0
/*166 */     memory_region_allocate_system_memory(ram, NULL, "mpc8544ds.ram", ram_size);   // 0.0
/*168 */     memory_region_add_subregion(address_space_mem, 0, ram);                       // 0.0
/*172 */     dev = qdev_create(NULL, "e500-ccsr");                                         // 0.0
/*174 */     object_property_add_child(qdev_get_machine(), "e500-ccsr",                    // 0.0
/*176 */                               OBJECT(dev), NULL);                                 // 0.0
/*178 */     qdev_init_nofail(dev);                                                        // 0.0
/*180 */     ccsr = CCSR(dev);                                                             // 0.0
/*182 */     ccsr_addr_space = &ccsr->ccsr_space;                                          // 0.0
/*184 */     memory_region_add_subregion(address_space_mem, params->ccsrbar_base,          // 0.0
/*186 */                                 ccsr_addr_space);                                 // 0.0
/*190 */     mpic = ppce500_init_mpic(params, ccsr_addr_space, irqs);                      // 0.0
/*194 */     /* Serial */                                                                  // 0.0
/*196 */     if (serial_hds[0]) {                                                          // 0.0
/*198 */         serial_mm_init(ccsr_addr_space, MPC8544_SERIAL0_REGS_OFFSET,              // 0.0
/*200 */                        0, mpic[42], 399193,                                       // 0.0
/*202 */                        serial_hds[0], DEVICE_BIG_ENDIAN);                         // 0.0
/*204 */     }                                                                             // 0.0
/*208 */     if (serial_hds[1]) {                                                          // 0.0
/*210 */         serial_mm_init(ccsr_addr_space, MPC8544_SERIAL1_REGS_OFFSET,              // 0.0
/*212 */                        0, mpic[42], 399193,                                       // 0.0
/*214 */                        serial_hds[1], DEVICE_BIG_ENDIAN);                         // 0.0
/*216 */     }                                                                             // 0.0
/*220 */     /* General Utility device */                                                  // 0.0
/*222 */     dev = qdev_create(NULL, "mpc8544-guts");                                      // 0.0
/*224 */     qdev_init_nofail(dev);                                                        // 0.0
/*226 */     s = SYS_BUS_DEVICE(dev);                                                      // 0.0
/*228 */     memory_region_add_subregion(ccsr_addr_space, MPC8544_UTIL_OFFSET,             // 0.0
/*230 */                                 sysbus_mmio_get_region(s, 0));                    // 0.0
/*234 */     /* PCI */                                                                     // 0.0
/*236 */     dev = qdev_create(NULL, "e500-pcihost");                                      // 0.0
/*238 */     qdev_prop_set_uint32(dev, "first_slot", params->pci_first_slot);              // 0.0
/*240 */     qdev_prop_set_uint32(dev, "first_pin_irq", pci_irq_nrs[0]);                   // 0.0
/*242 */     qdev_init_nofail(dev);                                                        // 0.0
/*244 */     s = SYS_BUS_DEVICE(dev);                                                      // 0.0
/*246 */     for (i = 0; i < PCI_NUM_PINS; i++) {                                          // 0.0
/*248 */         sysbus_connect_irq(s, i, mpic[pci_irq_nrs[i]]);                           // 0.0
/*250 */     }                                                                             // 0.0
/*254 */     memory_region_add_subregion(ccsr_addr_space, MPC8544_PCI_REGS_OFFSET,         // 0.0
/*256 */                                 sysbus_mmio_get_region(s, 0));                    // 0.0
/*260 */     pci_bus = (PCIBus *)qdev_get_child_bus(dev, "pci.0");                         // 0.0
/*262 */     if (!pci_bus)                                                                 // 0.0
/*264 */         printf("couldn't create PCI controller!\n");                              // 0.0
/*268 */     if (pci_bus) {                                                                // 0.0
/*270 */         /* Register network interfaces. */                                        // 0.0
/*272 */         for (i = 0; i < nb_nics; i++) {                                           // 0.0
/*274 */             pci_nic_init_nofail(&nd_table[i], pci_bus, "virtio", NULL);           // 0.0
/*276 */         }                                                                         // 0.0
/*278 */     }                                                                             // 0.0
/*282 */     /* Register spinning region */                                                // 0.0
/*284 */     sysbus_create_simple("e500-spin", params->spin_base, NULL);                   // 0.0
/*288 */     if (cur_base < (32 * 1024 * 1024)) {                                          // 0.0
/*290 */         /* u-boot occupies memory up to 32MB, so load blobs above */              // 0.0
/*292 */         cur_base = (32 * 1024 * 1024);                                            // 0.0
/*294 */     }                                                                             // 0.0
/*298 */     if (params->has_mpc8xxx_gpio) {                                               // 0.0
/*300 */         qemu_irq poweroff_irq;                                                    // 0.0
/*304 */         dev = qdev_create(NULL, "mpc8xxx_gpio");                                  // 0.0
/*306 */         s = SYS_BUS_DEVICE(dev);                                                  // 0.0
/*308 */         qdev_init_nofail(dev);                                                    // 0.0
/*310 */         sysbus_connect_irq(s, 0, mpic[MPC8XXX_GPIO_IRQ]);                         // 0.0
/*312 */         memory_region_add_subregion(ccsr_addr_space, MPC8XXX_GPIO_OFFSET,         // 0.0
/*314 */                                     sysbus_mmio_get_region(s, 0));                // 0.0
/*318 */         /* Power Off GPIO at Pin 0 */                                             // 0.0
/*320 */         poweroff_irq = qemu_allocate_irq(ppce500_power_off, NULL, 0);             // 0.0
/*322 */         qdev_connect_gpio_out(dev, 0, poweroff_irq);                              // 0.0
/*324 */     }                                                                             // 0.0
/*328 */     /* Platform Bus Device */                                                     // 0.0
/*330 */     if (params->has_platform_bus) {                                               // 0.0
/*332 */         dev = qdev_create(NULL, TYPE_PLATFORM_BUS_DEVICE);                        // 0.0
/*334 */         dev->id = TYPE_PLATFORM_BUS_DEVICE;                                       // 0.0
/*336 */         qdev_prop_set_uint32(dev, "num_irqs", params->platform_bus_num_irqs);     // 0.0
/*338 */         qdev_prop_set_uint32(dev, "mmio_size", params->platform_bus_size);        // 0.0
/*340 */         qdev_init_nofail(dev);                                                    // 0.0
/*342 */         s = SYS_BUS_DEVICE(dev);                                                  // 0.0
/*346 */         for (i = 0; i < params->platform_bus_num_irqs; i++) {                     // 0.0
/*348 */             int irqn = params->platform_bus_first_irq + i;                        // 0.0
/*350 */             sysbus_connect_irq(s, i, mpic[irqn]);                                 // 0.0
/*352 */         }                                                                         // 0.0
/*356 */         memory_region_add_subregion(address_space_mem,                            // 0.0
/*358 */                                     params->platform_bus_base,                    // 0.0
/*360 */                                     sysbus_mmio_get_region(s, 0));                // 0.0
/*362 */     }                                                                             // 0.0
/*366 */     /* Load kernel. */                                                            // 0.0
/*368 */     if (machine->kernel_filename) {                                               // 0.0
/*370 */         kernel_base = cur_base;                                                   // 0.0
/*372 */         kernel_size = load_image_targphys(machine->kernel_filename,               // 0.0
/*374 */                                           cur_base,                               // 0.0
/*376 */                                           ram_size - cur_base);                   // 0.0
/*378 */         if (kernel_size < 0) {                                                    // 0.0
/*380 */             fprintf(stderr, "qemu: could not load kernel '%s'\n",                 // 0.0
/*382 */                     machine->kernel_filename);                                    // 0.0
/*384 */             exit(1);                                                              // 0.0
/*386 */         }                                                                         // 0.0
/*390 */         cur_base += kernel_size;                                                  // 0.0
/*392 */     }                                                                             // 0.0
/*396 */     /* Load initrd. */                                                            // 0.0
/*398 */     if (machine->initrd_filename) {                                               // 0.0
/*400 */         initrd_base = (cur_base + INITRD_LOAD_PAD) & ~INITRD_PAD_MASK;            // 0.0
/*402 */         initrd_size = load_image_targphys(machine->initrd_filename, initrd_base,  // 0.0
/*404 */                                           ram_size - initrd_base);                // 0.0
/*408 */         if (initrd_size < 0) {                                                    // 0.0
/*410 */             fprintf(stderr, "qemu: could not load initial ram disk '%s'\n",       // 0.0
/*412 */                     machine->initrd_filename);                                    // 0.0
/*414 */             exit(1);                                                              // 0.0
/*416 */         }                                                                         // 0.0
/*420 */         cur_base = initrd_base + initrd_size;                                     // 0.0
/*422 */     }                                                                             // 0.0
/*426 */     /*                                                                            // 0.0
/*428 */      * Smart firmware defaults ahead!                                             // 0.0
/*430 */      *                                                                            // 0.0
/*432 */      * We follow the following table to select which payload we execute.          // 0.0
/*434 */      *                                                                            // 0.0
/*436 */      *  -kernel | -bios | payload                                                 // 0.0
/*438 */      * ---------+-------+---------                                                // 0.0
/*440 */      *     N    |   Y   | u-boot                                                  // 0.0
/*442 */      *     N    |   N   | u-boot                                                  // 0.0
/*444 */      *     Y    |   Y   | u-boot                                                  // 0.0
/*446 */      *     Y    |   N   | kernel                                                  // 0.0
/*448 */      *                                                                            // 0.0
/*450 */      * This ensures backwards compatibility with how we used to expose            // 0.0
/*452 */      * -kernel to users but allows them to run through u-boot as well.            // 0.0
/*454 */      */                                                                           // 0.0
/*456 */     if (bios_name == NULL) {                                                      // 0.0
/*458 */         if (machine->kernel_filename) {                                           // 0.0
/*460 */             bios_name = machine->kernel_filename;                                 // 0.0
/*462 */         } else {                                                                  // 0.0
/*464 */             bios_name = "u-boot.e500";                                            // 0.0
/*466 */         }                                                                         // 0.0
/*468 */     }                                                                             // 0.0
/*470 */     filename = qemu_find_file(QEMU_FILE_TYPE_BIOS, bios_name);                    // 0.0
/*474 */     bios_size = load_elf(filename, NULL, NULL, &bios_entry, &loadaddr, NULL,      // 0.0
/*476 */                          1, ELF_MACHINE, 0);                                      // 0.0
/*478 */     if (bios_size < 0) {                                                          // 0.0
/*480 */         /*                                                                        // 0.0
/*482 */          * Hrm. No ELF image? Try a uImage, maybe someone is giving us an         // 0.0
/*484 */          * ePAPR compliant kernel                                                 // 0.0
/*486 */          */                                                                       // 0.0
/*488 */         kernel_size = load_uimage(filename, &bios_entry, &loadaddr, NULL,         // 0.0
/*490 */                                   NULL, NULL);                                    // 0.0
/*492 */         if (kernel_size < 0) {                                                    // 0.0
/*494 */             fprintf(stderr, "qemu: could not load firmware '%s'\n", filename);    // 0.0
/*496 */             exit(1);                                                              // 0.0
/*498 */         }                                                                         // 0.0
/*500 */     }                                                                             // 0.0
/*504 */     /* Reserve space for dtb */                                                   // 0.0
/*506 */     dt_base = (loadaddr + bios_size + DTC_LOAD_PAD) & ~DTC_PAD_MASK;              // 0.0
/*510 */     dt_size = ppce500_prep_device_tree(machine, params, dt_base,                  // 0.0
/*512 */                                        initrd_base, initrd_size,                  // 0.0
/*514 */                                        kernel_base, kernel_size);                 // 0.0
/*516 */     if (dt_size < 0) {                                                            // 0.0
/*518 */         fprintf(stderr, "couldn't load device tree\n");                           // 0.0
/*520 */         exit(1);                                                                  // 0.0
/*522 */     }                                                                             // 0.0
/*524 */     assert(dt_size < DTB_MAX_SIZE);                                               // 0.0
/*528 */     boot_info = env->load_info;                                                   // 0.0
/*530 */     boot_info->entry = bios_entry;                                                // 0.0
/*532 */     boot_info->dt_base = dt_base;                                                 // 0.0
/*534 */     boot_info->dt_size = dt_size;                                                 // 0.0
/*538 */     if (kvm_enabled()) {                                                          // 0.0
/*540 */         kvmppc_init();                                                            // 0.0
/*542 */     }                                                                             // 0.0
/*544 */ }                                                                                 // 0.0
