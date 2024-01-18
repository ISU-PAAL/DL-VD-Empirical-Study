// commit message qemu@e26110cfc6 (target=0, prob=0.095715806, correct=True): module: implement module loading
/*0  */ static ModuleTypeList *find_type(module_init_type type)  // (0) 0.2353
/*2  */ {                                                        // (5) 0.01471
/*4  */     ModuleTypeList *l;                                   // (2) 0.1324
/*8  */     init_types();                                        // (3) 0.1029
/*12 */     l = &init_type_list[type];                           // (1) 0.2059
/*16 */     return l;                                            // (4) 0.08824
/*18 */ }                                                        // (6) 0.01471
