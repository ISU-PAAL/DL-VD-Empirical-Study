// commit message qemu@187337f8b0 (target=1, prob=0.99652356, correct=True): Fix off-by-one memory region sizes.
/*0  */ void pl011_init(uint32_t base, qemu_irq irq,                          // (7) 0.05469
/*2  */                 CharDriverState *chr)                                 // (6) 0.05729
/*4  */ {                                                                     // (20) 0.002604
/*6  */     int iomemtype;                                                    // (18) 0.02344
/*8  */     pl011_state *s;                                                   // (15) 0.02604
/*12 */     s = (pl011_state *)qemu_mallocz(sizeof(pl011_state));             // (3) 0.07031
/*14 */     iomemtype = cpu_register_io_memory(0, pl011_readfn,               // (4) 0.0625
/*16 */                                        pl011_writefn, s);             // (0) 0.1198
/*18 */     cpu_register_physical_memory(base, 0x00000fff, iomemtype);        // (5) 0.0599
/*20 */     s->base = base;                                                   // (16) 0.02344
/*22 */     s->irq = irq;                                                     // (13) 0.02865
/*24 */     s->chr = chr;                                                     // (14) 0.02865
/*26 */     s->read_trigger = 1;                                              // (12) 0.02865
/*28 */     s->ifl = 0x12;                                                    // (9) 0.03125
/*30 */     s->cr = 0x300;                                                    // (11) 0.02865
/*32 */     s->flags = 0x90;                                                  // (10) 0.02865
/*34 */     if (chr){                                                         // (17) 0.02344
/*36 */         qemu_chr_add_handlers(chr, pl011_can_recieve, pl011_recieve,  // (1) 0.09375
/*38 */                               pl011_event, s);                        // (2) 0.09375
/*40 */     }                                                                 // (19) 0.01042
/*42 */     /* ??? Save/restore.  */                                          // (8) 0.03125
/*44 */ }                                                                     // (21) 0.002604
