// commit message qemu@3393bc105d (target=0, prob=0.2743291, correct=True): usb-hub: need to check dev->attached
/*0  */ static int usb_hub_broadcast_packet(USBHubState *s, USBPacket *p)  // (1) 0.09524
/*2  */ {                                                                  // (15) 0.003968
/*4  */     USBHubPort *port;                                              // (10) 0.03571
/*6  */     USBDevice *dev;                                                // (11) 0.03175
/*8  */     int i, ret;                                                    // (12) 0.03175
/*12 */     for(i = 0; i < NUM_PORTS; i++) {                               // (4) 0.0754
/*14 */         port = &s->ports[i];                                       // (6) 0.06349
/*16 */         dev = port->port.dev;                                      // (7) 0.05952
/*18 */         if (dev && (port->wPortStatus & PORT_STAT_ENABLE)) {       // (0) 0.1071
/*20 */             ret = usb_handle_packet(dev, p);                       // (2) 0.09524
/*22 */             if (ret != USB_RET_NODEV) {                            // (3) 0.09524
/*24 */                 return ret;                                        // (5) 0.07143
/*26 */             }                                                      // (8) 0.04762
/*28 */         }                                                          // (13) 0.03175
/*30 */     }                                                              // (14) 0.01587
/*32 */     return USB_RET_NODEV;                                          // (9) 0.04762
/*34 */ }                                                                  // (16) 0.003968
