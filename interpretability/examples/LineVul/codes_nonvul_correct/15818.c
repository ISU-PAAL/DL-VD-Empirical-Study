// commit message qemu@4445b1d27e (target=0, prob=0.18865067, correct=True): spapr: Remove sPAPRConfigureConnectorState sub-structure
/*0  */ static uint32_t drc_isolate_physical(sPAPRDRConnector *drc)             // (3) 0.05044
/*2  */ {                                                                       // (26) 0.002193
/*4  */     switch (drc->state) {                                               // (19) 0.02412
/*6  */     case SPAPR_DRC_STATE_PHYSICAL_POWERON:                              // (8) 0.04605
/*8  */         return RTAS_OUT_SUCCESS; /* Nothing to do */                    // (4) 0.04825
/*10 */     case SPAPR_DRC_STATE_PHYSICAL_CONFIGURED:                           // (5) 0.04825
/*12 */         break; /* see below */                                          // (17) 0.02851
/*14 */     case SPAPR_DRC_STATE_PHYSICAL_UNISOLATE:                            // (6) 0.04825
/*16 */         return RTAS_OUT_PARAM_ERROR; /* not allowed */                  // (7) 0.04825
/*18 */     default:                                                            // (21) 0.01096
/*20 */         g_assert_not_reached();                                         // (13) 0.03509
/*22 */     }                                                                   // (23) 0.008772
/*26 */     /* if the guest is configuring a device attached to this DRC, we    // (11) 0.04167
/*28 */      * should reset the configuration state at this point since it may  // (14) 0.03509
/*30 */      * no longer be reliable (guest released device and needs to start  // (12) 0.03947
/*32 */      * over, or unplug occurred so the FDT is no longer valid)          // (9) 0.04386
/*34 */      */                                                                 // (22) 0.01096
/*36 */     g_free(drc->ccs);                                                   // (18) 0.02851
/*38 */     drc->ccs = NULL;                                                    // (20) 0.02412
/*42 */     drc->state = SPAPR_DRC_STATE_PHYSICAL_POWERON;                      // (2) 0.05482
/*46 */     if (drc->unplug_requested) {                                        // (15) 0.03289
/*48 */         uint32_t drc_index = spapr_drc_index(drc);                      // (1) 0.0614
/*50 */         trace_spapr_drc_set_isolation_state_finalizing(drc_index);      // (0) 0.06798
/*52 */         spapr_drc_detach(drc);                                          // (10) 0.04386
/*54 */     }                                                                   // (24) 0.008772
/*58 */     return RTAS_OUT_SUCCESS;                                            // (16) 0.02851
/*60 */ }                                                                       // (25) 0.002193
