// commit message qemu@3a5c76baf3 (target=0, prob=0.19406635, correct=True): fw_cfg: factor out initialization of FW_CFG_ID (rev. number)
/*0   */ static FWCfgState *bochs_bios_init(void)                                          // (14) 0.0332
/*2   */ {                                                                                 // (24) 0.001953
/*4   */     FWCfgState *fw_cfg;                                                           // (17) 0.02344
/*6   */     uint8_t *smbios_tables, *smbios_anchor;                                       // (12) 0.04492
/*8   */     size_t smbios_tables_len, smbios_anchor_len;                                  // (8) 0.04688
/*10  */     uint64_t *numa_fw_cfg;                                                        // (15) 0.0293
/*12  */     int i, j;                                                                     // (18) 0.01562
/*14  */     unsigned int apic_id_limit = pc_apic_id_limit(max_cpus);                      // (5) 0.05078
/*18  */     fw_cfg = fw_cfg_init_io(BIOS_CFG_IOPORT);                                     // (4) 0.05273
/*20  */     /* FW_CFG_MAX_CPUS is a bit confusing/problematic on x86:                     // (9) 0.04687
/*22  */      *                                                                            // (21) 0.009766
/*24  */      * SeaBIOS needs FW_CFG_MAX_CPUS for CPU hotplug, but the CPU hotplug         // (3) 0.05469
/*26  */      * QEMU<->SeaBIOS interface is not based on the "CPU index", but on the APIC  // (2) 0.05469
/*28  */      * ID of hotplugged CPUs[1]. This means that FW_CFG_MAX_CPUS is not the       // (1) 0.05664
/*30  */      * "maximum number of CPUs", but the "limit to the APIC ID values SeaBIOS     // (11) 0.04687
/*32  */      * may see".                                                                  // (19) 0.01562
/*34  */      *                                                                            // (20) 0.009766
/*36  */      * So, this means we must not use max_cpus, here, but the maximum possible    // (10) 0.04687
/*38  */      * APIC ID value, plus one.                                                   // (16) 0.02539
/*40  */      *                                                                            // (23) 0.009766
/*42  */      * [1] The only kind of "CPU identifier" used between SeaBIOS and QEMU is     // (6) 0.05078
/*44  */      *     the APIC ID, not the "CPU index"                                       // (13) 0.03906
/*46  */      */                                                                           // (22) 0.009766
/*48  */     fw_cfg_add_i16(fw_cfg, FW_CFG_MAX_CPUS, (uint16_t)apic_id_limit);             // (0) 0.07812
/*50  */     fw_cfg_add_i32(fw_cfg, FW_CFG_ID, 1);                                         // (7) 0.05078
/*52  */     fw_cfg_add_i64(fw_cfg, FW_CFG_RAM_SIZE, (uint64_t)ram_size);                  // 0.0
/*54  */     fw_cfg_add_bytes(fw_cfg, FW_CFG_ACPI_TABLES,                                  // 0.0
/*56  */                      acpi_tables, acpi_tables_len);                               // 0.0
/*58  */     fw_cfg_add_i32(fw_cfg, FW_CFG_IRQ0_OVERRIDE, kvm_allows_irq0_override());     // 0.0
/*62  */     smbios_tables = smbios_get_table_legacy(&smbios_tables_len);                  // 0.0
/*64  */     if (smbios_tables) {                                                          // 0.0
/*66  */         fw_cfg_add_bytes(fw_cfg, FW_CFG_SMBIOS_ENTRIES,                           // 0.0
/*68  */                          smbios_tables, smbios_tables_len);                       // 0.0
/*70  */     }                                                                             // 0.0
/*74  */     smbios_get_tables(&smbios_tables, &smbios_tables_len,                         // 0.0
/*76  */                       &smbios_anchor, &smbios_anchor_len);                        // 0.0
/*78  */     if (smbios_anchor) {                                                          // 0.0
/*80  */         fw_cfg_add_file(fw_cfg, "etc/smbios/smbios-tables",                       // 0.0
/*82  */                         smbios_tables, smbios_tables_len);                        // 0.0
/*84  */         fw_cfg_add_file(fw_cfg, "etc/smbios/smbios-anchor",                       // 0.0
/*86  */                         smbios_anchor, smbios_anchor_len);                        // 0.0
/*88  */     }                                                                             // 0.0
/*92  */     fw_cfg_add_bytes(fw_cfg, FW_CFG_E820_TABLE,                                   // 0.0
/*94  */                      &e820_reserve, sizeof(e820_reserve));                        // 0.0
/*96  */     fw_cfg_add_file(fw_cfg, "etc/e820", e820_table,                               // 0.0
/*98  */                     sizeof(struct e820_entry) * e820_entries);                    // 0.0
/*102 */     fw_cfg_add_bytes(fw_cfg, FW_CFG_HPET, &hpet_cfg, sizeof(hpet_cfg));           // 0.0
/*104 */     /* allocate memory for the NUMA channel: one (64bit) word for the number      // 0.0
/*106 */      * of nodes, one word for each VCPU->node and one word for each node to       // 0.0
/*108 */      * hold the amount of memory.                                                 // 0.0
/*110 */      */                                                                           // 0.0
/*112 */     numa_fw_cfg = g_new0(uint64_t, 1 + apic_id_limit + nb_numa_nodes);            // 0.0
/*114 */     numa_fw_cfg[0] = cpu_to_le64(nb_numa_nodes);                                  // 0.0
/*116 */     for (i = 0; i < max_cpus; i++) {                                              // 0.0
/*118 */         unsigned int apic_id = x86_cpu_apic_id_from_index(i);                     // 0.0
/*120 */         assert(apic_id < apic_id_limit);                                          // 0.0
/*122 */         for (j = 0; j < nb_numa_nodes; j++) {                                     // 0.0
/*124 */             if (test_bit(i, numa_info[j].node_cpu)) {                             // 0.0
/*126 */                 numa_fw_cfg[apic_id + 1] = cpu_to_le64(j);                        // 0.0
/*128 */                 break;                                                            // 0.0
/*130 */             }                                                                     // 0.0
/*132 */         }                                                                         // 0.0
/*134 */     }                                                                             // 0.0
/*136 */     for (i = 0; i < nb_numa_nodes; i++) {                                         // 0.0
/*138 */         numa_fw_cfg[apic_id_limit + 1 + i] = cpu_to_le64(numa_info[i].node_mem);  // 0.0
/*140 */     }                                                                             // 0.0
/*142 */     fw_cfg_add_bytes(fw_cfg, FW_CFG_NUMA, numa_fw_cfg,                            // 0.0
/*144 */                      (1 + apic_id_limit + nb_numa_nodes) *                        // 0.0
/*146 */                      sizeof(*numa_fw_cfg));                                       // 0.0
/*150 */     return fw_cfg;                                                                // 0.0
/*152 */ }                                                                                 // 0.0
