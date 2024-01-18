// commit message qemu@41264b385c (target=1, prob=0.9992192, correct=True): PPC/KVM: early validation of vcpu id
/*0   */ static void ppc_cpu_realizefn(DeviceState *dev, Error **errp)                   // (8) 0.04297
/*1   */ {                                                                               // (25) 0.001953
/*2   */     CPUState *cs = CPU(dev);                                                    // (18) 0.02344
/*3   */     PowerPCCPU *cpu = POWERPC_CPU(dev);                                         // (12) 0.0332
/*4   */     PowerPCCPUClass *pcc = POWERPC_CPU_GET_CLASS(cpu);                          // (7) 0.04492
/*5   */     Error *local_err = NULL;                                                    // (21) 0.02148
/*6   */ #if !defined(CONFIG_USER_ONLY)                                                  // (16) 0.02539
/*7   */     int max_smt = kvm_enabled() ? kvmppc_smt_threads() : 1;                     // (4) 0.05664
/*8   */ #endif                                                                          // (23) 0.003906
/*9   */ #if !defined(CONFIG_USER_ONLY)                                                  // (15) 0.02539
/*10  */     if (smp_threads > max_smt) {                                                // (13) 0.0332
/*11  */         error_setg(errp, "Cannot support more than %d threads on PPC with %s",  // (2) 0.06055
/*12  */                    max_smt, kvm_enabled() ? "KVM" : "TCG");                     // (1) 0.07422
/*13  */     if (!is_power_of_2(smp_threads)) {                                          // (10) 0.03906
/*14  */         error_setg(errp, "Cannot support %d threads on PPC with %s, "           // (3) 0.05859
/*15  */                    "threads count must be a power of 2.",                       // (5) 0.05664
/*16  */                    smp_threads, kvm_enabled() ? "KVM" : "TCG");                 // (0) 0.07617
/*17  */ #endif                                                                          // (24) 0.003906
/*18  */     cpu_exec_init(cs, &local_err);                                              // (14) 0.03125
/*19  */     if (local_err != NULL) {                                                    // (19) 0.02344
/*20  */         error_propagate(errp, local_err);                                       // (11) 0.03711
/*21  */ #if !defined(CONFIG_USER_ONLY)                                                  // (17) 0.02539
/*22  */     cpu->cpu_dt_id = (cs->cpu_index / smp_threads) * max_smt                    // (6) 0.05664
/*23  */         + (cs->cpu_index % smp_threads);                                        // (9) 0.04102
/*24  */ #endif                                                                          // (22) 0.003906
/*25  */     if (tcg_enabled()) {                                                        // (20) 0.02148
/*26  */         if (ppc_fixup_cpu(cpu) != 0) {                                          // 0.0
/*27  */             error_setg(errp, "Unable to emulate selected CPU with TCG");        // 0.0
/*28  */ #if defined(TARGET_PPCEMB)                                                      // 0.0
/*29  */     if (!ppc_cpu_is_valid(pcc)) {                                               // 0.0
/*30  */         error_setg(errp, "CPU does not possess a BookE or 4xx MMU. "            // 0.0
/*31  */                    "Please use qemu-system-ppc or qemu-system-ppc64 instead "   // 0.0
/*32  */                    "or choose another CPU model.");                             // 0.0
/*33  */ #endif                                                                          // 0.0
/*34  */     create_ppc_opcodes(cpu, &local_err);                                        // 0.0
/*35  */     if (local_err != NULL) {                                                    // 0.0
/*36  */         error_propagate(errp, local_err);                                       // 0.0
/*37  */     init_ppc_proc(cpu);                                                         // 0.0
/*38  */     if (pcc->insns_flags & PPC_FLOAT) {                                         // 0.0
/*39  */         gdb_register_coprocessor(cs, gdb_get_float_reg, gdb_set_float_reg,      // 0.0
/*40  */                                  33, "power-fpu.xml", 0);                       // 0.0
/*41  */     if (pcc->insns_flags & PPC_ALTIVEC) {                                       // 0.0
/*42  */         gdb_register_coprocessor(cs, gdb_get_avr_reg, gdb_set_avr_reg,          // 0.0
/*43  */                                  34, "power-altivec.xml", 0);                   // 0.0
/*44  */     if (pcc->insns_flags & PPC_SPE) {                                           // 0.0
/*45  */         gdb_register_coprocessor(cs, gdb_get_spe_reg, gdb_set_spe_reg,          // 0.0
/*46  */                                  34, "power-spe.xml", 0);                       // 0.0
/*47  */     if (pcc->insns_flags2 & PPC2_VSX) {                                         // 0.0
/*48  */         gdb_register_coprocessor(cs, gdb_get_vsx_reg, gdb_set_vsx_reg,          // 0.0
/*49  */                                  32, "power-vsx.xml", 0);                       // 0.0
/*50  */     qemu_init_vcpu(cs);                                                         // 0.0
/*51  */     pcc->parent_realize(dev, errp);                                             // 0.0
/*52  */ #if defined(PPC_DUMP_CPU)                                                       // 0.0
/*53  */     {                                                                           // 0.0
/*54  */         CPUPPCState *env = &cpu->env;                                           // 0.0
/*55  */         const char *mmu_model, *excp_model, *bus_model;                         // 0.0
/*56  */         switch (env->mmu_model) {                                               // 0.0
/*57  */         case POWERPC_MMU_32B:                                                   // 0.0
/*58  */             mmu_model = "PowerPC 32";                                           // 0.0
/*59  */             break;                                                              // 0.0
/*60  */         case POWERPC_MMU_SOFT_6xx:                                              // 0.0
/*61  */             mmu_model = "PowerPC 6xx/7xx with software driven TLBs";            // 0.0
/*62  */             break;                                                              // 0.0
/*63  */         case POWERPC_MMU_SOFT_74xx:                                             // 0.0
/*64  */             mmu_model = "PowerPC 74xx with software driven TLBs";               // 0.0
/*65  */             break;                                                              // 0.0
/*66  */         case POWERPC_MMU_SOFT_4xx:                                              // 0.0
/*67  */             mmu_model = "PowerPC 4xx with software driven TLBs";                // 0.0
/*68  */             break;                                                              // 0.0
/*69  */         case POWERPC_MMU_SOFT_4xx_Z:                                            // 0.0
/*70  */             mmu_model = "PowerPC 4xx with software driven TLBs "                // 0.0
/*71  */                 "and zones protections";                                        // 0.0
/*72  */             break;                                                              // 0.0
/*73  */         case POWERPC_MMU_REAL:                                                  // 0.0
/*74  */             mmu_model = "PowerPC real mode only";                               // 0.0
/*75  */             break;                                                              // 0.0
/*76  */         case POWERPC_MMU_MPC8xx:                                                // 0.0
/*77  */             mmu_model = "PowerPC MPC8xx";                                       // 0.0
/*78  */             break;                                                              // 0.0
/*79  */         case POWERPC_MMU_BOOKE:                                                 // 0.0
/*80  */             mmu_model = "PowerPC BookE";                                        // 0.0
/*81  */             break;                                                              // 0.0
/*82  */         case POWERPC_MMU_BOOKE206:                                              // 0.0
/*83  */             mmu_model = "PowerPC BookE 2.06";                                   // 0.0
/*84  */             break;                                                              // 0.0
/*85  */         case POWERPC_MMU_601:                                                   // 0.0
/*86  */             mmu_model = "PowerPC 601";                                          // 0.0
/*87  */             break;                                                              // 0.0
/*88  */ #if defined (TARGET_PPC64)                                                      // 0.0
/*89  */         case POWERPC_MMU_64B:                                                   // 0.0
/*90  */             mmu_model = "PowerPC 64";                                           // 0.0
/*91  */             break;                                                              // 0.0
/*92  */ #endif                                                                          // 0.0
/*93  */         default:                                                                // 0.0
/*94  */             mmu_model = "Unknown or invalid";                                   // 0.0
/*95  */             break;                                                              // 0.0
/*96  */         switch (env->excp_model) {                                              // 0.0
/*97  */         case POWERPC_EXCP_STD:                                                  // 0.0
/*98  */             excp_model = "PowerPC";                                             // 0.0
/*99  */             break;                                                              // 0.0
/*100 */         case POWERPC_EXCP_40x:                                                  // 0.0
/*101 */             excp_model = "PowerPC 40x";                                         // 0.0
/*102 */             break;                                                              // 0.0
/*103 */         case POWERPC_EXCP_601:                                                  // 0.0
/*104 */             excp_model = "PowerPC 601";                                         // 0.0
/*105 */             break;                                                              // 0.0
/*106 */         case POWERPC_EXCP_602:                                                  // 0.0
/*107 */             excp_model = "PowerPC 602";                                         // 0.0
/*108 */             break;                                                              // 0.0
/*109 */         case POWERPC_EXCP_603:                                                  // 0.0
/*110 */             excp_model = "PowerPC 603";                                         // 0.0
/*111 */             break;                                                              // 0.0
/*112 */         case POWERPC_EXCP_603E:                                                 // 0.0
/*113 */             excp_model = "PowerPC 603e";                                        // 0.0
/*114 */             break;                                                              // 0.0
/*115 */         case POWERPC_EXCP_604:                                                  // 0.0
/*116 */             excp_model = "PowerPC 604";                                         // 0.0
/*117 */             break;                                                              // 0.0
/*118 */         case POWERPC_EXCP_7x0:                                                  // 0.0
/*119 */             excp_model = "PowerPC 740/750";                                     // 0.0
/*120 */             break;                                                              // 0.0
/*121 */         case POWERPC_EXCP_7x5:                                                  // 0.0
/*122 */             excp_model = "PowerPC 745/755";                                     // 0.0
/*123 */             break;                                                              // 0.0
/*124 */         case POWERPC_EXCP_74xx:                                                 // 0.0
/*125 */             excp_model = "PowerPC 74xx";                                        // 0.0
/*126 */             break;                                                              // 0.0
/*127 */         case POWERPC_EXCP_BOOKE:                                                // 0.0
/*128 */             excp_model = "PowerPC BookE";                                       // 0.0
/*129 */             break;                                                              // 0.0
/*130 */ #if defined (TARGET_PPC64)                                                      // 0.0
/*131 */         case POWERPC_EXCP_970:                                                  // 0.0
/*132 */             excp_model = "PowerPC 970";                                         // 0.0
/*133 */             break;                                                              // 0.0
/*134 */ #endif                                                                          // 0.0
/*135 */         default:                                                                // 0.0
/*136 */             excp_model = "Unknown or invalid";                                  // 0.0
/*137 */             break;                                                              // 0.0
/*138 */         switch (env->bus_model) {                                               // 0.0
/*139 */         case PPC_FLAGS_INPUT_6xx:                                               // 0.0
/*140 */             bus_model = "PowerPC 6xx";                                          // 0.0
/*141 */             break;                                                              // 0.0
/*142 */         case PPC_FLAGS_INPUT_BookE:                                             // 0.0
/*143 */             bus_model = "PowerPC BookE";                                        // 0.0
/*144 */             break;                                                              // 0.0
/*145 */         case PPC_FLAGS_INPUT_405:                                               // 0.0
/*146 */             bus_model = "PowerPC 405";                                          // 0.0
/*147 */             break;                                                              // 0.0
/*148 */         case PPC_FLAGS_INPUT_401:                                               // 0.0
/*149 */             bus_model = "PowerPC 401/403";                                      // 0.0
/*150 */             break;                                                              // 0.0
/*151 */         case PPC_FLAGS_INPUT_RCPU:                                              // 0.0
/*152 */             bus_model = "RCPU / MPC8xx";                                        // 0.0
/*153 */             break;                                                              // 0.0
/*154 */ #if defined (TARGET_PPC64)                                                      // 0.0
/*155 */         case PPC_FLAGS_INPUT_970:                                               // 0.0
/*156 */             bus_model = "PowerPC 970";                                          // 0.0
/*157 */             break;                                                              // 0.0
/*158 */ #endif                                                                          // 0.0
/*159 */         default:                                                                // 0.0
/*160 */             bus_model = "Unknown or invalid";                                   // 0.0
/*161 */             break;                                                              // 0.0
/*162 */         printf("PowerPC %-12s : PVR %08x MSR %016" PRIx64 "\n"                  // 0.0
/*163 */                "    MMU model        : %s\n",                                   // 0.0
/*164 */                object_class_get_name(OBJECT_CLASS(pcc)),                        // 0.0
/*165 */                pcc->pvr, pcc->msr_mask, mmu_model);                             // 0.0
/*166 */ #if !defined(CONFIG_USER_ONLY)                                                  // 0.0
/*167 */         if (env->tlb.tlb6) {                                                    // 0.0
/*168 */             printf("                       %d %s TLB in %d ways\n",             // 0.0
/*169 */                    env->nb_tlb, env->id_tlbs ? "splitted" : "merged",           // 0.0
/*170 */                    env->nb_ways);                                               // 0.0
/*171 */ #endif                                                                          // 0.0
/*172 */         printf("    Exceptions model : %s\n"                                    // 0.0
/*173 */                "    Bus model        : %s\n",                                   // 0.0
/*174 */                excp_model, bus_model);                                          // 0.0
/*175 */         printf("    MSR features     :\n");                                     // 0.0
/*176 */         if (env->flags & POWERPC_FLAG_SPE)                                      // 0.0
/*177 */             printf("                        signal processing engine enable"    // 0.0
/*178 */                    "\n");                                                       // 0.0
/*179 */         else if (env->flags & POWERPC_FLAG_VRE)                                 // 0.0
/*180 */             printf("                        vector processor enable\n");        // 0.0
/*181 */         if (env->flags & POWERPC_FLAG_TGPR)                                     // 0.0
/*182 */             printf("                        temporary GPRs\n");                 // 0.0
/*183 */         else if (env->flags & POWERPC_FLAG_CE)                                  // 0.0
/*184 */             printf("                        critical input enable\n");          // 0.0
/*185 */         if (env->flags & POWERPC_FLAG_SE)                                       // 0.0
/*186 */             printf("                        single-step trace mode\n");         // 0.0
/*187 */         else if (env->flags & POWERPC_FLAG_DWE)                                 // 0.0
/*188 */             printf("                        debug wait enable\n");              // 0.0
/*189 */         else if (env->flags & POWERPC_FLAG_UBLE)                                // 0.0
/*190 */             printf("                        user BTB lock enable\n");           // 0.0
/*191 */         if (env->flags & POWERPC_FLAG_BE)                                       // 0.0
/*192 */             printf("                        branch-step trace mode\n");         // 0.0
/*193 */         else if (env->flags & POWERPC_FLAG_DE)                                  // 0.0
/*194 */             printf("                        debug interrupt enable\n");         // 0.0
/*195 */         if (env->flags & POWERPC_FLAG_PX)                                       // 0.0
/*196 */             printf("                        inclusive protection\n");           // 0.0
/*197 */         else if (env->flags & POWERPC_FLAG_PMM)                                 // 0.0
/*198 */             printf("                        performance monitor mark\n");       // 0.0
/*199 */         if (env->flags == POWERPC_FLAG_NONE)                                    // 0.0
/*200 */             printf("                        none\n");                           // 0.0
/*201 */         printf("    Time-base/decrementer clock source: %s\n",                  // 0.0
/*202 */                env->flags & POWERPC_FLAG_RTC_CLK ? "RTC clock" : "bus clock");  // 0.0
/*203 */         dump_ppc_insns(env);                                                    // 0.0
/*204 */         dump_ppc_sprs(env);                                                     // 0.0
/*205 */         fflush(stdout);                                                         // 0.0
/*206 */ #endif                                                                          // 0.0
