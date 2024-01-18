// commit message qemu@30d335d68d (target=1, prob=0.4121478, correct=False): hotplug: more fixes for scsi disk hotplug.
/*0   */ static PCIDevice *qemu_pci_hot_add_storage(Monitor *mon,                           // (5) 0.04492
/*2   */                                            const char *devaddr,                    // (1) 0.09375
/*4   */                                            const char *opts)                       // (0) 0.09375
/*6   */ {                                                                                  // (27) 0.001953
/*8   */     PCIDevice *dev;                                                                // (17) 0.01953
/*10  */     DriveInfo *dinfo = NULL;                                                       // (16) 0.02148
/*12  */     int type = -1;                                                                 // (21) 0.01758
/*14  */     char buf[128];                                                                 // (22) 0.01562
/*16  */     PCIBus *bus;                                                                   // (20) 0.01758
/*18  */     int devfn;                                                                     // (24) 0.01367
/*22  */     if (get_param_value(buf, sizeof(buf), "if", opts)) {                           // (3) 0.04688
/*24  */         if (!strcmp(buf, "scsi"))                                                  // (10) 0.03516
/*26  */             type = IF_SCSI;                                                        // (11) 0.03516
/*28  */         else if (!strcmp(buf, "virtio")) {                                         // (7) 0.03906
/*30  */             type = IF_VIRTIO;                                                      // (9) 0.03711
/*32  */         } else {                                                                   // (18) 0.01953
/*34  */             monitor_printf(mon, "type %s not a hotpluggable PCI device.\n", buf);  // (2) 0.06836
/*36  */             return NULL;                                                           // (13) 0.02734
/*38  */         }                                                                          // (23) 0.01562
/*40  */     } else {                                                                       // (25) 0.01172
/*42  */         monitor_printf(mon, "no if= specified\n");                                 // (6) 0.04102
/*44  */         return NULL;                                                               // (19) 0.01953
/*46  */     }                                                                              // (26) 0.007812
/*50  */     if (get_param_value(buf, sizeof(buf), "file", opts)) {                         // (4) 0.04688
/*52  */         dinfo = add_init_drive(opts);                                              // (8) 0.03711
/*54  */         if (!dinfo)                                                                // (15) 0.02344
/*56  */             return NULL;                                                           // (14) 0.02734
/*58  */         if (dinfo->devaddr) {                                                      // (12) 0.03125
/*60  */             monitor_printf(mon, "Parameter addr not supported\n");                 // 0.0
/*62  */             return NULL;                                                           // 0.0
/*64  */         }                                                                          // 0.0
/*66  */     } else {                                                                       // 0.0
/*68  */         dinfo = NULL;                                                              // 0.0
/*70  */     }                                                                              // 0.0
/*74  */     bus = pci_get_bus_devfn(&devfn, devaddr);                                      // 0.0
/*76  */     if (!bus) {                                                                    // 0.0
/*78  */         monitor_printf(mon, "Invalid PCI device address %s\n", devaddr);           // 0.0
/*80  */         return NULL;                                                               // 0.0
/*82  */     }                                                                              // 0.0
/*86  */     switch (type) {                                                                // 0.0
/*88  */     case IF_SCSI:                                                                  // 0.0
/*90  */         if (!dinfo) {                                                              // 0.0
/*92  */             monitor_printf(mon, "scsi requires a backing file/device.\n");         // 0.0
/*94  */             return NULL;                                                           // 0.0
/*96  */         }                                                                          // 0.0
/*98  */         dev = pci_create(bus, devfn, "lsi53c895a");                                // 0.0
/*100 */         if (qdev_init(&dev->qdev) < 0)                                             // 0.0
/*102 */             dev = NULL;                                                            // 0.0
/*104 */         if (dev) {                                                                 // 0.0
/*106 */             BusState *scsibus = QLIST_FIRST(&dev->qdev.child_bus);                 // 0.0
/*108 */             scsi_bus_legacy_add_drive(DO_UPCAST(SCSIBus, qbus, scsibus),           // 0.0
/*110 */                                       dinfo, dinfo->unit);                         // 0.0
/*112 */         }                                                                          // 0.0
/*114 */         break;                                                                     // 0.0
/*116 */     case IF_VIRTIO:                                                                // 0.0
/*118 */         if (!dinfo) {                                                              // 0.0
/*120 */             monitor_printf(mon, "virtio requires a backing file/device.\n");       // 0.0
/*122 */             return NULL;                                                           // 0.0
/*124 */         }                                                                          // 0.0
/*126 */         dev = pci_create(bus, devfn, "virtio-blk-pci");                            // 0.0
/*128 */         qdev_prop_set_drive(&dev->qdev, "drive", dinfo);                           // 0.0
/*130 */         if (qdev_init(&dev->qdev) < 0)                                             // 0.0
/*132 */             dev = NULL;                                                            // 0.0
/*134 */         break;                                                                     // 0.0
/*136 */     default:                                                                       // 0.0
/*138 */         dev = NULL;                                                                // 0.0
/*140 */     }                                                                              // 0.0
/*142 */     return dev;                                                                    // 0.0
/*144 */ }                                                                                  // 0.0
