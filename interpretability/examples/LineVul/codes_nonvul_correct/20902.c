// commit message qemu@7a0e58fa64 (target=0, prob=0.13601214, correct=True): target-arm: Split NO_MIGRATE into ALIAS and NO_RAW
/*0  */ static void add_cpreg_to_list(gpointer key, gpointer opaque)                 // (3) 0.08756
/*2  */ {                                                                            // (11) 0.004608
/*4  */     ARMCPU *cpu = opaque;                                                    // (8) 0.05069
/*6  */     uint64_t regidx;                                                         // (9) 0.05069
/*8  */     const ARMCPRegInfo *ri;                                                  // (7) 0.0553
/*12 */     regidx = *(uint32_t *)key;                                               // (5) 0.07373
/*14 */     ri = get_arm_cp_reginfo(cpu->cp_regs, regidx);                           // (1) 0.1244
/*18 */     if (!(ri->type & ARM_CP_NO_MIGRATE)) {                                   // (2) 0.1014
/*20 */         cpu->cpreg_indexes[cpu->cpreg_array_len] = cpreg_to_kvm_id(regidx);  // (0) 0.1797
/*22 */         /* The value array need not be initialized at this point */          // (4) 0.08756
/*24 */         cpu->cpreg_array_len++;                                              // (6) 0.07373
/*26 */     }                                                                        // (10) 0.01843
/*28 */ }                                                                            // (12) 0.004608
