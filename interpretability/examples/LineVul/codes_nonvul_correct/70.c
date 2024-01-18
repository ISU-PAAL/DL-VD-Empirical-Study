// commit message qemu@f1c52354e5 (target=0, prob=0.009590597, correct=True): spapr: Cleanups relating to DRC awaiting_release field
/*0  */ static uint32_t drc_set_unusable(sPAPRDRConnector *drc)              // (3) 0.1299
/*2  */ {                                                                    // (8) 0.00565
/*4  */     drc->allocation_state = SPAPR_DR_ALLOCATION_STATE_UNUSABLE;      // (2) 0.1525
/*6  */     if (drc->awaiting_release) {                                     // (5) 0.0791
/*8  */         uint32_t drc_index = spapr_drc_index(drc);                   // (1) 0.1582
/*10 */         trace_spapr_drc_set_allocation_state_finalizing(drc_index);  // (0) 0.1751
/*12 */         spapr_drc_detach(drc);                                       // (4) 0.113
/*14 */     }                                                                // (7) 0.0226
/*18 */     return RTAS_OUT_SUCCESS;                                         // (6) 0.07345
/*20 */ }                                                                    // (9) 0.00565
