// commit message qemu@b0706b7167 (target=1, prob=0.3711879, correct=False): cputlb: atomically update tlb fields used by tlb_reset_dirty
/*0   */ void tlb_set_page_with_attrs(CPUState *cpu, target_ulong vaddr,                       // (6) 0.04883
/*2   */                              hwaddr paddr, MemTxAttrs attrs, int prot,                // (0) 0.08594
/*4   */                              int mmu_idx, target_ulong size)                          // (1) 0.08008
/*6   */ {                                                                                     // (25) 0.001953
/*8   */     CPUArchState *env = cpu->env_ptr;                                                 // (13) 0.0293
/*10  */     MemoryRegionSection *section;                                                     // (19) 0.01758
/*12  */     unsigned int index;                                                               // (23) 0.01367
/*14  */     target_ulong address;                                                             // (20) 0.01758
/*16  */     target_ulong code_address;                                                        // (17) 0.02148
/*18  */     uintptr_t addend;                                                                 // (18) 0.01953
/*20  */     CPUTLBEntry *te;                                                                  // (16) 0.02344
/*22  */     hwaddr iotlb, xlat, sz;                                                           // (10) 0.03125
/*24  */     unsigned vidx = env->vtlb_index++ % CPU_VTLB_SIZE;                                // (7) 0.04687
/*26  */     int asidx = cpu_asidx_from_attrs(cpu, attrs);                                     // (8) 0.04687
/*30  */     assert_cpu_is_self(cpu);                                                          // (15) 0.02539
/*32  */     assert(size >= TARGET_PAGE_SIZE);                                                 // (14) 0.0293
/*34  */     if (size != TARGET_PAGE_SIZE) {                                                   // (12) 0.03125
/*36  */         tlb_add_large_page(env, vaddr, size);                                         // (9) 0.04492
/*38  */     }                                                                                 // (24) 0.007812
/*42  */     sz = size;                                                                        // (21) 0.01562
/*44  */     section = address_space_translate_for_iotlb(cpu, asidx, paddr, &xlat, &sz);       // (2) 0.06641
/*46  */     assert(sz >= TARGET_PAGE_SIZE);                                                   // (11) 0.03125
/*50  */     tlb_debug("vaddr=" TARGET_FMT_lx " paddr=0x" TARGET_FMT_plx                       // (3) 0.06641
/*52  */               " prot=%x idx=%d\n",                                                    // (5) 0.05078
/*54  */               vaddr, paddr, prot, mmu_idx);                                           // (4) 0.05273
/*58  */     address = vaddr;                                                                  // (22) 0.01562
/*60  */     if (!memory_region_is_ram(section->mr) && !memory_region_is_romd(section->mr)) {  // 0.0
/*62  */         /* IO memory case */                                                          // 0.0
/*64  */         address |= TLB_MMIO;                                                          // 0.0
/*66  */         addend = 0;                                                                   // 0.0
/*68  */     } else {                                                                          // 0.0
/*70  */         /* TLB_MMIO for rom/romd handled below */                                     // 0.0
/*72  */         addend = (uintptr_t)memory_region_get_ram_ptr(section->mr) + xlat;            // 0.0
/*74  */     }                                                                                 // 0.0
/*78  */     code_address = address;                                                           // 0.0
/*80  */     iotlb = memory_region_section_get_iotlb(cpu, section, vaddr, paddr, xlat,         // 0.0
/*82  */                                             prot, &address);                          // 0.0
/*86  */     index = (vaddr >> TARGET_PAGE_BITS) & (CPU_TLB_SIZE - 1);                         // 0.0
/*88  */     te = &env->tlb_table[mmu_idx][index];                                             // 0.0
/*92  */     /* do not discard the translation in te, evict it into a victim tlb */            // 0.0
/*94  */     env->tlb_v_table[mmu_idx][vidx] = *te;                                            // 0.0
/*96  */     env->iotlb_v[mmu_idx][vidx] = env->iotlb[mmu_idx][index];                         // 0.0
/*100 */     /* refill the tlb */                                                              // 0.0
/*102 */     env->iotlb[mmu_idx][index].addr = iotlb - vaddr;                                  // 0.0
/*104 */     env->iotlb[mmu_idx][index].attrs = attrs;                                         // 0.0
/*106 */     te->addend = addend - vaddr;                                                      // 0.0
/*108 */     if (prot & PAGE_READ) {                                                           // 0.0
/*110 */         te->addr_read = address;                                                      // 0.0
/*112 */     } else {                                                                          // 0.0
/*114 */         te->addr_read = -1;                                                           // 0.0
/*116 */     }                                                                                 // 0.0
/*120 */     if (prot & PAGE_EXEC) {                                                           // 0.0
/*122 */         te->addr_code = code_address;                                                 // 0.0
/*124 */     } else {                                                                          // 0.0
/*126 */         te->addr_code = -1;                                                           // 0.0
/*128 */     }                                                                                 // 0.0
/*130 */     if (prot & PAGE_WRITE) {                                                          // 0.0
/*132 */         if ((memory_region_is_ram(section->mr) && section->readonly)                  // 0.0
/*134 */             || memory_region_is_romd(section->mr)) {                                  // 0.0
/*136 */             /* Write access calls the I/O callback.  */                               // 0.0
/*138 */             te->addr_write = address | TLB_MMIO;                                      // 0.0
/*140 */         } else if (memory_region_is_ram(section->mr)                                  // 0.0
/*142 */                    && cpu_physical_memory_is_clean(                                   // 0.0
/*144 */                         memory_region_get_ram_addr(section->mr) + xlat)) {            // 0.0
/*146 */             te->addr_write = address | TLB_NOTDIRTY;                                  // 0.0
/*148 */         } else {                                                                      // 0.0
/*150 */             te->addr_write = address;                                                 // 0.0
/*152 */         }                                                                             // 0.0
/*154 */     } else {                                                                          // 0.0
/*156 */         te->addr_write = -1;                                                          // 0.0
/*158 */     }                                                                                 // 0.0
/*160 */ }                                                                                     // 0.0
