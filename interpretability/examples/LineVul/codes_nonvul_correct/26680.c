// commit message qemu@100f738850 (target=0, prob=0.45928213, correct=True): xics: pass appropriate types to realize() handlers.
/*0  */ static void ics_simple_realize(DeviceState *dev, Error **errp)               // (3) 0.1026
/*2  */ {                                                                            // (9) 0.005128
/*4  */     ICSState *ics = ICS_SIMPLE(dev);                                         // (5) 0.08718
/*8  */     if (!ics->nr_irqs) {                                                     // (6) 0.06667
/*10 */         error_setg(errp, "Number of interrupts needs to be greater 0");      // (2) 0.1282
/*12 */         return;                                                              // (7) 0.04615
/*14 */     }                                                                        // (8) 0.02051
/*16 */     ics->irqs = g_malloc0(ics->nr_irqs * sizeof(ICSIRQState));               // (1) 0.1487
/*18 */     ics->qirqs = qemu_allocate_irqs(ics_simple_set_irq, ics, ics->nr_irqs);  // (0) 0.2051
/*22 */     qemu_register_reset(ics_simple_reset, dev);                              // (4) 0.09744
/*24 */ }                                                                            // (10) 0.005128
