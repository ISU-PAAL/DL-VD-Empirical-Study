// commit message qemu@8991c460be (target=1, prob=0.007855027, correct=False): intel_iommu: relax iq tail check on VTD_GCMD_QIE enable
/*0 */ static inline bool vtd_queued_inv_enable_check(IntelIOMMUState *s)  // (0) 0.5111
/*2 */ {                                                                   // (2) 0.02222
/*4 */     return s->iq_tail == 0;                                         // (1) 0.2667
/*6 */ }                                                                   // (3) 0.02222
