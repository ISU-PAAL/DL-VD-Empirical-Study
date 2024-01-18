// commit message qemu@efec3dd631 (target=1, prob=0.9782453, correct=True): qdev: Replace no_user by cannot_instantiate_with_device_add_yet
/*0  */ static void arm_mptimer_class_init(ObjectClass *klass, void *data)  // (0) 0.1667
/*2  */ {                                                                   // (7) 0.007576
/*4  */     DeviceClass *dc = DEVICE_CLASS(klass);                          // (3) 0.1212
/*8  */     dc->realize = arm_mptimer_realize;                              // (2) 0.1288
/*10 */     dc->vmsd = &vmstate_arm_mptimer;                                // (1) 0.1439
/*12 */     dc->reset = arm_mptimer_reset;                                  // (5) 0.1136
/*14 */     dc->no_user = 1;                                                // (6) 0.08333
/*16 */     dc->props = arm_mptimer_properties;                             // (4) 0.1212
/*18 */ }                                                                   // (8) 0.007576
