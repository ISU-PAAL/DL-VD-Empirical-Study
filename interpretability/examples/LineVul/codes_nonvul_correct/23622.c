// commit message qemu@ac1970fbe8 (target=0, prob=0.034561653, correct=True): memory: per-AddressSpace dispatch
/*0   */ void tlb_set_page(CPUArchState *env, target_ulong vaddr,                       // (8) 0.04102
/*2   */                   target_phys_addr_t paddr, int prot,                          // (2) 0.05859
/*4   */                   int mmu_idx, target_ulong size)                              // (3) 0.05859
/*6   */ {                                                                              // (28) 0.001953
/*8   */     MemoryRegionSection *section;                                              // (20) 0.01758
/*10  */     unsigned int index;                                                        // (24) 0.01367
/*12  */     target_ulong address;                                                      // (21) 0.01758
/*14  */     target_ulong code_address;                                                 // (18) 0.02148
/*16  */     uintptr_t addend;                                                          // (19) 0.01953
/*18  */     CPUTLBEntry *te;                                                           // (17) 0.02344
/*20  */     target_phys_addr_t iotlb;                                                  // (16) 0.02734
/*24  */     assert(size >= TARGET_PAGE_SIZE);                                          // (15) 0.0293
/*26  */     if (size != TARGET_PAGE_SIZE) {                                            // (14) 0.03125
/*28  */         tlb_add_large_page(env, vaddr, size);                                  // (5) 0.04492
/*30  */     }                                                                          // (25) 0.007812
/*32  */     section = phys_page_find(paddr >> TARGET_PAGE_BITS);                       // (6) 0.04492
/*34  */ #if defined(DEBUG_TLB)                                                         // (22) 0.01758
/*36  */     printf("tlb_set_page: vaddr=" TARGET_FMT_lx " paddr=0x" TARGET_FMT_plx     // (0) 0.07422
/*38  */            " prot=%x idx=%d pd=0x%08lx\n",                                     // (1) 0.0625
/*40  */            vaddr, paddr, prot, mmu_idx, pd);                                   // (4) 0.05273
/*42  */ #endif                                                                         // (27) 0.003906
/*46  */     address = vaddr;                                                           // (23) 0.01562
/*48  */     if (!(memory_region_is_ram(section->mr) ||                                 // (10) 0.03711
/*50  */           memory_region_is_romd(section->mr))) {                               // (7) 0.04492
/*52  */         /* IO memory case (romd handled later) */                              // (11) 0.03516
/*54  */         address |= TLB_MMIO;                                                   // (13) 0.0332
/*56  */     }                                                                          // (26) 0.007812
/*58  */     if (memory_region_is_ram(section->mr) ||                                   // (12) 0.03516
/*60  */         memory_region_is_romd(section->mr)) {                                  // (9) 0.04102
/*62  */         addend = (uintptr_t)memory_region_get_ram_ptr(section->mr)             // 0.0
/*64  */         + memory_region_section_addr(section, paddr);                          // 0.0
/*66  */     } else {                                                                   // 0.0
/*68  */         addend = 0;                                                            // 0.0
/*70  */     }                                                                          // 0.0
/*74  */     code_address = address;                                                    // 0.0
/*76  */     iotlb = memory_region_section_get_iotlb(env, section, vaddr, paddr, prot,  // 0.0
/*78  */                                             &address);                         // 0.0
/*82  */     index = (vaddr >> TARGET_PAGE_BITS) & (CPU_TLB_SIZE - 1);                  // 0.0
/*84  */     env->iotlb[mmu_idx][index] = iotlb - vaddr;                                // 0.0
/*86  */     te = &env->tlb_table[mmu_idx][index];                                      // 0.0
/*88  */     te->addend = addend - vaddr;                                               // 0.0
/*90  */     if (prot & PAGE_READ) {                                                    // 0.0
/*92  */         te->addr_read = address;                                               // 0.0
/*94  */     } else {                                                                   // 0.0
/*96  */         te->addr_read = -1;                                                    // 0.0
/*98  */     }                                                                          // 0.0
/*102 */     if (prot & PAGE_EXEC) {                                                    // 0.0
/*104 */         te->addr_code = code_address;                                          // 0.0
/*106 */     } else {                                                                   // 0.0
/*108 */         te->addr_code = -1;                                                    // 0.0
/*110 */     }                                                                          // 0.0
/*112 */     if (prot & PAGE_WRITE) {                                                   // 0.0
/*114 */         if ((memory_region_is_ram(section->mr) && section->readonly)           // 0.0
/*116 */             || memory_region_is_romd(section->mr)) {                           // 0.0
/*118 */             /* Write access calls the I/O callback.  */                        // 0.0
/*120 */             te->addr_write = address | TLB_MMIO;                               // 0.0
/*122 */         } else if (memory_region_is_ram(section->mr)                           // 0.0
/*124 */                    && !cpu_physical_memory_is_dirty(                           // 0.0
/*126 */                            section->mr->ram_addr                               // 0.0
/*128 */                            + memory_region_section_addr(section, paddr))) {    // 0.0
/*130 */             te->addr_write = address | TLB_NOTDIRTY;                           // 0.0
/*132 */         } else {                                                               // 0.0
/*134 */             te->addr_write = address;                                          // 0.0
/*136 */         }                                                                      // 0.0
/*138 */     } else {                                                                   // 0.0
/*140 */         te->addr_write = -1;                                                   // 0.0
/*142 */     }                                                                          // 0.0
/*144 */ }                                                                              // 0.0
