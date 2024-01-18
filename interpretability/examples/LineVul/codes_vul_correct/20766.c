// commit message qemu@e23a1b33b5 (target=1, prob=0.93396664, correct=True): New qdev_init_nofail()
/*0  */ static void ecc_init(target_phys_addr_t base, qemu_irq irq, uint32_t version)  // (0) 0.1415
/*2  */ {                                                                              // (12) 0.004717
/*4  */     DeviceState *dev;                                                          // (10) 0.03774
/*6  */     SysBusDevice *s;                                                           // (8) 0.04717
/*10 */     dev = qdev_create(NULL, "eccmemctl");                                      // (3) 0.08491
/*12 */     qdev_prop_set_uint32(dev, "version", version);                             // (2) 0.09434
/*14 */     qdev_init(dev);                                                            // (9) 0.04717
/*16 */     s = sysbus_from_qdev(dev);                                                 // (7) 0.07075
/*18 */     sysbus_connect_irq(s, 0, irq);                                             // (4) 0.08491
/*20 */     sysbus_mmio_map(s, 0, base);                                               // (5) 0.08019
/*22 */     if (version == 0) { // SS-600MP only                                       // (6) 0.07547
/*24 */         sysbus_mmio_map(s, 1, base + 0x1000);                                  // (1) 0.1179
/*26 */     }                                                                          // (11) 0.01887
/*28 */ }                                                                              // (13) 0.004717
