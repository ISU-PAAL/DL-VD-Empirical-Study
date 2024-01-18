// commit message qemu@4be746345f (target=0, prob=0.19903497, correct=True): hw: Convert from BlockDriverState to BlockBackend, mostly
/*0   */ static void mainstone_common_init(MemoryRegion *address_space_mem,               // (8) 0.03516
/*2   */                                   MachineState *machine,                         // (1) 0.07422
/*4   */                                   enum mainstone_model_e model, int arm_id)      // (0) 0.0918
/*6   */ {                                                                                // (28) 0.001953
/*8   */     uint32_t sector_len = 256 * 1024;                                            // (14) 0.0293
/*10  */     hwaddr mainstone_flash_base[] = { MST_FLASH_0, MST_FLASH_1 };                // (4) 0.06055
/*12  */     PXA2xxState *mpu;                                                            // (17) 0.02539
/*14  */     DeviceState *mst_irq;                                                        // (18) 0.02344
/*16  */     DriveInfo *dinfo;                                                            // (20) 0.01758
/*18  */     int i;                                                                       // (25) 0.01172
/*20  */     int be;                                                                      // (24) 0.01172
/*22  */     MemoryRegion *rom = g_new(MemoryRegion, 1);                                  // (10) 0.0332
/*24  */     const char *cpu_model = machine->cpu_model;                                  // (12) 0.03125
/*28  */     if (!cpu_model)                                                              // (21) 0.01758
/*30  */         cpu_model = "pxa270-c5";                                                 // (7) 0.03711
/*34  */     /* Setup CPU & memory */                                                     // (19) 0.01758
/*36  */     mpu = pxa270_init(address_space_mem, mainstone_binfo.ram_size, cpu_model);   // (3) 0.0625
/*38  */     memory_region_init_ram(rom, NULL, "mainstone.rom", MAINSTONE_ROM,            // (5) 0.05273
/*40  */                            &error_abort);                                        // (2) 0.0625
/*42  */     vmstate_register_ram_global(rom);                                            // (15) 0.02734
/*44  */     memory_region_set_readonly(rom, true);                                       // (13) 0.03125
/*46  */     memory_region_add_subregion(address_space_mem, 0, rom);                      // (6) 0.04297
/*50  */ #ifdef TARGET_WORDS_BIGENDIAN                                                    // (16) 0.02539
/*52  */     be = 1;                                                                      // (23) 0.01367
/*54  */ #else                                                                            // (27) 0.003906
/*56  */     be = 0;                                                                      // (22) 0.01367
/*58  */ #endif                                                                           // (26) 0.003906
/*60  */     /* There are two 32MiB flash devices on the board */                         // (11) 0.03125
/*62  */     for (i = 0; i < 2; i ++) {                                                   // (9) 0.0332
/*64  */         dinfo = drive_get(IF_PFLASH, 0, i);                                      // 0.0
/*66  */         if (!dinfo) {                                                            // 0.0
/*68  */             if (qtest_enabled()) {                                               // 0.0
/*70  */                 break;                                                           // 0.0
/*72  */             }                                                                    // 0.0
/*74  */             fprintf(stderr, "Two flash images must be given with the "           // 0.0
/*76  */                     "'pflash' parameter\n");                                     // 0.0
/*78  */             exit(1);                                                             // 0.0
/*80  */         }                                                                        // 0.0
/*84  */         if (!pflash_cfi01_register(mainstone_flash_base[i], NULL,                // 0.0
/*86  */                                    i ? "mainstone.flash1" : "mainstone.flash0",  // 0.0
/*88  */                                    MAINSTONE_FLASH,                              // 0.0
/*90  */                                    blk_bs(blk_by_legacy_dinfo(dinfo)),           // 0.0
/*92  */                                    sector_len, MAINSTONE_FLASH / sector_len,     // 0.0
/*94  */                                    4, 0, 0, 0, 0, be)) {                         // 0.0
/*96  */             fprintf(stderr, "qemu: Error registering flash memory.\n");          // 0.0
/*98  */             exit(1);                                                             // 0.0
/*100 */         }                                                                        // 0.0
/*102 */     }                                                                            // 0.0
/*106 */     mst_irq = sysbus_create_simple("mainstone-fpga", MST_FPGA_PHYS,              // 0.0
/*108 */                     qdev_get_gpio_in(mpu->gpio, 0));                             // 0.0
/*112 */     /* setup keypad */                                                           // 0.0
/*114 */     pxa27x_register_keypad(mpu->kp, map, 0xe0);                                  // 0.0
/*118 */     /* MMC/SD host */                                                            // 0.0
/*120 */     pxa2xx_mmci_handlers(mpu->mmc, NULL, qdev_get_gpio_in(mst_irq, MMC_IRQ));    // 0.0
/*124 */     pxa2xx_pcmcia_set_irq_cb(mpu->pcmcia[0],                                     // 0.0
/*126 */             qdev_get_gpio_in(mst_irq, S0_IRQ),                                   // 0.0
/*128 */             qdev_get_gpio_in(mst_irq, S0_CD_IRQ));                               // 0.0
/*130 */     pxa2xx_pcmcia_set_irq_cb(mpu->pcmcia[1],                                     // 0.0
/*132 */             qdev_get_gpio_in(mst_irq, S1_IRQ),                                   // 0.0
/*134 */             qdev_get_gpio_in(mst_irq, S1_CD_IRQ));                               // 0.0
/*138 */     smc91c111_init(&nd_table[0], MST_ETH_PHYS,                                   // 0.0
/*140 */                     qdev_get_gpio_in(mst_irq, ETHERNET_IRQ));                    // 0.0
/*144 */     mainstone_binfo.kernel_filename = machine->kernel_filename;                  // 0.0
/*146 */     mainstone_binfo.kernel_cmdline = machine->kernel_cmdline;                    // 0.0
/*148 */     mainstone_binfo.initrd_filename = machine->initrd_filename;                  // 0.0
/*150 */     mainstone_binfo.board_id = arm_id;                                           // 0.0
/*152 */     arm_load_kernel(mpu->cpu, &mainstone_binfo);                                 // 0.0
/*154 */ }                                                                                // 0.0
