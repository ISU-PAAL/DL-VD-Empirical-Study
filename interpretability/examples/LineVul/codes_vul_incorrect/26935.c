// commit message qemu@7b62a95504 (target=1, prob=0.013544783, correct=False): Add missing definition for number of input pins for the PowerPC 970 bus. Use proper INPUT_NB definitions to allocate PowerPC input pins structure,   fixing a buffer overflow in the 6xx bus case.
/*0 */ void ppc970_irq_init (CPUState *env)                                         // (1) 0.2381
/*2 */ {                                                                            // (2) 0.01587
/*4 */     env->irq_inputs = (void **)qemu_allocate_irqs(&ppc970_set_irq, env, 7);  // (0) 0.6032
/*6 */ }                                                                            // (3) 0.01587
