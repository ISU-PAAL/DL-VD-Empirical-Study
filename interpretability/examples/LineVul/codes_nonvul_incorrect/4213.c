// commit message qemu@a8170e5e97 (target=0, prob=0.5352325, correct=False): Rename target_phys_addr_t to hwaddr
/*0   */ static void mcf5208evb_init(QEMUMachineInitArgs *args)                           // (5) 0.03906
/*2   */ {                                                                                // (31) 0.001953
/*4   */     ram_addr_t ram_size = args->ram_size;                                        // (6) 0.03516
/*6   */     const char *cpu_model = args->cpu_model;                                     // (12) 0.03125
/*8   */     const char *kernel_filename = args->kernel_filename;                         // (10) 0.03125
/*10  */     CPUM68KState *env;                                                           // (21) 0.02148
/*12  */     int kernel_size;                                                             // (28) 0.01562
/*14  */     uint64_t elf_entry;                                                          // (20) 0.02149
/*16  */     target_phys_addr_t entry;                                                    // (17) 0.02344
/*18  */     qemu_irq *pic;                                                               // (18) 0.02344
/*20  */     MemoryRegion *address_space_mem = get_system_memory();                       // (7) 0.03516
/*22  */     MemoryRegion *ram = g_new(MemoryRegion, 1);                                  // (9) 0.0332
/*24  */     MemoryRegion *sram = g_new(MemoryRegion, 1);                                 // (8) 0.03516
/*28  */     if (!cpu_model)                                                              // (27) 0.01758
/*30  */         cpu_model = "m5208";                                                     // (11) 0.03125
/*32  */     env = cpu_init(cpu_model);                                                   // (16) 0.02539
/*34  */     if (!env) {                                                                  // (29) 0.01562
/*36  */         fprintf(stderr, "Unable to find m68k CPU definition\n");                 // (0) 0.05273
/*38  */         exit(1);                                                                 // (22) 0.02148
/*40  */     }                                                                            // (30) 0.007812
/*44  */     /* Initialize CPU registers.  */                                             // (23) 0.02148
/*46  */     env->vbr = 0;                                                                // (26) 0.01953
/*48  */     /* TODO: Configure BARs.  */                                                 // (14) 0.02734
/*52  */     /* DRAM at 0x40000000 */                                                     // (19) 0.02344
/*54  */     memory_region_init_ram(ram, "mcf5208.ram", ram_size);                        // (4) 0.04883
/*56  */     vmstate_register_ram_global(ram);                                            // (15) 0.02734
/*58  */     memory_region_add_subregion(address_space_mem, 0x40000000, ram);             // (3) 0.04883
/*62  */     /* Internal SRAM.  */                                                        // (25) 0.01953
/*64  */     memory_region_init_ram(sram, "mcf5208.sram", 16384);                         // (2) 0.05078
/*66  */     vmstate_register_ram_global(sram);                                           // (13) 0.0293
/*68  */     memory_region_add_subregion(address_space_mem, 0x80000000, sram);            // (1) 0.05078
/*72  */     /* Internal peripherals.  */                                                 // (24) 0.01953
/*74  */     pic = mcf_intc_init(address_space_mem, 0xfc048000, env);                     // 0.0
/*78  */     mcf_uart_mm_init(address_space_mem, 0xfc060000, pic[26], serial_hds[0]);     // 0.0
/*80  */     mcf_uart_mm_init(address_space_mem, 0xfc064000, pic[27], serial_hds[1]);     // 0.0
/*82  */     mcf_uart_mm_init(address_space_mem, 0xfc068000, pic[28], serial_hds[2]);     // 0.0
/*86  */     mcf5208_sys_init(address_space_mem, pic);                                    // 0.0
/*90  */     if (nb_nics > 1) {                                                           // 0.0
/*92  */         fprintf(stderr, "Too many NICs\n");                                      // 0.0
/*94  */         exit(1);                                                                 // 0.0
/*96  */     }                                                                            // 0.0
/*98  */     if (nd_table[0].used)                                                        // 0.0
/*100 */         mcf_fec_init(address_space_mem, &nd_table[0],                            // 0.0
/*102 */                      0xfc030000, pic + 36);                                      // 0.0
/*106 */     /*  0xfc000000 SCM.  */                                                      // 0.0
/*108 */     /*  0xfc004000 XBS.  */                                                      // 0.0
/*110 */     /*  0xfc008000 FlexBus CS.  */                                               // 0.0
/*112 */     /* 0xfc030000 FEC.  */                                                       // 0.0
/*114 */     /*  0xfc040000 SCM + Power management.  */                                   // 0.0
/*116 */     /*  0xfc044000 eDMA.  */                                                     // 0.0
/*118 */     /* 0xfc048000 INTC.  */                                                      // 0.0
/*120 */     /*  0xfc058000 I2C.  */                                                      // 0.0
/*122 */     /*  0xfc05c000 QSPI.  */                                                     // 0.0
/*124 */     /* 0xfc060000 UART0.  */                                                     // 0.0
/*126 */     /* 0xfc064000 UART0.  */                                                     // 0.0
/*128 */     /* 0xfc068000 UART0.  */                                                     // 0.0
/*130 */     /*  0xfc070000 DMA timers.  */                                               // 0.0
/*132 */     /* 0xfc080000 PIT0.  */                                                      // 0.0
/*134 */     /* 0xfc084000 PIT1.  */                                                      // 0.0
/*136 */     /*  0xfc088000 EPORT.  */                                                    // 0.0
/*138 */     /*  0xfc08c000 Watchdog.  */                                                 // 0.0
/*140 */     /*  0xfc090000 clock module.  */                                             // 0.0
/*142 */     /*  0xfc0a0000 CCM + reset.  */                                              // 0.0
/*144 */     /*  0xfc0a4000 GPIO.  */                                                     // 0.0
/*146 */     /* 0xfc0a8000 SDRAM controller.  */                                          // 0.0
/*150 */     /* Load kernel.  */                                                          // 0.0
/*152 */     if (!kernel_filename) {                                                      // 0.0
/*154 */         fprintf(stderr, "Kernel image must be specified\n");                     // 0.0
/*156 */         exit(1);                                                                 // 0.0
/*158 */     }                                                                            // 0.0
/*162 */     kernel_size = load_elf(kernel_filename, NULL, NULL, &elf_entry,              // 0.0
/*164 */                            NULL, NULL, 1, ELF_MACHINE, 0);                       // 0.0
/*166 */     entry = elf_entry;                                                           // 0.0
/*168 */     if (kernel_size < 0) {                                                       // 0.0
/*170 */         kernel_size = load_uimage(kernel_filename, &entry, NULL, NULL);          // 0.0
/*172 */     }                                                                            // 0.0
/*174 */     if (kernel_size < 0) {                                                       // 0.0
/*176 */         kernel_size = load_image_targphys(kernel_filename, 0x40000000,           // 0.0
/*178 */                                           ram_size);                             // 0.0
/*180 */         entry = 0x40000000;                                                      // 0.0
/*182 */     }                                                                            // 0.0
/*184 */     if (kernel_size < 0) {                                                       // 0.0
/*186 */         fprintf(stderr, "qemu: could not load kernel '%s'\n", kernel_filename);  // 0.0
/*188 */         exit(1);                                                                 // 0.0
/*190 */     }                                                                            // 0.0
/*194 */     env->pc = entry;                                                             // 0.0
/*196 */ }                                                                                // 0.0
