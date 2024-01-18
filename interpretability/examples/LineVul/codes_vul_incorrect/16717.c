// commit message qemu@bd8b92d5c8 (target=1, prob=0.29925475, correct=False): usb: Suppress bogus error when automatic usb-hub creation fails
/*0  */ void usb_claim_port(USBDevice *dev, Error **errp)                                           // (10) 0.0332
/*2  */ {                                                                                           // (25) 0.001953
/*4  */     USBBus *bus = usb_bus_from_device(dev);                                                 // (9) 0.03516
/*6  */     USBPort *port;                                                                          // (19) 0.01562
/*10 */     assert(dev->port == NULL);                                                              // (18) 0.02148
/*14 */     if (dev->port_path) {                                                                   // (17) 0.02344
/*16 */         QTAILQ_FOREACH(port, &bus->free, next) {                                            // (6) 0.04883
/*18 */             if (strcmp(port->path, dev->port_path) == 0) {                                  // (5) 0.05859
/*20 */                 break;                                                                      // (12) 0.0332
/*22 */             }                                                                               // (16) 0.02344
/*24 */         }                                                                                   // (21) 0.01562
/*26 */         if (port == NULL) {                                                                 // (13) 0.02734
/*28 */             error_setg(errp, "usb port %s (bus %s) not found (in use?)",                    // (1) 0.07031
/*30 */                        dev->port_path, bus->qbus.name);                                     // (2) 0.06836
/*32 */             return;                                                                         // (14) 0.02539
/*34 */         }                                                                                   // (22) 0.01562
/*36 */     } else {                                                                                // (24) 0.01172
/*38 */         if (bus->nfree == 1 && strcmp(object_get_typename(OBJECT(dev)), "usb-hub") != 0) {  // (0) 0.08008
/*40 */             /* Create a new hub and chain it on */                                          // (8) 0.04102
/*42 */             usb_create_simple(bus, "usb-hub");                                              // (7) 0.04687
/*44 */         }                                                                                   // (23) 0.01562
/*46 */         if (bus->nfree == 0) {                                                              // (11) 0.0332
/*48 */             error_setg(errp, "tried to attach usb device %s to a bus "                      // (4) 0.0625
/*50 */                        "with no free ports", dev->product_desc);                            // (3) 0.06641
/*52 */             return;                                                                         // (15) 0.02539
/*54 */         }                                                                                   // (20) 0.01562
/*56 */         port = QTAILQ_FIRST(&bus->free);                                                    // 0.0
/*58 */     }                                                                                       // 0.0
/*60 */     trace_usb_port_claim(bus->busnr, port->path);                                           // 0.0
/*64 */     QTAILQ_REMOVE(&bus->free, port, next);                                                  // 0.0
/*66 */     bus->nfree--;                                                                           // 0.0
/*70 */     dev->port = port;                                                                       // 0.0
/*72 */     port->dev = dev;                                                                        // 0.0
/*76 */     QTAILQ_INSERT_TAIL(&bus->used, port, next);                                             // 0.0
/*78 */     bus->nused++;                                                                           // 0.0
/*80 */ }                                                                                           // 0.0
