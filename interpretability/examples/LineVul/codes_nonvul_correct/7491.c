// commit message qemu@3dc6f86936 (target=0, prob=0.2706052, correct=True): Convert error_report() to warn_report()
/*0  */ int qdev_prop_check_globals(void)                                         // (13) 0.02783
/*2  */ {                                                                         // (30) 0.001988
/*4  */     GList *l;                                                             // (22) 0.0159
/*6  */     int ret = 0;                                                          // (23) 0.0159
/*10 */     for (l = global_props; l; l = l->next) {                              // (7) 0.04175
/*12 */         GlobalProperty *prop = l->data;                                   // (9) 0.03181
/*14 */         ObjectClass *oc;                                                  // (20) 0.02386
/*16 */         DeviceClass *dc;                                                  // (19) 0.02386
/*18 */         if (prop->used) {                                                 // (14) 0.02783
/*20 */             continue;                                                     // (15) 0.02584
/*22 */         }                                                                 // (24) 0.0159
/*24 */         if (!prop->user_provided) {                                       // (10) 0.03181
/*26 */             continue;                                                     // (16) 0.02584
/*28 */         }                                                                 // (25) 0.0159
/*30 */         oc = object_class_by_name(prop->driver);                          // (6) 0.04374
/*32 */         oc = object_class_dynamic_cast(oc, TYPE_DEVICE);                  // (4) 0.05169
/*34 */         if (!oc) {                                                        // (21) 0.02386
/*36 */             error_report("Warning: global %s.%s has invalid class name",  // (3) 0.05567
/*38 */                        prop->driver, prop->property);                     // (1) 0.05964
/*40 */             ret = 1;                                                      // (11) 0.02982
/*42 */             continue;                                                     // (17) 0.02584
/*44 */         }                                                                 // (26) 0.0159
/*46 */         dc = DEVICE_CLASS(oc);                                            // (8) 0.03181
/*48 */         if (!dc->hotpluggable && !prop->used) {                           // (5) 0.04374
/*50 */             error_report("Warning: global %s.%s=%s not used",             // (2) 0.05765
/*52 */                        prop->driver, prop->property, prop->value);        // (0) 0.06759
/*54 */             ret = 1;                                                      // (12) 0.02982
/*56 */             continue;                                                     // (18) 0.02584
/*58 */         }                                                                 // (27) 0.0159
/*60 */     }                                                                     // (29) 0.007952
/*62 */     return ret;                                                           // (28) 0.01193
/*64 */ }                                                                         // (31) 0.001988
