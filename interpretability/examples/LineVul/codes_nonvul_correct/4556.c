// commit message qemu@a8170e5e97 (target=0, prob=0.010580757, correct=True): Rename target_phys_addr_t to hwaddr
/*0  */ static uint64_t imx_timerg_read(void *opaque, target_phys_addr_t offset,  // (1) 0.05378
/*2  */                                 unsigned size)                            // (0) 0.06773
/*4  */ {                                                                         // (28) 0.001992
/*6  */     IMXTimerGState *s = (IMXTimerGState *)opaque;                         // (9) 0.04183
/*10 */     DPRINTF("g-read(offset=%x)", offset >> 2);                            // (10) 0.03984
/*12 */     switch (offset >> 2) {                                                // (23) 0.01992
/*14 */     case 0: /* Control Register */                                        // (24) 0.01992
/*16 */         DPRINTF(" cr = %x\n", s->cr);                                     // (5) 0.04382
/*18 */         return s->cr;                                                     // (16) 0.0239
/*22 */     case 1: /* prescaler */                                               // (20) 0.02191
/*24 */         DPRINTF(" pr = %x\n", s->pr);                                     // (6) 0.04382
/*26 */         return s->pr;                                                     // (17) 0.0239
/*30 */     case 2: /* Status Register */                                         // (25) 0.01992
/*32 */         DPRINTF(" sr = %x\n", s->sr);                                     // (7) 0.04382
/*34 */         return s->sr;                                                     // (18) 0.0239
/*38 */     case 3: /* Interrupt Register */                                      // (21) 0.02191
/*40 */         DPRINTF(" ir = %x\n", s->ir);                                     // (8) 0.04382
/*42 */         return s->ir;                                                     // (19) 0.0239
/*46 */     case 4: /* Output Compare Register 1 */                               // (15) 0.0239
/*48 */         DPRINTF(" ocr1 = %x\n", s->ocr1);                                 // (2) 0.0498
/*50 */         return s->ocr1;                                                   // (13) 0.0259
/*56 */     case 9: /* cnt */                                                     // (22) 0.01992
/*58 */         imx_timerg_update_counts(s);                                      // (11) 0.03984
/*60 */         DPRINTF(" cnt = %x\n", s->cnt);                                   // (3) 0.04781
/*62 */         return s->cnt;                                                    // (14) 0.0259
/*64 */     }                                                                     // (27) 0.007968
/*68 */     IPRINTF("imx_timerg_read: Bad offset %x\n",                           // (4) 0.04582
/*70 */             (int)offset >> 2);                                            // (12) 0.03586
/*72 */     return 0;                                                             // (26) 0.01195
/*74 */ }                                                                         // (29) 0.001992
