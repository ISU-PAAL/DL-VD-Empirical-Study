// commit message qemu@5b4a047fbe (target=1, prob=0.5006109, correct=True): xlnx-ep108: Fix minimum RAM check
/*0  */ static void xlnx_ep108_init(MachineState *machine)                               // (15) 0.03125
/*2  */ {                                                                                // (22) 0.001953
/*4  */     XlnxEP108 *s = g_new0(XlnxEP108, 1);                                         // (9) 0.04688
/*6  */     Error *err = NULL;                                                           // (17) 0.01758
/*10 */     object_initialize(&s->soc, sizeof(s->soc), TYPE_XLNX_ZYNQMP);                // (4) 0.05664
/*12 */     object_property_add_child(OBJECT(machine), "soc", OBJECT(&s->soc),           // (8) 0.05078
/*14 */                               &error_abort);                                     // (2) 0.06836
/*18 */     object_property_set_bool(OBJECT(&s->soc), true, "realized", &err);           // (7) 0.05273
/*20 */     if (err) {                                                                   // (18) 0.01562
/*22 */         error_report("%s", error_get_pretty(err));                               // (10) 0.04297
/*24 */         exit(1);                                                                 // (16) 0.02148
/*26 */     }                                                                            // (19) 0.007813
/*30 */     if (machine->ram_size > EP108_MAX_RAM_SIZE) {                                // (13) 0.04102
/*32 */         error_report("WARNING: RAM size " RAM_ADDR_FMT " above max supported, "  // (5) 0.05664
/*34 */                      "reduced to %llx", machine->ram_size, EP108_MAX_RAM_SIZE);  // (1) 0.08398
/*36 */         machine->ram_size = EP108_MAX_RAM_SIZE;                                  // (11) 0.04297
/*38 */     }                                                                            // (20) 0.007812
/*42 */     if (machine->ram_size <= 0x08000000) {                                       // (14) 0.0332
/*44 */         qemu_log("WARNING: RAM size " RAM_ADDR_FMT " is small for EP108",        // (3) 0.0625
/*46 */                  machine->ram_size);                                             // (12) 0.04297
/*48 */     }                                                                            // (21) 0.007812
/*52 */     memory_region_allocate_system_memory(&s->ddr_ram, NULL, "ddr-ram",           // (6) 0.05664
/*54 */                                          machine->ram_size);                     // (0) 0.08984
/*56 */     memory_region_add_subregion(get_system_memory(), 0, &s->ddr_ram);            // 0.0
/*60 */     xlnx_ep108_binfo.ram_size = machine->ram_size;                               // 0.0
/*62 */     xlnx_ep108_binfo.kernel_filename = machine->kernel_filename;                 // 0.0
/*64 */     xlnx_ep108_binfo.kernel_cmdline = machine->kernel_cmdline;                   // 0.0
/*66 */     xlnx_ep108_binfo.initrd_filename = machine->initrd_filename;                 // 0.0
/*68 */     xlnx_ep108_binfo.loader_start = 0;                                           // 0.0
/*70 */     arm_load_kernel(s->soc.boot_cpu_ptr, &xlnx_ep108_binfo);                     // 0.0
/*72 */ }                                                                                // 0.0
