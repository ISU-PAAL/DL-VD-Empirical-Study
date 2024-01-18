// commit message qemu@b0d768c35e (target=1, prob=0.024570156, correct=False): chardev: fix pty_chr_timer
/*0  */ static gboolean pty_chr_timer(gpointer opaque)  // (2) 0.1168
/*2  */ {                                               // (11) 0.007299
/*4  */     struct CharDriverState *chr = opaque;       // (3) 0.09489
/*6  */     PtyCharDriver *s = chr->opaque;             // (1) 0.1168
/*10 */     if (s->connected) {                         // (5) 0.07299
/*12 */         goto out;                               // (6) 0.07299
/*14 */     }                                           // (9) 0.0292
/*18 */     /* Next poll ... */                         // (7) 0.05839
/*20 */     pty_chr_update_read_handler(chr);           // (0) 0.1314
/*24 */ out:                                            // (10) 0.0146
/*26 */     s->timer_tag = 0;                           // (4) 0.08029
/*28 */     return FALSE;                               // (8) 0.0438
/*30 */ }                                               // (12) 0.007299
