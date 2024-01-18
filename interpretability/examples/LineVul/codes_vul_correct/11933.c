// commit message qemu@efec3dd631 (target=1, prob=0.7613908, correct=True): qdev: Replace no_user by cannot_instantiate_with_device_add_yet
/*0  */ static void piix3_class_init(ObjectClass *klass, void *data)  // (7) 0.0692
/*2  */ {                                                             // (13) 0.00346
/*4  */     DeviceClass *dc = DEVICE_CLASS(klass);                    // (10) 0.05536
/*6  */     PCIDeviceClass *k = PCI_DEVICE_CLASS(klass);              // (6) 0.07266
/*10 */     dc->desc        = "ISA bridge";                           // (8) 0.06228
/*12 */     dc->vmsd        = &vmstate_piix3;                         // (2) 0.08304
/*14 */     dc->no_user     = 1,                                      // (11) 0.0519
/*16 */     k->no_hotplug   = 1;                                      // (12) 0.04844
/*18 */     k->init         = piix3_initfn;                           // (5) 0.07612
/*20 */     k->config_write = piix3_write_config;                     // (9) 0.05882
/*22 */     k->vendor_id    = PCI_VENDOR_ID_INTEL;                    // (3) 0.08304
/*24 */     /* 82371SB PIIX3 PCI-to-ISA bridge (Step A1) */           // (1) 0.08304
/*26 */     k->device_id    = PCI_DEVICE_ID_INTEL_82371SB_0;          // (0) 0.1003
/*28 */     k->class_id     = PCI_CLASS_BRIDGE_ISA;                   // (4) 0.07958
/*30 */ }                                                             // (14) 0.00346
