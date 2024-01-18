// commit message qemu@8dfe8e7f4f (target=0, prob=0.59641147, correct=False): pseries: Add helper to calculate recommended hash page table size
/*0   */ static void ppc_spapr_init(MachineState *machine)                                        // (12) 0.03125
/*2   */ {                                                                                        // (31) 0.001953
/*4   */     sPAPRMachineState *spapr = SPAPR_MACHINE(machine);                                   // (2) 0.04687
/*6   */     sPAPRMachineClass *smc = SPAPR_MACHINE_GET_CLASS(machine);                           // (0) 0.05273
/*8   */     const char *kernel_filename = machine->kernel_filename;                              // (14) 0.03125
/*10  */     const char *kernel_cmdline = machine->kernel_cmdline;                                // (8) 0.03516
/*12  */     const char *initrd_filename = machine->initrd_filename;                              // (9) 0.03516
/*14  */     PowerPCCPU *cpu;                                                                     // (23) 0.01953
/*16  */     PCIHostState *phb;                                                                   // (24) 0.01953
/*18  */     int i;                                                                               // (29) 0.01172
/*20  */     MemoryRegion *sysmem = get_system_memory();                                          // (16) 0.0293
/*22  */     MemoryRegion *ram = g_new(MemoryRegion, 1);                                          // (11) 0.0332
/*24  */     MemoryRegion *rma_region;                                                            // (22) 0.02148
/*26  */     void *rma = NULL;                                                                    // (27) 0.01953
/*28  */     hwaddr rma_alloc_size;                                                               // (19) 0.02539
/*30  */     hwaddr node0_size = spapr_node0_size();                                              // (6) 0.03906
/*32  */     uint32_t initrd_base = 0;                                                            // (17) 0.02734
/*34  */     long kernel_size = 0, initrd_size = 0;                                               // (10) 0.0332
/*36  */     long load_limit, fw_size;                                                            // (18) 0.02539
/*38  */     bool kernel_le = false;                                                              // (26) 0.01953
/*40  */     char *filename;                                                                      // (28) 0.01367
/*44  */     msi_supported = true;                                                                // (25) 0.01953
/*48  */     QLIST_INIT(&spapr->phbs);                                                            // (13) 0.03125
/*52  */     cpu_ppc_hypercall = emulate_spapr_hypercall;                                         // (5) 0.03906
/*56  */     /* Allocate RMA if necessary */                                                      // (20) 0.02148
/*58  */     rma_alloc_size = kvmppc_alloc_rma(&rma);                                             // (3) 0.04492
/*62  */     if (rma_alloc_size == -1) {                                                          // (15) 0.03125
/*64  */         error_report("Unable to create RMA");                                            // (7) 0.03516
/*66  */         exit(1);                                                                         // (21) 0.02148
/*68  */     }                                                                                    // (30) 0.007812
/*72  */     if (rma_alloc_size && (rma_alloc_size < node0_size)) {                               // (1) 0.05078
/*74  */         spapr->rma_size = rma_alloc_size;                                                // (4) 0.04492
/*76  */     } else {                                                                             // 0.0
/*78  */         spapr->rma_size = node0_size;                                                    // 0.0
/*82  */         /* With KVM, we don't actually know whether KVM supports an                      // 0.0
/*84  */          * unbounded RMA (PR KVM) or is limited by the hash table size                   // 0.0
/*86  */          * (HV KVM using VRMA), so we always assume the latter                           // 0.0
/*88  */          *                                                                               // 0.0
/*90  */          * In that case, we also limit the initial allocations for RTAS                  // 0.0
/*92  */          * etc... to 256M since we have no way to know what the VRMA size                // 0.0
/*94  */          * is going to be as it depends on the size of the hash table                    // 0.0
/*96  */          * isn't determined yet.                                                         // 0.0
/*98  */          */                                                                              // 0.0
/*100 */         if (kvm_enabled()) {                                                             // 0.0
/*102 */             spapr->vrma_adjust = 1;                                                      // 0.0
/*104 */             spapr->rma_size = MIN(spapr->rma_size, 0x10000000);                          // 0.0
/*106 */         }                                                                                // 0.0
/*108 */     }                                                                                    // 0.0
/*112 */     if (spapr->rma_size > node0_size) {                                                  // 0.0
/*114 */         error_report("Numa node 0 has to span the RMA (%#08"HWADDR_PRIx")",              // 0.0
/*116 */                      spapr->rma_size);                                                   // 0.0
/*118 */         exit(1);                                                                         // 0.0
/*120 */     }                                                                                    // 0.0
/*124 */     /* Setup a load limit for the ramdisk leaving room for SLOF and FDT */               // 0.0
/*126 */     load_limit = MIN(spapr->rma_size, RTAS_MAX_ADDR) - FW_OVERHEAD;                      // 0.0
/*130 */     /* We aim for a hash table of size 1/128 the size of RAM.  The                       // 0.0
/*132 */      * normal rule of thumb is 1/64 the size of RAM, but that's much                     // 0.0
/*134 */      * more than needed for the Linux guests we support. */                              // 0.0
/*136 */     spapr->htab_shift = 18; /* Minimum architected size */                               // 0.0
/*138 */     while (spapr->htab_shift <= 46) {                                                    // 0.0
/*140 */         if ((1ULL << (spapr->htab_shift + 7)) >= machine->maxram_size) {                 // 0.0
/*142 */             break;                                                                       // 0.0
/*144 */         }                                                                                // 0.0
/*146 */         spapr->htab_shift++;                                                             // 0.0
/*148 */     }                                                                                    // 0.0
/*150 */     spapr_alloc_htab(spapr);                                                             // 0.0
/*154 */     /* Set up Interrupt Controller before we create the VCPUs */                         // 0.0
/*156 */     spapr->icp = xics_system_init(machine,                                               // 0.0
/*158 */                                   DIV_ROUND_UP(max_cpus * kvmppc_smt_threads(),          // 0.0
/*160 */                                                smp_threads),                             // 0.0
/*162 */                                   XICS_IRQS, &error_fatal);                              // 0.0
/*166 */     if (smc->dr_lmb_enabled) {                                                           // 0.0
/*168 */         spapr_validate_node_memory(machine, &error_fatal);                               // 0.0
/*170 */     }                                                                                    // 0.0
/*174 */     /* init CPUs */                                                                      // 0.0
/*176 */     if (machine->cpu_model == NULL) {                                                    // 0.0
/*178 */         machine->cpu_model = kvm_enabled() ? "host" : "POWER7";                          // 0.0
/*180 */     }                                                                                    // 0.0
/*182 */     for (i = 0; i < smp_cpus; i++) {                                                     // 0.0
/*184 */         cpu = cpu_ppc_init(machine->cpu_model);                                          // 0.0
/*186 */         if (cpu == NULL) {                                                               // 0.0
/*188 */             error_report("Unable to find PowerPC CPU definition");                       // 0.0
/*190 */             exit(1);                                                                     // 0.0
/*192 */         }                                                                                // 0.0
/*194 */         spapr_cpu_init(spapr, cpu, &error_fatal);                                        // 0.0
/*196 */     }                                                                                    // 0.0
/*200 */     if (kvm_enabled()) {                                                                 // 0.0
/*202 */         /* Enable H_LOGICAL_CI_* so SLOF can talk to in-kernel devices */                // 0.0
/*204 */         kvmppc_enable_logical_ci_hcalls();                                               // 0.0
/*206 */         kvmppc_enable_set_mode_hcall();                                                  // 0.0
/*208 */     }                                                                                    // 0.0
/*212 */     /* allocate RAM */                                                                   // 0.0
/*214 */     memory_region_allocate_system_memory(ram, NULL, "ppc_spapr.ram",                     // 0.0
/*216 */                                          machine->ram_size);                             // 0.0
/*218 */     memory_region_add_subregion(sysmem, 0, ram);                                         // 0.0
/*222 */     if (rma_alloc_size && rma) {                                                         // 0.0
/*224 */         rma_region = g_new(MemoryRegion, 1);                                             // 0.0
/*226 */         memory_region_init_ram_ptr(rma_region, NULL, "ppc_spapr.rma",                    // 0.0
/*228 */                                    rma_alloc_size, rma);                                 // 0.0
/*230 */         vmstate_register_ram_global(rma_region);                                         // 0.0
/*232 */         memory_region_add_subregion(sysmem, 0, rma_region);                              // 0.0
/*234 */     }                                                                                    // 0.0
/*238 */     /* initialize hotplug memory address space */                                        // 0.0
/*240 */     if (machine->ram_size < machine->maxram_size) {                                      // 0.0
/*242 */         ram_addr_t hotplug_mem_size = machine->maxram_size - machine->ram_size;          // 0.0
/*246 */         if (machine->ram_slots > SPAPR_MAX_RAM_SLOTS) {                                  // 0.0
/*248 */             error_report("Specified number of memory slots %"                            // 0.0
/*250 */                          PRIu64" exceeds max supported %d",                              // 0.0
/*252 */                          machine->ram_slots, SPAPR_MAX_RAM_SLOTS);                       // 0.0
/*254 */             exit(1);                                                                     // 0.0
/*256 */         }                                                                                // 0.0
/*260 */         spapr->hotplug_memory.base = ROUND_UP(machine->ram_size,                         // 0.0
/*262 */                                               SPAPR_HOTPLUG_MEM_ALIGN);                  // 0.0
/*264 */         memory_region_init(&spapr->hotplug_memory.mr, OBJECT(spapr),                     // 0.0
/*266 */                            "hotplug-memory", hotplug_mem_size);                          // 0.0
/*268 */         memory_region_add_subregion(sysmem, spapr->hotplug_memory.base,                  // 0.0
/*270 */                                     &spapr->hotplug_memory.mr);                          // 0.0
/*272 */     }                                                                                    // 0.0
/*276 */     if (smc->dr_lmb_enabled) {                                                           // 0.0
/*278 */         spapr_create_lmb_dr_connectors(spapr);                                           // 0.0
/*280 */     }                                                                                    // 0.0
/*284 */     filename = qemu_find_file(QEMU_FILE_TYPE_BIOS, "spapr-rtas.bin");                    // 0.0
/*286 */     if (!filename) {                                                                     // 0.0
/*288 */         error_report("Could not find LPAR rtas '%s'", "spapr-rtas.bin");                 // 0.0
/*290 */         exit(1);                                                                         // 0.0
/*292 */     }                                                                                    // 0.0
/*294 */     spapr->rtas_size = get_image_size(filename);                                         // 0.0
/*296 */     spapr->rtas_blob = g_malloc(spapr->rtas_size);                                       // 0.0
/*298 */     if (load_image_size(filename, spapr->rtas_blob, spapr->rtas_size) < 0) {             // 0.0
/*300 */         error_report("Could not load LPAR rtas '%s'", filename);                         // 0.0
/*302 */         exit(1);                                                                         // 0.0
/*304 */     }                                                                                    // 0.0
/*306 */     if (spapr->rtas_size > RTAS_MAX_SIZE) {                                              // 0.0
/*308 */         error_report("RTAS too big ! 0x%zx bytes (max is 0x%x)",                         // 0.0
/*310 */                      (size_t)spapr->rtas_size, RTAS_MAX_SIZE);                           // 0.0
/*312 */         exit(1);                                                                         // 0.0
/*314 */     }                                                                                    // 0.0
/*316 */     g_free(filename);                                                                    // 0.0
/*320 */     /* Set up EPOW events infrastructure */                                              // 0.0
/*322 */     spapr_events_init(spapr);                                                            // 0.0
/*326 */     /* Set up the RTC RTAS interfaces */                                                 // 0.0
/*328 */     spapr_rtc_create(spapr);                                                             // 0.0
/*332 */     /* Set up VIO bus */                                                                 // 0.0
/*334 */     spapr->vio_bus = spapr_vio_bus_init();                                               // 0.0
/*338 */     for (i = 0; i < MAX_SERIAL_PORTS; i++) {                                             // 0.0
/*340 */         if (serial_hds[i]) {                                                             // 0.0
/*342 */             spapr_vty_create(spapr->vio_bus, serial_hds[i]);                             // 0.0
/*344 */         }                                                                                // 0.0
/*346 */     }                                                                                    // 0.0
/*350 */     /* We always have at least the nvram device on VIO */                                // 0.0
/*352 */     spapr_create_nvram(spapr);                                                           // 0.0
/*356 */     /* Set up PCI */                                                                     // 0.0
/*358 */     spapr_pci_rtas_init();                                                               // 0.0
/*362 */     phb = spapr_create_phb(spapr, 0);                                                    // 0.0
/*366 */     for (i = 0; i < nb_nics; i++) {                                                      // 0.0
/*368 */         NICInfo *nd = &nd_table[i];                                                      // 0.0
/*372 */         if (!nd->model) {                                                                // 0.0
/*374 */             nd->model = g_strdup("ibmveth");                                             // 0.0
/*376 */         }                                                                                // 0.0
/*380 */         if (strcmp(nd->model, "ibmveth") == 0) {                                         // 0.0
/*382 */             spapr_vlan_create(spapr->vio_bus, nd);                                       // 0.0
/*384 */         } else {                                                                         // 0.0
/*386 */             pci_nic_init_nofail(&nd_table[i], phb->bus, nd->model, NULL);                // 0.0
/*388 */         }                                                                                // 0.0
/*390 */     }                                                                                    // 0.0
/*394 */     for (i = 0; i <= drive_get_max_bus(IF_SCSI); i++) {                                  // 0.0
/*396 */         spapr_vscsi_create(spapr->vio_bus);                                              // 0.0
/*398 */     }                                                                                    // 0.0
/*402 */     /* Graphics */                                                                       // 0.0
/*404 */     if (spapr_vga_init(phb->bus, &error_fatal)) {                                        // 0.0
/*406 */         spapr->has_graphics = true;                                                      // 0.0
/*408 */         machine->usb |= defaults_enabled() && !machine->usb_disabled;                    // 0.0
/*410 */     }                                                                                    // 0.0
/*414 */     if (machine->usb) {                                                                  // 0.0
/*416 */         if (smc->use_ohci_by_default) {                                                  // 0.0
/*418 */             pci_create_simple(phb->bus, -1, "pci-ohci");                                 // 0.0
/*420 */         } else {                                                                         // 0.0
/*422 */             pci_create_simple(phb->bus, -1, "nec-usb-xhci");                             // 0.0
/*424 */         }                                                                                // 0.0
/*428 */         if (spapr->has_graphics) {                                                       // 0.0
/*430 */             USBBus *usb_bus = usb_bus_find(-1);                                          // 0.0
/*434 */             usb_create_simple(usb_bus, "usb-kbd");                                       // 0.0
/*436 */             usb_create_simple(usb_bus, "usb-mouse");                                     // 0.0
/*438 */         }                                                                                // 0.0
/*440 */     }                                                                                    // 0.0
/*444 */     if (spapr->rma_size < (MIN_RMA_SLOF << 20)) {                                        // 0.0
/*446 */         error_report(                                                                    // 0.0
/*448 */             "pSeries SLOF firmware requires >= %ldM guest RMA (Real Mode Area memory)",  // 0.0
/*450 */             MIN_RMA_SLOF);                                                               // 0.0
/*452 */         exit(1);                                                                         // 0.0
/*454 */     }                                                                                    // 0.0
/*458 */     if (kernel_filename) {                                                               // 0.0
/*460 */         uint64_t lowaddr = 0;                                                            // 0.0
/*464 */         kernel_size = load_elf(kernel_filename, translate_kernel_address, NULL,          // 0.0
/*466 */                                NULL, &lowaddr, NULL, 1, PPC_ELF_MACHINE, 0);             // 0.0
/*468 */         if (kernel_size == ELF_LOAD_WRONG_ENDIAN) {                                      // 0.0
/*470 */             kernel_size = load_elf(kernel_filename,                                      // 0.0
/*472 */                                    translate_kernel_address, NULL,                       // 0.0
/*474 */                                    NULL, &lowaddr, NULL, 0, PPC_ELF_MACHINE, 0);         // 0.0
/*476 */             kernel_le = kernel_size > 0;                                                 // 0.0
/*478 */         }                                                                                // 0.0
/*480 */         if (kernel_size < 0) {                                                           // 0.0
/*482 */             error_report("error loading %s: %s",                                         // 0.0
/*484 */                          kernel_filename, load_elf_strerror(kernel_size));               // 0.0
/*486 */             exit(1);                                                                     // 0.0
/*488 */         }                                                                                // 0.0
/*492 */         /* load initrd */                                                                // 0.0
/*494 */         if (initrd_filename) {                                                           // 0.0
/*496 */             /* Try to locate the initrd in the gap between the kernel                    // 0.0
/*498 */              * and the firmware. Add a bit of space just in case                         // 0.0
/*500 */              */                                                                          // 0.0
/*502 */             initrd_base = (KERNEL_LOAD_ADDR + kernel_size + 0x1ffff) & ~0xffff;          // 0.0
/*504 */             initrd_size = load_image_targphys(initrd_filename, initrd_base,              // 0.0
/*506 */                                               load_limit - initrd_base);                 // 0.0
/*508 */             if (initrd_size < 0) {                                                       // 0.0
/*510 */                 error_report("could not load initial ram disk '%s'",                     // 0.0
/*512 */                              initrd_filename);                                           // 0.0
/*514 */                 exit(1);                                                                 // 0.0
/*516 */             }                                                                            // 0.0
/*518 */         } else {                                                                         // 0.0
/*520 */             initrd_base = 0;                                                             // 0.0
/*522 */             initrd_size = 0;                                                             // 0.0
/*524 */         }                                                                                // 0.0
/*526 */     }                                                                                    // 0.0
/*530 */     if (bios_name == NULL) {                                                             // 0.0
/*532 */         bios_name = FW_FILE_NAME;                                                        // 0.0
/*534 */     }                                                                                    // 0.0
/*536 */     filename = qemu_find_file(QEMU_FILE_TYPE_BIOS, bios_name);                           // 0.0
/*538 */     if (!filename) {                                                                     // 0.0
/*540 */         error_report("Could not find LPAR firmware '%s'", bios_name);                    // 0.0
/*542 */         exit(1);                                                                         // 0.0
/*544 */     }                                                                                    // 0.0
/*546 */     fw_size = load_image_targphys(filename, 0, FW_MAX_SIZE);                             // 0.0
/*548 */     if (fw_size <= 0) {                                                                  // 0.0
/*550 */         error_report("Could not load LPAR firmware '%s'", filename);                     // 0.0
/*552 */         exit(1);                                                                         // 0.0
/*554 */     }                                                                                    // 0.0
/*556 */     g_free(filename);                                                                    // 0.0
/*560 */     /* FIXME: Should register things through the MachineState's qdev                     // 0.0
/*562 */      * interface, this is a legacy from the sPAPREnvironment structure                   // 0.0
/*564 */      * which predated MachineState but had a similar function */                         // 0.0
/*566 */     vmstate_register(NULL, 0, &vmstate_spapr, spapr);                                    // 0.0
/*568 */     register_savevm_live(NULL, "spapr/htab", -1, 1,                                      // 0.0
/*570 */                          &savevm_htab_handlers, spapr);                                  // 0.0
/*574 */     /* Prepare the device tree */                                                        // 0.0
/*576 */     spapr->fdt_skel = spapr_create_fdt_skel(initrd_base, initrd_size,                    // 0.0
/*578 */                                             kernel_size, kernel_le,                      // 0.0
/*580 */                                             kernel_cmdline,                              // 0.0
/*582 */                                             spapr->check_exception_irq);                 // 0.0
/*584 */     assert(spapr->fdt_skel != NULL);                                                     // 0.0
/*588 */     /* used by RTAS */                                                                   // 0.0
/*590 */     QTAILQ_INIT(&spapr->ccs_list);                                                       // 0.0
/*592 */     qemu_register_reset(spapr_ccs_reset_hook, spapr);                                    // 0.0
/*596 */     qemu_register_boot_set(spapr_boot_set, spapr);                                       // 0.0
/*598 */ }                                                                                        // 0.0
