// commit message qemu@7d553f27fc (target=0, prob=0.29357982, correct=True): usb-bus: convert USBDeviceClass init to realize
/*0   */ static int usb_host_open(USBHostDevice *s, libusb_device *dev)                   // (5) 0.04102
/*2   */ {                                                                                // (26) 0.001953
/*4   */     USBDevice *udev = USB_DEVICE(s);                                             // (10) 0.03125
/*6   */     int bus_num = libusb_get_bus_number(dev);                                    // (8) 0.03711
/*8   */     int addr    = libusb_get_device_address(dev);                                // (6) 0.03906
/*10  */     int rc;                                                                      // (23) 0.01172
/*14  */     trace_usb_host_open_started(bus_num, addr);                                  // (7) 0.03711
/*18  */     if (s->dh != NULL) {                                                         // (18) 0.02344
/*20  */         goto fail;                                                               // (20) 0.01953
/*22  */     }                                                                            // (25) 0.007812
/*24  */     rc = libusb_open(dev, &s->dh);                                               // (9) 0.0332
/*26  */     if (rc != 0) {                                                               // (22) 0.01953
/*28  */         goto fail;                                                               // (21) 0.01953
/*30  */     }                                                                            // (24) 0.007812
/*34  */     s->dev     = dev;                                                            // (14) 0.02539
/*36  */     s->bus_num = bus_num;                                                        // (16) 0.02539
/*38  */     s->addr    = addr;                                                           // (19) 0.02344
/*42  */     usb_host_detach_kernel(s);                                                   // (11) 0.02734
/*46  */     libusb_get_device_descriptor(dev, &s->ddesc);                                // (4) 0.04297
/*48  */     usb_host_get_port(s->dev, s->port, sizeof(s->port));                         // (3) 0.04883
/*52  */     usb_ep_init(udev);                                                           // (17) 0.02344
/*54  */     usb_host_ep_update(s);                                                       // (15) 0.02539
/*58  */     udev->speed     = speed_map[libusb_get_device_speed(dev)];                   // (2) 0.05469
/*60  */     usb_host_speed_compat(s);                                                    // (12) 0.02734
/*64  */     if (s->ddesc.iProduct) {                                                     // (13) 0.02734
/*66  */         libusb_get_string_descriptor_ascii(s->dh, s->ddesc.iProduct,             // (1) 0.06641
/*68  */                                            (unsigned char *)udev->product_desc,  // (0) 0.1035
/*70  */                                            sizeof(udev->product_desc));          // 0.0
/*72  */     } else {                                                                     // 0.0
/*74  */         snprintf(udev->product_desc, sizeof(udev->product_desc),                 // 0.0
/*76  */                  "host:%d.%d", bus_num, addr);                                   // 0.0
/*78  */     }                                                                            // 0.0
/*82  */     rc = usb_device_attach(udev);                                                // 0.0
/*84  */     if (rc) {                                                                    // 0.0
/*86  */         goto fail;                                                               // 0.0
/*88  */     }                                                                            // 0.0
/*92  */     trace_usb_host_open_success(bus_num, addr);                                  // 0.0
/*94  */     return 0;                                                                    // 0.0
/*98  */ fail:                                                                            // 0.0
/*100 */     trace_usb_host_open_failure(bus_num, addr);                                  // 0.0
/*102 */     if (s->dh != NULL) {                                                         // 0.0
/*104 */         libusb_close(s->dh);                                                     // 0.0
/*106 */         s->dh = NULL;                                                            // 0.0
/*108 */         s->dev = NULL;                                                           // 0.0
/*110 */     }                                                                            // 0.0
/*112 */     return -1;                                                                   // 0.0
/*114 */ }                                                                                // 0.0
