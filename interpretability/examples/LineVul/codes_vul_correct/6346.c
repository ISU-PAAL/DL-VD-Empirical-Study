// commit message qemu@2f295167e0 (target=1, prob=0.744248, correct=True): q35/mch: implement extended TSEG sizes
/*0  */ static void q35_host_class_init(ObjectClass *klass, void *data)  // (3) 0.104
/*2  */ {                                                                // (10) 0.00495
/*4  */     DeviceClass *dc = DEVICE_CLASS(klass);                       // (5) 0.07921
/*6  */     PCIHostBridgeClass *hc = PCI_HOST_BRIDGE_CLASS(klass);       // (0) 0.1238
/*10 */     hc->root_bus_path = q35_host_root_bus_path;                  // (2) 0.1139
/*12 */     dc->realize = q35_host_realize;                              // (6) 0.07921
/*14 */     dc->props = mch_props;                                       // (7) 0.06931
/*16 */     /* Reason: needs to be wired up by pc_q35_init */            // (4) 0.09406
/*18 */     dc->user_creatable = false;                                  // (9) 0.05941
/*20 */     set_bit(DEVICE_CATEGORY_BRIDGE, dc->categories);             // (1) 0.1188
/*22 */     dc->fw_name = "pci";                                         // (8) 0.06436
/*24 */ }                                                                // (11) 0.00495
