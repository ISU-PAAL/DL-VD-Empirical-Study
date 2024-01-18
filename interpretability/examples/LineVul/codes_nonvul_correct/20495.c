// commit message qemu@37f51384ae (target=0, prob=0.043521244, correct=True): intel-iommu: Extend address width to 48 bits
/*0  */ static void vtd_iommu_replay(IOMMUMemoryRegion *iommu_mr, IOMMUNotifier *n)    // (6) 0.06641
/*2  */ {                                                                              // (18) 0.001953
/*4  */     VTDAddressSpace *vtd_as = container_of(iommu_mr, VTDAddressSpace, iommu);  // (7) 0.0625
/*6  */     IntelIOMMUState *s = vtd_as->iommu_state;                                  // (9) 0.04297
/*8  */     uint8_t bus_n = pci_bus_num(vtd_as->bus);                                  // (8) 0.04688
/*10 */     VTDContextEntry ce;                                                        // (14) 0.01758
/*14 */     /*                                                                         // (17) 0.007812
/*16 */      * The replay can be triggered by either a invalidation or a newly         // (11) 0.03516
/*18 */      * created entry. No matter what, we release existing mappings             // (13) 0.0332
/*20 */      * (it means flushing caches for UNMAP-only registers).                    // (12) 0.03516
/*22 */      */                                                                        // (16) 0.009766
/*24 */     vtd_address_space_unmap(vtd_as, n);                                        // (10) 0.03906
/*28 */     if (vtd_dev_to_context_entry(s, bus_n, vtd_as->devfn, &ce) == 0) {         // (3) 0.07227
/*30 */         trace_vtd_replay_ce_valid(bus_n, PCI_SLOT(vtd_as->devfn),              // (5) 0.07031
/*32 */                                   PCI_FUNC(vtd_as->devfn),                     // (1) 0.08984
/*34 */                                   VTD_CONTEXT_ENTRY_DID(ce.hi),                // (0) 0.0957
/*36 */                                   ce.hi, ce.lo);                               // (2) 0.08008
/*38 */         vtd_page_walk(&ce, 0, ~0ULL, vtd_replay_hook, (void *)n, false);       // (4) 0.07227
/*40 */     } else {                                                                   // (15) 0.01172
/*42 */         trace_vtd_replay_ce_invalid(bus_n, PCI_SLOT(vtd_as->devfn),            // 0.0
/*44 */                                     PCI_FUNC(vtd_as->devfn));                  // 0.0
/*46 */     }                                                                          // 0.0
/*50 */     return;                                                                    // 0.0
/*52 */ }                                                                              // 0.0
