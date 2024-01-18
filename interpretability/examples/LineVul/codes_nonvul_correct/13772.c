// commit message qemu@6a81dd172c (target=0, prob=0.07920136, correct=True): spapr_iommu: Rename vfio_accel parameter
/*0  */ sPAPRTCETable *spapr_tce_new_table(DeviceState *owner, uint32_t liobn,  // (4) 0.0625
/*2  */                                    uint64_t bus_offset,                 // (3) 0.08203
/*4  */                                    uint32_t page_shift,                 // (2) 0.08203
/*6  */                                    uint32_t nb_table,                   // (0) 0.08398
/*8  */                                    bool vfio_accel)                     // (1) 0.08203
/*10 */ {                                                                       // (22) 0.001953
/*12 */     sPAPRTCETable *tcet;                                                // (12) 0.02734
/*14 */     char tmp[64];                                                       // (19) 0.01563
/*18 */     if (spapr_tce_find_by_liobn(liobn)) {                               // (8) 0.04883
/*20 */         fprintf(stderr, "Attempted to create TCE table with duplicate"  // (9) 0.04883
/*22 */                 " LIOBN 0x%x\n", liobn);                                // (6) 0.05859
/*24 */         return NULL;                                                    // (17) 0.01953
/*26 */     }                                                                   // (20) 0.007813
/*30 */     if (!nb_table) {                                                    // (16) 0.01953
/*32 */         return NULL;                                                    // (18) 0.01953
/*34 */     }                                                                   // (21) 0.007813
/*38 */     tcet = SPAPR_TCE_TABLE(object_new(TYPE_SPAPR_TCE_TABLE));           // (5) 0.05859
/*40 */     tcet->liobn = liobn;                                                // (15) 0.02734
/*42 */     tcet->bus_offset = bus_offset;                                      // (13) 0.02734
/*44 */     tcet->page_shift = page_shift;                                      // (14) 0.02734
/*46 */     tcet->nb_table = nb_table;                                          // (11) 0.0293
/*48 */     tcet->vfio_accel = vfio_accel;                                      // (10) 0.03906
/*52 */     snprintf(tmp, sizeof(tmp), "tce-table-%x", liobn);                  // (7) 0.04883
/*54 */     object_property_add_child(OBJECT(owner), tmp, OBJECT(tcet), NULL);  // 0.0
/*58 */     object_property_set_bool(OBJECT(tcet), true, "realized", NULL);     // 0.0
/*62 */     return tcet;                                                        // 0.0
/*64 */ }                                                                       // 0.0
