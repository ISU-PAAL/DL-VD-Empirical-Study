// commit message qemu@6350b09046 (target=1, prob=0.53782636, correct=True): qdev: fix off-by-one
/*0  */ static void set_int8(Object *obj, Visitor *v, void *opaque,     // (7) 0.05263
/*2  */                      const char *name, Error **errp)            // (2) 0.07519
/*4  */ {                                                               // (23) 0.002506
/*6  */     DeviceState *dev = DEVICE(obj);                             // (11) 0.03258
/*8  */     Property *prop = opaque;                                    // (15) 0.02256
/*10 */     int8_t *ptr = qdev_get_prop_ptr(dev, prop);                 // (4) 0.05764
/*12 */     Error *local_err = NULL;                                    // (13) 0.02757
/*14 */     int64_t value;                                              // (16) 0.02256
/*18 */     if (dev->state != DEV_STATE_CREATED) {                      // (10) 0.04511
/*20 */         error_set(errp, QERR_PERMISSION_DENIED);                // (3) 0.06266
/*22 */         return;                                                 // (17) 0.02256
/*24 */     }                                                           // (20) 0.01003
/*28 */     visit_type_int(v, &value, name, &local_err);                // (8) 0.05263
/*30 */     if (local_err) {                                            // (14) 0.02506
/*32 */         error_propagate(errp, local_err);                       // (9) 0.04762
/*34 */         return;                                                 // (18) 0.02256
/*36 */     }                                                           // (21) 0.01003
/*38 */     if (value > prop->info->min && value <= prop->info->max) {  // (6) 0.05514
/*40 */         *ptr = value;                                           // (12) 0.03008
/*42 */     } else {                                                    // (19) 0.01504
/*44 */         error_set(errp, QERR_PROPERTY_VALUE_OUT_OF_RANGE,       // (1) 0.07769
/*46 */                   dev->id?:"", name, value, prop->info->min,    // (0) 0.08271
/*48 */                   prop->info->max);                             // (5) 0.05764
/*50 */     }                                                           // (22) 0.01003
/*52 */ }                                                               // (24) 0.002506
