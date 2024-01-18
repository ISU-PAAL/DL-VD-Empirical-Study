// commit message qemu@ad0ebb91cd (target=1, prob=0.999183, correct=True): pseries: Convert sPAPR TCEs to use generic IOMMU infrastructure
/*0   */ static void ppc_spapr_init(ram_addr_t ram_size,                                  // (8) 0.03907
/*1   */                            const char *boot_device,                              // (3) 0.0645
/*2   */                            const char *kernel_filename,                          // (5) 0.06444
/*3   */                            const char *kernel_cmdline,                           // (1) 0.0664
/*4   */                            const char *initrd_filename,                          // (2) 0.0664
/*5   */                            const char *cpu_model)                                // (4) 0.06444
/*6   */ {                                                                                // (24) 0.001953
/*7   */     PowerPCCPU *cpu;                                                             // (20) 0.01954
/*8   */     CPUPPCState *env;                                                            // (21) 0.01953
/*9   */     int i;                                                                       // (23) 0.01172
/*10  */     MemoryRegion *sysmem = get_system_memory();                                  // (16) 0.02929
/*11  */     MemoryRegion *ram = g_new(MemoryRegion, 1);                                  // (13) 0.0332
/*12  */     target_phys_addr_t rma_alloc_size, rma_size;                                 // (7) 0.04296
/*13  */     uint32_t initrd_base = 0;                                                    // (17) 0.02734
/*14  */     long kernel_size = 0, initrd_size = 0;                                       // (12) 0.03321
/*15  */     long load_limit, rtas_limit, fw_size;                                        // (11) 0.03712
/*16  */     long pteg_shift = 17;                                                        // (18) 0.02344
/*17  */     char *filename;                                                              // (22) 0.01367
/*18  */     spapr = g_malloc0(sizeof(*spapr));                                           // (10) 0.03906
/*19  */     QLIST_INIT(&spapr->phbs);                                                    // (14) 0.03125
/*20  */     cpu_ppc_hypercall = emulate_spapr_hypercall;                                 // (9) 0.03906
/*21  */     /* Allocate RMA if necessary */                                              // (19) 0.02148
/*22  */     rma_alloc_size = kvmppc_alloc_rma("ppc_spapr.rma", sysmem);                  // (0) 0.06641
/*23  */     if (rma_alloc_size == -1) {                                                  // (15) 0.03125
/*24  */         hw_error("qemu: Unable to create RMA\n");                                // (6) 0.04688
/*25  */         exit(1);                                                                 // 0.0
/*26  */     }                                                                            // 0.0
/*27  */     if (rma_alloc_size && (rma_alloc_size < ram_size)) {                         // 0.0
/*28  */         rma_size = rma_alloc_size;                                               // 0.0
/*29  */     } else {                                                                     // 0.0
/*30  */         rma_size = ram_size;                                                     // 0.0
/*31  */     }                                                                            // 0.0
/*32  */     /* We place the device tree and RTAS just below either the top of the RMA,   // 0.0
/*33  */      * or just below 2GB, whichever is lowere, so that it can be                 // 0.0
/*34  */      * processed with 32-bit real mode code if necessary */                      // 0.0
/*35  */     rtas_limit = MIN(rma_size, 0x80000000);                                      // 0.0
/*36  */     spapr->rtas_addr = rtas_limit - RTAS_MAX_SIZE;                               // 0.0
/*37  */     spapr->fdt_addr = spapr->rtas_addr - FDT_MAX_SIZE;                           // 0.0
/*38  */     load_limit = spapr->fdt_addr - FW_OVERHEAD;                                  // 0.0
/*39  */     /* init CPUs */                                                              // 0.0
/*40  */     if (cpu_model == NULL) {                                                     // 0.0
/*41  */         cpu_model = kvm_enabled() ? "host" : "POWER7";                           // 0.0
/*42  */     }                                                                            // 0.0
/*43  */     for (i = 0; i < smp_cpus; i++) {                                             // 0.0
/*44  */         cpu = cpu_ppc_init(cpu_model);                                           // 0.0
/*45  */         if (cpu == NULL) {                                                       // 0.0
/*46  */             fprintf(stderr, "Unable to find PowerPC CPU definition\n");          // 0.0
/*47  */             exit(1);                                                             // 0.0
/*48  */         }                                                                        // 0.0
/*49  */         env = &cpu->env;                                                         // 0.0
/*50  */         /* Set time-base frequency to 512 MHz */                                 // 0.0
/*51  */         cpu_ppc_tb_init(env, TIMEBASE_FREQ);                                     // 0.0
/*52  */         qemu_register_reset(spapr_cpu_reset, cpu);                               // 0.0
/*53  */         env->hreset_vector = 0x60;                                               // 0.0
/*54  */         env->hreset_excp_prefix = 0;                                             // 0.0
/*55  */         env->gpr[3] = env->cpu_index;                                            // 0.0
/*56  */     }                                                                            // 0.0
/*57  */     /* allocate RAM */                                                           // 0.0
/*58  */     spapr->ram_limit = ram_size;                                                 // 0.0
/*59  */     if (spapr->ram_limit > rma_alloc_size) {                                     // 0.0
/*60  */         ram_addr_t nonrma_base = rma_alloc_size;                                 // 0.0
/*61  */         ram_addr_t nonrma_size = spapr->ram_limit - rma_alloc_size;              // 0.0
/*62  */         memory_region_init_ram(ram, "ppc_spapr.ram", nonrma_size);               // 0.0
/*63  */         vmstate_register_ram_global(ram);                                        // 0.0
/*64  */         memory_region_add_subregion(sysmem, nonrma_base, ram);                   // 0.0
/*65  */     }                                                                            // 0.0
/*66  */     /* allocate hash page table.  For now we always make this 16mb,              // 0.0
/*67  */      * later we should probably make it scale to the size of guest               // 0.0
/*68  */      * RAM */                                                                    // 0.0
/*69  */     spapr->htab_size = 1ULL << (pteg_shift + 7);                                 // 0.0
/*70  */     spapr->htab = qemu_memalign(spapr->htab_size, spapr->htab_size);             // 0.0
/*71  */     for (env = first_cpu; env != NULL; env = env->next_cpu) {                    // 0.0
/*72  */         env->external_htab = spapr->htab;                                        // 0.0
/*73  */         env->htab_base = -1;                                                     // 0.0
/*74  */         env->htab_mask = spapr->htab_size - 1;                                   // 0.0
/*75  */         /* Tell KVM that we're in PAPR mode */                                   // 0.0
/*76  */         env->spr[SPR_SDR1] = (unsigned long)spapr->htab |                        // 0.0
/*77  */                              ((pteg_shift + 7) - 18);                            // 0.0
/*78  */         env->spr[SPR_HIOR] = 0;                                                  // 0.0
/*79  */         if (kvm_enabled()) {                                                     // 0.0
/*80  */             kvmppc_set_papr(env);                                                // 0.0
/*81  */         }                                                                        // 0.0
/*82  */     }                                                                            // 0.0
/*83  */     filename = qemu_find_file(QEMU_FILE_TYPE_BIOS, "spapr-rtas.bin");            // 0.0
/*84  */     spapr->rtas_size = load_image_targphys(filename, spapr->rtas_addr,           // 0.0
/*85  */                                            rtas_limit - spapr->rtas_addr);       // 0.0
/*86  */     if (spapr->rtas_size < 0) {                                                  // 0.0
/*87  */         hw_error("qemu: could not load LPAR rtas '%s'\n", filename);             // 0.0
/*88  */         exit(1);                                                                 // 0.0
/*89  */     }                                                                            // 0.0
/*90  */     if (spapr->rtas_size > RTAS_MAX_SIZE) {                                      // 0.0
/*91  */         hw_error("RTAS too big ! 0x%lx bytes (max is 0x%x)\n",                   // 0.0
/*92  */                  spapr->rtas_size, RTAS_MAX_SIZE);                               // 0.0
/*93  */         exit(1);                                                                 // 0.0
/*94  */     }                                                                            // 0.0
/*95  */     g_free(filename);                                                            // 0.0
/*96  */     /* Set up Interrupt Controller */                                            // 0.0
/*97  */     spapr->icp = xics_system_init(XICS_IRQS);                                    // 0.0
/*98  */     spapr->next_irq = 16;                                                        // 0.0
/*99  */     /* Set up VIO bus */                                                         // 0.0
/*100 */     spapr->vio_bus = spapr_vio_bus_init();                                       // 0.0
/*101 */     for (i = 0; i < MAX_SERIAL_PORTS; i++) {                                     // 0.0
/*102 */         if (serial_hds[i]) {                                                     // 0.0
/*103 */             spapr_vty_create(spapr->vio_bus, serial_hds[i]);                     // 0.0
/*104 */         }                                                                        // 0.0
/*105 */     }                                                                            // 0.0
/*106 */     /* Set up PCI */                                                             // 0.0
/*107 */     spapr_create_phb(spapr, "pci", SPAPR_PCI_BUID,                               // 0.0
/*108 */                      SPAPR_PCI_MEM_WIN_ADDR,                                     // 0.0
/*109 */                      SPAPR_PCI_MEM_WIN_SIZE,                                     // 0.0
/*110 */                      SPAPR_PCI_IO_WIN_ADDR);                                     // 0.0
/*111 */     for (i = 0; i < nb_nics; i++) {                                              // 0.0
/*112 */         NICInfo *nd = &nd_table[i];                                              // 0.0
/*113 */         if (!nd->model) {                                                        // 0.0
/*114 */             nd->model = g_strdup("ibmveth");                                     // 0.0
/*115 */         }                                                                        // 0.0
/*116 */         if (strcmp(nd->model, "ibmveth") == 0) {                                 // 0.0
/*117 */             spapr_vlan_create(spapr->vio_bus, nd);                               // 0.0
/*118 */         } else {                                                                 // 0.0
/*119 */             pci_nic_init_nofail(&nd_table[i], nd->model, NULL);                  // 0.0
/*120 */         }                                                                        // 0.0
/*121 */     }                                                                            // 0.0
/*122 */     for (i = 0; i <= drive_get_max_bus(IF_SCSI); i++) {                          // 0.0
/*123 */         spapr_vscsi_create(spapr->vio_bus);                                      // 0.0
/*124 */     }                                                                            // 0.0
/*125 */     if (rma_size < (MIN_RMA_SLOF << 20)) {                                       // 0.0
/*126 */         fprintf(stderr, "qemu: pSeries SLOF firmware requires >= "               // 0.0
/*127 */                 "%ldM guest RMA (Real Mode Area memory)\n", MIN_RMA_SLOF);       // 0.0
/*128 */         exit(1);                                                                 // 0.0
/*129 */     }                                                                            // 0.0
/*130 */     fprintf(stderr, "sPAPR memory map:\n");                                      // 0.0
/*131 */     fprintf(stderr, "RTAS                 : 0x%08lx..%08lx\n",                   // 0.0
/*132 */             (unsigned long)spapr->rtas_addr,                                     // 0.0
/*133 */             (unsigned long)(spapr->rtas_addr + spapr->rtas_size - 1));           // 0.0
/*134 */     fprintf(stderr, "FDT                  : 0x%08lx..%08lx\n",                   // 0.0
/*135 */             (unsigned long)spapr->fdt_addr,                                      // 0.0
/*136 */             (unsigned long)(spapr->fdt_addr + FDT_MAX_SIZE - 1));                // 0.0
/*137 */     if (kernel_filename) {                                                       // 0.0
/*138 */         uint64_t lowaddr = 0;                                                    // 0.0
/*139 */         kernel_size = load_elf(kernel_filename, translate_kernel_address, NULL,  // 0.0
/*140 */                                NULL, &lowaddr, NULL, 1, ELF_MACHINE, 0);         // 0.0
/*141 */         if (kernel_size < 0) {                                                   // 0.0
/*142 */             kernel_size = load_image_targphys(kernel_filename,                   // 0.0
/*143 */                                               KERNEL_LOAD_ADDR,                  // 0.0
/*144 */                                               load_limit - KERNEL_LOAD_ADDR);    // 0.0
/*145 */         }                                                                        // 0.0
/*146 */         if (kernel_size < 0) {                                                   // 0.0
/*147 */             fprintf(stderr, "qemu: could not load kernel '%s'\n",                // 0.0
/*148 */                     kernel_filename);                                            // 0.0
/*149 */             exit(1);                                                             // 0.0
/*150 */         }                                                                        // 0.0
/*151 */         fprintf(stderr, "Kernel               : 0x%08x..%08lx\n",                // 0.0
/*152 */                 KERNEL_LOAD_ADDR, KERNEL_LOAD_ADDR + kernel_size - 1);           // 0.0
/*153 */         /* load initrd */                                                        // 0.0
/*154 */         if (initrd_filename) {                                                   // 0.0
/*155 */             /* Try to locate the initrd in the gap between the kernel            // 0.0
/*156 */              * and the firmware. Add a bit of space just in case                 // 0.0
/*157 */              */                                                                  // 0.0
/*158 */             initrd_base = (KERNEL_LOAD_ADDR + kernel_size + 0x1ffff) & ~0xffff;  // 0.0
/*159 */             initrd_size = load_image_targphys(initrd_filename, initrd_base,      // 0.0
/*160 */                                               load_limit - initrd_base);         // 0.0
/*161 */             if (initrd_size < 0) {                                               // 0.0
/*162 */                 fprintf(stderr, "qemu: could not load initial ram disk '%s'\n",  // 0.0
/*163 */                         initrd_filename);                                        // 0.0
/*164 */                 exit(1);                                                         // 0.0
/*165 */             }                                                                    // 0.0
/*166 */             fprintf(stderr, "Ramdisk              : 0x%08lx..%08lx\n",           // 0.0
/*167 */                     (long)initrd_base, (long)(initrd_base + initrd_size - 1));   // 0.0
/*168 */         } else {                                                                 // 0.0
/*169 */             initrd_base = 0;                                                     // 0.0
/*170 */             initrd_size = 0;                                                     // 0.0
/*171 */         }                                                                        // 0.0
/*172 */     }                                                                            // 0.0
/*173 */     filename = qemu_find_file(QEMU_FILE_TYPE_BIOS, FW_FILE_NAME);                // 0.0
/*174 */     fw_size = load_image_targphys(filename, 0, FW_MAX_SIZE);                     // 0.0
/*175 */     if (fw_size < 0) {                                                           // 0.0
/*176 */         hw_error("qemu: could not load LPAR rtas '%s'\n", filename);             // 0.0
/*177 */         exit(1);                                                                 // 0.0
/*178 */     }                                                                            // 0.0
/*179 */     g_free(filename);                                                            // 0.0
/*180 */     fprintf(stderr, "Firmware load        : 0x%08x..%08lx\n",                    // 0.0
/*181 */             0, fw_size);                                                         // 0.0
/*182 */     fprintf(stderr, "Firmware runtime     : 0x%08lx..%08lx\n",                   // 0.0
/*183 */             load_limit, (unsigned long)spapr->fdt_addr);                         // 0.0
/*184 */     spapr->entry_point = 0x100;                                                  // 0.0
/*185 */     /* SLOF will startup the secondary CPUs using RTAS */                        // 0.0
/*186 */     for (env = first_cpu; env != NULL; env = env->next_cpu) {                    // 0.0
/*187 */         env->halted = 1;                                                         // 0.0
/*188 */     }                                                                            // 0.0
/*189 */     /* Prepare the device tree */                                                // 0.0
/*190 */     spapr->fdt_skel = spapr_create_fdt_skel(cpu_model, rma_size,                 // 0.0
/*191 */                                             initrd_base, initrd_size,            // 0.0
/*192 */                                             kernel_size,                         // 0.0
/*193 */                                             boot_device, kernel_cmdline,         // 0.0
/*194 */                                             pteg_shift + 7);                     // 0.0
/*195 */     assert(spapr->fdt_skel != NULL);                                             // 0.0
/*196 */     qemu_register_reset(spapr_reset, spapr);                                     // 0.0
/*197 */ }                                                                                // 0.0
