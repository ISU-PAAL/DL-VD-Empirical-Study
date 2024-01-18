// commit message qemu@03ae4133ab (target=0, prob=0.93559545, correct=False): target-ppc: Add pvr_match() callback
/*0   */ static void ppc_cpu_class_init(ObjectClass *oc, void *data)             // (9) 0.03906
/*2   */ {                                                                       // (25) 0.001953
/*4   */     PowerPCCPUClass *pcc = POWERPC_CPU_CLASS(oc);                       // (7) 0.04102
/*6   */     CPUClass *cc = CPU_CLASS(oc);                                       // (21) 0.02734
/*8   */     DeviceClass *dc = DEVICE_CLASS(oc);                                 // (19) 0.0293
/*12  */     pcc->parent_realize = dc->realize;                                  // (18) 0.03125
/*14  */     pcc->pvr = CPU_POWERPC_DEFAULT_MASK;                                // (8) 0.04102
/*16  */     pcc->pvr_mask = CPU_POWERPC_DEFAULT_MASK;                           // (5) 0.04492
/*18  */     pcc->interrupts_big_endian = ppc_cpu_interrupts_big_endian_always;  // (0) 0.06055
/*20  */     dc->realize = ppc_cpu_realizefn;                                    // (14) 0.03516
/*22  */     dc->unrealize = ppc_cpu_unrealizefn;                                // (10) 0.03906
/*26  */     pcc->parent_reset = cc->reset;                                      // (20) 0.02734
/*28  */     cc->reset = ppc_cpu_reset;                                          // (22) 0.02734
/*32  */     cc->class_by_name = ppc_cpu_class_by_name;                          // (6) 0.04297
/*34  */     cc->has_work = ppc_cpu_has_work;                                    // (15) 0.03516
/*36  */     cc->do_interrupt = ppc_cpu_do_interrupt;                            // (12) 0.03906
/*38  */     cc->dump_state = ppc_cpu_dump_state;                                // (16) 0.03516
/*40  */     cc->dump_statistics = ppc_cpu_dump_statistics;                      // (11) 0.03906
/*42  */     cc->set_pc = ppc_cpu_set_pc;                                        // (17) 0.03516
/*44  */     cc->gdb_read_register = ppc_cpu_gdb_read_register;                  // (4) 0.04687
/*46  */     cc->gdb_write_register = ppc_cpu_gdb_write_register;                // (3) 0.04687
/*48  */ #ifdef CONFIG_USER_ONLY                                                 // (23) 0.01758
/*50  */     cc->handle_mmu_fault = ppc_cpu_handle_mmu_fault;                    // (2) 0.05078
/*52  */ #else                                                                   // (24) 0.003906
/*54  */     cc->get_phys_page_debug = ppc_cpu_get_phys_page_debug;              // (1) 0.05078
/*56  */     cc->vmsd = &vmstate_ppc_cpu;                                        // (13) 0.03516
/*58  */ #if defined(TARGET_PPC64)                                               // 0.0
/*60  */     cc->write_elf64_note = ppc64_cpu_write_elf64_note;                  // 0.0
/*62  */     cc->write_elf64_qemunote = ppc64_cpu_write_elf64_qemunote;          // 0.0
/*64  */ #endif                                                                  // 0.0
/*66  */ #endif                                                                  // 0.0
/*70  */     cc->gdb_num_core_regs = 71;                                         // 0.0
/*74  */ #ifdef USE_APPLE_GDB                                                    // 0.0
/*76  */     cc->gdb_read_register = ppc_cpu_gdb_read_register_apple;            // 0.0
/*78  */     cc->gdb_write_register = ppc_cpu_gdb_write_register_apple;          // 0.0
/*80  */     cc->gdb_num_core_regs = 71 + 32;                                    // 0.0
/*82  */ #endif                                                                  // 0.0
/*86  */ #if defined(TARGET_PPC64)                                               // 0.0
/*88  */     cc->gdb_core_xml_file = "power64-core.xml";                         // 0.0
/*90  */ #else                                                                   // 0.0
/*92  */     cc->gdb_core_xml_file = "power-core.xml";                           // 0.0
/*94  */ #endif                                                                  // 0.0
/*96  */ #ifndef CONFIG_USER_ONLY                                                // 0.0
/*98  */     cc->virtio_is_big_endian = ppc_cpu_is_big_endian;                   // 0.0
/*100 */ #endif                                                                  // 0.0
/*104 */     dc->fw_name = "PowerPC,UNKNOWN";                                    // 0.0
/*106 */ }                                                                       // 0.0
