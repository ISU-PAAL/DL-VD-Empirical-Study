// commit message qemu@4f2d3d705c (target=0, prob=0.38694012, correct=True): qdev: initialize properties via QOM
/*0  */ static void device_initfn(Object *obj)                                        // (11) 0.04167
/*2  */ {                                                                             // (15) 0.003788
/*4  */     DeviceState *dev = DEVICE(obj);                                           // (9) 0.04924
/*6  */     Property *prop;                                                           // (12) 0.02652
/*10 */     if (qdev_hotplug) {                                                       // (10) 0.04545
/*12 */         dev->hotplugged = 1;                                                  // (6) 0.05682
/*14 */         qdev_hot_added = true;                                                // (5) 0.06061
/*16 */     }                                                                         // (13) 0.01515
/*20 */     dev->instance_id_alias = -1;                                              // (8) 0.05303
/*22 */     dev->state = DEV_STATE_CREATED;                                           // (7) 0.05682
/*26 */     qdev_prop_set_defaults(dev, qdev_get_props(dev));                         // (2) 0.0947
/*28 */     for (prop = qdev_get_props(dev); prop && prop->name; prop++) {            // (1) 0.09848
/*30 */         qdev_property_add_legacy(dev, prop, NULL);                            // (3) 0.08712
/*32 */         qdev_property_add_static(dev, prop, NULL);                            // (4) 0.08333
/*34 */     }                                                                         // (14) 0.01515
/*38 */     object_property_add_str(OBJECT(dev), "type", qdev_get_type, NULL, NULL);  // (0) 0.1136
/*40 */ }                                                                             // (16) 0.003788
