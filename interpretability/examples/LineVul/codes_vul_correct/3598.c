// commit message qemu@efec3dd631 (target=1, prob=0.83923763, correct=True): qdev: Replace no_user by cannot_instantiate_with_device_add_yet
/*0  */ static void raven_class_init(ObjectClass *klass, void *data)  // (4) 0.08531
/*2  */ {                                                             // (11) 0.004739
/*4  */     PCIDeviceClass *k = PCI_DEVICE_CLASS(klass);              // (2) 0.09953
/*6  */     DeviceClass *dc = DEVICE_CLASS(klass);                    // (6) 0.07583
/*10 */     k->init = raven_init;                                     // (10) 0.05213
/*12 */     k->vendor_id = PCI_VENDOR_ID_MOTOROLA;                    // (1) 0.1137
/*14 */     k->device_id = PCI_DEVICE_ID_MOTOROLA_RAVEN;              // (0) 0.1185
/*16 */     k->revision = 0x00;                                       // (8) 0.05687
/*18 */     k->class_id = PCI_CLASS_BRIDGE_HOST;                      // (3) 0.09479
/*20 */     dc->desc = "PReP Host Bridge - Motorola Raven";           // (5) 0.08057
/*22 */     dc->vmsd = &vmstate_raven;                                // (7) 0.07583
/*24 */     dc->no_user = 1;                                          // (9) 0.05213
/*26 */ }                                                             // (12) 0.004739
