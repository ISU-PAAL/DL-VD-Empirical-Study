// commit message qemu@3dc6f86936 (target=0, prob=0.14520964, correct=True): Convert error_report() to warn_report()
/*0   */ static void spapr_populate_cpu_dt(CPUState *cs, void *fdt, int offset,         // (9) 0.05078
/*2   */                                   sPAPRMachineState *spapr)                    // (0) 0.08594
/*4   */ {                                                                              // (20) 0.001953
/*6   */     PowerPCCPU *cpu = POWERPC_CPU(cs);                                         // (13) 0.0332
/*8   */     CPUPPCState *env = &cpu->env;                                              // (15) 0.0293
/*10  */     PowerPCCPUClass *pcc = POWERPC_CPU_GET_CLASS(cs);                          // (10) 0.04492
/*12  */     int index = ppc_get_vcpu_dt_id(cpu);                                       // (11) 0.03906
/*14  */     uint32_t segs[] = {cpu_to_be32(28), cpu_to_be32(40),                       // (6) 0.05859
/*16  */                        0xffffffff, 0xffffffff};                                // (3) 0.0625
/*18  */     uint32_t tbfreq = kvm_enabled() ? kvmppc_get_tbfreq()                      // (7) 0.05859
/*20  */         : SPAPR_TIMEBASE_FREQ;                                                 // (12) 0.03906
/*22  */     uint32_t cpufreq = kvm_enabled() ? kvmppc_get_clockfreq() : 1000000000;    // (2) 0.0625
/*24  */     uint32_t page_sizes_prop[64];                                              // (14) 0.03125
/*26  */     size_t page_sizes_prop_size;                                               // (16) 0.0293
/*28  */     uint32_t vcpus_per_socket = smp_threads * smp_cores;                       // (8) 0.05273
/*30  */     uint32_t pft_size_prop[] = {0, cpu_to_be32(spapr->htab_shift)};            // (1) 0.06836
/*32  */     int compat_smt = MIN(smp_threads, ppc_compat_max_threads(cpu));            // (5) 0.05859
/*34  */     sPAPRDRConnector *drc;                                                     // (17) 0.02539
/*36  */     int drc_index;                                                             // (18) 0.01758
/*38  */     uint32_t radix_AP_encodings[PPC_PAGE_SIZES_MAX_SZ];                        // (4) 0.06055
/*40  */     int i;                                                                     // (19) 0.01172
/*44  */     drc = spapr_drc_by_id(TYPE_SPAPR_DRC_CPU, index);                          // 0.0
/*46  */     if (drc) {                                                                 // 0.0
/*48  */         drc_index = spapr_drc_index(drc);                                      // 0.0
/*50  */         _FDT((fdt_setprop_cell(fdt, offset, "ibm,my-drc-index", drc_index)));  // 0.0
/*52  */     }                                                                          // 0.0
/*56  */     _FDT((fdt_setprop_cell(fdt, offset, "reg", index)));                       // 0.0
/*58  */     _FDT((fdt_setprop_string(fdt, offset, "device_type", "cpu")));             // 0.0
/*62  */     _FDT((fdt_setprop_cell(fdt, offset, "cpu-version", env->spr[SPR_PVR])));   // 0.0
/*64  */     _FDT((fdt_setprop_cell(fdt, offset, "d-cache-block-size",                  // 0.0
/*66  */                            env->dcache_line_size)));                           // 0.0
/*68  */     _FDT((fdt_setprop_cell(fdt, offset, "d-cache-line-size",                   // 0.0
/*70  */                            env->dcache_line_size)));                           // 0.0
/*72  */     _FDT((fdt_setprop_cell(fdt, offset, "i-cache-block-size",                  // 0.0
/*74  */                            env->icache_line_size)));                           // 0.0
/*76  */     _FDT((fdt_setprop_cell(fdt, offset, "i-cache-line-size",                   // 0.0
/*78  */                            env->icache_line_size)));                           // 0.0
/*82  */     if (pcc->l1_dcache_size) {                                                 // 0.0
/*84  */         _FDT((fdt_setprop_cell(fdt, offset, "d-cache-size",                    // 0.0
/*86  */                                pcc->l1_dcache_size)));                         // 0.0
/*88  */     } else {                                                                   // 0.0
/*90  */         error_report("Warning: Unknown L1 dcache size for cpu");               // 0.0
/*92  */     }                                                                          // 0.0
/*94  */     if (pcc->l1_icache_size) {                                                 // 0.0
/*96  */         _FDT((fdt_setprop_cell(fdt, offset, "i-cache-size",                    // 0.0
/*98  */                                pcc->l1_icache_size)));                         // 0.0
/*100 */     } else {                                                                   // 0.0
/*102 */         error_report("Warning: Unknown L1 icache size for cpu");               // 0.0
/*104 */     }                                                                          // 0.0
/*108 */     _FDT((fdt_setprop_cell(fdt, offset, "timebase-frequency", tbfreq)));       // 0.0
/*110 */     _FDT((fdt_setprop_cell(fdt, offset, "clock-frequency", cpufreq)));         // 0.0
/*112 */     _FDT((fdt_setprop_cell(fdt, offset, "slb-size", env->slb_nr)));            // 0.0
/*114 */     _FDT((fdt_setprop_cell(fdt, offset, "ibm,slb-size", env->slb_nr)));        // 0.0
/*116 */     _FDT((fdt_setprop_string(fdt, offset, "status", "okay")));                 // 0.0
/*118 */     _FDT((fdt_setprop(fdt, offset, "64-bit", NULL, 0)));                       // 0.0
/*122 */     if (env->spr_cb[SPR_PURR].oea_read) {                                      // 0.0
/*124 */         _FDT((fdt_setprop(fdt, offset, "ibm,purr", NULL, 0)));                 // 0.0
/*126 */     }                                                                          // 0.0
/*130 */     if (env->mmu_model & POWERPC_MMU_1TSEG) {                                  // 0.0
/*132 */         _FDT((fdt_setprop(fdt, offset, "ibm,processor-segment-sizes",          // 0.0
/*134 */                           segs, sizeof(segs))));                               // 0.0
/*136 */     }                                                                          // 0.0
/*140 */     /* Advertise VMX/VSX (vector extensions) if available                      // 0.0
/*142 */      *   0 / no property == no vector extensions                               // 0.0
/*144 */      *   1               == VMX / Altivec available                            // 0.0
/*146 */      *   2               == VSX available */                                   // 0.0
/*148 */     if (env->insns_flags & PPC_ALTIVEC) {                                      // 0.0
/*150 */         uint32_t vmx = (env->insns_flags2 & PPC2_VSX) ? 2 : 1;                 // 0.0
/*154 */         _FDT((fdt_setprop_cell(fdt, offset, "ibm,vmx", vmx)));                 // 0.0
/*156 */     }                                                                          // 0.0
/*160 */     /* Advertise DFP (Decimal Floating Point) if available                     // 0.0
/*162 */      *   0 / no property == no DFP                                             // 0.0
/*164 */      *   1               == DFP available */                                   // 0.0
/*166 */     if (env->insns_flags2 & PPC2_DFP) {                                        // 0.0
/*168 */         _FDT((fdt_setprop_cell(fdt, offset, "ibm,dfp", 1)));                   // 0.0
/*170 */     }                                                                          // 0.0
/*174 */     page_sizes_prop_size = ppc_create_page_sizes_prop(env, page_sizes_prop,    // 0.0
/*176 */                                                   sizeof(page_sizes_prop));    // 0.0
/*178 */     if (page_sizes_prop_size) {                                                // 0.0
/*180 */         _FDT((fdt_setprop(fdt, offset, "ibm,segment-page-sizes",               // 0.0
/*182 */                           page_sizes_prop, page_sizes_prop_size)));            // 0.0
/*184 */     }                                                                          // 0.0
/*188 */     spapr_populate_pa_features(env, fdt, offset, false);                       // 0.0
/*192 */     _FDT((fdt_setprop_cell(fdt, offset, "ibm,chip-id",                         // 0.0
/*194 */                            cs->cpu_index / vcpus_per_socket)));                // 0.0
/*198 */     _FDT((fdt_setprop(fdt, offset, "ibm,pft-size",                             // 0.0
/*200 */                       pft_size_prop, sizeof(pft_size_prop))));                 // 0.0
/*204 */     if (nb_numa_nodes > 1) {                                                   // 0.0
/*206 */         _FDT(spapr_fixup_cpu_numa_dt(fdt, offset, cpu));                       // 0.0
/*208 */     }                                                                          // 0.0
/*212 */     _FDT(spapr_fixup_cpu_smt_dt(fdt, offset, cpu, compat_smt));                // 0.0
/*216 */     if (pcc->radix_page_info) {                                                // 0.0
/*218 */         for (i = 0; i < pcc->radix_page_info->count; i++) {                    // 0.0
/*220 */             radix_AP_encodings[i] =                                            // 0.0
/*222 */                 cpu_to_be32(pcc->radix_page_info->entries[i]);                 // 0.0
/*224 */         }                                                                      // 0.0
/*226 */         _FDT((fdt_setprop(fdt, offset, "ibm,processor-radix-AP-encodings",     // 0.0
/*228 */                           radix_AP_encodings,                                  // 0.0
/*230 */                           pcc->radix_page_info->count *                        // 0.0
/*232 */                           sizeof(radix_AP_encodings[0]))));                    // 0.0
/*234 */     }                                                                          // 0.0
/*236 */ }                                                                              // 0.0
