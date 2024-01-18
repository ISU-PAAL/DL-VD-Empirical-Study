// commit message qemu@a80bf99fa3 (target=1, prob=0.8279372, correct=True): char-mux: Use separate input buffers (Jan Kiszka)
/*0  */ static int mux_chr_can_read(void *opaque)                               // (3) 0.1111
/*2  */ {                                                                       // (8) 0.006536
/*4  */     CharDriverState *chr = opaque;                                      // (5) 0.07843
/*6  */     MuxDriver *d = chr->opaque;                                         // (4) 0.09804
/*10 */     if ((d->prod - d->cons) < MUX_BUFFER_SIZE)                          // (1) 0.1503
/*12 */         return 1;                                                       // (6) 0.06536
/*14 */     if (d->chr_can_read[chr->focus])                                    // (2) 0.1242
/*16 */         return d->chr_can_read[chr->focus](d->ext_opaque[chr->focus]);  // (0) 0.2222
/*18 */     return 0;                                                           // (7) 0.03922
/*20 */ }                                                                       // (9) 0.006536
