// commit message qemu@efec3dd631 (target=1, prob=0.9885932, correct=True): qdev: Replace no_user by cannot_instantiate_with_device_add_yet
/*0  */ static void bonito_pcihost_class_init(ObjectClass *klass, void *data)  // (1) 0.219
/*2  */ {                                                                      // (5) 0.009524
/*4  */     DeviceClass *dc = DEVICE_CLASS(klass);                             // (3) 0.1524
/*6  */     SysBusDeviceClass *k = SYS_BUS_DEVICE_CLASS(klass);                // (0) 0.2286
/*10 */     k->init = bonito_pcihost_initfn;                                   // (2) 0.1619
/*12 */     dc->no_user = 1;                                                   // (4) 0.1048
/*14 */ }                                                                      // (6) 0.009524
