// commit message qemu@68d553587c (target=0, prob=0.7931164, correct=False): usb-ehci: Use PCI DMA stub functions
/*0   */ static int ehci_process_itd(EHCIState *ehci,                                       // (14) 0.0358
/*2   */                             EHCIitd *itd)                                          // (1) 0.07046
/*4   */ {                                                                                  // (19) 0.002016
/*6   */     USBPort *port;                                                                 // (16) 0.0165
/*8   */     USBDevice *dev;                                                                // (17) 0.016
/*10  */     int ret;                                                                       // (18) 0.01171
/*12  */     uint32_t i, j, len, pid, dir, devaddr, endp;                                   // (12) 0.045
/*14  */     uint32_t pg, off, ptr1, ptr2, max, mult;                                       // (13) 0.04097
/*18  */     dir =(itd->bufptr[1] & ITD_BUFPTR_DIRECTION);                                  // (11) 0.0506
/*20  */     devaddr = get_field(itd->bufptr[0], ITD_BUFPTR_DEVADDR);                       // (6) 0.05645
/*22  */     endp = get_field(itd->bufptr[0], ITD_BUFPTR_EP);                               // (10) 0.05255
/*24  */     max = get_field(itd->bufptr[1], ITD_BUFPTR_MAXPKT);                            // (7) 0.05448
/*26  */     mult = get_field(itd->bufptr[2], ITD_BUFPTR_MULT);                             // (9) 0.05256
/*30  */     for(i = 0; i < 8; i++) {                                                       // (15) 0.0314
/*32  */         if (itd->transact[i] & ITD_XACT_ACTIVE) {                                  // (8) 0.05446
/*34  */             pg   = get_field(itd->transact[i], ITD_XACT_PGSEL);                    // (0) 0.07198
/*36  */             off  = itd->transact[i] & ITD_XACT_OFFSET_MASK;                        // (3) 0.06808
/*38  */             ptr1 = (itd->bufptr[pg] & ITD_BUFPTR_MASK);                            // (5) 0.06618
/*40  */             ptr2 = (itd->bufptr[pg+1] & ITD_BUFPTR_MASK);                          // (2) 0.07004
/*42  */             len  = get_field(itd->transact[i], ITD_XACT_LENGTH);                   // (4) 0.06807
/*46  */             if (len > max * mult) {                                                // 0.0
/*48  */                 len = max * mult;                                                  // 0.0
/*50  */             }                                                                      // 0.0
/*54  */             if (len > BUFF_SIZE) {                                                 // 0.0
/*56  */                 return USB_RET_PROCERR;                                            // 0.0
/*58  */             }                                                                      // 0.0
/*62  */             qemu_sglist_init(&ehci->isgl, 2);                                      // 0.0
/*64  */             if (off + len > 4096) {                                                // 0.0
/*66  */                 /* transfer crosses page border */                                 // 0.0
/*68  */                 uint32_t len2 = off + len - 4096;                                  // 0.0
/*70  */                 uint32_t len1 = len - len2;                                        // 0.0
/*72  */                 qemu_sglist_add(&ehci->isgl, ptr1 + off, len1);                    // 0.0
/*74  */                 qemu_sglist_add(&ehci->isgl, ptr2, len2);                          // 0.0
/*76  */             } else {                                                               // 0.0
/*78  */                 qemu_sglist_add(&ehci->isgl, ptr1 + off, len);                     // 0.0
/*80  */             }                                                                      // 0.0
/*84  */             pid = dir ? USB_TOKEN_IN : USB_TOKEN_OUT;                              // 0.0
/*88  */             usb_packet_setup(&ehci->ipacket, pid, devaddr, endp);                  // 0.0
/*90  */             usb_packet_map(&ehci->ipacket, &ehci->isgl);                           // 0.0
/*94  */             ret = USB_RET_NODEV;                                                   // 0.0
/*96  */             for (j = 0; j < NB_PORTS; j++) {                                       // 0.0
/*98  */                 port = &ehci->ports[j];                                            // 0.0
/*100 */                 dev = port->dev;                                                   // 0.0
/*104 */                 if (!(ehci->portsc[j] &(PORTSC_CONNECT))) {                        // 0.0
/*106 */                     continue;                                                      // 0.0
/*108 */                 }                                                                  // 0.0
/*112 */                 ret = usb_handle_packet(dev, &ehci->ipacket);                      // 0.0
/*116 */                 if (ret != USB_RET_NODEV) {                                        // 0.0
/*118 */                     break;                                                         // 0.0
/*120 */                 }                                                                  // 0.0
/*122 */             }                                                                      // 0.0
/*126 */             usb_packet_unmap(&ehci->ipacket);                                      // 0.0
/*128 */             qemu_sglist_destroy(&ehci->isgl);                                      // 0.0
/*132 */ #if 0                                                                              // 0.0
/*134 */             /*  In isoch, there is no facility to indicate a NAK so let's          // 0.0
/*136 */              *  instead just complete a zero-byte transaction.  Setting            // 0.0
/*138 */              *  DBERR seems too draconian.                                         // 0.0
/*140 */              */                                                                    // 0.0
/*144 */             if (ret == USB_RET_NAK) {                                              // 0.0
/*146 */                 if (ehci->isoch_pause > 0) {                                       // 0.0
/*148 */                     DPRINTF("ISOCH: received a NAK but paused so returning\n");    // 0.0
/*150 */                     ehci->isoch_pause--;                                           // 0.0
/*152 */                     return 0;                                                      // 0.0
/*154 */                 } else if (ehci->isoch_pause == -1) {                              // 0.0
/*156 */                     DPRINTF("ISOCH: recv NAK & isoch pause inactive, setting\n");  // 0.0
/*158 */                     // Pause frindex for up to 50 msec waiting for data from       // 0.0
/*160 */                     // remote                                                      // 0.0
/*162 */                     ehci->isoch_pause = 50;                                        // 0.0
/*164 */                     return 0;                                                      // 0.0
/*166 */                 } else {                                                           // 0.0
/*168 */                     DPRINTF("ISOCH: isoch pause timeout! return 0\n");             // 0.0
/*170 */                     ret = 0;                                                       // 0.0
/*172 */                 }                                                                  // 0.0
/*174 */             } else {                                                               // 0.0
/*176 */                 DPRINTF("ISOCH: received ACK, clearing pause\n");                  // 0.0
/*178 */                 ehci->isoch_pause = -1;                                            // 0.0
/*180 */             }                                                                      // 0.0
/*182 */ #else                                                                              // 0.0
/*184 */             if (ret == USB_RET_NAK) {                                              // 0.0
/*186 */                 ret = 0;                                                           // 0.0
/*188 */             }                                                                      // 0.0
/*190 */ #endif                                                                             // 0.0
/*194 */             if (ret >= 0) {                                                        // 0.0
/*196 */                 if (!dir) {                                                        // 0.0
/*198 */                     /* OUT */                                                      // 0.0
/*200 */                     set_field(&itd->transact[i], len - ret, ITD_XACT_LENGTH);      // 0.0
/*202 */                 } else {                                                           // 0.0
/*204 */                     /* IN */                                                       // 0.0
/*206 */                     set_field(&itd->transact[i], ret, ITD_XACT_LENGTH);            // 0.0
/*208 */                 }                                                                  // 0.0
/*212 */                 if (itd->transact[i] & ITD_XACT_IOC) {                             // 0.0
/*214 */                     ehci_record_interrupt(ehci, USBSTS_INT);                       // 0.0
/*216 */                 }                                                                  // 0.0
/*218 */             }                                                                      // 0.0
/*220 */             itd->transact[i] &= ~ITD_XACT_ACTIVE;                                  // 0.0
/*222 */         }                                                                          // 0.0
/*224 */     }                                                                              // 0.0
/*226 */     return 0;                                                                      // 0.0
/*228 */ }                                                                                  // 0.0
