// commit message qemu@bf55b7afce (target=0, prob=0.39694777, correct=True): memory: tune last param of iommu_ops.translate()
/*0  */ static MemoryRegionSection address_space_do_translate(AddressSpace *as,             // (7) 0.03516
/*2  */                                                       hwaddr addr,                  // (3) 0.1133
/*4  */                                                       hwaddr *xlat,                 // (0) 0.1172
/*6  */                                                       hwaddr *plen,                 // (1) 0.1172
/*8  */                                                       bool is_write,                // (4) 0.1133
/*10 */                                                       bool is_mmio)                 // (2) 0.1152
/*12 */ {                                                                                   // (16) 0.001953
/*14 */     IOMMUTLBEntry iotlb;                                                            // (9) 0.0293
/*16 */     MemoryRegionSection *section;                                                   // (12) 0.01758
/*18 */     MemoryRegion *mr;                                                               // (13) 0.01563
/*22 */     for (;;) {                                                                      // (14) 0.01563
/*24 */         AddressSpaceDispatch *d = atomic_rcu_read(&as->dispatch);                   // (6) 0.04883
/*26 */         section = address_space_translate_internal(d, addr, &addr, plen, is_mmio);  // (5) 0.06445
/*28 */         mr = section->mr;                                                           // (10) 0.02734
/*32 */         if (!mr->iommu_ops) {                                                       // (8) 0.03516
/*34 */             break;                                                                  // (11) 0.02539
/*36 */         }                                                                           // (15) 0.01562
/*40 */         iotlb = mr->iommu_ops->translate(mr, addr, is_write);                       // 0.0
/*42 */         addr = ((iotlb.translated_addr & ~iotlb.addr_mask)                          // 0.0
/*44 */                 | (addr & iotlb.addr_mask));                                        // 0.0
/*46 */         *plen = MIN(*plen, (addr | iotlb.addr_mask) - addr + 1);                    // 0.0
/*48 */         if (!(iotlb.perm & (1 << is_write))) {                                      // 0.0
/*50 */             goto translate_fail;                                                    // 0.0
/*52 */         }                                                                           // 0.0
/*56 */         as = iotlb.target_as;                                                       // 0.0
/*58 */     }                                                                               // 0.0
/*62 */     *xlat = addr;                                                                   // 0.0
/*66 */     return *section;                                                                // 0.0
/*70 */ translate_fail:                                                                     // 0.0
/*72 */     return (MemoryRegionSection) { .mr = &io_mem_unassigned };                      // 0.0
/*74 */ }                                                                                   // 0.0
