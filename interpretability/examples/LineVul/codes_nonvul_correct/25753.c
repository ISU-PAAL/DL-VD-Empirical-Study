// commit message qemu@7264961934 (target=0, prob=0.26165107, correct=True): hw: add .min_cpus and .default_cpus fields to machine_class
/*0  */ exynos4_boards_init_common(MachineState *machine,                              // (17) 0.03125
/*2  */                            Exynos4BoardType board_type)                        // (0) 0.07031
/*4  */ {                                                                              // (19) 0.001953
/*6  */     Exynos4BoardState *s = g_new(Exynos4BoardState, 1);                        // (9) 0.04883
/*8  */     MachineClass *mc = MACHINE_GET_CLASS(machine);                             // (16) 0.03516
/*12 */     if (smp_cpus != EXYNOS4210_NCPUS && !qtest_enabled()) {                    // (7) 0.05469
/*14 */         error_report("%s board supports only %d CPU cores, ignoring smp_cpus"  // (8) 0.05469
/*16 */                      " value",                                                 // (13) 0.04492
/*18 */                      mc->name, EXYNOS4210_NCPUS);                              // (1) 0.06641
/*20 */     }                                                                          // (18) 0.007812
/*24 */     exynos4_board_binfo.ram_size = exynos4_board_ram_size[board_type];         // (3) 0.0625
/*26 */     exynos4_board_binfo.board_id = exynos4_board_id[board_type];               // (5) 0.05859
/*28 */     exynos4_board_binfo.smp_bootreg_addr =                                     // (15) 0.04102
/*30 */             exynos4_board_smp_bootreg_addr[board_type];                        // (4) 0.05859
/*32 */     exynos4_board_binfo.kernel_filename = machine->kernel_filename;            // (12) 0.04492
/*34 */     exynos4_board_binfo.initrd_filename = machine->initrd_filename;            // (11) 0.04883
/*36 */     exynos4_board_binfo.kernel_cmdline = machine->kernel_cmdline;              // (10) 0.04883
/*38 */     exynos4_board_binfo.gic_cpu_if_addr =                                      // (14) 0.04297
/*40 */             EXYNOS4210_SMP_PRIVATE_BASE_ADDR + 0x100;                          // (2) 0.06641
/*44 */     PRINT_DEBUG("\n ram_size: %luMiB [0x%08lx]\n"                              // (6) 0.05664
/*46 */             " kernel_filename: %s\n"                                           // 0.0
/*48 */             " kernel_cmdline: %s\n"                                            // 0.0
/*50 */             " initrd_filename: %s\n",                                          // 0.0
/*52 */             exynos4_board_ram_size[board_type] / 1048576,                      // 0.0
/*54 */             exynos4_board_ram_size[board_type],                                // 0.0
/*56 */             machine->kernel_filename,                                          // 0.0
/*58 */             machine->kernel_cmdline,                                           // 0.0
/*60 */             machine->initrd_filename);                                         // 0.0
/*64 */     exynos4_boards_init_ram(s, get_system_memory(),                            // 0.0
/*66 */                             exynos4_board_ram_size[board_type]);               // 0.0
/*70 */     s->soc = exynos4210_init(get_system_memory());                             // 0.0
/*74 */     return s;                                                                  // 0.0
/*76 */ }                                                                              // 0.0
