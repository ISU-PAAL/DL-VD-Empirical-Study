// commit message qemu@4482e05cbb (target=1, prob=0.35961172, correct=False): cpu: make cpu_generic_init() abort QEMU on error
/*0  */ static void puv3_init(MachineState *machine)                               // (10) 0.03779
/*2  */ {                                                                          // (23) 0.002907
/*4  */     ram_addr_t ram_size = machine->ram_size;                               // (2) 0.05233
/*6  */     const char *cpu_model = machine->cpu_model;                            // (7) 0.04651
/*8  */     const char *kernel_filename = machine->kernel_filename;                // (8) 0.04651
/*10 */     const char *initrd_filename = machine->initrd_filename;                // (3) 0.05233
/*12 */     CPUUniCore32State *env;                                                // (12) 0.03488
/*14 */     UniCore32CPU *cpu;                                                     // (16) 0.02907
/*18 */     if (initrd_filename) {                                                 // (13) 0.03198
/*20 */         error_report("Please use kernel built-in initramdisk");            // (1) 0.06105
/*22 */         exit(1);                                                           // (14) 0.03198
/*24 */     }                                                                      // (20) 0.01163
/*28 */     if (!cpu_model) {                                                      // (17) 0.02907
/*30 */         cpu_model = "UniCore-II";                                          // (4) 0.05233
/*32 */     }                                                                      // (21) 0.01163
/*36 */     cpu = UNICORE32_CPU(cpu_generic_init(TYPE_UNICORE32_CPU, cpu_model));  // (0) 0.09012
/*38 */     if (!cpu) {                                                            // (19) 0.02326
/*40 */         error_report("Unable to find CPU definition");                     // (5) 0.05233
/*42 */         exit(1);                                                           // (15) 0.03198
/*44 */     }                                                                      // (22) 0.01163
/*46 */     env = &cpu->env;                                                       // (18) 0.02907
/*50 */     puv3_soc_init(env);                                                    // (11) 0.03779
/*52 */     puv3_board_init(env, ram_size);                                        // (6) 0.04942
/*54 */     puv3_load_kernel(kernel_filename);                                     // (9) 0.0436
/*56 */ }                                                                          // (24) 0.002907
