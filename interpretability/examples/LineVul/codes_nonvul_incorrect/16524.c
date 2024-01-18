// commit message qemu@4be746345f (target=0, prob=0.5753632, correct=False): hw: Convert from BlockDriverState to BlockBackend, mostly
/*0  */ static void collie_init(MachineState *machine)                          // (16) 0.02344
/*2  */ {                                                                       // (21) 0.001953
/*4  */     const char *cpu_model = machine->cpu_model;                         // (12) 0.03125
/*6  */     const char *kernel_filename = machine->kernel_filename;             // (13) 0.03125
/*8  */     const char *kernel_cmdline = machine->kernel_cmdline;               // (11) 0.03516
/*10 */     const char *initrd_filename = machine->initrd_filename;             // (10) 0.03516
/*12 */     StrongARMState *s;                                                  // (19) 0.01758
/*14 */     DriveInfo *dinfo;                                                   // (18) 0.01758
/*16 */     MemoryRegion *sysmem = get_system_memory();                         // (15) 0.0293
/*20 */     if (!cpu_model) {                                                   // (17) 0.01953
/*22 */         cpu_model = "sa1110";                                           // (14) 0.03125
/*24 */     }                                                                   // (20) 0.007813
/*28 */     s = sa1110_init(sysmem, collie_binfo.ram_size, cpu_model);          // (6) 0.05469
/*32 */     dinfo = drive_get(IF_PFLASH, 0, 0);                                 // (8) 0.03906
/*34 */     pflash_cfi01_register(SA_CS0, NULL, "collie.fl1", 0x02000000,       // (4) 0.06055
/*36 */                     dinfo ? blk_bs(blk_by_legacy_dinfo(dinfo)) : NULL,  // (2) 0.08594
/*38 */                     (64 * 1024), 512, 4, 0x00, 0x00, 0x00, 0x00, 0);    // (0) 0.08984
/*42 */     dinfo = drive_get(IF_PFLASH, 0, 1);                                 // (9) 0.03906
/*44 */     pflash_cfi01_register(SA_CS1, NULL, "collie.fl2", 0x02000000,       // (5) 0.06055
/*46 */                     dinfo ? blk_bs(blk_by_legacy_dinfo(dinfo)) : NULL,  // (3) 0.08594
/*48 */                     (64 * 1024), 512, 4, 0x00, 0x00, 0x00, 0x00, 0);    // (1) 0.08984
/*52 */     sysbus_create_simple("scoop", 0x40800000, NULL);                    // (7) 0.04297
/*56 */     collie_binfo.kernel_filename = kernel_filename;                     // 0.0
/*58 */     collie_binfo.kernel_cmdline = kernel_cmdline;                       // 0.0
/*60 */     collie_binfo.initrd_filename = initrd_filename;                     // 0.0
/*62 */     collie_binfo.board_id = 0x208;                                      // 0.0
/*64 */     arm_load_kernel(s->cpu, &collie_binfo);                             // 0.0
/*66 */ }                                                                       // 0.0
