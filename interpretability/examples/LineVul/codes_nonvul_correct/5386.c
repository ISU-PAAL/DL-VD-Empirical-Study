// commit message qemu@b3a2319792 (target=0, prob=0.3705666, correct=True): Use qemu_irqs between CPUs and interrupt controller Fix interrupt priority handling which prevented SMP from working
/*0  */ void *slavio_intctl_init(target_phys_addr_t addr, target_phys_addr_t addrg,                                      // (7) 0.05859
/*2  */                          const uint32_t *intbit_to_level,                                                        // (4) 0.07227
/*4  */                          qemu_irq **irq, qemu_irq **cpu_irq,                                                     // (2) 0.08984
/*6  */                          unsigned int cputimer)                                                                  // (6) 0.05859
/*10 */ {                                                                                                                // (17) 0.001953
/*12 */     int slavio_intctl_io_memory, slavio_intctlm_io_memory, i;                                                    // (8) 0.05664
/*14 */     SLAVIO_INTCTLState *s;                                                                                       // (13) 0.02734
/*18 */     s = qemu_mallocz(sizeof(SLAVIO_INTCTLState));                                                                // (10) 0.04883
/*20 */     if (!s)                                                                                                      // (15) 0.01367
/*22 */         return NULL;                                                                                             // (14) 0.01953
/*26 */     s->intbit_to_level = intbit_to_level;                                                                        // (12) 0.03711
/*28 */     for (i = 0; i < MAX_CPUS; i++) {                                                                             // (11) 0.03711
/*30 */ 	slavio_intctl_io_memory = cpu_register_io_memory(0, slavio_intctl_mem_read, slavio_intctl_mem_write, s);        // (3) 0.08984
/*32 */ 	cpu_register_physical_memory(addr + i * TARGET_PAGE_SIZE, INTCTL_SIZE,                                          // (9) 0.05273
/*34 */                                      slavio_intctl_io_memory);                                                   // (1) 0.0918
/*36 */     }                                                                                                            // (16) 0.007812
/*40 */     slavio_intctlm_io_memory = cpu_register_io_memory(0, slavio_intctlm_mem_read, slavio_intctlm_mem_write, s);  // (0) 0.09961
/*42 */     cpu_register_physical_memory(addrg, INTCTLM_SIZE, slavio_intctlm_io_memory);                                 // (5) 0.0625
/*46 */     register_savevm("slavio_intctl", addr, 1, slavio_intctl_save, slavio_intctl_load, s);                        // 0.0
/*48 */     qemu_register_reset(slavio_intctl_reset, s);                                                                 // 0.0
/*50 */     *irq = qemu_allocate_irqs(slavio_set_irq, s, 32);                                                            // 0.0
/*54 */     *cpu_irq = qemu_allocate_irqs(slavio_set_timer_irq_cpu, s, MAX_CPUS);                                        // 0.0
/*56 */     s->cputimer_bit = 1 << s->intbit_to_level[cputimer];                                                         // 0.0
/*58 */     slavio_intctl_reset(s);                                                                                      // 0.0
/*60 */     return s;                                                                                                    // 0.0
/*62 */ }                                                                                                                // 0.0
