// commit message qemu@e40c3d2e7f (target=0, prob=0.29386985, correct=True): hw/arm/virt: fix limit of 64-bit ACPI/ECAM PCI MMIO range
/*0   */ static void acpi_dsdt_add_pci(Aml *scope, const MemMapEntry *memmap,             // (8) 0.0508
/*2   */                               uint32_t irq, bool use_highmem)                    // (0) 0.082
/*4   */ {                                                                                // (17) 0.001966
/*6   */     Aml *method, *crs, *ifctx, *UUID, *ifctx1, *elsectx, *buf;                   // (1) 0.06469
/*8   */     int i, bus_no;                                                               // (16) 0.01957
/*10  */     hwaddr base_mmio = memmap[VIRT_PCIE_MMIO].base;                              // (9) 0.05076
/*12  */     hwaddr size_mmio = memmap[VIRT_PCIE_MMIO].size;                              // (10) 0.05076
/*14  */     hwaddr base_pio = memmap[VIRT_PCIE_PIO].base;                                // (13) 0.04881
/*16  */     hwaddr size_pio = memmap[VIRT_PCIE_PIO].size;                                // (11) 0.04881
/*18  */     hwaddr base_ecam = memmap[VIRT_PCIE_ECAM].base;                              // (12) 0.04881
/*20  */     hwaddr size_ecam = memmap[VIRT_PCIE_ECAM].size;                              // (14) 0.0488
/*22  */     int nr_pcie_buses = size_ecam / PCIE_MMCFG_SIZE_MIN;                         // (4) 0.05666
/*26  */     Aml *dev = aml_device("%s", "PCI0");                                         // (15) 0.04102
/*28  */     aml_append(dev, aml_name_decl("_HID", aml_string("PNP0A08")));               // (2) 0.06443
/*30  */     aml_append(dev, aml_name_decl("_CID", aml_string("PNP0A03")));               // (3) 0.06442
/*32  */     aml_append(dev, aml_name_decl("_SEG", aml_int(0)));                          // (5) 0.05661
/*34  */     aml_append(dev, aml_name_decl("_BBN", aml_int(0)));                          // (7) 0.05661
/*36  */     aml_append(dev, aml_name_decl("_ADR", aml_int(0)));                          // (6) 0.05661
/*38  */     aml_append(dev, aml_name_decl("_UID", aml_string("PCI0")));                  // 0.0
/*40  */     aml_append(dev, aml_name_decl("_STR", aml_unicode("PCIe 0 Device")));        // 0.0
/*42  */     aml_append(dev, aml_name_decl("_CCA", aml_int(1)));                          // 0.0
/*46  */     /* Declare the PCI Routing Table. */                                         // 0.0
/*48  */     Aml *rt_pkg = aml_package(nr_pcie_buses * PCI_NUM_PINS);                     // 0.0
/*50  */     for (bus_no = 0; bus_no < nr_pcie_buses; bus_no++) {                         // 0.0
/*52  */         for (i = 0; i < PCI_NUM_PINS; i++) {                                     // 0.0
/*54  */             int gsi = (i + bus_no) % PCI_NUM_PINS;                               // 0.0
/*56  */             Aml *pkg = aml_package(4);                                           // 0.0
/*58  */             aml_append(pkg, aml_int((bus_no << 16) | 0xFFFF));                   // 0.0
/*60  */             aml_append(pkg, aml_int(i));                                         // 0.0
/*62  */             aml_append(pkg, aml_name("GSI%d", gsi));                             // 0.0
/*64  */             aml_append(pkg, aml_int(0));                                         // 0.0
/*66  */             aml_append(rt_pkg, pkg);                                             // 0.0
/*68  */         }                                                                        // 0.0
/*70  */     }                                                                            // 0.0
/*72  */     aml_append(dev, aml_name_decl("_PRT", rt_pkg));                              // 0.0
/*76  */     /* Create GSI link device */                                                 // 0.0
/*78  */     for (i = 0; i < PCI_NUM_PINS; i++) {                                         // 0.0
/*80  */         uint32_t irqs =  irq + i;                                                // 0.0
/*82  */         Aml *dev_gsi = aml_device("GSI%d", i);                                   // 0.0
/*84  */         aml_append(dev_gsi, aml_name_decl("_HID", aml_string("PNP0C0F")));       // 0.0
/*86  */         aml_append(dev_gsi, aml_name_decl("_UID", aml_int(0)));                  // 0.0
/*88  */         crs = aml_resource_template();                                           // 0.0
/*90  */         aml_append(crs,                                                          // 0.0
/*92  */                    aml_interrupt(AML_CONSUMER, AML_LEVEL, AML_ACTIVE_HIGH,       // 0.0
/*94  */                                  AML_EXCLUSIVE, &irqs, 1));                      // 0.0
/*96  */         aml_append(dev_gsi, aml_name_decl("_PRS", crs));                         // 0.0
/*98  */         crs = aml_resource_template();                                           // 0.0
/*100 */         aml_append(crs,                                                          // 0.0
/*102 */                    aml_interrupt(AML_CONSUMER, AML_LEVEL, AML_ACTIVE_HIGH,       // 0.0
/*104 */                                  AML_EXCLUSIVE, &irqs, 1));                      // 0.0
/*106 */         aml_append(dev_gsi, aml_name_decl("_CRS", crs));                         // 0.0
/*108 */         method = aml_method("_SRS", 1, AML_NOTSERIALIZED);                       // 0.0
/*110 */         aml_append(dev_gsi, method);                                             // 0.0
/*112 */         aml_append(dev, dev_gsi);                                                // 0.0
/*114 */     }                                                                            // 0.0
/*118 */     method = aml_method("_CBA", 0, AML_NOTSERIALIZED);                           // 0.0
/*120 */     aml_append(method, aml_return(aml_int(base_ecam)));                          // 0.0
/*122 */     aml_append(dev, method);                                                     // 0.0
/*126 */     method = aml_method("_CRS", 0, AML_NOTSERIALIZED);                           // 0.0
/*128 */     Aml *rbuf = aml_resource_template();                                         // 0.0
/*130 */     aml_append(rbuf,                                                             // 0.0
/*132 */         aml_word_bus_number(AML_MIN_FIXED, AML_MAX_FIXED, AML_POS_DECODE,        // 0.0
/*134 */                             0x0000, 0x0000, nr_pcie_buses - 1, 0x0000,           // 0.0
/*136 */                             nr_pcie_buses));                                     // 0.0
/*138 */     aml_append(rbuf,                                                             // 0.0
/*140 */         aml_dword_memory(AML_POS_DECODE, AML_MIN_FIXED, AML_MAX_FIXED,           // 0.0
/*142 */                          AML_NON_CACHEABLE, AML_READ_WRITE, 0x0000, base_mmio,   // 0.0
/*144 */                          base_mmio + size_mmio - 1, 0x0000, size_mmio));         // 0.0
/*146 */     aml_append(rbuf,                                                             // 0.0
/*148 */         aml_dword_io(AML_MIN_FIXED, AML_MAX_FIXED, AML_POS_DECODE,               // 0.0
/*150 */                      AML_ENTIRE_RANGE, 0x0000, 0x0000, size_pio - 1, base_pio,   // 0.0
/*152 */                      size_pio));                                                 // 0.0
/*156 */     if (use_highmem) {                                                           // 0.0
/*158 */         hwaddr base_mmio_high = memmap[VIRT_PCIE_MMIO_HIGH].base;                // 0.0
/*160 */         hwaddr size_mmio_high = memmap[VIRT_PCIE_MMIO_HIGH].size;                // 0.0
/*164 */         aml_append(rbuf,                                                         // 0.0
/*166 */             aml_qword_memory(AML_POS_DECODE, AML_MIN_FIXED, AML_MAX_FIXED,       // 0.0
/*168 */                              AML_NON_CACHEABLE, AML_READ_WRITE, 0x0000,          // 0.0
/*170 */                              base_mmio_high, base_mmio_high, 0x0000,             // 0.0
/*172 */                              size_mmio_high));                                   // 0.0
/*174 */     }                                                                            // 0.0
/*178 */     aml_append(method, aml_name_decl("RBUF", rbuf));                             // 0.0
/*180 */     aml_append(method, aml_return(rbuf));                                        // 0.0
/*182 */     aml_append(dev, method);                                                     // 0.0
/*186 */     /* Declare an _OSC (OS Control Handoff) method */                            // 0.0
/*188 */     aml_append(dev, aml_name_decl("SUPP", aml_int(0)));                          // 0.0
/*190 */     aml_append(dev, aml_name_decl("CTRL", aml_int(0)));                          // 0.0
/*192 */     method = aml_method("_OSC", 4, AML_NOTSERIALIZED);                           // 0.0
/*194 */     aml_append(method,                                                           // 0.0
/*196 */         aml_create_dword_field(aml_arg(3), aml_int(0), "CDW1"));                 // 0.0
/*200 */     /* PCI Firmware Specification 3.0                                            // 0.0
/*202 */      * 4.5.1. _OSC Interface for PCI Host Bridge Devices                         // 0.0
/*204 */      * The _OSC interface for a PCI/PCI-X/PCI Express hierarchy is               // 0.0
/*206 */      * identified by the Universal Unique IDentifier (UUID)                      // 0.0
/*208 */      * 33DB4D5B-1FF7-401C-9657-7441C03DD766                                      // 0.0
/*210 */      */                                                                          // 0.0
/*212 */     UUID = aml_touuid("33DB4D5B-1FF7-401C-9657-7441C03DD766");                   // 0.0
/*214 */     ifctx = aml_if(aml_equal(aml_arg(0), UUID));                                 // 0.0
/*216 */     aml_append(ifctx,                                                            // 0.0
/*218 */         aml_create_dword_field(aml_arg(3), aml_int(4), "CDW2"));                 // 0.0
/*220 */     aml_append(ifctx,                                                            // 0.0
/*222 */         aml_create_dword_field(aml_arg(3), aml_int(8), "CDW3"));                 // 0.0
/*224 */     aml_append(ifctx, aml_store(aml_name("CDW2"), aml_name("SUPP")));            // 0.0
/*226 */     aml_append(ifctx, aml_store(aml_name("CDW3"), aml_name("CTRL")));            // 0.0
/*228 */     aml_append(ifctx, aml_store(aml_and(aml_name("CTRL"), aml_int(0x1D), NULL),  // 0.0
/*230 */                                 aml_name("CTRL")));                              // 0.0
/*234 */     ifctx1 = aml_if(aml_lnot(aml_equal(aml_arg(1), aml_int(0x1))));              // 0.0
/*236 */     aml_append(ifctx1, aml_store(aml_or(aml_name("CDW1"), aml_int(0x08), NULL),  // 0.0
/*238 */                                  aml_name("CDW1")));                             // 0.0
/*240 */     aml_append(ifctx, ifctx1);                                                   // 0.0
/*244 */     ifctx1 = aml_if(aml_lnot(aml_equal(aml_name("CDW3"), aml_name("CTRL"))));    // 0.0
/*246 */     aml_append(ifctx1, aml_store(aml_or(aml_name("CDW1"), aml_int(0x10), NULL),  // 0.0
/*248 */                                  aml_name("CDW1")));                             // 0.0
/*250 */     aml_append(ifctx, ifctx1);                                                   // 0.0
/*254 */     aml_append(ifctx, aml_store(aml_name("CTRL"), aml_name("CDW3")));            // 0.0
/*256 */     aml_append(ifctx, aml_return(aml_arg(3)));                                   // 0.0
/*258 */     aml_append(method, ifctx);                                                   // 0.0
/*262 */     elsectx = aml_else();                                                        // 0.0
/*264 */     aml_append(elsectx, aml_store(aml_or(aml_name("CDW1"), aml_int(4), NULL),    // 0.0
/*266 */                                   aml_name("CDW1")));                            // 0.0
/*268 */     aml_append(elsectx, aml_return(aml_arg(3)));                                 // 0.0
/*270 */     aml_append(method, elsectx);                                                 // 0.0
/*272 */     aml_append(dev, method);                                                     // 0.0
/*276 */     method = aml_method("_DSM", 4, AML_NOTSERIALIZED);                           // 0.0
/*280 */     /* PCI Firmware Specification 3.0                                            // 0.0
/*282 */      * 4.6.1. _DSM for PCI Express Slot Information                              // 0.0
/*284 */      * The UUID in _DSM in this context is                                       // 0.0
/*286 */      * {E5C937D0-3553-4D7A-9117-EA4D19C3434D}                                    // 0.0
/*288 */      */                                                                          // 0.0
/*290 */     UUID = aml_touuid("E5C937D0-3553-4D7A-9117-EA4D19C3434D");                   // 0.0
/*292 */     ifctx = aml_if(aml_equal(aml_arg(0), UUID));                                 // 0.0
/*294 */     ifctx1 = aml_if(aml_equal(aml_arg(2), aml_int(0)));                          // 0.0
/*296 */     uint8_t byte_list[1] = {1};                                                  // 0.0
/*298 */     buf = aml_buffer(1, byte_list);                                              // 0.0
/*300 */     aml_append(ifctx1, aml_return(buf));                                         // 0.0
/*302 */     aml_append(ifctx, ifctx1);                                                   // 0.0
/*304 */     aml_append(method, ifctx);                                                   // 0.0
/*308 */     byte_list[0] = 0;                                                            // 0.0
/*310 */     buf = aml_buffer(1, byte_list);                                              // 0.0
/*312 */     aml_append(method, aml_return(buf));                                         // 0.0
/*314 */     aml_append(dev, method);                                                     // 0.0
/*318 */     Aml *dev_rp0 = aml_device("%s", "RP0");                                      // 0.0
/*320 */     aml_append(dev_rp0, aml_name_decl("_ADR", aml_int(0)));                      // 0.0
/*322 */     aml_append(dev, dev_rp0);                                                    // 0.0
/*324 */     aml_append(scope, dev);                                                      // 0.0
/*326 */ }                                                                                // 0.0
