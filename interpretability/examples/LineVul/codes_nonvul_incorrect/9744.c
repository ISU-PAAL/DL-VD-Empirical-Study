// commit message qemu@fb846a094f (target=0, prob=0.51321816, correct=False): virtio-ccw: implement ->device_plugged
/*0   */ static void virtio_ccw_device_realize(VirtioCcwDevice *dev, Error **errp)         // (4) 0.05469
/*2   */ {                                                                                 // (31) 0.001953
/*4   */     unsigned int cssid = 0;                                                       // (17) 0.02148
/*6   */     unsigned int ssid = 0;                                                        // (20) 0.01953
/*8   */     unsigned int schid;                                                           // (26) 0.01562
/*10  */     unsigned int devno;                                                           // (25) 0.01562
/*12  */     bool have_devno = false;                                                      // (16) 0.02148
/*14  */     bool found = false;                                                           // (24) 0.01563
/*16  */     SubchDev *sch;                                                                // (22) 0.01758
/*18  */     int num;                                                                      // (28) 0.01172
/*20  */     DeviceState *parent = DEVICE(dev);                                            // (10) 0.02539
/*22  */     Error *err = NULL;                                                            // (21) 0.01758
/*24  */     VirtIOCCWDeviceClass *k = VIRTIO_CCW_DEVICE_GET_CLASS(dev);                   // (5) 0.05469
/*26  */     VirtIODevice *vdev;                                                           // (12) 0.02344
/*30  */     sch = g_malloc0(sizeof(SubchDev));                                            // (7) 0.03516
/*34  */     sch->driver_data = dev;                                                       // (18) 0.02148
/*36  */     dev->sch = sch;                                                               // (23) 0.01758
/*40  */     dev->indicators = NULL;                                                       // (19) 0.01953
/*44  */     /* Initialize subchannel structure. */                                        // (15) 0.02148
/*46  */     sch->channel_prog = 0x0;                                                      // (8) 0.02734
/*48  */     sch->last_cmd_valid = false;                                                  // (11) 0.02539
/*50  */     sch->thinint_active = false;                                                  // (14) 0.02344
/*52  */     /*                                                                            // (30) 0.007812
/*54  */      * Use a device number if provided. Otherwise, fall back to subchannel        // (6) 0.03711
/*56  */      * number.                                                                    // (27) 0.01367
/*58  */      */                                                                           // (29) 0.009766
/*60  */     if (dev->bus_id) {                                                            // (13) 0.02344
/*62  */         num = sscanf(dev->bus_id, "%x.%x.%04x", &cssid, &ssid, &devno);           // (1) 0.08008
/*64  */         if (num == 3) {                                                           // (9) 0.02734
/*66  */             if ((cssid > MAX_CSSID) || (ssid > MAX_SSID)) {                       // (3) 0.0625
/*68  */                 error_setg(errp, "Invalid cssid or ssid: cssid %x, ssid %x",      // (0) 0.08398
/*70  */                            cssid, ssid);                                          // (2) 0.06445
/*72  */                 goto out_err;                                                     // 0.0
/*74  */             }                                                                     // 0.0
/*76  */             /* Enforce use of virtual cssid. */                                   // 0.0
/*78  */             if (cssid != VIRTUAL_CSSID) {                                         // 0.0
/*80  */                 error_setg(errp, "cssid %x not valid for virtio devices",         // 0.0
/*82  */                            cssid);                                                // 0.0
/*84  */                 goto out_err;                                                     // 0.0
/*86  */             }                                                                     // 0.0
/*88  */             if (css_devno_used(cssid, ssid, devno)) {                             // 0.0
/*90  */                 error_setg(errp, "Device %x.%x.%04x already exists",              // 0.0
/*92  */                            cssid, ssid, devno);                                   // 0.0
/*94  */                 goto out_err;                                                     // 0.0
/*96  */             }                                                                     // 0.0
/*98  */             sch->cssid = cssid;                                                   // 0.0
/*100 */             sch->ssid = ssid;                                                     // 0.0
/*102 */             sch->devno = devno;                                                   // 0.0
/*104 */             have_devno = true;                                                    // 0.0
/*106 */         } else {                                                                  // 0.0
/*108 */             error_setg(errp, "Malformed devno parameter '%s'", dev->bus_id);      // 0.0
/*110 */             goto out_err;                                                         // 0.0
/*112 */         }                                                                         // 0.0
/*114 */     }                                                                             // 0.0
/*118 */     /* Find the next free id. */                                                  // 0.0
/*120 */     if (have_devno) {                                                             // 0.0
/*122 */         for (schid = 0; schid <= MAX_SCHID; schid++) {                            // 0.0
/*124 */             if (!css_find_subch(1, cssid, ssid, schid)) {                         // 0.0
/*126 */                 sch->schid = schid;                                               // 0.0
/*128 */                 css_subch_assign(cssid, ssid, schid, devno, sch);                 // 0.0
/*130 */                 found = true;                                                     // 0.0
/*132 */                 break;                                                            // 0.0
/*134 */             }                                                                     // 0.0
/*136 */         }                                                                         // 0.0
/*138 */         if (!found) {                                                             // 0.0
/*140 */             error_setg(errp, "No free subchannel found for %x.%x.%04x",           // 0.0
/*142 */                        cssid, ssid, devno);                                       // 0.0
/*144 */             goto out_err;                                                         // 0.0
/*146 */         }                                                                         // 0.0
/*148 */         trace_virtio_ccw_new_device(cssid, ssid, schid, devno,                    // 0.0
/*150 */                                     "user-configured");                           // 0.0
/*152 */     } else {                                                                      // 0.0
/*154 */         cssid = VIRTUAL_CSSID;                                                    // 0.0
/*156 */         for (ssid = 0; ssid <= MAX_SSID; ssid++) {                                // 0.0
/*158 */             for (schid = 0; schid <= MAX_SCHID; schid++) {                        // 0.0
/*160 */                 if (!css_find_subch(1, cssid, ssid, schid)) {                     // 0.0
/*162 */                     sch->cssid = cssid;                                           // 0.0
/*164 */                     sch->ssid = ssid;                                             // 0.0
/*166 */                     sch->schid = schid;                                           // 0.0
/*168 */                     devno = schid;                                                // 0.0
/*170 */                     /*                                                            // 0.0
/*172 */                      * If the devno is already taken, look further in this        // 0.0
/*174 */                      * subchannel set.                                            // 0.0
/*176 */                      */                                                           // 0.0
/*178 */                     while (css_devno_used(cssid, ssid, devno)) {                  // 0.0
/*180 */                         if (devno == MAX_SCHID) {                                 // 0.0
/*182 */                             devno = 0;                                            // 0.0
/*184 */                         } else if (devno == schid - 1) {                          // 0.0
/*186 */                             error_setg(errp, "No free devno found");              // 0.0
/*188 */                             goto out_err;                                         // 0.0
/*190 */                         } else {                                                  // 0.0
/*192 */                             devno++;                                              // 0.0
/*194 */                         }                                                         // 0.0
/*196 */                     }                                                             // 0.0
/*198 */                     sch->devno = devno;                                           // 0.0
/*200 */                     css_subch_assign(cssid, ssid, schid, devno, sch);             // 0.0
/*202 */                     found = true;                                                 // 0.0
/*204 */                     break;                                                        // 0.0
/*206 */                 }                                                                 // 0.0
/*208 */             }                                                                     // 0.0
/*210 */             if (found) {                                                          // 0.0
/*212 */                 break;                                                            // 0.0
/*214 */             }                                                                     // 0.0
/*216 */         }                                                                         // 0.0
/*218 */         if (!found) {                                                             // 0.0
/*220 */             error_setg(errp, "Virtual channel subsystem is full!");               // 0.0
/*222 */             goto out_err;                                                         // 0.0
/*224 */         }                                                                         // 0.0
/*226 */         trace_virtio_ccw_new_device(cssid, ssid, schid, devno,                    // 0.0
/*228 */                                     "auto-configured");                           // 0.0
/*230 */     }                                                                             // 0.0
/*234 */     /* Build initial schib. */                                                    // 0.0
/*236 */     css_sch_build_virtual_schib(sch, 0, VIRTIO_CCW_CHPID_TYPE);                   // 0.0
/*240 */     sch->ccw_cb = virtio_ccw_cb;                                                  // 0.0
/*244 */     /* Build senseid data. */                                                     // 0.0
/*246 */     memset(&sch->id, 0, sizeof(SenseId));                                         // 0.0
/*248 */     sch->id.reserved = 0xff;                                                      // 0.0
/*250 */     sch->id.cu_type = VIRTIO_CCW_CU_TYPE;                                         // 0.0
/*254 */     if (k->realize) {                                                             // 0.0
/*256 */         k->realize(dev, &err);                                                    // 0.0
/*258 */     }                                                                             // 0.0
/*260 */     if (err) {                                                                    // 0.0
/*262 */         error_propagate(errp, err);                                               // 0.0
/*264 */         css_subch_assign(cssid, ssid, schid, devno, NULL);                        // 0.0
/*266 */         goto out_err;                                                             // 0.0
/*268 */     }                                                                             // 0.0
/*272 */     /* device_id is only set after vdev has been realized */                      // 0.0
/*274 */     vdev = virtio_ccw_get_vdev(sch);                                              // 0.0
/*276 */     sch->id.cu_model = vdev->device_id;                                           // 0.0
/*280 */     /* Only the first 32 feature bits are used. */                                // 0.0
/*282 */     dev->host_features[0] = virtio_bus_get_vdev_features(&dev->bus,               // 0.0
/*284 */                                                          dev->host_features[0]);  // 0.0
/*288 */     virtio_add_feature(&dev->host_features[0], VIRTIO_F_NOTIFY_ON_EMPTY);         // 0.0
/*290 */     virtio_add_feature(&dev->host_features[0], VIRTIO_F_BAD_FEATURE);             // 0.0
/*294 */     css_generate_sch_crws(sch->cssid, sch->ssid, sch->schid,                      // 0.0
/*296 */                           parent->hotplugged, 1);                                 // 0.0
/*298 */     return;                                                                       // 0.0
/*302 */ out_err:                                                                          // 0.0
/*304 */     dev->sch = NULL;                                                              // 0.0
/*306 */     g_free(sch);                                                                  // 0.0
/*308 */ }                                                                                 // 0.0
