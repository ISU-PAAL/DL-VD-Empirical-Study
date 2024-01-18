// commit message qemu@30c367ed44 (target=1, prob=0.5614074, correct=True): qdev-properties-system.c: Allow vlan or netdev for -device, not both
/*0  */ static void set_vlan(Object *obj, Visitor *v, void *opaque,  // (6) 0.05497
/*2  */                      const char *name, Error **errp)         // (0) 0.07853
/*4  */ {                                                            // (21) 0.002618
/*6  */     DeviceState *dev = DEVICE(obj);                          // (10) 0.03403
/*8  */     Property *prop = opaque;                                 // (17) 0.02356
/*10 */     NICPeers *peers_ptr = qdev_get_prop_ptr(dev, prop);      // (3) 0.06545
/*12 */     NetClientState **ptr = &peers_ptr->ncs[0];               // (7) 0.05236
/*14 */     Error *local_err = NULL;                                 // (12) 0.0288
/*16 */     int32_t id;                                              // (18) 0.02356
/*18 */     NetClientState *hubport;                                 // (15) 0.02618
/*22 */     if (dev->realized) {                                     // (13) 0.0288
/*24 */         qdev_prop_set_after_realize(dev, name, errp);        // (2) 0.06806
/*30 */     visit_type_int32(v, &id, name, &local_err);              // (5) 0.05759
/*32 */     if (local_err) {                                         // (16) 0.02618
/*34 */         error_propagate(errp, local_err);                    // (8) 0.04974
/*38 */     if (id == -1) {                                          // (14) 0.0288
/*40 */         *ptr = NULL;                                         // (11) 0.03141
/*50 */     hubport = net_hub_port_find(id);                         // (9) 0.04188
/*52 */     if (!hubport) {                                          // (19) 0.02356
/*54 */         error_set(errp, QERR_INVALID_PARAMETER_VALUE,        // (1) 0.07592
/*56 */                   name, prop->info->name);                   // (4) 0.06545
/*60 */     *ptr = hubport;                                          // (20) 0.02356
