// commit message qemu@049a9f7b94 (target=1, prob=0.42692235, correct=False): i82378/i82374: Do not create DMA controller twice
/*0  */ static void i82378_init(DeviceState *dev, I82378State *s)                        // (4) 0.04297
/*2  */ {                                                                                // (28) 0.001953
/*4  */     ISABus *isabus = DO_UPCAST(ISABus, qbus, qdev_get_child_bus(dev, "isa.0"));  // (0) 0.07812
/*6  */     ISADevice *pit;                                                              // (22) 0.01953
/*8  */     qemu_irq *out0_irq;                                                          // (12) 0.03125
/*12 */     /* This device has:                                                          // (23) 0.01562
/*14 */        2 82C59 (irq)                                                             // (14) 0.02734
/*16 */        1 82C54 (pit)                                                             // (17) 0.02539
/*18 */        2 82C37 (dma)                                                             // (15) 0.02734
/*20 */        NMI                                                                       // (24) 0.01562
/*22 */        Utility Bus Support Registers                                             // (21) 0.02148
/*26 */        All devices accept byte access only, except timer                         // (13) 0.0293
/*28 */      */                                                                          // (27) 0.009766
/*32 */     qdev_init_gpio_out(dev, s->out, 2);                                          // (5) 0.04102
/*34 */     qdev_init_gpio_in(dev, i82378_request_pic_irq, 16);                          // (2) 0.05664
/*38 */     /* Workaround the fact that i8259 is not qdev'ified... */                    // (7) 0.03906
/*40 */     out0_irq = qemu_allocate_irqs(i82378_request_out0_irq, s, 1);                // (1) 0.07031
/*44 */     /* 2 82C59 (irq) */                                                          // (18) 0.02539
/*46 */     s->i8259 = i8259_init(isabus, *out0_irq);                                    // (3) 0.04883
/*48 */     isa_bus_irqs(isabus, s->i8259);                                              // (8) 0.03906
/*52 */     /* 1 82C54 (pit) */                                                          // (20) 0.02344
/*54 */     pit = pit_init(isabus, 0x40, 0, NULL);                                       // (9) 0.03906
/*58 */     /* speaker */                                                                // (25) 0.01172
/*60 */     pcspk_init(isabus, pit);                                                     // (16) 0.02734
/*64 */     /* 2 82C37 (dma) */                                                          // (19) 0.02539
/*66 */     DMA_init(1, &s->out[1]);                                                     // (11) 0.0332
/*68 */     isa_create_simple(isabus, "i82374");                                         // (10) 0.03711
/*72 */     /* timer */                                                                  // (26) 0.01172
/*74 */     isa_create_simple(isabus, "mc146818rtc");                                    // (6) 0.04102
/*76 */ }                                                                                // (29) 0.001953
