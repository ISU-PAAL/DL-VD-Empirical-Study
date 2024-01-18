// commit message qemu@3010460fb9 (target=1, prob=0.36874643, correct=False): i386: hvf: inject General Protection Fault when vmexit through vmcall
/*0   */ int hvf_vcpu_exec(CPUState *cpu)                                                 // (16) 0.0293
/*2   */ {                                                                                // (27) 0.001953
/*4   */     X86CPU *x86_cpu = X86_CPU(cpu);                                              // (9) 0.03711
/*6   */     CPUX86State *env = &x86_cpu->env;                                            // (10) 0.03516
/*8   */     int ret = 0;                                                                 // (21) 0.01563
/*10  */     uint64_t rip = 0;                                                            // (19) 0.02148
/*14  */     cpu->halted = 0;                                                             // (20) 0.01953
/*18  */     if (hvf_process_events(cpu)) {                                               // (15) 0.03125
/*20  */         return EXCP_HLT;                                                         // (17) 0.02734
/*22  */     }                                                                            // (26) 0.007812
/*26  */     do {                                                                         // (25) 0.009766
/*28  */         if (cpu->vcpu_dirty) {                                                   // (14) 0.0332
/*30  */             hvf_put_registers(cpu);                                              // (5) 0.04297
/*32  */             cpu->vcpu_dirty = false;                                             // (7) 0.03906
/*34  */         }                                                                        // (22) 0.01562
/*38  */         if (hvf_inject_interrupts(cpu)) {                                        // (4) 0.04492
/*40  */             return EXCP_INTERRUPT;                                               // (8) 0.03906
/*42  */         }                                                                        // (24) 0.01562
/*44  */         vmx_update_tpr(cpu);                                                     // (12) 0.0332
/*48  */         qemu_mutex_unlock_iothread();                                            // (6) 0.04102
/*50  */         if (!cpu_is_bsp(X86_CPU(cpu)) && cpu->halted) {                          // (2) 0.05664
/*52  */             qemu_mutex_lock_iothread();                                          // (3) 0.04687
/*54  */             return EXCP_HLT;                                                     // (11) 0.03516
/*56  */         }                                                                        // (23) 0.01562
/*60  */         hv_return_t r  = hv_vcpu_run(cpu->hvf_fd);                               // (1) 0.0625
/*62  */         assert_hvf_ok(r);                                                        // (13) 0.0332
/*66  */         /* handle VMEXIT */                                                      // (18) 0.02539
/*68  */         uint64_t exit_reason = rvmcs(cpu->hvf_fd, VMCS_EXIT_REASON);             // (0) 0.07031
/*70  */         uint64_t exit_qual = rvmcs(cpu->hvf_fd, VMCS_EXIT_QUALIFICATION);        // 0.0
/*72  */         uint32_t ins_len = (uint32_t)rvmcs(cpu->hvf_fd,                          // 0.0
/*74  */                                            VMCS_EXIT_INSTRUCTION_LENGTH);        // 0.0
/*78  */         uint64_t idtvec_info = rvmcs(cpu->hvf_fd, VMCS_IDT_VECTORING_INFO);      // 0.0
/*82  */         hvf_store_events(cpu, ins_len, idtvec_info);                             // 0.0
/*84  */         rip = rreg(cpu->hvf_fd, HV_X86_RIP);                                     // 0.0
/*86  */         RFLAGS(env) = rreg(cpu->hvf_fd, HV_X86_RFLAGS);                          // 0.0
/*88  */         env->eflags = RFLAGS(env);                                               // 0.0
/*92  */         qemu_mutex_lock_iothread();                                              // 0.0
/*96  */         update_apic_tpr(cpu);                                                    // 0.0
/*98  */         current_cpu = cpu;                                                       // 0.0
/*102 */         ret = 0;                                                                 // 0.0
/*104 */         switch (exit_reason) {                                                   // 0.0
/*106 */         case EXIT_REASON_HLT: {                                                  // 0.0
/*108 */             macvm_set_rip(cpu, rip + ins_len);                                   // 0.0
/*110 */             if (!((cpu->interrupt_request & CPU_INTERRUPT_HARD) &&               // 0.0
/*112 */                 (EFLAGS(env) & IF_MASK))                                         // 0.0
/*114 */                 && !(cpu->interrupt_request & CPU_INTERRUPT_NMI) &&              // 0.0
/*116 */                 !(idtvec_info & VMCS_IDT_VEC_VALID)) {                           // 0.0
/*118 */                 cpu->halted = 1;                                                 // 0.0
/*120 */                 ret = EXCP_HLT;                                                  // 0.0
/*122 */             }                                                                    // 0.0
/*124 */             ret = EXCP_INTERRUPT;                                                // 0.0
/*126 */             break;                                                               // 0.0
/*128 */         }                                                                        // 0.0
/*130 */         case EXIT_REASON_MWAIT: {                                                // 0.0
/*132 */             ret = EXCP_INTERRUPT;                                                // 0.0
/*134 */             break;                                                               // 0.0
/*136 */         }                                                                        // 0.0
/*138 */             /* Need to check if MMIO or unmmaped fault */                        // 0.0
/*140 */         case EXIT_REASON_EPT_FAULT:                                              // 0.0
/*142 */         {                                                                        // 0.0
/*144 */             hvf_slot *slot;                                                      // 0.0
/*146 */             addr_t gpa = rvmcs(cpu->hvf_fd, VMCS_GUEST_PHYSICAL_ADDRESS);        // 0.0
/*150 */             if (((idtvec_info & VMCS_IDT_VEC_VALID) == 0) &&                     // 0.0
/*152 */                 ((exit_qual & EXIT_QUAL_NMIUDTI) != 0)) {                        // 0.0
/*154 */                 vmx_set_nmi_blocking(cpu);                                       // 0.0
/*156 */             }                                                                    // 0.0
/*160 */             slot = hvf_find_overlap_slot(gpa, gpa);                              // 0.0
/*162 */             /* mmio */                                                           // 0.0
/*164 */             if (ept_emulation_fault(slot, gpa, exit_qual)) {                     // 0.0
/*166 */                 struct x86_decode decode;                                        // 0.0
/*170 */                 load_regs(cpu);                                                  // 0.0
/*172 */                 env->hvf_emul->fetch_rip = rip;                                  // 0.0
/*176 */                 decode_instruction(env, &decode);                                // 0.0
/*178 */                 exec_instruction(env, &decode);                                  // 0.0
/*180 */                 store_regs(cpu);                                                 // 0.0
/*182 */                 break;                                                           // 0.0
/*184 */             }                                                                    // 0.0
/*186 */             break;                                                               // 0.0
/*188 */         }                                                                        // 0.0
/*190 */         case EXIT_REASON_INOUT:                                                  // 0.0
/*192 */         {                                                                        // 0.0
/*194 */             uint32_t in = (exit_qual & 8) != 0;                                  // 0.0
/*196 */             uint32_t size =  (exit_qual & 7) + 1;                                // 0.0
/*198 */             uint32_t string =  (exit_qual & 16) != 0;                            // 0.0
/*200 */             uint32_t port =  exit_qual >> 16;                                    // 0.0
/*202 */             /*uint32_t rep = (exit_qual & 0x20) != 0;*/                          // 0.0
/*206 */ #if 1                                                                            // 0.0
/*208 */             if (!string && in) {                                                 // 0.0
/*210 */                 uint64_t val = 0;                                                // 0.0
/*212 */                 load_regs(cpu);                                                  // 0.0
/*214 */                 hvf_handle_io(env, port, &val, 0, size, 1);                      // 0.0
/*216 */                 if (size == 1) {                                                 // 0.0
/*218 */                     AL(env) = val;                                               // 0.0
/*220 */                 } else if (size == 2) {                                          // 0.0
/*222 */                     AX(env) = val;                                               // 0.0
/*224 */                 } else if (size == 4) {                                          // 0.0
/*226 */                     RAX(env) = (uint32_t)val;                                    // 0.0
/*228 */                 } else {                                                         // 0.0
/*230 */                     VM_PANIC("size");                                            // 0.0
/*232 */                 }                                                                // 0.0
/*234 */                 RIP(env) += ins_len;                                             // 0.0
/*236 */                 store_regs(cpu);                                                 // 0.0
/*238 */                 break;                                                           // 0.0
/*240 */             } else if (!string && !in) {                                         // 0.0
/*242 */                 RAX(env) = rreg(cpu->hvf_fd, HV_X86_RAX);                        // 0.0
/*244 */                 hvf_handle_io(env, port, &RAX(env), 1, size, 1);                 // 0.0
/*246 */                 macvm_set_rip(cpu, rip + ins_len);                               // 0.0
/*248 */                 break;                                                           // 0.0
/*250 */             }                                                                    // 0.0
/*252 */ #endif                                                                           // 0.0
/*254 */             struct x86_decode decode;                                            // 0.0
/*258 */             load_regs(cpu);                                                      // 0.0
/*260 */             env->hvf_emul->fetch_rip = rip;                                      // 0.0
/*264 */             decode_instruction(env, &decode);                                    // 0.0
/*266 */             VM_PANIC_ON(ins_len != decode.len);                                  // 0.0
/*268 */             exec_instruction(env, &decode);                                      // 0.0
/*270 */             store_regs(cpu);                                                     // 0.0
/*274 */             break;                                                               // 0.0
/*276 */         }                                                                        // 0.0
/*278 */         case EXIT_REASON_CPUID: {                                                // 0.0
/*280 */             uint32_t rax = (uint32_t)rreg(cpu->hvf_fd, HV_X86_RAX);              // 0.0
/*282 */             uint32_t rbx = (uint32_t)rreg(cpu->hvf_fd, HV_X86_RBX);              // 0.0
/*284 */             uint32_t rcx = (uint32_t)rreg(cpu->hvf_fd, HV_X86_RCX);              // 0.0
/*286 */             uint32_t rdx = (uint32_t)rreg(cpu->hvf_fd, HV_X86_RDX);              // 0.0
/*290 */             cpu_x86_cpuid(env, rax, rcx, &rax, &rbx, &rcx, &rdx);                // 0.0
/*294 */             wreg(cpu->hvf_fd, HV_X86_RAX, rax);                                  // 0.0
/*296 */             wreg(cpu->hvf_fd, HV_X86_RBX, rbx);                                  // 0.0
/*298 */             wreg(cpu->hvf_fd, HV_X86_RCX, rcx);                                  // 0.0
/*300 */             wreg(cpu->hvf_fd, HV_X86_RDX, rdx);                                  // 0.0
/*304 */             macvm_set_rip(cpu, rip + ins_len);                                   // 0.0
/*306 */             break;                                                               // 0.0
/*308 */         }                                                                        // 0.0
/*310 */         case EXIT_REASON_XSETBV: {                                               // 0.0
/*312 */             X86CPU *x86_cpu = X86_CPU(cpu);                                      // 0.0
/*314 */             CPUX86State *env = &x86_cpu->env;                                    // 0.0
/*316 */             uint32_t eax = (uint32_t)rreg(cpu->hvf_fd, HV_X86_RAX);              // 0.0
/*318 */             uint32_t ecx = (uint32_t)rreg(cpu->hvf_fd, HV_X86_RCX);              // 0.0
/*320 */             uint32_t edx = (uint32_t)rreg(cpu->hvf_fd, HV_X86_RDX);              // 0.0
/*324 */             if (ecx) {                                                           // 0.0
/*326 */                 macvm_set_rip(cpu, rip + ins_len);                               // 0.0
/*328 */                 break;                                                           // 0.0
/*330 */             }                                                                    // 0.0
/*332 */             env->xcr0 = ((uint64_t)edx << 32) | eax;                             // 0.0
/*334 */             wreg(cpu->hvf_fd, HV_X86_XCR0, env->xcr0 | 1);                       // 0.0
/*336 */             macvm_set_rip(cpu, rip + ins_len);                                   // 0.0
/*338 */             break;                                                               // 0.0
/*340 */         }                                                                        // 0.0
/*342 */         case EXIT_REASON_INTR_WINDOW:                                            // 0.0
/*344 */             vmx_clear_int_window_exiting(cpu);                                   // 0.0
/*346 */             ret = EXCP_INTERRUPT;                                                // 0.0
/*348 */             break;                                                               // 0.0
/*350 */         case EXIT_REASON_NMI_WINDOW:                                             // 0.0
/*352 */             vmx_clear_nmi_window_exiting(cpu);                                   // 0.0
/*354 */             ret = EXCP_INTERRUPT;                                                // 0.0
/*356 */             break;                                                               // 0.0
/*358 */         case EXIT_REASON_EXT_INTR:                                               // 0.0
/*360 */             /* force exit and allow io handling */                               // 0.0
/*362 */             ret = EXCP_INTERRUPT;                                                // 0.0
/*364 */             break;                                                               // 0.0
/*366 */         case EXIT_REASON_RDMSR:                                                  // 0.0
/*368 */         case EXIT_REASON_WRMSR:                                                  // 0.0
/*370 */         {                                                                        // 0.0
/*372 */             load_regs(cpu);                                                      // 0.0
/*374 */             if (exit_reason == EXIT_REASON_RDMSR) {                              // 0.0
/*376 */                 simulate_rdmsr(cpu);                                             // 0.0
/*378 */             } else {                                                             // 0.0
/*380 */                 simulate_wrmsr(cpu);                                             // 0.0
/*382 */             }                                                                    // 0.0
/*384 */             RIP(env) += rvmcs(cpu->hvf_fd, VMCS_EXIT_INSTRUCTION_LENGTH);        // 0.0
/*386 */             store_regs(cpu);                                                     // 0.0
/*388 */             break;                                                               // 0.0
/*390 */         }                                                                        // 0.0
/*392 */         case EXIT_REASON_CR_ACCESS: {                                            // 0.0
/*394 */             int cr;                                                              // 0.0
/*396 */             int reg;                                                             // 0.0
/*400 */             load_regs(cpu);                                                      // 0.0
/*402 */             cr = exit_qual & 15;                                                 // 0.0
/*404 */             reg = (exit_qual >> 8) & 15;                                         // 0.0
/*408 */             switch (cr) {                                                        // 0.0
/*410 */             case 0x0: {                                                          // 0.0
/*412 */                 macvm_set_cr0(cpu->hvf_fd, RRX(env, reg));                       // 0.0
/*414 */                 break;                                                           // 0.0
/*416 */             }                                                                    // 0.0
/*418 */             case 4: {                                                            // 0.0
/*420 */                 macvm_set_cr4(cpu->hvf_fd, RRX(env, reg));                       // 0.0
/*422 */                 break;                                                           // 0.0
/*424 */             }                                                                    // 0.0
/*426 */             case 8: {                                                            // 0.0
/*428 */                 X86CPU *x86_cpu = X86_CPU(cpu);                                  // 0.0
/*430 */                 if (exit_qual & 0x10) {                                          // 0.0
/*432 */                     RRX(env, reg) = cpu_get_apic_tpr(x86_cpu->apic_state);       // 0.0
/*434 */                 } else {                                                         // 0.0
/*436 */                     int tpr = RRX(env, reg);                                     // 0.0
/*438 */                     cpu_set_apic_tpr(x86_cpu->apic_state, tpr);                  // 0.0
/*440 */                     ret = EXCP_INTERRUPT;                                        // 0.0
/*442 */                 }                                                                // 0.0
/*444 */                 break;                                                           // 0.0
/*446 */             }                                                                    // 0.0
/*448 */             default:                                                             // 0.0
/*450 */                 error_report("Unrecognized CR %d\n", cr);                        // 0.0
/*452 */                 abort();                                                         // 0.0
/*454 */             }                                                                    // 0.0
/*456 */             RIP(env) += ins_len;                                                 // 0.0
/*458 */             store_regs(cpu);                                                     // 0.0
/*460 */             break;                                                               // 0.0
/*462 */         }                                                                        // 0.0
/*464 */         case EXIT_REASON_APIC_ACCESS: { /* TODO */                               // 0.0
/*466 */             struct x86_decode decode;                                            // 0.0
/*470 */             load_regs(cpu);                                                      // 0.0
/*472 */             env->hvf_emul->fetch_rip = rip;                                      // 0.0
/*476 */             decode_instruction(env, &decode);                                    // 0.0
/*478 */             exec_instruction(env, &decode);                                      // 0.0
/*480 */             store_regs(cpu);                                                     // 0.0
/*482 */             break;                                                               // 0.0
/*484 */         }                                                                        // 0.0
/*486 */         case EXIT_REASON_TPR: {                                                  // 0.0
/*488 */             ret = 1;                                                             // 0.0
/*490 */             break;                                                               // 0.0
/*492 */         }                                                                        // 0.0
/*494 */         case EXIT_REASON_TASK_SWITCH: {                                          // 0.0
/*496 */             uint64_t vinfo = rvmcs(cpu->hvf_fd, VMCS_IDT_VECTORING_INFO);        // 0.0
/*498 */             x68_segment_selector sel = {.sel = exit_qual & 0xffff};              // 0.0
/*500 */             vmx_handle_task_switch(cpu, sel, (exit_qual >> 30) & 0x3,            // 0.0
/*502 */              vinfo & VMCS_INTR_VALID, vinfo & VECTORING_INFO_VECTOR_MASK, vinfo  // 0.0
/*504 */              & VMCS_INTR_T_MASK);                                                // 0.0
/*506 */             break;                                                               // 0.0
/*508 */         }                                                                        // 0.0
/*510 */         case EXIT_REASON_TRIPLE_FAULT: {                                         // 0.0
/*512 */             qemu_system_reset_request(SHUTDOWN_CAUSE_GUEST_RESET);               // 0.0
/*514 */             ret = EXCP_INTERRUPT;                                                // 0.0
/*516 */             break;                                                               // 0.0
/*518 */         }                                                                        // 0.0
/*520 */         case EXIT_REASON_RDPMC:                                                  // 0.0
/*522 */             wreg(cpu->hvf_fd, HV_X86_RAX, 0);                                    // 0.0
/*524 */             wreg(cpu->hvf_fd, HV_X86_RDX, 0);                                    // 0.0
/*526 */             macvm_set_rip(cpu, rip + ins_len);                                   // 0.0
/*528 */             break;                                                               // 0.0
/*530 */         case VMX_REASON_VMCALL:                                                  // 0.0
/*532 */             /* TODO: inject #GP fault */                                         // 0.0
/*534 */             break;                                                               // 0.0
/*536 */         default:                                                                 // 0.0
/*538 */             error_report("%llx: unhandled exit %llx\n", rip, exit_reason);       // 0.0
/*540 */         }                                                                        // 0.0
/*542 */     } while (ret == 0);                                                          // 0.0
/*546 */     return ret;                                                                  // 0.0
/*548 */ }                                                                                // 0.0
