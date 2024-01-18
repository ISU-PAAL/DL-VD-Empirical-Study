// commit message qemu@9646f4927f (target=0, prob=0.076289855, correct=True): target-i386: Don't try to enable PT State xsave component
/*0   */ void cpu_x86_cpuid(CPUX86State *env, uint32_t index, uint32_t count,           // (7) 0.05469
/*2   */                    uint32_t *eax, uint32_t *ebx,                               // (1) 0.06641
/*4   */                    uint32_t *ecx, uint32_t *edx)                               // (0) 0.06641
/*6   */ {                                                                              // (21) 0.001953
/*8   */     X86CPU *cpu = x86_env_get_cpu(env);                                        // (12) 0.03906
/*10  */     CPUState *cs = CPU(cpu);                                                   // (18) 0.02344
/*12  */     uint32_t pkg_offset;                                                       // (19) 0.02344
/*16  */     /* test if maximum index reached */                                        // (20) 0.01953
/*18  */     if (index & 0x80000000) {                                                  // (17) 0.02539
/*20  */         if (index > env->cpuid_xlevel) {                                       // (13) 0.03906
/*22  */             if (env->cpuid_xlevel2 > 0) {                                      // (11) 0.04883
/*24  */                 /* Handle the Centaur's CPUID instruction. */                  // (9) 0.05078
/*26  */                 if (index > env->cpuid_xlevel2) {                              // (6) 0.05664
/*28  */                     index = env->cpuid_xlevel2;                                // (3) 0.05859
/*30  */                 } else if (index < 0xC0000000) {                               // (8) 0.05273
/*32  */                     index = env->cpuid_xlevel;                                 // (5) 0.05664
/*34  */                 }                                                              // (15) 0.03125
/*36  */             } else {                                                           // (16) 0.02734
/*38  */                 /* Intel documentation states that invalid EAX input will      // (10) 0.04883
/*40  */                  * return the same information as EAX=cpuid_level              // (4) 0.05664
/*42  */                  * (Intel SDM Vol. 2A - Instruction Set Reference - CPUID)     // (2) 0.06445
/*44  */                  */                                                            // (14) 0.0332
/*46  */                 index =  env->cpuid_level;                                     // 0.0
/*48  */             }                                                                  // 0.0
/*50  */         }                                                                      // 0.0
/*52  */     } else {                                                                   // 0.0
/*54  */         if (index > env->cpuid_level)                                          // 0.0
/*56  */             index = env->cpuid_level;                                          // 0.0
/*58  */     }                                                                          // 0.0
/*62  */     switch(index) {                                                            // 0.0
/*64  */     case 0:                                                                    // 0.0
/*66  */         *eax = env->cpuid_level;                                               // 0.0
/*68  */         *ebx = env->cpuid_vendor1;                                             // 0.0
/*70  */         *edx = env->cpuid_vendor2;                                             // 0.0
/*72  */         *ecx = env->cpuid_vendor3;                                             // 0.0
/*74  */         break;                                                                 // 0.0
/*76  */     case 1:                                                                    // 0.0
/*78  */         *eax = env->cpuid_version;                                             // 0.0
/*80  */         *ebx = (cpu->apic_id << 24) |                                          // 0.0
/*82  */                8 << 8; /* CLFLUSH size in quad words, Linux wants it. */       // 0.0
/*84  */         *ecx = env->features[FEAT_1_ECX];                                      // 0.0
/*86  */         if ((*ecx & CPUID_EXT_XSAVE) && (env->cr[4] & CR4_OSXSAVE_MASK)) {     // 0.0
/*88  */             *ecx |= CPUID_EXT_OSXSAVE;                                         // 0.0
/*90  */         }                                                                      // 0.0
/*92  */         *edx = env->features[FEAT_1_EDX];                                      // 0.0
/*94  */         if (cs->nr_cores * cs->nr_threads > 1) {                               // 0.0
/*96  */             *ebx |= (cs->nr_cores * cs->nr_threads) << 16;                     // 0.0
/*98  */             *edx |= CPUID_HT;                                                  // 0.0
/*100 */         }                                                                      // 0.0
/*102 */         break;                                                                 // 0.0
/*104 */     case 2:                                                                    // 0.0
/*106 */         /* cache info: needed for Pentium Pro compatibility */                 // 0.0
/*108 */         if (cpu->cache_info_passthrough) {                                     // 0.0
/*110 */             host_cpuid(index, 0, eax, ebx, ecx, edx);                          // 0.0
/*112 */             break;                                                             // 0.0
/*114 */         }                                                                      // 0.0
/*116 */         *eax = 1; /* Number of CPUID[EAX=2] calls required */                  // 0.0
/*118 */         *ebx = 0;                                                              // 0.0
/*120 */         if (!cpu->enable_l3_cache) {                                           // 0.0
/*122 */             *ecx = 0;                                                          // 0.0
/*124 */         } else {                                                               // 0.0
/*126 */             *ecx = L3_N_DESCRIPTOR;                                            // 0.0
/*128 */         }                                                                      // 0.0
/*130 */         *edx = (L1D_DESCRIPTOR << 16) | \                                      // 0.0
/*132 */                (L1I_DESCRIPTOR <<  8) | \                                      // 0.0
/*134 */                (L2_DESCRIPTOR);                                                // 0.0
/*136 */         break;                                                                 // 0.0
/*138 */     case 4:                                                                    // 0.0
/*140 */         /* cache info: needed for Core compatibility */                        // 0.0
/*142 */         if (cpu->cache_info_passthrough) {                                     // 0.0
/*144 */             host_cpuid(index, count, eax, ebx, ecx, edx);                      // 0.0
/*146 */             *eax &= ~0xFC000000;                                               // 0.0
/*148 */         } else {                                                               // 0.0
/*150 */             *eax = 0;                                                          // 0.0
/*152 */             switch (count) {                                                   // 0.0
/*154 */             case 0: /* L1 dcache info */                                       // 0.0
/*156 */                 *eax |= CPUID_4_TYPE_DCACHE | \                                // 0.0
/*158 */                         CPUID_4_LEVEL(1) | \                                   // 0.0
/*160 */                         CPUID_4_SELF_INIT_LEVEL;                               // 0.0
/*162 */                 *ebx = (L1D_LINE_SIZE - 1) | \                                 // 0.0
/*164 */                        ((L1D_PARTITIONS - 1) << 12) | \                        // 0.0
/*166 */                        ((L1D_ASSOCIATIVITY - 1) << 22);                        // 0.0
/*168 */                 *ecx = L1D_SETS - 1;                                           // 0.0
/*170 */                 *edx = CPUID_4_NO_INVD_SHARING;                                // 0.0
/*172 */                 break;                                                         // 0.0
/*174 */             case 1: /* L1 icache info */                                       // 0.0
/*176 */                 *eax |= CPUID_4_TYPE_ICACHE | \                                // 0.0
/*178 */                         CPUID_4_LEVEL(1) | \                                   // 0.0
/*180 */                         CPUID_4_SELF_INIT_LEVEL;                               // 0.0
/*182 */                 *ebx = (L1I_LINE_SIZE - 1) | \                                 // 0.0
/*184 */                        ((L1I_PARTITIONS - 1) << 12) | \                        // 0.0
/*186 */                        ((L1I_ASSOCIATIVITY - 1) << 22);                        // 0.0
/*188 */                 *ecx = L1I_SETS - 1;                                           // 0.0
/*190 */                 *edx = CPUID_4_NO_INVD_SHARING;                                // 0.0
/*192 */                 break;                                                         // 0.0
/*194 */             case 2: /* L2 cache info */                                        // 0.0
/*196 */                 *eax |= CPUID_4_TYPE_UNIFIED | \                               // 0.0
/*198 */                         CPUID_4_LEVEL(2) | \                                   // 0.0
/*200 */                         CPUID_4_SELF_INIT_LEVEL;                               // 0.0
/*202 */                 if (cs->nr_threads > 1) {                                      // 0.0
/*204 */                     *eax |= (cs->nr_threads - 1) << 14;                        // 0.0
/*206 */                 }                                                              // 0.0
/*208 */                 *ebx = (L2_LINE_SIZE - 1) | \                                  // 0.0
/*210 */                        ((L2_PARTITIONS - 1) << 12) | \                         // 0.0
/*212 */                        ((L2_ASSOCIATIVITY - 1) << 22);                         // 0.0
/*214 */                 *ecx = L2_SETS - 1;                                            // 0.0
/*216 */                 *edx = CPUID_4_NO_INVD_SHARING;                                // 0.0
/*218 */                 break;                                                         // 0.0
/*220 */             case 3: /* L3 cache info */                                        // 0.0
/*222 */                 if (!cpu->enable_l3_cache) {                                   // 0.0
/*224 */                     *eax = 0;                                                  // 0.0
/*226 */                     *ebx = 0;                                                  // 0.0
/*228 */                     *ecx = 0;                                                  // 0.0
/*230 */                     *edx = 0;                                                  // 0.0
/*232 */                     break;                                                     // 0.0
/*234 */                 }                                                              // 0.0
/*236 */                 *eax |= CPUID_4_TYPE_UNIFIED | \                               // 0.0
/*238 */                         CPUID_4_LEVEL(3) | \                                   // 0.0
/*240 */                         CPUID_4_SELF_INIT_LEVEL;                               // 0.0
/*242 */                 pkg_offset = apicid_pkg_offset(cs->nr_cores, cs->nr_threads);  // 0.0
/*244 */                 *eax |= ((1 << pkg_offset) - 1) << 14;                         // 0.0
/*246 */                 *ebx = (L3_N_LINE_SIZE - 1) | \                                // 0.0
/*248 */                        ((L3_N_PARTITIONS - 1) << 12) | \                       // 0.0
/*250 */                        ((L3_N_ASSOCIATIVITY - 1) << 22);                       // 0.0
/*252 */                 *ecx = L3_N_SETS - 1;                                          // 0.0
/*254 */                 *edx = CPUID_4_INCLUSIVE | CPUID_4_COMPLEX_IDX;                // 0.0
/*256 */                 break;                                                         // 0.0
/*258 */             default: /* end of info */                                         // 0.0
/*260 */                 *eax = 0;                                                      // 0.0
/*262 */                 *ebx = 0;                                                      // 0.0
/*264 */                 *ecx = 0;                                                      // 0.0
/*266 */                 *edx = 0;                                                      // 0.0
/*268 */                 break;                                                         // 0.0
/*270 */             }                                                                  // 0.0
/*272 */         }                                                                      // 0.0
/*276 */         /* QEMU gives out its own APIC IDs, never pass down bits 31..26.  */   // 0.0
/*278 */         if ((*eax & 31) && cs->nr_cores > 1) {                                 // 0.0
/*280 */             *eax |= (cs->nr_cores - 1) << 26;                                  // 0.0
/*282 */         }                                                                      // 0.0
/*284 */         break;                                                                 // 0.0
/*286 */     case 5:                                                                    // 0.0
/*288 */         /* mwait info: needed for Core compatibility */                        // 0.0
/*290 */         *eax = 0; /* Smallest monitor-line size in bytes */                    // 0.0
/*292 */         *ebx = 0; /* Largest monitor-line size in bytes */                     // 0.0
/*294 */         *ecx = CPUID_MWAIT_EMX | CPUID_MWAIT_IBE;                              // 0.0
/*296 */         *edx = 0;                                                              // 0.0
/*298 */         break;                                                                 // 0.0
/*300 */     case 6:                                                                    // 0.0
/*302 */         /* Thermal and Power Leaf */                                           // 0.0
/*304 */         *eax = env->features[FEAT_6_EAX];                                      // 0.0
/*306 */         *ebx = 0;                                                              // 0.0
/*308 */         *ecx = 0;                                                              // 0.0
/*310 */         *edx = 0;                                                              // 0.0
/*312 */         break;                                                                 // 0.0
/*314 */     case 7:                                                                    // 0.0
/*316 */         /* Structured Extended Feature Flags Enumeration Leaf */               // 0.0
/*318 */         if (count == 0) {                                                      // 0.0
/*320 */             *eax = 0; /* Maximum ECX value for sub-leaves */                   // 0.0
/*322 */             *ebx = env->features[FEAT_7_0_EBX]; /* Feature flags */            // 0.0
/*324 */             *ecx = env->features[FEAT_7_0_ECX]; /* Feature flags */            // 0.0
/*326 */             if ((*ecx & CPUID_7_0_ECX_PKU) && env->cr[4] & CR4_PKE_MASK) {     // 0.0
/*328 */                 *ecx |= CPUID_7_0_ECX_OSPKE;                                   // 0.0
/*330 */             }                                                                  // 0.0
/*332 */             *edx = 0; /* Reserved */                                           // 0.0
/*334 */         } else {                                                               // 0.0
/*336 */             *eax = 0;                                                          // 0.0
/*338 */             *ebx = 0;                                                          // 0.0
/*340 */             *ecx = 0;                                                          // 0.0
/*342 */             *edx = 0;                                                          // 0.0
/*344 */         }                                                                      // 0.0
/*346 */         break;                                                                 // 0.0
/*348 */     case 9:                                                                    // 0.0
/*350 */         /* Direct Cache Access Information Leaf */                             // 0.0
/*352 */         *eax = 0; /* Bits 0-31 in DCA_CAP MSR */                               // 0.0
/*354 */         *ebx = 0;                                                              // 0.0
/*356 */         *ecx = 0;                                                              // 0.0
/*358 */         *edx = 0;                                                              // 0.0
/*360 */         break;                                                                 // 0.0
/*362 */     case 0xA:                                                                  // 0.0
/*364 */         /* Architectural Performance Monitoring Leaf */                        // 0.0
/*366 */         if (kvm_enabled() && cpu->enable_pmu) {                                // 0.0
/*368 */             KVMState *s = cs->kvm_state;                                       // 0.0
/*372 */             *eax = kvm_arch_get_supported_cpuid(s, 0xA, count, R_EAX);         // 0.0
/*374 */             *ebx = kvm_arch_get_supported_cpuid(s, 0xA, count, R_EBX);         // 0.0
/*376 */             *ecx = kvm_arch_get_supported_cpuid(s, 0xA, count, R_ECX);         // 0.0
/*378 */             *edx = kvm_arch_get_supported_cpuid(s, 0xA, count, R_EDX);         // 0.0
/*380 */         } else {                                                               // 0.0
/*382 */             *eax = 0;                                                          // 0.0
/*384 */             *ebx = 0;                                                          // 0.0
/*386 */             *ecx = 0;                                                          // 0.0
/*388 */             *edx = 0;                                                          // 0.0
/*390 */         }                                                                      // 0.0
/*392 */         break;                                                                 // 0.0
/*394 */     case 0xB:                                                                  // 0.0
/*396 */         /* Extended Topology Enumeration Leaf */                               // 0.0
/*398 */         if (!cpu->enable_cpuid_0xb) {                                          // 0.0
/*400 */                 *eax = *ebx = *ecx = *edx = 0;                                 // 0.0
/*402 */                 break;                                                         // 0.0
/*404 */         }                                                                      // 0.0
/*408 */         *ecx = count & 0xff;                                                   // 0.0
/*410 */         *edx = cpu->apic_id;                                                   // 0.0
/*414 */         switch (count) {                                                       // 0.0
/*416 */         case 0:                                                                // 0.0
/*418 */             *eax = apicid_core_offset(cs->nr_cores, cs->nr_threads);           // 0.0
/*420 */             *ebx = cs->nr_threads;                                             // 0.0
/*422 */             *ecx |= CPUID_TOPOLOGY_LEVEL_SMT;                                  // 0.0
/*424 */             break;                                                             // 0.0
/*426 */         case 1:                                                                // 0.0
/*428 */             *eax = apicid_pkg_offset(cs->nr_cores, cs->nr_threads);            // 0.0
/*430 */             *ebx = cs->nr_cores * cs->nr_threads;                              // 0.0
/*432 */             *ecx |= CPUID_TOPOLOGY_LEVEL_CORE;                                 // 0.0
/*434 */             break;                                                             // 0.0
/*436 */         default:                                                               // 0.0
/*438 */             *eax = 0;                                                          // 0.0
/*440 */             *ebx = 0;                                                          // 0.0
/*442 */             *ecx |= CPUID_TOPOLOGY_LEVEL_INVALID;                              // 0.0
/*444 */         }                                                                      // 0.0
/*448 */         assert(!(*eax & ~0x1f));                                               // 0.0
/*450 */         *ebx &= 0xffff; /* The count doesn't need to be reliable. */           // 0.0
/*452 */         break;                                                                 // 0.0
/*454 */     case 0xD: {                                                                // 0.0
/*456 */         KVMState *s = cs->kvm_state;                                           // 0.0
/*458 */         uint64_t ena_mask;                                                     // 0.0
/*460 */         int i;                                                                 // 0.0
/*464 */         /* Processor Extended State */                                         // 0.0
/*466 */         *eax = 0;                                                              // 0.0
/*468 */         *ebx = 0;                                                              // 0.0
/*470 */         *ecx = 0;                                                              // 0.0
/*472 */         *edx = 0;                                                              // 0.0
/*474 */         if (!(env->features[FEAT_1_ECX] & CPUID_EXT_XSAVE)) {                  // 0.0
/*476 */             break;                                                             // 0.0
/*478 */         }                                                                      // 0.0
/*480 */         if (kvm_enabled()) {                                                   // 0.0
/*482 */             ena_mask = kvm_arch_get_supported_cpuid(s, 0xd, 0, R_EDX);         // 0.0
/*484 */             ena_mask <<= 32;                                                   // 0.0
/*486 */             ena_mask |= kvm_arch_get_supported_cpuid(s, 0xd, 0, R_EAX);        // 0.0
/*488 */         } else {                                                               // 0.0
/*490 */             ena_mask = -1;                                                     // 0.0
/*492 */         }                                                                      // 0.0
/*496 */         if (count == 0) {                                                      // 0.0
/*498 */             *ecx = 0x240;                                                      // 0.0
/*500 */             for (i = 2; i < ARRAY_SIZE(x86_ext_save_areas); i++) {             // 0.0
/*502 */                 const ExtSaveArea *esa = &x86_ext_save_areas[i];               // 0.0
/*504 */                 if ((env->features[esa->feature] & esa->bits) == esa->bits     // 0.0
/*506 */                     && ((ena_mask >> i) & 1) != 0) {                           // 0.0
/*508 */                     if (i < 32) {                                              // 0.0
/*510 */                         *eax |= 1u << i;                                       // 0.0
/*512 */                     } else {                                                   // 0.0
/*514 */                         *edx |= 1u << (i - 32);                                // 0.0
/*516 */                     }                                                          // 0.0
/*518 */                     *ecx = MAX(*ecx, esa->offset + esa->size);                 // 0.0
/*520 */                 }                                                              // 0.0
/*522 */             }                                                                  // 0.0
/*524 */             *eax |= ena_mask & (XSTATE_FP_MASK | XSTATE_SSE_MASK);             // 0.0
/*526 */             *ebx = *ecx;                                                       // 0.0
/*528 */         } else if (count == 1) {                                               // 0.0
/*530 */             *eax = env->features[FEAT_XSAVE];                                  // 0.0
/*532 */         } else if (count < ARRAY_SIZE(x86_ext_save_areas)) {                   // 0.0
/*534 */             const ExtSaveArea *esa = &x86_ext_save_areas[count];               // 0.0
/*536 */             if ((env->features[esa->feature] & esa->bits) == esa->bits         // 0.0
/*538 */                 && ((ena_mask >> count) & 1) != 0) {                           // 0.0
/*540 */                 *eax = esa->size;                                              // 0.0
/*542 */                 *ebx = esa->offset;                                            // 0.0
/*544 */             }                                                                  // 0.0
/*546 */         }                                                                      // 0.0
/*548 */         break;                                                                 // 0.0
/*550 */     }                                                                          // 0.0
/*552 */     case 0x80000000:                                                           // 0.0
/*554 */         *eax = env->cpuid_xlevel;                                              // 0.0
/*556 */         *ebx = env->cpuid_vendor1;                                             // 0.0
/*558 */         *edx = env->cpuid_vendor2;                                             // 0.0
/*560 */         *ecx = env->cpuid_vendor3;                                             // 0.0
/*562 */         break;                                                                 // 0.0
/*564 */     case 0x80000001:                                                           // 0.0
/*566 */         *eax = env->cpuid_version;                                             // 0.0
/*568 */         *ebx = 0;                                                              // 0.0
/*570 */         *ecx = env->features[FEAT_8000_0001_ECX];                              // 0.0
/*572 */         *edx = env->features[FEAT_8000_0001_EDX];                              // 0.0
/*576 */         /* The Linux kernel checks for the CMPLegacy bit and                   // 0.0
/*578 */          * discards multiple thread information if it is set.                  // 0.0
/*580 */          * So don't set it here for Intel to make Linux guests happy.          // 0.0
/*582 */          */                                                                    // 0.0
/*584 */         if (cs->nr_cores * cs->nr_threads > 1) {                               // 0.0
/*586 */             if (env->cpuid_vendor1 != CPUID_VENDOR_INTEL_1 ||                  // 0.0
/*588 */                 env->cpuid_vendor2 != CPUID_VENDOR_INTEL_2 ||                  // 0.0
/*590 */                 env->cpuid_vendor3 != CPUID_VENDOR_INTEL_3) {                  // 0.0
/*592 */                 *ecx |= 1 << 1;    /* CmpLegacy bit */                         // 0.0
/*594 */             }                                                                  // 0.0
/*596 */         }                                                                      // 0.0
/*598 */         break;                                                                 // 0.0
/*600 */     case 0x80000002:                                                           // 0.0
/*602 */     case 0x80000003:                                                           // 0.0
/*604 */     case 0x80000004:                                                           // 0.0
/*606 */         *eax = env->cpuid_model[(index - 0x80000002) * 4 + 0];                 // 0.0
/*608 */         *ebx = env->cpuid_model[(index - 0x80000002) * 4 + 1];                 // 0.0
/*610 */         *ecx = env->cpuid_model[(index - 0x80000002) * 4 + 2];                 // 0.0
/*612 */         *edx = env->cpuid_model[(index - 0x80000002) * 4 + 3];                 // 0.0
/*614 */         break;                                                                 // 0.0
/*616 */     case 0x80000005:                                                           // 0.0
/*618 */         /* cache info (L1 cache) */                                            // 0.0
/*620 */         if (cpu->cache_info_passthrough) {                                     // 0.0
/*622 */             host_cpuid(index, 0, eax, ebx, ecx, edx);                          // 0.0
/*624 */             break;                                                             // 0.0
/*626 */         }                                                                      // 0.0
/*628 */         *eax = (L1_DTLB_2M_ASSOC << 24) | (L1_DTLB_2M_ENTRIES << 16) | \       // 0.0
/*630 */                (L1_ITLB_2M_ASSOC <<  8) | (L1_ITLB_2M_ENTRIES);                // 0.0
/*632 */         *ebx = (L1_DTLB_4K_ASSOC << 24) | (L1_DTLB_4K_ENTRIES << 16) | \       // 0.0
/*634 */                (L1_ITLB_4K_ASSOC <<  8) | (L1_ITLB_4K_ENTRIES);                // 0.0
/*636 */         *ecx = (L1D_SIZE_KB_AMD << 24) | (L1D_ASSOCIATIVITY_AMD << 16) | \     // 0.0
/*638 */                (L1D_LINES_PER_TAG << 8) | (L1D_LINE_SIZE);                     // 0.0
/*640 */         *edx = (L1I_SIZE_KB_AMD << 24) | (L1I_ASSOCIATIVITY_AMD << 16) | \     // 0.0
/*642 */                (L1I_LINES_PER_TAG << 8) | (L1I_LINE_SIZE);                     // 0.0
/*644 */         break;                                                                 // 0.0
/*646 */     case 0x80000006:                                                           // 0.0
/*648 */         /* cache info (L2 cache) */                                            // 0.0
/*650 */         if (cpu->cache_info_passthrough) {                                     // 0.0
/*652 */             host_cpuid(index, 0, eax, ebx, ecx, edx);                          // 0.0
/*654 */             break;                                                             // 0.0
/*656 */         }                                                                      // 0.0
/*658 */         *eax = (AMD_ENC_ASSOC(L2_DTLB_2M_ASSOC) << 28) | \                     // 0.0
/*660 */                (L2_DTLB_2M_ENTRIES << 16) | \                                  // 0.0
/*662 */                (AMD_ENC_ASSOC(L2_ITLB_2M_ASSOC) << 12) | \                     // 0.0
/*664 */                (L2_ITLB_2M_ENTRIES);                                           // 0.0
/*666 */         *ebx = (AMD_ENC_ASSOC(L2_DTLB_4K_ASSOC) << 28) | \                     // 0.0
/*668 */                (L2_DTLB_4K_ENTRIES << 16) | \                                  // 0.0
/*670 */                (AMD_ENC_ASSOC(L2_ITLB_4K_ASSOC) << 12) | \                     // 0.0
/*672 */                (L2_ITLB_4K_ENTRIES);                                           // 0.0
/*674 */         *ecx = (L2_SIZE_KB_AMD << 16) | \                                      // 0.0
/*676 */                (AMD_ENC_ASSOC(L2_ASSOCIATIVITY) << 12) | \                     // 0.0
/*678 */                (L2_LINES_PER_TAG << 8) | (L2_LINE_SIZE);                       // 0.0
/*680 */         if (!cpu->enable_l3_cache) {                                           // 0.0
/*682 */             *edx = ((L3_SIZE_KB / 512) << 18) | \                              // 0.0
/*684 */                    (AMD_ENC_ASSOC(L3_ASSOCIATIVITY) << 12) | \                 // 0.0
/*686 */                    (L3_LINES_PER_TAG << 8) | (L3_LINE_SIZE);                   // 0.0
/*688 */         } else {                                                               // 0.0
/*690 */             *edx = ((L3_N_SIZE_KB_AMD / 512) << 18) | \                        // 0.0
/*692 */                    (AMD_ENC_ASSOC(L3_N_ASSOCIATIVITY) << 12) | \               // 0.0
/*694 */                    (L3_N_LINES_PER_TAG << 8) | (L3_N_LINE_SIZE);               // 0.0
/*696 */         }                                                                      // 0.0
/*698 */         break;                                                                 // 0.0
/*700 */     case 0x80000007:                                                           // 0.0
/*702 */         *eax = 0;                                                              // 0.0
/*704 */         *ebx = 0;                                                              // 0.0
/*706 */         *ecx = 0;                                                              // 0.0
/*708 */         *edx = env->features[FEAT_8000_0007_EDX];                              // 0.0
/*710 */         break;                                                                 // 0.0
/*712 */     case 0x80000008:                                                           // 0.0
/*714 */         /* virtual & phys address size in low 2 bytes. */                      // 0.0
/*716 */         if (env->features[FEAT_8000_0001_EDX] & CPUID_EXT2_LM) {               // 0.0
/*718 */             /* 64 bit processor, 48 bits virtual, configurable                 // 0.0
/*720 */              * physical bits.                                                  // 0.0
/*722 */              */                                                                // 0.0
/*724 */             *eax = 0x00003000 + cpu->phys_bits;                                // 0.0
/*726 */         } else {                                                               // 0.0
/*728 */             *eax = cpu->phys_bits;                                             // 0.0
/*730 */         }                                                                      // 0.0
/*732 */         *ebx = 0;                                                              // 0.0
/*734 */         *ecx = 0;                                                              // 0.0
/*736 */         *edx = 0;                                                              // 0.0
/*738 */         if (cs->nr_cores * cs->nr_threads > 1) {                               // 0.0
/*740 */             *ecx |= (cs->nr_cores * cs->nr_threads) - 1;                       // 0.0
/*742 */         }                                                                      // 0.0
/*744 */         break;                                                                 // 0.0
/*746 */     case 0x8000000A:                                                           // 0.0
/*748 */         if (env->features[FEAT_8000_0001_ECX] & CPUID_EXT3_SVM) {              // 0.0
/*750 */             *eax = 0x00000001; /* SVM Revision */                              // 0.0
/*752 */             *ebx = 0x00000010; /* nr of ASIDs */                               // 0.0
/*754 */             *ecx = 0;                                                          // 0.0
/*756 */             *edx = env->features[FEAT_SVM]; /* optional features */            // 0.0
/*758 */         } else {                                                               // 0.0
/*760 */             *eax = 0;                                                          // 0.0
/*762 */             *ebx = 0;                                                          // 0.0
/*764 */             *ecx = 0;                                                          // 0.0
/*766 */             *edx = 0;                                                          // 0.0
/*768 */         }                                                                      // 0.0
/*770 */         break;                                                                 // 0.0
/*772 */     case 0xC0000000:                                                           // 0.0
/*774 */         *eax = env->cpuid_xlevel2;                                             // 0.0
/*776 */         *ebx = 0;                                                              // 0.0
/*778 */         *ecx = 0;                                                              // 0.0
/*780 */         *edx = 0;                                                              // 0.0
/*782 */         break;                                                                 // 0.0
/*784 */     case 0xC0000001:                                                           // 0.0
/*786 */         /* Support for VIA CPU's CPUID instruction */                          // 0.0
/*788 */         *eax = env->cpuid_version;                                             // 0.0
/*790 */         *ebx = 0;                                                              // 0.0
/*792 */         *ecx = 0;                                                              // 0.0
/*794 */         *edx = env->features[FEAT_C000_0001_EDX];                              // 0.0
/*796 */         break;                                                                 // 0.0
/*798 */     case 0xC0000002:                                                           // 0.0
/*800 */     case 0xC0000003:                                                           // 0.0
/*802 */     case 0xC0000004:                                                           // 0.0
/*804 */         /* Reserved for the future, and now filled with zero */                // 0.0
/*806 */         *eax = 0;                                                              // 0.0
/*808 */         *ebx = 0;                                                              // 0.0
/*810 */         *ecx = 0;                                                              // 0.0
/*812 */         *edx = 0;                                                              // 0.0
/*814 */         break;                                                                 // 0.0
/*816 */     default:                                                                   // 0.0
/*818 */         /* reserved values: zero */                                            // 0.0
/*820 */         *eax = 0;                                                              // 0.0
/*822 */         *ebx = 0;                                                              // 0.0
/*824 */         *ecx = 0;                                                              // 0.0
/*826 */         *edx = 0;                                                              // 0.0
/*828 */         break;                                                                 // 0.0
/*830 */     }                                                                          // 0.0
/*832 */ }                                                                              // 0.0
