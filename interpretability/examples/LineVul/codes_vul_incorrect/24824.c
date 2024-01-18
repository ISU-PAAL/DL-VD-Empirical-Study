// commit message qemu@a3f409cb4a (target=1, prob=0.0620865, correct=False): intel_iommu: support all masks in interrupt entry cache invalidation
/*0   */ static void vtd_init(IntelIOMMUState *s)                                     // (13) 0.0293
/*2   */ {                                                                            // (24) 0.001953
/*4   */     X86IOMMUState *x86_iommu = X86_IOMMU_DEVICE(s);                          // (3) 0.05664
/*8   */     memset(s->csr, 0, DMAR_REG_SIZE);                                        // (10) 0.03906
/*10  */     memset(s->wmask, 0, DMAR_REG_SIZE);                                      // (11) 0.03906
/*12  */     memset(s->w1cmask, 0, DMAR_REG_SIZE);                                    // (8) 0.04297
/*14  */     memset(s->womask, 0, DMAR_REG_SIZE);                                     // (9) 0.04102
/*18  */     s->iommu_ops.translate = vtd_iommu_translate;                            // (7) 0.04687
/*20  */     s->iommu_ops.notify_started = vtd_iommu_notify_started;                  // (4) 0.05469
/*22  */     s->root = 0;                                                             // (21) 0.01758
/*24  */     s->root_extended = false;                                                // (15) 0.02344
/*26  */     s->dmar_enabled = false;                                                 // (16) 0.02344
/*28  */     s->iq_head = 0;                                                          // (17) 0.02148
/*30  */     s->iq_tail = 0;                                                          // (19) 0.02148
/*32  */     s->iq = 0;                                                               // (22) 0.01758
/*34  */     s->iq_size = 0;                                                          // (20) 0.02148
/*36  */     s->qi_enabled = false;                                                   // (18) 0.02148
/*38  */     s->iq_last_desc_type = VTD_INV_DESC_NONE;                                // (6) 0.04883
/*40  */     s->next_frcd_reg = 0;                                                    // (14) 0.0293
/*42  */     s->cap = VTD_CAP_FRO | VTD_CAP_NFR | VTD_CAP_ND | VTD_CAP_MGAW |         // (1) 0.07617
/*44  */              VTD_CAP_SAGAW | VTD_CAP_MAMV | VTD_CAP_PSI | VTD_CAP_SLLPS;     // (0) 0.0918
/*46  */     s->ecap = VTD_ECAP_QI | VTD_ECAP_IRO;                                    // (5) 0.04883
/*50  */     if (x86_iommu->intr_supported) {                                         // (12) 0.03516
/*52  */         s->ecap |= VTD_ECAP_IR | VTD_ECAP_EIM;                               // (2) 0.05859
/*54  */     }                                                                        // (23) 0.007812
/*58  */     vtd_reset_context_cache(s);                                              // 0.0
/*60  */     vtd_reset_iotlb(s);                                                      // 0.0
/*64  */     /* Define registers with default values and bit semantics */             // 0.0
/*66  */     vtd_define_long(s, DMAR_VER_REG, 0x10UL, 0, 0);                          // 0.0
/*68  */     vtd_define_quad(s, DMAR_CAP_REG, s->cap, 0, 0);                          // 0.0
/*70  */     vtd_define_quad(s, DMAR_ECAP_REG, s->ecap, 0, 0);                        // 0.0
/*72  */     vtd_define_long(s, DMAR_GCMD_REG, 0, 0xff800000UL, 0);                   // 0.0
/*74  */     vtd_define_long_wo(s, DMAR_GCMD_REG, 0xff800000UL);                      // 0.0
/*76  */     vtd_define_long(s, DMAR_GSTS_REG, 0, 0, 0);                              // 0.0
/*78  */     vtd_define_quad(s, DMAR_RTADDR_REG, 0, 0xfffffffffffff000ULL, 0);        // 0.0
/*80  */     vtd_define_quad(s, DMAR_CCMD_REG, 0, 0xe0000003ffffffffULL, 0);          // 0.0
/*82  */     vtd_define_quad_wo(s, DMAR_CCMD_REG, 0x3ffff0000ULL);                    // 0.0
/*86  */     /* Advanced Fault Logging not supported */                               // 0.0
/*88  */     vtd_define_long(s, DMAR_FSTS_REG, 0, 0, 0x11UL);                         // 0.0
/*90  */     vtd_define_long(s, DMAR_FECTL_REG, 0x80000000UL, 0x80000000UL, 0);       // 0.0
/*92  */     vtd_define_long(s, DMAR_FEDATA_REG, 0, 0x0000ffffUL, 0);                 // 0.0
/*94  */     vtd_define_long(s, DMAR_FEADDR_REG, 0, 0xfffffffcUL, 0);                 // 0.0
/*98  */     /* Treated as RsvdZ when EIM in ECAP_REG is not supported                // 0.0
/*100 */      * vtd_define_long(s, DMAR_FEUADDR_REG, 0, 0xffffffffUL, 0);             // 0.0
/*102 */      */                                                                      // 0.0
/*104 */     vtd_define_long(s, DMAR_FEUADDR_REG, 0, 0, 0);                           // 0.0
/*108 */     /* Treated as RO for implementations that PLMR and PHMR fields reported  // 0.0
/*110 */      * as Clear in the CAP_REG.                                              // 0.0
/*112 */      * vtd_define_long(s, DMAR_PMEN_REG, 0, 0x80000000UL, 0);                // 0.0
/*114 */      */                                                                      // 0.0
/*116 */     vtd_define_long(s, DMAR_PMEN_REG, 0, 0, 0);                              // 0.0
/*120 */     vtd_define_quad(s, DMAR_IQH_REG, 0, 0, 0);                               // 0.0
/*122 */     vtd_define_quad(s, DMAR_IQT_REG, 0, 0x7fff0ULL, 0);                      // 0.0
/*124 */     vtd_define_quad(s, DMAR_IQA_REG, 0, 0xfffffffffffff007ULL, 0);           // 0.0
/*126 */     vtd_define_long(s, DMAR_ICS_REG, 0, 0, 0x1UL);                           // 0.0
/*128 */     vtd_define_long(s, DMAR_IECTL_REG, 0x80000000UL, 0x80000000UL, 0);       // 0.0
/*130 */     vtd_define_long(s, DMAR_IEDATA_REG, 0, 0xffffffffUL, 0);                 // 0.0
/*132 */     vtd_define_long(s, DMAR_IEADDR_REG, 0, 0xfffffffcUL, 0);                 // 0.0
/*134 */     /* Treadted as RsvdZ when EIM in ECAP_REG is not supported */            // 0.0
/*136 */     vtd_define_long(s, DMAR_IEUADDR_REG, 0, 0, 0);                           // 0.0
/*140 */     /* IOTLB registers */                                                    // 0.0
/*142 */     vtd_define_quad(s, DMAR_IOTLB_REG, 0, 0Xb003ffff00000000ULL, 0);         // 0.0
/*144 */     vtd_define_quad(s, DMAR_IVA_REG, 0, 0xfffffffffffff07fULL, 0);           // 0.0
/*146 */     vtd_define_quad_wo(s, DMAR_IVA_REG, 0xfffffffffffff07fULL);              // 0.0
/*150 */     /* Fault Recording Registers, 128-bit */                                 // 0.0
/*152 */     vtd_define_quad(s, DMAR_FRCD_REG_0_0, 0, 0, 0);                          // 0.0
/*154 */     vtd_define_quad(s, DMAR_FRCD_REG_0_2, 0, 0, 0x8000000000000000ULL);      // 0.0
/*158 */     /*                                                                       // 0.0
/*160 */      * Interrupt remapping registers.                                        // 0.0
/*162 */      */                                                                      // 0.0
/*164 */     vtd_define_quad(s, DMAR_IRTA_REG, 0, 0xfffffffffffff80fULL, 0);          // 0.0
/*166 */ }                                                                            // 0.0
