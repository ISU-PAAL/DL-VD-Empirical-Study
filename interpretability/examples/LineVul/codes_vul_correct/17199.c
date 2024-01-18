// commit message qemu@d3aea641a4 (target=1, prob=0.9990859, correct=True): usbredir: Verify we have 32 bits bulk length cap when redirecting to xhci
/*0  */ static void usbredir_do_attach(void *opaque)                                    // (9) 0.04673
/*2  */ {                                                                               // (14) 0.003115
/*4  */     USBRedirDevice *dev = opaque;                                               // (10) 0.03738
/*8  */     /* In order to work properly with XHCI controllers we need these caps */    // (5) 0.05919
/*10 */     if ((dev->dev.port->speedmask & USB_SPEED_MASK_SUPER) && !(                 // (2) 0.08723
/*13 */                                     usb_redir_cap_ep_info_max_packet_size) &&   // (0) 0.1682
/*18 */                                     usb_redir_cap_64bits_ids))) {               // (1) 0.1495
/*20 */         ERROR("usb-redir-host lacks capabilities needed for use with XHCI\n");  // (3) 0.08411
/*22 */         usbredir_reject_device(dev);                                            // (8) 0.05607
/*24 */         return;                                                                 // (11) 0.02804
/*26 */     }                                                                           // (13) 0.01246
/*30 */     if (usb_device_attach(&dev->dev) != 0) {                                    // (6) 0.05919
/*32 */         WARNING("rejecting device due to speed mismatch\n");                    // (4) 0.06231
/*34 */         usbredir_reject_device(dev);                                            // (7) 0.05607
/*36 */     }                                                                           // (12) 0.01246
/*38 */ }                                                                               // (15) 0.003115
