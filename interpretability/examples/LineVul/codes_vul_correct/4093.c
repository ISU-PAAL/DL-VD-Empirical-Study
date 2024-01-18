// commit message qemu@d44168fffa (target=1, prob=0.9990971, correct=True): Fix -usbdevice crash
/*0  */ static USBDevice *usb_net_init(const char *cmdline)         // (7) 0.06504
/*2  */ {                                                           // (14) 0.004065
/*4  */     USBDevice *dev;                                         // (11) 0.03252
/*6  */     QemuOpts *opts;                                         // (8) 0.04878
/*8  */     int idx;                                                // (12) 0.02846
/*12 */     opts = qemu_opts_parse(&qemu_net_opts, cmdline, NULL);  // (0) 0.1179
/*14 */     if (!opts) {                                            // (10) 0.03659
/*18 */     qemu_opt_set(opts, "type", "nic");                      // (4) 0.0813
/*20 */     qemu_opt_set(opts, "model", "usb");                     // (3) 0.0813
/*24 */     idx = net_client_init(NULL, opts, 0);                   // (5) 0.07724
/*26 */     if (idx == -1) {                                        // (9) 0.04878
/*32 */     dev = usb_create(NULL /* FIXME */, "usb-net");          // (2) 0.0813
/*37 */     qdev_set_nic_properties(&dev->qdev, &nd_table[idx]);    // (1) 0.1016
/*39 */     qdev_init_nofail(&dev->qdev);                           // (6) 0.06911
/*41 */     return dev;                                             // (13) 0.02439
