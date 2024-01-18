// commit message qemu@1a20a032cc (target=1, prob=0.5527746, correct=True): usb-bsd: fix a file descriptor leak
/*0   */ USBDevice *usb_host_device_open(const char *devname)                               // (11) 0.0332
/*2   */ {                                                                                  // (31) 0.001953
/*4   */     struct usb_device_info bus_info, dev_info;                                     // (12) 0.0332
/*6   */     USBDevice *d = NULL;                                                           // (19) 0.01953
/*8   */     USBHostDevice *dev;                                                            // (23) 0.01758
/*10  */     char ctlpath[PATH_MAX + 1];                                                    // (15) 0.02734
/*12  */     char buspath[PATH_MAX + 1];                                                    // (16) 0.02539
/*14  */     int bfd, dfd, bus, address, i;                                                 // (13) 0.03125
/*16  */     int ugendebug = UGEN_DEBUG_LEVEL;                                              // (10) 0.03516
/*20  */     if (usb_host_find_device(&bus, &address, devname) < 0)                         // (6) 0.04688
/*22  */         return NULL;                                                               // (22) 0.01953
/*26  */     snprintf(buspath, PATH_MAX, "/dev/usb%d", bus);                                // (7) 0.04297
/*30  */     bfd = open(buspath, O_RDWR);                                                   // (14) 0.03125
/*32  */     if (bfd < 0) {                                                                 // (18) 0.02148
/*34  */ #ifdef DEBUG                                                                       // (26) 0.007812
/*36  */         printf("usb_host_device_open: failed to open usb bus - %s\n",              // (2) 0.05469
/*38  */                strerror(errno));                                                   // (9) 0.04102
/*40  */ #endif                                                                             // (29) 0.003906
/*42  */         return NULL;                                                               // (21) 0.01953
/*44  */     }                                                                              // (27) 0.007812
/*48  */     bus_info.udi_addr = address;                                                   // (17) 0.02539
/*50  */     if (ioctl(bfd, USB_DEVICEINFO, &bus_info) < 0) {                               // (5) 0.05078
/*52  */ #ifdef DEBUG                                                                       // (25) 0.007812
/*54  */         printf("usb_host_device_open: failed to grab bus information - %s\n",      // (3) 0.05469
/*56  */                strerror(errno));                                                   // (8) 0.04102
/*58  */ #endif                                                                             // (28) 0.003906
/*60  */         return NULL;                                                               // (20) 0.01953
/*62  */     }                                                                              // (24) 0.007812
/*66  */ #if defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(__DragonFly__)  // (4) 0.05273
/*68  */     snprintf(ctlpath, PATH_MAX, "/dev/%s", bus_info.udi_devnames[0]);              // (1) 0.05859
/*70  */ #else                                                                              // (30) 0.003906
/*72  */     snprintf(ctlpath, PATH_MAX, "/dev/%s.00", bus_info.udi_devnames[0]);           // (0) 0.0625
/*74  */ #endif                                                                             // 0.0
/*78  */     dfd  = open(ctlpath, O_RDWR);                                                  // 0.0
/*80  */     if (dfd < 0) {                                                                 // 0.0
/*82  */         dfd = open(ctlpath, O_RDONLY);                                             // 0.0
/*84  */         if (dfd < 0) {                                                             // 0.0
/*86  */ #ifdef DEBUG                                                                       // 0.0
/*88  */             printf("usb_host_device_open: failed to open usb device %s - %s\n",    // 0.0
/*90  */                    ctlpath, strerror(errno));                                      // 0.0
/*92  */ #endif                                                                             // 0.0
/*94  */         }                                                                          // 0.0
/*96  */     }                                                                              // 0.0
/*100 */     if (dfd >= 0) {                                                                // 0.0
/*102 */         if (ioctl(dfd, USB_GET_DEVICEINFO, &dev_info) < 0) {                       // 0.0
/*104 */ #ifdef DEBUG                                                                       // 0.0
/*106 */             printf("usb_host_device_open: failed to grab device info - %s\n",      // 0.0
/*108 */                    strerror(errno));                                               // 0.0
/*110 */ #endif                                                                             // 0.0
/*112 */             goto fail;                                                             // 0.0
/*114 */         }                                                                          // 0.0
/*118 */         d = usb_create(NULL /* FIXME */, "usb-host");                              // 0.0
/*120 */         dev = DO_UPCAST(USBHostDevice, dev, d);                                    // 0.0
/*124 */         if (dev_info.udi_speed == 1)                                               // 0.0
/*126 */             dev->dev.speed = USB_SPEED_LOW - 1;                                    // 0.0
/*128 */         else                                                                       // 0.0
/*130 */             dev->dev.speed = USB_SPEED_FULL - 1;                                   // 0.0
/*134 */         if (strncmp(dev_info.udi_product, "product", 7) != 0)                      // 0.0
/*136 */             pstrcpy(dev->dev.product_desc, sizeof(dev->dev.product_desc),          // 0.0
/*138 */                     dev_info.udi_product);                                         // 0.0
/*140 */         else                                                                       // 0.0
/*142 */             snprintf(dev->dev.product_desc, sizeof(dev->dev.product_desc),         // 0.0
/*144 */                      "host:%s", devname);                                          // 0.0
/*148 */         pstrcpy(dev->devpath, sizeof(dev->devpath), "/dev/");                      // 0.0
/*150 */         pstrcat(dev->devpath, sizeof(dev->devpath), dev_info.udi_devnames[0]);     // 0.0
/*154 */         /* Mark the endpoints as not yet open */                                   // 0.0
/*156 */         for (i = 0; i < USB_MAX_ENDPOINTS; i++)                                    // 0.0
/*158 */            dev->ep_fd[i] = -1;                                                     // 0.0
/*162 */         ioctl(dfd, USB_SETDEBUG, &ugendebug);                                      // 0.0
/*166 */         return (USBDevice *)dev;                                                   // 0.0
/*168 */     }                                                                              // 0.0
/*172 */ fail:                                                                              // 0.0
/*174 */     return NULL;                                                                   // 0.0
/*176 */ }                                                                                  // 0.0
