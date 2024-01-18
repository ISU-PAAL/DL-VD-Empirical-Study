// commit message qemu@a8170e5e97 (target=0, prob=0.5463893, correct=False): Rename target_phys_addr_t to hwaddr
/*0  */ void esp_init(target_phys_addr_t espaddr, int it_shift,                       // (8) 0.04202
/*2  */               ESPDMAMemoryReadWriteFunc dma_memory_read,                      // (1) 0.06092
/*4  */               ESPDMAMemoryReadWriteFunc dma_memory_write,                     // (2) 0.06092
/*6  */               void *dma_opaque, qemu_irq irq, qemu_irq *reset,                // (0) 0.08193
/*8  */               qemu_irq *dma_enable)                                           // (4) 0.05252
/*10 */ {                                                                             // (25) 0.002101
/*12 */     DeviceState *dev;                                                         // (22) 0.01681
/*14 */     SysBusDevice *s;                                                          // (21) 0.02101
/*16 */     SysBusESPState *sysbus;                                                   // (18) 0.02731
/*18 */     ESPState *esp;                                                            // (23) 0.01681
/*22 */     dev = qdev_create(NULL, "esp");                                           // (15) 0.03151
/*24 */     sysbus = DO_UPCAST(SysBusESPState, busdev.qdev, dev);                     // (3) 0.05462
/*26 */     esp = &sysbus->esp;                                                       // (20) 0.02311
/*28 */     esp->dma_memory_read = dma_memory_read;                                   // (9) 0.03992
/*30 */     esp->dma_memory_write = dma_memory_write;                                 // (10) 0.03992
/*32 */     esp->dma_opaque = dma_opaque;                                             // (13) 0.03571
/*34 */     sysbus->it_shift = it_shift;                                              // (17) 0.02941
/*36 */     /* XXX for now until rc4030 has been changed to use DMA enable signal */  // (6) 0.04412
/*38 */     esp->dma_enabled = 1;                                                     // (19) 0.02521
/*40 */     qdev_init_nofail(dev);                                                    // (16) 0.02941
/*42 */     s = sysbus_from_qdev(dev);                                                // (14) 0.03151
/*44 */     sysbus_connect_irq(s, 0, irq);                                            // (11) 0.03782
/*46 */     sysbus_mmio_map(s, 0, espaddr);                                           // (12) 0.03781
/*48 */     *reset = qdev_get_gpio_in(dev, 0);                                        // (7) 0.04202
/*50 */     *dma_enable = qdev_get_gpio_in(dev, 1);                                   // (5) 0.04832
/*52 */ }                                                                             // (24) 0.002101
