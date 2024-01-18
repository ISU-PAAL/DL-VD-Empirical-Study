// commit message qemu@4be746345f (target=0, prob=0.15175484, correct=True): hw: Convert from BlockDriverState to BlockBackend, mostly
/*0  */ static void verdex_init(MachineState *machine)                                     // (14) 0.02539
/*2  */ {                                                                                  // (25) 0.001953
/*4  */     const char *cpu_model = machine->cpu_model;                                    // (12) 0.03125
/*6  */     PXA2xxState *cpu;                                                              // (16) 0.02344
/*8  */     DriveInfo *dinfo;                                                              // (18) 0.01758
/*10 */     int be;                                                                        // (21) 0.01172
/*12 */     MemoryRegion *address_space_mem = get_system_memory();                         // (9) 0.03516
/*16 */     uint32_t verdex_rom = 0x02000000;                                              // (10) 0.03516
/*18 */     uint32_t verdex_ram = 0x10000000;                                              // (11) 0.03516
/*22 */     cpu = pxa270_init(address_space_mem, verdex_ram, cpu_model ?: "pxa270-c0");    // (3) 0.07031
/*26 */     dinfo = drive_get(IF_PFLASH, 0, 0);                                            // (8) 0.03906
/*28 */     if (!dinfo && !qtest_enabled()) {                                              // (13) 0.0293
/*30 */         fprintf(stderr, "A flash image must be given with the "                    // (6) 0.04688
/*32 */                 "'pflash' parameter\n");                                           // (7) 0.04492
/*34 */         exit(1);                                                                   // (17) 0.02148
/*36 */     }                                                                              // (22) 0.007813
/*40 */ #ifdef TARGET_WORDS_BIGENDIAN                                                      // (15) 0.02539
/*42 */     be = 1;                                                                        // (20) 0.01367
/*44 */ #else                                                                              // (24) 0.003906
/*46 */     be = 0;                                                                        // (19) 0.01367
/*48 */ #endif                                                                             // (23) 0.003906
/*50 */     if (!pflash_cfi01_register(0x00000000, NULL, "verdex.rom", verdex_rom,         // (4) 0.06445
/*52 */                                dinfo ? blk_bs(blk_by_legacy_dinfo(dinfo)) : NULL,  // (0) 0.1074
/*54 */                                sector_len, verdex_rom / sector_len,                // (1) 0.08594
/*56 */                                2, 0, 0, 0, 0, be)) {                               // (2) 0.08398
/*58 */         fprintf(stderr, "qemu: Error registering flash memory.\n");                // (5) 0.05273
/*60 */         exit(1);                                                                   // 0.0
/*62 */     }                                                                              // 0.0
/*66 */     /* Interrupt line of NIC is connected to GPIO line 99 */                       // 0.0
/*68 */     smc91c111_init(&nd_table[0], 0x04000300,                                       // 0.0
/*70 */                     qdev_get_gpio_in(cpu->gpio, 99));                              // 0.0
/*72 */ }                                                                                  // 0.0
