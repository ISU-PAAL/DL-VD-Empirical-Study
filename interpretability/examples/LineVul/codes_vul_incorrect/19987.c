// commit message qemu@4482e05cbb (target=1, prob=0.093528725, correct=False): cpu: make cpu_generic_init() abort QEMU on error
/*0  */ static void cpu_devinit(const char *cpu_model, unsigned int id,          // (6) 0.05149
/*2  */                         uint64_t prom_addr, qemu_irq **cpu_irqs)         // (0) 0.1165
/*4  */ {                                                                        // (21) 0.00271
/*6  */     CPUState *cs;                                                        // (17) 0.02168
/*8  */     SPARCCPU *cpu;                                                       // (13) 0.0271
/*10 */     CPUSPARCState *env;                                                  // (11) 0.02981
/*14 */     cpu = SPARC_CPU(cpu_generic_init(TYPE_SPARC_CPU, cpu_model));        // (3) 0.07317
/*16 */     if (cpu == NULL) {                                                   // (14) 0.0271
/*18 */         fprintf(stderr, "qemu: Unable to find Sparc CPU definition\n");  // (2) 0.07859
/*20 */         exit(1);                                                         // (12) 0.02981
/*22 */     }                                                                    // (19) 0.01084
/*24 */     env = &cpu->env;                                                     // (15) 0.0271
/*28 */     cpu_sparc_set_id(env, id);                                           // (7) 0.04607
/*30 */     if (id == 0) {                                                       // (16) 0.0271
/*32 */         qemu_register_reset(main_cpu_reset, cpu);                        // (4) 0.06233
/*34 */     } else {                                                             // (18) 0.01626
/*36 */         qemu_register_reset(secondary_cpu_reset, cpu);                   // (5) 0.06233
/*38 */         cs = CPU(cpu);                                                   // (9) 0.03523
/*40 */         cs->halted = 1;                                                  // (8) 0.03794
/*42 */     }                                                                    // (20) 0.01084
/*44 */     *cpu_irqs = qemu_allocate_irqs(cpu_set_irq, cpu, MAX_PILS);          // (1) 0.08943
/*46 */     env->prom_addr = prom_addr;                                          // (10) 0.03523
/*48 */ }                                                                        // (22) 0.00271
