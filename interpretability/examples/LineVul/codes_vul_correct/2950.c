// commit message qemu@75cc7f0183 (target=1, prob=0.9991899, correct=True): machine: query mem-merge machine property
/*0   */ static void machine_initfn(Object *obj)                                                           // (17) 0.02148
/*2   */ {                                                                                                 // (18) 0.001953
/*4   */     MachineState *ms = MACHINE(obj);                                                              // (15) 0.02734
/*8   */     ms->kernel_irqchip_allowed = true;                                                            // (13) 0.0293
/*10  */     ms->kvm_shadow_mem = -1;                                                                      // (14) 0.0293
/*12  */     ms->dump_guest_core = true;                                                                   // (16) 0.02734
/*17  */     object_property_add_str(obj, "accel",                                                         // (11) 0.0332
/*19  */                             machine_get_accel, machine_set_accel, NULL);                          // (1) 0.08398
/*21  */     object_property_set_description(obj, "accel",                                                 // (12) 0.0332
/*23  */                                     "Accelerator list",                                           // (2) 0.08008
/*25  */                                     NULL);                                                        // (4) 0.07227
/*27  */     object_property_add_bool(obj, "kernel-irqchip",                                               // (9) 0.03906
/*29  */                              NULL,                                                                // (6) 0.05859
/*31  */                              machine_set_kernel_irqchip,                                          // (3) 0.07422
/*33  */                              NULL);                                                               // (7) 0.05859
/*35  */     object_property_set_description(obj, "kernel-irqchip",                                        // (10) 0.03906
/*37  */                                     "Use KVM in-kernel irqchip",                                  // (0) 0.08984
/*39  */                                     NULL);                                                        // (5) 0.07227
/*41  */     object_property_add(obj, "kvm-shadow-mem", "int",                                             // (8) 0.04297
/*43  */                         machine_get_kvm_shadow_mem,                                               // 0.0
/*45  */                         machine_set_kvm_shadow_mem,                                               // 0.0
/*47  */                         NULL, NULL, NULL);                                                        // 0.0
/*49  */     object_property_set_description(obj, "kvm-shadow-mem",                                        // 0.0
/*51  */                                     "KVM shadow MMU size",                                        // 0.0
/*53  */                                     NULL);                                                        // 0.0
/*55  */     object_property_add_str(obj, "kernel",                                                        // 0.0
/*57  */                             machine_get_kernel, machine_set_kernel, NULL);                        // 0.0
/*59  */     object_property_set_description(obj, "kernel",                                                // 0.0
/*61  */                                     "Linux kernel image file",                                    // 0.0
/*63  */                                     NULL);                                                        // 0.0
/*65  */     object_property_add_str(obj, "initrd",                                                        // 0.0
/*67  */                             machine_get_initrd, machine_set_initrd, NULL);                        // 0.0
/*69  */     object_property_set_description(obj, "initrd",                                                // 0.0
/*71  */                                     "Linux initial ramdisk file",                                 // 0.0
/*73  */                                     NULL);                                                        // 0.0
/*75  */     object_property_add_str(obj, "append",                                                        // 0.0
/*77  */                             machine_get_append, machine_set_append, NULL);                        // 0.0
/*79  */     object_property_set_description(obj, "append",                                                // 0.0
/*81  */                                     "Linux kernel command line",                                  // 0.0
/*83  */                                     NULL);                                                        // 0.0
/*85  */     object_property_add_str(obj, "dtb",                                                           // 0.0
/*87  */                             machine_get_dtb, machine_set_dtb, NULL);                              // 0.0
/*89  */     object_property_set_description(obj, "dtb",                                                   // 0.0
/*91  */                                     "Linux kernel device tree file",                              // 0.0
/*93  */                                     NULL);                                                        // 0.0
/*95  */     object_property_add_str(obj, "dumpdtb",                                                       // 0.0
/*97  */                             machine_get_dumpdtb, machine_set_dumpdtb, NULL);                      // 0.0
/*99  */     object_property_set_description(obj, "dumpdtb",                                               // 0.0
/*101 */                                     "Dump current dtb to a file and quit",                        // 0.0
/*103 */                                     NULL);                                                        // 0.0
/*105 */     object_property_add(obj, "phandle-start", "int",                                              // 0.0
/*107 */                         machine_get_phandle_start,                                                // 0.0
/*109 */                         machine_set_phandle_start,                                                // 0.0
/*111 */                         NULL, NULL, NULL);                                                        // 0.0
/*113 */     object_property_set_description(obj, "phandle-start",                                         // 0.0
/*115 */                                     "The first phandle ID we may generate dynamically",           // 0.0
/*117 */                                     NULL);                                                        // 0.0
/*119 */     object_property_add_str(obj, "dt-compatible",                                                 // 0.0
/*121 */                             machine_get_dt_compatible,                                            // 0.0
/*123 */                             machine_set_dt_compatible,                                            // 0.0
/*125 */                             NULL);                                                                // 0.0
/*127 */     object_property_set_description(obj, "dt-compatible",                                         // 0.0
/*129 */                                     "Overrides the \"compatible\" property of the dt root node",  // 0.0
/*131 */                                     NULL);                                                        // 0.0
/*133 */     object_property_add_bool(obj, "dump-guest-core",                                              // 0.0
/*135 */                              machine_get_dump_guest_core,                                         // 0.0
/*137 */                              machine_set_dump_guest_core,                                         // 0.0
/*139 */                              NULL);                                                               // 0.0
/*141 */     object_property_set_description(obj, "dump-guest-core",                                       // 0.0
/*143 */                                     "Include guest memory in  a core dump",                       // 0.0
/*145 */                                     NULL);                                                        // 0.0
/*147 */     object_property_add_bool(obj, "mem-merge",                                                    // 0.0
/*149 */                              machine_get_mem_merge,                                               // 0.0
/*151 */                              machine_set_mem_merge, NULL);                                        // 0.0
/*153 */     object_property_set_description(obj, "mem-merge",                                             // 0.0
/*155 */                                     "Enable/disable memory merge support",                        // 0.0
/*157 */                                     NULL);                                                        // 0.0
/*159 */     object_property_add_bool(obj, "usb",                                                          // 0.0
/*161 */                              machine_get_usb,                                                     // 0.0
/*163 */                              machine_set_usb, NULL);                                              // 0.0
/*165 */     object_property_set_description(obj, "usb",                                                   // 0.0
/*167 */                                     "Set on/off to enable/disable usb",                           // 0.0
/*169 */                                     NULL);                                                        // 0.0
/*171 */     object_property_add_str(obj, "firmware",                                                      // 0.0
/*173 */                             machine_get_firmware,                                                 // 0.0
/*175 */                             machine_set_firmware, NULL);                                          // 0.0
/*177 */     object_property_set_description(obj, "firmware",                                              // 0.0
/*179 */                                     "Firmware image",                                             // 0.0
/*181 */                                     NULL);                                                        // 0.0
/*183 */     object_property_add_bool(obj, "iommu",                                                        // 0.0
/*185 */                              machine_get_iommu,                                                   // 0.0
/*187 */                              machine_set_iommu, NULL);                                            // 0.0
/*189 */     object_property_set_description(obj, "iommu",                                                 // 0.0
/*191 */                                     "Set on/off to enable/disable Intel IOMMU (VT-d)",            // 0.0
/*193 */                                     NULL);                                                        // 0.0
/*197 */     /* Register notifier when init is done for sysbus sanity checks */                            // 0.0
/*199 */     ms->sysbus_notifier.notify = machine_init_notify;                                             // 0.0
/*201 */     qemu_add_machine_init_done_notifier(&ms->sysbus_notifier);                                    // 0.0
/*203 */ }                                                                                                 // 0.0
