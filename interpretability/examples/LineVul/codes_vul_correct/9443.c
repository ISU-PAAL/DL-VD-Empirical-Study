// commit message qemu@e23a1b33b5 (target=1, prob=0.96537524, correct=True): New qdev_init_nofail()
/*0  */ static void ram_init(target_phys_addr_t addr, ram_addr_t RAM_size)  // (0) 0.1472
/*2  */ {                                                                   // (11) 0.006135
/*4  */     DeviceState *dev;                                               // (8) 0.04908
/*6  */     SysBusDevice *s;                                                // (6) 0.06135
/*8  */     RamDevice *d;                                                   // (9) 0.04908
/*12 */     /* allocate RAM */                                              // (10) 0.04294
/*14 */     dev = qdev_create(NULL, "memory");                              // (3) 0.09202
/*16 */     s = sysbus_from_qdev(dev);                                      // (4) 0.09202
/*20 */     d = FROM_SYSBUS(RamDevice, s);                                  // (2) 0.09816
/*22 */     d->size = RAM_size;                                             // (5) 0.06748
/*24 */     qdev_init(dev);                                                 // (7) 0.06135
/*28 */     sysbus_mmio_map(s, 0, addr);                                    // (1) 0.1043
/*30 */ }                                                                   // (12) 0.006135
