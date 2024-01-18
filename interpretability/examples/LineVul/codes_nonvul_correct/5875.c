// commit message qemu@e5ba83c53a (target=0, prob=0.2784012, correct=True): PPC: 440: Default to 440EP CPU
/*0   */ CPUState *ppc440ep_init(MemoryRegion *address_space_mem, ram_addr_t *ram_size,    // (6) 0.05663
/*2   */                         PCIBus **pcip, const unsigned int pci_irq_nrs[4],         // (0) 0.08397
/*4   */                         int do_init, const char *cpu_model)                       // (1) 0.06836
/*6   */ {                                                                                 // (23) 0.001957
/*8   */     MemoryRegion *ram_memories                                                    // (17) 0.01953
/*10  */         = g_malloc(PPC440EP_SDRAM_NR_BANKS * sizeof(*ram_memories));              // (2) 0.06835
/*12  */     target_phys_addr_t ram_bases[PPC440EP_SDRAM_NR_BANKS];                        // (4) 0.05859
/*14  */     target_phys_addr_t ram_sizes[PPC440EP_SDRAM_NR_BANKS];                        // (5) 0.05859
/*16  */     CPUState *env;                                                                // (18) 0.01562
/*18  */     qemu_irq *pic;                                                                // (14) 0.02352
/*20  */     qemu_irq *irqs;                                                               // (12) 0.02539
/*22  */     qemu_irq *pci_irqs;                                                           // (11) 0.03125
/*26  */     if (cpu_model == NULL) {                                                      // (15) 0.02343
/*28  */         cpu_model = "440-Xilinx"; // XXX: should be 440EP                         // (7) 0.04882
/*30  */     }                                                                             // (22) 0.007811
/*32  */     env = cpu_init(cpu_model);                                                    // (13) 0.02539
/*34  */     if (!env) {                                                                   // (19) 0.01562
/*36  */         fprintf(stderr, "Unable to initialize CPU!\n");                           // (8) 0.04687
/*38  */         exit(1);                                                                  // (16) 0.02148
/*40  */     }                                                                             // (21) 0.007811
/*44  */     ppc_booke_timers_init(env, 400000000, 0);                                     // (9) 0.04101
/*46  */     ppc_dcr_init(env, NULL, NULL);                                                // (10) 0.0332
/*50  */     /* interrupt controller */                                                    // (20) 0.01367
/*52  */     irqs = g_malloc0(sizeof(qemu_irq) * PPCUIC_OUTPUT_NB);                        // (3) 0.0664
/*54  */     irqs[PPCUIC_OUTPUT_INT] = ((qemu_irq *)env->irq_inputs)[PPC40x_INPUT_INT];    // 0.0
/*56  */     irqs[PPCUIC_OUTPUT_CINT] = ((qemu_irq *)env->irq_inputs)[PPC40x_INPUT_CINT];  // 0.0
/*58  */     pic = ppcuic_init(env, irqs, 0x0C0, 0, 1);                                    // 0.0
/*62  */     /* SDRAM controller */                                                        // 0.0
/*64  */     memset(ram_bases, 0, sizeof(ram_bases));                                      // 0.0
/*66  */     memset(ram_sizes, 0, sizeof(ram_sizes));                                      // 0.0
/*68  */     *ram_size = ppc4xx_sdram_adjust(*ram_size, PPC440EP_SDRAM_NR_BANKS,           // 0.0
/*70  */                                     ram_memories,                                 // 0.0
/*72  */                                     ram_bases, ram_sizes,                         // 0.0
/*74  */                                     ppc440ep_sdram_bank_sizes);                   // 0.0
/*76  */     /* XXX 440EP's ECC interrupts are on UIC1, but we've only created UIC0. */    // 0.0
/*78  */     ppc4xx_sdram_init(env, pic[14], PPC440EP_SDRAM_NR_BANKS, ram_memories,        // 0.0
/*80  */                       ram_bases, ram_sizes, do_init);                             // 0.0
/*84  */     /* PCI */                                                                     // 0.0
/*86  */     pci_irqs = g_malloc(sizeof(qemu_irq) * 4);                                    // 0.0
/*88  */     pci_irqs[0] = pic[pci_irq_nrs[0]];                                            // 0.0
/*90  */     pci_irqs[1] = pic[pci_irq_nrs[1]];                                            // 0.0
/*92  */     pci_irqs[2] = pic[pci_irq_nrs[2]];                                            // 0.0
/*94  */     pci_irqs[3] = pic[pci_irq_nrs[3]];                                            // 0.0
/*96  */     *pcip = ppc4xx_pci_init(env, pci_irqs,                                        // 0.0
/*98  */                             PPC440EP_PCI_CONFIG,                                  // 0.0
/*100 */                             PPC440EP_PCI_INTACK,                                  // 0.0
/*102 */                             PPC440EP_PCI_SPECIAL,                                 // 0.0
/*104 */                             PPC440EP_PCI_REGS);                                   // 0.0
/*106 */     if (!*pcip)                                                                   // 0.0
/*108 */         printf("couldn't create PCI controller!\n");                              // 0.0
/*112 */     isa_mmio_init(PPC440EP_PCI_IO, PPC440EP_PCI_IOLEN);                           // 0.0
/*116 */     if (serial_hds[0] != NULL) {                                                  // 0.0
/*118 */         serial_mm_init(address_space_mem, 0xef600300, 0, pic[0],                  // 0.0
/*120 */                        PPC_SERIAL_MM_BAUDBASE, serial_hds[0],                     // 0.0
/*122 */                        DEVICE_BIG_ENDIAN);                                        // 0.0
/*124 */     }                                                                             // 0.0
/*126 */     if (serial_hds[1] != NULL) {                                                  // 0.0
/*128 */         serial_mm_init(address_space_mem, 0xef600400, 0, pic[1],                  // 0.0
/*130 */                        PPC_SERIAL_MM_BAUDBASE, serial_hds[1],                     // 0.0
/*132 */                        DEVICE_BIG_ENDIAN);                                        // 0.0
/*134 */     }                                                                             // 0.0
/*138 */     return env;                                                                   // 0.0
/*140 */ }                                                                                 // 0.0
