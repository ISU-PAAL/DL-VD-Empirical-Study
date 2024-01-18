// commit message qemu@a8170e5e97 (target=0, prob=0.2837164, correct=True): Rename target_phys_addr_t to hwaddr
/*0   */ int load_multiboot(void *fw_cfg,                                                                   // (21) 0.0254
/*2   */                    FILE *f,                                                                        // (11) 0.04297
/*4   */                    const char *kernel_filename,                                                    // (8) 0.04882
/*6   */                    const char *initrd_filename,                                                    // (5) 0.05078
/*8   */                    const char *kernel_cmdline,                                                     // (4) 0.05078
/*10  */                    int kernel_file_size,                                                           // (6) 0.04883
/*12  */                    uint8_t *header)                                                                // (7) 0.04882
/*14  */ {                                                                                                  // (24) 0.001954
/*16  */     int i, is_multiboot = 0;                                                                       // (17) 0.02735
/*18  */     uint32_t flags = 0;                                                                            // (22) 0.02148
/*20  */     uint32_t mh_entry_addr;                                                                        // (20) 0.02734
/*22  */     uint32_t mh_load_addr;                                                                         // (18) 0.02734
/*24  */     uint32_t mb_kernel_size;                                                                       // (19) 0.02734
/*26  */     MultibootState mbs;                                                                            // (23) 0.01955
/*28  */     uint8_t bootinfo[MBI_SIZE];                                                                    // (16) 0.0293
/*30  */     uint8_t *mb_bootinfo_data;                                                                     // (15) 0.0293
/*34  */     /* Ok, let's see if it is a multiboot image.                                                   // (12) 0.03516
/*36  */        The header is 12x32bit long, so the latest entry may be 8192 - 48. */                       // (3) 0.05273
/*38  */     for (i = 0; i < (8192 - 48); i += 4) {                                                         // (10) 0.04297
/*40  */         if (ldl_p(header+i) == 0x1BADB002) {                                                       // (1) 0.05468
/*42  */             uint32_t checksum = ldl_p(header+i+8);                                                 // (0) 0.05664
/*44  */             flags = ldl_p(header+i+4);                                                             // (9) 0.04687
/*46  */             checksum += flags;                                                                     // (14) 0.03125
/*48  */             checksum += (uint32_t)0x1BADB002;                                                      // (2) 0.05468
/*50  */             if (!checksum) {                                                                       // (13) 0.0332
/*52  */                 is_multiboot = 1;                                                                  // 0.0
/*54  */                 break;                                                                             // 0.0
/*56  */             }                                                                                      // 0.0
/*58  */         }                                                                                          // 0.0
/*60  */     }                                                                                              // 0.0
/*64  */     if (!is_multiboot)                                                                             // 0.0
/*66  */         return 0; /* no multiboot */                                                               // 0.0
/*70  */     mb_debug("qemu: I believe we found a multiboot image!\n");                                     // 0.0
/*72  */     memset(bootinfo, 0, sizeof(bootinfo));                                                         // 0.0
/*74  */     memset(&mbs, 0, sizeof(mbs));                                                                  // 0.0
/*78  */     if (flags & 0x00000004) { /* MULTIBOOT_HEADER_HAS_VBE */                                       // 0.0
/*80  */         fprintf(stderr, "qemu: multiboot knows VBE. we don't.\n");                                 // 0.0
/*82  */     }                                                                                              // 0.0
/*84  */     if (!(flags & 0x00010000)) { /* MULTIBOOT_HEADER_HAS_ADDR */                                   // 0.0
/*86  */         uint64_t elf_entry;                                                                        // 0.0
/*88  */         uint64_t elf_low, elf_high;                                                                // 0.0
/*90  */         int kernel_size;                                                                           // 0.0
/*92  */         fclose(f);                                                                                 // 0.0
/*96  */         if (((struct elf64_hdr*)header)->e_machine == EM_X86_64) {                                 // 0.0
/*98  */             fprintf(stderr, "Cannot load x86-64 image, give a 32bit one.\n");                      // 0.0
/*100 */             exit(1);                                                                               // 0.0
/*102 */         }                                                                                          // 0.0
/*106 */         kernel_size = load_elf(kernel_filename, NULL, NULL, &elf_entry,                            // 0.0
/*108 */                                &elf_low, &elf_high, 0, ELF_MACHINE, 0);                            // 0.0
/*110 */         if (kernel_size < 0) {                                                                     // 0.0
/*112 */             fprintf(stderr, "Error while loading elf kernel\n");                                   // 0.0
/*114 */             exit(1);                                                                               // 0.0
/*116 */         }                                                                                          // 0.0
/*118 */         mh_load_addr = elf_low;                                                                    // 0.0
/*120 */         mb_kernel_size = elf_high - elf_low;                                                       // 0.0
/*122 */         mh_entry_addr = elf_entry;                                                                 // 0.0
/*126 */         mbs.mb_buf = g_malloc(mb_kernel_size);                                                     // 0.0
/*128 */         if (rom_copy(mbs.mb_buf, mh_load_addr, mb_kernel_size) != mb_kernel_size) {                // 0.0
/*130 */             fprintf(stderr, "Error while fetching elf kernel from rom\n");                         // 0.0
/*132 */             exit(1);                                                                               // 0.0
/*134 */         }                                                                                          // 0.0
/*138 */         mb_debug("qemu: loading multiboot-elf kernel (%#x bytes) with entry %#zx\n",               // 0.0
/*140 */                   mb_kernel_size, (size_t)mh_entry_addr);                                          // 0.0
/*142 */     } else {                                                                                       // 0.0
/*144 */         /* Valid if mh_flags sets MULTIBOOT_HEADER_HAS_ADDR. */                                    // 0.0
/*146 */         uint32_t mh_header_addr = ldl_p(header+i+12);                                              // 0.0
/*148 */         uint32_t mh_load_end_addr = ldl_p(header+i+20);                                            // 0.0
/*150 */         uint32_t mh_bss_end_addr = ldl_p(header+i+24);                                             // 0.0
/*152 */         mh_load_addr = ldl_p(header+i+16);                                                         // 0.0
/*154 */         uint32_t mb_kernel_text_offset = i - (mh_header_addr - mh_load_addr);                      // 0.0
/*156 */         uint32_t mb_load_size = 0;                                                                 // 0.0
/*158 */         mh_entry_addr = ldl_p(header+i+28);                                                        // 0.0
/*162 */         if (mh_load_end_addr) {                                                                    // 0.0
/*164 */             mb_kernel_size = mh_bss_end_addr - mh_load_addr;                                       // 0.0
/*166 */             mb_load_size = mh_load_end_addr - mh_load_addr;                                        // 0.0
/*168 */         } else {                                                                                   // 0.0
/*170 */             mb_kernel_size = kernel_file_size - mb_kernel_text_offset;                             // 0.0
/*172 */             mb_load_size = mb_kernel_size;                                                         // 0.0
/*174 */         }                                                                                          // 0.0
/*178 */         /* Valid if mh_flags sets MULTIBOOT_HEADER_HAS_VBE.                                        // 0.0
/*180 */         uint32_t mh_mode_type = ldl_p(header+i+32);                                                // 0.0
/*182 */         uint32_t mh_width = ldl_p(header+i+36);                                                    // 0.0
/*184 */         uint32_t mh_height = ldl_p(header+i+40);                                                   // 0.0
/*186 */         uint32_t mh_depth = ldl_p(header+i+44); */                                                 // 0.0
/*190 */         mb_debug("multiboot: mh_header_addr = %#x\n", mh_header_addr);                             // 0.0
/*192 */         mb_debug("multiboot: mh_load_addr = %#x\n", mh_load_addr);                                 // 0.0
/*194 */         mb_debug("multiboot: mh_load_end_addr = %#x\n", mh_load_end_addr);                         // 0.0
/*196 */         mb_debug("multiboot: mh_bss_end_addr = %#x\n", mh_bss_end_addr);                           // 0.0
/*198 */         mb_debug("qemu: loading multiboot kernel (%#x bytes) at %#x\n",                            // 0.0
/*200 */                  mb_load_size, mh_load_addr);                                                      // 0.0
/*204 */         mbs.mb_buf = g_malloc(mb_kernel_size);                                                     // 0.0
/*206 */         fseek(f, mb_kernel_text_offset, SEEK_SET);                                                 // 0.0
/*208 */         if (fread(mbs.mb_buf, 1, mb_load_size, f) != mb_load_size) {                               // 0.0
/*210 */             fprintf(stderr, "fread() failed\n");                                                   // 0.0
/*212 */             exit(1);                                                                               // 0.0
/*214 */         }                                                                                          // 0.0
/*216 */         memset(mbs.mb_buf + mb_load_size, 0, mb_kernel_size - mb_load_size);                       // 0.0
/*218 */         fclose(f);                                                                                 // 0.0
/*220 */     }                                                                                              // 0.0
/*224 */     mbs.mb_buf_phys = mh_load_addr;                                                                // 0.0
/*228 */     mbs.mb_buf_size = TARGET_PAGE_ALIGN(mb_kernel_size);                                           // 0.0
/*230 */     mbs.offset_mbinfo = mbs.mb_buf_size;                                                           // 0.0
/*234 */     /* Calculate space for cmdlines and mb_mods */                                                 // 0.0
/*236 */     mbs.mb_buf_size += strlen(kernel_filename) + 1;                                                // 0.0
/*238 */     mbs.mb_buf_size += strlen(kernel_cmdline) + 1;                                                 // 0.0
/*240 */     if (initrd_filename) {                                                                         // 0.0
/*242 */         const char *r = initrd_filename;                                                           // 0.0
/*244 */         mbs.mb_buf_size += strlen(r) + 1;                                                          // 0.0
/*246 */         mbs.mb_mods_avail = 1;                                                                     // 0.0
/*248 */         while (*(r = get_opt_value(NULL, 0, r))) {                                                 // 0.0
/*250 */            mbs.mb_mods_avail++;                                                                    // 0.0
/*252 */            r++;                                                                                    // 0.0
/*254 */         }                                                                                          // 0.0
/*256 */         mbs.mb_buf_size += MB_MOD_SIZE * mbs.mb_mods_avail;                                        // 0.0
/*258 */     }                                                                                              // 0.0
/*262 */     mbs.mb_buf_size = TARGET_PAGE_ALIGN(mbs.mb_buf_size);                                          // 0.0
/*266 */     /* enlarge mb_buf to hold cmdlines and mb-info structs */                                      // 0.0
/*268 */     mbs.mb_buf          = g_realloc(mbs.mb_buf, mbs.mb_buf_size);                                  // 0.0
/*270 */     mbs.offset_cmdlines = mbs.offset_mbinfo + mbs.mb_mods_avail * MB_MOD_SIZE;                     // 0.0
/*274 */     if (initrd_filename) {                                                                         // 0.0
/*276 */         char *next_initrd, not_last;                                                               // 0.0
/*280 */         mbs.offset_mods = mbs.mb_buf_size;                                                         // 0.0
/*284 */         do {                                                                                       // 0.0
/*286 */             char *next_space;                                                                      // 0.0
/*288 */             int mb_mod_length;                                                                     // 0.0
/*290 */             uint32_t offs = mbs.mb_buf_size;                                                       // 0.0
/*294 */             next_initrd = (char *)get_opt_value(NULL, 0, initrd_filename);                         // 0.0
/*296 */             not_last = *next_initrd;                                                               // 0.0
/*298 */             *next_initrd = '\0';                                                                   // 0.0
/*300 */             /* if a space comes after the module filename, treat everything                        // 0.0
/*302 */                after that as parameters */                                                         // 0.0
/*304 */             target_phys_addr_t c = mb_add_cmdline(&mbs, initrd_filename);                          // 0.0
/*306 */             if ((next_space = strchr(initrd_filename, ' ')))                                       // 0.0
/*308 */                 *next_space = '\0';                                                                // 0.0
/*310 */             mb_debug("multiboot loading module: %s\n", initrd_filename);                           // 0.0
/*312 */             mb_mod_length = get_image_size(initrd_filename);                                       // 0.0
/*314 */             if (mb_mod_length < 0) {                                                               // 0.0
/*316 */                 fprintf(stderr, "Failed to open file '%s'\n", initrd_filename);                    // 0.0
/*318 */                 exit(1);                                                                           // 0.0
/*320 */             }                                                                                      // 0.0
/*324 */             mbs.mb_buf_size = TARGET_PAGE_ALIGN(mb_mod_length + mbs.mb_buf_size);                  // 0.0
/*326 */             mbs.mb_buf = g_realloc(mbs.mb_buf, mbs.mb_buf_size);                                   // 0.0
/*330 */             load_image(initrd_filename, (unsigned char *)mbs.mb_buf + offs);                       // 0.0
/*332 */             mb_add_mod(&mbs, mbs.mb_buf_phys + offs,                                               // 0.0
/*334 */                        mbs.mb_buf_phys + offs + mb_mod_length, c);                                 // 0.0
/*338 */             mb_debug("mod_start: %p\nmod_end:   %p\n  cmdline: "TARGET_FMT_plx"\n",                // 0.0
/*340 */                      (char *)mbs.mb_buf + offs,                                                    // 0.0
/*342 */                      (char *)mbs.mb_buf + offs + mb_mod_length, c);                                // 0.0
/*344 */             initrd_filename = next_initrd+1;                                                       // 0.0
/*346 */         } while (not_last);                                                                        // 0.0
/*348 */     }                                                                                              // 0.0
/*352 */     /* Commandline support */                                                                      // 0.0
/*354 */     char kcmdline[strlen(kernel_filename) + strlen(kernel_cmdline) + 2];                           // 0.0
/*356 */     snprintf(kcmdline, sizeof(kcmdline), "%s %s",                                                  // 0.0
/*358 */              kernel_filename, kernel_cmdline);                                                     // 0.0
/*360 */     stl_p(bootinfo + MBI_CMDLINE, mb_add_cmdline(&mbs, kcmdline));                                 // 0.0
/*364 */     stl_p(bootinfo + MBI_MODS_ADDR,  mbs.mb_buf_phys + mbs.offset_mbinfo);                         // 0.0
/*366 */     stl_p(bootinfo + MBI_MODS_COUNT, mbs.mb_mods_count); /* mods_count */                          // 0.0
/*370 */     /* the kernel is where we want it to be now */                                                 // 0.0
/*372 */     stl_p(bootinfo + MBI_FLAGS, MULTIBOOT_FLAGS_MEMORY                                             // 0.0
/*374 */                                 | MULTIBOOT_FLAGS_BOOT_DEVICE                                      // 0.0
/*376 */                                 | MULTIBOOT_FLAGS_CMDLINE                                          // 0.0
/*378 */                                 | MULTIBOOT_FLAGS_MODULES                                          // 0.0
/*380 */                                 | MULTIBOOT_FLAGS_MMAP);                                           // 0.0
/*382 */     stl_p(bootinfo + MBI_MEM_LOWER,   640);                                                        // 0.0
/*384 */     stl_p(bootinfo + MBI_MEM_UPPER,   (ram_size / 1024) - 1024);                                   // 0.0
/*386 */     stl_p(bootinfo + MBI_BOOT_DEVICE, 0x8000ffff); /* XXX: use the -boot switch? */                // 0.0
/*388 */     stl_p(bootinfo + MBI_MMAP_ADDR,   ADDR_E820_MAP);                                              // 0.0
/*392 */     mb_debug("multiboot: mh_entry_addr = %#x\n", mh_entry_addr);                                   // 0.0
/*394 */     mb_debug("           mb_buf_phys   = "TARGET_FMT_plx"\n", mbs.mb_buf_phys);                    // 0.0
/*396 */     mb_debug("           mod_start     = "TARGET_FMT_plx"\n", mbs.mb_buf_phys + mbs.offset_mods);  // 0.0
/*398 */     mb_debug("           mb_mods_count = %d\n", mbs.mb_mods_count);                                // 0.0
/*402 */     /* save bootinfo off the stack */                                                              // 0.0
/*404 */     mb_bootinfo_data = g_malloc(sizeof(bootinfo));                                                 // 0.0
/*406 */     memcpy(mb_bootinfo_data, bootinfo, sizeof(bootinfo));                                          // 0.0
/*410 */     /* Pass variables to option rom */                                                             // 0.0
/*412 */     fw_cfg_add_i32(fw_cfg, FW_CFG_KERNEL_ENTRY, mh_entry_addr);                                    // 0.0
/*414 */     fw_cfg_add_i32(fw_cfg, FW_CFG_KERNEL_ADDR, mh_load_addr);                                      // 0.0
/*416 */     fw_cfg_add_i32(fw_cfg, FW_CFG_KERNEL_SIZE, mbs.mb_buf_size);                                   // 0.0
/*418 */     fw_cfg_add_bytes(fw_cfg, FW_CFG_KERNEL_DATA,                                                   // 0.0
/*420 */                      mbs.mb_buf, mbs.mb_buf_size);                                                 // 0.0
/*424 */     fw_cfg_add_i32(fw_cfg, FW_CFG_INITRD_ADDR, ADDR_MBI);                                          // 0.0
/*426 */     fw_cfg_add_i32(fw_cfg, FW_CFG_INITRD_SIZE, sizeof(bootinfo));                                  // 0.0
/*428 */     fw_cfg_add_bytes(fw_cfg, FW_CFG_INITRD_DATA, mb_bootinfo_data,                                 // 0.0
/*430 */                      sizeof(bootinfo));                                                            // 0.0
/*434 */     option_rom[nb_option_roms].name = "multiboot.bin";                                             // 0.0
/*436 */     option_rom[nb_option_roms].bootindex = 0;                                                      // 0.0
/*438 */     nb_option_roms++;                                                                              // 0.0
/*442 */     return 1; /* yes, we are multiboot */                                                          // 0.0
/*444 */ }                                                                                                  // 0.0
