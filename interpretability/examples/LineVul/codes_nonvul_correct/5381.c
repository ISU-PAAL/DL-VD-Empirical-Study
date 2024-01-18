// commit message qemu@bf298f83c3 (target=0, prob=0.17030315, correct=True): A bit optimization for tlb_set_page()
/*0   */ void tlb_set_page(CPUState *env, target_ulong vaddr,                                                  // (7) 0.03906
/*2   */                   target_phys_addr_t paddr, int prot,                                                 // (3) 0.05859
/*4   */                   int mmu_idx, target_ulong size)                                                     // (4) 0.05859
/*6   */ {                                                                                                     // (29) 0.001953
/*8   */     PhysPageDesc *p;                                                                                  // (17) 0.01758
/*10  */     unsigned long pd;                                                                                 // (22) 0.01563
/*12  */     unsigned int index;                                                                               // (24) 0.01367
/*14  */     target_ulong address;                                                                             // (18) 0.01758
/*16  */     target_ulong code_address;                                                                        // (15) 0.02148
/*18  */     unsigned long addend;                                                                             // (20) 0.01563
/*20  */     CPUTLBEntry *te;                                                                                  // (14) 0.02344
/*22  */     CPUWatchpoint *wp;                                                                                // (16) 0.01758
/*24  */     target_phys_addr_t iotlb;                                                                         // (13) 0.02734
/*28  */     assert(size >= TARGET_PAGE_SIZE);                                                                 // (12) 0.0293
/*30  */     if (size != TARGET_PAGE_SIZE) {                                                                   // (10) 0.03125
/*32  */         tlb_add_large_page(env, vaddr, size);                                                         // (5) 0.04492
/*34  */     }                                                                                                 // (26) 0.007812
/*36  */     p = phys_page_find(paddr >> TARGET_PAGE_BITS);                                                    // (6) 0.04492
/*38  */     if (!p) {                                                                                         // (23) 0.01562
/*40  */         pd = IO_MEM_UNASSIGNED;                                                                       // (8) 0.03906
/*42  */     } else {                                                                                          // (25) 0.01172
/*44  */         pd = p->phys_offset;                                                                          // (11) 0.03125
/*46  */     }                                                                                                 // (27) 0.007812
/*48  */ #if defined(DEBUG_TLB)                                                                                // (19) 0.01758
/*50  */     printf("tlb_set_page: vaddr=" TARGET_FMT_lx " paddr=0x%08x prot=%x idx=%d smmu=%d pd=0x%08lx\n",  // (0) 0.1133
/*52  */            vaddr, (int)paddr, prot, mmu_idx, is_softmmu, pd);                                         // (2) 0.07031
/*54  */ #endif                                                                                                // (28) 0.003906
/*58  */     address = vaddr;                                                                                  // (21) 0.01563
/*60  */     if ((pd & ~TARGET_PAGE_MASK) > IO_MEM_ROM && !(pd & IO_MEM_ROMD)) {                               // (1) 0.07422
/*62  */         /* IO memory case (romd handled later) */                                                     // (9) 0.03516
/*64  */         address |= TLB_MMIO;                                                                          // 0.0
/*66  */     }                                                                                                 // 0.0
/*68  */     addend = (unsigned long)qemu_get_ram_ptr(pd & TARGET_PAGE_MASK);                                  // 0.0
/*70  */     if ((pd & ~TARGET_PAGE_MASK) <= IO_MEM_ROM) {                                                     // 0.0
/*72  */         /* Normal RAM.  */                                                                            // 0.0
/*74  */         iotlb = pd & TARGET_PAGE_MASK;                                                                // 0.0
/*76  */         if ((pd & ~TARGET_PAGE_MASK) == IO_MEM_RAM)                                                   // 0.0
/*78  */             iotlb |= IO_MEM_NOTDIRTY;                                                                 // 0.0
/*80  */         else                                                                                          // 0.0
/*82  */             iotlb |= IO_MEM_ROM;                                                                      // 0.0
/*84  */     } else {                                                                                          // 0.0
/*86  */         /* IO handlers are currently passed a physical address.                                       // 0.0
/*88  */            It would be nice to pass an offset from the base address                                   // 0.0
/*90  */            of that region.  This would avoid having to special case RAM,                              // 0.0
/*92  */            and avoid full address decoding in every device.                                           // 0.0
/*94  */            We can't use the high bits of pd for this because                                          // 0.0
/*96  */            IO_MEM_ROMD uses these as a ram address.  */                                               // 0.0
/*98  */         iotlb = (pd & ~TARGET_PAGE_MASK);                                                             // 0.0
/*100 */         if (p) {                                                                                      // 0.0
/*102 */             iotlb += p->region_offset;                                                                // 0.0
/*104 */         } else {                                                                                      // 0.0
/*106 */             iotlb += paddr;                                                                           // 0.0
/*108 */         }                                                                                             // 0.0
/*110 */     }                                                                                                 // 0.0
/*114 */     code_address = address;                                                                           // 0.0
/*116 */     /* Make accesses to pages with watchpoints go via the                                             // 0.0
/*118 */        watchpoint trap routines.  */                                                                  // 0.0
/*120 */     QTAILQ_FOREACH(wp, &env->watchpoints, entry) {                                                    // 0.0
/*122 */         if (vaddr == (wp->vaddr & TARGET_PAGE_MASK)) {                                                // 0.0
/*124 */             iotlb = io_mem_watch + paddr;                                                             // 0.0
/*126 */             /* TODO: The memory case can be optimized by not trapping                                 // 0.0
/*128 */                reads of pages with a write breakpoint.  */                                            // 0.0
/*130 */             address |= TLB_MMIO;                                                                      // 0.0
/*132 */         }                                                                                             // 0.0
/*134 */     }                                                                                                 // 0.0
/*138 */     index = (vaddr >> TARGET_PAGE_BITS) & (CPU_TLB_SIZE - 1);                                         // 0.0
/*140 */     env->iotlb[mmu_idx][index] = iotlb - vaddr;                                                       // 0.0
/*142 */     te = &env->tlb_table[mmu_idx][index];                                                             // 0.0
/*144 */     te->addend = addend - vaddr;                                                                      // 0.0
/*146 */     if (prot & PAGE_READ) {                                                                           // 0.0
/*148 */         te->addr_read = address;                                                                      // 0.0
/*150 */     } else {                                                                                          // 0.0
/*152 */         te->addr_read = -1;                                                                           // 0.0
/*154 */     }                                                                                                 // 0.0
/*158 */     if (prot & PAGE_EXEC) {                                                                           // 0.0
/*160 */         te->addr_code = code_address;                                                                 // 0.0
/*162 */     } else {                                                                                          // 0.0
/*164 */         te->addr_code = -1;                                                                           // 0.0
/*166 */     }                                                                                                 // 0.0
/*168 */     if (prot & PAGE_WRITE) {                                                                          // 0.0
/*170 */         if ((pd & ~TARGET_PAGE_MASK) == IO_MEM_ROM ||                                                 // 0.0
/*172 */             (pd & IO_MEM_ROMD)) {                                                                     // 0.0
/*174 */             /* Write access calls the I/O callback.  */                                               // 0.0
/*176 */             te->addr_write = address | TLB_MMIO;                                                      // 0.0
/*178 */         } else if ((pd & ~TARGET_PAGE_MASK) == IO_MEM_RAM &&                                          // 0.0
/*180 */                    !cpu_physical_memory_is_dirty(pd)) {                                               // 0.0
/*182 */             te->addr_write = address | TLB_NOTDIRTY;                                                  // 0.0
/*184 */         } else {                                                                                      // 0.0
/*186 */             te->addr_write = address;                                                                 // 0.0
/*188 */         }                                                                                             // 0.0
/*190 */     } else {                                                                                          // 0.0
/*192 */         te->addr_write = -1;                                                                          // 0.0
/*194 */     }                                                                                                 // 0.0
/*196 */ }                                                                                                     // 0.0
