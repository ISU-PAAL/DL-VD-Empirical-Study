// commit message qemu@37f51384ae (target=0, prob=0.050806243, correct=True): intel-iommu: Extend address width to 48 bits
/*0   */ static bool vtd_do_iommu_translate(VTDAddressSpace *vtd_as, PCIBus *bus,       // (3) 0.05859
/*2   */                                    uint8_t devfn, hwaddr addr, bool is_write,  // (0) 0.09961
/*4   */                                    IOMMUTLBEntry *entry)                       // (1) 0.08789
/*6   */ {                                                                              // (25) 0.001953
/*8   */     IntelIOMMUState *s = vtd_as->iommu_state;                                  // (7) 0.04297
/*10  */     VTDContextEntry ce;                                                        // (18) 0.01758
/*12  */     uint8_t bus_num = pci_bus_num(bus);                                        // (8) 0.03711
/*14  */     VTDContextCacheEntry *cc_entry = &vtd_as->context_cache_entry;             // (6) 0.04883
/*16  */     uint64_t slpte, page_mask;                                                 // (11) 0.0293
/*18  */     uint32_t level;                                                            // (19) 0.01758
/*20  */     uint16_t source_id = vtd_make_source_id(bus_num, devfn);                   // (4) 0.05273
/*22  */     int ret_fr;                                                                // (20) 0.01563
/*24  */     bool is_fpd_set = false;                                                   // (15) 0.02539
/*26  */     bool reads = true;                                                         // (22) 0.01562
/*28  */     bool writes = true;                                                        // (21) 0.01562
/*30  */     uint8_t access_flags;                                                      // (16) 0.02148
/*32  */     VTDIOTLBEntry *iotlb_entry;                                                // (10) 0.03125
/*36  */     /*                                                                         // (24) 0.007812
/*38  */      * We have standalone memory region for interrupt addresses, we            // (13) 0.0293
/*40  */      * should never receive translation requests in this region.               // (14) 0.02734
/*42  */      */                                                                        // (23) 0.009766
/*44  */     assert(!vtd_is_interrupt_addr(addr));                                      // (9) 0.03516
/*48  */     /* Try to fetch slpte form IOTLB */                                        // (12) 0.0293
/*50  */     iotlb_entry = vtd_lookup_iotlb(s, source_id, addr);                        // (5) 0.05078
/*52  */     if (iotlb_entry) {                                                         // (17) 0.02148
/*54  */         trace_vtd_iotlb_page_hit(source_id, addr, iotlb_entry->slpte,          // (2) 0.06836
/*56  */                                  iotlb_entry->domain_id);                      // 0.0
/*58  */         slpte = iotlb_entry->slpte;                                            // 0.0
/*60  */         access_flags = iotlb_entry->access_flags;                              // 0.0
/*62  */         page_mask = iotlb_entry->mask;                                         // 0.0
/*64  */         goto out;                                                              // 0.0
/*66  */     }                                                                          // 0.0
/*70  */     /* Try to fetch context-entry from cache first */                          // 0.0
/*72  */     if (cc_entry->context_cache_gen == s->context_cache_gen) {                 // 0.0
/*74  */         trace_vtd_iotlb_cc_hit(bus_num, devfn, cc_entry->context_entry.hi,     // 0.0
/*76  */                                cc_entry->context_entry.lo,                     // 0.0
/*78  */                                cc_entry->context_cache_gen);                   // 0.0
/*80  */         ce = cc_entry->context_entry;                                          // 0.0
/*82  */         is_fpd_set = ce.lo & VTD_CONTEXT_ENTRY_FPD;                            // 0.0
/*84  */     } else {                                                                   // 0.0
/*86  */         ret_fr = vtd_dev_to_context_entry(s, bus_num, devfn, &ce);             // 0.0
/*88  */         is_fpd_set = ce.lo & VTD_CONTEXT_ENTRY_FPD;                            // 0.0
/*90  */         if (ret_fr) {                                                          // 0.0
/*92  */             ret_fr = -ret_fr;                                                  // 0.0
/*94  */             if (is_fpd_set && vtd_is_qualified_fault(ret_fr)) {                // 0.0
/*96  */                 trace_vtd_fault_disabled();                                    // 0.0
/*98  */             } else {                                                           // 0.0
/*100 */                 vtd_report_dmar_fault(s, source_id, addr, ret_fr, is_write);   // 0.0
/*102 */             }                                                                  // 0.0
/*104 */             goto error;                                                        // 0.0
/*106 */         }                                                                      // 0.0
/*108 */         /* Update context-cache */                                             // 0.0
/*110 */         trace_vtd_iotlb_cc_update(bus_num, devfn, ce.hi, ce.lo,                // 0.0
/*112 */                                   cc_entry->context_cache_gen,                 // 0.0
/*114 */                                   s->context_cache_gen);                       // 0.0
/*116 */         cc_entry->context_entry = ce;                                          // 0.0
/*118 */         cc_entry->context_cache_gen = s->context_cache_gen;                    // 0.0
/*120 */     }                                                                          // 0.0
/*124 */     /*                                                                         // 0.0
/*126 */      * We don't need to translate for pass-through context entries.            // 0.0
/*128 */      * Also, let's ignore IOTLB caching as well for PT devices.                // 0.0
/*130 */      */                                                                        // 0.0
/*132 */     if (vtd_ce_get_type(&ce) == VTD_CONTEXT_TT_PASS_THROUGH) {                 // 0.0
/*134 */         entry->iova = addr & VTD_PAGE_MASK_4K;                                 // 0.0
/*136 */         entry->translated_addr = entry->iova;                                  // 0.0
/*138 */         entry->addr_mask = ~VTD_PAGE_MASK_4K;                                  // 0.0
/*140 */         entry->perm = IOMMU_RW;                                                // 0.0
/*142 */         trace_vtd_translate_pt(source_id, entry->iova);                        // 0.0
/*146 */         /*                                                                     // 0.0
/*148 */          * When this happens, it means firstly caching-mode is not             // 0.0
/*150 */          * enabled, and this is the first passthrough translation for          // 0.0
/*152 */          * the device. Let's enable the fast path for passthrough.             // 0.0
/*154 */          *                                                                     // 0.0
/*156 */          * When passthrough is disabled again for the device, we can           // 0.0
/*158 */          * capture it via the context entry invalidation, then the             // 0.0
/*160 */          * IOMMU region can be swapped back.                                   // 0.0
/*162 */          */                                                                    // 0.0
/*164 */         vtd_pt_enable_fast_path(s, source_id);                                 // 0.0
/*168 */         return true;                                                           // 0.0
/*170 */     }                                                                          // 0.0
/*174 */     ret_fr = vtd_iova_to_slpte(&ce, addr, is_write, &slpte, &level,            // 0.0
/*176 */                                &reads, &writes);                               // 0.0
/*178 */     if (ret_fr) {                                                              // 0.0
/*180 */         ret_fr = -ret_fr;                                                      // 0.0
/*182 */         if (is_fpd_set && vtd_is_qualified_fault(ret_fr)) {                    // 0.0
/*184 */             trace_vtd_fault_disabled();                                        // 0.0
/*186 */         } else {                                                               // 0.0
/*188 */             vtd_report_dmar_fault(s, source_id, addr, ret_fr, is_write);       // 0.0
/*190 */         }                                                                      // 0.0
/*192 */         goto error;                                                            // 0.0
/*194 */     }                                                                          // 0.0
/*198 */     page_mask = vtd_slpt_level_page_mask(level);                               // 0.0
/*200 */     access_flags = IOMMU_ACCESS_FLAG(reads, writes);                           // 0.0
/*202 */     vtd_update_iotlb(s, source_id, VTD_CONTEXT_ENTRY_DID(ce.hi), addr, slpte,  // 0.0
/*204 */                      access_flags, level);                                     // 0.0
/*206 */ out:                                                                           // 0.0
/*208 */     entry->iova = addr & page_mask;                                            // 0.0
/*210 */     entry->translated_addr = vtd_get_slpte_addr(slpte) & page_mask;            // 0.0
/*212 */     entry->addr_mask = ~page_mask;                                             // 0.0
/*214 */     entry->perm = access_flags;                                                // 0.0
/*216 */     return true;                                                               // 0.0
/*220 */ error:                                                                         // 0.0
/*222 */     entry->iova = 0;                                                           // 0.0
/*224 */     entry->translated_addr = 0;                                                // 0.0
/*226 */     entry->addr_mask = 0;                                                      // 0.0
/*228 */     entry->perm = IOMMU_NONE;                                                  // 0.0
/*230 */     return false;                                                              // 0.0
/*232 */ }                                                                              // 0.0
