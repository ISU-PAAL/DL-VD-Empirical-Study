// commit message qemu@8f5d58ef2c (target=1, prob=0.77962196, correct=True): qom: enforce readonly nature of link's check callback
/*0 */ void object_property_allow_set_link(Object *obj, const char *name,  // (1) 0.2273
/*2 */                                     Object *val, Error **errp)      // (0) 0.5
/*4 */ {                                                                   // (3) 0.01136
/*6 */     /* Allow the link to be set, always */                          // (2) 0.1477
/*8 */ }                                                                   // (4) 0.01136
