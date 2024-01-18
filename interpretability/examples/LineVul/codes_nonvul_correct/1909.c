// commit message qemu@ee9a569ab8 (target=0, prob=0.0065671722, correct=True): spapr_vio/spapr_iommu: Move VIO bypass where it belongs
/*0 */ void spapr_tce_set_bypass(sPAPRTCETable *tcet, bool bypass)  // (0) 0.5625
/*2 */ {                                                            // (2) 0.02083
/*4 */     tcet->bypass = bypass;                                   // (1) 0.2292
/*6 */ }                                                            // (3) 0.02083
