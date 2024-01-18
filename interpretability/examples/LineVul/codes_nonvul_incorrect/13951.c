// commit message qemu@4be746345f (target=0, prob=0.5339907, correct=False): hw: Convert from BlockDriverState to BlockBackend, mostly
/*0   */ static void taihu_405ep_init(MachineState *machine)                              // (11) 0.03125
/*2   */ {                                                                                // (26) 0.001953
/*4   */     ram_addr_t ram_size = machine->ram_size;                                     // (9) 0.03516
/*6   */     const char *kernel_filename = machine->kernel_filename;                      // (13) 0.03125
/*8   */     const char *initrd_filename = machine->initrd_filename;                      // (10) 0.03516
/*10  */     char *filename;                                                              // (25) 0.01367
/*12  */     qemu_irq *pic;                                                               // (19) 0.02344
/*14  */     MemoryRegion *sysmem = get_system_memory();                                  // (15) 0.0293
/*16  */     MemoryRegion *bios;                                                          // (22) 0.01758
/*18  */     MemoryRegion *ram_memories = g_malloc(2 * sizeof(*ram_memories));            // (4) 0.04883
/*20  */     MemoryRegion *ram = g_malloc0(sizeof(*ram));                                 // (7) 0.03711
/*22  */     hwaddr ram_bases[2], ram_sizes[2];                                           // (5) 0.03906
/*24  */     long bios_size;                                                              // (24) 0.01563
/*26  */     target_ulong kernel_base, initrd_base;                                       // (12) 0.03125
/*28  */     long kernel_size, initrd_size;                                               // (17) 0.02539
/*30  */     int linux_boot;                                                              // (23) 0.01563
/*32  */     int fl_idx, fl_sectors;                                                      // (16) 0.02734
/*34  */     DriveInfo *dinfo;                                                            // (21) 0.01758
/*38  */     /* RAM is soldered to the board so the size cannot be changed */             // (8) 0.03516
/*40  */     ram_size = 0x08000000;                                                       // (20) 0.02344
/*42  */     memory_region_allocate_system_memory(ram, NULL, "taihu_405ep.ram",           // (3) 0.05469
/*44  */                                          ram_size);                              // (1) 0.08594
/*48  */     ram_bases[0] = 0;                                                            // (18) 0.02539
/*50  */     ram_sizes[0] = 0x04000000;                                                   // (14) 0.03125
/*52  */     memory_region_init_alias(&ram_memories[0], NULL,                             // (6) 0.03906
/*54  */                              "taihu_405ep.ram-0", ram, ram_bases[0],             // (0) 0.0957
/*56  */                              ram_sizes[0]);                                      // (2) 0.06836
/*58  */     ram_bases[1] = 0x04000000;                                                   // 0.0
/*60  */     ram_sizes[1] = 0x04000000;                                                   // 0.0
/*62  */     memory_region_init_alias(&ram_memories[1], NULL,                             // 0.0
/*64  */                              "taihu_405ep.ram-1", ram, ram_bases[1],             // 0.0
/*66  */                              ram_sizes[1]);                                      // 0.0
/*68  */ #ifdef DEBUG_BOARD_INIT                                                          // 0.0
/*70  */     printf("%s: register cpu\n", __func__);                                      // 0.0
/*72  */ #endif                                                                           // 0.0
/*74  */     ppc405ep_init(sysmem, ram_memories, ram_bases, ram_sizes,                    // 0.0
/*76  */                   33333333, &pic, kernel_filename == NULL ? 0 : 1);              // 0.0
/*78  */     /* allocate and load BIOS */                                                 // 0.0
/*80  */ #ifdef DEBUG_BOARD_INIT                                                          // 0.0
/*82  */     printf("%s: register BIOS\n", __func__);                                     // 0.0
/*84  */ #endif                                                                           // 0.0
/*86  */     fl_idx = 0;                                                                  // 0.0
/*88  */ #if defined(USE_FLASH_BIOS)                                                      // 0.0
/*90  */     dinfo = drive_get(IF_PFLASH, 0, fl_idx);                                     // 0.0
/*92  */     if (dinfo) {                                                                 // 0.0
/*94  */         BlockDriverState *bs = blk_bs(blk_by_legacy_dinfo(dinfo));               // 0.0
/*98  */         bios_size = bdrv_getlength(bs);                                          // 0.0
/*100 */         /* XXX: should check that size is 2MB */                                 // 0.0
/*102 */         //        bios_size = 2 * 1024 * 1024;                                   // 0.0
/*104 */         fl_sectors = (bios_size + 65535) >> 16;                                  // 0.0
/*106 */ #ifdef DEBUG_BOARD_INIT                                                          // 0.0
/*108 */         printf("Register parallel flash %d size %lx"                             // 0.0
/*110 */                " at addr %lx '%s' %d\n",                                         // 0.0
/*112 */                fl_idx, bios_size, -bios_size,                                    // 0.0
/*114 */                bdrv_get_device_name(bs), fl_sectors);                            // 0.0
/*116 */ #endif                                                                           // 0.0
/*118 */         pflash_cfi02_register((uint32_t)(-bios_size),                            // 0.0
/*120 */                               NULL, "taihu_405ep.bios", bios_size,               // 0.0
/*122 */                               bs, 65536, fl_sectors, 1,                          // 0.0
/*124 */                               4, 0x0001, 0x22DA, 0x0000, 0x0000, 0x555, 0x2AA,   // 0.0
/*126 */                               1);                                                // 0.0
/*128 */         fl_idx++;                                                                // 0.0
/*130 */     } else                                                                       // 0.0
/*132 */ #endif                                                                           // 0.0
/*134 */     {                                                                            // 0.0
/*136 */ #ifdef DEBUG_BOARD_INIT                                                          // 0.0
/*138 */         printf("Load BIOS from file\n");                                         // 0.0
/*140 */ #endif                                                                           // 0.0
/*142 */         if (bios_name == NULL)                                                   // 0.0
/*144 */             bios_name = BIOS_FILENAME;                                           // 0.0
/*146 */         bios = g_new(MemoryRegion, 1);                                           // 0.0
/*148 */         memory_region_init_ram(bios, NULL, "taihu_405ep.bios", BIOS_SIZE,        // 0.0
/*150 */                                &error_abort);                                    // 0.0
/*152 */         vmstate_register_ram_global(bios);                                       // 0.0
/*154 */         filename = qemu_find_file(QEMU_FILE_TYPE_BIOS, bios_name);               // 0.0
/*156 */         if (filename) {                                                          // 0.0
/*158 */             bios_size = load_image(filename, memory_region_get_ram_ptr(bios));   // 0.0
/*160 */             g_free(filename);                                                    // 0.0
/*162 */             if (bios_size < 0 || bios_size > BIOS_SIZE) {                        // 0.0
/*164 */                 error_report("Could not load PowerPC BIOS '%s'", bios_name);     // 0.0
/*166 */                 exit(1);                                                         // 0.0
/*168 */             }                                                                    // 0.0
/*170 */             bios_size = (bios_size + 0xfff) & ~0xfff;                            // 0.0
/*172 */             memory_region_add_subregion(sysmem, (uint32_t)(-bios_size), bios);   // 0.0
/*174 */         } else if (!qtest_enabled()) {                                           // 0.0
/*176 */             error_report("Could not load PowerPC BIOS '%s'", bios_name);         // 0.0
/*178 */             exit(1);                                                             // 0.0
/*180 */         }                                                                        // 0.0
/*182 */         memory_region_set_readonly(bios, true);                                  // 0.0
/*184 */     }                                                                            // 0.0
/*186 */     /* Register Linux flash */                                                   // 0.0
/*188 */     dinfo = drive_get(IF_PFLASH, 0, fl_idx);                                     // 0.0
/*190 */     if (dinfo) {                                                                 // 0.0
/*192 */         BlockDriverState *bs = blk_bs(blk_by_legacy_dinfo(dinfo));               // 0.0
/*196 */         bios_size = bdrv_getlength(bs);                                          // 0.0
/*198 */         /* XXX: should check that size is 32MB */                                // 0.0
/*200 */         bios_size = 32 * 1024 * 1024;                                            // 0.0
/*202 */         fl_sectors = (bios_size + 65535) >> 16;                                  // 0.0
/*204 */ #ifdef DEBUG_BOARD_INIT                                                          // 0.0
/*206 */         printf("Register parallel flash %d size %lx"                             // 0.0
/*208 */                " at addr " TARGET_FMT_lx " '%s'\n",                              // 0.0
/*210 */                fl_idx, bios_size, (target_ulong)0xfc000000,                      // 0.0
/*212 */                bdrv_get_device_name(bs));                                        // 0.0
/*214 */ #endif                                                                           // 0.0
/*216 */         pflash_cfi02_register(0xfc000000, NULL, "taihu_405ep.flash", bios_size,  // 0.0
/*218 */                               bs, 65536, fl_sectors, 1,                          // 0.0
/*220 */                               4, 0x0001, 0x22DA, 0x0000, 0x0000, 0x555, 0x2AA,   // 0.0
/*222 */                               1);                                                // 0.0
/*224 */         fl_idx++;                                                                // 0.0
/*226 */     }                                                                            // 0.0
/*228 */     /* Register CLPD & LCD display */                                            // 0.0
/*230 */ #ifdef DEBUG_BOARD_INIT                                                          // 0.0
/*232 */     printf("%s: register CPLD\n", __func__);                                     // 0.0
/*234 */ #endif                                                                           // 0.0
/*236 */     taihu_cpld_init(sysmem, 0x50100000);                                         // 0.0
/*238 */     /* Load kernel */                                                            // 0.0
/*240 */     linux_boot = (kernel_filename != NULL);                                      // 0.0
/*242 */     if (linux_boot) {                                                            // 0.0
/*244 */ #ifdef DEBUG_BOARD_INIT                                                          // 0.0
/*246 */         printf("%s: load kernel\n", __func__);                                   // 0.0
/*248 */ #endif                                                                           // 0.0
/*250 */         kernel_base = KERNEL_LOAD_ADDR;                                          // 0.0
/*252 */         /* now we can load the kernel */                                         // 0.0
/*254 */         kernel_size = load_image_targphys(kernel_filename, kernel_base,          // 0.0
/*256 */                                           ram_size - kernel_base);               // 0.0
/*258 */         if (kernel_size < 0) {                                                   // 0.0
/*260 */             fprintf(stderr, "qemu: could not load kernel '%s'\n",                // 0.0
/*262 */                     kernel_filename);                                            // 0.0
/*264 */             exit(1);                                                             // 0.0
/*266 */         }                                                                        // 0.0
/*268 */         /* load initrd */                                                        // 0.0
/*270 */         if (initrd_filename) {                                                   // 0.0
/*272 */             initrd_base = INITRD_LOAD_ADDR;                                      // 0.0
/*274 */             initrd_size = load_image_targphys(initrd_filename, initrd_base,      // 0.0
/*276 */                                               ram_size - initrd_base);           // 0.0
/*278 */             if (initrd_size < 0) {                                               // 0.0
/*280 */                 fprintf(stderr,                                                  // 0.0
/*282 */                         "qemu: could not load initial ram disk '%s'\n",          // 0.0
/*284 */                         initrd_filename);                                        // 0.0
/*286 */                 exit(1);                                                         // 0.0
/*288 */             }                                                                    // 0.0
/*290 */         } else {                                                                 // 0.0
/*292 */             initrd_base = 0;                                                     // 0.0
/*294 */             initrd_size = 0;                                                     // 0.0
/*296 */         }                                                                        // 0.0
/*298 */     } else {                                                                     // 0.0
/*300 */         kernel_base = 0;                                                         // 0.0
/*302 */         kernel_size = 0;                                                         // 0.0
/*304 */         initrd_base = 0;                                                         // 0.0
/*306 */         initrd_size = 0;                                                         // 0.0
/*308 */     }                                                                            // 0.0
/*310 */ #ifdef DEBUG_BOARD_INIT                                                          // 0.0
/*312 */     printf("%s: Done\n", __func__);                                              // 0.0
/*314 */ #endif                                                                           // 0.0
/*316 */ }                                                                                // 0.0
