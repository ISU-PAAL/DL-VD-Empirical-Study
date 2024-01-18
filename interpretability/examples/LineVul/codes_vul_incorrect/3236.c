// commit message qemu@898248a329 (target=1, prob=0.38781998, correct=False): xhci: drop ER_FULL_HACK workaround
/*0  */ static void xhci_reset(DeviceState *dev)                          // (19) 0.02539
/*2  */ {                                                                 // (28) 0.001953
/*4  */     XHCIState *xhci = XHCI(dev);                                  // (13) 0.03516
/*6  */     int i;                                                        // (24) 0.01172
/*10 */     trace_usb_xhci_reset();                                       // (20) 0.02539
/*12 */     if (!(xhci->usbsts & USBSTS_HCH)) {                           // (9) 0.04102
/*14 */         DPRINTF("xhci: reset while running!\n");                  // (6) 0.04297
/*16 */     }                                                             // (26) 0.007812
/*20 */     xhci->usbcmd = 0;                                             // (21) 0.02539
/*22 */     xhci->usbsts = USBSTS_HCH;                                    // (14) 0.0332
/*24 */     xhci->dnctrl = 0;                                             // (22) 0.02344
/*26 */     xhci->crcr_low = 0;                                           // (15) 0.0293
/*28 */     xhci->crcr_high = 0;                                          // (16) 0.0293
/*30 */     xhci->dcbaap_low = 0;                                         // (17) 0.0293
/*32 */     xhci->dcbaap_high = 0;                                        // (18) 0.0293
/*34 */     xhci->config = 0;                                             // (23) 0.02148
/*38 */     for (i = 0; i < xhci->numslots; i++) {                        // (4) 0.04492
/*40 */         xhci_disable_slot(xhci, i+1);                             // (3) 0.04492
/*42 */     }                                                             // (25) 0.007813
/*46 */     for (i = 0; i < xhci->numports; i++) {                        // (10) 0.04102
/*48 */         xhci_port_update(xhci->ports + i, 0);                     // (0) 0.04883
/*50 */     }                                                             // (27) 0.007812
/*54 */     for (i = 0; i < xhci->numintrs; i++) {                        // (7) 0.04297
/*56 */         xhci->intr[i].iman = 0;                                   // (12) 0.03906
/*58 */         xhci->intr[i].imod = 0;                                   // (11) 0.04102
/*60 */         xhci->intr[i].erstsz = 0;                                 // (8) 0.04297
/*62 */         xhci->intr[i].erstba_low = 0;                             // (1) 0.04688
/*64 */         xhci->intr[i].erstba_high = 0;                            // (2) 0.04688
/*66 */         xhci->intr[i].erdp_low = 0;                               // (5) 0.04492
/*68 */         xhci->intr[i].erdp_high = 0;                              // 0.0
/*70 */         xhci->intr[i].msix_used = 0;                              // 0.0
/*74 */         xhci->intr[i].er_ep_idx = 0;                              // 0.0
/*76 */         xhci->intr[i].er_pcs = 1;                                 // 0.0
/*78 */         xhci->intr[i].er_full = 0;                                // 0.0
/*80 */         xhci->intr[i].ev_buffer_put = 0;                          // 0.0
/*82 */         xhci->intr[i].ev_buffer_get = 0;                          // 0.0
/*84 */     }                                                             // 0.0
/*88 */     xhci->mfindex_start = qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL);  // 0.0
/*90 */     xhci_mfwrap_update(xhci);                                     // 0.0
/*92 */ }                                                                 // 0.0
