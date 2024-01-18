// commit message qemu@d85937e683 (target=0, prob=0.795607, correct=False): kvm/openpic: in-kernel mpic support
/*0  */ static qemu_irq *ppce500_init_mpic(PPCE500Params *params, MemoryRegion *ccsr,  // (2) 0.06327
/*2  */                                    qemu_irq **irqs)                            // (0) 0.0898
/*4  */ {                                                                              // (24) 0.002041
/*6  */     qemu_irq *mpic;                                                            // (15) 0.02653
/*8  */     DeviceState *dev;                                                          // (18) 0.01633
/*10 */     SysBusDevice *s;                                                           // (16) 0.02041
/*12 */     int i, j, k;                                                               // (17) 0.02041
/*16 */     mpic = g_new(qemu_irq, 256);                                               // (10) 0.03878
/*18 */     dev = qdev_create(NULL, "openpic");                                        // (11) 0.03265
/*20 */     qdev_prop_set_uint32(dev, "nb_cpus", smp_cpus);                            // (6) 0.0551
/*22 */     qdev_prop_set_uint32(dev, "model", params->mpic_version);                  // (8) 0.05102
/*24 */     qdev_init_nofail(dev);                                                     // (14) 0.02857
/*26 */     s = SYS_BUS_DEVICE(dev);                                                   // (13) 0.03061
/*30 */     k = 0;                                                                     // (20) 0.01429
/*32 */     for (i = 0; i < smp_cpus; i++) {                                           // (9) 0.04082
/*34 */         for (j = 0; j < OPENPIC_OUTPUT_NB; j++) {                              // (5) 0.05714
/*36 */             sysbus_connect_irq(s, k++, irqs[i][j]);                            // (3) 0.06327
/*38 */         }                                                                      // (19) 0.01633
/*40 */     }                                                                          // (22) 0.008163
/*44 */     for (i = 0; i < 256; i++) {                                                // (12) 0.03265
/*46 */         mpic[i] = qdev_get_gpio_in(dev, i);                                    // (7) 0.0551
/*48 */     }                                                                          // (23) 0.008163
/*52 */     memory_region_add_subregion(ccsr, MPC8544_MPIC_REGS_OFFSET,                // (4) 0.05918
/*54 */                                 s->mmio[0].memory);                            // (1) 0.08163
/*58 */     return mpic;                                                               // (21) 0.01429
/*60 */ }                                                                              // (25) 0.002041
