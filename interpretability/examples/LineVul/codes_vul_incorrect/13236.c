// commit message qemu@f53c398aa6 (target=1, prob=0.2737706, correct=False): usb: USBPacket: add status, rename owner -> ep
/*0  */ static void ohci_async_cancel_device(OHCIState *ohci, USBDevice *dev)  // (0) 0.1812
/*2  */ {                                                                      // (7) 0.007246
/*4  */     if (ohci->async_td &&                                              // (5) 0.0942
/*6  */         ohci->usb_packet.owner != NULL &&                              // (3) 0.1377
/*8  */         ohci->usb_packet.owner->dev == dev) {                          // (2) 0.1594
/*10 */         usb_cancel_packet(&ohci->usb_packet);                          // (1) 0.1667
/*12 */         ohci->async_td = 0;                                            // (4) 0.1232
/*14 */     }                                                                  // (6) 0.02899
/*16 */ }                                                                      // (8) 0.007246
