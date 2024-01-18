// commit message qemu@92c0bba9a9 (target=0, prob=0.1904924, correct=True): omap: remove L4_MUX_HACK
/*0  */ struct omap_l4_s *omap_l4_init(target_phys_addr_t base, int ta_num)          // (9) 0.06055
/*2  */ {                                                                            // (18) 0.001953
/*4  */     struct omap_l4_s *bus = g_malloc0(                                       // (12) 0.03906
/*6  */                     sizeof(*bus) + ta_num * sizeof(*bus->ta));               // (1) 0.06641
/*10 */     bus->ta_num = ta_num;                                                    // (14) 0.02539
/*12 */     bus->base = base;                                                        // (17) 0.01758
/*16 */ #ifdef L4_MUX_HACK                                                           // (16) 0.02148
/*18 */     omap_l4_io_entries = 1;                                                  // (13) 0.03125
/*20 */     omap_l4_io_entry = g_malloc0(125 * sizeof(*omap_l4_io_entry));           // (8) 0.06445
/*24 */     omap_cpu_io_entry =                                                      // (15) 0.02344
/*26 */             cpu_register_io_memory(omap_l4_io_readfn,                        // (10) 0.05859
/*28 */                             omap_l4_io_writefn, bus, DEVICE_NATIVE_ENDIAN);  // (0) 0.0957
/*30 */ # define L4_PAGES	(0xb4000 / TARGET_PAGE_SIZE)                               // (11) 0.04102
/*32 */     omap_l4_io_readb_fn = g_malloc0(sizeof(void *) * L4_PAGES);              // (2) 0.06641
/*34 */     omap_l4_io_readh_fn = g_malloc0(sizeof(void *) * L4_PAGES);              // (5) 0.06641
/*36 */     omap_l4_io_readw_fn = g_malloc0(sizeof(void *) * L4_PAGES);              // (3) 0.06641
/*38 */     omap_l4_io_writeb_fn = g_malloc0(sizeof(void *) * L4_PAGES);             // (6) 0.06641
/*40 */     omap_l4_io_writeh_fn = g_malloc0(sizeof(void *) * L4_PAGES);             // (7) 0.06641
/*42 */     omap_l4_io_writew_fn = g_malloc0(sizeof(void *) * L4_PAGES);             // (4) 0.06641
/*44 */     omap_l4_io_opaque = g_malloc0(sizeof(void *) * L4_PAGES);                // 0.0
/*46 */ #endif                                                                       // 0.0
/*50 */     return bus;                                                              // 0.0
/*52 */ }                                                                            // 0.0
