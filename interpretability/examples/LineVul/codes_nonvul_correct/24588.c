// commit message qemu@619d11e463 (target=0, prob=0.2846033, correct=True): pc: initialize memory hotplug address space
/*0   */ FWCfgState *pc_memory_init(MemoryRegion *system_memory,                                           // (12) 0.03516
/*2   */                            const char *kernel_filename,                                           // (5) 0.06445
/*4   */                            const char *kernel_cmdline,                                            // (4) 0.06641
/*6   */                            const char *initrd_filename,                                           // (3) 0.06641
/*8   */                            ram_addr_t below_4g_mem_size,                                          // (0) 0.07812
/*10  */                            ram_addr_t above_4g_mem_size,                                          // (1) 0.07812
/*12  */                            MemoryRegion *rom_memory,                                              // (6) 0.06445
/*14  */                            MemoryRegion **ram_memory,                                             // (7) 0.06445
/*16  */                            PcGuestInfo *guest_info)                                               // (2) 0.07031
/*18  */ {                                                                                                 // (20) 0.001953
/*20  */     int linux_boot, i;                                                                            // (18) 0.01953
/*22  */     MemoryRegion *ram, *option_rom_mr;                                                            // (14) 0.0293
/*24  */     MemoryRegion *ram_below_4g, *ram_above_4g;                                                    // (8) 0.04102
/*26  */     FWCfgState *fw_cfg;                                                                           // (17) 0.02344
/*30  */     linux_boot = (kernel_filename != NULL);                                                       // (16) 0.02734
/*34  */     /* Allocate RAM.  We allocate it as a single memory region and use                            // (11) 0.03711
/*36  */      * aliases to address portions of it, mostly for backwards compatibility                      // (13) 0.03125
/*38  */      * with older qemus that used qemu_ram_alloc().                                               // (9) 0.03906
/*40  */      */                                                                                           // (19) 0.009766
/*42  */     ram = g_malloc(sizeof(*ram));                                                                 // (15) 0.0293
/*44  */     memory_region_init_ram(ram, NULL, "pc.ram",                                                   // (10) 0.03906
/*46  */                            below_4g_mem_size + above_4g_mem_size);                                // 0.0
/*48  */     vmstate_register_ram_global(ram);                                                             // 0.0
/*50  */     *ram_memory = ram;                                                                            // 0.0
/*52  */     ram_below_4g = g_malloc(sizeof(*ram_below_4g));                                               // 0.0
/*54  */     memory_region_init_alias(ram_below_4g, NULL, "ram-below-4g", ram,                             // 0.0
/*56  */                              0, below_4g_mem_size);                                               // 0.0
/*58  */     memory_region_add_subregion(system_memory, 0, ram_below_4g);                                  // 0.0
/*60  */     e820_add_entry(0, below_4g_mem_size, E820_RAM);                                               // 0.0
/*62  */     if (above_4g_mem_size > 0) {                                                                  // 0.0
/*64  */         ram_above_4g = g_malloc(sizeof(*ram_above_4g));                                           // 0.0
/*66  */         memory_region_init_alias(ram_above_4g, NULL, "ram-above-4g", ram,                         // 0.0
/*68  */                                  below_4g_mem_size, above_4g_mem_size);                           // 0.0
/*70  */         memory_region_add_subregion(system_memory, 0x100000000ULL,                                // 0.0
/*72  */                                     ram_above_4g);                                                // 0.0
/*74  */         e820_add_entry(0x100000000ULL, above_4g_mem_size, E820_RAM);                              // 0.0
/*76  */     }                                                                                             // 0.0
/*82  */     /* Initialize PC system firmware */                                                           // 0.0
/*84  */     pc_system_firmware_init(rom_memory, guest_info->isapc_ram_fw);                                // 0.0
/*88  */     option_rom_mr = g_malloc(sizeof(*option_rom_mr));                                             // 0.0
/*90  */     memory_region_init_ram(option_rom_mr, NULL, "pc.rom", PC_ROM_SIZE);                           // 0.0
/*92  */     vmstate_register_ram_global(option_rom_mr);                                                   // 0.0
/*94  */     memory_region_add_subregion_overlap(rom_memory,                                               // 0.0
/*96  */                                         PC_ROM_MIN_VGA,                                           // 0.0
/*98  */                                         option_rom_mr,                                            // 0.0
/*100 */                                         1);                                                       // 0.0
/*104 */     fw_cfg = bochs_bios_init();                                                                   // 0.0
/*106 */     rom_set_fw(fw_cfg);                                                                           // 0.0
/*110 */     if (linux_boot) {                                                                             // 0.0
/*112 */         load_linux(fw_cfg, kernel_filename, initrd_filename, kernel_cmdline, below_4g_mem_size);  // 0.0
/*114 */     }                                                                                             // 0.0
/*118 */     for (i = 0; i < nb_option_roms; i++) {                                                        // 0.0
/*120 */         rom_add_option(option_rom[i].name, option_rom[i].bootindex);                              // 0.0
/*122 */     }                                                                                             // 0.0
/*124 */     guest_info->fw_cfg = fw_cfg;                                                                  // 0.0
/*126 */     return fw_cfg;                                                                                // 0.0
/*128 */ }                                                                                                 // 0.0
