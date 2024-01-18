// commit message qemu@63ffb564dc (target=0, prob=0.18462624, correct=True): fdc: refactor device creation
/*0   */ static void pc_init1(ram_addr_t ram_size,                                             // (10) 0.03125
/*2   */                      const char *boot_device,                                         // (2) 0.05273
/*4   */                      const char *kernel_filename,                                     // (5) 0.05273
/*6   */                      const char *kernel_cmdline,                                      // (1) 0.05469
/*8   */                      const char *initrd_filename,                                     // (0) 0.05469
/*10  */                      const char *cpu_model,                                           // (4) 0.05273
/*12  */                      int pci_enabled,                                                 // (7) 0.04883
/*14  */                      int kvmclock_enabled)                                            // (3) 0.05273
/*16  */ {                                                                                     // (27) 0.001953
/*18  */     int i;                                                                            // (25) 0.01172
/*20  */     ram_addr_t below_4g_mem_size, above_4g_mem_size;                                  // (6) 0.05078
/*22  */     PCIBus *pci_bus;                                                                  // (22) 0.02344
/*24  */     PCII440FXState *i440fx_state;                                                     // (13) 0.0293
/*26  */     int piix3_devfn = -1;                                                             // (18) 0.02734
/*28  */     qemu_irq *cpu_irq;                                                                // (16) 0.0293
/*30  */     qemu_irq *isa_irq;                                                                // (15) 0.0293
/*32  */     qemu_irq *i8259;                                                                  // (19) 0.02734
/*34  */     qemu_irq *cmos_s3;                                                                // (9) 0.03125
/*36  */     qemu_irq *smi_irq;                                                                // (11) 0.03125
/*38  */     IsaIrqState *isa_irq_state;                                                       // (12) 0.0293
/*40  */     DriveInfo *hd[MAX_IDE_BUS * MAX_IDE_DEVS];                                        // (8) 0.04102
/*42  */     FDCtrl *floppy_controller;                                                        // (23) 0.02344
/*44  */     BusState *idebus[MAX_IDE_BUS];                                                    // (14) 0.0293
/*46  */     ISADevice *rtc_state;                                                             // (20) 0.02539
/*50  */     pc_cpus_init(cpu_model);                                                          // (17) 0.02734
/*54  */     if (kvmclock_enabled) {                                                           // (24) 0.02344
/*56  */         kvmclock_create();                                                            // (21) 0.02539
/*58  */     }                                                                                 // (26) 0.007813
/*62  */     /* allocate ram and load rom/bios */                                              // 0.0
/*64  */     pc_memory_init(ram_size, kernel_filename, kernel_cmdline, initrd_filename,        // 0.0
/*66  */                    &below_4g_mem_size, &above_4g_mem_size);                           // 0.0
/*70  */     cpu_irq = pc_allocate_cpu_irq();                                                  // 0.0
/*72  */     i8259 = i8259_init(cpu_irq[0]);                                                   // 0.0
/*74  */     isa_irq_state = qemu_mallocz(sizeof(*isa_irq_state));                             // 0.0
/*76  */     isa_irq_state->i8259 = i8259;                                                     // 0.0
/*78  */     if (pci_enabled) {                                                                // 0.0
/*80  */         ioapic_init(isa_irq_state);                                                   // 0.0
/*82  */     }                                                                                 // 0.0
/*84  */     isa_irq = qemu_allocate_irqs(isa_irq_handler, isa_irq_state, 24);                 // 0.0
/*88  */     if (pci_enabled) {                                                                // 0.0
/*90  */         pci_bus = i440fx_init(&i440fx_state, &piix3_devfn, isa_irq, ram_size);        // 0.0
/*92  */     } else {                                                                          // 0.0
/*94  */         pci_bus = NULL;                                                               // 0.0
/*96  */         i440fx_state = NULL;                                                          // 0.0
/*98  */         isa_bus_new(NULL);                                                            // 0.0
/*100 */     }                                                                                 // 0.0
/*102 */     isa_bus_irqs(isa_irq);                                                            // 0.0
/*106 */     pc_register_ferr_irq(isa_reserve_irq(13));                                        // 0.0
/*110 */     pc_vga_init(pci_enabled? pci_bus: NULL);                                          // 0.0
/*114 */     /* init basic PC hardware */                                                      // 0.0
/*116 */     pc_basic_device_init(isa_irq, &floppy_controller, &rtc_state);                    // 0.0
/*120 */     for(i = 0; i < nb_nics; i++) {                                                    // 0.0
/*122 */         NICInfo *nd = &nd_table[i];                                                   // 0.0
/*126 */         if (!pci_enabled || (nd->model && strcmp(nd->model, "ne2k_isa") == 0))        // 0.0
/*128 */             pc_init_ne2k_isa(nd);                                                     // 0.0
/*130 */         else                                                                          // 0.0
/*132 */             pci_nic_init_nofail(nd, "e1000", NULL);                                   // 0.0
/*134 */     }                                                                                 // 0.0
/*138 */     if (drive_get_max_bus(IF_IDE) >= MAX_IDE_BUS) {                                   // 0.0
/*140 */         fprintf(stderr, "qemu: too many IDE bus\n");                                  // 0.0
/*142 */         exit(1);                                                                      // 0.0
/*144 */     }                                                                                 // 0.0
/*148 */     for(i = 0; i < MAX_IDE_BUS * MAX_IDE_DEVS; i++) {                                 // 0.0
/*150 */         hd[i] = drive_get(IF_IDE, i / MAX_IDE_DEVS, i % MAX_IDE_DEVS);                // 0.0
/*152 */     }                                                                                 // 0.0
/*156 */     if (pci_enabled) {                                                                // 0.0
/*158 */         PCIDevice *dev;                                                               // 0.0
/*160 */         dev = pci_piix3_ide_init(pci_bus, hd, piix3_devfn + 1);                       // 0.0
/*162 */         idebus[0] = qdev_get_child_bus(&dev->qdev, "ide.0");                          // 0.0
/*164 */         idebus[1] = qdev_get_child_bus(&dev->qdev, "ide.1");                          // 0.0
/*166 */     } else {                                                                          // 0.0
/*168 */         for(i = 0; i < MAX_IDE_BUS; i++) {                                            // 0.0
/*170 */             ISADevice *dev;                                                           // 0.0
/*172 */             dev = isa_ide_init(ide_iobase[i], ide_iobase2[i], ide_irq[i],             // 0.0
/*174 */                                hd[MAX_IDE_DEVS * i], hd[MAX_IDE_DEVS * i + 1]);       // 0.0
/*176 */             idebus[i] = qdev_get_child_bus(&dev->qdev, "ide.0");                      // 0.0
/*178 */         }                                                                             // 0.0
/*180 */     }                                                                                 // 0.0
/*184 */     audio_init(isa_irq, pci_enabled ? pci_bus : NULL);                                // 0.0
/*188 */     pc_cmos_init(below_4g_mem_size, above_4g_mem_size, boot_device,                   // 0.0
/*190 */                  idebus[0], idebus[1], floppy_controller, rtc_state);                 // 0.0
/*194 */     if (pci_enabled && usb_enabled) {                                                 // 0.0
/*196 */         usb_uhci_piix3_init(pci_bus, piix3_devfn + 2);                                // 0.0
/*198 */     }                                                                                 // 0.0
/*202 */     if (pci_enabled && acpi_enabled) {                                                // 0.0
/*204 */         uint8_t *eeprom_buf = qemu_mallocz(8 * 256); /* XXX: make this persistent */  // 0.0
/*206 */         i2c_bus *smbus;                                                               // 0.0
/*210 */         cmos_s3 = qemu_allocate_irqs(pc_cmos_set_s3_resume, rtc_state, 1);            // 0.0
/*212 */         smi_irq = qemu_allocate_irqs(pc_acpi_smi_interrupt, first_cpu, 1);            // 0.0
/*214 */         /* TODO: Populate SPD eeprom data.  */                                        // 0.0
/*216 */         smbus = piix4_pm_init(pci_bus, piix3_devfn + 3, 0xb100,                       // 0.0
/*218 */                               isa_reserve_irq(9), *cmos_s3, *smi_irq,                 // 0.0
/*220 */                               kvm_enabled());                                         // 0.0
/*222 */         for (i = 0; i < 8; i++) {                                                     // 0.0
/*224 */             DeviceState *eeprom;                                                      // 0.0
/*226 */             eeprom = qdev_create((BusState *)smbus, "smbus-eeprom");                  // 0.0
/*228 */             qdev_prop_set_uint8(eeprom, "address", 0x50 + i);                         // 0.0
/*230 */             qdev_prop_set_ptr(eeprom, "data", eeprom_buf + (i * 256));                // 0.0
/*232 */             qdev_init_nofail(eeprom);                                                 // 0.0
/*234 */         }                                                                             // 0.0
/*236 */     }                                                                                 // 0.0
/*240 */     if (i440fx_state) {                                                               // 0.0
/*242 */         i440fx_init_memory_mappings(i440fx_state);                                    // 0.0
/*244 */     }                                                                                 // 0.0
/*248 */     if (pci_enabled) {                                                                // 0.0
/*250 */         pc_pci_device_init(pci_bus);                                                  // 0.0
/*252 */     }                                                                                 // 0.0
/*254 */ }                                                                                     // 0.0
