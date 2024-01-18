// commit message qemu@ce5b1bbf62 (target=1, prob=0.895328, correct=True): exec: move cpu_exec_init() calls to realize functions
/*0  */ static void openrisc_cpu_class_init(ObjectClass *oc, void *data)         // (8) 0.04102
/*2  */ {                                                                        // (28) 0.001953
/*4  */     OpenRISCCPUClass *occ = OPENRISC_CPU_CLASS(oc);                      // (7) 0.04297
/*6  */     CPUClass *cc = CPU_CLASS(occ);                                       // (20) 0.02734
/*8  */     DeviceClass *dc = DEVICE_CLASS(oc);                                  // (16) 0.0293
/*12 */     occ->parent_realize = dc->realize;                                   // (17) 0.0293
/*14 */     dc->realize = openrisc_cpu_realizefn;                                // (10) 0.03711
/*18 */     occ->parent_reset = cc->reset;                                       // (21) 0.02539
/*20 */     cc->reset = openrisc_cpu_reset;                                      // (19) 0.0293
/*24 */     cc->class_by_name = openrisc_cpu_class_by_name;                      // (5) 0.04492
/*26 */     cc->has_work = openrisc_cpu_has_work;                                // (14) 0.03711
/*28 */     cc->do_interrupt = openrisc_cpu_do_interrupt;                        // (9) 0.04102
/*30 */     cc->cpu_exec_interrupt = openrisc_cpu_exec_interrupt;                // (6) 0.04492
/*32 */     cc->dump_state = openrisc_cpu_dump_state;                            // (15) 0.03711
/*34 */     cc->set_pc = openrisc_cpu_set_pc;                                    // (13) 0.03711
/*36 */     cc->gdb_read_register = openrisc_cpu_gdb_read_register;              // (4) 0.04883
/*38 */     cc->gdb_write_register = openrisc_cpu_gdb_write_register;            // (3) 0.04883
/*40 */ #ifdef CONFIG_USER_ONLY                                                  // (23) 0.01758
/*42 */     cc->handle_mmu_fault = openrisc_cpu_handle_mmu_fault;                // (1) 0.05273
/*44 */ #else                                                                    // (27) 0.003906
/*46 */     cc->get_phys_page_debug = openrisc_cpu_get_phys_page_debug;          // (0) 0.05273
/*48 */     dc->vmsd = &vmstate_openrisc_cpu;                                    // (11) 0.03711
/*50 */ #endif                                                                   // (26) 0.003906
/*52 */     cc->gdb_num_core_regs = 32 + 3;                                      // (12) 0.03711
/*56 */     /*                                                                   // (25) 0.007812
/*58 */      * Reason: openrisc_cpu_initfn() calls cpu_exec_init(), which saves  // (2) 0.04883
/*60 */      * the object in cpus -> dangling pointer after final                // (18) 0.0293
/*62 */      * object_unref().                                                   // (22) 0.01953
/*64 */      */                                                                  // (24) 0.009766
/*66 */     dc->cannot_destroy_with_object_finalize_yet = true;                  // 0.0
/*68 */ }                                                                        // 0.0
