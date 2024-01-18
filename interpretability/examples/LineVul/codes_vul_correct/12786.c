// commit message qemu@280503ee9d (target=1, prob=0.7327875, correct=True): hw/nvram/spapr_nvram: Device can not be created by the users
/*0  */ static void spapr_nvram_class_init(ObjectClass *klass, void *data)  // (1) 0.09957
/*2  */ {                                                                   // (12) 0.004329
/*4  */     DeviceClass *dc = DEVICE_CLASS(klass);                          // (8) 0.06926
/*6  */     VIOsPAPRDeviceClass *k = VIO_SPAPR_DEVICE_CLASS(klass);         // (0) 0.1255
/*10 */     k->realize = spapr_nvram_realize;                               // (5) 0.07792
/*12 */     k->devnode = spapr_nvram_devnode;                               // (6) 0.07792
/*14 */     k->dt_name = "nvram";                                           // (10) 0.05628
/*16 */     k->dt_type = "nvram";                                           // (9) 0.05628
/*18 */     k->dt_compatible = "qemu,spapr-nvram";                          // (3) 0.09091
/*20 */     set_bit(DEVICE_CATEGORY_MISC, dc->categories);                  // (2) 0.09957
/*22 */     dc->props = spapr_nvram_properties;                             // (7) 0.07359
/*24 */     dc->vmsd = &vmstate_spapr_nvram;                                // (4) 0.08658
/*28 */ }                                                                   // (11) 0.004329
