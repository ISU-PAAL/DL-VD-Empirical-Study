// commit message qemu@9be385980d (target=0, prob=0.041453253, correct=True): coccinelle: Remove unnecessary variables for function return value
/*0  */ static int kvm_s390_register_io_adapter(S390FLICState *fs, uint32_t id,  // (3) 0.0676
/*2  */                                         uint8_t isc, bool swap,          // (0) 0.1142
/*4  */                                         bool is_maskable)                // (1) 0.1049
/*6  */ {                                                                        // (22) 0.002331
/*8  */     struct kvm_s390_io_adapter adapter = {                               // (8) 0.03963
/*10 */         .id = id,                                                        // (14) 0.02797
/*12 */         .isc = isc,                                                      // (11) 0.0303
/*14 */         .maskable = is_maskable,                                         // (9) 0.0373
/*16 */         .swap = swap,                                                    // (13) 0.0303
/*18 */     };                                                                   // (19) 0.009324
/*20 */     KVMS390FLICState *flic = KVM_S390_FLIC(fs);                          // (5) 0.05828
/*22 */     int r, ret;                                                          // (17) 0.01865
/*24 */     struct kvm_device_attr attr = {                                      // (10) 0.03263
/*26 */         .group = KVM_DEV_FLIC_ADAPTER_REGISTER,                          // (6) 0.05594
/*28 */         .addr = (uint64_t)&adapter,                                      // (7) 0.04662
/*30 */     };                                                                   // (20) 0.009324
/*34 */     if (!kvm_check_extension(kvm_state, KVM_CAP_IRQ_ROUTING)) {          // (2) 0.07226
/*36 */         /* nothing to do */                                              // (15) 0.02797
/*38 */         return 0;                                                        // (16) 0.02331
/*40 */     }                                                                    // (21) 0.009324
/*44 */     r = ioctl(flic->fd, KVM_SET_DEVICE_ATTR, &attr);                     // (4) 0.06294
/*48 */     ret = r ? -errno : 0;                                                // (12) 0.0303
/*50 */     return ret;                                                          // (18) 0.01399
/*52 */ }                                                                        // (23) 0.002331
