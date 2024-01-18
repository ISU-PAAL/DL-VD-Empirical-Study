// commit message qemu@7ebaf79556 (target=0, prob=0.031219551, correct=True): spapr: Introduce sPAPRCPUCoreClass
/*0  */ static void spapr_cpu_core_host_initfn(Object *obj)                // (2) 0.1387
/*2  */ {                                                                  // (7) 0.007299
/*4  */     sPAPRCPUCore *core = SPAPR_CPU_CORE(obj);                      // (1) 0.1679
/*6  */     char *name = g_strdup_printf("%s-" TYPE_POWERPC_CPU, "host");  // (0) 0.2117
/*8  */     ObjectClass *oc = object_class_by_name(name);                  // (3) 0.1314
/*12 */     g_assert(oc);                                                  // (6) 0.06569
/*14 */     g_free((void *)name);                                          // (5) 0.08029
/*16 */     core->cpu_class = oc;                                          // (4) 0.08759
/*18 */ }                                                                  // (8) 0.007299
