// commit message qemu@f8ed85ac99 (target=1, prob=0.12427138, correct=False): Fix bad error handling after memory_region_init_ram()
/*0   */ static void xen_ram_init(PCMachineState *pcms,                                   // (12) 0.0293
/*2   */                          ram_addr_t ram_size, MemoryRegion **ram_memory_p)       // (2) 0.08203
/*4   */ {                                                                                // (22) 0.001953
/*6   */     MemoryRegion *sysmem = get_system_memory();                                  // (13) 0.0293
/*8   */     ram_addr_t block_len;                                                        // (17) 0.02344
/*10  */     uint64_t user_lowmem = object_property_get_int(qdev_get_machine(),           // (4) 0.05273
/*12  */                                                    PC_MACHINE_MAX_RAM_BELOW_4G,  // (0) 0.1309
/*14  */                                                    &error_abort);                // (1) 0.1094
/*18  */     /* Handle the machine opt max-ram-below-4g.  It is basically doing           // (9) 0.04297
/*20  */      * min(xen limit, user limit).                                               // (16) 0.02734
/*22  */      */                                                                          // (19) 0.009766
/*24  */     if (HVM_BELOW_4G_RAM_END <= user_lowmem) {                                   // (6) 0.04883
/*26  */         user_lowmem = HVM_BELOW_4G_RAM_END;                                      // (5) 0.05078
/*28  */     }                                                                            // (20) 0.007812
/*32  */     if (ram_size >= user_lowmem) {                                               // (14) 0.0293
/*34  */         pcms->above_4g_mem_size = ram_size - user_lowmem;                        // (3) 0.05469
/*36  */         pcms->below_4g_mem_size = user_lowmem;                                   // (7) 0.04687
/*38  */     } else {                                                                     // (18) 0.01172
/*40  */         pcms->above_4g_mem_size = 0;                                             // (10) 0.04102
/*42  */         pcms->below_4g_mem_size = ram_size;                                      // (8) 0.04492
/*44  */     }                                                                            // (21) 0.007812
/*46  */     if (!pcms->above_4g_mem_size) {                                              // (11) 0.03516
/*48  */         block_len = ram_size;                                                    // (15) 0.0293
/*50  */     } else {                                                                     // 0.0
/*52  */         /*                                                                       // 0.0
/*54  */          * Xen does not allocate the memory continuously, it keeps a             // 0.0
/*56  */          * hole of the size computed above or passed in.                         // 0.0
/*58  */          */                                                                      // 0.0
/*60  */         block_len = (1ULL << 32) + pcms->above_4g_mem_size;                      // 0.0
/*62  */     }                                                                            // 0.0
/*64  */     memory_region_init_ram(&ram_memory, NULL, "xen.ram", block_len,              // 0.0
/*66  */                            &error_abort);                                        // 0.0
/*68  */     *ram_memory_p = &ram_memory;                                                 // 0.0
/*70  */     vmstate_register_ram_global(&ram_memory);                                    // 0.0
/*74  */     memory_region_init_alias(&ram_640k, NULL, "xen.ram.640k",                    // 0.0
/*76  */                              &ram_memory, 0, 0xa0000);                           // 0.0
/*78  */     memory_region_add_subregion(sysmem, 0, &ram_640k);                           // 0.0
/*80  */     /* Skip of the VGA IO memory space, it will be registered later by the VGA   // 0.0
/*82  */      * emulated device.                                                          // 0.0
/*84  */      *                                                                           // 0.0
/*86  */      * The area between 0xc0000 and 0x100000 will be used by SeaBIOS to load     // 0.0
/*88  */      * the Options ROM, so it is registered here as RAM.                         // 0.0
/*90  */      */                                                                          // 0.0
/*92  */     memory_region_init_alias(&ram_lo, NULL, "xen.ram.lo",                        // 0.0
/*94  */                              &ram_memory, 0xc0000,                               // 0.0
/*96  */                              pcms->below_4g_mem_size - 0xc0000);                 // 0.0
/*98  */     memory_region_add_subregion(sysmem, 0xc0000, &ram_lo);                       // 0.0
/*100 */     if (pcms->above_4g_mem_size > 0) {                                           // 0.0
/*102 */         memory_region_init_alias(&ram_hi, NULL, "xen.ram.hi",                    // 0.0
/*104 */                                  &ram_memory, 0x100000000ULL,                    // 0.0
/*106 */                                  pcms->above_4g_mem_size);                       // 0.0
/*108 */         memory_region_add_subregion(sysmem, 0x100000000ULL, &ram_hi);            // 0.0
/*110 */     }                                                                            // 0.0
/*112 */ }                                                                                // 0.0
