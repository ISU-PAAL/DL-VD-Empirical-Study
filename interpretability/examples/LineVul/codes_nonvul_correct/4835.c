// commit message qemu@c97294ec1b (target=0, prob=0.43586326, correct=True): SMBIOS: Build aggregate smbios tables and entry point
/*0   */ static void pc_init1(QEMUMachineInitArgs *args,                                   // (8) 0.03125
/*2   */                      int pci_enabled,                                             // (4) 0.04883
/*4   */                      int kvmclock_enabled)                                        // (0) 0.05273
/*6   */ {                                                                                 // (31) 0.001953
/*8   */     MemoryRegion *system_memory = get_system_memory();                            // (7) 0.03125
/*10  */     MemoryRegion *system_io = get_system_io();                                    // (9) 0.03125
/*12  */     int i;                                                                        // (29) 0.01172
/*14  */     ram_addr_t below_4g_mem_size, above_4g_mem_size;                              // (2) 0.05078
/*16  */     PCIBus *pci_bus;                                                              // (20) 0.02344
/*18  */     ISABus *isa_bus;                                                              // (24) 0.02148
/*20  */     PCII440FXState *i440fx_state;                                                 // (11) 0.0293
/*22  */     int piix3_devfn = -1;                                                         // (14) 0.02734
/*24  */     qemu_irq *cpu_irq;                                                            // (13) 0.0293
/*26  */     qemu_irq *gsi;                                                                // (19) 0.02539
/*28  */     qemu_irq *i8259;                                                              // (16) 0.02734
/*30  */     qemu_irq *smi_irq;                                                            // (10) 0.03125
/*32  */     GSIState *gsi_state;                                                          // (21) 0.02344
/*34  */     DriveInfo *hd[MAX_IDE_BUS * MAX_IDE_DEVS];                                    // (6) 0.04101
/*36  */     BusState *idebus[MAX_IDE_BUS];                                                // (12) 0.0293
/*38  */     ISADevice *rtc_state;                                                         // (18) 0.02539
/*40  */     ISADevice *floppy;                                                            // (23) 0.02148
/*42  */     MemoryRegion *ram_memory;                                                     // (28) 0.01953
/*44  */     MemoryRegion *pci_memory;                                                     // (22) 0.02148
/*46  */     MemoryRegion *rom_memory;                                                     // (27) 0.01953
/*48  */     DeviceState *icc_bridge;                                                      // (26) 0.01956
/*50  */     FWCfgState *fw_cfg = NULL;                                                    // (15) 0.02734
/*52  */     PcGuestInfo *guest_info;                                                      // (17) 0.02539
/*56  */     if (xen_enabled() && xen_hvm_init(&ram_memory) != 0) {                        // (1) 0.05078
/*58  */         fprintf(stderr, "xen hardware virtual machine initialisation failed\n");  // (3) 0.05078
/*60  */         exit(1);                                                                  // (25) 0.02148
/*62  */     }                                                                             // (30) 0.007812
/*66  */     icc_bridge = qdev_create(NULL, TYPE_ICC_BRIDGE);                              // (5) 0.04687
/*68  */     object_property_add_child(qdev_get_machine(), "icc-bridge",                   // 0.0
/*70  */                               OBJECT(icc_bridge), NULL);                          // 0.0
/*74  */     pc_cpus_init(args->cpu_model, icc_bridge);                                    // 0.0
/*78  */     if (kvm_enabled() && kvmclock_enabled) {                                      // 0.0
/*80  */         kvmclock_create();                                                        // 0.0
/*82  */     }                                                                             // 0.0
/*86  */     /* Check whether RAM fits below 4G (leaving 1/2 GByte for IO memory).         // 0.0
/*88  */      * If it doesn't, we need to split it in chunks below and above 4G.           // 0.0
/*90  */      * In any case, try to make sure that guest addresses aligned at              // 0.0
/*92  */      * 1G boundaries get mapped to host addresses aligned at 1G boundaries.       // 0.0
/*94  */      * For old machine types, use whatever split we used historically to avoid    // 0.0
/*96  */      * breaking migration.                                                        // 0.0
/*98  */      */                                                                           // 0.0
/*100 */     if (args->ram_size >= 0xe0000000) {                                           // 0.0
/*102 */         ram_addr_t lowmem = gigabyte_align ? 0xc0000000 : 0xe0000000;             // 0.0
/*104 */         above_4g_mem_size = args->ram_size - lowmem;                              // 0.0
/*106 */         below_4g_mem_size = lowmem;                                               // 0.0
/*108 */     } else {                                                                      // 0.0
/*110 */         above_4g_mem_size = 0;                                                    // 0.0
/*112 */         below_4g_mem_size = args->ram_size;                                       // 0.0
/*114 */     }                                                                             // 0.0
/*118 */     if (pci_enabled) {                                                            // 0.0
/*120 */         pci_memory = g_new(MemoryRegion, 1);                                      // 0.0
/*122 */         memory_region_init(pci_memory, NULL, "pci", UINT64_MAX);                  // 0.0
/*124 */         rom_memory = pci_memory;                                                  // 0.0
/*126 */     } else {                                                                      // 0.0
/*128 */         pci_memory = NULL;                                                        // 0.0
/*130 */         rom_memory = system_memory;                                               // 0.0
/*132 */     }                                                                             // 0.0
/*136 */     guest_info = pc_guest_info_init(below_4g_mem_size, above_4g_mem_size);        // 0.0
/*140 */     guest_info->has_acpi_build = has_acpi_build;                                  // 0.0
/*144 */     guest_info->has_pci_info = has_pci_info;                                      // 0.0
/*146 */     guest_info->isapc_ram_fw = !pci_enabled;                                      // 0.0
/*150 */     if (smbios_defaults) {                                                        // 0.0
/*152 */         /* These values are guest ABI, do not change */                           // 0.0
/*154 */         smbios_set_defaults("QEMU", "Standard PC (i440FX + PIIX, 1996)",          // 0.0
/*156 */                             args->machine->name);                                 // 0.0
/*158 */     }                                                                             // 0.0
/*162 */     /* allocate ram and load rom/bios */                                          // 0.0
/*164 */     if (!xen_enabled()) {                                                         // 0.0
/*166 */         fw_cfg = pc_memory_init(system_memory,                                    // 0.0
/*168 */                        args->kernel_filename, args->kernel_cmdline,               // 0.0
/*170 */                        args->initrd_filename,                                     // 0.0
/*172 */                        below_4g_mem_size, above_4g_mem_size,                      // 0.0
/*174 */                        rom_memory, &ram_memory, guest_info);                      // 0.0
/*176 */     }                                                                             // 0.0
/*180 */     gsi_state = g_malloc0(sizeof(*gsi_state));                                    // 0.0
/*182 */     if (kvm_irqchip_in_kernel()) {                                                // 0.0
/*184 */         kvm_pc_setup_irq_routing(pci_enabled);                                    // 0.0
/*186 */         gsi = qemu_allocate_irqs(kvm_pc_gsi_handler, gsi_state,                   // 0.0
/*188 */                                  GSI_NUM_PINS);                                   // 0.0
/*190 */     } else {                                                                      // 0.0
/*192 */         gsi = qemu_allocate_irqs(gsi_handler, gsi_state, GSI_NUM_PINS);           // 0.0
/*194 */     }                                                                             // 0.0
/*198 */     if (pci_enabled) {                                                            // 0.0
/*200 */         pci_bus = i440fx_init(&i440fx_state, &piix3_devfn, &isa_bus, gsi,         // 0.0
/*202 */                               system_memory, system_io, args->ram_size,           // 0.0
/*204 */                               below_4g_mem_size,                                  // 0.0
/*206 */                               above_4g_mem_size,                                  // 0.0
/*208 */                               pci_memory, ram_memory);                            // 0.0
/*210 */     } else {                                                                      // 0.0
/*212 */         pci_bus = NULL;                                                           // 0.0
/*214 */         i440fx_state = NULL;                                                      // 0.0
/*216 */         isa_bus = isa_bus_new(NULL, system_io);                                   // 0.0
/*218 */         no_hpet = 1;                                                              // 0.0
/*220 */     }                                                                             // 0.0
/*222 */     isa_bus_irqs(isa_bus, gsi);                                                   // 0.0
/*226 */     if (kvm_irqchip_in_kernel()) {                                                // 0.0
/*228 */         i8259 = kvm_i8259_init(isa_bus);                                          // 0.0
/*230 */     } else if (xen_enabled()) {                                                   // 0.0
/*232 */         i8259 = xen_interrupt_controller_init();                                  // 0.0
/*234 */     } else {                                                                      // 0.0
/*236 */         cpu_irq = pc_allocate_cpu_irq();                                          // 0.0
/*238 */         i8259 = i8259_init(isa_bus, cpu_irq[0]);                                  // 0.0
/*240 */     }                                                                             // 0.0
/*244 */     for (i = 0; i < ISA_NUM_IRQS; i++) {                                          // 0.0
/*246 */         gsi_state->i8259_irq[i] = i8259[i];                                       // 0.0
/*248 */     }                                                                             // 0.0
/*250 */     if (pci_enabled) {                                                            // 0.0
/*252 */         ioapic_init_gsi(gsi_state, "i440fx");                                     // 0.0
/*254 */     }                                                                             // 0.0
/*256 */     qdev_init_nofail(icc_bridge);                                                 // 0.0
/*260 */     pc_register_ferr_irq(gsi[13]);                                                // 0.0
/*264 */     pc_vga_init(isa_bus, pci_enabled ? pci_bus : NULL);                           // 0.0
/*268 */     /* init basic PC hardware */                                                  // 0.0
/*270 */     pc_basic_device_init(isa_bus, gsi, &rtc_state, &floppy, xen_enabled(),        // 0.0
/*272 */         0x4);                                                                     // 0.0
/*276 */     pc_nic_init(isa_bus, pci_bus);                                                // 0.0
/*280 */     ide_drive_get(hd, MAX_IDE_BUS);                                               // 0.0
/*282 */     if (pci_enabled) {                                                            // 0.0
/*284 */         PCIDevice *dev;                                                           // 0.0
/*286 */         if (xen_enabled()) {                                                      // 0.0
/*288 */             dev = pci_piix3_xen_ide_init(pci_bus, hd, piix3_devfn + 1);           // 0.0
/*290 */         } else {                                                                  // 0.0
/*292 */             dev = pci_piix3_ide_init(pci_bus, hd, piix3_devfn + 1);               // 0.0
/*294 */         }                                                                         // 0.0
/*296 */         idebus[0] = qdev_get_child_bus(&dev->qdev, "ide.0");                      // 0.0
/*298 */         idebus[1] = qdev_get_child_bus(&dev->qdev, "ide.1");                      // 0.0
/*300 */     } else {                                                                      // 0.0
/*302 */         for(i = 0; i < MAX_IDE_BUS; i++) {                                        // 0.0
/*304 */             ISADevice *dev;                                                       // 0.0
/*306 */             char busname[] = "ide.0";                                             // 0.0
/*308 */             dev = isa_ide_init(isa_bus, ide_iobase[i], ide_iobase2[i],            // 0.0
/*310 */                                ide_irq[i],                                        // 0.0
/*312 */                                hd[MAX_IDE_DEVS * i], hd[MAX_IDE_DEVS * i + 1]);   // 0.0
/*314 */             /*                                                                    // 0.0
/*316 */              * The ide bus name is ide.0 for the first bus and ide.1 for the      // 0.0
/*318 */              * second one.                                                        // 0.0
/*320 */              */                                                                   // 0.0
/*322 */             busname[4] = '0' + i;                                                 // 0.0
/*324 */             idebus[i] = qdev_get_child_bus(DEVICE(dev), busname);                 // 0.0
/*326 */         }                                                                         // 0.0
/*328 */     }                                                                             // 0.0
/*332 */     pc_cmos_init(below_4g_mem_size, above_4g_mem_size, args->boot_order,          // 0.0
/*334 */                  floppy, idebus[0], idebus[1], rtc_state);                        // 0.0
/*338 */     if (pci_enabled && usb_enabled(false)) {                                      // 0.0
/*340 */         pci_create_simple(pci_bus, piix3_devfn + 2, "piix3-usb-uhci");            // 0.0
/*342 */     }                                                                             // 0.0
/*346 */     if (pci_enabled && acpi_enabled) {                                            // 0.0
/*348 */         I2CBus *smbus;                                                            // 0.0
/*352 */         smi_irq = qemu_allocate_irqs(pc_acpi_smi_interrupt, first_cpu, 1);        // 0.0
/*354 */         /* TODO: Populate SPD eeprom data.  */                                    // 0.0
/*356 */         smbus = piix4_pm_init(pci_bus, piix3_devfn + 3, 0xb100,                   // 0.0
/*358 */                               gsi[9], *smi_irq,                                   // 0.0
/*360 */                               kvm_enabled(), fw_cfg);                             // 0.0
/*362 */         smbus_eeprom_init(smbus, 8, NULL, 0);                                     // 0.0
/*364 */     }                                                                             // 0.0
/*368 */     if (pci_enabled) {                                                            // 0.0
/*370 */         pc_pci_device_init(pci_bus);                                              // 0.0
/*372 */     }                                                                             // 0.0
/*374 */ }                                                                                 // 0.0
