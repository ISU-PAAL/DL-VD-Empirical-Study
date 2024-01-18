// commit message qemu@4f9242fc93 (target=0, prob=0.3728168, correct=True): spapr: Make DRC reset force DRC into known state
/*0  */ static void reset(DeviceState *d)                                                 // (21) 0.01758
/*2  */ {                                                                                 // (25) 0.001953
/*4  */     sPAPRDRConnector *drc = SPAPR_DR_CONNECTOR(d);                                // (5) 0.04883
/*6  */     sPAPRDRConnectorClass *drck = SPAPR_DR_CONNECTOR_GET_CLASS(drc);              // (3) 0.06055
/*10 */     trace_spapr_drc_reset(spapr_drc_index(drc));                                  // (4) 0.05078
/*14 */     g_free(drc->ccs);                                                             // (18) 0.02539
/*16 */     drc->ccs = NULL;                                                              // (19) 0.02148
/*20 */     /* immediately upon reset we can safely assume DRCs whose devices             // (15) 0.03125
/*22 */      * are pending removal can be safely removed, and that they will              // (13) 0.0332
/*24 */      * subsequently be left in an ISOLATED state. move the DRC to this            // (9) 0.04102
/*26 */      * state in these cases (which will in turn complete any pending              // (14) 0.0332
/*28 */      * device removals)                                                           // (20) 0.01953
/*30 */      */                                                                           // (24) 0.009766
/*32 */     if (drc->awaiting_release) {                                                  // (16) 0.02734
/*34 */         drck->set_isolation_state(drc, SPAPR_DR_ISOLATION_STATE_ISOLATED);        // (1) 0.07031
/*36 */         /* generally this should also finalize the removal, but if the device     // (8) 0.04102
/*38 */          * hasn't yet been configured we normally defer removal under the         // (11) 0.03906
/*40 */          * assumption that this transition is taking place as part of device      // (10) 0.03906
/*42 */          * configuration. so check if we're still waiting after this, and         // (7) 0.04297
/*44 */          * force removal if we are                                                // (17) 0.02734
/*46 */          */                                                                       // (22) 0.01758
/*48 */         if (drc->awaiting_release) {                                              // (12) 0.03516
/*50 */             spapr_drc_detach(drc, DEVICE(drc->dev), NULL);                        // (2) 0.06641
/*52 */         }                                                                         // (23) 0.01562
/*56 */         /* non-PCI devices may be awaiting a transition to UNUSABLE */            // (6) 0.04492
/*58 */         if (spapr_drc_type(drc) != SPAPR_DR_CONNECTOR_TYPE_PCI &&                 // (0) 0.07227
/*60 */             drc->awaiting_release) {                                              // 0.0
/*62 */             drck->set_allocation_state(drc, SPAPR_DR_ALLOCATION_STATE_UNUSABLE);  // 0.0
/*64 */         }                                                                         // 0.0
/*66 */     }                                                                             // 0.0
/*68 */ }                                                                                 // 0.0
