// commit message qemu@a8170e5e97 (target=0, prob=0.6457112, correct=False): Rename target_phys_addr_t to hwaddr
/*0   */ static void lm32_evr_init(QEMUMachineInitArgs *args)                             // (9) 0.03906
/*2   */ {                                                                                // (25) 0.001953
/*4   */     const char *cpu_model = args->cpu_model;                                     // (17) 0.03125
/*6   */     const char *kernel_filename = args->kernel_filename;                         // (16) 0.03125
/*8   */     LM32CPU *cpu;                                                                // (22) 0.01758
/*10  */     CPULM32State *env;                                                           // (19) 0.01953
/*12  */     DriveInfo *dinfo;                                                            // (21) 0.01758
/*14  */     MemoryRegion *address_space_mem =  get_system_memory();                      // (14) 0.03711
/*16  */     MemoryRegion *phys_ram = g_new(MemoryRegion, 1);                             // (15) 0.03711
/*18  */     qemu_irq *cpu_irq, irq[32];                                                  // (11) 0.03906
/*20  */     ResetInfo *reset_info;                                                       // (20) 0.01953
/*22  */     int i;                                                                       // (24) 0.01172
/*26  */     /* memory map */                                                             // (23) 0.01367
/*28  */     target_phys_addr_t flash_base  = 0x04000000;                                 // (13) 0.03906
/*30  */     size_t flash_sector_size       = 256 * 1024;                                 // (6) 0.04297
/*32  */     size_t flash_size              = 32 * 1024 * 1024;                           // (2) 0.05664
/*34  */     target_phys_addr_t ram_base    = 0x08000000;                                 // (7) 0.04297
/*36  */     size_t ram_size                = 64 * 1024 * 1024;                           // (0) 0.06055
/*38  */     target_phys_addr_t timer0_base = 0x80002000;                                 // (12) 0.03906
/*40  */     target_phys_addr_t uart0_base  = 0x80006000;                                 // (5) 0.04297
/*42  */     target_phys_addr_t timer1_base = 0x8000a000;                                 // (8) 0.04102
/*44  */     int uart0_irq                  = 0;                                          // (1) 0.05859
/*46  */     int timer0_irq                 = 1;                                          // (4) 0.05469
/*48  */     int timer1_irq                 = 3;                                          // (3) 0.05469
/*52  */     reset_info = g_malloc0(sizeof(ResetInfo));                                   // (10) 0.03906
/*56  */     if (cpu_model == NULL) {                                                     // (18) 0.02344
/*58  */         cpu_model = "lm32-full";                                                 // 0.0
/*60  */     }                                                                            // 0.0
/*62  */     cpu = cpu_lm32_init(cpu_model);                                              // 0.0
/*64  */     env = &cpu->env;                                                             // 0.0
/*66  */     reset_info->cpu = cpu;                                                       // 0.0
/*70  */     reset_info->flash_base = flash_base;                                         // 0.0
/*74  */     memory_region_init_ram(phys_ram, "lm32_evr.sdram", ram_size);                // 0.0
/*76  */     vmstate_register_ram_global(phys_ram);                                       // 0.0
/*78  */     memory_region_add_subregion(address_space_mem, ram_base, phys_ram);          // 0.0
/*82  */     dinfo = drive_get(IF_PFLASH, 0, 0);                                          // 0.0
/*84  */     /* Spansion S29NS128P */                                                     // 0.0
/*86  */     pflash_cfi02_register(flash_base, NULL, "lm32_evr.flash", flash_size,        // 0.0
/*88  */                           dinfo ? dinfo->bdrv : NULL, flash_sector_size,         // 0.0
/*90  */                           flash_size / flash_sector_size, 1, 2,                  // 0.0
/*92  */                           0x01, 0x7e, 0x43, 0x00, 0x555, 0x2aa, 1);              // 0.0
/*96  */     /* create irq lines */                                                       // 0.0
/*98  */     cpu_irq = qemu_allocate_irqs(cpu_irq_handler, env, 1);                       // 0.0
/*100 */     env->pic_state = lm32_pic_init(*cpu_irq);                                    // 0.0
/*102 */     for (i = 0; i < 32; i++) {                                                   // 0.0
/*104 */         irq[i] = qdev_get_gpio_in(env->pic_state, i);                            // 0.0
/*106 */     }                                                                            // 0.0
/*110 */     sysbus_create_simple("lm32-uart", uart0_base, irq[uart0_irq]);               // 0.0
/*112 */     sysbus_create_simple("lm32-timer", timer0_base, irq[timer0_irq]);            // 0.0
/*114 */     sysbus_create_simple("lm32-timer", timer1_base, irq[timer1_irq]);            // 0.0
/*118 */     /* make sure juart isn't the first chardev */                                // 0.0
/*120 */     env->juart_state = lm32_juart_init();                                        // 0.0
/*124 */     reset_info->bootstrap_pc = flash_base;                                       // 0.0
/*128 */     if (kernel_filename) {                                                       // 0.0
/*130 */         uint64_t entry;                                                          // 0.0
/*132 */         int kernel_size;                                                         // 0.0
/*136 */         kernel_size = load_elf(kernel_filename, NULL, NULL, &entry, NULL, NULL,  // 0.0
/*138 */                                1, ELF_MACHINE, 0);                               // 0.0
/*140 */         reset_info->bootstrap_pc = entry;                                        // 0.0
/*144 */         if (kernel_size < 0) {                                                   // 0.0
/*146 */             kernel_size = load_image_targphys(kernel_filename, ram_base,         // 0.0
/*148 */                                               ram_size);                         // 0.0
/*150 */             reset_info->bootstrap_pc = ram_base;                                 // 0.0
/*152 */         }                                                                        // 0.0
/*156 */         if (kernel_size < 0) {                                                   // 0.0
/*158 */             fprintf(stderr, "qemu: could not load kernel '%s'\n",                // 0.0
/*160 */                     kernel_filename);                                            // 0.0
/*162 */             exit(1);                                                             // 0.0
/*164 */         }                                                                        // 0.0
/*166 */     }                                                                            // 0.0
/*170 */     qemu_register_reset(main_cpu_reset, reset_info);                             // 0.0
/*172 */ }                                                                                // 0.0
