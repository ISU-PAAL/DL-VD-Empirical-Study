// commit message qemu@0360784754 (target=1, prob=0.44685042, correct=False): usb-host: Initialize dev->port the obviously safe way
/*0   */ static int usb_host_open(USBHostDevice *dev, int bus_num,                        // (7) 0.03711
/*2   */                          int addr, const char *port,                             // (1) 0.0625
/*4   */                          const char *prod_name, int speed)                       // (0) 0.06836
/*6   */ {                                                                                // (33) 0.001953
/*8   */     int fd = -1, ret;                                                            // (16) 0.02344
/*12  */     trace_usb_host_open_started(bus_num, addr);                                  // (8) 0.03711
/*16  */     if (dev->fd != -1) {                                                         // (13) 0.02539
/*18  */         goto fail;                                                               // (18) 0.01953
/*20  */     }                                                                            // (27) 0.007812
/*24  */     fd = usb_host_open_device(bus_num, addr);                                    // (6) 0.03906
/*26  */     if (fd < 0) {                                                                // (19) 0.01953
/*28  */         goto fail;                                                               // (20) 0.01953
/*30  */     }                                                                            // (28) 0.007812
/*32  */     DPRINTF("husb: opened %s\n", buf);                                           // (11) 0.03516
/*36  */     dev->bus_num = bus_num;                                                      // (14) 0.02539
/*38  */     dev->addr = addr;                                                            // (24) 0.01758
/*40  */     strcpy(dev->port, port);                                                     // (15) 0.02539
/*42  */     dev->fd = fd;                                                                // (21) 0.01953
/*46  */     /* read the device description */                                            // (23) 0.01758
/*48  */     dev->descr_len = read(fd, dev->descr, sizeof(dev->descr));                   // (2) 0.05078
/*50  */     if (dev->descr_len <= 0) {                                                   // (12) 0.0293
/*52  */         perror("husb: reading device data failed");                              // (10) 0.03516
/*54  */         goto fail;                                                               // (17) 0.01953
/*56  */     }                                                                            // (29) 0.007812
/*60  */ #ifdef DEBUG                                                                     // (26) 0.007813
/*62  */     {                                                                            // (30) 0.007812
/*64  */         int x;                                                                   // (22) 0.01953
/*66  */         printf("=== begin dumping device descriptor data ===\n");                // (9) 0.03711
/*68  */         for (x = 0; x < dev->descr_len; x++) {                                   // (3) 0.04883
/*70  */             printf("%02x ", dev->descr[x]);                                      // (4) 0.04688
/*72  */         }                                                                        // (25) 0.01562
/*74  */         printf("\n=== end dumping device descriptor data ===\n");                // (5) 0.04102
/*76  */     }                                                                            // (31) 0.007812
/*78  */ #endif                                                                           // (32) 0.003906
/*84  */     /* start unconfigured -- we'll wait for the guest to set a configuration */  // 0.0
/*86  */     if (!usb_host_claim_interfaces(dev, 0)) {                                    // 0.0
/*88  */         goto fail;                                                               // 0.0
/*90  */     }                                                                            // 0.0
/*94  */     usb_ep_init(&dev->dev);                                                      // 0.0
/*96  */     usb_linux_update_endp_table(dev);                                            // 0.0
/*100 */     if (speed == -1) {                                                           // 0.0
/*102 */         struct usbdevfs_connectinfo ci;                                          // 0.0
/*106 */         ret = ioctl(fd, USBDEVFS_CONNECTINFO, &ci);                              // 0.0
/*108 */         if (ret < 0) {                                                           // 0.0
/*110 */             perror("usb_host_device_open: USBDEVFS_CONNECTINFO");                // 0.0
/*112 */             goto fail;                                                           // 0.0
/*114 */         }                                                                        // 0.0
/*118 */         if (ci.slow) {                                                           // 0.0
/*120 */             speed = USB_SPEED_LOW;                                               // 0.0
/*122 */         } else {                                                                 // 0.0
/*124 */             speed = USB_SPEED_HIGH;                                              // 0.0
/*126 */         }                                                                        // 0.0
/*128 */     }                                                                            // 0.0
/*130 */     dev->dev.speed = speed;                                                      // 0.0
/*132 */     dev->dev.speedmask = (1 << speed);                                           // 0.0
/*134 */     if (dev->dev.speed == USB_SPEED_HIGH && usb_linux_full_speed_compat(dev)) {  // 0.0
/*136 */         dev->dev.speedmask |= USB_SPEED_MASK_FULL;                               // 0.0
/*138 */     }                                                                            // 0.0
/*142 */     trace_usb_host_open_success(bus_num, addr);                                  // 0.0
/*146 */     if (!prod_name || prod_name[0] == '\0') {                                    // 0.0
/*148 */         snprintf(dev->dev.product_desc, sizeof(dev->dev.product_desc),           // 0.0
/*150 */                  "host:%d.%d", bus_num, addr);                                   // 0.0
/*152 */     } else {                                                                     // 0.0
/*154 */         pstrcpy(dev->dev.product_desc, sizeof(dev->dev.product_desc),            // 0.0
/*156 */                 prod_name);                                                      // 0.0
/*158 */     }                                                                            // 0.0
/*162 */     ret = usb_device_attach(&dev->dev);                                          // 0.0
/*164 */     if (ret) {                                                                   // 0.0
/*166 */         goto fail;                                                               // 0.0
/*168 */     }                                                                            // 0.0
/*172 */     /* USB devio uses 'write' flag to check for async completions */             // 0.0
/*174 */     qemu_set_fd_handler(dev->fd, NULL, async_complete, dev);                     // 0.0
/*178 */     return 0;                                                                    // 0.0
/*182 */ fail:                                                                            // 0.0
/*184 */     trace_usb_host_open_failure(bus_num, addr);                                  // 0.0
/*186 */     if (dev->fd != -1) {                                                         // 0.0
/*188 */         close(dev->fd);                                                          // 0.0
/*190 */         dev->fd = -1;                                                            // 0.0
/*192 */     }                                                                            // 0.0
/*194 */     return -1;                                                                   // 0.0
/*196 */ }                                                                                // 0.0
