// commit message qemu@db7dfd4c7e (target=0, prob=0.37422022, correct=True): hw/arm/allwinner-a10: initialize EMAC
/*0  */ static void cubieboard_init(QEMUMachineInitArgs *args)                          // (12) 0.04208
/*2  */ {                                                                               // (18) 0.002475
/*4  */     CubieBoardState *s = g_new(CubieBoardState, 1);                             // (9) 0.05198
/*6  */     Error *err = NULL;                                                          // (16) 0.02228
/*10 */     s->a10 = AW_A10(object_new(TYPE_AW_A10));                                   // (6) 0.05941
/*12 */     object_property_set_bool(OBJECT(s->a10), true, "realized", &err);           // (3) 0.06931
/*14 */     if (err != NULL) {                                                          // (15) 0.02475
/*16 */         error_report("Couldn't realize Allwinner A10: %s\n",                    // (4) 0.06188
/*18 */                 error_get_pretty(err));                                         // (7) 0.05693
/*20 */         exit(1);                                                                // (14) 0.02723
/*22 */     }                                                                           // (17) 0.009901
/*26 */     memory_region_init_ram(&s->sdram, NULL, "cubieboard.ram", args->ram_size);  // (1) 0.07921
/*28 */     vmstate_register_ram_global(&s->sdram);                                     // (13) 0.04208
/*30 */     memory_region_add_subregion(get_system_memory(), AW_A10_SDRAM_BASE,         // (2) 0.07426
/*32 */                                 &s->sdram);                                     // (0) 0.09158
/*36 */     cubieboard_binfo.ram_size = args->ram_size;                                 // (10) 0.0495
/*38 */     cubieboard_binfo.kernel_filename = args->kernel_filename;                   // (11) 0.0495
/*40 */     cubieboard_binfo.kernel_cmdline = args->kernel_cmdline;                     // (8) 0.05446
/*42 */     arm_load_kernel(&s->a10->cpu, &cubieboard_binfo);                           // (5) 0.06188
/*44 */ }                                                                               // (19) 0.002475
