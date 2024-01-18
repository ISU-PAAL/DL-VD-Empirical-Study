// commit message qemu@92b3eeadd9 (target=1, prob=0.66230977, correct=True): qom: Fix crash with qom-list and link properties
/*0  */ Object *object_resolve_path_component(Object *parent, const gchar *part)  // (0) 0.1228
/*2  */ {                                                                         // (12) 0.005848
/*4  */     ObjectProperty *prop = object_property_find(parent, part, NULL);      // (1) 0.117
/*6  */     if (prop == NULL) {                                                   // (6) 0.05848
/*8  */         return NULL;                                                      // (7) 0.05848
/*10 */     }                                                                     // (10) 0.02339
/*14 */     if (object_property_is_link(prop)) {                                  // (4) 0.09357
/*16 */         return *(Object **)prop->opaque;                                  // (2) 0.1053
/*18 */     } else if (object_property_is_child(prop)) {                          // (3) 0.1053
/*20 */         return prop->opaque;                                              // (5) 0.07602
/*22 */     } else {                                                              // (9) 0.03509
/*24 */         return NULL;                                                      // (8) 0.05848
/*26 */     }                                                                     // (11) 0.02339
/*28 */ }                                                                         // (13) 0.005848
