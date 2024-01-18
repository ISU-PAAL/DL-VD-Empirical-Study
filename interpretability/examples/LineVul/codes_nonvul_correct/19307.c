// commit message qemu@ddb603ab6c (target=0, prob=0.42982087, correct=True): xhci: don't kick in xhci_submit and xhci_fire_ctl_transfer
/*0   */ static int xhci_fire_ctl_transfer(XHCIState *xhci, XHCITransfer *xfer)  // (2) 0.05859
/*2   */ {                                                                       // (24) 0.001953
/*4   */     XHCITRB *trb_setup, *trb_status;                                    // (13) 0.03711
/*6   */     uint8_t bmRequestType;                                              // (17) 0.02344
/*10  */     trb_setup = &xfer->trbs[0];                                         // (14) 0.0332
/*12  */     trb_status = &xfer->trbs[xfer->trb_count-1];                        // (7) 0.04883
/*16  */     trace_usb_xhci_xfer_start(xfer, xfer->epctx->slotid,                // (3) 0.05469
/*18  */                               xfer->epctx->epid, xfer->streamid);       // (0) 0.08594
/*22  */     /* at most one Event Data TRB allowed after STATUS */               // (15) 0.03125
/*24  */     if (TRB_TYPE(*trb_status) == TR_EVDATA && xfer->trb_count > 2) {    // (1) 0.06445
/*26  */         trb_status--;                                                   // (16) 0.02539
/*28  */     }                                                                   // (21) 0.007812
/*32  */     /* do some sanity checks */                                         // (20) 0.01758
/*34  */     if (TRB_TYPE(*trb_setup) != TR_SETUP) {                             // (10) 0.04297
/*36  */         DPRINTF("xhci: ep0 first TD not SETUP: %d\n",                   // (4) 0.05469
/*38  */                 TRB_TYPE(*trb_setup));                                  // (8) 0.04883
/*40  */         return -1;                                                      // (18) 0.02148
/*42  */     }                                                                   // (22) 0.007812
/*44  */     if (TRB_TYPE(*trb_status) != TR_STATUS) {                           // (11) 0.04297
/*46  */         DPRINTF("xhci: ep0 last TD not STATUS: %d\n",                   // (5) 0.05469
/*48  */                 TRB_TYPE(*trb_status));                                 // (9) 0.04883
/*50  */         return -1;                                                      // (19) 0.02148
/*52  */     }                                                                   // (23) 0.007812
/*54  */     if (!(trb_setup->control & TRB_TR_IDT)) {                           // (12) 0.04297
/*56  */         DPRINTF("xhci: Setup TRB doesn't have IDT set\n");              // (6) 0.05273
/*58  */         return -1;                                                      // 0.0
/*60  */     }                                                                   // 0.0
/*62  */     if ((trb_setup->status & 0x1ffff) != 8) {                           // 0.0
/*64  */         DPRINTF("xhci: Setup TRB has bad length (%d)\n",                // 0.0
/*66  */                 (trb_setup->status & 0x1ffff));                         // 0.0
/*68  */         return -1;                                                      // 0.0
/*70  */     }                                                                   // 0.0
/*74  */     bmRequestType = trb_setup->parameter;                               // 0.0
/*78  */     xfer->in_xfer = bmRequestType & USB_DIR_IN;                         // 0.0
/*80  */     xfer->iso_xfer = false;                                             // 0.0
/*82  */     xfer->timed_xfer = false;                                           // 0.0
/*86  */     if (xhci_setup_packet(xfer) < 0) {                                  // 0.0
/*88  */         return -1;                                                      // 0.0
/*90  */     }                                                                   // 0.0
/*92  */     xfer->packet.parameter = trb_setup->parameter;                      // 0.0
/*96  */     usb_handle_packet(xfer->packet.ep->dev, &xfer->packet);             // 0.0
/*100 */     xhci_try_complete_packet(xfer);                                     // 0.0
/*102 */     if (!xfer->running_async && !xfer->running_retry) {                 // 0.0
/*104 */         xhci_kick_epctx(xfer->epctx, 0);                                // 0.0
/*106 */     }                                                                   // 0.0
/*108 */     return 0;                                                           // 0.0
/*110 */ }                                                                       // 0.0
