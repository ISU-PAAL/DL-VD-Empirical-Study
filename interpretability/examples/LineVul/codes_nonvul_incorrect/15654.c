// commit message qemu@2adba0a18a (target=0, prob=0.7211498, correct=False): pc: acpi: create Processor and Notify objects only for valid lapics
/*0   */ static void build_processor_devices(Aml *sb_scope, unsigned acpi_cpus,            // (9) 0.04297
/*2   */                                     AcpiCpuInfo *cpu, AcpiPmInfo *pm)             // (0) 0.09961
/*4   */ {                                                                                 // (24) 0.001954
/*6   */     int i;                                                                        // (22) 0.01172
/*8   */     Aml *dev;                                                                     // (21) 0.01562
/*10  */     Aml *crs;                                                                     // (17) 0.01758
/*12  */     Aml *pkg;                                                                     // (19) 0.01563
/*14  */     Aml *field;                                                                   // (20) 0.01562
/*16  */     Aml *ifctx;                                                                   // (16) 0.01758
/*18  */     Aml *method;                                                                  // (18) 0.01563
/*22  */     /* The current AML generator can cover the APIC ID range [0..255],            // (10) 0.04102
/*24  */      * inclusive, for VCPU hotplug. */                                            // (12) 0.02734
/*26  */     QEMU_BUILD_BUG_ON(ACPI_CPU_HOTPLUG_ID_LIMIT > 256);                           // (3) 0.0625
/*28  */     g_assert(acpi_cpus <= ACPI_CPU_HOTPLUG_ID_LIMIT);                             // (6) 0.05469
/*32  */     /* create PCI0.PRES device and its _CRS to reserve CPU hotplug MMIO */        // (8) 0.04687
/*34  */     dev = aml_device("PCI0." stringify(CPU_HOTPLUG_RESOURCE_DEVICE));             // (5) 0.05859
/*36  */     aml_append(dev, aml_name_decl("_HID", aml_eisaid("PNP0A06")));                // (2) 0.06836
/*38  */     aml_append(dev,                                                               // (15) 0.01953
/*40  */         aml_name_decl("_UID", aml_string("CPU Hotplug resources"))                // (7) 0.05273
/*42  */     );                                                                            // (23) 0.007812
/*44  */     /* device present, functioning, decoding, not shown in UI */                  // (11) 0.03125
/*46  */     aml_append(dev, aml_name_decl("_STA", aml_int(0xB)));                         // (4) 0.06055
/*48  */     crs = aml_resource_template();                                                // (13) 0.02539
/*50  */     aml_append(crs,                                                               // (14) 0.02148
/*52  */         aml_io(AML_DECODE16, pm->cpu_hp_io_base, pm->cpu_hp_io_base, 1,           // (1) 0.08008
/*54  */                pm->cpu_hp_io_len)                                                 // 0.0
/*56  */     );                                                                            // 0.0
/*58  */     aml_append(dev, aml_name_decl("_CRS", crs));                                  // 0.0
/*60  */     aml_append(sb_scope, dev);                                                    // 0.0
/*62  */     /* declare CPU hotplug MMIO region and PRS field to access it */              // 0.0
/*64  */     aml_append(sb_scope, aml_operation_region(                                    // 0.0
/*66  */         "PRST", AML_SYSTEM_IO, aml_int(pm->cpu_hp_io_base), pm->cpu_hp_io_len));  // 0.0
/*68  */     field = aml_field("PRST", AML_BYTE_ACC, AML_NOLOCK, AML_PRESERVE);            // 0.0
/*70  */     aml_append(field, aml_named_field("PRS", 256));                               // 0.0
/*72  */     aml_append(sb_scope, field);                                                  // 0.0
/*76  */     /* build Processor object for each processor */                               // 0.0
/*78  */     for (i = 0; i < acpi_cpus; i++) {                                             // 0.0
/*80  */         dev = aml_processor(i, 0, 0, "CP%.02X", i);                               // 0.0
/*84  */         method = aml_method("_MAT", 0, AML_NOTSERIALIZED);                        // 0.0
/*86  */         aml_append(method,                                                        // 0.0
/*88  */             aml_return(aml_call1(CPU_MAT_METHOD, aml_int(i))));                   // 0.0
/*90  */         aml_append(dev, method);                                                  // 0.0
/*94  */         method = aml_method("_STA", 0, AML_NOTSERIALIZED);                        // 0.0
/*96  */         aml_append(method,                                                        // 0.0
/*98  */             aml_return(aml_call1(CPU_STATUS_METHOD, aml_int(i))));                // 0.0
/*100 */         aml_append(dev, method);                                                  // 0.0
/*104 */         method = aml_method("_EJ0", 1, AML_NOTSERIALIZED);                        // 0.0
/*106 */         aml_append(method,                                                        // 0.0
/*108 */             aml_return(aml_call2(CPU_EJECT_METHOD, aml_int(i), aml_arg(0)))       // 0.0
/*110 */         );                                                                        // 0.0
/*112 */         aml_append(dev, method);                                                  // 0.0
/*116 */         aml_append(sb_scope, dev);                                                // 0.0
/*118 */     }                                                                             // 0.0
/*122 */     /* build this code:                                                           // 0.0
/*124 */      *   Method(NTFY, 2) {If (LEqual(Arg0, 0x00)) {Notify(CP00, Arg1)} ...}       // 0.0
/*126 */      */                                                                           // 0.0
/*128 */     /* Arg0 = Processor ID = APIC ID */                                           // 0.0
/*130 */     method = aml_method(AML_NOTIFY_METHOD, 2, AML_NOTSERIALIZED);                 // 0.0
/*132 */     for (i = 0; i < acpi_cpus; i++) {                                             // 0.0
/*134 */         ifctx = aml_if(aml_equal(aml_arg(0), aml_int(i)));                        // 0.0
/*136 */         aml_append(ifctx,                                                         // 0.0
/*138 */             aml_notify(aml_name("CP%.02X", i), aml_arg(1))                        // 0.0
/*140 */         );                                                                        // 0.0
/*142 */         aml_append(method, ifctx);                                                // 0.0
/*144 */     }                                                                             // 0.0
/*146 */     aml_append(sb_scope, method);                                                 // 0.0
/*150 */     /* build "Name(CPON, Package() { One, One, ..., Zero, Zero, ... })"           // 0.0
/*152 */      *                                                                            // 0.0
/*154 */      * Note: The ability to create variable-sized packages was first              // 0.0
/*156 */      * introduced in ACPI 2.0. ACPI 1.0 only allowed fixed-size packages          // 0.0
/*158 */      * ith up to 255 elements. Windows guests up to win2k8 fail when              // 0.0
/*160 */      * VarPackageOp is used.                                                      // 0.0
/*162 */      */                                                                           // 0.0
/*164 */     pkg = acpi_cpus <= 255 ? aml_package(acpi_cpus) :                             // 0.0
/*166 */                              aml_varpackage(acpi_cpus);                           // 0.0
/*170 */     for (i = 0; i < acpi_cpus; i++) {                                             // 0.0
/*172 */         uint8_t b = test_bit(i, cpu->found_cpus) ? 0x01 : 0x00;                   // 0.0
/*174 */         aml_append(pkg, aml_int(b));                                              // 0.0
/*176 */     }                                                                             // 0.0
/*178 */     aml_append(sb_scope, aml_name_decl(CPU_ON_BITMAP, pkg));                      // 0.0
/*180 */ }                                                                                 // 0.0
