// commit message qemu@da57febfed (target=0, prob=0.7814106, correct=False): qdev: give all devices a canonical path
/*0  */ DeviceState *qdev_try_create(BusState *bus, const char *name)  // (0) 0.1053
/*2  */ {                                                              // (15) 0.005263
/*4  */     DeviceState *dev;                                          // (8) 0.04211
/*8  */     if (object_class_by_name(name) == NULL) {                  // (1) 0.1
/*10 */         return NULL;                                           // (6) 0.05263
/*12 */     }                                                          // (12) 0.02105
/*14 */     dev = DEVICE(object_new(name));                            // (5) 0.07368
/*16 */     if (!dev) {                                                // (9) 0.04211
/*18 */         return NULL;                                           // (7) 0.05263
/*20 */     }                                                          // (13) 0.02105
/*24 */     if (!bus) {                                                // (10) 0.04211
/*26 */         bus = sysbus_get_default();                            // (2) 0.08421
/*28 */     }                                                          // (14) 0.02105
/*32 */     qdev_set_parent_bus(dev, bus);                             // (3) 0.08421
/*34 */     qdev_prop_set_globals(dev);                                // (4) 0.08421
/*38 */     return dev;                                                // (11) 0.03158
/*40 */ }                                                              // (16) 0.005263
