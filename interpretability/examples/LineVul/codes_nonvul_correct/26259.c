// commit message qemu@0ae18ceeaa (target=0, prob=0.28515616, correct=True): Check NIC model in some NIC init functions (Mark McLoughlin)
/*0   */ static void integratorcp_init(ram_addr_t ram_size, int vga_ram_size,              // (6) 0.04884
/*2   */                      const char *boot_device, DisplayState *ds,                   // (2) 0.06262
/*4   */                      const char *kernel_filename, const char *kernel_cmdline,     // (0) 0.06835
/*6   */                      const char *initrd_filename, const char *cpu_model)          // (1) 0.06835
/*8   */ {                                                                                 // (26) 0.001953
/*10  */     CPUState *env;                                                                // (22) 0.01562
/*12  */     uint32_t ram_offset;                                                          // (20) 0.02148
/*14  */     qemu_irq *pic;                                                                // (17) 0.02343
/*16  */     qemu_irq *cpu_pic;                                                            // (14) 0.02734
/*18  */     int sd;                                                                       // (24) 0.01172
/*22  */     if (!cpu_model)                                                               // (21) 0.01758
/*24  */         cpu_model = "arm926";                                                     // (12) 0.03124
/*26  */     env = cpu_init(cpu_model);                                                    // (15) 0.02539
/*28  */     if (!env) {                                                                   // (23) 0.01562
/*30  */         fprintf(stderr, "Unable to find CPU definition\n");                       // (8) 0.04687
/*32  */         exit(1);                                                                  // (19) 0.02148
/*34  */     }                                                                             // (25) 0.007811
/*36  */     ram_offset = qemu_ram_alloc(ram_size);                                        // (9) 0.0371
/*38  */     /* ??? On a real system the first 1Mb is mapped as SSRAM or boot flash.  */   // (7) 0.04882
/*40  */     /* ??? RAM should repeat to fill physical memory space.  */                   // (11) 0.03124
/*42  */     /* SDRAM at address zero*/                                                    // (18) 0.02148
/*44  */     cpu_register_physical_memory(0, ram_size, ram_offset | IO_MEM_RAM);           // (5) 0.05468
/*46  */     /* And again at address 0x80000000 */                                         // (16) 0.02539
/*48  */     cpu_register_physical_memory(0x80000000, ram_size, ram_offset | IO_MEM_RAM);  // (4) 0.06054
/*52  */     integratorcm_init(ram_size >> 20);                                            // (13) 0.02929
/*54  */     cpu_pic = arm_pic_init_cpu(env);                                              // (10) 0.0332
/*56  */     pic = icp_pic_init(0x14000000, cpu_pic[ARM_PIC_CPU_IRQ],                      // (3) 0.06054
/*58  */                        cpu_pic[ARM_PIC_CPU_FIQ]);                                 // 0.0
/*60  */     icp_pic_init(0xca000000, pic[26], NULL);                                      // 0.0
/*62  */     icp_pit_init(0x13000000, pic, 5);                                             // 0.0
/*64  */     pl031_init(0x15000000, pic[8]);                                               // 0.0
/*66  */     pl011_init(0x16000000, pic[1], serial_hds[0], PL011_ARM);                     // 0.0
/*68  */     pl011_init(0x17000000, pic[2], serial_hds[1], PL011_ARM);                     // 0.0
/*70  */     icp_control_init(0xcb000000);                                                 // 0.0
/*72  */     pl050_init(0x18000000, pic[3], 0);                                            // 0.0
/*74  */     pl050_init(0x19000000, pic[4], 1);                                            // 0.0
/*76  */     sd = drive_get_index(IF_SD, 0, 0);                                            // 0.0
/*78  */     if (sd == -1) {                                                               // 0.0
/*80  */         fprintf(stderr, "qemu: missing SecureDigital card\n");                    // 0.0
/*82  */         exit(1);                                                                  // 0.0
/*84  */     }                                                                             // 0.0
/*86  */     pl181_init(0x1c000000, drives_table[sd].bdrv, pic[23], pic[24]);              // 0.0
/*88  */     if (nd_table[0].vlan) {                                                       // 0.0
/*90  */         if (nd_table[0].model == NULL                                             // 0.0
/*92  */             || strcmp(nd_table[0].model, "smc91c111") == 0) {                     // 0.0
/*94  */             smc91c111_init(&nd_table[0], 0xc8000000, pic[27]);                    // 0.0
/*96  */         } else if (strcmp(nd_table[0].model, "?") == 0) {                         // 0.0
/*98  */             fprintf(stderr, "qemu: Supported NICs: smc91c111\n");                 // 0.0
/*100 */             exit (1);                                                             // 0.0
/*102 */         } else {                                                                  // 0.0
/*104 */             fprintf(stderr, "qemu: Unsupported NIC: %s\n", nd_table[0].model);    // 0.0
/*106 */             exit (1);                                                             // 0.0
/*108 */         }                                                                         // 0.0
/*110 */     }                                                                             // 0.0
/*112 */     pl110_init(ds, 0xc0000000, pic[22], 0);                                       // 0.0
/*116 */     integrator_binfo.ram_size = ram_size;                                         // 0.0
/*118 */     integrator_binfo.kernel_filename = kernel_filename;                           // 0.0
/*120 */     integrator_binfo.kernel_cmdline = kernel_cmdline;                             // 0.0
/*122 */     integrator_binfo.initrd_filename = initrd_filename;                           // 0.0
/*124 */     arm_load_kernel(env, &integrator_binfo);                                      // 0.0
/*126 */ }                                                                                 // 0.0
