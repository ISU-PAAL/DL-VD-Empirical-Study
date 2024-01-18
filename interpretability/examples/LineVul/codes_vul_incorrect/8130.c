// commit message qemu@f7b879e072 (target=1, prob=0.48585168, correct=False): qdev: defer DEVICE_DEL event until instance_finalize()
/*0  */ static void device_unparent(Object *obj)                                         // (16) 0.02743
/*2  */ {                                                                                // (23) 0.002494
/*4  */     DeviceState *dev = DEVICE(obj);                                              // (14) 0.03242
/*6  */     BusState *bus;                                                               // (18) 0.01995
/*10 */     if (dev->realized) {                                                         // (17) 0.02743
/*12 */         object_property_set_bool(obj, false, "realized", NULL);                  // (2) 0.06234
/*14 */     }                                                                            // (19) 0.009975
/*16 */     while (dev->num_child_bus) {                                                 // (13) 0.03491
/*18 */         bus = QLIST_FIRST(&dev->child_bus);                                      // (3) 0.05237
/*20 */         object_unparent(OBJECT(bus));                                            // (8) 0.04239
/*22 */     }                                                                            // (20) 0.009975
/*24 */     if (dev->parent_bus) {                                                       // (15) 0.02993
/*26 */         bus_remove_child(dev->parent_bus, dev);                                  // (4) 0.05237
/*28 */         object_unref(OBJECT(dev->parent_bus));                                   // (5) 0.05237
/*30 */         dev->parent_bus = NULL;                                                  // (11) 0.03741
/*32 */     }                                                                            // (21) 0.009975
/*36 */     /* Only send event if the device had been completely realized */             // (12) 0.03741
/*38 */     if (dev->pending_deleted_event) {                                            // (9) 0.0399
/*40 */         g_assert(dev->canonical_path);                                           // (6) 0.04489
/*44 */         qapi_event_send_device_deleted(!!dev->id, dev->id, dev->canonical_path,  // (1) 0.08728
/*46 */                                        &error_abort);                            // (0) 0.1097
/*48 */         g_free(dev->canonical_path);                                             // (7) 0.04489
/*50 */         dev->canonical_path = NULL;                                              // (10) 0.0399
/*52 */     }                                                                            // (22) 0.009975
/*54 */ }                                                                                // (24) 0.002494
