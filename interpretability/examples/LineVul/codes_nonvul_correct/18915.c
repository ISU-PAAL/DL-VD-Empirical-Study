// commit message qemu@bb5fc20f7c (target=0, prob=0.3399939, correct=True): monitor: Rework modal password input (Jan Kiszka)
/*0   */ static int usb_device_add(const char *devname, int is_hotplug)            // (6) 0.03906
/*2   */ {                                                                         // (28) 0.001953
/*4   */     const char *p;                                                        // (26) 0.01563
/*6   */     USBDevice *dev;                                                       // (25) 0.01563
/*10  */     if (!free_usb_ports)                                                  // (22) 0.02148
/*12  */         return -1;                                                        // (23) 0.02148
/*16  */     if (strstart(devname, "host:", &p)) {                                 // (9) 0.03711
/*18  */         dev = usb_host_device_open(p);                                    // (8) 0.03711
/*20  */     } else if (!strcmp(devname, "mouse")) {                               // (14) 0.0332
/*22  */         dev = usb_mouse_init();                                           // (18) 0.0293
/*24  */     } else if (!strcmp(devname, "tablet")) {                              // (12) 0.03516
/*26  */         dev = usb_tablet_init();                                          // (17) 0.03125
/*28  */     } else if (!strcmp(devname, "keyboard")) {                            // (11) 0.03516
/*30  */         dev = usb_keyboard_init();                                        // (16) 0.03125
/*32  */     } else if (strstart(devname, "disk:", &p)) {                          // (4) 0.04102
/*34  */         BlockDriverState *bs;                                             // (20) 0.02539
/*38  */         dev = usb_msd_init(p, &bs);                                       // (5) 0.04102
/*40  */         if (!dev)                                                         // (24) 0.02148
/*42  */             return -1;                                                    // (19) 0.0293
/*44  */         if (bdrv_key_required(bs)) {                                      // (7) 0.03906
/*46  */             autostart = 0;                                                // (15) 0.0332
/*48  */             if (is_hotplug && monitor_read_bdrv_key(bs) < 0) {            // (0) 0.06641
/*50  */                 dev->handle_destroy(dev);                                 // (1) 0.04492
/*52  */                 return -1;                                                // (10) 0.03711
/*54  */             }                                                             // (21) 0.02344
/*56  */         }                                                                 // (27) 0.01562
/*58  */     } else if (!strcmp(devname, "wacom-tablet")) {                        // (2) 0.04297
/*60  */         dev = usb_wacom_init();                                           // (13) 0.0332
/*62  */     } else if (strstart(devname, "serial:", &p)) {                        // (3) 0.04102
/*64  */         dev = usb_serial_init(p);                                         // 0.0
/*66  */ #ifdef CONFIG_BRLAPI                                                      // 0.0
/*68  */     } else if (!strcmp(devname, "braille")) {                             // 0.0
/*70  */         dev = usb_baum_init();                                            // 0.0
/*72  */ #endif                                                                    // 0.0
/*74  */     } else if (strstart(devname, "net:", &p)) {                           // 0.0
/*76  */         int nic = nb_nics;                                                // 0.0
/*80  */         if (net_client_init("nic", p) < 0)                                // 0.0
/*82  */             return -1;                                                    // 0.0
/*84  */         nd_table[nic].model = "usb";                                      // 0.0
/*86  */         dev = usb_net_init(&nd_table[nic]);                               // 0.0
/*88  */     } else if (!strcmp(devname, "bt") || strstart(devname, "bt:", &p)) {  // 0.0
/*90  */         dev = usb_bt_init(devname[2] ? hci_init(p) :                      // 0.0
/*92  */                         bt_new_hci(qemu_find_bt_vlan(0)));                // 0.0
/*94  */     } else {                                                              // 0.0
/*96  */         return -1;                                                        // 0.0
/*98  */     }                                                                     // 0.0
/*100 */     if (!dev)                                                             // 0.0
/*102 */         return -1;                                                        // 0.0
/*106 */     return usb_device_add_dev(dev);                                       // 0.0
/*108 */ }                                                                         // 0.0
