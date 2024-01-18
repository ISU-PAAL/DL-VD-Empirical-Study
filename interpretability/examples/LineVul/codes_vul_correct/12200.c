// commit message qemu@f8ed85ac99 (target=1, prob=0.8520541, correct=True): Fix bad error handling after memory_region_init_ram()
/*0  */ static int ram_init1(SysBusDevice *dev)                               // (5) 0.08784
/*2  */ {                                                                     // (7) 0.006757
/*4  */     RamDevice *d = SUN4U_RAM(dev);                                    // (3) 0.1081
/*8  */     memory_region_init_ram(&d->ram, OBJECT(d), "sun4u.ram", d->size,  // (1) 0.2095
/*10 */                            &error_abort);                             // (0) 0.2162
/*12 */     vmstate_register_ram_global(&d->ram);                             // (4) 0.1081
/*14 */     sysbus_init_mmio(dev, &d->ram);                                   // (2) 0.1216
/*16 */     return 0;                                                         // (6) 0.04054
/*18 */ }                                                                     // (8) 0.006757
