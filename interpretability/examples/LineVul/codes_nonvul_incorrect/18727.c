// commit message qemu@13f1c77364 (target=0, prob=0.55424976, correct=False): openrisc: Initial SMP support
/*0  */ static void openrisc_sim_init(MachineState *machine)                            // (12) 0.0293
/*2  */ {                                                                               // (25) 0.001953
/*4  */     ram_addr_t ram_size = machine->ram_size;                                    // (9) 0.03516
/*6  */     const char *cpu_model = machine->cpu_model;                                 // (11) 0.03125
/*8  */     const char *kernel_filename = machine->kernel_filename;                     // (10) 0.03125
/*10 */     OpenRISCCPU *cpu = NULL;                                                    // (19) 0.02539
/*12 */     MemoryRegion *ram;                                                          // (21) 0.01563
/*14 */     int n;                                                                      // (22) 0.01172
/*18 */     if (!cpu_model) {                                                           // (20) 0.01953
/*20 */         cpu_model = "or1200";                                                   // (15) 0.0293
/*22 */     }                                                                           // (23) 0.007812
/*26 */     for (n = 0; n < smp_cpus; n++) {                                            // (8) 0.03906
/*28 */         cpu = OPENRISC_CPU(cpu_generic_init(TYPE_OPENRISC_CPU, cpu_model));     // (2) 0.06641
/*30 */         qemu_register_reset(main_cpu_reset, cpu);                               // (6) 0.04492
/*32 */         main_cpu_reset(cpu);                                                    // (16) 0.0293
/*34 */     }                                                                           // (24) 0.007812
/*38 */     ram = g_malloc(sizeof(*ram));                                               // (13) 0.0293
/*40 */     memory_region_init_ram(ram, NULL, "openrisc.ram", ram_size, &error_fatal);  // (3) 0.0625
/*42 */     memory_region_add_subregion(get_system_memory(), 0, ram);                   // (7) 0.04297
/*46 */     cpu_openrisc_pic_init(cpu);                                                 // (17) 0.0293
/*48 */     cpu_openrisc_clock_init(cpu);                                               // (14) 0.0293
/*52 */     serial_mm_init(get_system_memory(), 0x90000000, 0, cpu->env.irq[2],         // (4) 0.06055
/*54 */                    115200, serial_hds[0], DEVICE_NATIVE_ENDIAN);                // (1) 0.07227
/*58 */     if (nd_table[0].used) {                                                     // (18) 0.02734
/*60 */         openrisc_sim_net_init(get_system_memory(), 0x92000000,                  // (5) 0.05664
/*62 */                               0x92000400, cpu->env.irq[4], nd_table);           // (0) 0.0957
/*64 */     }                                                                           // 0.0
/*68 */     cpu_openrisc_load_kernel(ram_size, kernel_filename, cpu);                   // 0.0
/*70 */ }                                                                               // 0.0
