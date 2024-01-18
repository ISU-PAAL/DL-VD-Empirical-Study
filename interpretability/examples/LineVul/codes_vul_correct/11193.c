// commit message qemu@f8ed85ac99 (target=1, prob=0.54637766, correct=True): Fix bad error handling after memory_region_init_ram()
/*0  */ static void tosa_init(MachineState *machine)                                // (21) 0.02344
/*2  */ {                                                                           // (24) 0.001954
/*4  */     const char *cpu_model = machine->cpu_model;                             // (12) 0.03125
/*6  */     const char *kernel_filename = machine->kernel_filename;                 // (13) 0.03125
/*8  */     const char *kernel_cmdline = machine->kernel_cmdline;                   // (10) 0.03516
/*10 */     const char *initrd_filename = machine->initrd_filename;                 // (8) 0.03516
/*12 */     MemoryRegion *address_space_mem = get_system_memory();                  // (9) 0.03516
/*14 */     MemoryRegion *rom = g_new(MemoryRegion, 1);                             // (11) 0.0332
/*16 */     PXA2xxState *mpu;                                                       // (19) 0.02539
/*18 */     TC6393xbState *tmio;                                                    // (22) 0.02344
/*20 */     DeviceState *scp0, *scp1;                                               // (16) 0.0293
/*24 */     if (!cpu_model)                                                         // (23) 0.01758
/*26 */         cpu_model = "pxa255";                                               // (14) 0.03125
/*30 */     mpu = pxa255_init(address_space_mem, tosa_binfo.ram_size);              // (2) 0.05469
/*34 */     memory_region_init_ram(rom, NULL, "tosa.rom", TOSA_ROM, &error_abort);  // (1) 0.06445
/*36 */     vmstate_register_ram_global(rom);                                       // (17) 0.02734
/*38 */     memory_region_set_readonly(rom, true);                                  // (15) 0.03125
/*40 */     memory_region_add_subregion(address_space_mem, 0, rom);                 // (7) 0.04297
/*44 */     tmio = tc6393xb_init(address_space_mem, 0x10000000,                     // (6) 0.04883
/*46 */             qdev_get_gpio_in(mpu->gpio, TOSA_GPIO_TC6393XB_INT));           // (0) 0.08203
/*50 */     scp0 = sysbus_create_simple("scoop", 0x08800000, NULL);                 // (5) 0.05078
/*52 */     scp1 = sysbus_create_simple("scoop", 0x14800040, NULL);                 // (4) 0.05078
/*56 */     tosa_gpio_setup(mpu, scp0, scp1, tmio);                                 // (3) 0.05078
/*60 */     tosa_microdrive_attach(mpu);                                            // (18) 0.02734
/*64 */     tosa_tg_init(mpu);                                                      // (20) 0.02539
/*68 */     tosa_binfo.kernel_filename = kernel_filename;                           // 0.0
/*70 */     tosa_binfo.kernel_cmdline = kernel_cmdline;                             // 0.0
/*72 */     tosa_binfo.initrd_filename = initrd_filename;                           // 0.0
/*74 */     tosa_binfo.board_id = 0x208;                                            // 0.0
/*76 */     arm_load_kernel(mpu->cpu, &tosa_binfo);                                 // 0.0
/*78 */     sl_bootparam_write(SL_PXA_PARAM_BASE);                                  // 0.0
/*80 */ }                                                                           // 0.0
