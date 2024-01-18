// commit message qemu@274250c301 (target=1, prob=0.99915874, correct=True): s390x/css: add s390-squash-mcss machine option
/*0  */ static inline void s390_machine_initfn(Object *obj)                              // (16) 0.0293
/*2  */ {                                                                                // (17) 0.001953
/*4  */     object_property_add_bool(obj, "aes-key-wrap",                                // (10) 0.04102
/*6  */                              machine_get_aes_key_wrap,                           // (2) 0.07617
/*8  */                              machine_set_aes_key_wrap, NULL);                    // (0) 0.08008
/*10 */     object_property_set_description(obj, "aes-key-wrap",                         // (11) 0.04102
/*12 */             "enable/disable AES key wrapping using the CPACF wrapping key",      // (6) 0.05078
/*15 */     object_property_set_bool(obj, true, "aes-key-wrap", NULL);                   // (8) 0.04883
/*19 */     object_property_add_bool(obj, "dea-key-wrap",                                // (12) 0.04102
/*21 */                              machine_get_dea_key_wrap,                           // (3) 0.07617
/*23 */                              machine_set_dea_key_wrap, NULL);                    // (1) 0.08008
/*25 */     object_property_set_description(obj, "dea-key-wrap",                         // (13) 0.04102
/*27 */             "enable/disable DEA key wrapping using the CPACF wrapping key",      // (7) 0.05078
/*30 */     object_property_set_bool(obj, true, "dea-key-wrap", NULL);                   // (9) 0.04883
/*32 */     object_property_add_str(obj, "loadparm",                                     // (15) 0.03516
/*34 */             machine_get_loadparm, machine_set_loadparm, NULL);                   // (5) 0.05664
/*36 */     object_property_set_description(obj, "loadparm",                             // (14) 0.03516
/*38 */             "Up to 8 chars in set of [A-Za-z0-9. ] (lower case chars converted"  // (4) 0.07227
/*40 */             " to upper case) to pass to machine loader, boot manager,"           // 0.0
/*42 */             " and guest kernel",                                                 // 0.0
/*52 */ }                                                                                // 0.0
