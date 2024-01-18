// commit message qemu@7839ff593b (target=1, prob=0.21498677, correct=False): pc: get rid of builtin pvpanic for "-M pc-1.5"
/*0  */ static void pc_compat_1_4(QEMUMachineInitArgs *args)                              // (2) 0.1471
/*2  */ {                                                                                 // (5) 0.007353
/*4  */     pc_compat_1_5(args);                                                          // (3) 0.1029
/*6  */     has_pvpanic = false;                                                          // (4) 0.08088
/*8  */     x86_cpu_compat_set_features("n270", FEAT_1_ECX, 0, CPUID_EXT_MOVBE);          // (1) 0.2721
/*10 */     x86_cpu_compat_set_features("Westmere", FEAT_1_ECX, 0, CPUID_EXT_PCLMULQDQ);  // (0) 0.3015
/*12 */ }                                                                                 // (6) 0.007353
