// commit message qemu@c34d440a72 (target=0, prob=0.041631587, correct=True): kvm: x86: Consolidate TCG and KVM MCE injection code
/*0  */ int kvm_arch_on_sigbus(int code, void *addr)                                    // (9) 0.03711
/*2  */ {                                                                               // (24) 0.001953
/*4  */ #ifdef KVM_CAP_MCE                                                              // (19) 0.01953
/*6  */     if ((first_cpu->mcg_cap & MCG_SER_P) && addr && code == BUS_MCEERR_AO) {    // (2) 0.07227
/*8  */         void *vaddr;                                                            // (16) 0.02344
/*10 */         ram_addr_t ram_addr;                                                    // (13) 0.03125
/*12 */         target_phys_addr_t paddr;                                               // (11) 0.0332
/*16 */         /* Hope we are lucky for AO MCE */                                      // (10) 0.03516
/*18 */         vaddr = addr;                                                           // (17) 0.02344
/*20 */         if (qemu_ram_addr_from_host(vaddr, &ram_addr) ||                        // (5) 0.05859
/*22 */             !kvm_physical_memory_addr_from_ram(first_cpu->kvm_state, ram_addr,  // (1) 0.07422
/*24 */                                                &paddr)) {                       // (0) 0.09961
/*26 */             fprintf(stderr, "Hardware memory error for memory used by "         // (6) 0.05273
/*28 */                     "QEMU itself instead of guest system!: %p\n", addr);        // (3) 0.07031
/*30 */             return 0;                                                           // (14) 0.02734
/*32 */         }                                                                       // (20) 0.01562
/*34 */         kvm_mce_inj_srao_memscrub2(first_cpu, paddr);                           // (4) 0.0625
/*36 */     } else                                                                      // (22) 0.009766
/*38 */ #endif /* KVM_CAP_MCE */                                                        // (18) 0.02148
/*40 */     {                                                                           // (23) 0.007812
/*42 */         if (code == BUS_MCEERR_AO) {                                            // (8) 0.04297
/*44 */             return 0;                                                           // (15) 0.02734
/*46 */         } else if (code == BUS_MCEERR_AR) {                                     // (7) 0.04492
/*48 */             hardware_memory_error();                                            // (12) 0.0332
/*50 */         } else {                                                                // 0.0
/*52 */             return 1;                                                           // 0.0
/*54 */         }                                                                       // (21) 0.01562
/*56 */     }                                                                           // 0.0
/*58 */     return 0;                                                                   // 0.0
/*60 */ }                                                                               // 0.0
