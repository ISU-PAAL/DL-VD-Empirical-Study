// commit message qemu@788d2599de (target=1, prob=0.35283014, correct=False): spapr_pci: fix multifunction hotplug
/*0  */ static void spapr_phb_hot_plug_child(HotplugHandler *plug_handler,            // (6) 0.04492
/*2  */                                      DeviceState *plugged_dev, Error **errp)  // (0) 0.0957
/*4  */ {                                                                             // (26) 0.001953
/*6  */     sPAPRPHBState *phb = SPAPR_PCI_HOST_BRIDGE(DEVICE(plug_handler));         // (2) 0.06836
/*8  */     PCIDevice *pdev = PCI_DEVICE(plugged_dev);                                // (7) 0.04102
/*10 */     sPAPRDRConnector *drc = spapr_phb_get_pci_drc(phb, pdev);                 // (3) 0.06641
/*12 */     Error *local_err = NULL;                                                  // (16) 0.02148
/*16 */     /* if DR is disabled we don't need to do anything in the case of          // (8) 0.03711
/*18 */      * hotplug or coldplug callbacks                                          // (15) 0.02344
/*20 */      */                                                                       // (23) 0.009766
/*22 */     if (!phb->dr_enabled) {                                                   // (14) 0.02539
/*24 */         /* if this is a hotplug operation initiated by the user               // (9) 0.03711
/*26 */          * we need to let them know it's not enabled                          // (10) 0.03711
/*28 */          */                                                                   // (19) 0.01758
/*30 */         if (plugged_dev->hotplugged) {                                        // (11) 0.03711
/*32 */             error_setg(errp, QERR_BUS_NO_HOTPLUG,                             // (4) 0.0625
/*34 */                        object_get_typename(OBJECT(phb)));                     // (1) 0.07227
/*36 */         }                                                                     // (22) 0.01562
/*38 */         return;                                                               // (20) 0.01758
/*40 */     }                                                                         // (24) 0.007812
/*44 */     g_assert(drc);                                                            // (17) 0.01953
/*48 */     spapr_phb_add_pci_device(drc, phb, pdev, &local_err);                     // (5) 0.06055
/*50 */     if (local_err) {                                                          // (18) 0.01953
/*52 */         error_propagate(errp, local_err);                                     // (12) 0.03711
/*54 */         return;                                                               // (21) 0.01758
/*56 */     }                                                                         // (25) 0.007812
/*58 */     if (plugged_dev->hotplugged) {                                            // (13) 0.0293
/*60 */         spapr_hotplug_req_add_by_index(drc);                                  // 0.0
/*62 */     }                                                                         // 0.0
/*64 */ }                                                                             // 0.0
