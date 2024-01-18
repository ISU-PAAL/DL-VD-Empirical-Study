// commit message qemu@a8170e5e97 (target=0, prob=0.61984026, correct=False): Rename target_phys_addr_t to hwaddr
/*0  */ MemoryRegion *escc_init(target_phys_addr_t base, qemu_irq irqA, qemu_irq irqB,  // (0) 0.08333
/*2  */               CharDriverState *chrA, CharDriverState *chrB,                     // (1) 0.06532
/*4  */               int clock, int it_shift)                                          // (8) 0.0473
/*6  */ {                                                                               // (23) 0.002252
/*8  */     DeviceState *dev;                                                           // (19) 0.01802
/*10 */     SysBusDevice *s;                                                            // (17) 0.02252
/*12 */     SerialState *d;                                                             // (20) 0.01802
/*16 */     dev = qdev_create(NULL, "escc");                                            // (14) 0.03604
/*18 */     qdev_prop_set_uint32(dev, "disabled", 0);                                   // (10) 0.04504
/*20 */     qdev_prop_set_uint32(dev, "frequency", clock);                              // (9) 0.04504
/*22 */     qdev_prop_set_uint32(dev, "it_shift", it_shift);                            // (2) 0.05405
/*24 */     qdev_prop_set_chr(dev, "chrB", chrB);                                       // (3) 0.05405
/*26 */     qdev_prop_set_chr(dev, "chrA", chrA);                                       // (4) 0.05405
/*28 */     qdev_prop_set_uint32(dev, "chnBtype", ser);                                 // (5) 0.04955
/*30 */     qdev_prop_set_uint32(dev, "chnAtype", ser);                                 // (6) 0.04955
/*32 */     qdev_init_nofail(dev);                                                      // (16) 0.03153
/*34 */     s = sysbus_from_qdev(dev);                                                  // (15) 0.03378
/*36 */     sysbus_connect_irq(s, 0, irqB);                                             // (12) 0.04279
/*38 */     sysbus_connect_irq(s, 1, irqA);                                             // (11) 0.04279
/*40 */     if (base) {                                                                 // (21) 0.01802
/*42 */         sysbus_mmio_map(s, 0, base);                                            // (7) 0.0473
/*44 */     }                                                                           // (22) 0.009009
/*48 */     d = FROM_SYSBUS(SerialState, s);                                            // (13) 0.03604
/*50 */     return &d->mmio;                                                            // (18) 0.02252
/*52 */ }                                                                               // (24) 0.002252
