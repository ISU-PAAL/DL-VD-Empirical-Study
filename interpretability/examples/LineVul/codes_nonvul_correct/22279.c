// commit message qemu@079d0b7f1e (target=0, prob=0.10445439, correct=True): usb: Set USBEndpoint in usb_packet_setup().
/*0  */ static int xhci_setup_packet(XHCITransfer *xfer, XHCIPort *port, int ep)  // (3) 0.1099
/*2  */ {                                                                         // (9) 0.003663
/*4  */     usb_packet_setup(&xfer->packet,                                       // (7) 0.05861
/*6  */                      xfer->in_xfer ? USB_TOKEN_IN : USB_TOKEN_OUT,        // (0) 0.1538
/*8  */                      xfer->xhci->slots[xfer->slotid-1].devaddr,           // (1) 0.1502
/*10 */                      ep & 0x7f);                                          // (5) 0.0989
/*12 */     usb_packet_addbuf(&xfer->packet, xfer->data, xfer->data_length);      // (4) 0.1062
/*14 */     DPRINTF("xhci: setup packet pid 0x%x addr %d ep %d\n",                // (6) 0.0989
/*16 */             xfer->packet.pid, xfer->packet.devaddr, xfer->packet.devep);  // (2) 0.1392
/*18 */     return 0;                                                             // (8) 0.02198
/*20 */ }                                                                         // (10) 0.003663
