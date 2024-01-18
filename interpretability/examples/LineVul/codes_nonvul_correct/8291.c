// commit message qemu@524d18d8bd (target=0, prob=0.039063215, correct=True): s390x: get rid of cpu_s390x_create()
/*0  */ S390CPU *s390x_new_cpu(const char *cpu_model, uint32_t core_id, Error **errp)  // (0) 0.1199
/*2  */ {                                                                              // (19) 0.003745
/*4  */     S390CPU *cpu;                                                              // (11) 0.03371
/*6  */     Error *err = NULL;                                                         // (12) 0.03371
/*10 */     cpu = cpu_s390x_create(cpu_model, &err);                                   // (3) 0.07491
/*12 */     if (err != NULL) {                                                         // (7) 0.03745
/*14 */         goto out;                                                              // (8) 0.03745
/*16 */     }                                                                          // (15) 0.01498
/*20 */     object_property_set_int(OBJECT(cpu), core_id, "core-id", &err);            // (1) 0.1049
/*22 */     if (err != NULL) {                                                         // (9) 0.03745
/*24 */         goto out;                                                              // (10) 0.03745
/*26 */     }                                                                          // (16) 0.01498
/*28 */     object_property_set_bool(OBJECT(cpu), true, "realized", &err);             // (2) 0.09363
/*32 */ out:                                                                           // (18) 0.007491
/*34 */     if (err) {                                                                 // (13) 0.02996
/*36 */         error_propagate(errp, err);                                            // (4) 0.06367
/*38 */         object_unref(OBJECT(cpu));                                             // (5) 0.06367
/*40 */         cpu = NULL;                                                            // (6) 0.0412
/*42 */     }                                                                          // (17) 0.01498
/*44 */     return cpu;                                                                // (14) 0.02247
/*46 */ }                                                                              // (20) 0.003745
