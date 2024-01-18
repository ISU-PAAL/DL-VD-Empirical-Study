// commit message qemu@187337f8b0 (target=1, prob=0.9947017, correct=True): Fix off-by-one memory region sizes.
/*0  */ void *pl080_init(uint32_t base, qemu_irq irq, int nchannels)    // (1) 0.1134
/*2  */ {                                                               // (12) 0.004202
/*4  */     int iomemtype;                                              // (10) 0.03782
/*6  */     pl080_state *s;                                             // (8) 0.04202
/*10 */     s = (pl080_state *)qemu_mallocz(sizeof(pl080_state));       // (2) 0.1134
/*12 */     iomemtype = cpu_register_io_memory(0, pl080_readfn,         // (3) 0.1008
/*14 */                                        pl080_writefn, s);       // (0) 0.1933
/*16 */     cpu_register_physical_memory(base, 0x00000fff, iomemtype);  // (4) 0.09664
/*18 */     s->base = base;                                             // (9) 0.03782
/*20 */     s->irq = irq;                                               // (7) 0.04622
/*22 */     s->nchannels = nchannels;                                   // (5) 0.05462
/*24 */     /* ??? Save/restore.  */                                    // (6) 0.05042
/*26 */     return s;                                                   // (11) 0.02521
/*28 */ }                                                               // (13) 0.004202
