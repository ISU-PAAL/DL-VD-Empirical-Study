// commit message qemu@6977afda16 (target=1, prob=0.25867847, correct=False): ppc/kvm: check some capabilities with kvm_vm_check_extension()
/*0  */ int kvmppc_reset_htab(int shift_hint)                                       // (12) 0.0332
/*2  */ {                                                                           // (28) 0.001953
/*4  */     uint32_t shift = shift_hint;                                            // (16) 0.02734
/*8  */     if (!kvm_enabled()) {                                                   // (19) 0.02148
/*10 */         /* Full emulation, tell caller to allocate htab itself */           // (10) 0.03711
/*12 */         return 0;                                                           // (21) 0.01953
/*14 */     }                                                                       // (27) 0.007812
/*16 */     if (kvm_check_extension(kvm_state, KVM_CAP_PPC_ALLOC_HTAB)) {           // (1) 0.06641
/*18 */         int ret;                                                            // (22) 0.01953
/*20 */         ret = kvm_vm_ioctl(kvm_state, KVM_PPC_ALLOCATE_HTAB, &shift);       // (0) 0.07617
/*22 */         if (ret == -ENOTTY) {                                               // (14) 0.0332
/*24 */             /* At least some versions of PR KVM advertise the               // (5) 0.04297
/*26 */              * capability, but don't implement the ioctl().  Oops.          // (3) 0.05078
/*28 */              * Return 0 so that we allocate the htab in qemu, as is         // (2) 0.05664
/*30 */              * correct for PR. */                                           // (11) 0.03516
/*32 */             return 0;                                                       // (17) 0.02734
/*34 */         } else if (ret < 0) {                                               // (15) 0.03125
/*36 */             return ret;                                                     // (18) 0.02734
/*38 */         }                                                                   // (24) 0.01563
/*40 */         return shift;                                                       // (20) 0.01953
/*42 */     }                                                                       // (26) 0.007813
/*46 */     /* We have a kernel that predates the htab reset calls.  For PR         // (7) 0.03906
/*48 */      * KVM, we need to allocate the htab ourselves, for an HV KVM of        // (4) 0.04688
/*50 */      * this era, it has allocated a 16MB fixed size hash table already. */  // (6) 0.04102
/*52 */     if (kvmppc_is_pr(kvm_state)) {                                          // (8) 0.03906
/*54 */         /* PR - tell caller to allocate htab */                             // (13) 0.0332
/*56 */         return 0;                                                           // (23) 0.01953
/*58 */     } else {                                                                // (25) 0.01172
/*60 */         /* HV - assume 16MB kernel allocated htab */                        // (9) 0.03711
/*62 */         return 24;                                                          // 0.0
/*64 */     }                                                                       // 0.0
/*66 */ }                                                                           // 0.0
