// commit message qemu@72cf2d4f0e (target=0, prob=0.008605552, correct=True): Fix sys-queue.h conflict for good
/*0  */ int usb_device_delete_addr(int busnr, int addr)  // (4) 0.05839
/*2  */ {                                                // (21) 0.00365
/*4  */     USBBus *bus;                                 // (15) 0.0292
/*6  */     USBPort *port;                               // (14) 0.0292
/*8  */     USBDevice *dev;                              // (13) 0.0292
/*12 */     bus = usb_bus_find(busnr);                   // (5) 0.05109
/*14 */     if (!bus)                                    // (17) 0.02555
/*16 */         return -1;                               // (9) 0.04015
/*20 */     TAILQ_FOREACH(port, &bus->used, next) {      // (1) 0.07299
/*22 */         if (port->dev->addr == addr)             // (3) 0.06204
/*24 */             break;                               // (6) 0.04745
/*26 */     }                                            // (20) 0.0146
/*28 */     if (!port)                                   // (18) 0.02555
/*30 */         return -1;                               // (10) 0.04015
/*34 */     dev = port->dev;                             // (12) 0.03285
/*36 */     TAILQ_REMOVE(&bus->used, port, next);        // (2) 0.06934
/*38 */     bus->nused--;                                // (11) 0.03285
/*42 */     usb_attach(port, NULL);                      // (8) 0.04015
/*44 */     dev->info->handle_destroy(dev);              // (7) 0.04745
/*48 */     TAILQ_INSERT_TAIL(&bus->free, port, next);   // (0) 0.07664
/*50 */     bus->nfree++;                                // (16) 0.0292
/*52 */     return 0;                                    // (19) 0.0219
/*54 */ }                                                // (22) 0.00365
