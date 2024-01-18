// commit message qemu@46232aaacb (target=0, prob=0.89716756, correct=False): cpu/apic: drop icc bus/bridge
/*0  */ static void x86_cpu_common_class_init(ObjectClass *oc, void *data)  // (5) 0.04297
/*2  */ {                                                                   // (24) 0.001953
/*4  */     X86CPUClass *xcc = X86_CPU_CLASS(oc);                           // (9) 0.03906
/*6  */     CPUClass *cc = CPU_CLASS(oc);                                   // (20) 0.02734
/*8  */     DeviceClass *dc = DEVICE_CLASS(oc);                             // (18) 0.0293
/*12 */     xcc->parent_realize = dc->realize;                              // (17) 0.03125
/*14 */     dc->realize = x86_cpu_realizefn;                                // (12) 0.03516
/*16 */     dc->bus_type = TYPE_ICC_BUS;                                    // (16) 0.03125
/*18 */     dc->props = x86_cpu_properties;                                 // (19) 0.0293
/*22 */     xcc->parent_reset = cc->reset;                                  // (21) 0.02734
/*24 */     cc->reset = x86_cpu_reset;                                      // (22) 0.02734
/*26 */     cc->reset_dump_flags = CPU_DUMP_FPU | CPU_DUMP_CCOP;            // (1) 0.05273
/*30 */     cc->class_by_name = x86_cpu_class_by_name;                      // (7) 0.04297
/*32 */     cc->parse_features = x86_cpu_parse_featurestr;                  // (11) 0.03711
/*34 */     cc->has_work = x86_cpu_has_work;                                // (15) 0.03516
/*36 */     cc->do_interrupt = x86_cpu_do_interrupt;                        // (10) 0.03906
/*38 */     cc->cpu_exec_interrupt = x86_cpu_exec_interrupt;                // (8) 0.04297
/*40 */     cc->dump_state = x86_cpu_dump_state;                            // (14) 0.03516
/*42 */     cc->set_pc = x86_cpu_set_pc;                                    // (13) 0.03516
/*44 */     cc->synchronize_from_tb = x86_cpu_synchronize_from_tb;          // (0) 0.05469
/*46 */     cc->gdb_read_register = x86_cpu_gdb_read_register;              // (3) 0.04687
/*48 */     cc->gdb_write_register = x86_cpu_gdb_write_register;            // (4) 0.04687
/*50 */     cc->get_arch_id = x86_cpu_get_arch_id;                          // (6) 0.04297
/*52 */     cc->get_paging_enabled = x86_cpu_get_paging_enabled;            // (2) 0.04687
/*54 */ #ifdef CONFIG_USER_ONLY                                             // (23) 0.01758
/*56 */     cc->handle_mmu_fault = x86_cpu_handle_mmu_fault;                // 0.0
/*58 */ #else                                                               // 0.0
/*60 */     cc->get_memory_mapping = x86_cpu_get_memory_mapping;            // 0.0
/*62 */     cc->get_phys_page_debug = x86_cpu_get_phys_page_debug;          // 0.0
/*64 */     cc->write_elf64_note = x86_cpu_write_elf64_note;                // 0.0
/*66 */     cc->write_elf64_qemunote = x86_cpu_write_elf64_qemunote;        // 0.0
/*68 */     cc->write_elf32_note = x86_cpu_write_elf32_note;                // 0.0
/*70 */     cc->write_elf32_qemunote = x86_cpu_write_elf32_qemunote;        // 0.0
/*72 */     cc->vmsd = &vmstate_x86_cpu;                                    // 0.0
/*74 */ #endif                                                              // 0.0
/*76 */     cc->gdb_num_core_regs = CPU_NB_REGS * 2 + 25;                   // 0.0
/*78 */ #ifndef CONFIG_USER_ONLY                                            // 0.0
/*80 */     cc->debug_excp_handler = breakpoint_handler;                    // 0.0
/*82 */ #endif                                                              // 0.0
/*84 */     cc->cpu_exec_enter = x86_cpu_exec_enter;                        // 0.0
/*86 */     cc->cpu_exec_exit = x86_cpu_exec_exit;                          // 0.0
/*88 */ }                                                                   // 0.0
