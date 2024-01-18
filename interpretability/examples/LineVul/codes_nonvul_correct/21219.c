// commit message qemu@7b527b86eb (target=0, prob=0.27089018, correct=True): s390x/ipl: remove dead code
/*0   */ static int s390_ipl_init(SysBusDevice *dev)                                       // (14) 0.0293
/*2   */ {                                                                                 // (24) 0.001954
/*4   */     S390IPLState *ipl = S390_IPL(dev);                                            // (8) 0.03711
/*6   */     uint64_t pentry = KERN_IMAGE_START;                                           // (9) 0.03711
/*8   */     int kernel_size;                                                              // (18) 0.01562
/*12  */     int bios_size;                                                                // (19) 0.01562
/*14  */     char *bios_filename;                                                          // (17) 0.01953
/*18  */     /*                                                                            // (23) 0.007812
/*20  */      * Always load the bios if it was enforced,                                   // (15) 0.02734
/*22  */      * even if an external kernel has been defined.                               // (16) 0.02734
/*24  */      */                                                                           // (22) 0.009766
/*26  */     if (!ipl->kernel || ipl->enforce_bios) {                                      // (10) 0.03711
/*28  */         uint64_t fwbase = (MIN(ram_size, 0x80000000U) - 0x200000) & ~0xffffUL;    // (1) 0.07812
/*32  */         if (bios_name == NULL) {                                                  // (13) 0.0332
/*34  */             bios_name = ipl->firmware;                                            // (6) 0.04297
/*36  */         }                                                                         // (21) 0.01562
/*40  */         bios_filename = qemu_find_file(QEMU_FILE_TYPE_BIOS, bios_name);           // (3) 0.06641
/*42  */         if (bios_filename == NULL) {                                              // (12) 0.0332
/*44  */             hw_error("could not find stage1 bootloader\n");                       // (5) 0.05078
/*46  */         }                                                                         // (20) 0.01562
/*50  */         bios_size = load_elf(bios_filename, bios_translate_addr, &fwbase,         // (4) 0.06055
/*52  */                              &ipl->bios_start_addr, NULL, NULL, 1,                // (0) 0.08594
/*54  */                              ELF_MACHINE, 0);                                     // (2) 0.07227
/*56  */         if (bios_size > 0) {                                                      // (11) 0.0332
/*58  */             /* Adjust ELF start address to final location */                      // (7) 0.04102
/*60  */             ipl->bios_start_addr += fwbase;                                       // 0.0
/*62  */         } else {                                                                  // 0.0
/*64  */             /* Try to load non-ELF file (e.g. s390-zipl.rom) */                   // 0.0
/*66  */             bios_size = load_image_targphys(bios_filename, ZIPL_IMAGE_START,      // 0.0
/*68  */                                             4096);                                // 0.0
/*70  */             ipl->bios_start_addr = ZIPL_IMAGE_START;                              // 0.0
/*72  */             if (bios_size > 4096) {                                               // 0.0
/*74  */                 hw_error("stage1 bootloader is > 4k\n");                          // 0.0
/*76  */             }                                                                     // 0.0
/*78  */         }                                                                         // 0.0
/*80  */         g_free(bios_filename);                                                    // 0.0
/*84  */         if (bios_size == -1) {                                                    // 0.0
/*86  */             hw_error("could not load bootloader '%s'\n", bios_name);              // 0.0
/*88  */         }                                                                         // 0.0
/*92  */         /* default boot target is the bios */                                     // 0.0
/*94  */         ipl->start_addr = ipl->bios_start_addr;                                   // 0.0
/*96  */     }                                                                             // 0.0
/*100 */     if (ipl->kernel) {                                                            // 0.0
/*102 */         kernel_size = load_elf(ipl->kernel, NULL, NULL, &pentry, NULL,            // 0.0
/*104 */                                NULL, 1, ELF_MACHINE, 0);                          // 0.0
/*106 */         if (kernel_size < 0) {                                                    // 0.0
/*108 */             kernel_size = load_image_targphys(ipl->kernel, 0, ram_size);          // 0.0
/*110 */         }                                                                         // 0.0
/*112 */         if (kernel_size < 0) {                                                    // 0.0
/*114 */             fprintf(stderr, "could not load kernel '%s'\n", ipl->kernel);         // 0.0
/*116 */             return -1;                                                            // 0.0
/*118 */         }                                                                         // 0.0
/*120 */         /*                                                                        // 0.0
/*122 */          * Is it a Linux kernel (starting at 0x10000)? If yes, we fill in the     // 0.0
/*124 */          * kernel parameters here as well. Note: For old kernels (up to 3.2)      // 0.0
/*126 */          * we can not rely on the ELF entry point - it was 0x800 (the SALIPL      // 0.0
/*128 */          * loader) and it won't work. For this case we force it to 0x10000, too.  // 0.0
/*130 */          */                                                                       // 0.0
/*132 */         if (pentry == KERN_IMAGE_START || pentry == 0x800) {                      // 0.0
/*134 */             ipl->start_addr = KERN_IMAGE_START;                                   // 0.0
/*136 */             /* Overwrite parameters in the kernel image, which are "rom" */       // 0.0
/*138 */             strcpy(rom_ptr(KERN_PARM_AREA), ipl->cmdline);                        // 0.0
/*140 */         } else {                                                                  // 0.0
/*142 */             ipl->start_addr = pentry;                                             // 0.0
/*144 */         }                                                                         // 0.0
/*148 */         if (ipl->initrd) {                                                        // 0.0
/*150 */             ram_addr_t initrd_offset;                                             // 0.0
/*152 */             int initrd_size;                                                      // 0.0
/*156 */             initrd_offset = INITRD_START;                                         // 0.0
/*158 */             while (kernel_size + 0x100000 > initrd_offset) {                      // 0.0
/*160 */                 initrd_offset += 0x100000;                                        // 0.0
/*162 */             }                                                                     // 0.0
/*164 */             initrd_size = load_image_targphys(ipl->initrd, initrd_offset,         // 0.0
/*166 */                                               ram_size - initrd_offset);          // 0.0
/*168 */             if (initrd_size == -1) {                                              // 0.0
/*170 */                 fprintf(stderr, "qemu: could not load initrd '%s'\n",             // 0.0
/*172 */                         ipl->initrd);                                             // 0.0
/*174 */                 exit(1);                                                          // 0.0
/*176 */             }                                                                     // 0.0
/*180 */             /*                                                                    // 0.0
/*182 */              * we have to overwrite values in the kernel image,                   // 0.0
/*184 */              * which are "rom"                                                    // 0.0
/*186 */              */                                                                   // 0.0
/*188 */             stq_p(rom_ptr(INITRD_PARM_START), initrd_offset);                     // 0.0
/*190 */             stq_p(rom_ptr(INITRD_PARM_SIZE), initrd_size);                        // 0.0
/*192 */         }                                                                         // 0.0
/*194 */     }                                                                             // 0.0
/*196 */     return 0;                                                                     // 0.0
/*198 */ }                                                                                 // 0.0
