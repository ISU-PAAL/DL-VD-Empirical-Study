// commit message qemu@03fcbd9dc5 (target=1, prob=0.47423735, correct=False): qdev: Check for the availability of a hotplug controller before adding a device
/*0   */ DeviceState *qdev_device_add(QemuOpts *opts, Error **errp)                    // (5) 0.04688
/*2   */ {                                                                             // (31) 0.001953
/*4   */     DeviceClass *dc;                                                          // (22) 0.01563
/*6   */     const char *driver, *path;                                                // (15) 0.02148
/*8   */     DeviceState *dev;                                                         // (21) 0.01563
/*10  */     BusState *bus = NULL;                                                     // (16) 0.01953
/*12  */     Error *err = NULL;                                                        // (20) 0.01758
/*16  */     driver = qemu_opt_get(opts, "driver");                                    // (8) 0.03711
/*18  */     if (!driver) {                                                            // (24) 0.01562
/*20  */         error_setg(errp, QERR_MISSING_PARAMETER, "driver");                   // (3) 0.06055
/*22  */         return NULL;                                                          // (18) 0.01953
/*24  */     }                                                                         // (30) 0.007812
/*28  */     /* find driver */                                                         // (28) 0.01367
/*30  */     dc = qdev_get_device_class(&driver, errp);                                // (7) 0.03711
/*32  */     if (!dc) {                                                                // (23) 0.01562
/*34  */         return NULL;                                                          // (19) 0.01953
/*36  */     }                                                                         // (29) 0.007812
/*40  */     /* find bus */                                                            // (27) 0.01367
/*42  */     path = qemu_opt_get(opts, "bus");                                         // (10) 0.03711
/*44  */     if (path != NULL) {                                                       // (17) 0.01953
/*46  */         bus = qbus_find(path, errp);                                          // (9) 0.03711
/*48  */         if (!bus) {                                                           // (14) 0.02344
/*50  */             return NULL;                                                      // (13) 0.02734
/*52  */         }                                                                     // (25) 0.01562
/*54  */         if (!object_dynamic_cast(OBJECT(bus), dc->bus_type)) {                // (4) 0.05469
/*56  */             error_setg(errp, "Device '%s' can't go on %s bus",                // (1) 0.06445
/*58  */                        driver, object_get_typename(OBJECT(bus)));             // (0) 0.07422
/*60  */             return NULL;                                                      // (12) 0.02734
/*62  */         }                                                                     // (26) 0.01562
/*64  */     } else if (dc->bus_type != NULL) {                                        // (11) 0.03125
/*66  */         bus = qbus_find_recursive(sysbus_get_default(), NULL, dc->bus_type);  // (2) 0.0625
/*68  */         if (!bus || qbus_is_full(bus)) {                                      // (6) 0.04102
/*70  */             error_setg(errp, "No '%s' bus found for device '%s'",             // 0.0
/*72  */                        dc->bus_type, driver);                                 // 0.0
/*74  */             return NULL;                                                      // 0.0
/*76  */         }                                                                     // 0.0
/*78  */     }                                                                         // 0.0
/*80  */     if (qdev_hotplug && bus && !qbus_is_hotpluggable(bus)) {                  // 0.0
/*82  */         error_setg(errp, QERR_BUS_NO_HOTPLUG, bus->name);                     // 0.0
/*84  */         return NULL;                                                          // 0.0
/*86  */     }                                                                         // 0.0
/*90  */     if (!migration_is_idle()) {                                               // 0.0
/*92  */         error_setg(errp, "device_add not allowed while migrating");           // 0.0
/*94  */         return NULL;                                                          // 0.0
/*96  */     }                                                                         // 0.0
/*100 */     /* create device */                                                       // 0.0
/*102 */     dev = DEVICE(object_new(driver));                                         // 0.0
/*106 */     if (bus) {                                                                // 0.0
/*108 */         qdev_set_parent_bus(dev, bus);                                        // 0.0
/*115 */     }                                                                         // 0.0
/*119 */     qdev_set_id(dev, qemu_opts_id(opts));                                     // 0.0
/*123 */     /* set properties */                                                      // 0.0
/*125 */     if (qemu_opt_foreach(opts, set_property, dev, &err)) {                    // 0.0
/*128 */     }                                                                         // 0.0
/*132 */     dev->opts = opts;                                                         // 0.0
/*134 */     object_property_set_bool(OBJECT(dev), true, "realized", &err);            // 0.0
/*136 */     if (err != NULL) {                                                        // 0.0
/*138 */         dev->opts = NULL;                                                     // 0.0
/*141 */     }                                                                         // 0.0
/*143 */     return dev;                                                               // 0.0
/*147 */ err_del_dev:                                                                  // 0.0
/*149 */     error_propagate(errp, err);                                               // 0.0
/*151 */     object_unparent(OBJECT(dev));                                             // 0.0
/*153 */     object_unref(OBJECT(dev));                                                // 0.0
/*155 */     return NULL;                                                              // 0.0
/*157 */ }                                                                             // 0.0
