// commit message qemu@d44168fffa (target=1, prob=0.99926645, correct=True): Fix -usbdevice crash
/*0  */ static USBDevice *usb_msd_init(const char *filename)                        // (12) 0.03125
/*2  */ {                                                                           // (30) 0.001953
/*4  */     static int nr=0;                                                        // (19) 0.01953
/*6  */     char id[8];                                                             // (29) 0.01562
/*8  */     QemuOpts *opts;                                                         // (17) 0.02344
/*10 */     DriveInfo *dinfo;                                                       // (20) 0.01758
/*12 */     USBDevice *dev;                                                         // (25) 0.01563
/*14 */     int fatal_error;                                                        // (28) 0.01562
/*16 */     const char *p1;                                                         // (21) 0.01758
/*18 */     char fmt[32];                                                           // (27) 0.01562
/*22 */     /* parse -usbdevice disk: syntax into drive opts */                     // (13) 0.03125
/*24 */     snprintf(id, sizeof(id), "usb%d", nr++);                                // (6) 0.04102
/*26 */     opts = qemu_opts_create(&qemu_drive_opts, id, 0);                       // (1) 0.05469
/*30 */     p1 = strchr(filename, ':');                                             // (15) 0.0293
/*32 */     if (p1++) {                                                             // (24) 0.01758
/*34 */         const char *p2;                                                     // (16) 0.02539
/*38 */         if (strstart(filename, "format=", &p2)) {                           // (5) 0.04492
/*40 */             int len = MIN(p1 - p2, sizeof(fmt));                            // (2) 0.05273
/*42 */             pstrcpy(fmt, len, p2);                                          // (4) 0.04687
/*44 */             qemu_opt_set(opts, "format", fmt);                              // (3) 0.05273
/*46 */         } else if (*filename != ':') {                                      // (11) 0.0332
/*48 */             printf("unrecognized USB mass-storage option %s\n", filename);  // (0) 0.05469
/*52 */         filename = p1;                                                      // (18) 0.02344
/*55 */     if (!*filename) {                                                       // (22) 0.01758
/*57 */         printf("block device specification needed\n");                      // (14) 0.03125
/*61 */     qemu_opt_set(opts, "file", filename);                                   // (10) 0.03711
/*63 */     qemu_opt_set(opts, "if", "none");                                       // (8) 0.03906
/*67 */     /* create host drive */                                                 // (26) 0.01563
/*69 */     dinfo = drive_init(opts, NULL, &fatal_error);                           // (7) 0.04102
/*71 */     if (!dinfo) {                                                           // (23) 0.01758
/*73 */         qemu_opts_del(opts);                                                // (9) 0.03711
/*79 */     /* create guest device */                                               // 0.0
/*81 */     dev = usb_create(NULL /* FIXME */, "usb-storage");                      // 0.0
/*86 */     qdev_prop_set_drive(&dev->qdev, "drive", dinfo);                        // 0.0
/*88 */     if (qdev_init(&dev->qdev) < 0)                                          // 0.0
/*93 */     return dev;                                                             // 0.0
