// commit message qemu@2cd5394311 (target=0, prob=0.265181, correct=True): cpu: Introduce a wrapper for tlb_flush() that can be used in common code
/*0  */ static void cpu_common_reset(CPUState *cpu)                // (8) 0.0405
/*2  */ {                                                          // (22) 0.003115
/*4  */     CPUClass *cc = CPU_GET_CLASS(cpu);                     // (5) 0.04984
/*8  */     if (qemu_loglevel_mask(CPU_LOG_RESET)) {               // (1) 0.07165
/*10 */         qemu_log("CPU Reset (CPU %d)\n", cpu->cpu_index);  // (0) 0.08723
/*12 */         log_cpu_state(cpu, cc->reset_dump_flags);          // (2) 0.07165
/*14 */     }                                                      // (18) 0.01246
/*18 */     cpu->interrupt_request = 0;                            // (13) 0.03738
/*20 */     cpu->halted = 0;                                       // (16) 0.03115
/*22 */     cpu->mem_io_pc = 0;                                    // (9) 0.0405
/*24 */     cpu->mem_io_vaddr = 0;                                 // (7) 0.04361
/*26 */     cpu->icount_extra = 0;                                 // (14) 0.03738
/*28 */     cpu->icount_decr.u32 = 0;                              // (4) 0.04984
/*30 */     cpu->can_do_io = 1;                                    // (10) 0.0405
/*32 */     cpu->exception_index = -1;                             // (11) 0.0405
/*34 */     cpu->crash_occurred = false;                           // (12) 0.0405
/*38 */     if (tcg_enabled()) {                                   // (15) 0.03427
/*40 */         cpu_tb_jmp_cache_clear(cpu);                       // (3) 0.06542
/*44 */ #ifdef CONFIG_SOFTMMU                                      // (17) 0.02804
/*46 */         tlb_flush(cpu, 0);                                 // (6) 0.04984
/*48 */ #endif                                                     // (20) 0.006231
/*50 */     }                                                      // (19) 0.01246
/*52 */ }                                                          // (21) 0.003115
