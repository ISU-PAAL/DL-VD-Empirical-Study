// commit message qemu@8f5d58ef2c (target=1, prob=0.11782362, correct=False): qom: enforce readonly nature of link's check callback
/*0 */ const char *object_get_typename(Object *obj)  // (0) 0.4054
/*2 */ {                                             // (2) 0.02703
/*4 */     return obj->class->type->name;            // (1) 0.3243
/*6 */ }                                             // (3) 0.02703
