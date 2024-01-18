// commit message qemu@4482e05cbb (target=1, prob=0.6086053, correct=True): cpu: make cpu_generic_init() abort QEMU on error
/*0   */ static void lm32_evr_init(MachineState *machine)                                 // (13) 0.03125
/*2   */ {                                                                                // (27) 0.001953
/*4   */     const char *cpu_model = machine->cpu_model;                                  // (14) 0.03125
/*6   */     const char *kernel_filename = machine->kernel_filename;                      // (15) 0.03125
/*8   */     LM32CPU *cpu;                                                                // (22) 0.01758
/*10  */     CPULM32State *env;                                                           // (20) 0.01953
/*12  */     DriveInfo *dinfo;                                                            // (23) 0.01758
/*14  */     MemoryRegion *address_space_mem =  get_system_memory();                      // (7) 0.03711
/*16  */     MemoryRegion *phys_ram = g_new(MemoryRegion, 1);                             // (8) 0.03711
/*18  */     qemu_irq irq[32];                                                            // (18) 0.02734
/*20  */     ResetInfo *reset_info;                                                       // (21) 0.01953
/*22  */     int i;                                                                       // (25) 0.01172
/*26  */     /* memory map */                                                             // (24) 0.01367
/*28  */     hwaddr flash_base  = 0x04000000;                                             // (16) 0.03125
/*30  */     size_t flash_sector_size       = 256 * 1024;                                 // (5) 0.04297
/*32  */     size_t flash_size              = 32 * 1024 * 1024;                           // (2) 0.05664
/*34  */     hwaddr ram_base    = 0x08000000;                                             // (9) 0.03516
/*36  */     size_t ram_size                = 64 * 1024 * 1024;                           // (0) 0.06055
/*38  */     hwaddr timer0_base = 0x80002000;                                             // (17) 0.03125
/*40  */     hwaddr uart0_base  = 0x80006000;                                             // (10) 0.03516
/*42  */     hwaddr timer1_base = 0x8000a000;                                             // (12) 0.0332
/*44  */     int uart0_irq                  = 0;                                          // (1) 0.05859
/*46  */     int timer0_irq                 = 1;                                          // (3) 0.05469
/*48  */     int timer1_irq                 = 3;                                          // (4) 0.05469
/*52  */     reset_info = g_malloc0(sizeof(ResetInfo));                                   // (6) 0.03906
/*56  */     if (cpu_model == NULL) {                                                     // (19) 0.02344
/*58  */         cpu_model = "lm32-full";                                                 // (11) 0.03516
/*60  */     }                                                                            // (26) 0.007812
/*62  */     cpu = LM32_CPU(cpu_generic_init(TYPE_LM32_CPU, cpu_model));                  // 0.0
/*64  */     if (cpu == NULL) {                                                           // 0.0
/*66  */         fprintf(stderr, "qemu: unable to find CPU '%s'\n", cpu_model);           // 0.0
/*68  */         exit(1);                                                                 // 0.0
/*70  */     }                                                                            // 0.0
/*74  */     env = &cpu->env;                                                             // 0.0
/*76  */     reset_info->cpu = cpu;                                                       // 0.0
/*80  */     reset_info->flash_base = flash_base;                                         // 0.0
/*84  */     memory_region_allocate_system_memory(phys_ram, NULL, "lm32_evr.sdram",       // 0.0
/*86  */                                          ram_size);                              // 0.0
/*88  */     memory_region_add_subregion(address_space_mem, ram_base, phys_ram);          // 0.0
/*92  */     dinfo = drive_get(IF_PFLASH, 0, 0);                                          // 0.0
/*94  */     /* Spansion S29NS128P */                                                     // 0.0
/*96  */     pflash_cfi02_register(flash_base, NULL, "lm32_evr.flash", flash_size,        // 0.0
/*98  */                           dinfo ? blk_by_legacy_dinfo(dinfo) : NULL,             // 0.0
/*100 */                           flash_sector_size, flash_size / flash_sector_size,     // 0.0
/*102 */                           1, 2, 0x01, 0x7e, 0x43, 0x00, 0x555, 0x2aa, 1);        // 0.0
/*106 */     /* create irq lines */                                                       // 0.0
/*108 */     env->pic_state = lm32_pic_init(qemu_allocate_irq(cpu_irq_handler, cpu, 0));  // 0.0
/*110 */     for (i = 0; i < 32; i++) {                                                   // 0.0
/*112 */         irq[i] = qdev_get_gpio_in(env->pic_state, i);                            // 0.0
/*114 */     }                                                                            // 0.0
/*118 */     lm32_uart_create(uart0_base, irq[uart0_irq], serial_hds[0]);                 // 0.0
/*120 */     sysbus_create_simple("lm32-timer", timer0_base, irq[timer0_irq]);            // 0.0
/*122 */     sysbus_create_simple("lm32-timer", timer1_base, irq[timer1_irq]);            // 0.0
/*126 */     /* make sure juart isn't the first chardev */                                // 0.0
/*128 */     env->juart_state = lm32_juart_init(serial_hds[1]);                           // 0.0
/*132 */     reset_info->bootstrap_pc = flash_base;                                       // 0.0
/*136 */     if (kernel_filename) {                                                       // 0.0
/*138 */         uint64_t entry;                                                          // 0.0
/*140 */         int kernel_size;                                                         // 0.0
/*144 */         kernel_size = load_elf(kernel_filename, NULL, NULL, &entry, NULL, NULL,  // 0.0
/*146 */                                1, EM_LATTICEMICO32, 0, 0);                       // 0.0
/*148 */         reset_info->bootstrap_pc = entry;                                        // 0.0
/*152 */         if (kernel_size < 0) {                                                   // 0.0
/*154 */             kernel_size = load_image_targphys(kernel_filename, ram_base,         // 0.0
/*156 */                                               ram_size);                         // 0.0
/*158 */             reset_info->bootstrap_pc = ram_base;                                 // 0.0
/*160 */         }                                                                        // 0.0
/*164 */         if (kernel_size < 0) {                                                   // 0.0
/*166 */             fprintf(stderr, "qemu: could not load kernel '%s'\n",                // 0.0
/*168 */                     kernel_filename);                                            // 0.0
/*170 */             exit(1);                                                             // 0.0
/*172 */         }                                                                        // 0.0
/*174 */     }                                                                            // 0.0
/*178 */     qemu_register_reset(main_cpu_reset, reset_info);                             // 0.0
/*180 */ }                                                                                // 0.0
