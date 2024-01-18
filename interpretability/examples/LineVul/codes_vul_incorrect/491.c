// commit message qemu@7b0309490c (target=1, prob=0.41239092, correct=False): qdev-monitor: Set properties after parent is assigned in device_add
/*0   */ DeviceState *qdev_device_add(QemuOpts *opts)                                  // (8) 0.03711
/*2   */ {                                                                             // (32) 0.001953
/*4   */     ObjectClass *oc;                                                          // (23) 0.01562
/*6   */     DeviceClass *dc;                                                          // (22) 0.01563
/*8   */     const char *driver, *path, *id;                                           // (13) 0.02734
/*10  */     DeviceState *dev;                                                         // (21) 0.01563
/*12  */     BusState *bus = NULL;                                                     // (16) 0.01953
/*14  */     Error *err = NULL;                                                        // (20) 0.01758
/*18  */     driver = qemu_opt_get(opts, "driver");                                    // (9) 0.03711
/*20  */     if (!driver) {                                                            // (24) 0.01562
/*22  */         qerror_report(QERR_MISSING_PARAMETER, "driver");                      // (3) 0.05469
/*24  */         return NULL;                                                          // (17) 0.01953
/*26  */     }                                                                         // (30) 0.007812
/*30  */     /* find driver */                                                         // (27) 0.01367
/*32  */     oc = object_class_by_name(driver);                                        // (12) 0.03125
/*34  */     if (!oc) {                                                                // (26) 0.01562
/*36  */         const char *typename = find_typename_by_alias(driver);                // (4) 0.05078
/*40  */         if (typename) {                                                       // (14) 0.02734
/*42  */             driver = typename;                                                // (11) 0.03125
/*44  */             oc = object_class_by_name(driver);                                // (5) 0.04687
/*46  */         }                                                                     // (25) 0.01562
/*48  */     }                                                                         // (28) 0.007812
/*52  */     if (!object_class_dynamic_cast(oc, TYPE_DEVICE)) {                        // (6) 0.04297
/*54  */         qerror_report(ERROR_CLASS_GENERIC_ERROR,                              // (7) 0.04297
/*56  */                       "'%s' is not a valid device model name", driver);       // (0) 0.06836
/*58  */         return NULL;                                                          // (19) 0.01953
/*60  */     }                                                                         // (31) 0.007812
/*64  */     if (object_class_is_abstract(oc)) {                                       // (10) 0.0332
/*66  */         qerror_report(QERR_INVALID_PARAMETER_VALUE, "driver",                 // (1) 0.05859
/*68  */                       "non-abstract device type");                            // (2) 0.05664
/*70  */         return NULL;                                                          // (18) 0.01953
/*72  */     }                                                                         // (29) 0.007812
/*76  */     dc = DEVICE_CLASS(oc);                                                    // (15) 0.02344
/*78  */     if (dc->cannot_instantiate_with_device_add_yet) {                         // 0.0
/*80  */         qerror_report(QERR_INVALID_PARAMETER_VALUE, "driver",                 // 0.0
/*82  */                       "pluggable device type");                               // 0.0
/*84  */         return NULL;                                                          // 0.0
/*86  */     }                                                                         // 0.0
/*90  */     /* find bus */                                                            // 0.0
/*92  */     path = qemu_opt_get(opts, "bus");                                         // 0.0
/*94  */     if (path != NULL) {                                                       // 0.0
/*96  */         bus = qbus_find(path);                                                // 0.0
/*98  */         if (!bus) {                                                           // 0.0
/*100 */             return NULL;                                                      // 0.0
/*102 */         }                                                                     // 0.0
/*104 */         if (!object_dynamic_cast(OBJECT(bus), dc->bus_type)) {                // 0.0
/*106 */             qerror_report(QERR_BAD_BUS_FOR_DEVICE,                            // 0.0
/*108 */                           driver, object_get_typename(OBJECT(bus)));          // 0.0
/*110 */             return NULL;                                                      // 0.0
/*112 */         }                                                                     // 0.0
/*114 */     } else if (dc->bus_type != NULL) {                                        // 0.0
/*116 */         bus = qbus_find_recursive(sysbus_get_default(), NULL, dc->bus_type);  // 0.0
/*118 */         if (!bus) {                                                           // 0.0
/*120 */             qerror_report(QERR_NO_BUS_FOR_DEVICE,                             // 0.0
/*122 */                           dc->bus_type, driver);                              // 0.0
/*124 */             return NULL;                                                      // 0.0
/*126 */         }                                                                     // 0.0
/*128 */     }                                                                         // 0.0
/*130 */     if (qdev_hotplug && bus && !bus->allow_hotplug) {                         // 0.0
/*132 */         qerror_report(QERR_BUS_NO_HOTPLUG, bus->name);                        // 0.0
/*134 */         return NULL;                                                          // 0.0
/*136 */     }                                                                         // 0.0
/*140 */     /* create device, set properties */                                       // 0.0
/*142 */     dev = DEVICE(object_new(driver));                                         // 0.0
/*146 */     if (bus) {                                                                // 0.0
/*148 */         qdev_set_parent_bus(dev, bus);                                        // 0.0
/*150 */     }                                                                         // 0.0
/*154 */     id = qemu_opts_id(opts);                                                  // 0.0
/*156 */     if (id) {                                                                 // 0.0
/*158 */         dev->id = id;                                                         // 0.0
/*160 */     }                                                                         // 0.0
/*162 */     if (qemu_opt_foreach(opts, set_property, dev, 1) != 0) {                  // 0.0
/*164 */         object_unparent(OBJECT(dev));                                         // 0.0
/*166 */         object_unref(OBJECT(dev));                                            // 0.0
/*168 */         return NULL;                                                          // 0.0
/*170 */     }                                                                         // 0.0
/*172 */     if (dev->id) {                                                            // 0.0
/*174 */         object_property_add_child(qdev_get_peripheral(), dev->id,             // 0.0
/*176 */                                   OBJECT(dev), NULL);                         // 0.0
/*178 */     } else {                                                                  // 0.0
/*180 */         static int anon_count;                                                // 0.0
/*182 */         gchar *name = g_strdup_printf("device[%d]", anon_count++);            // 0.0
/*184 */         object_property_add_child(qdev_get_peripheral_anon(), name,           // 0.0
/*186 */                                   OBJECT(dev), NULL);                         // 0.0
/*188 */         g_free(name);                                                         // 0.0
/*190 */     }                                                                         // 0.0
/*194 */     dev->opts = opts;                                                         // 0.0
/*196 */     object_property_set_bool(OBJECT(dev), true, "realized", &err);            // 0.0
/*198 */     if (err != NULL) {                                                        // 0.0
/*200 */         qerror_report_err(err);                                               // 0.0
/*202 */         error_free(err);                                                      // 0.0
/*204 */         dev->opts = NULL;                                                     // 0.0
/*206 */         object_unparent(OBJECT(dev));                                         // 0.0
/*208 */         object_unref(OBJECT(dev));                                            // 0.0
/*210 */         qerror_report(QERR_DEVICE_INIT_FAILED, driver);                       // 0.0
/*212 */         return NULL;                                                          // 0.0
/*214 */     }                                                                         // 0.0
/*216 */     return dev;                                                               // 0.0
/*218 */ }                                                                             // 0.0
