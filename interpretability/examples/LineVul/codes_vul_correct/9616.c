// commit message qemu@603987488c (target=1, prob=0.6535251, correct=True): PPC64: Partial fix to Linux crash: revert to old devfn
/*0  */ PCIBus *pci_pmac_init(qemu_irq *pic)                                             // (6) 0.04102
/*2  */ {                                                                                // (26) 0.001953
/*4  */     DeviceState *dev;                                                            // (22) 0.01563
/*6  */     SysBusDevice *s;                                                             // (17) 0.01953
/*8  */     UNINState *d;                                                                // (21) 0.01758
/*12 */     /* Use values found on a real PowerMac */                                    // (14) 0.02539
/*14 */     /* Uninorth main bus */                                                      // (18) 0.01953
/*16 */     dev = qdev_create(NULL, "Uni-north main");                                   // (9) 0.03711
/*18 */     qdev_init_nofail(dev);                                                       // (13) 0.02734
/*20 */     s = sysbus_from_qdev(dev);                                                   // (12) 0.0293
/*22 */     d = FROM_SYSBUS(UNINState, s);                                               // (11) 0.0332
/*24 */     d->host_state.bus = pci_register_bus(&d->busdev.qdev, "pci",                 // (2) 0.05664
/*26 */                                          pci_unin_set_irq, pci_unin_map_irq,     // (0) 0.1133
/*28 */                                          pic, 11 << 3, 4);                       // (1) 0.09375
/*32 */     pci_create_simple(d->host_state.bus, 11 << 3, "Uni-north main");             // (4) 0.05469
/*36 */     sysbus_mmio_map(s, 0, 0xf2800000);                                           // (8) 0.03906
/*38 */     sysbus_mmio_map(s, 1, 0xf2c00000);                                           // (7) 0.04102
/*42 */     /* DEC 21154 bridge */                                                       // (20) 0.01758
/*44 */ #if 0                                                                            // (23) 0.005859
/*46 */     /* XXX: not activated as PPC BIOS doesn't handle multiple buses properly */  // (10) 0.03711
/*48 */     pci_create_simple(d->host_state.bus, 12 << 3, "DEC 21154");                  // (5) 0.05078
/*50 */ #endif                                                                           // (25) 0.003906
/*54 */     /* Uninorth AGP bus */                                                       // (15) 0.02148
/*56 */     pci_create_simple(d->host_state.bus, 13 << 3, "Uni-north AGP");              // (3) 0.05664
/*60 */     /* Uninorth internal bus */                                                  // (19) 0.01953
/*62 */ #if 0                                                                            // (24) 0.005859
/*64 */     /* XXX: not needed for now */                                                // (16) 0.02148
/*66 */     pci_create_simple(d->host_state.bus, 14 << 3, "Uni-north internal");         // 0.0
/*68 */ #endif                                                                           // 0.0
/*72 */     return d->host_state.bus;                                                    // 0.0
/*74 */ }                                                                                // 0.0
