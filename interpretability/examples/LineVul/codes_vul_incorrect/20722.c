// commit message qemu@4715d42efe (target=1, prob=0.33654666, correct=False): qom: Do not reuse errp after a possible error
/*0  */ static void property_get_enum(Object *obj, Visitor *v, void *opaque,  // (2) 0.1667
/*2  */                               const char *name, Error **errp)         // (0) 0.2955
/*4  */ {                                                                     // (6) 0.007576
/*6  */     EnumProperty *prop = opaque;                                      // (4) 0.08333
/*8  */     int value;                                                        // (5) 0.04545
/*12 */     value = prop->get(obj, errp);                                     // (3) 0.1061
/*14 */     visit_type_enum(v, &value, prop->strings, NULL, name, errp);      // (1) 0.1894
/*16 */ }                                                                     // (7) 0.007576
