// commit message qemu@4482e05cbb (target=1, prob=0.6416214, correct=True): cpu: make cpu_generic_init() abort QEMU on error
/*0   */ static void bamboo_init(MachineState *machine)                                    // (19) 0.02179
/*2   */ {                                                                                 // (31) 0.002425
/*4   */     ram_addr_t ram_size = machine->ram_size;                                      // (8) 0.03497
/*6   */     const char *kernel_filename = machine->kernel_filename;                       // (12) 0.03105
/*8   */     const char *kernel_cmdline = machine->kernel_cmdline;                         // (9) 0.03494
/*10  */     const char *initrd_filename = machine->initrd_filename;                       // (7) 0.035
/*12  */     unsigned int pci_irq_nrs[4] = { 28, 27, 26, 25 };                             // (4) 0.04853
/*14  */     MemoryRegion *address_space_mem = get_system_memory();                        // (6) 0.03514
/*16  */     MemoryRegion *isa = g_new(MemoryRegion, 1);                                   // (10) 0.033
/*18  */     MemoryRegion *ram_memories                                                    // (23) 0.01942
/*20  */         = g_malloc(PPC440EP_SDRAM_NR_BANKS * sizeof(*ram_memories));              // (0) 0.06792
/*22  */     hwaddr ram_bases[PPC440EP_SDRAM_NR_BANKS];                                    // (2) 0.05055
/*24  */     hwaddr ram_sizes[PPC440EP_SDRAM_NR_BANKS];                                    // (3) 0.05048
/*26  */     qemu_irq *pic;                                                                // (17) 0.02329
/*28  */     qemu_irq *irqs;                                                               // (15) 0.02522
/*30  */     PCIBus *pcibus;                                                               // (25) 0.01941
/*32  */     PowerPCCPU *cpu;                                                              // (22) 0.01942
/*34  */     CPUPPCState *env;                                                             // (21) 0.01944
/*36  */     uint64_t elf_entry;                                                           // (20) 0.02138
/*38  */     uint64_t elf_lowaddr;                                                         // (16) 0.02341
/*40  */     hwaddr loadaddr = 0;                                                          // (18) 0.02183
/*42  */     target_long initrd_size = 0;                                                  // (14) 0.02712
/*44  */     DeviceState *dev;                                                             // (26) 0.01638
/*46  */     int success;                                                                  // (28) 0.0117
/*48  */     int i;                                                                        // (29) 0.01167
/*52  */     /* Setup CPU. */                                                              // (27) 0.01561
/*54  */     if (machine->cpu_model == NULL) {                                             // (13) 0.02718
/*56  */         machine->cpu_model = "440EP";                                             // (11) 0.033
/*58  */     }                                                                             // (30) 0.007769
/*60  */     cpu = POWERPC_CPU(cpu_generic_init(TYPE_POWERPC_CPU, machine->cpu_model));    // (1) 0.0583
/*62  */     if (cpu == NULL) {                                                            // (24) 0.01941
/*64  */         fprintf(stderr, "Unable to initialize CPU!\n");                           // (5) 0.04658
/*66  */         exit(1);                                                                  // 0.0
/*68  */     }                                                                             // 0.0
/*70  */     env = &cpu->env;                                                              // 0.0
/*74  */     if (env->mmu_model != POWERPC_MMU_BOOKE) {                                    // 0.0
/*76  */         fprintf(stderr, "MMU model %i not supported by this machine.\n",          // 0.0
/*78  */             env->mmu_model);                                                      // 0.0
/*80  */         exit(1);                                                                  // 0.0
/*82  */     }                                                                             // 0.0
/*86  */     qemu_register_reset(main_cpu_reset, cpu);                                     // 0.0
/*88  */     ppc_booke_timers_init(cpu, 400000000, 0);                                     // 0.0
/*90  */     ppc_dcr_init(env, NULL, NULL);                                                // 0.0
/*94  */     /* interrupt controller */                                                    // 0.0
/*96  */     irqs = g_malloc0(sizeof(qemu_irq) * PPCUIC_OUTPUT_NB);                        // 0.0
/*98  */     irqs[PPCUIC_OUTPUT_INT] = ((qemu_irq *)env->irq_inputs)[PPC40x_INPUT_INT];    // 0.0
/*100 */     irqs[PPCUIC_OUTPUT_CINT] = ((qemu_irq *)env->irq_inputs)[PPC40x_INPUT_CINT];  // 0.0
/*102 */     pic = ppcuic_init(env, irqs, 0x0C0, 0, 1);                                    // 0.0
/*106 */     /* SDRAM controller */                                                        // 0.0
/*108 */     memset(ram_bases, 0, sizeof(ram_bases));                                      // 0.0
/*110 */     memset(ram_sizes, 0, sizeof(ram_sizes));                                      // 0.0
/*112 */     ram_size = ppc4xx_sdram_adjust(ram_size, PPC440EP_SDRAM_NR_BANKS,             // 0.0
/*114 */                                    ram_memories,                                  // 0.0
/*116 */                                    ram_bases, ram_sizes,                          // 0.0
/*118 */                                    ppc440ep_sdram_bank_sizes);                    // 0.0
/*120 */     /* XXX 440EP's ECC interrupts are on UIC1, but we've only created UIC0. */    // 0.0
/*122 */     ppc4xx_sdram_init(env, pic[14], PPC440EP_SDRAM_NR_BANKS, ram_memories,        // 0.0
/*124 */                       ram_bases, ram_sizes, 1);                                   // 0.0
/*128 */     /* PCI */                                                                     // 0.0
/*130 */     dev = sysbus_create_varargs(TYPE_PPC4xx_PCI_HOST_BRIDGE,                      // 0.0
/*132 */                                 PPC440EP_PCI_CONFIG,                              // 0.0
/*134 */                                 pic[pci_irq_nrs[0]], pic[pci_irq_nrs[1]],         // 0.0
/*136 */                                 pic[pci_irq_nrs[2]], pic[pci_irq_nrs[3]],         // 0.0
/*138 */                                 NULL);                                            // 0.0
/*140 */     pcibus = (PCIBus *)qdev_get_child_bus(dev, "pci.0");                          // 0.0
/*142 */     if (!pcibus) {                                                                // 0.0
/*144 */         fprintf(stderr, "couldn't create PCI controller!\n");                     // 0.0
/*146 */         exit(1);                                                                  // 0.0
/*148 */     }                                                                             // 0.0
/*152 */     memory_region_init_alias(isa, NULL, "isa_mmio",                               // 0.0
/*154 */                              get_system_io(), 0, PPC440EP_PCI_IOLEN);             // 0.0
/*156 */     memory_region_add_subregion(get_system_memory(), PPC440EP_PCI_IO, isa);       // 0.0
/*160 */     if (serial_hds[0] != NULL) {                                                  // 0.0
/*162 */         serial_mm_init(address_space_mem, 0xef600300, 0, pic[0],                  // 0.0
/*164 */                        PPC_SERIAL_MM_BAUDBASE, serial_hds[0],                     // 0.0
/*166 */                        DEVICE_BIG_ENDIAN);                                        // 0.0
/*168 */     }                                                                             // 0.0
/*170 */     if (serial_hds[1] != NULL) {                                                  // 0.0
/*172 */         serial_mm_init(address_space_mem, 0xef600400, 0, pic[1],                  // 0.0
/*174 */                        PPC_SERIAL_MM_BAUDBASE, serial_hds[1],                     // 0.0
/*176 */                        DEVICE_BIG_ENDIAN);                                        // 0.0
/*178 */     }                                                                             // 0.0
/*182 */     if (pcibus) {                                                                 // 0.0
/*184 */         /* Register network interfaces. */                                        // 0.0
/*186 */         for (i = 0; i < nb_nics; i++) {                                           // 0.0
/*188 */             /* There are no PCI NICs on the Bamboo board, but there are           // 0.0
/*190 */              * PCI slots, so we can pick whatever default model we want. */       // 0.0
/*192 */             pci_nic_init_nofail(&nd_table[i], pcibus, "e1000", NULL);             // 0.0
/*194 */         }                                                                         // 0.0
/*196 */     }                                                                             // 0.0
/*200 */     /* Load kernel. */                                                            // 0.0
/*202 */     if (kernel_filename) {                                                        // 0.0
/*204 */         success = load_uimage(kernel_filename, &entry, &loadaddr, NULL,           // 0.0
/*206 */                               NULL, NULL);                                        // 0.0
/*208 */         if (success < 0) {                                                        // 0.0
/*210 */             success = load_elf(kernel_filename, NULL, NULL, &elf_entry,           // 0.0
/*212 */                                &elf_lowaddr, NULL, 1, PPC_ELF_MACHINE,            // 0.0
/*214 */                                0, 0);                                             // 0.0
/*216 */             entry = elf_entry;                                                    // 0.0
/*218 */             loadaddr = elf_lowaddr;                                               // 0.0
/*220 */         }                                                                         // 0.0
/*222 */         /* XXX try again as binary */                                             // 0.0
/*224 */         if (success < 0) {                                                        // 0.0
/*226 */             fprintf(stderr, "qemu: could not load kernel '%s'\n",                 // 0.0
/*228 */                     kernel_filename);                                             // 0.0
/*230 */             exit(1);                                                              // 0.0
/*232 */         }                                                                         // 0.0
/*234 */     }                                                                             // 0.0
/*238 */     /* Load initrd. */                                                            // 0.0
/*240 */     if (initrd_filename) {                                                        // 0.0
/*242 */         initrd_size = load_image_targphys(initrd_filename, RAMDISK_ADDR,          // 0.0
/*244 */                                           ram_size - RAMDISK_ADDR);               // 0.0
/*248 */         if (initrd_size < 0) {                                                    // 0.0
/*250 */             fprintf(stderr, "qemu: could not load ram disk '%s' at %x\n",         // 0.0
/*252 */                     initrd_filename, RAMDISK_ADDR);                               // 0.0
/*254 */             exit(1);                                                              // 0.0
/*256 */         }                                                                         // 0.0
/*258 */     }                                                                             // 0.0
/*262 */     /* If we're loading a kernel directly, we must load the device tree too. */   // 0.0
/*264 */     if (kernel_filename) {                                                        // 0.0
/*266 */         if (bamboo_load_device_tree(FDT_ADDR, ram_size, RAMDISK_ADDR,             // 0.0
/*268 */                                     initrd_size, kernel_cmdline) < 0) {           // 0.0
/*270 */             fprintf(stderr, "couldn't load device tree\n");                       // 0.0
/*272 */             exit(1);                                                              // 0.0
/*274 */         }                                                                         // 0.0
/*276 */     }                                                                             // 0.0
/*278 */ }                                                                                 // 0.0
