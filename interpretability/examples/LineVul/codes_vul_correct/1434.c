// commit message qemu@b86160555f (target=1, prob=0.55353886, correct=True): integrator: fix Linux boot failure by emulating dbg region
/*0   */ static void integratorcp_init(QEMUMachineInitArgs *args)                         // (11) 0.0332
/*2   */ {                                                                                // (30) 0.001953
/*4   */     ram_addr_t ram_size = args->ram_size;                                        // (7) 0.03516
/*6   */     const char *cpu_model = args->cpu_model;                                     // (15) 0.03125
/*8   */     const char *kernel_filename = args->kernel_filename;                         // (16) 0.03125
/*10  */     const char *kernel_cmdline = args->kernel_cmdline;                           // (9) 0.03516
/*12  */     const char *initrd_filename = args->initrd_filename;                         // (10) 0.03516
/*14  */     ARMCPU *cpu;                                                                 // (24) 0.01758
/*16  */     MemoryRegion *address_space_mem = get_system_memory();                       // (8) 0.03516
/*18  */     MemoryRegion *ram = g_new(MemoryRegion, 1);                                  // (12) 0.0332
/*20  */     MemoryRegion *ram_alias = g_new(MemoryRegion, 1);                            // (6) 0.03711
/*22  */     qemu_irq pic[32];                                                            // (19) 0.02539
/*24  */     DeviceState *dev;                                                            // (25) 0.01563
/*26  */     int i;                                                                       // (27) 0.01172
/*30  */     if (!cpu_model) {                                                            // (23) 0.01953
/*32  */         cpu_model = "arm926";                                                    // (14) 0.03125
/*34  */     }                                                                            // (29) 0.007812
/*36  */     cpu = cpu_arm_init(cpu_model);                                               // (17) 0.0293
/*38  */     if (!cpu) {                                                                  // (26) 0.01562
/*40  */         fprintf(stderr, "Unable to find CPU definition\n");                      // (4) 0.04687
/*42  */         exit(1);                                                                 // (22) 0.02148
/*44  */     }                                                                            // (28) 0.007812
/*48  */     memory_region_init_ram(ram, NULL, "integrator.ram", ram_size);               // (3) 0.04883
/*50  */     vmstate_register_ram_global(ram);                                            // (18) 0.02734
/*52  */     /* ??? On a real system the first 1Mb is mapped as SSRAM or boot flash.  */  // (2) 0.04883
/*54  */     /* ??? RAM should repeat to fill physical memory space.  */                  // (13) 0.03125
/*56  */     /* SDRAM at address zero*/                                                   // (21) 0.02148
/*58  */     memory_region_add_subregion(address_space_mem, 0, ram);                      // (5) 0.04297
/*60  */     /* And again at address 0x80000000 */                                        // (20) 0.02539
/*62  */     memory_region_init_alias(ram_alias, NULL, "ram.alias", ram, 0, ram_size);    // (0) 0.05859
/*64  */     memory_region_add_subregion(address_space_mem, 0x80000000, ram_alias);       // (1) 0.05273
/*68  */     dev = qdev_create(NULL, TYPE_INTEGRATOR_CM);                                 // 0.0
/*70  */     qdev_prop_set_uint32(dev, "memsz", ram_size >> 20);                          // 0.0
/*72  */     qdev_init_nofail(dev);                                                       // 0.0
/*74  */     sysbus_mmio_map((SysBusDevice *)dev, 0, 0x10000000);                         // 0.0
/*78  */     dev = sysbus_create_varargs(TYPE_INTEGRATOR_PIC, 0x14000000,                 // 0.0
/*80  */                                 qdev_get_gpio_in(DEVICE(cpu), ARM_CPU_IRQ),      // 0.0
/*82  */                                 qdev_get_gpio_in(DEVICE(cpu), ARM_CPU_FIQ),      // 0.0
/*84  */                                 NULL);                                           // 0.0
/*86  */     for (i = 0; i < 32; i++) {                                                   // 0.0
/*88  */         pic[i] = qdev_get_gpio_in(dev, i);                                       // 0.0
/*90  */     }                                                                            // 0.0
/*92  */     sysbus_create_simple(TYPE_INTEGRATOR_PIC, 0xca000000, pic[26]);              // 0.0
/*94  */     sysbus_create_varargs("integrator_pit", 0x13000000,                          // 0.0
/*96  */                           pic[5], pic[6], pic[7], NULL);                         // 0.0
/*98  */     sysbus_create_simple("pl031", 0x15000000, pic[8]);                           // 0.0
/*100 */     sysbus_create_simple("pl011", 0x16000000, pic[1]);                           // 0.0
/*102 */     sysbus_create_simple("pl011", 0x17000000, pic[2]);                           // 0.0
/*104 */     icp_control_init(0xcb000000);                                                // 0.0
/*106 */     sysbus_create_simple("pl050_keyboard", 0x18000000, pic[3]);                  // 0.0
/*108 */     sysbus_create_simple("pl050_mouse", 0x19000000, pic[4]);                     // 0.0
/*111 */     sysbus_create_varargs("pl181", 0x1c000000, pic[23], pic[24], NULL);          // 0.0
/*113 */     if (nd_table[0].used)                                                        // 0.0
/*115 */         smc91c111_init(&nd_table[0], 0xc8000000, pic[27]);                       // 0.0
/*119 */     sysbus_create_simple("pl110", 0xc0000000, pic[22]);                          // 0.0
/*123 */     integrator_binfo.ram_size = ram_size;                                        // 0.0
/*125 */     integrator_binfo.kernel_filename = kernel_filename;                          // 0.0
/*127 */     integrator_binfo.kernel_cmdline = kernel_cmdline;                            // 0.0
/*129 */     integrator_binfo.initrd_filename = initrd_filename;                          // 0.0
/*131 */     arm_load_kernel(cpu, &integrator_binfo);                                     // 0.0
/*133 */ }                                                                                // 0.0
