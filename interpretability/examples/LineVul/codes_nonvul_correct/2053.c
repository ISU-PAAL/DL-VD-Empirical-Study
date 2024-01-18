// commit message qemu@1eabfce6d5 (target=0, prob=0.107270256, correct=True): target-i386: Remove has_msr_mtrr global variable
/*0   */ static int kvm_get_msrs(X86CPU *cpu)                                                          // (11) 0.03125
/*2   */ {                                                                                             // (26) 0.001953
/*4   */     CPUX86State *env = &cpu->env;                                                             // (16) 0.0293
/*6   */     struct kvm_msr_entry *msrs = cpu->kvm_msr_buf->entries;                                   // (7) 0.05469
/*8   */     int ret, i;                                                                               // (20) 0.01563
/*10  */     uint64_t mtrr_top_bits;                                                                   // (15) 0.0293
/*14  */     kvm_msr_buf_reset(cpu);                                                                   // (17) 0.0293
/*18  */     kvm_msr_entry_add(cpu, MSR_IA32_SYSENTER_CS, 0);                                          // (4) 0.05859
/*20  */     kvm_msr_entry_add(cpu, MSR_IA32_SYSENTER_ESP, 0);                                         // (2) 0.06055
/*22  */     kvm_msr_entry_add(cpu, MSR_IA32_SYSENTER_EIP, 0);                                         // (3) 0.06055
/*24  */     kvm_msr_entry_add(cpu, MSR_PAT, 0);                                                       // (9) 0.04492
/*26  */     if (has_msr_star) {                                                                       // (19) 0.02539
/*28  */         kvm_msr_entry_add(cpu, MSR_STAR, 0);                                                  // (8) 0.05078
/*30  */     }                                                                                         // (25) 0.007812
/*32  */     if (has_msr_hsave_pa) {                                                                   // (12) 0.03125
/*34  */         kvm_msr_entry_add(cpu, MSR_VM_HSAVE_PA, 0);                                           // (1) 0.0625
/*36  */     }                                                                                         // (23) 0.007812
/*38  */     if (has_msr_tsc_aux) {                                                                    // (14) 0.03125
/*40  */         kvm_msr_entry_add(cpu, MSR_TSC_AUX, 0);                                               // (6) 0.05859
/*42  */     }                                                                                         // (24) 0.007812
/*44  */     if (has_msr_tsc_adjust) {                                                                 // (13) 0.03125
/*46  */         kvm_msr_entry_add(cpu, MSR_TSC_ADJUST, 0);                                            // (5) 0.05859
/*48  */     }                                                                                         // (21) 0.007812
/*50  */     if (has_msr_tsc_deadline) {                                                               // (10) 0.0332
/*52  */         kvm_msr_entry_add(cpu, MSR_IA32_TSCDEADLINE, 0);                                      // (0) 0.06445
/*54  */     }                                                                                         // (22) 0.007812
/*56  */     if (has_msr_misc_enable) {                                                                // (18) 0.0293
/*58  */         kvm_msr_entry_add(cpu, MSR_IA32_MISC_ENABLE, 0);                                      // 0.0
/*60  */     }                                                                                         // 0.0
/*62  */     if (has_msr_smbase) {                                                                     // 0.0
/*64  */         kvm_msr_entry_add(cpu, MSR_IA32_SMBASE, 0);                                           // 0.0
/*66  */     }                                                                                         // 0.0
/*68  */     if (has_msr_feature_control) {                                                            // 0.0
/*70  */         kvm_msr_entry_add(cpu, MSR_IA32_FEATURE_CONTROL, 0);                                  // 0.0
/*72  */     }                                                                                         // 0.0
/*74  */     if (has_msr_bndcfgs) {                                                                    // 0.0
/*76  */         kvm_msr_entry_add(cpu, MSR_IA32_BNDCFGS, 0);                                          // 0.0
/*78  */     }                                                                                         // 0.0
/*80  */     if (has_msr_xss) {                                                                        // 0.0
/*82  */         kvm_msr_entry_add(cpu, MSR_IA32_XSS, 0);                                              // 0.0
/*84  */     }                                                                                         // 0.0
/*90  */     if (!env->tsc_valid) {                                                                    // 0.0
/*92  */         kvm_msr_entry_add(cpu, MSR_IA32_TSC, 0);                                              // 0.0
/*94  */         env->tsc_valid = !runstate_is_running();                                              // 0.0
/*96  */     }                                                                                         // 0.0
/*100 */ #ifdef TARGET_X86_64                                                                          // 0.0
/*102 */     if (lm_capable_kernel) {                                                                  // 0.0
/*104 */         kvm_msr_entry_add(cpu, MSR_CSTAR, 0);                                                 // 0.0
/*106 */         kvm_msr_entry_add(cpu, MSR_KERNELGSBASE, 0);                                          // 0.0
/*108 */         kvm_msr_entry_add(cpu, MSR_FMASK, 0);                                                 // 0.0
/*110 */         kvm_msr_entry_add(cpu, MSR_LSTAR, 0);                                                 // 0.0
/*112 */     }                                                                                         // 0.0
/*114 */ #endif                                                                                        // 0.0
/*116 */     kvm_msr_entry_add(cpu, MSR_KVM_SYSTEM_TIME, 0);                                           // 0.0
/*118 */     kvm_msr_entry_add(cpu, MSR_KVM_WALL_CLOCK, 0);                                            // 0.0
/*120 */     if (has_msr_async_pf_en) {                                                                // 0.0
/*122 */         kvm_msr_entry_add(cpu, MSR_KVM_ASYNC_PF_EN, 0);                                       // 0.0
/*124 */     }                                                                                         // 0.0
/*126 */     if (has_msr_pv_eoi_en) {                                                                  // 0.0
/*128 */         kvm_msr_entry_add(cpu, MSR_KVM_PV_EOI_EN, 0);                                         // 0.0
/*130 */     }                                                                                         // 0.0
/*132 */     if (has_msr_kvm_steal_time) {                                                             // 0.0
/*134 */         kvm_msr_entry_add(cpu, MSR_KVM_STEAL_TIME, 0);                                        // 0.0
/*136 */     }                                                                                         // 0.0
/*138 */     if (has_msr_architectural_pmu) {                                                          // 0.0
/*140 */         kvm_msr_entry_add(cpu, MSR_CORE_PERF_FIXED_CTR_CTRL, 0);                              // 0.0
/*142 */         kvm_msr_entry_add(cpu, MSR_CORE_PERF_GLOBAL_CTRL, 0);                                 // 0.0
/*144 */         kvm_msr_entry_add(cpu, MSR_CORE_PERF_GLOBAL_STATUS, 0);                               // 0.0
/*146 */         kvm_msr_entry_add(cpu, MSR_CORE_PERF_GLOBAL_OVF_CTRL, 0);                             // 0.0
/*148 */         for (i = 0; i < MAX_FIXED_COUNTERS; i++) {                                            // 0.0
/*150 */             kvm_msr_entry_add(cpu, MSR_CORE_PERF_FIXED_CTR0 + i, 0);                          // 0.0
/*152 */         }                                                                                     // 0.0
/*154 */         for (i = 0; i < num_architectural_pmu_counters; i++) {                                // 0.0
/*156 */             kvm_msr_entry_add(cpu, MSR_P6_PERFCTR0 + i, 0);                                   // 0.0
/*158 */             kvm_msr_entry_add(cpu, MSR_P6_EVNTSEL0 + i, 0);                                   // 0.0
/*160 */         }                                                                                     // 0.0
/*162 */     }                                                                                         // 0.0
/*166 */     if (env->mcg_cap) {                                                                       // 0.0
/*168 */         kvm_msr_entry_add(cpu, MSR_MCG_STATUS, 0);                                            // 0.0
/*170 */         kvm_msr_entry_add(cpu, MSR_MCG_CTL, 0);                                               // 0.0
/*172 */         if (has_msr_mcg_ext_ctl) {                                                            // 0.0
/*174 */             kvm_msr_entry_add(cpu, MSR_MCG_EXT_CTL, 0);                                       // 0.0
/*176 */         }                                                                                     // 0.0
/*178 */         for (i = 0; i < (env->mcg_cap & 0xff) * 4; i++) {                                     // 0.0
/*180 */             kvm_msr_entry_add(cpu, MSR_MC0_CTL + i, 0);                                       // 0.0
/*182 */         }                                                                                     // 0.0
/*184 */     }                                                                                         // 0.0
/*188 */     if (has_msr_hv_hypercall) {                                                               // 0.0
/*190 */         kvm_msr_entry_add(cpu, HV_X64_MSR_HYPERCALL, 0);                                      // 0.0
/*192 */         kvm_msr_entry_add(cpu, HV_X64_MSR_GUEST_OS_ID, 0);                                    // 0.0
/*194 */     }                                                                                         // 0.0
/*196 */     if (has_msr_hv_vapic) {                                                                   // 0.0
/*198 */         kvm_msr_entry_add(cpu, HV_X64_MSR_APIC_ASSIST_PAGE, 0);                               // 0.0
/*200 */     }                                                                                         // 0.0
/*202 */     if (has_msr_hv_tsc) {                                                                     // 0.0
/*204 */         kvm_msr_entry_add(cpu, HV_X64_MSR_REFERENCE_TSC, 0);                                  // 0.0
/*206 */     }                                                                                         // 0.0
/*208 */     if (has_msr_hv_crash) {                                                                   // 0.0
/*210 */         int j;                                                                                // 0.0
/*214 */         for (j = 0; j < HV_X64_MSR_CRASH_PARAMS; j++) {                                       // 0.0
/*216 */             kvm_msr_entry_add(cpu, HV_X64_MSR_CRASH_P0 + j, 0);                               // 0.0
/*218 */         }                                                                                     // 0.0
/*220 */     }                                                                                         // 0.0
/*222 */     if (has_msr_hv_runtime) {                                                                 // 0.0
/*224 */         kvm_msr_entry_add(cpu, HV_X64_MSR_VP_RUNTIME, 0);                                     // 0.0
/*226 */     }                                                                                         // 0.0
/*228 */     if (cpu->hyperv_synic) {                                                                  // 0.0
/*230 */         uint32_t msr;                                                                         // 0.0
/*234 */         kvm_msr_entry_add(cpu, HV_X64_MSR_SCONTROL, 0);                                       // 0.0
/*236 */         kvm_msr_entry_add(cpu, HV_X64_MSR_SVERSION, 0);                                       // 0.0
/*238 */         kvm_msr_entry_add(cpu, HV_X64_MSR_SIEFP, 0);                                          // 0.0
/*240 */         kvm_msr_entry_add(cpu, HV_X64_MSR_SIMP, 0);                                           // 0.0
/*242 */         for (msr = HV_X64_MSR_SINT0; msr <= HV_X64_MSR_SINT15; msr++) {                       // 0.0
/*244 */             kvm_msr_entry_add(cpu, msr, 0);                                                   // 0.0
/*246 */         }                                                                                     // 0.0
/*248 */     }                                                                                         // 0.0
/*250 */     if (has_msr_hv_stimer) {                                                                  // 0.0
/*252 */         uint32_t msr;                                                                         // 0.0
/*256 */         for (msr = HV_X64_MSR_STIMER0_CONFIG; msr <= HV_X64_MSR_STIMER3_COUNT;                // 0.0
/*258 */              msr++) {                                                                         // 0.0
/*260 */             kvm_msr_entry_add(cpu, msr, 0);                                                   // 0.0
/*262 */         }                                                                                     // 0.0
/*264 */     }                                                                                         // 0.0
/*266 */     if (has_msr_mtrr) {                                                                       // 0.0
/*268 */         kvm_msr_entry_add(cpu, MSR_MTRRdefType, 0);                                           // 0.0
/*270 */         kvm_msr_entry_add(cpu, MSR_MTRRfix64K_00000, 0);                                      // 0.0
/*272 */         kvm_msr_entry_add(cpu, MSR_MTRRfix16K_80000, 0);                                      // 0.0
/*274 */         kvm_msr_entry_add(cpu, MSR_MTRRfix16K_A0000, 0);                                      // 0.0
/*276 */         kvm_msr_entry_add(cpu, MSR_MTRRfix4K_C0000, 0);                                       // 0.0
/*278 */         kvm_msr_entry_add(cpu, MSR_MTRRfix4K_C8000, 0);                                       // 0.0
/*280 */         kvm_msr_entry_add(cpu, MSR_MTRRfix4K_D0000, 0);                                       // 0.0
/*282 */         kvm_msr_entry_add(cpu, MSR_MTRRfix4K_D8000, 0);                                       // 0.0
/*284 */         kvm_msr_entry_add(cpu, MSR_MTRRfix4K_E0000, 0);                                       // 0.0
/*286 */         kvm_msr_entry_add(cpu, MSR_MTRRfix4K_E8000, 0);                                       // 0.0
/*288 */         kvm_msr_entry_add(cpu, MSR_MTRRfix4K_F0000, 0);                                       // 0.0
/*290 */         kvm_msr_entry_add(cpu, MSR_MTRRfix4K_F8000, 0);                                       // 0.0
/*292 */         for (i = 0; i < MSR_MTRRcap_VCNT; i++) {                                              // 0.0
/*294 */             kvm_msr_entry_add(cpu, MSR_MTRRphysBase(i), 0);                                   // 0.0
/*296 */             kvm_msr_entry_add(cpu, MSR_MTRRphysMask(i), 0);                                   // 0.0
/*298 */         }                                                                                     // 0.0
/*300 */     }                                                                                         // 0.0
/*304 */     ret = kvm_vcpu_ioctl(CPU(cpu), KVM_GET_MSRS, cpu->kvm_msr_buf);                           // 0.0
/*306 */     if (ret < 0) {                                                                            // 0.0
/*308 */         return ret;                                                                           // 0.0
/*310 */     }                                                                                         // 0.0
/*314 */     assert(ret == cpu->kvm_msr_buf->nmsrs);                                                   // 0.0
/*316 */     /*                                                                                        // 0.0
/*318 */      * MTRR masks: Each mask consists of 5 parts                                              // 0.0
/*320 */      * a  10..0: must be zero                                                                 // 0.0
/*322 */      * b  11   : valid bit                                                                    // 0.0
/*324 */      * c n-1.12: actual mask bits                                                             // 0.0
/*326 */      * d  51..n: reserved must be zero                                                        // 0.0
/*328 */      * e  63.52: reserved must be zero                                                        // 0.0
/*330 */      *                                                                                        // 0.0
/*332 */      * 'n' is the number of physical bits supported by the CPU and is                         // 0.0
/*334 */      * apparently always <= 52.   We know our 'n' but don't know what                         // 0.0
/*336 */      * the destinations 'n' is; it might be smaller, in which case                            // 0.0
/*338 */      * it masks (c) on loading. It might be larger, in which case                             // 0.0
/*340 */      * we fill 'd' so that d..c is consistent irrespetive of the 'n'                          // 0.0
/*342 */      * we're migrating to.                                                                    // 0.0
/*344 */      */                                                                                       // 0.0
/*348 */     if (cpu->fill_mtrr_mask) {                                                                // 0.0
/*350 */         QEMU_BUILD_BUG_ON(TARGET_PHYS_ADDR_SPACE_BITS > 52);                                  // 0.0
/*352 */         assert(cpu->phys_bits <= TARGET_PHYS_ADDR_SPACE_BITS);                                // 0.0
/*354 */         mtrr_top_bits = MAKE_64BIT_MASK(cpu->phys_bits, 52 - cpu->phys_bits);                 // 0.0
/*356 */     } else {                                                                                  // 0.0
/*358 */         mtrr_top_bits = 0;                                                                    // 0.0
/*360 */     }                                                                                         // 0.0
/*364 */     for (i = 0; i < ret; i++) {                                                               // 0.0
/*366 */         uint32_t index = msrs[i].index;                                                       // 0.0
/*368 */         switch (index) {                                                                      // 0.0
/*370 */         case MSR_IA32_SYSENTER_CS:                                                            // 0.0
/*372 */             env->sysenter_cs = msrs[i].data;                                                  // 0.0
/*374 */             break;                                                                            // 0.0
/*376 */         case MSR_IA32_SYSENTER_ESP:                                                           // 0.0
/*378 */             env->sysenter_esp = msrs[i].data;                                                 // 0.0
/*380 */             break;                                                                            // 0.0
/*382 */         case MSR_IA32_SYSENTER_EIP:                                                           // 0.0
/*384 */             env->sysenter_eip = msrs[i].data;                                                 // 0.0
/*386 */             break;                                                                            // 0.0
/*388 */         case MSR_PAT:                                                                         // 0.0
/*390 */             env->pat = msrs[i].data;                                                          // 0.0
/*392 */             break;                                                                            // 0.0
/*394 */         case MSR_STAR:                                                                        // 0.0
/*396 */             env->star = msrs[i].data;                                                         // 0.0
/*398 */             break;                                                                            // 0.0
/*400 */ #ifdef TARGET_X86_64                                                                          // 0.0
/*402 */         case MSR_CSTAR:                                                                       // 0.0
/*404 */             env->cstar = msrs[i].data;                                                        // 0.0
/*406 */             break;                                                                            // 0.0
/*408 */         case MSR_KERNELGSBASE:                                                                // 0.0
/*410 */             env->kernelgsbase = msrs[i].data;                                                 // 0.0
/*412 */             break;                                                                            // 0.0
/*414 */         case MSR_FMASK:                                                                       // 0.0
/*416 */             env->fmask = msrs[i].data;                                                        // 0.0
/*418 */             break;                                                                            // 0.0
/*420 */         case MSR_LSTAR:                                                                       // 0.0
/*422 */             env->lstar = msrs[i].data;                                                        // 0.0
/*424 */             break;                                                                            // 0.0
/*426 */ #endif                                                                                        // 0.0
/*428 */         case MSR_IA32_TSC:                                                                    // 0.0
/*430 */             env->tsc = msrs[i].data;                                                          // 0.0
/*432 */             break;                                                                            // 0.0
/*434 */         case MSR_TSC_AUX:                                                                     // 0.0
/*436 */             env->tsc_aux = msrs[i].data;                                                      // 0.0
/*438 */             break;                                                                            // 0.0
/*440 */         case MSR_TSC_ADJUST:                                                                  // 0.0
/*442 */             env->tsc_adjust = msrs[i].data;                                                   // 0.0
/*444 */             break;                                                                            // 0.0
/*446 */         case MSR_IA32_TSCDEADLINE:                                                            // 0.0
/*448 */             env->tsc_deadline = msrs[i].data;                                                 // 0.0
/*450 */             break;                                                                            // 0.0
/*452 */         case MSR_VM_HSAVE_PA:                                                                 // 0.0
/*454 */             env->vm_hsave = msrs[i].data;                                                     // 0.0
/*456 */             break;                                                                            // 0.0
/*458 */         case MSR_KVM_SYSTEM_TIME:                                                             // 0.0
/*460 */             env->system_time_msr = msrs[i].data;                                              // 0.0
/*462 */             break;                                                                            // 0.0
/*464 */         case MSR_KVM_WALL_CLOCK:                                                              // 0.0
/*466 */             env->wall_clock_msr = msrs[i].data;                                               // 0.0
/*468 */             break;                                                                            // 0.0
/*470 */         case MSR_MCG_STATUS:                                                                  // 0.0
/*472 */             env->mcg_status = msrs[i].data;                                                   // 0.0
/*474 */             break;                                                                            // 0.0
/*476 */         case MSR_MCG_CTL:                                                                     // 0.0
/*478 */             env->mcg_ctl = msrs[i].data;                                                      // 0.0
/*480 */             break;                                                                            // 0.0
/*482 */         case MSR_MCG_EXT_CTL:                                                                 // 0.0
/*484 */             env->mcg_ext_ctl = msrs[i].data;                                                  // 0.0
/*486 */             break;                                                                            // 0.0
/*488 */         case MSR_IA32_MISC_ENABLE:                                                            // 0.0
/*490 */             env->msr_ia32_misc_enable = msrs[i].data;                                         // 0.0
/*492 */             break;                                                                            // 0.0
/*494 */         case MSR_IA32_SMBASE:                                                                 // 0.0
/*496 */             env->smbase = msrs[i].data;                                                       // 0.0
/*498 */             break;                                                                            // 0.0
/*500 */         case MSR_IA32_FEATURE_CONTROL:                                                        // 0.0
/*502 */             env->msr_ia32_feature_control = msrs[i].data;                                     // 0.0
/*504 */             break;                                                                            // 0.0
/*506 */         case MSR_IA32_BNDCFGS:                                                                // 0.0
/*508 */             env->msr_bndcfgs = msrs[i].data;                                                  // 0.0
/*510 */             break;                                                                            // 0.0
/*512 */         case MSR_IA32_XSS:                                                                    // 0.0
/*514 */             env->xss = msrs[i].data;                                                          // 0.0
/*516 */             break;                                                                            // 0.0
/*518 */         default:                                                                              // 0.0
/*520 */             if (msrs[i].index >= MSR_MC0_CTL &&                                               // 0.0
/*522 */                 msrs[i].index < MSR_MC0_CTL + (env->mcg_cap & 0xff) * 4) {                    // 0.0
/*524 */                 env->mce_banks[msrs[i].index - MSR_MC0_CTL] = msrs[i].data;                   // 0.0
/*526 */             }                                                                                 // 0.0
/*528 */             break;                                                                            // 0.0
/*530 */         case MSR_KVM_ASYNC_PF_EN:                                                             // 0.0
/*532 */             env->async_pf_en_msr = msrs[i].data;                                              // 0.0
/*534 */             break;                                                                            // 0.0
/*536 */         case MSR_KVM_PV_EOI_EN:                                                               // 0.0
/*538 */             env->pv_eoi_en_msr = msrs[i].data;                                                // 0.0
/*540 */             break;                                                                            // 0.0
/*542 */         case MSR_KVM_STEAL_TIME:                                                              // 0.0
/*544 */             env->steal_time_msr = msrs[i].data;                                               // 0.0
/*546 */             break;                                                                            // 0.0
/*548 */         case MSR_CORE_PERF_FIXED_CTR_CTRL:                                                    // 0.0
/*550 */             env->msr_fixed_ctr_ctrl = msrs[i].data;                                           // 0.0
/*552 */             break;                                                                            // 0.0
/*554 */         case MSR_CORE_PERF_GLOBAL_CTRL:                                                       // 0.0
/*556 */             env->msr_global_ctrl = msrs[i].data;                                              // 0.0
/*558 */             break;                                                                            // 0.0
/*560 */         case MSR_CORE_PERF_GLOBAL_STATUS:                                                     // 0.0
/*562 */             env->msr_global_status = msrs[i].data;                                            // 0.0
/*564 */             break;                                                                            // 0.0
/*566 */         case MSR_CORE_PERF_GLOBAL_OVF_CTRL:                                                   // 0.0
/*568 */             env->msr_global_ovf_ctrl = msrs[i].data;                                          // 0.0
/*570 */             break;                                                                            // 0.0
/*572 */         case MSR_CORE_PERF_FIXED_CTR0 ... MSR_CORE_PERF_FIXED_CTR0 + MAX_FIXED_COUNTERS - 1:  // 0.0
/*574 */             env->msr_fixed_counters[index - MSR_CORE_PERF_FIXED_CTR0] = msrs[i].data;         // 0.0
/*576 */             break;                                                                            // 0.0
/*578 */         case MSR_P6_PERFCTR0 ... MSR_P6_PERFCTR0 + MAX_GP_COUNTERS - 1:                       // 0.0
/*580 */             env->msr_gp_counters[index - MSR_P6_PERFCTR0] = msrs[i].data;                     // 0.0
/*582 */             break;                                                                            // 0.0
/*584 */         case MSR_P6_EVNTSEL0 ... MSR_P6_EVNTSEL0 + MAX_GP_COUNTERS - 1:                       // 0.0
/*586 */             env->msr_gp_evtsel[index - MSR_P6_EVNTSEL0] = msrs[i].data;                       // 0.0
/*588 */             break;                                                                            // 0.0
/*590 */         case HV_X64_MSR_HYPERCALL:                                                            // 0.0
/*592 */             env->msr_hv_hypercall = msrs[i].data;                                             // 0.0
/*594 */             break;                                                                            // 0.0
/*596 */         case HV_X64_MSR_GUEST_OS_ID:                                                          // 0.0
/*598 */             env->msr_hv_guest_os_id = msrs[i].data;                                           // 0.0
/*600 */             break;                                                                            // 0.0
/*602 */         case HV_X64_MSR_APIC_ASSIST_PAGE:                                                     // 0.0
/*604 */             env->msr_hv_vapic = msrs[i].data;                                                 // 0.0
/*606 */             break;                                                                            // 0.0
/*608 */         case HV_X64_MSR_REFERENCE_TSC:                                                        // 0.0
/*610 */             env->msr_hv_tsc = msrs[i].data;                                                   // 0.0
/*612 */             break;                                                                            // 0.0
/*614 */         case HV_X64_MSR_CRASH_P0 ... HV_X64_MSR_CRASH_P4:                                     // 0.0
/*616 */             env->msr_hv_crash_params[index - HV_X64_MSR_CRASH_P0] = msrs[i].data;             // 0.0
/*618 */             break;                                                                            // 0.0
/*620 */         case HV_X64_MSR_VP_RUNTIME:                                                           // 0.0
/*622 */             env->msr_hv_runtime = msrs[i].data;                                               // 0.0
/*624 */             break;                                                                            // 0.0
/*626 */         case HV_X64_MSR_SCONTROL:                                                             // 0.0
/*628 */             env->msr_hv_synic_control = msrs[i].data;                                         // 0.0
/*630 */             break;                                                                            // 0.0
/*632 */         case HV_X64_MSR_SVERSION:                                                             // 0.0
/*634 */             env->msr_hv_synic_version = msrs[i].data;                                         // 0.0
/*636 */             break;                                                                            // 0.0
/*638 */         case HV_X64_MSR_SIEFP:                                                                // 0.0
/*640 */             env->msr_hv_synic_evt_page = msrs[i].data;                                        // 0.0
/*642 */             break;                                                                            // 0.0
/*644 */         case HV_X64_MSR_SIMP:                                                                 // 0.0
/*646 */             env->msr_hv_synic_msg_page = msrs[i].data;                                        // 0.0
/*648 */             break;                                                                            // 0.0
/*650 */         case HV_X64_MSR_SINT0 ... HV_X64_MSR_SINT15:                                          // 0.0
/*652 */             env->msr_hv_synic_sint[index - HV_X64_MSR_SINT0] = msrs[i].data;                  // 0.0
/*654 */             break;                                                                            // 0.0
/*656 */         case HV_X64_MSR_STIMER0_CONFIG:                                                       // 0.0
/*658 */         case HV_X64_MSR_STIMER1_CONFIG:                                                       // 0.0
/*660 */         case HV_X64_MSR_STIMER2_CONFIG:                                                       // 0.0
/*662 */         case HV_X64_MSR_STIMER3_CONFIG:                                                       // 0.0
/*664 */             env->msr_hv_stimer_config[(index - HV_X64_MSR_STIMER0_CONFIG)/2] =                // 0.0
/*666 */                                 msrs[i].data;                                                 // 0.0
/*668 */             break;                                                                            // 0.0
/*670 */         case HV_X64_MSR_STIMER0_COUNT:                                                        // 0.0
/*672 */         case HV_X64_MSR_STIMER1_COUNT:                                                        // 0.0
/*674 */         case HV_X64_MSR_STIMER2_COUNT:                                                        // 0.0
/*676 */         case HV_X64_MSR_STIMER3_COUNT:                                                        // 0.0
/*678 */             env->msr_hv_stimer_count[(index - HV_X64_MSR_STIMER0_COUNT)/2] =                  // 0.0
/*680 */                                 msrs[i].data;                                                 // 0.0
/*682 */             break;                                                                            // 0.0
/*684 */         case MSR_MTRRdefType:                                                                 // 0.0
/*686 */             env->mtrr_deftype = msrs[i].data;                                                 // 0.0
/*688 */             break;                                                                            // 0.0
/*690 */         case MSR_MTRRfix64K_00000:                                                            // 0.0
/*692 */             env->mtrr_fixed[0] = msrs[i].data;                                                // 0.0
/*694 */             break;                                                                            // 0.0
/*696 */         case MSR_MTRRfix16K_80000:                                                            // 0.0
/*698 */             env->mtrr_fixed[1] = msrs[i].data;                                                // 0.0
/*700 */             break;                                                                            // 0.0
/*702 */         case MSR_MTRRfix16K_A0000:                                                            // 0.0
/*704 */             env->mtrr_fixed[2] = msrs[i].data;                                                // 0.0
/*706 */             break;                                                                            // 0.0
/*708 */         case MSR_MTRRfix4K_C0000:                                                             // 0.0
/*710 */             env->mtrr_fixed[3] = msrs[i].data;                                                // 0.0
/*712 */             break;                                                                            // 0.0
/*714 */         case MSR_MTRRfix4K_C8000:                                                             // 0.0
/*716 */             env->mtrr_fixed[4] = msrs[i].data;                                                // 0.0
/*718 */             break;                                                                            // 0.0
/*720 */         case MSR_MTRRfix4K_D0000:                                                             // 0.0
/*722 */             env->mtrr_fixed[5] = msrs[i].data;                                                // 0.0
/*724 */             break;                                                                            // 0.0
/*726 */         case MSR_MTRRfix4K_D8000:                                                             // 0.0
/*728 */             env->mtrr_fixed[6] = msrs[i].data;                                                // 0.0
/*730 */             break;                                                                            // 0.0
/*732 */         case MSR_MTRRfix4K_E0000:                                                             // 0.0
/*734 */             env->mtrr_fixed[7] = msrs[i].data;                                                // 0.0
/*736 */             break;                                                                            // 0.0
/*738 */         case MSR_MTRRfix4K_E8000:                                                             // 0.0
/*740 */             env->mtrr_fixed[8] = msrs[i].data;                                                // 0.0
/*742 */             break;                                                                            // 0.0
/*744 */         case MSR_MTRRfix4K_F0000:                                                             // 0.0
/*746 */             env->mtrr_fixed[9] = msrs[i].data;                                                // 0.0
/*748 */             break;                                                                            // 0.0
/*750 */         case MSR_MTRRfix4K_F8000:                                                             // 0.0
/*752 */             env->mtrr_fixed[10] = msrs[i].data;                                               // 0.0
/*754 */             break;                                                                            // 0.0
/*756 */         case MSR_MTRRphysBase(0) ... MSR_MTRRphysMask(MSR_MTRRcap_VCNT - 1):                  // 0.0
/*758 */             if (index & 1) {                                                                  // 0.0
/*760 */                 env->mtrr_var[MSR_MTRRphysIndex(index)].mask = msrs[i].data |                 // 0.0
/*762 */                                                                mtrr_top_bits;                 // 0.0
/*764 */             } else {                                                                          // 0.0
/*766 */                 env->mtrr_var[MSR_MTRRphysIndex(index)].base = msrs[i].data;                  // 0.0
/*768 */             }                                                                                 // 0.0
/*770 */             break;                                                                            // 0.0
/*772 */         }                                                                                     // 0.0
/*774 */     }                                                                                         // 0.0
/*778 */     return 0;                                                                                 // 0.0
/*780 */ }                                                                                             // 0.0
