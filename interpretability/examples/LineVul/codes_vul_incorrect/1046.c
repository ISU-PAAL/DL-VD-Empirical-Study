// commit message qemu@00f4d64ee7 (target=1, prob=0.1835538, correct=False): kvmclock: clock should count only if vm is running
/*0  */ static void kvmclock_pre_save(void *opaque)                                     // (5) 0.05357
/*2  */ {                                                                               // (19) 0.003571
/*4  */     KVMClockState *s = opaque;                                                  // (7) 0.04286
/*6  */     struct kvm_clock_data data;                                                 // (8) 0.04286
/*8  */     int ret;                                                                    // (14) 0.02143
/*12 */     if (s->clock_valid) {                                                       // (9) 0.04286
/*14 */         return;                                                                 // (13) 0.03214
/*16 */     }                                                                           // (16) 0.01429
/*18 */     ret = kvm_vm_ioctl(kvm_state, KVM_GET_CLOCK, &data);                        // (1) 0.1036
/*20 */     if (ret < 0) {                                                              // (12) 0.03571
/*22 */         fprintf(stderr, "KVM_GET_CLOCK failed: %s\n", strerror(ret));           // (0) 0.125
/*24 */         data.clock = 0;                                                         // (6) 0.04643
/*26 */     }                                                                           // (17) 0.01429
/*28 */     s->clock = data.clock;                                                      // (10) 0.03929
/*30 */     /*                                                                          // (18) 0.01429
/*32 */      * If the VM is stopped, declare the clock state valid to avoid re-reading  // (3) 0.075
/*34 */      * it on next vmsave (which would return a different value). Will be reset  // (2) 0.07857
/*36 */      * when the VM is continued.                                                // (11) 0.03929
/*38 */      */                                                                         // (15) 0.01786
/*40 */     s->clock_valid = !runstate_is_running();                                    // (4) 0.06071
/*42 */ }                                                                               // (20) 0.003571
