// commit message qemu@3ad9fd5a25 (target=1, prob=0.11400969, correct=False): target-mips: fix memory leak
/*0   */ static int64_t load_kernel (void)                                                  // (15) 0.02148
/*2   */ {                                                                                  // (28) 0.001953
/*4   */     int64_t kernel_entry, kernel_high;                                             // (9) 0.0293
/*6   */     long initrd_size;                                                              // (21) 0.01758
/*8   */     ram_addr_t initrd_offset;                                                      // (13) 0.02539
/*10  */     int big_endian;                                                                // (22) 0.01758
/*12  */     uint32_t *prom_buf;                                                            // (14) 0.02344
/*14  */     long prom_size;                                                                // (23) 0.01562
/*16  */     int prom_index = 0;                                                            // (18) 0.01953
/*18  */     uint64_t (*xlate_to_kseg0) (void *opaque, uint64_t addr);                      // (4) 0.05859
/*22  */ #ifdef TARGET_WORDS_BIGENDIAN                                                      // (12) 0.02539
/*24  */     big_endian = 1;                                                                // (19) 0.01953
/*26  */ #else                                                                              // (27) 0.003906
/*28  */     big_endian = 0;                                                                // (20) 0.01953
/*30  */ #endif                                                                             // (26) 0.003906
/*34  */     if (load_elf(loaderparams.kernel_filename, cpu_mips_kseg0_to_phys, NULL,       // (3) 0.0625
/*36  */                  (uint64_t *)&kernel_entry, NULL, (uint64_t *)&kernel_high,        // (0) 0.07812
/*38  */                  big_endian, ELF_MACHINE, 1) < 0) {                                // (2) 0.06641
/*40  */         fprintf(stderr, "qemu: could not load kernel '%s'\n",                      // (5) 0.05859
/*42  */                 loaderparams.kernel_filename);                                     // (7) 0.04297
/*44  */         exit(1);                                                                   // (17) 0.02148
/*46  */     }                                                                              // (25) 0.007812
/*50  */     /* Sanity check where the kernel has been linked */                            // (11) 0.02734
/*52  */     if (kvm_enabled()) {                                                           // (16) 0.02148
/*54  */         if (kernel_entry & 0x80000000ll) {                                         // (8) 0.03906
/*56  */             error_report("KVM guest kernels must be linked in useg. "              // (6) 0.05273
/*58  */                          "Did you forget to enable CONFIG_KVM_GUEST?");            // (1) 0.07617
/*60  */             exit(1);                                                               // (10) 0.0293
/*62  */         }                                                                          // (24) 0.01562
/*66  */         xlate_to_kseg0 = cpu_mips_kvm_um_phys_to_kseg0;                            // 0.0
/*68  */     } else {                                                                       // 0.0
/*70  */         if (!(kernel_entry & 0x80000000ll)) {                                      // 0.0
/*72  */             error_report("KVM guest kernels aren't supported with TCG. "           // 0.0
/*74  */                          "Did you unintentionally enable CONFIG_KVM_GUEST?");      // 0.0
/*76  */             exit(1);                                                               // 0.0
/*78  */         }                                                                          // 0.0
/*82  */         xlate_to_kseg0 = cpu_mips_phys_to_kseg0;                                   // 0.0
/*84  */     }                                                                              // 0.0
/*88  */     /* load initrd */                                                              // 0.0
/*90  */     initrd_size = 0;                                                               // 0.0
/*92  */     initrd_offset = 0;                                                             // 0.0
/*94  */     if (loaderparams.initrd_filename) {                                            // 0.0
/*96  */         initrd_size = get_image_size (loaderparams.initrd_filename);               // 0.0
/*98  */         if (initrd_size > 0) {                                                     // 0.0
/*100 */             initrd_offset = (kernel_high + ~INITRD_PAGE_MASK) & INITRD_PAGE_MASK;  // 0.0
/*102 */             if (initrd_offset + initrd_size > ram_size) {                          // 0.0
/*104 */                 fprintf(stderr,                                                    // 0.0
/*106 */                         "qemu: memory too small for initial ram disk '%s'\n",      // 0.0
/*108 */                         loaderparams.initrd_filename);                             // 0.0
/*110 */                 exit(1);                                                           // 0.0
/*112 */             }                                                                      // 0.0
/*114 */             initrd_size = load_image_targphys(loaderparams.initrd_filename,        // 0.0
/*116 */                                               initrd_offset,                       // 0.0
/*118 */                                               ram_size - initrd_offset);           // 0.0
/*120 */         }                                                                          // 0.0
/*122 */         if (initrd_size == (target_ulong) -1) {                                    // 0.0
/*124 */             fprintf(stderr, "qemu: could not load initial ram disk '%s'\n",        // 0.0
/*126 */                     loaderparams.initrd_filename);                                 // 0.0
/*128 */             exit(1);                                                               // 0.0
/*130 */         }                                                                          // 0.0
/*132 */     }                                                                              // 0.0
/*136 */     /* Setup prom parameters. */                                                   // 0.0
/*138 */     prom_size = ENVP_NB_ENTRIES * (sizeof(int32_t) + ENVP_ENTRY_SIZE);             // 0.0
/*140 */     prom_buf = g_malloc(prom_size);                                                // 0.0
/*144 */     prom_set(prom_buf, prom_index++, "%s", loaderparams.kernel_filename);          // 0.0
/*146 */     if (initrd_size > 0) {                                                         // 0.0
/*148 */         prom_set(prom_buf, prom_index++, "rd_start=0x%" PRIx64 " rd_size=%li %s",  // 0.0
/*150 */                  xlate_to_kseg0(NULL, initrd_offset), initrd_size,                 // 0.0
/*152 */                  loaderparams.kernel_cmdline);                                     // 0.0
/*154 */     } else {                                                                       // 0.0
/*156 */         prom_set(prom_buf, prom_index++, "%s", loaderparams.kernel_cmdline);       // 0.0
/*158 */     }                                                                              // 0.0
/*162 */     prom_set(prom_buf, prom_index++, "memsize");                                   // 0.0
/*164 */     prom_set(prom_buf, prom_index++, "%i",                                         // 0.0
/*166 */              MIN(loaderparams.ram_size, 256 << 20));                               // 0.0
/*170 */     prom_set(prom_buf, prom_index++, "modetty0");                                  // 0.0
/*172 */     prom_set(prom_buf, prom_index++, "38400n8r");                                  // 0.0
/*174 */     prom_set(prom_buf, prom_index++, NULL);                                        // 0.0
/*178 */     rom_add_blob_fixed("prom", prom_buf, prom_size,                                // 0.0
/*180 */                        cpu_mips_kseg0_to_phys(NULL, ENVP_ADDR));                   // 0.0
/*185 */     return kernel_entry;                                                           // 0.0
/*187 */ }                                                                                  // 0.0
