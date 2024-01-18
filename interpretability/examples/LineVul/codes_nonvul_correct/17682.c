// commit message qemu@0e9b9edae7 (target=0, prob=0.21677257, correct=True): acpi: convert linker from GArray to BIOSLinker structure
/*0   */ build_dsdt(GArray *table_data, GArray *linker,                                      // (11) 0.03519
/*2   */            AcpiPmInfo *pm, AcpiMiscInfo *misc,                                      // (6) 0.05078
/*4   */            PcPciInfo *pci, MachineState *machine)                                   // (7) 0.04688
/*6   */ {                                                                                   // (23) 0.001953
/*8   */     CrsRangeEntry *entry;                                                           // (20) 0.01953
/*10  */     Aml *dsdt, *sb_scope, *scope, *dev, *method, *field, *pkg, *crs;                // (1) 0.06445
/*12  */     GPtrArray *mem_ranges = g_ptr_array_new_with_free_func(crs_range_free);         // (3) 0.06445
/*14  */     GPtrArray *io_ranges = g_ptr_array_new_with_free_func(crs_range_free);          // (2) 0.06445
/*16  */     PCMachineState *pcms = PC_MACHINE(machine);                                     // (12) 0.03516
/*18  */     uint32_t nr_mem = machine->ram_slots;                                           // (10) 0.03711
/*20  */     int root_bus_limit = 0xFF;                                                      // (15) 0.02734
/*22  */     PCIBus *bus = NULL;                                                             // (19) 0.02148
/*24  */     int i;                                                                          // (22) 0.01172
/*28  */     dsdt = init_aml_allocator();                                                    // (16) 0.02734
/*32  */     /* Reserve space for header */                                                  // (21) 0.01758
/*34  */     acpi_data_push(dsdt->buf, sizeof(AcpiTableHeader));                             // (8) 0.04297
/*38  */     build_dbg_aml(dsdt);                                                            // (18) 0.02539
/*40  */     if (misc->is_piix4) {                                                           // (17) 0.02734
/*42  */         sb_scope = aml_scope("_SB");                                                // (9) 0.03906
/*44  */         dev = aml_device("PCI0");                                                   // (13) 0.03516
/*46  */         aml_append(dev, aml_name_decl("_HID", aml_eisaid("PNP0A03")));              // (0) 0.07617
/*48  */         aml_append(dev, aml_name_decl("_ADR", aml_int(0)));                         // (4) 0.06445
/*50  */         aml_append(dev, aml_name_decl("_UID", aml_int(1)));                         // (5) 0.0625
/*52  */         aml_append(sb_scope, dev);                                                  // (14) 0.03515
/*54  */         aml_append(dsdt, sb_scope);                                                 // 0.0
/*58  */         build_hpet_aml(dsdt);                                                       // 0.0
/*60  */         build_piix4_pm(dsdt);                                                       // 0.0
/*62  */         build_piix4_isa_bridge(dsdt);                                               // 0.0
/*64  */         build_isa_devices_aml(dsdt);                                                // 0.0
/*66  */         build_piix4_pci_hotplug(dsdt);                                              // 0.0
/*68  */         build_piix4_pci0_int(dsdt);                                                 // 0.0
/*70  */     } else {                                                                        // 0.0
/*72  */         sb_scope = aml_scope("_SB");                                                // 0.0
/*74  */         aml_append(sb_scope,                                                        // 0.0
/*76  */             aml_operation_region("PCST", AML_SYSTEM_IO, aml_int(0xae00), 0x0c));    // 0.0
/*78  */         aml_append(sb_scope,                                                        // 0.0
/*80  */             aml_operation_region("PCSB", AML_SYSTEM_IO, aml_int(0xae0c), 0x01));    // 0.0
/*82  */         field = aml_field("PCSB", AML_ANY_ACC, AML_NOLOCK, AML_WRITE_AS_ZEROS);     // 0.0
/*84  */         aml_append(field, aml_named_field("PCIB", 8));                              // 0.0
/*86  */         aml_append(sb_scope, field);                                                // 0.0
/*88  */         aml_append(dsdt, sb_scope);                                                 // 0.0
/*92  */         sb_scope = aml_scope("_SB");                                                // 0.0
/*94  */         dev = aml_device("PCI0");                                                   // 0.0
/*96  */         aml_append(dev, aml_name_decl("_HID", aml_eisaid("PNP0A08")));              // 0.0
/*98  */         aml_append(dev, aml_name_decl("_CID", aml_eisaid("PNP0A03")));              // 0.0
/*100 */         aml_append(dev, aml_name_decl("_ADR", aml_int(0)));                         // 0.0
/*102 */         aml_append(dev, aml_name_decl("_UID", aml_int(1)));                         // 0.0
/*104 */         aml_append(dev, aml_name_decl("SUPP", aml_int(0)));                         // 0.0
/*106 */         aml_append(dev, aml_name_decl("CTRL", aml_int(0)));                         // 0.0
/*108 */         aml_append(dev, build_q35_osc_method());                                    // 0.0
/*110 */         aml_append(sb_scope, dev);                                                  // 0.0
/*112 */         aml_append(dsdt, sb_scope);                                                 // 0.0
/*116 */         build_hpet_aml(dsdt);                                                       // 0.0
/*118 */         build_q35_isa_bridge(dsdt);                                                 // 0.0
/*120 */         build_isa_devices_aml(dsdt);                                                // 0.0
/*122 */         build_q35_pci0_int(dsdt);                                                   // 0.0
/*124 */     }                                                                               // 0.0
/*128 */     build_legacy_cpu_hotplug_aml(dsdt, machine, pm->cpu_hp_io_base);                // 0.0
/*130 */     build_memory_hotplug_aml(dsdt, nr_mem, pm->mem_hp_io_base,                      // 0.0
/*132 */                              pm->mem_hp_io_len);                                    // 0.0
/*136 */     scope =  aml_scope("_GPE");                                                     // 0.0
/*138 */     {                                                                               // 0.0
/*140 */         aml_append(scope, aml_name_decl("_HID", aml_string("ACPI0006")));           // 0.0
/*144 */         if (misc->is_piix4) {                                                       // 0.0
/*146 */             method = aml_method("_E01", 0, AML_NOTSERIALIZED);                      // 0.0
/*148 */             aml_append(method,                                                      // 0.0
/*150 */                 aml_acquire(aml_name("\\_SB.PCI0.BLCK"), 0xFFFF));                  // 0.0
/*152 */             aml_append(method, aml_call0("\\_SB.PCI0.PCNT"));                       // 0.0
/*154 */             aml_append(method, aml_release(aml_name("\\_SB.PCI0.BLCK")));           // 0.0
/*156 */             aml_append(scope, method);                                              // 0.0
/*158 */         }                                                                           // 0.0
/*162 */         method = aml_method("_E03", 0, AML_NOTSERIALIZED);                          // 0.0
/*164 */         aml_append(method, aml_call0(MEMORY_HOTPLUG_HANDLER_PATH));                 // 0.0
/*166 */         aml_append(scope, method);                                                  // 0.0
/*168 */     }                                                                               // 0.0
/*170 */     aml_append(dsdt, scope);                                                        // 0.0
/*174 */     bus = PC_MACHINE(machine)->bus;                                                 // 0.0
/*176 */     if (bus) {                                                                      // 0.0
/*178 */         QLIST_FOREACH(bus, &bus->child, sibling) {                                  // 0.0
/*180 */             uint8_t bus_num = pci_bus_num(bus);                                     // 0.0
/*182 */             uint8_t numa_node = pci_bus_numa_node(bus);                             // 0.0
/*186 */             /* look only for expander root buses */                                 // 0.0
/*188 */             if (!pci_bus_is_root(bus)) {                                            // 0.0
/*190 */                 continue;                                                           // 0.0
/*192 */             }                                                                       // 0.0
/*196 */             if (bus_num < root_bus_limit) {                                         // 0.0
/*198 */                 root_bus_limit = bus_num - 1;                                       // 0.0
/*200 */             }                                                                       // 0.0
/*204 */             scope = aml_scope("\\_SB");                                             // 0.0
/*206 */             dev = aml_device("PC%.02X", bus_num);                                   // 0.0
/*208 */             aml_append(dev, aml_name_decl("_UID", aml_int(bus_num)));               // 0.0
/*210 */             aml_append(dev, aml_name_decl("_HID", aml_eisaid("PNP0A03")));          // 0.0
/*212 */             aml_append(dev, aml_name_decl("_BBN", aml_int(bus_num)));               // 0.0
/*216 */             if (numa_node != NUMA_NODE_UNASSIGNED) {                                // 0.0
/*218 */                 aml_append(dev, aml_name_decl("_PXM", aml_int(numa_node)));         // 0.0
/*220 */             }                                                                       // 0.0
/*224 */             aml_append(dev, build_prt(false));                                      // 0.0
/*226 */             crs = build_crs(PCI_HOST_BRIDGE(BUS(bus)->parent),                      // 0.0
/*228 */                             io_ranges, mem_ranges);                                 // 0.0
/*230 */             aml_append(dev, aml_name_decl("_CRS", crs));                            // 0.0
/*232 */             aml_append(scope, dev);                                                 // 0.0
/*234 */             aml_append(dsdt, scope);                                                // 0.0
/*236 */         }                                                                           // 0.0
/*238 */     }                                                                               // 0.0
/*242 */     scope = aml_scope("\\_SB.PCI0");                                                // 0.0
/*244 */     /* build PCI0._CRS */                                                           // 0.0
/*246 */     crs = aml_resource_template();                                                  // 0.0
/*248 */     aml_append(crs,                                                                 // 0.0
/*250 */         aml_word_bus_number(AML_MIN_FIXED, AML_MAX_FIXED, AML_POS_DECODE,           // 0.0
/*252 */                             0x0000, 0x0, root_bus_limit,                            // 0.0
/*254 */                             0x0000, root_bus_limit + 1));                           // 0.0
/*256 */     aml_append(crs, aml_io(AML_DECODE16, 0x0CF8, 0x0CF8, 0x01, 0x08));              // 0.0
/*260 */     aml_append(crs,                                                                 // 0.0
/*262 */         aml_word_io(AML_MIN_FIXED, AML_MAX_FIXED,                                   // 0.0
/*264 */                     AML_POS_DECODE, AML_ENTIRE_RANGE,                               // 0.0
/*266 */                     0x0000, 0x0000, 0x0CF7, 0x0000, 0x0CF8));                       // 0.0
/*270 */     crs_replace_with_free_ranges(io_ranges, 0x0D00, 0xFFFF);                        // 0.0
/*272 */     for (i = 0; i < io_ranges->len; i++) {                                          // 0.0
/*274 */         entry = g_ptr_array_index(io_ranges, i);                                    // 0.0
/*276 */         aml_append(crs,                                                             // 0.0
/*278 */             aml_word_io(AML_MIN_FIXED, AML_MAX_FIXED,                               // 0.0
/*280 */                         AML_POS_DECODE, AML_ENTIRE_RANGE,                           // 0.0
/*282 */                         0x0000, entry->base, entry->limit,                          // 0.0
/*284 */                         0x0000, entry->limit - entry->base + 1));                   // 0.0
/*286 */     }                                                                               // 0.0
/*290 */     aml_append(crs,                                                                 // 0.0
/*292 */         aml_dword_memory(AML_POS_DECODE, AML_MIN_FIXED, AML_MAX_FIXED,              // 0.0
/*294 */                          AML_CACHEABLE, AML_READ_WRITE,                             // 0.0
/*296 */                          0, 0x000A0000, 0x000BFFFF, 0, 0x00020000));                // 0.0
/*300 */     crs_replace_with_free_ranges(mem_ranges, pci->w32.begin, pci->w32.end - 1);     // 0.0
/*302 */     for (i = 0; i < mem_ranges->len; i++) {                                         // 0.0
/*304 */         entry = g_ptr_array_index(mem_ranges, i);                                   // 0.0
/*306 */         aml_append(crs,                                                             // 0.0
/*308 */             aml_dword_memory(AML_POS_DECODE, AML_MIN_FIXED, AML_MAX_FIXED,          // 0.0
/*310 */                              AML_NON_CACHEABLE, AML_READ_WRITE,                     // 0.0
/*312 */                              0, entry->base, entry->limit,                          // 0.0
/*314 */                              0, entry->limit - entry->base + 1));                   // 0.0
/*316 */     }                                                                               // 0.0
/*320 */     if (pci->w64.begin) {                                                           // 0.0
/*322 */         aml_append(crs,                                                             // 0.0
/*324 */             aml_qword_memory(AML_POS_DECODE, AML_MIN_FIXED, AML_MAX_FIXED,          // 0.0
/*326 */                              AML_CACHEABLE, AML_READ_WRITE,                         // 0.0
/*328 */                              0, pci->w64.begin, pci->w64.end - 1, 0,                // 0.0
/*330 */                              pci->w64.end - pci->w64.begin));                       // 0.0
/*332 */     }                                                                               // 0.0
/*336 */     if (misc->tpm_version != TPM_VERSION_UNSPEC) {                                  // 0.0
/*338 */         aml_append(crs, aml_memory32_fixed(TPM_TIS_ADDR_BASE,                       // 0.0
/*340 */                    TPM_TIS_ADDR_SIZE, AML_READ_WRITE));                             // 0.0
/*342 */     }                                                                               // 0.0
/*344 */     aml_append(scope, aml_name_decl("_CRS", crs));                                  // 0.0
/*348 */     /* reserve GPE0 block resources */                                              // 0.0
/*350 */     dev = aml_device("GPE0");                                                       // 0.0
/*352 */     aml_append(dev, aml_name_decl("_HID", aml_string("PNP0A06")));                  // 0.0
/*354 */     aml_append(dev, aml_name_decl("_UID", aml_string("GPE0 resources")));           // 0.0
/*356 */     /* device present, functioning, decoding, not shown in UI */                    // 0.0
/*358 */     aml_append(dev, aml_name_decl("_STA", aml_int(0xB)));                           // 0.0
/*360 */     crs = aml_resource_template();                                                  // 0.0
/*362 */     aml_append(crs,                                                                 // 0.0
/*364 */         aml_io(AML_DECODE16, pm->gpe0_blk, pm->gpe0_blk, 1, pm->gpe0_blk_len)       // 0.0
/*366 */     );                                                                              // 0.0
/*368 */     aml_append(dev, aml_name_decl("_CRS", crs));                                    // 0.0
/*370 */     aml_append(scope, dev);                                                         // 0.0
/*374 */     g_ptr_array_free(io_ranges, true);                                              // 0.0
/*376 */     g_ptr_array_free(mem_ranges, true);                                             // 0.0
/*380 */     /* reserve PCIHP resources */                                                   // 0.0
/*382 */     if (pm->pcihp_io_len) {                                                         // 0.0
/*384 */         dev = aml_device("PHPR");                                                   // 0.0
/*386 */         aml_append(dev, aml_name_decl("_HID", aml_string("PNP0A06")));              // 0.0
/*388 */         aml_append(dev,                                                             // 0.0
/*390 */             aml_name_decl("_UID", aml_string("PCI Hotplug resources")));            // 0.0
/*392 */         /* device present, functioning, decoding, not shown in UI */                // 0.0
/*394 */         aml_append(dev, aml_name_decl("_STA", aml_int(0xB)));                       // 0.0
/*396 */         crs = aml_resource_template();                                              // 0.0
/*398 */         aml_append(crs,                                                             // 0.0
/*400 */             aml_io(AML_DECODE16, pm->pcihp_io_base, pm->pcihp_io_base, 1,           // 0.0
/*402 */                    pm->pcihp_io_len)                                                // 0.0
/*404 */         );                                                                          // 0.0
/*406 */         aml_append(dev, aml_name_decl("_CRS", crs));                                // 0.0
/*408 */         aml_append(scope, dev);                                                     // 0.0
/*410 */     }                                                                               // 0.0
/*412 */     aml_append(dsdt, scope);                                                        // 0.0
/*416 */     /*  create S3_ / S4_ / S5_ packages if necessary */                             // 0.0
/*418 */     scope = aml_scope("\\");                                                        // 0.0
/*420 */     if (!pm->s3_disabled) {                                                         // 0.0
/*422 */         pkg = aml_package(4);                                                       // 0.0
/*424 */         aml_append(pkg, aml_int(1)); /* PM1a_CNT.SLP_TYP */                         // 0.0
/*426 */         aml_append(pkg, aml_int(1)); /* PM1b_CNT.SLP_TYP, FIXME: not impl. */       // 0.0
/*428 */         aml_append(pkg, aml_int(0)); /* reserved */                                 // 0.0
/*430 */         aml_append(pkg, aml_int(0)); /* reserved */                                 // 0.0
/*432 */         aml_append(scope, aml_name_decl("_S3", pkg));                               // 0.0
/*434 */     }                                                                               // 0.0
/*438 */     if (!pm->s4_disabled) {                                                         // 0.0
/*440 */         pkg = aml_package(4);                                                       // 0.0
/*442 */         aml_append(pkg, aml_int(pm->s4_val)); /* PM1a_CNT.SLP_TYP */                // 0.0
/*444 */         /* PM1b_CNT.SLP_TYP, FIXME: not impl. */                                    // 0.0
/*446 */         aml_append(pkg, aml_int(pm->s4_val));                                       // 0.0
/*448 */         aml_append(pkg, aml_int(0)); /* reserved */                                 // 0.0
/*450 */         aml_append(pkg, aml_int(0)); /* reserved */                                 // 0.0
/*452 */         aml_append(scope, aml_name_decl("_S4", pkg));                               // 0.0
/*454 */     }                                                                               // 0.0
/*458 */     pkg = aml_package(4);                                                           // 0.0
/*460 */     aml_append(pkg, aml_int(0)); /* PM1a_CNT.SLP_TYP */                             // 0.0
/*462 */     aml_append(pkg, aml_int(0)); /* PM1b_CNT.SLP_TYP not impl. */                   // 0.0
/*464 */     aml_append(pkg, aml_int(0)); /* reserved */                                     // 0.0
/*466 */     aml_append(pkg, aml_int(0)); /* reserved */                                     // 0.0
/*468 */     aml_append(scope, aml_name_decl("_S5", pkg));                                   // 0.0
/*470 */     aml_append(dsdt, scope);                                                        // 0.0
/*474 */     /* create fw_cfg node, unconditionally */                                       // 0.0
/*476 */     {                                                                               // 0.0
/*478 */         /* when using port i/o, the 8-bit data register *always* overlaps           // 0.0
/*480 */          * with half of the 16-bit control register. Hence, the total size          // 0.0
/*482 */          * of the i/o region used is FW_CFG_CTL_SIZE; when using DMA, the           // 0.0
/*484 */          * DMA control register is located at FW_CFG_DMA_IO_BASE + 4 */             // 0.0
/*486 */         uint8_t io_size = object_property_get_bool(OBJECT(pcms->fw_cfg),            // 0.0
/*488 */                                                    "dma_enabled", NULL) ?           // 0.0
/*490 */                           ROUND_UP(FW_CFG_CTL_SIZE, 4) + sizeof(dma_addr_t) :       // 0.0
/*492 */                           FW_CFG_CTL_SIZE;                                          // 0.0
/*496 */         scope = aml_scope("\\_SB.PCI0");                                            // 0.0
/*498 */         dev = aml_device("FWCF");                                                   // 0.0
/*502 */         aml_append(dev, aml_name_decl("_HID", aml_string("QEMU0002")));             // 0.0
/*506 */         /* device present, functioning, decoding, not shown in UI */                // 0.0
/*508 */         aml_append(dev, aml_name_decl("_STA", aml_int(0xB)));                       // 0.0
/*512 */         crs = aml_resource_template();                                              // 0.0
/*514 */         aml_append(crs,                                                             // 0.0
/*516 */             aml_io(AML_DECODE16, FW_CFG_IO_BASE, FW_CFG_IO_BASE, 0x01, io_size)     // 0.0
/*518 */         );                                                                          // 0.0
/*520 */         aml_append(dev, aml_name_decl("_CRS", crs));                                // 0.0
/*524 */         aml_append(scope, dev);                                                     // 0.0
/*526 */         aml_append(dsdt, scope);                                                    // 0.0
/*528 */     }                                                                               // 0.0
/*532 */     if (misc->applesmc_io_base) {                                                   // 0.0
/*534 */         scope = aml_scope("\\_SB.PCI0.ISA");                                        // 0.0
/*536 */         dev = aml_device("SMC");                                                    // 0.0
/*540 */         aml_append(dev, aml_name_decl("_HID", aml_eisaid("APP0001")));              // 0.0
/*542 */         /* device present, functioning, decoding, not shown in UI */                // 0.0
/*544 */         aml_append(dev, aml_name_decl("_STA", aml_int(0xB)));                       // 0.0
/*548 */         crs = aml_resource_template();                                              // 0.0
/*550 */         aml_append(crs,                                                             // 0.0
/*552 */             aml_io(AML_DECODE16, misc->applesmc_io_base, misc->applesmc_io_base,    // 0.0
/*554 */                    0x01, APPLESMC_MAX_DATA_LENGTH)                                  // 0.0
/*556 */         );                                                                          // 0.0
/*558 */         aml_append(crs, aml_irq_no_flags(6));                                       // 0.0
/*560 */         aml_append(dev, aml_name_decl("_CRS", crs));                                // 0.0
/*564 */         aml_append(scope, dev);                                                     // 0.0
/*566 */         aml_append(dsdt, scope);                                                    // 0.0
/*568 */     }                                                                               // 0.0
/*572 */     if (misc->pvpanic_port) {                                                       // 0.0
/*574 */         scope = aml_scope("\\_SB.PCI0.ISA");                                        // 0.0
/*578 */         dev = aml_device("PEVT");                                                   // 0.0
/*580 */         aml_append(dev, aml_name_decl("_HID", aml_string("QEMU0001")));             // 0.0
/*584 */         crs = aml_resource_template();                                              // 0.0
/*586 */         aml_append(crs,                                                             // 0.0
/*588 */             aml_io(AML_DECODE16, misc->pvpanic_port, misc->pvpanic_port, 1, 1)      // 0.0
/*590 */         );                                                                          // 0.0
/*592 */         aml_append(dev, aml_name_decl("_CRS", crs));                                // 0.0
/*596 */         aml_append(dev, aml_operation_region("PEOR", AML_SYSTEM_IO,                 // 0.0
/*598 */                                               aml_int(misc->pvpanic_port), 1));     // 0.0
/*600 */         field = aml_field("PEOR", AML_BYTE_ACC, AML_NOLOCK, AML_PRESERVE);          // 0.0
/*602 */         aml_append(field, aml_named_field("PEPT", 8));                              // 0.0
/*604 */         aml_append(dev, field);                                                     // 0.0
/*608 */         /* device present, functioning, decoding, shown in UI */                    // 0.0
/*610 */         aml_append(dev, aml_name_decl("_STA", aml_int(0xF)));                       // 0.0
/*614 */         method = aml_method("RDPT", 0, AML_NOTSERIALIZED);                          // 0.0
/*616 */         aml_append(method, aml_store(aml_name("PEPT"), aml_local(0)));              // 0.0
/*618 */         aml_append(method, aml_return(aml_local(0)));                               // 0.0
/*620 */         aml_append(dev, method);                                                    // 0.0
/*624 */         method = aml_method("WRPT", 1, AML_NOTSERIALIZED);                          // 0.0
/*626 */         aml_append(method, aml_store(aml_arg(0), aml_name("PEPT")));                // 0.0
/*628 */         aml_append(dev, method);                                                    // 0.0
/*632 */         aml_append(scope, dev);                                                     // 0.0
/*634 */         aml_append(dsdt, scope);                                                    // 0.0
/*636 */     }                                                                               // 0.0
/*640 */     sb_scope = aml_scope("\\_SB");                                                  // 0.0
/*642 */     {                                                                               // 0.0
/*644 */         build_memory_devices(sb_scope, nr_mem, pm->mem_hp_io_base,                  // 0.0
/*646 */                              pm->mem_hp_io_len);                                    // 0.0
/*650 */         {                                                                           // 0.0
/*652 */             Object *pci_host;                                                       // 0.0
/*654 */             PCIBus *bus = NULL;                                                     // 0.0
/*658 */             pci_host = acpi_get_i386_pci_host();                                    // 0.0
/*660 */             if (pci_host) {                                                         // 0.0
/*662 */                 bus = PCI_HOST_BRIDGE(pci_host)->bus;                               // 0.0
/*664 */             }                                                                       // 0.0
/*668 */             if (bus) {                                                              // 0.0
/*670 */                 Aml *scope = aml_scope("PCI0");                                     // 0.0
/*672 */                 /* Scan all PCI buses. Generate tables to support hotplug. */       // 0.0
/*674 */                 build_append_pci_bus_devices(scope, bus, pm->pcihp_bridge_en);      // 0.0
/*678 */                 if (misc->tpm_version != TPM_VERSION_UNSPEC) {                      // 0.0
/*680 */                     dev = aml_device("ISA.TPM");                                    // 0.0
/*682 */                     aml_append(dev, aml_name_decl("_HID", aml_eisaid("PNP0C31")));  // 0.0
/*684 */                     aml_append(dev, aml_name_decl("_STA", aml_int(0xF)));           // 0.0
/*686 */                     crs = aml_resource_template();                                  // 0.0
/*688 */                     aml_append(crs, aml_memory32_fixed(TPM_TIS_ADDR_BASE,           // 0.0
/*690 */                                TPM_TIS_ADDR_SIZE, AML_READ_WRITE));                 // 0.0
/*692 */                     /*                                                              // 0.0
/*694 */                         FIXME: TPM_TIS_IRQ=5 conflicts with PNP0C0F irqs,           // 0.0
/*696 */                         Rewrite to take IRQ from TPM device model and               // 0.0
/*698 */                         fix default IRQ value there to use some unused IRQ          // 0.0
/*700 */                      */                                                             // 0.0
/*702 */                     /* aml_append(crs, aml_irq_no_flags(TPM_TIS_IRQ)); */           // 0.0
/*704 */                     aml_append(dev, aml_name_decl("_CRS", crs));                    // 0.0
/*706 */                     aml_append(scope, dev);                                         // 0.0
/*708 */                 }                                                                   // 0.0
/*712 */                 aml_append(sb_scope, scope);                                        // 0.0
/*714 */             }                                                                       // 0.0
/*716 */         }                                                                           // 0.0
/*718 */         aml_append(dsdt, sb_scope);                                                 // 0.0
/*720 */     }                                                                               // 0.0
/*724 */     /* copy AML table into ACPI tables blob and patch header there */               // 0.0
/*726 */     g_array_append_vals(table_data, dsdt->buf->data, dsdt->buf->len);               // 0.0
/*728 */     build_header(linker, table_data,                                                // 0.0
/*730 */         (void *)(table_data->data + table_data->len - dsdt->buf->len),              // 0.0
/*732 */         "DSDT", dsdt->buf->len, 1, NULL, NULL);                                     // 0.0
/*734 */     free_aml_allocator();                                                           // 0.0
/*736 */ }                                                                                   // 0.0
