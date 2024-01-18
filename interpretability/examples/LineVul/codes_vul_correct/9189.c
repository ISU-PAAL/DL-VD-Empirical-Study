// commit message qemu@b21da4e504 (target=1, prob=0.9989502, correct=True): xhci: Fix memory leak on xhci_disable_ep
/*0  */ static TRBCCode xhci_disable_ep(XHCIState *xhci, unsigned int slotid,     // (3) 0.06566
/*1  */                                unsigned int epid)                         // (0) 0.08586
/*2  */ {                                                                         // (21) 0.002525
/*3  */     XHCISlot *slot;                                                       // (17) 0.02525
/*4  */     XHCIEPContext *epctx;                                                 // (16) 0.0303
/*5  */     int i;                                                                // (20) 0.01515
/*6  */     trace_usb_xhci_ep_disable(slotid, epid);                              // (6) 0.05051
/*7  */     assert(slotid >= 1 && slotid <= xhci->numslots);                      // (5) 0.05556
/*8  */     assert(epid >= 1 && epid <= 31);                                      // (13) 0.03535
/*9  */     slot = &xhci->slots[slotid-1];                                        // (8) 0.04545
/*10 */     if (!slot->eps[epid-1]) {                                             // (9) 0.03788
/*11 */         DPRINTF("xhci: slot %d ep %d already disabled\n", slotid, epid);  // (1) 0.07828
/*12 */         return CC_SUCCESS;                                                // (14) 0.03535
/*13 */     xhci_ep_nuke_xfers(xhci, slotid, epid);                               // (4) 0.06061
/*14 */     epctx = slot->eps[epid-1];                                            // (10) 0.03788
/*15 */     if (epctx->nr_pstreams) {                                             // (11) 0.03788
/*16 */         xhci_free_streams(epctx);                                         // (7) 0.04798
/*17 */     xhci_set_ep_state(xhci, epctx, NULL, EP_DISABLED);                    // (2) 0.07071
/*18 */     timer_free(epctx->kick_timer);                                        // (15) 0.03535
/*19 */     g_free(epctx);                                                        // (18) 0.02525
/*20 */     slot->eps[epid-1] = NULL;                                             // (12) 0.03788
/*21 */     return CC_SUCCESS;                                                    // (19) 0.02525
