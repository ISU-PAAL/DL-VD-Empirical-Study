// commit message qemu@dca6eeed8c (target=0, prob=0.5199856, correct=False): arm: highbank: Defeature CPU override
/*0   */ static void calxeda_init(MachineState *machine, enum cxmachines machine_id)       // (1) 0.04297
/*2   */ {                                                                                 // (32) 0.001953
/*4   */     ram_addr_t ram_size = machine->ram_size;                                      // (6) 0.03516
/*6   */     const char *cpu_model = machine->cpu_model;                                   // (10) 0.03125
/*8   */     const char *kernel_filename = machine->kernel_filename;                       // (11) 0.03125
/*10  */     const char *kernel_cmdline = machine->kernel_cmdline;                         // (8) 0.03516
/*12  */     const char *initrd_filename = machine->initrd_filename;                       // (5) 0.03516
/*14  */     DeviceState *dev = NULL;                                                      // (23) 0.01953
/*16  */     SysBusDevice *busdev;                                                         // (22) 0.02148
/*18  */     qemu_irq pic[128];                                                            // (17) 0.02539
/*20  */     int n;                                                                        // (30) 0.01172
/*22  */     qemu_irq cpu_irq[4];                                                          // (12) 0.03125
/*24  */     qemu_irq cpu_fiq[4];                                                          // (13) 0.03125
/*26  */     MemoryRegion *sysram;                                                         // (28) 0.01758
/*28  */     MemoryRegion *dram;                                                           // (27) 0.01758
/*30  */     MemoryRegion *sysmem;                                                         // (26) 0.01758
/*32  */     char *sysboot_filename;                                                       // (25) 0.01953
/*36  */     if (!cpu_model) {                                                             // (24) 0.01953
/*38  */         switch (machine_id) {                                                     // (14) 0.02734
/*40  */         case CALXEDA_HIGHBANK:                                                    // (7) 0.03516
/*42  */             cpu_model = "cortex-a9";                                              // (3) 0.04297
/*44  */             break;                                                                // (19) 0.02539
/*46  */         case CALXEDA_MIDWAY:                                                      // (9) 0.0332
/*48  */             cpu_model = "cortex-a15";                                             // (2) 0.04297
/*50  */             break;                                                                // (18) 0.02539
/*52  */         }                                                                         // (29) 0.01562
/*54  */     }                                                                             // (31) 0.007812
/*58  */     for (n = 0; n < smp_cpus; n++) {                                              // (4) 0.03906
/*60  */         ObjectClass *oc = cpu_class_by_name(TYPE_ARM_CPU, cpu_model);             // (0) 0.05859
/*62  */         Object *cpuobj;                                                           // (21) 0.02344
/*64  */         ARMCPU *cpu;                                                              // (16) 0.02539
/*66  */         Error *err = NULL;                                                        // (15) 0.02539
/*70  */         if (!oc) {                                                                // (20) 0.02344
/*72  */             error_report("Unable to find CPU definition");                        // 0.0
/*74  */             exit(1);                                                              // 0.0
/*76  */         }                                                                         // 0.0
/*80  */         cpuobj = object_new(object_class_get_name(oc));                           // 0.0
/*82  */         cpu = ARM_CPU(cpuobj);                                                    // 0.0
/*86  */         /* By default A9 and A15 CPUs have EL3 enabled.  This board does not      // 0.0
/*88  */          * currently support EL3 so the CPU EL3 property is disabled before       // 0.0
/*90  */          * realization.                                                           // 0.0
/*92  */          */                                                                       // 0.0
/*94  */         if (object_property_find(cpuobj, "has_el3", NULL)) {                      // 0.0
/*96  */             object_property_set_bool(cpuobj, false, "has_el3", &err);             // 0.0
/*98  */             if (err) {                                                            // 0.0
/*100 */                 error_report_err(err);                                            // 0.0
/*102 */                 exit(1);                                                          // 0.0
/*104 */             }                                                                     // 0.0
/*106 */         }                                                                         // 0.0
/*110 */         if (object_property_find(cpuobj, "reset-cbar", NULL)) {                   // 0.0
/*112 */             object_property_set_int(cpuobj, MPCORE_PERIPHBASE,                    // 0.0
/*114 */                                     "reset-cbar", &error_abort);                  // 0.0
/*116 */         }                                                                         // 0.0
/*118 */         object_property_set_bool(cpuobj, true, "realized", &err);                 // 0.0
/*120 */         if (err) {                                                                // 0.0
/*122 */             error_report_err(err);                                                // 0.0
/*124 */             exit(1);                                                              // 0.0
/*126 */         }                                                                         // 0.0
/*128 */         cpu_irq[n] = qdev_get_gpio_in(DEVICE(cpu), ARM_CPU_IRQ);                  // 0.0
/*130 */         cpu_fiq[n] = qdev_get_gpio_in(DEVICE(cpu), ARM_CPU_FIQ);                  // 0.0
/*132 */     }                                                                             // 0.0
/*136 */     sysmem = get_system_memory();                                                 // 0.0
/*138 */     dram = g_new(MemoryRegion, 1);                                                // 0.0
/*140 */     memory_region_allocate_system_memory(dram, NULL, "highbank.dram", ram_size);  // 0.0
/*142 */     /* SDRAM at address zero.  */                                                 // 0.0
/*144 */     memory_region_add_subregion(sysmem, 0, dram);                                 // 0.0
/*148 */     sysram = g_new(MemoryRegion, 1);                                              // 0.0
/*150 */     memory_region_init_ram(sysram, NULL, "highbank.sysram", 0x8000,               // 0.0
/*152 */                            &error_fatal);                                         // 0.0
/*154 */     memory_region_add_subregion(sysmem, 0xfff88000, sysram);                      // 0.0
/*156 */     if (bios_name != NULL) {                                                      // 0.0
/*158 */         sysboot_filename = qemu_find_file(QEMU_FILE_TYPE_BIOS, bios_name);        // 0.0
/*160 */         if (sysboot_filename != NULL) {                                           // 0.0
/*162 */             if (load_image_targphys(sysboot_filename, 0xfff88000, 0x8000) < 0) {  // 0.0
/*164 */                 hw_error("Unable to load %s\n", bios_name);                       // 0.0
/*166 */             }                                                                     // 0.0
/*168 */             g_free(sysboot_filename);                                             // 0.0
/*170 */         } else {                                                                  // 0.0
/*172 */            hw_error("Unable to find %s\n", bios_name);                            // 0.0
/*174 */         }                                                                         // 0.0
/*176 */     }                                                                             // 0.0
/*180 */     switch (machine_id) {                                                         // 0.0
/*182 */     case CALXEDA_HIGHBANK:                                                        // 0.0
/*184 */         dev = qdev_create(NULL, "l2x0");                                          // 0.0
/*186 */         qdev_init_nofail(dev);                                                    // 0.0
/*188 */         busdev = SYS_BUS_DEVICE(dev);                                             // 0.0
/*190 */         sysbus_mmio_map(busdev, 0, 0xfff12000);                                   // 0.0
/*194 */         dev = qdev_create(NULL, "a9mpcore_priv");                                 // 0.0
/*196 */         break;                                                                    // 0.0
/*198 */     case CALXEDA_MIDWAY:                                                          // 0.0
/*200 */         dev = qdev_create(NULL, "a15mpcore_priv");                                // 0.0
/*202 */         break;                                                                    // 0.0
/*204 */     }                                                                             // 0.0
/*206 */     qdev_prop_set_uint32(dev, "num-cpu", smp_cpus);                               // 0.0
/*208 */     qdev_prop_set_uint32(dev, "num-irq", NIRQ_GIC);                               // 0.0
/*210 */     qdev_init_nofail(dev);                                                        // 0.0
/*212 */     busdev = SYS_BUS_DEVICE(dev);                                                 // 0.0
/*214 */     sysbus_mmio_map(busdev, 0, MPCORE_PERIPHBASE);                                // 0.0
/*216 */     for (n = 0; n < smp_cpus; n++) {                                              // 0.0
/*218 */         sysbus_connect_irq(busdev, n, cpu_irq[n]);                                // 0.0
/*220 */         sysbus_connect_irq(busdev, n + smp_cpus, cpu_fiq[n]);                     // 0.0
/*222 */     }                                                                             // 0.0
/*226 */     for (n = 0; n < 128; n++) {                                                   // 0.0
/*228 */         pic[n] = qdev_get_gpio_in(dev, n);                                        // 0.0
/*230 */     }                                                                             // 0.0
/*234 */     dev = qdev_create(NULL, "sp804");                                             // 0.0
/*236 */     qdev_prop_set_uint32(dev, "freq0", 150000000);                                // 0.0
/*238 */     qdev_prop_set_uint32(dev, "freq1", 150000000);                                // 0.0
/*240 */     qdev_init_nofail(dev);                                                        // 0.0
/*242 */     busdev = SYS_BUS_DEVICE(dev);                                                 // 0.0
/*244 */     sysbus_mmio_map(busdev, 0, 0xfff34000);                                       // 0.0
/*246 */     sysbus_connect_irq(busdev, 0, pic[18]);                                       // 0.0
/*248 */     sysbus_create_simple("pl011", 0xfff36000, pic[20]);                           // 0.0
/*252 */     dev = qdev_create(NULL, "highbank-regs");                                     // 0.0
/*254 */     qdev_init_nofail(dev);                                                        // 0.0
/*256 */     busdev = SYS_BUS_DEVICE(dev);                                                 // 0.0
/*258 */     sysbus_mmio_map(busdev, 0, 0xfff3c000);                                       // 0.0
/*262 */     sysbus_create_simple("pl061", 0xfff30000, pic[14]);                           // 0.0
/*264 */     sysbus_create_simple("pl061", 0xfff31000, pic[15]);                           // 0.0
/*266 */     sysbus_create_simple("pl061", 0xfff32000, pic[16]);                           // 0.0
/*268 */     sysbus_create_simple("pl061", 0xfff33000, pic[17]);                           // 0.0
/*270 */     sysbus_create_simple("pl031", 0xfff35000, pic[19]);                           // 0.0
/*272 */     sysbus_create_simple("pl022", 0xfff39000, pic[23]);                           // 0.0
/*276 */     sysbus_create_simple("sysbus-ahci", 0xffe08000, pic[83]);                     // 0.0
/*280 */     if (nd_table[0].used) {                                                       // 0.0
/*282 */         qemu_check_nic_model(&nd_table[0], "xgmac");                              // 0.0
/*284 */         dev = qdev_create(NULL, "xgmac");                                         // 0.0
/*286 */         qdev_set_nic_properties(dev, &nd_table[0]);                               // 0.0
/*288 */         qdev_init_nofail(dev);                                                    // 0.0
/*290 */         sysbus_mmio_map(SYS_BUS_DEVICE(dev), 0, 0xfff50000);                      // 0.0
/*292 */         sysbus_connect_irq(SYS_BUS_DEVICE(dev), 0, pic[77]);                      // 0.0
/*294 */         sysbus_connect_irq(SYS_BUS_DEVICE(dev), 1, pic[78]);                      // 0.0
/*296 */         sysbus_connect_irq(SYS_BUS_DEVICE(dev), 2, pic[79]);                      // 0.0
/*300 */         qemu_check_nic_model(&nd_table[1], "xgmac");                              // 0.0
/*302 */         dev = qdev_create(NULL, "xgmac");                                         // 0.0
/*304 */         qdev_set_nic_properties(dev, &nd_table[1]);                               // 0.0
/*306 */         qdev_init_nofail(dev);                                                    // 0.0
/*308 */         sysbus_mmio_map(SYS_BUS_DEVICE(dev), 0, 0xfff51000);                      // 0.0
/*310 */         sysbus_connect_irq(SYS_BUS_DEVICE(dev), 0, pic[80]);                      // 0.0
/*312 */         sysbus_connect_irq(SYS_BUS_DEVICE(dev), 1, pic[81]);                      // 0.0
/*314 */         sysbus_connect_irq(SYS_BUS_DEVICE(dev), 2, pic[82]);                      // 0.0
/*316 */     }                                                                             // 0.0
/*320 */     highbank_binfo.ram_size = ram_size;                                           // 0.0
/*322 */     highbank_binfo.kernel_filename = kernel_filename;                             // 0.0
/*324 */     highbank_binfo.kernel_cmdline = kernel_cmdline;                               // 0.0
/*326 */     highbank_binfo.initrd_filename = initrd_filename;                             // 0.0
/*328 */     /* highbank requires a dtb in order to boot, and the dtb will override        // 0.0
/*330 */      * the board ID. The following value is ignored, so set it to -1 to be        // 0.0
/*332 */      * clear that the value is meaningless.                                       // 0.0
/*334 */      */                                                                           // 0.0
/*336 */     highbank_binfo.board_id = -1;                                                 // 0.0
/*338 */     highbank_binfo.nb_cpus = smp_cpus;                                            // 0.0
/*340 */     highbank_binfo.loader_start = 0;                                              // 0.0
/*342 */     highbank_binfo.write_secondary_boot = hb_write_secondary;                     // 0.0
/*344 */     highbank_binfo.secondary_cpu_reset_hook = hb_reset_secondary;                 // 0.0
/*346 */     arm_load_kernel(ARM_CPU(first_cpu), &highbank_binfo);                         // 0.0
/*348 */ }                                                                                 // 0.0
