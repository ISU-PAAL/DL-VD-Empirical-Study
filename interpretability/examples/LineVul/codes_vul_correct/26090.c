// commit message qemu@e23a1b33b5 (target=1, prob=0.8481476, correct=True): New qdev_init_nofail()
/*0  */ static void slavio_misc_init(target_phys_addr_t base,                     // (9) 0.03711
/*2  */                              target_phys_addr_t aux1_base,                // (1) 0.07812
/*4  */                              target_phys_addr_t aux2_base, qemu_irq irq,  // (0) 0.0957
/*6  */                              qemu_irq fdc_tc)                             // (2) 0.07617
/*8  */ {                                                                         // (25) 0.001953
/*10 */     DeviceState *dev;                                                     // (22) 0.01563
/*12 */     SysBusDevice *s;                                                      // (20) 0.01953
/*16 */     dev = qdev_create(NULL, "slavio_misc");                               // (8) 0.03711
/*18 */     qdev_init(dev);                                                       // (21) 0.01953
/*20 */     s = sysbus_from_qdev(dev);                                            // (10) 0.0293
/*22 */     if (base) {                                                           // (23) 0.01562
/*24 */         /* 8 bit registers */                                             // (14) 0.02344
/*26 */         /* Slavio control */                                              // (12) 0.02344
/*28 */         sysbus_mmio_map(s, 0, base + MISC_CFG);                           // (4) 0.05273
/*30 */         /* Diagnostics */                                                 // (18) 0.02148
/*32 */         sysbus_mmio_map(s, 1, base + MISC_DIAG);                          // (3) 0.05469
/*34 */         /* Modem control */                                               // (13) 0.02344
/*36 */         sysbus_mmio_map(s, 2, base + MISC_MDM);                           // (5) 0.05273
/*38 */         /* 16 bit registers */                                            // (15) 0.02344
/*40 */         /* ss600mp diag LEDs */                                           // (11) 0.0293
/*42 */         sysbus_mmio_map(s, 3, base + MISC_LEDS);                          // (6) 0.05273
/*44 */         /* 32 bit registers */                                            // (16) 0.02344
/*46 */         /* System control */                                              // (19) 0.02148
/*48 */         sysbus_mmio_map(s, 4, base + MISC_SYS);                           // (7) 0.05273
/*50 */     }                                                                     // (24) 0.007812
/*52 */     if (aux1_base) {                                                      // (17) 0.02148
/*54 */         /* AUX 1 (Misc System Functions) */                               // 0.0
/*56 */         sysbus_mmio_map(s, 5, aux1_base);                                 // 0.0
/*58 */     }                                                                     // 0.0
/*60 */     if (aux2_base) {                                                      // 0.0
/*62 */         /* AUX 2 (Software Powerdown Control) */                          // 0.0
/*64 */         sysbus_mmio_map(s, 6, aux2_base);                                 // 0.0
/*66 */     }                                                                     // 0.0
/*68 */     sysbus_connect_irq(s, 0, irq);                                        // 0.0
/*70 */     sysbus_connect_irq(s, 1, fdc_tc);                                     // 0.0
/*72 */     qemu_system_powerdown = qdev_get_gpio_in(dev, 0);                     // 0.0
/*74 */ }                                                                         // 0.0
