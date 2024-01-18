// commit message qemu@d78c19b5cf (target=0, prob=0.077513635, correct=True): memory: Fix IOMMU replay base address
/*0  */ static target_ulong put_tce_emu(sPAPRTCETable *tcet, target_ulong ioba,   // (3) 0.07673
/*2  */                                 target_ulong tce)                         // (0) 0.09406
/*4  */ {                                                                         // (18) 0.002475
/*6  */     IOMMUTLBEntry entry;                                                  // (15) 0.03218
/*8  */     hwaddr page_mask = IOMMU_PAGE_MASK(tcet->page_shift);                 // (4) 0.06683
/*10 */     unsigned long index = (ioba - tcet->bus_offset) >> tcet->page_shift;  // (5) 0.06436
/*14 */     if (index >= tcet->nb_table) {                                        // (10) 0.03713
/*16 */         hcall_dprintf("spapr_vio_put_tce on out-of-bounds IOBA 0x"        // (1) 0.08911
/*18 */                       TARGET_FMT_lx "\n", ioba);                          // (2) 0.08663
/*20 */         return H_PARAMETER;                                               // (11) 0.03713
/*22 */     }                                                                     // (17) 0.009901
/*26 */     tcet->table[index] = tce;                                             // (13) 0.03465
/*30 */     entry.target_as = &address_space_memory,                              // (9) 0.0396
/*32 */     entry.iova = ioba & page_mask;                                        // (12) 0.03713
/*34 */     entry.translated_addr = tce & page_mask;                              // (8) 0.04208
/*36 */     entry.addr_mask = ~page_mask;                                         // (14) 0.03465
/*38 */     entry.perm = spapr_tce_iommu_access_flags(tce);                       // (6) 0.06188
/*40 */     memory_region_notify_iommu(&tcet->iommu, entry);                      // (7) 0.05693
/*44 */     return H_SUCCESS;                                                     // (16) 0.02475
/*46 */ }                                                                         // (19) 0.002475
