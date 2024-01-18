// commit message qemu@24408a7d2b (target=0, prob=0.4502084, correct=True): spapr: move cpu_setup after kvmppc_set_papr
/*0   */ static void ppc_spapr_init(QEMUMachineInitArgs *args)                             // (3) 0.03907
/*2   */ {                                                                                 // (30) 0.001957
/*4   */     ram_addr_t ram_size = args->ram_size;                                         // (7) 0.03515
/*6   */     const char *cpu_model = args->cpu_model;                                      // (14) 0.03125
/*8   */     const char *kernel_filename = args->kernel_filename;                          // (15) 0.03125
/*10  */     const char *kernel_cmdline = args->kernel_cmdline;                            // (9) 0.03515
/*12  */     const char *initrd_filename = args->initrd_filename;                          // (8) 0.03515
/*14  */     const char *boot_device = args->boot_order;                                   // (12) 0.03129
/*16  */     PowerPCCPU *cpu;                                                              // (22) 0.01954
/*18  */     CPUPPCState *env;                                                             // (25) 0.01953
/*20  */     PCIHostState *phb;                                                            // (23) 0.01953
/*22  */     int i;                                                                        // (28) 0.01172
/*24  */     MemoryRegion *sysmem = get_system_memory();                                   // (17) 0.02929
/*26  */     MemoryRegion *ram = g_new(MemoryRegion, 1);                                   // (11) 0.0332
/*28  */     hwaddr rma_alloc_size;                                                        // (19) 0.02539
/*30  */     uint32_t initrd_base = 0;                                                     // (18) 0.02735
/*32  */     long kernel_size = 0, initrd_size = 0;                                        // (10) 0.0332
/*34  */     long load_limit, rtas_limit, fw_size;                                         // (6) 0.03712
/*36  */     bool kernel_le = false;                                                       // (24) 0.01953
/*38  */     char *filename;                                                               // (27) 0.01367
/*42  */     msi_supported = true;                                                         // (26) 0.01953
/*46  */     spapr = g_malloc0(sizeof(*spapr));                                            // (5) 0.03906
/*48  */     QLIST_INIT(&spapr->phbs);                                                     // (13) 0.03125
/*52  */     cpu_ppc_hypercall = emulate_spapr_hypercall;                                  // (4) 0.03906
/*56  */     /* Allocate RMA if necessary */                                               // (20) 0.02148
/*58  */     rma_alloc_size = kvmppc_alloc_rma("ppc_spapr.rma", sysmem);                   // (0) 0.0664
/*62  */     if (rma_alloc_size == -1) {                                                   // (16) 0.03125
/*64  */         hw_error("qemu: Unable to create RMA\n");                                 // (2) 0.04687
/*66  */         exit(1);                                                                  // (21) 0.02148
/*68  */     }                                                                             // (29) 0.007811
/*72  */     if (rma_alloc_size && (rma_alloc_size < ram_size)) {                          // (1) 0.04882
/*74  */         spapr->rma_size = rma_alloc_size;                                         // 0.0
/*76  */     } else {                                                                      // 0.0
/*78  */         spapr->rma_size = ram_size;                                               // 0.0
/*82  */         /* With KVM, we don't actually know whether KVM supports an               // 0.0
/*84  */          * unbounded RMA (PR KVM) or is limited by the hash table size            // 0.0
/*86  */          * (HV KVM using VRMA), so we always assume the latter                    // 0.0
/*88  */          *                                                                        // 0.0
/*90  */          * In that case, we also limit the initial allocations for RTAS           // 0.0
/*92  */          * etc... to 256M since we have no way to know what the VRMA size         // 0.0
/*94  */          * is going to be as it depends on the size of the hash table             // 0.0
/*96  */          * isn't determined yet.                                                  // 0.0
/*98  */          */                                                                       // 0.0
/*100 */         if (kvm_enabled()) {                                                      // 0.0
/*102 */             spapr->vrma_adjust = 1;                                               // 0.0
/*104 */             spapr->rma_size = MIN(spapr->rma_size, 0x10000000);                   // 0.0
/*106 */         }                                                                         // 0.0
/*108 */     }                                                                             // 0.0
/*112 */     /* We place the device tree and RTAS just below either the top of the RMA,    // 0.0
/*114 */      * or just below 2GB, whichever is lowere, so that it can be                  // 0.0
/*116 */      * processed with 32-bit real mode code if necessary */                       // 0.0
/*118 */     rtas_limit = MIN(spapr->rma_size, 0x80000000);                                // 0.0
/*120 */     spapr->rtas_addr = rtas_limit - RTAS_MAX_SIZE;                                // 0.0
/*122 */     spapr->fdt_addr = spapr->rtas_addr - FDT_MAX_SIZE;                            // 0.0
/*124 */     load_limit = spapr->fdt_addr - FW_OVERHEAD;                                   // 0.0
/*128 */     /* We aim for a hash table of size 1/128 the size of RAM.  The                // 0.0
/*130 */      * normal rule of thumb is 1/64 the size of RAM, but that's much              // 0.0
/*132 */      * more than needed for the Linux guests we support. */                       // 0.0
/*134 */     spapr->htab_shift = 18; /* Minimum architected size */                        // 0.0
/*136 */     while (spapr->htab_shift <= 46) {                                             // 0.0
/*138 */         if ((1ULL << (spapr->htab_shift + 7)) >= ram_size) {                      // 0.0
/*140 */             break;                                                                // 0.0
/*142 */         }                                                                         // 0.0
/*144 */         spapr->htab_shift++;                                                      // 0.0
/*146 */     }                                                                             // 0.0
/*150 */     /* Set up Interrupt Controller before we create the VCPUs */                  // 0.0
/*152 */     spapr->icp = xics_system_init(smp_cpus * kvmppc_smt_threads() / smp_threads,  // 0.0
/*154 */                                   XICS_IRQS);                                     // 0.0
/*156 */     spapr->next_irq = XICS_IRQ_BASE;                                              // 0.0
/*160 */     /* init CPUs */                                                               // 0.0
/*162 */     if (cpu_model == NULL) {                                                      // 0.0
/*164 */         cpu_model = kvm_enabled() ? "host" : "POWER7";                            // 0.0
/*166 */     }                                                                             // 0.0
/*168 */     for (i = 0; i < smp_cpus; i++) {                                              // 0.0
/*170 */         cpu = cpu_ppc_init(cpu_model);                                            // 0.0
/*172 */         if (cpu == NULL) {                                                        // 0.0
/*174 */             fprintf(stderr, "Unable to find PowerPC CPU definition\n");           // 0.0
/*176 */             exit(1);                                                              // 0.0
/*178 */         }                                                                         // 0.0
/*180 */         env = &cpu->env;                                                          // 0.0
/*184 */         xics_cpu_setup(spapr->icp, cpu);                                          // 0.0
/*188 */         /* Set time-base frequency to 512 MHz */                                  // 0.0
/*190 */         cpu_ppc_tb_init(env, TIMEBASE_FREQ);                                      // 0.0
/*194 */         /* PAPR always has exception vectors in RAM not ROM. To ensure this,      // 0.0
/*196 */          * MSR[IP] should never be set.                                           // 0.0
/*198 */          */                                                                       // 0.0
/*200 */         env->msr_mask &= ~(1 << 6);                                               // 0.0
/*204 */         /* Tell KVM that we're in PAPR mode */                                    // 0.0
/*206 */         if (kvm_enabled()) {                                                      // 0.0
/*208 */             kvmppc_set_papr(cpu);                                                 // 0.0
/*210 */         }                                                                         // 0.0
/*214 */         qemu_register_reset(spapr_cpu_reset, cpu);                                // 0.0
/*216 */     }                                                                             // 0.0
/*220 */     /* allocate RAM */                                                            // 0.0
/*222 */     spapr->ram_limit = ram_size;                                                  // 0.0
/*224 */     if (spapr->ram_limit > rma_alloc_size) {                                      // 0.0
/*226 */         ram_addr_t nonrma_base = rma_alloc_size;                                  // 0.0
/*228 */         ram_addr_t nonrma_size = spapr->ram_limit - rma_alloc_size;               // 0.0
/*232 */         memory_region_init_ram(ram, NULL, "ppc_spapr.ram", nonrma_size);          // 0.0
/*234 */         vmstate_register_ram_global(ram);                                         // 0.0
/*236 */         memory_region_add_subregion(sysmem, nonrma_base, ram);                    // 0.0
/*238 */     }                                                                             // 0.0
/*242 */     filename = qemu_find_file(QEMU_FILE_TYPE_BIOS, "spapr-rtas.bin");             // 0.0
/*244 */     spapr->rtas_size = load_image_targphys(filename, spapr->rtas_addr,            // 0.0
/*246 */                                            rtas_limit - spapr->rtas_addr);        // 0.0
/*248 */     if (spapr->rtas_size < 0) {                                                   // 0.0
/*250 */         hw_error("qemu: could not load LPAR rtas '%s'\n", filename);              // 0.0
/*252 */         exit(1);                                                                  // 0.0
/*254 */     }                                                                             // 0.0
/*256 */     if (spapr->rtas_size > RTAS_MAX_SIZE) {                                       // 0.0
/*258 */         hw_error("RTAS too big ! 0x%lx bytes (max is 0x%x)\n",                    // 0.0
/*260 */                  spapr->rtas_size, RTAS_MAX_SIZE);                                // 0.0
/*262 */         exit(1);                                                                  // 0.0
/*264 */     }                                                                             // 0.0
/*266 */     g_free(filename);                                                             // 0.0
/*270 */     /* Set up EPOW events infrastructure */                                       // 0.0
/*272 */     spapr_events_init(spapr);                                                     // 0.0
/*276 */     /* Set up VIO bus */                                                          // 0.0
/*278 */     spapr->vio_bus = spapr_vio_bus_init();                                        // 0.0
/*282 */     for (i = 0; i < MAX_SERIAL_PORTS; i++) {                                      // 0.0
/*284 */         if (serial_hds[i]) {                                                      // 0.0
/*286 */             spapr_vty_create(spapr->vio_bus, serial_hds[i]);                      // 0.0
/*288 */         }                                                                         // 0.0
/*290 */     }                                                                             // 0.0
/*294 */     /* We always have at least the nvram device on VIO */                         // 0.0
/*296 */     spapr_create_nvram(spapr);                                                    // 0.0
/*300 */     /* Set up PCI */                                                              // 0.0
/*302 */     spapr_pci_msi_init(spapr, SPAPR_PCI_MSI_WINDOW);                              // 0.0
/*304 */     spapr_pci_rtas_init();                                                        // 0.0
/*308 */     phb = spapr_create_phb(spapr, 0);                                             // 0.0
/*312 */     for (i = 0; i < nb_nics; i++) {                                               // 0.0
/*314 */         NICInfo *nd = &nd_table[i];                                               // 0.0
/*318 */         if (!nd->model) {                                                         // 0.0
/*320 */             nd->model = g_strdup("ibmveth");                                      // 0.0
/*322 */         }                                                                         // 0.0
/*326 */         if (strcmp(nd->model, "ibmveth") == 0) {                                  // 0.0
/*328 */             spapr_vlan_create(spapr->vio_bus, nd);                                // 0.0
/*330 */         } else {                                                                  // 0.0
/*332 */             pci_nic_init_nofail(&nd_table[i], phb->bus, nd->model, NULL);         // 0.0
/*334 */         }                                                                         // 0.0
/*336 */     }                                                                             // 0.0
/*340 */     for (i = 0; i <= drive_get_max_bus(IF_SCSI); i++) {                           // 0.0
/*342 */         spapr_vscsi_create(spapr->vio_bus);                                       // 0.0
/*344 */     }                                                                             // 0.0
/*348 */     /* Graphics */                                                                // 0.0
/*350 */     if (spapr_vga_init(phb->bus)) {                                               // 0.0
/*352 */         spapr->has_graphics = true;                                               // 0.0
/*354 */     }                                                                             // 0.0
/*358 */     if (usb_enabled(spapr->has_graphics)) {                                       // 0.0
/*360 */         pci_create_simple(phb->bus, -1, "pci-ohci");                              // 0.0
/*362 */         if (spapr->has_graphics) {                                                // 0.0
/*364 */             usbdevice_create("keyboard");                                         // 0.0
/*366 */             usbdevice_create("mouse");                                            // 0.0
/*368 */         }                                                                         // 0.0
/*370 */     }                                                                             // 0.0
/*374 */     if (spapr->rma_size < (MIN_RMA_SLOF << 20)) {                                 // 0.0
/*376 */         fprintf(stderr, "qemu: pSeries SLOF firmware requires >= "                // 0.0
/*378 */                 "%ldM guest RMA (Real Mode Area memory)\n", MIN_RMA_SLOF);        // 0.0
/*380 */         exit(1);                                                                  // 0.0
/*382 */     }                                                                             // 0.0
/*386 */     if (kernel_filename) {                                                        // 0.0
/*388 */         uint64_t lowaddr = 0;                                                     // 0.0
/*392 */         kernel_size = load_elf(kernel_filename, translate_kernel_address, NULL,   // 0.0
/*394 */                                NULL, &lowaddr, NULL, 1, ELF_MACHINE, 0);          // 0.0
/*396 */         if (kernel_size < 0) {                                                    // 0.0
/*398 */             kernel_size = load_elf(kernel_filename,                               // 0.0
/*400 */                                    translate_kernel_address, NULL,                // 0.0
/*402 */                                    NULL, &lowaddr, NULL, 0, ELF_MACHINE, 0);      // 0.0
/*404 */             kernel_le = kernel_size > 0;                                          // 0.0
/*406 */         }                                                                         // 0.0
/*408 */         if (kernel_size < 0) {                                                    // 0.0
/*410 */             kernel_size = load_image_targphys(kernel_filename,                    // 0.0
/*412 */                                               KERNEL_LOAD_ADDR,                   // 0.0
/*414 */                                               load_limit - KERNEL_LOAD_ADDR);     // 0.0
/*416 */         }                                                                         // 0.0
/*418 */         if (kernel_size < 0) {                                                    // 0.0
/*420 */             fprintf(stderr, "qemu: could not load kernel '%s'\n",                 // 0.0
/*422 */                     kernel_filename);                                             // 0.0
/*424 */             exit(1);                                                              // 0.0
/*426 */         }                                                                         // 0.0
/*430 */         /* load initrd */                                                         // 0.0
/*432 */         if (initrd_filename) {                                                    // 0.0
/*434 */             /* Try to locate the initrd in the gap between the kernel             // 0.0
/*436 */              * and the firmware. Add a bit of space just in case                  // 0.0
/*438 */              */                                                                   // 0.0
/*440 */             initrd_base = (KERNEL_LOAD_ADDR + kernel_size + 0x1ffff) & ~0xffff;   // 0.0
/*442 */             initrd_size = load_image_targphys(initrd_filename, initrd_base,       // 0.0
/*444 */                                               load_limit - initrd_base);          // 0.0
/*446 */             if (initrd_size < 0) {                                                // 0.0
/*448 */                 fprintf(stderr, "qemu: could not load initial ram disk '%s'\n",   // 0.0
/*450 */                         initrd_filename);                                         // 0.0
/*452 */                 exit(1);                                                          // 0.0
/*454 */             }                                                                     // 0.0
/*456 */         } else {                                                                  // 0.0
/*458 */             initrd_base = 0;                                                      // 0.0
/*460 */             initrd_size = 0;                                                      // 0.0
/*462 */         }                                                                         // 0.0
/*464 */     }                                                                             // 0.0
/*468 */     if (bios_name == NULL) {                                                      // 0.0
/*470 */         bios_name = FW_FILE_NAME;                                                 // 0.0
/*472 */     }                                                                             // 0.0
/*474 */     filename = qemu_find_file(QEMU_FILE_TYPE_BIOS, bios_name);                    // 0.0
/*476 */     fw_size = load_image_targphys(filename, 0, FW_MAX_SIZE);                      // 0.0
/*478 */     if (fw_size < 0) {                                                            // 0.0
/*480 */         hw_error("qemu: could not load LPAR rtas '%s'\n", filename);              // 0.0
/*482 */         exit(1);                                                                  // 0.0
/*484 */     }                                                                             // 0.0
/*486 */     g_free(filename);                                                             // 0.0
/*490 */     spapr->entry_point = 0x100;                                                   // 0.0
/*494 */     vmstate_register(NULL, 0, &vmstate_spapr, spapr);                             // 0.0
/*496 */     register_savevm_live(NULL, "spapr/htab", -1, 1,                               // 0.0
/*498 */                          &savevm_htab_handlers, spapr);                           // 0.0
/*502 */     /* Prepare the device tree */                                                 // 0.0
/*504 */     spapr->fdt_skel = spapr_create_fdt_skel(cpu_model,                            // 0.0
/*506 */                                             initrd_base, initrd_size,             // 0.0
/*508 */                                             kernel_size, kernel_le,               // 0.0
/*510 */                                             boot_device, kernel_cmdline,          // 0.0
/*512 */                                             spapr->epow_irq);                     // 0.0
/*514 */     assert(spapr->fdt_skel != NULL);                                              // 0.0
/*516 */ }                                                                                 // 0.0
