// commit message qemu@97679527bf (target=1, prob=0.5503574, correct=True): Fix overflow in i440fx_init()
/*0  */ PCIBus *i440fx_init(PCII440FXState **pi440fx_state, int *piix3_devfn, qemu_irq *pic, int ram_size)  // (1) 0.09018
/*2  */ {                                                                                                   // (24) 0.002004
/*4  */     DeviceState *dev;                                                                               // (22) 0.01603
/*6  */     PCIBus *b;                                                                                      // (20) 0.01804
/*8  */     PCIDevice *d;                                                                                   // (18) 0.02004
/*10 */     I440FXState *s;                                                                                 // (19) 0.02004
/*12 */     PIIX3State *piix3;                                                                              // (14) 0.02605
/*16 */     dev = qdev_create(NULL, "i440FX-pcihost");                                                      // (7) 0.04208
/*18 */     s = FROM_SYSBUS(I440FXState, sysbus_from_qdev(dev));                                            // (3) 0.0521
/*20 */     b = pci_bus_new(&s->busdev.qdev, NULL, 0);                                                      // (6) 0.04609
/*22 */     s->bus = b;                                                                                     // (21) 0.01804
/*24 */     qdev_init_nofail(dev);                                                                          // (13) 0.02806
/*28 */     d = pci_create_simple(b, 0, "i440FX");                                                          // (10) 0.04008
/*30 */     *pi440fx_state = DO_UPCAST(PCII440FXState, dev, d);                                             // (4) 0.0521
/*34 */     piix3 = DO_UPCAST(PIIX3State, dev,                                                              // (8) 0.04208
/*36 */                                  pci_create_simple(b, -1, "PIIX3"));                                // (0) 0.1002
/*38 */     piix3->pic = pic;                                                                               // (16) 0.02204
/*40 */     pci_bus_irqs(b, piix3_set_irq, pci_slot_get_pirq, piix3, 4);                                    // (2) 0.07214
/*42 */     (*pi440fx_state)->piix3 = piix3;                                                                // (11) 0.03808
/*46 */     *piix3_devfn = piix3->dev.devfn;                                                                // (9) 0.04008
/*50 */     ram_size = ram_size / 8 / 1024 / 1024;                                                          // (12) 0.03407
/*52 */     if (ram_size > 255)                                                                             // (17) 0.02204
/*54 */         ram_size = 255;                                                                             // (15) 0.02605
/*56 */     (*pi440fx_state)->dev.config[0x57]=ram_size;                                                    // (5) 0.04609
/*60 */     return b;                                                                                       // (23) 0.01202
/*62 */ }                                                                                                   // (25) 0.002004
