// commit message qemu@64607d0881 (target=0, prob=0.19527015, correct=True): qom: add a generic mechanism to resolve paths
/*0  */ void object_property_add(Object *obj, const char *name, const char *type,  // (9) 0.04575
/*2  */                          ObjectPropertyAccessor *get,                      // (3) 0.06754
/*4  */                          ObjectPropertyAccessor *set,                      // (4) 0.06754
/*6  */                          ObjectPropertyRelease *release,                   // (6) 0.06536
/*8  */                          void *opaque, Error **errp)                       // (0) 0.07407
/*10 */ {                                                                          // (22) 0.002179
/*12 */     ObjectProperty *prop;                                                  // (19) 0.01743
/*16 */     QTAILQ_FOREACH(prop, &obj->properties, node) {                         // (10) 0.04575
/*18 */         if (strcmp(prop->name, name) == 0) {                               // (7) 0.04793
/*20 */             error_setg(errp, "attempt to add duplicate property '%s'"      // (5) 0.06536
/*22 */                        " to object (type '%s')", name,                     // (1) 0.07407
/*24 */                        object_get_typename(obj));                          // (2) 0.06972
/*26 */             return;                                                        // (14) 0.02832
/*28 */         }                                                                  // (20) 0.01743
/*30 */     }                                                                      // (21) 0.008715
/*34 */     prop = g_malloc0(sizeof(*prop));                                       // (11) 0.03486
/*38 */     prop->name = g_strdup(name);                                           // (12) 0.03268
/*40 */     prop->type = g_strdup(type);                                           // (13) 0.03268
/*44 */     prop->get = get;                                                       // (16) 0.01961
/*46 */     prop->set = set;                                                       // (17) 0.01961
/*48 */     prop->release = release;                                               // (18) 0.01961
/*50 */     prop->opaque = opaque;                                                 // (15) 0.02179
/*54 */     QTAILQ_INSERT_TAIL(&obj->properties, prop, node);                      // (8) 0.04793
/*56 */ }                                                                          // (23) 0.002179
