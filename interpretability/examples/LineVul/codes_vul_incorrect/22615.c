// commit message qemu@654598c944 (target=1, prob=0.17209311, correct=False): pc_sysfw: Plug memory leak on pc_fw_add_pflash_drv() error path
/*0  */ static void pc_fw_add_pflash_drv(void)                          // (4) 0.06504
/*2  */ {                                                               // (18) 0.004065
/*4  */     QemuOpts *opts;                                             // (6) 0.04878
/*6  */     QEMUMachine *machine;                                       // (9) 0.04065
/*8  */     char *filename;                                             // (12) 0.02846
/*12 */     if (bios_name == NULL) {                                    // (5) 0.05285
/*14 */         bios_name = BIOS_FILENAME;                              // (2) 0.06911
/*16 */     }                                                           // (15) 0.01626
/*18 */     filename = qemu_find_file(QEMU_FILE_TYPE_BIOS, bios_name);  // (0) 0.1138
/*22 */     opts = drive_add(IF_PFLASH, -1, filename, "readonly=on");   // (1) 0.1098
/*26 */     g_free(filename);                                           // (11) 0.03659
/*30 */     if (opts == NULL) {                                         // (8) 0.04472
/*32 */       return;                                                   // (13) 0.02846
/*34 */     }                                                           // (16) 0.01626
/*38 */     machine = find_default_machine();                           // (7) 0.04472
/*40 */     if (machine == NULL) {                                      // (10) 0.04065
/*42 */       return;                                                   // (14) 0.02846
/*44 */     }                                                           // (17) 0.01626
/*48 */     drive_init(opts, machine->use_scsi);                        // (3) 0.06911
/*50 */ }                                                               // (19) 0.004065
