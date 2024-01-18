// commit message qemu@f5babeacc4 (target=0, prob=0.5401313, correct=False): spapr_drc: use g_strdup_printf() instead of snprintf()
/*0  */ static void realize(DeviceState *d, Error **errp)                            // (15) 0.02734
/*2  */ {                                                                            // (26) 0.001953
/*4  */     sPAPRDRConnector *drc = SPAPR_DR_CONNECTOR(d);                           // (6) 0.04883
/*6  */     Object *root_container;                                                  // (20) 0.01758
/*8  */     char link_name[256];                                                     // (18) 0.01953
/*10 */     gchar *child_name;                                                       // (19) 0.01953
/*12 */     Error *err = NULL;                                                       // (21) 0.01758
/*16 */     trace_spapr_drc_realize(spapr_drc_index(drc));                           // (4) 0.05273
/*18 */     /* NOTE: we do this as part of realize/unrealize due to the fact         // (9) 0.04102
/*20 */      * that the guest will communicate with the DRC via RTAS calls           // (11) 0.03516
/*22 */      * referencing the global DRC index. By unlinking the DRC                // (12) 0.03516
/*24 */      * from DRC_CONTAINER_PATH/<drc_index> we effectively make it            // (7) 0.04883
/*26 */      * inaccessible by the guest, since lookups rely on this path            // (13) 0.0332
/*28 */      * existing in the composition tree                                      // (17) 0.01953
/*30 */      */                                                                      // (24) 0.009766
/*32 */     root_container = container_get(object_get_root(), DRC_CONTAINER_PATH);   // (5) 0.05078
/*34 */     snprintf(link_name, sizeof(link_name), "%x", spapr_drc_index(drc));      // (3) 0.06055
/*36 */     child_name = object_get_canonical_path_component(OBJECT(drc));           // (8) 0.04687
/*38 */     trace_spapr_drc_realize_child(spapr_drc_index(drc), child_name);         // (2) 0.06445
/*40 */     object_property_add_alias(root_container, link_name,                     // (10) 0.03711
/*42 */                               drc->owner, child_name, &err);                 // (0) 0.08008
/*44 */     g_free(child_name);                                                      // (16) 0.02148
/*46 */     if (err) {                                                               // (23) 0.01562
/*48 */         error_propagate(errp, err);                                          // (14) 0.0332
/*50 */         return;                                                              // (22) 0.01758
/*52 */     }                                                                        // (25) 0.007812
/*54 */     vmstate_register(DEVICE(drc), spapr_drc_index(drc), &vmstate_spapr_drc,  // (1) 0.07227
/*56 */                      drc);                                                   // 0.0
/*58 */     qemu_register_reset(drc_reset, drc);                                     // 0.0
/*60 */     trace_spapr_drc_realize_complete(spapr_drc_index(drc));                  // 0.0
/*62 */ }                                                                            // 0.0
