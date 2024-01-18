// commit message qemu@c34d440a72 (target=0, prob=0.011256198, correct=True): kvm: x86: Consolidate TCG and KVM MCE injection code
/*0  */ static void kvm_mce_inj_srao_memscrub2(CPUState *env, target_phys_addr_t paddr)  // (1) 0.1151
/*2  */ {                                                                                // (12) 0.003289
/*4  */     struct kvm_x86_mce mce = {                                                   // (7) 0.05263
/*6  */         .bank = 9,                                                               // (10) 0.03947
/*8  */         .status = MCI_STATUS_VAL | MCI_STATUS_UC | MCI_STATUS_EN                 // (2) 0.1086
/*10 */                   | MCI_STATUS_MISCV | MCI_STATUS_ADDRV | MCI_STATUS_S           // (0) 0.148
/*12 */                   | 0xc0,                                                        // (6) 0.07237
/*14 */         .mcg_status = MCG_STATUS_MCIP | MCG_STATUS_RIPV,                         // (3) 0.102
/*16 */         .addr = paddr,                                                           // (9) 0.04276
/*18 */         .misc = (MCM_ADDR_PHYS << 6) | 0xc,                                      // (5) 0.08553
/*20 */     };                                                                           // (11) 0.01316
/*24 */     kvm_inject_x86_mce_on(env, &mce, ABORT_ON_ERROR);                            // (4) 0.09868
/*26 */     kvm_mce_broadcast_rest(env);                                                 // (8) 0.05263
/*28 */ }                                                                                // (13) 0.003289
