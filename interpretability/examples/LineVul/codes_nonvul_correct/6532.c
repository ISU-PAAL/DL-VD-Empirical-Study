// commit message qemu@f94d18d6c6 (target=0, prob=0.44567415, correct=True): xhci: only free completed transfers
/*0   */ static void xhci_kick_epctx(XHCIEPContext *epctx, unsigned int streamid)    // (5) 0.04883
/*2   */ {                                                                           // (26) 0.001953
/*4   */     XHCIState *xhci = epctx->xhci;                                          // (11) 0.03711
/*6   */     XHCIStreamContext *stctx;                                               // (17) 0.02344
/*8   */     XHCITransfer *xfer;                                                     // (16) 0.02344
/*10  */     XHCIRing *ring;                                                         // (21) 0.01953
/*12  */     USBEndpoint *ep = NULL;                                                 // (19) 0.02149
/*14  */     uint64_t mfindex;                                                       // (20) 0.02148
/*16  */     int length;                                                             // (23) 0.01172
/*18  */     int i;                                                                  // (24) 0.01172
/*22  */     trace_usb_xhci_ep_kick(epctx->slotid, epctx->epid, streamid);           // (2) 0.05859
/*26  */     /* If the device has been detached, but the guest has not noticed this  // (14) 0.03516
/*28  */        yet the 2 above checks will succeed, but we must NOT continue */     // (10) 0.03906
/*30  */     if (!xhci->slots[epctx->slotid - 1].uport ||                            // (7) 0.04492
/*32  */         !xhci->slots[epctx->slotid - 1].uport->dev ||                       // (4) 0.05469
/*34  */         !xhci->slots[epctx->slotid - 1].uport->dev->attached) {             // (1) 0.0625
/*36  */         return;                                                             // (22) 0.01758
/*38  */     }                                                                       // (25) 0.007812
/*42  */     if (epctx->retry) {                                                     // (18) 0.02344
/*44  */         XHCITransfer *xfer = epctx->retry;                                  // (8) 0.04297
/*48  */         trace_usb_xhci_xfer_retry(xfer);                                    // (6) 0.04687
/*50  */         assert(xfer->running_retry);                                        // (15) 0.0332
/*52  */         if (xfer->timed_xfer) {                                             // (13) 0.03711
/*54  */             /* time to kick the transfer? */                                // (12) 0.03711
/*56  */             mfindex = xhci_mfindex_get(xhci);                               // (3) 0.05664
/*58  */             xhci_check_intr_iso_kick(xhci, xfer, epctx, mfindex);           // (0) 0.07422
/*60  */             if (xfer->running_retry) {                                      // (9) 0.04297
/*62  */                 return;                                                     // 0.0
/*64  */             }                                                               // 0.0
/*66  */             xfer->timed_xfer = 0;                                           // 0.0
/*68  */             xfer->running_retry = 1;                                        // 0.0
/*70  */         }                                                                   // 0.0
/*72  */         if (xfer->iso_xfer) {                                               // 0.0
/*74  */             /* retry iso transfer */                                        // 0.0
/*76  */             if (xhci_setup_packet(xfer) < 0) {                              // 0.0
/*78  */                 return;                                                     // 0.0
/*80  */             }                                                               // 0.0
/*82  */             usb_handle_packet(xfer->packet.ep->dev, &xfer->packet);         // 0.0
/*84  */             assert(xfer->packet.status != USB_RET_NAK);                     // 0.0
/*86  */             xhci_complete_packet(xfer);                                     // 0.0
/*88  */         } else {                                                            // 0.0
/*90  */             /* retry nak'ed transfer */                                     // 0.0
/*92  */             if (xhci_setup_packet(xfer) < 0) {                              // 0.0
/*94  */                 return;                                                     // 0.0
/*96  */             }                                                               // 0.0
/*98  */             usb_handle_packet(xfer->packet.ep->dev, &xfer->packet);         // 0.0
/*100 */             if (xfer->packet.status == USB_RET_NAK) {                       // 0.0
/*102 */                 return;                                                     // 0.0
/*104 */             }                                                               // 0.0
/*106 */             xhci_complete_packet(xfer);                                     // 0.0
/*108 */         }                                                                   // 0.0
/*110 */         assert(!xfer->running_retry);                                       // 0.0
/*112 */         xhci_ep_free_xfer(epctx->retry);                                    // 0.0
/*114 */         epctx->retry = NULL;                                                // 0.0
/*116 */     }                                                                       // 0.0
/*120 */     if (epctx->state == EP_HALTED) {                                        // 0.0
/*122 */         DPRINTF("xhci: ep halted, not running schedule\n");                 // 0.0
/*124 */         return;                                                             // 0.0
/*126 */     }                                                                       // 0.0
/*132 */     if (epctx->nr_pstreams) {                                               // 0.0
/*134 */         uint32_t err;                                                       // 0.0
/*136 */         stctx = xhci_find_stream(epctx, streamid, &err);                    // 0.0
/*138 */         if (stctx == NULL) {                                                // 0.0
/*140 */             return;                                                         // 0.0
/*142 */         }                                                                   // 0.0
/*144 */         ring = &stctx->ring;                                                // 0.0
/*146 */         xhci_set_ep_state(xhci, epctx, stctx, EP_RUNNING);                  // 0.0
/*148 */     } else {                                                                // 0.0
/*150 */         ring = &epctx->ring;                                                // 0.0
/*152 */         streamid = 0;                                                       // 0.0
/*154 */         xhci_set_ep_state(xhci, epctx, NULL, EP_RUNNING);                   // 0.0
/*156 */     }                                                                       // 0.0
/*158 */     assert(ring->dequeue != 0);                                             // 0.0
/*162 */     while (1) {                                                             // 0.0
/*164 */         length = xhci_ring_chain_length(xhci, ring);                        // 0.0
/*166 */         if (length <= 0) {                                                  // 0.0
/*168 */             break;                                                          // 0.0
/*170 */         }                                                                   // 0.0
/*172 */         xfer = xhci_ep_alloc_xfer(epctx, length);                           // 0.0
/*174 */         if (xfer == NULL) {                                                 // 0.0
/*176 */             break;                                                          // 0.0
/*178 */         }                                                                   // 0.0
/*182 */         for (i = 0; i < length; i++) {                                      // 0.0
/*184 */             TRBType type;                                                   // 0.0
/*186 */             type = xhci_ring_fetch(xhci, ring, &xfer->trbs[i], NULL);       // 0.0
/*188 */             assert(type);                                                   // 0.0
/*190 */         }                                                                   // 0.0
/*192 */         xfer->streamid = streamid;                                          // 0.0
/*196 */         if (epctx->epid == 1) {                                             // 0.0
/*198 */             xhci_fire_ctl_transfer(xhci, xfer);                             // 0.0
/*200 */         } else {                                                            // 0.0
/*202 */             xhci_fire_transfer(xhci, xfer, epctx);                          // 0.0
/*204 */         }                                                                   // 0.0
/*206 */         if (xfer->complete) {                                               // 0.0
/*208 */             xhci_ep_free_xfer(xfer);                                        // 0.0
/*210 */             xfer = NULL;                                                    // 0.0
/*212 */         }                                                                   // 0.0
/*216 */         if (epctx->state == EP_HALTED) {                                    // 0.0
/*218 */             break;                                                          // 0.0
/*220 */         }                                                                   // 0.0
/*222 */         if (xfer != NULL && xfer->running_retry) {                          // 0.0
/*224 */             DPRINTF("xhci: xfer nacked, stopping schedule\n");              // 0.0
/*226 */             epctx->retry = xfer;                                            // 0.0
/*228 */             break;                                                          // 0.0
/*230 */         }                                                                   // 0.0
/*232 */     }                                                                       // 0.0
/*236 */     ep = xhci_epid_to_usbep(epctx);                                         // 0.0
/*238 */     if (ep) {                                                               // 0.0
/*240 */         usb_device_flush_ep_queue(ep->dev, ep);                             // 0.0
/*242 */     }                                                                       // 0.0
/*244 */ }                                                                           // 0.0
