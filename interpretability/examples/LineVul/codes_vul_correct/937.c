// commit message qemu@ad0ebb91cd (target=1, prob=0.574526, correct=True): pseries: Convert sPAPR TCEs to use generic IOMMU infrastructure
/*0  */ static target_ulong h_put_tce(CPUPPCState *env, sPAPREnvironment *spapr,     // (7) 0.05859
/*2  */                               target_ulong opcode, target_ulong *args)       // (0) 0.08398
/*4  */ {                                                                            // (22) 0.001953
/*6  */     target_ulong liobn = args[0];                                            // (11) 0.0293
/*8  */     target_ulong ioba = args[1];                                             // (14) 0.02734
/*10 */     target_ulong tce = args[2];                                              // (15) 0.02734
/*12 */     VIOsPAPRDevice *dev = spapr_vio_find_by_reg(spapr->vio_bus, liobn);      // (3) 0.07617
/*14 */     VIOsPAPR_RTCE *rtce;                                                     // (10) 0.0332
/*18 */     if (!dev) {                                                              // (17) 0.01562
/*20 */         hcall_dprintf("LIOBN 0x" TARGET_FMT_lx " does not exist\n", liobn);  // (4) 0.07422
/*22 */         return H_PARAMETER;                                                  // (12) 0.0293
/*24 */     }                                                                        // (20) 0.007812
/*28 */     ioba &= ~(SPAPR_VIO_TCE_PAGE_SIZE - 1);                                  // (8) 0.05078
/*32 */ #ifdef DEBUG_TCE                                                             // (18) 0.01367
/*34 */     fprintf(stderr, "spapr_vio_put_tce on %s  ioba 0x" TARGET_FMT_lx         // (2) 0.07617
/*36 */             "  TCE 0x" TARGET_FMT_lx "\n", dev->qdev.id, ioba, tce);         // (1) 0.08203
/*38 */ #endif                                                                       // (21) 0.003906
/*42 */     if (ioba >= dev->rtce_window_size) {                                     // (9) 0.03516
/*44 */         hcall_dprintf("Out-of-bounds IOBA 0x" TARGET_FMT_lx "\n", ioba);     // (5) 0.07422
/*46 */         return H_PARAMETER;                                                  // (13) 0.0293
/*48 */     }                                                                        // (19) 0.007812
/*52 */     rtce = dev->rtce_table + (ioba >> SPAPR_VIO_TCE_PAGE_SHIFT);             // (6) 0.06641
/*54 */     rtce->tce = tce;                                                         // (16) 0.02539
/*58 */     return H_SUCCESS;                                                        // 0.0
/*60 */ }                                                                            // 0.0
