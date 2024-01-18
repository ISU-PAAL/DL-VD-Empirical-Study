// commit message qemu@07caea315a (target=1, prob=0.8607244, correct=True): Fix pci_add nic not to exit on bad model
/*0  */ PCIDevice *pci_nic_init(NICInfo *nd, const char *default_model,         // (3) 0.09294
/*2  */                         const char *default_devaddr)                    // (0) 0.1152
/*4  */ {                                                                       // (15) 0.003717
/*6  */     const char *devaddr = nd->devaddr ? nd->devaddr : default_devaddr;  // (2) 0.09665
/*8  */     PCIDevice *pci_dev;                                                 // (7) 0.04833
/*10 */     DeviceState *dev;                                                   // (12) 0.02974
/*12 */     int i;                                                              // (14) 0.0223
/*16 */     i = qemu_check_nic_model_list(nd, pci_nic_models, default_model);   // (1) 0.1078
/*18 */     pci_dev = pci_create(pci_nic_names[i], devaddr);                    // (4) 0.0855
/*20 */     dev = &pci_dev->qdev;                                               // (6) 0.05204
/*22 */     if (nd->id)                                                         // (11) 0.03346
/*24 */         dev->id = qemu_strdup(nd->id);                                  // (5) 0.0855
/*26 */     dev->nd = nd;                                                       // (8) 0.03717
/*28 */     qdev_init(dev);                                                     // (9) 0.03717
/*30 */     nd->private = dev;                                                  // (10) 0.03717
/*32 */     return pci_dev;                                                     // (13) 0.02974
/*34 */ }                                                                       // (16) 0.003717
