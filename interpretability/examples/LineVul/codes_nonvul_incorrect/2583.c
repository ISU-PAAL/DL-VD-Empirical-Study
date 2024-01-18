// commit message qemu@1f3870ab24 (target=0, prob=0.5404342, correct=False): husb: support for USB host device auto disconnect (Max Krasnyansky)
/*0   */ USBDevice *usb_host_device_open(const char *devname)                             // (10) 0.0332
/*2   */ {                                                                                // (33) 0.001953
/*4   */     int fd = -1, ret;                                                            // (14) 0.02344
/*6   */     USBHostDevice *dev = NULL;                                                   // (16) 0.02148
/*8   */     struct usbdevfs_connectinfo ci;                                              // (13) 0.02539
/*10  */     char buf[1024];                                                              // (25) 0.01562
/*12  */     int bus_num, addr;                                                           // (18) 0.01953
/*14  */     char product_name[PRODUCT_NAME_SZ];                                          // (11) 0.03125
/*18  */     dev = qemu_mallocz(sizeof(USBHostDevice));                                   // (6) 0.03906
/*20  */     if (!dev)                                                                    // (27) 0.01367
/*22  */         goto fail;                                                               // (20) 0.01953
/*26  */ #ifdef DEBUG_ISOCH                                                               // (26) 0.01367
/*28  */     printf("usb_host_device_open %s\n", devname);                                // (8) 0.03906
/*30  */ #endif                                                                           // (32) 0.003906
/*32  */     if (usb_host_find_device(&bus_num, &addr,                                    // (7) 0.03906
/*34  */                              product_name, sizeof(product_name),                 // (0) 0.07422
/*36  */                              devname) < 0)                                       // (1) 0.06641
/*38  */         return NULL;                                                             // (23) 0.01953
/*42  */     snprintf(buf, sizeof(buf), USBDEVFS_PATH "/%03d/%03d",                       // (3) 0.05078
/*44  */              bus_num, addr);                                                     // (9) 0.03516
/*46  */     fd = open(buf, O_RDWR | O_NONBLOCK);                                         // (5) 0.04297
/*48  */     if (fd < 0) {                                                                // (21) 0.01953
/*50  */         perror(buf);                                                             // (15) 0.02344
/*52  */         return NULL;                                                             // (22) 0.01953
/*54  */     }                                                                            // (31) 0.007812
/*58  */     /* read the device description */                                            // (24) 0.01758
/*60  */     dev->descr_len = read(fd, dev->descr, sizeof(dev->descr));                   // (2) 0.05078
/*62  */     if (dev->descr_len <= 0) {                                                   // (12) 0.0293
/*64  */         perror("usb_host_device_open: reading device data failed");              // (4) 0.04492
/*66  */         goto fail;                                                               // (19) 0.01953
/*68  */     }                                                                            // (30) 0.007812
/*72  */ #ifdef DEBUG                                                                     // (28) 0.007813
/*74  */     {                                                                            // (29) 0.007813
/*76  */         int x;                                                                   // (17) 0.01953
/*78  */         printf("=== begin dumping device descriptor data ===\n");                // 0.0
/*80  */         for (x = 0; x < dev->descr_len; x++)                                     // 0.0
/*82  */             printf("%02x ", dev->descr[x]);                                      // 0.0
/*84  */         printf("\n=== end dumping device descriptor data ===\n");                // 0.0
/*86  */     }                                                                            // 0.0
/*88  */ #endif                                                                           // 0.0
/*92  */     dev->fd = fd;                                                                // 0.0
/*94  */     dev->configuration = 1;                                                      // 0.0
/*98  */     /* XXX - do something about initial configuration */                         // 0.0
/*100 */     if (!usb_host_update_interfaces(dev, 1))                                     // 0.0
/*102 */         goto fail;                                                               // 0.0
/*106 */     ret = ioctl(fd, USBDEVFS_CONNECTINFO, &ci);                                  // 0.0
/*108 */     if (ret < 0) {                                                               // 0.0
/*110 */         perror("usb_host_device_open: USBDEVFS_CONNECTINFO");                    // 0.0
/*112 */         goto fail;                                                               // 0.0
/*114 */     }                                                                            // 0.0
/*118 */ #ifdef DEBUG                                                                     // 0.0
/*120 */     printf("host USB device %d.%d grabbed\n", bus_num, addr);                    // 0.0
/*122 */ #endif                                                                           // 0.0
/*126 */     ret = usb_linux_update_endp_table(dev);                                      // 0.0
/*128 */     if (ret)                                                                     // 0.0
/*130 */         goto fail;                                                               // 0.0
/*134 */     if (ci.slow)                                                                 // 0.0
/*136 */         dev->dev.speed = USB_SPEED_LOW;                                          // 0.0
/*138 */     else                                                                         // 0.0
/*140 */         dev->dev.speed = USB_SPEED_HIGH;                                         // 0.0
/*142 */     dev->dev.handle_packet = usb_generic_handle_packet;                          // 0.0
/*146 */     dev->dev.handle_reset = usb_host_handle_reset;                               // 0.0
/*148 */     dev->dev.handle_control = usb_host_handle_control;                           // 0.0
/*150 */     dev->dev.handle_data = usb_host_handle_data;                                 // 0.0
/*152 */     dev->dev.handle_destroy = usb_host_handle_destroy;                           // 0.0
/*156 */     if (product_name[0] == '\0')                                                 // 0.0
/*158 */         snprintf(dev->dev.devname, sizeof(dev->dev.devname),                     // 0.0
/*160 */                  "host:%s", devname);                                            // 0.0
/*162 */     else                                                                         // 0.0
/*164 */         pstrcpy(dev->dev.devname, sizeof(dev->dev.devname),                      // 0.0
/*166 */                 product_name);                                                   // 0.0
/*170 */ #ifdef USE_ASYNCIO                                                               // 0.0
/*172 */     /* set up the signal handlers */                                             // 0.0
/*174 */     sigemptyset(&sigact.sa_mask);                                                // 0.0
/*176 */     sigact.sa_sigaction = isoch_done;                                            // 0.0
/*178 */     sigact.sa_flags = SA_SIGINFO;                                                // 0.0
/*180 */     sigact.sa_restorer = 0;                                                      // 0.0
/*182 */     ret = sigaction(SIG_ISOCOMPLETE, &sigact, NULL);                             // 0.0
/*184 */     if (ret < 0) {                                                               // 0.0
/*186 */         perror("usb_host_device_open: sigaction failed");                        // 0.0
/*188 */         goto fail;                                                               // 0.0
/*190 */     }                                                                            // 0.0
/*194 */     if (pipe(dev->pipe_fds) < 0) {                                               // 0.0
/*196 */         perror("usb_host_device_open: pipe creation failed");                    // 0.0
/*198 */         goto fail;                                                               // 0.0
/*200 */     }                                                                            // 0.0
/*202 */     fcntl(dev->pipe_fds[0], F_SETFL, O_NONBLOCK | O_ASYNC);                      // 0.0
/*204 */     fcntl(dev->pipe_fds[1], F_SETFL, O_NONBLOCK);                                // 0.0
/*206 */     qemu_set_fd_handler(dev->pipe_fds[0], urb_completion_pipe_read, NULL, dev);  // 0.0
/*208 */ #endif                                                                           // 0.0
/*210 */     dev->urbs_ready = 0;                                                         // 0.0
/*212 */     return (USBDevice *)dev;                                                     // 0.0
/*214 */ fail:                                                                            // 0.0
/*216 */     if (dev)                                                                     // 0.0
/*218 */         qemu_free(dev);                                                          // 0.0
/*220 */     close(fd);                                                                   // 0.0
/*222 */     return NULL;                                                                 // 0.0
/*224 */ }                                                                                // 0.0
