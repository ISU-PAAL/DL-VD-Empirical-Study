// commit message qemu@10ee2aaa41 (target=0, prob=0.23307502, correct=True): Remove unneded ac97 indirection accessing its state
/*0  */ static void ac97_map (PCIDevice *pci_dev, int region_num,         // (13) 0.04297
/*2  */                       uint32_t addr, uint32_t size, int type)     // (0) 0.07031
/*4  */ {                                                                 // (20) 0.001953
/*6  */     PCIAC97LinkState *d = (PCIAC97LinkState *) pci_dev;           // (12) 0.04492
/*8  */     AC97LinkState *s = &d->ac97;                                  // (14) 0.03125
/*12 */     if (!region_num) {                                            // (17) 0.01953
/*14 */         s->base[0] = addr;                                        // (15) 0.03125
/*16 */         register_ioport_read (addr, 256 * 1, 1, nam_readb, d);    // (1) 0.05859
/*18 */         register_ioport_read (addr, 256 * 2, 2, nam_readw, d);    // (2) 0.05859
/*20 */         register_ioport_read (addr, 256 * 4, 4, nam_readl, d);    // (3) 0.05859
/*22 */         register_ioport_write (addr, 256 * 1, 1, nam_writeb, d);  // (4) 0.05859
/*24 */         register_ioport_write (addr, 256 * 2, 2, nam_writew, d);  // (5) 0.05859
/*26 */         register_ioport_write (addr, 256 * 4, 4, nam_writel, d);  // (6) 0.05859
/*28 */     }                                                             // (19) 0.007812
/*30 */     else {                                                        // (18) 0.009766
/*32 */         s->base[1] = addr;                                        // (16) 0.03125
/*34 */         register_ioport_read (addr, 64 * 1, 1, nabm_readb, d);    // (7) 0.05859
/*36 */         register_ioport_read (addr, 64 * 2, 2, nabm_readw, d);    // (8) 0.05859
/*38 */         register_ioport_read (addr, 64 * 4, 4, nabm_readl, d);    // (9) 0.05859
/*40 */         register_ioport_write (addr, 64 * 1, 1, nabm_writeb, d);  // (10) 0.05859
/*42 */         register_ioport_write (addr, 64 * 2, 2, nabm_writew, d);  // (11) 0.05859
/*44 */         register_ioport_write (addr, 64 * 4, 4, nabm_writel, d);  // 0.0
/*46 */     }                                                             // 0.0
/*48 */ }                                                                 // 0.0
