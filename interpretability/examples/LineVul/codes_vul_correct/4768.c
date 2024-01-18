// commit message qemu@a01aedc8d3 (target=1, prob=0.55521375, correct=True): qom: Avoid leaking str and bool properties on failure
/*0  */ void object_property_add_bool(Object *obj, const char *name,          // (8) 0.05438
/*2  */                               bool (*get)(Object *, Error **),        // (1) 0.1178
/*4  */                               void (*set)(Object *, bool, Error **),  // (0) 0.1239
/*6  */                               Error **errp)                           // (2) 0.1027
/*8  */ {                                                                     // (12) 0.003021
/*10 */     BoolProperty *prop = g_malloc0(sizeof(*prop));                    // (7) 0.06042
/*14 */     prop->get = get;                                                  // (10) 0.02719
/*16 */     prop->set = set;                                                  // (11) 0.02719
/*20 */     object_property_add(obj, name, "bool",                            // (9) 0.04834
/*22 */                         get ? property_get_bool : NULL,               // (3) 0.0997
/*24 */                         set ? property_set_bool : NULL,               // (4) 0.0997
/*26 */                         property_release_bool,                        // (5) 0.08761
/*28 */                         prop, errp);                                  // (6) 0.08459
/*30 */ }                                                                     // (13) 0.003021
