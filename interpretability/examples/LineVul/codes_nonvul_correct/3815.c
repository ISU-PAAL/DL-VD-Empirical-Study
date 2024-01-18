// commit message qemu@2e84849aa2 (target=0, prob=0.03028971, correct=True): target-i386: Allow tsc-frequency to be larger then 2.147G
/*0  */ static void x86_cpuid_set_tsc_freq(Object *obj, Visitor *v, void *opaque,  // (2) 0.09836
/*2  */                                    const char *name, Error **errp)         // (0) 0.1443
/*4  */ {                                                                          // (16) 0.003279
/*6  */     X86CPU *cpu = X86_CPU(obj);                                            // (6) 0.05246
/*8  */     const int64_t min = 0;                                                 // (10) 0.03934
/*10 */     const int64_t max = INT_MAX;                                           // (8) 0.0459
/*12 */     int64_t value;                                                         // (11) 0.02951
/*16 */     visit_type_int(v, &value, name, errp);                                 // (4) 0.0623
/*18 */     if (error_is_set(errp)) {                                              // (7) 0.04918
/*20 */         return;                                                            // (12) 0.02951
/*22 */     }                                                                      // (14) 0.01311
/*24 */     if (value < min || value > max) {                                      // (9) 0.0459
/*26 */         error_set(errp, QERR_PROPERTY_VALUE_OUT_OF_RANGE, "",              // (1) 0.1082
/*28 */                   name ? name : "null", value, min, max);                  // (3) 0.09836
/*30 */         return;                                                            // (13) 0.02951
/*32 */     }                                                                      // (15) 0.01311
/*36 */     cpu->env.tsc_khz = value / 1000;                                       // (5) 0.05574
/*38 */ }                                                                          // (17) 0.003279
