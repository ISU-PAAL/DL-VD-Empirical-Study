// commit message qemu@04088adbe0 (target=0, prob=0.09178662, correct=True): powerpc/booke: move fdt loading to rom infrastructure
/*0   */ static void *mpc8544_load_device_tree(target_phys_addr_t addr,                // (7) 0.04492
/*2   */                                      uint32_t ramsize,                        // (3) 0.08594
/*4   */                                      target_phys_addr_t initrd_base,          // (0) 0.09375
/*6   */                                      target_phys_addr_t initrd_size,          // (1) 0.09375
/*8   */                                      const char *kernel_cmdline)              // (2) 0.08594
/*10  */ {                                                                             // (24) 0.001953
/*12  */     void *fdt = NULL;                                                         // (13) 0.01953
/*14  */ #ifdef CONFIG_FDT                                                             // (19) 0.01367
/*16  */     uint32_t mem_reg_property[] = {0, ramsize};                               // (8) 0.04102
/*18  */     char *filename;                                                           // (20) 0.01367
/*20  */     int fdt_size;                                                             // (16) 0.01758
/*22  */     int ret;                                                                  // (21) 0.01172
/*26  */     filename = qemu_find_file(QEMU_FILE_TYPE_BIOS, BINARY_DEVICE_TREE_FILE);  // (5) 0.07031
/*28  */     if (!filename) {                                                          // (18) 0.01562
/*30  */         goto out;                                                             // (15) 0.01953
/*32  */     }                                                                         // (23) 0.007812
/*34  */     fdt = load_device_tree(filename, &fdt_size);                              // (9) 0.03906
/*36  */     qemu_free(filename);                                                      // (11) 0.02148
/*38  */     if (fdt == NULL) {                                                        // (12) 0.02148
/*40  */         goto out;                                                             // (14) 0.01953
/*42  */     }                                                                         // (22) 0.007812
/*46  */     /* Manipulate device tree in memory. */                                   // (10) 0.02344
/*48  */     ret = qemu_devtree_setprop(fdt, "/memory", "reg", mem_reg_property,       // (6) 0.05859
/*50  */                                sizeof(mem_reg_property));                     // (4) 0.07422
/*52  */     if (ret < 0)                                                              // (17) 0.01758
/*54  */         fprintf(stderr, "couldn't set /memory/reg\n");                        // 0.0
/*58  */     ret = qemu_devtree_setprop_cell(fdt, "/chosen", "linux,initrd-start",     // 0.0
/*60  */                                     initrd_base);                             // 0.0
/*62  */     if (ret < 0)                                                              // 0.0
/*64  */         fprintf(stderr, "couldn't set /chosen/linux,initrd-start\n");         // 0.0
/*68  */     ret = qemu_devtree_setprop_cell(fdt, "/chosen", "linux,initrd-end",       // 0.0
/*70  */                                     (initrd_base + initrd_size));             // 0.0
/*72  */     if (ret < 0)                                                              // 0.0
/*74  */         fprintf(stderr, "couldn't set /chosen/linux,initrd-end\n");           // 0.0
/*78  */     ret = qemu_devtree_setprop_string(fdt, "/chosen", "bootargs",             // 0.0
/*80  */                                       kernel_cmdline);                        // 0.0
/*82  */     if (ret < 0)                                                              // 0.0
/*84  */         fprintf(stderr, "couldn't set /chosen/bootargs\n");                   // 0.0
/*88  */     if (kvm_enabled()) {                                                      // 0.0
/*90  */         struct dirent *dirp;                                                  // 0.0
/*92  */         DIR *dp;                                                              // 0.0
/*94  */         char buf[128];                                                        // 0.0
/*98  */         if ((dp = opendir("/proc/device-tree/cpus/")) == NULL) {              // 0.0
/*100 */             printf("Can't open directory /proc/device-tree/cpus/\n");         // 0.0
/*102 */             goto out;                                                         // 0.0
/*104 */         }                                                                     // 0.0
/*108 */         buf[0] = '\0';                                                        // 0.0
/*110 */         while ((dirp = readdir(dp)) != NULL) {                                // 0.0
/*112 */             if (strncmp(dirp->d_name, "PowerPC", 7) == 0) {                   // 0.0
/*114 */                 snprintf(buf, 128, "/cpus/%s", dirp->d_name);                 // 0.0
/*116 */                 break;                                                        // 0.0
/*118 */             }                                                                 // 0.0
/*120 */         }                                                                     // 0.0
/*122 */         closedir(dp);                                                         // 0.0
/*124 */         if (buf[0] == '\0') {                                                 // 0.0
/*126 */             printf("Unknow host!\n");                                         // 0.0
/*128 */             goto out;                                                         // 0.0
/*130 */         }                                                                     // 0.0
/*134 */         mpc8544_copy_soc_cell(fdt, buf, "clock-frequency");                   // 0.0
/*136 */         mpc8544_copy_soc_cell(fdt, buf, "timebase-frequency");                // 0.0
/*138 */     }                                                                         // 0.0
/*142 */     cpu_physical_memory_write (addr, (void *)fdt, fdt_size);                  // 0.0
/*146 */ out:                                                                          // 0.0
/*148 */ #endif                                                                        // 0.0
/*152 */     return fdt;                                                               // 0.0
/*154 */ }                                                                             // 0.0
