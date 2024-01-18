// commit message qemu@b061dc41f6 (target=1, prob=0.29288855, correct=False): qom: Do not register interface "types" in the type table and fix names
/*0  */ static void type_initialize_interface(TypeImpl *ti, const char *parent)  // (3) 0.0696
/*2  */ {                                                                        // (14) 0.003663
/*4  */     InterfaceClass *new_iface;                                           // (10) 0.04029
/*6  */     TypeInfo info = { };                                                 // (12) 0.03297
/*8  */     TypeImpl *iface_impl;                                                // (9) 0.04029
/*12 */     info.parent = parent;                                                // (13) 0.03297
/*14 */     info.name = g_strdup_printf("%s::%s", ti->name, info.parent);        // (1) 0.1062
/*16 */     info.abstract = true;                                                // (11) 0.03663
/*20 */     iface_impl = type_register(&info);                                   // (6) 0.05128
/*22 */     type_initialize(iface_impl);                                         // (7) 0.04762
/*24 */     g_free((char *)info.name);                                           // (8) 0.04762
/*28 */     new_iface = (InterfaceClass *)iface_impl->class;                     // (4) 0.0696
/*30 */     new_iface->concrete_class = ti->class;                               // (5) 0.06227
/*34 */     ti->class->interfaces = g_slist_append(ti->class->interfaces,        // (2) 0.08791
/*36 */                                            iface_impl->class);           // (0) 0.1795
/*38 */ }                                                                        // (15) 0.003663
