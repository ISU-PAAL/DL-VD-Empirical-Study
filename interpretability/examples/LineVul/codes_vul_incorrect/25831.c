// commit message qemu@0280b3eb7c (target=1, prob=0.118978366, correct=False): s390x/kvm: use cpu model for gscb on compat machines
/*0  */ static void ccw_machine_2_9_class_options(MachineClass *mc)  // (2) 0.1493
/*2  */ {                                                            // (6) 0.007463
/*4  */     S390CcwMachineClass *s390mc = S390_MACHINE_CLASS(mc);    // (0) 0.194
/*8  */     s390mc->gs_allowed = false;                              // (5) 0.09701
/*10 */     ccw_machine_2_10_class_options(mc);                      // (3) 0.1343
/*12 */     SET_MACHINE_COMPAT(mc, CCW_COMPAT_2_9);                  // (1) 0.194
/*14 */     s390mc->css_migration_enabled = false;                   // (4) 0.1194
/*16 */ }                                                            // (7) 0.007463
