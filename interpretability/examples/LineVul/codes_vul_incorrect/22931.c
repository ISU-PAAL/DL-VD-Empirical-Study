// commit message qemu@4482e05cbb (target=1, prob=0.41358945, correct=False): cpu: make cpu_generic_init() abort QEMU on error
/*0  */ static PowerPCCPU *ppc440_init_xilinx(ram_addr_t *ram_size,                       // (7) 0.05078
/*2  */                                       int do_init,                                // (4) 0.08203
/*4  */                                       const char *cpu_model,                      // (3) 0.08594
/*6  */                                       uint32_t sysclk)                            // (1) 0.08789
/*8  */ {                                                                                 // (21) 0.001953
/*10 */     PowerPCCPU *cpu;                                                              // (14) 0.01953
/*12 */     CPUPPCState *env;                                                             // (15) 0.01953
/*14 */     qemu_irq *irqs;                                                               // (12) 0.02539
/*18 */     cpu = POWERPC_CPU(cpu_generic_init(TYPE_POWERPC_CPU, cpu_model));             // (6) 0.05469
/*20 */     if (cpu == NULL) {                                                            // (16) 0.01953
/*22 */         fprintf(stderr, "Unable to initialize CPU!\n");                           // (9) 0.04688
/*24 */         exit(1);                                                                  // (13) 0.02148
/*26 */     }                                                                             // (20) 0.007812
/*28 */     env = &cpu->env;                                                              // (17) 0.01953
/*32 */     ppc_booke_timers_init(cpu, sysclk, 0/* no flags */);                          // (8) 0.05078
/*36 */     ppc_dcr_init(env, NULL, NULL);                                                // (11) 0.0332
/*40 */     /* interrupt controller */                                                    // (18) 0.01367
/*42 */     irqs = g_malloc0(sizeof(qemu_irq) * PPCUIC_OUTPUT_NB);                        // (5) 0.06641
/*44 */     irqs[PPCUIC_OUTPUT_INT] = ((qemu_irq *)env->irq_inputs)[PPC40x_INPUT_INT];    // (2) 0.08594
/*46 */     irqs[PPCUIC_OUTPUT_CINT] = ((qemu_irq *)env->irq_inputs)[PPC40x_INPUT_CINT];  // (0) 0.08984
/*48 */     ppcuic_init(env, irqs, 0x0C0, 0, 1);                                          // (10) 0.04688
/*50 */     return cpu;                                                                   // (19) 0.01172
/*52 */ }                                                                                 // 0.0
