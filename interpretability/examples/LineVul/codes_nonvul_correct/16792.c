// commit message qemu@4be746345f (target=0, prob=0.25986117, correct=True): hw: Convert from BlockDriverState to BlockBackend, mostly
/*0  */ static void connex_init(MachineState *machine)                                     // (15) 0.02344
/*2  */ {                                                                                  // (27) 0.001953
/*4  */     PXA2xxState *cpu;                                                              // (16) 0.02344
/*6  */     DriveInfo *dinfo;                                                              // (19) 0.01758
/*8  */     int be;                                                                        // (22) 0.01172
/*10 */     MemoryRegion *address_space_mem = get_system_memory();                         // (9) 0.03516
/*14 */     uint32_t connex_rom = 0x01000000;                                              // (10) 0.0332
/*16 */     uint32_t connex_ram = 0x04000000;                                              // (11) 0.0332
/*20 */     cpu = pxa255_init(address_space_mem, connex_ram);                              // (7) 0.04297
/*24 */     dinfo = drive_get(IF_PFLASH, 0, 0);                                            // (8) 0.03906
/*26 */     if (!dinfo && !qtest_enabled()) {                                              // (13) 0.0293
/*28 */         fprintf(stderr, "A flash image must be given with the "                    // (5) 0.04687
/*30 */                 "'pflash' parameter\n");                                           // (6) 0.04492
/*32 */         exit(1);                                                                   // (18) 0.02148
/*34 */     }                                                                              // (24) 0.007812
/*38 */ #ifdef TARGET_WORDS_BIGENDIAN                                                      // (14) 0.02539
/*40 */     be = 1;                                                                        // (20) 0.01367
/*42 */ #else                                                                              // (26) 0.003906
/*44 */     be = 0;                                                                        // (21) 0.01367
/*46 */ #endif                                                                             // (25) 0.003906
/*48 */     if (!pflash_cfi01_register(0x00000000, NULL, "connext.rom", connex_rom,        // (3) 0.06055
/*50 */                                dinfo ? blk_bs(blk_by_legacy_dinfo(dinfo)) : NULL,  // (0) 0.1074
/*52 */                                sector_len, connex_rom / sector_len,                // (1) 0.08398
/*54 */                                2, 0, 0, 0, 0, be)) {                               // (2) 0.08398
/*56 */         fprintf(stderr, "qemu: Error registering flash memory.\n");                // (4) 0.05273
/*58 */         exit(1);                                                                   // (17) 0.02148
/*60 */     }                                                                              // (23) 0.007812
/*64 */     /* Interrupt line of NIC is connected to GPIO line 36 */                       // (12) 0.03125
/*66 */     smc91c111_init(&nd_table[0], 0x04000300,                                       // 0.0
/*68 */                     qdev_get_gpio_in(cpu->gpio, 36));                              // 0.0
/*70 */ }                                                                                  // 0.0
