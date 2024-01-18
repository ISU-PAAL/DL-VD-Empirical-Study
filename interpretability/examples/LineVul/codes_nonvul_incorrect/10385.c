// commit message qemu@cdbf6e1659 (target=0, prob=0.6132145, correct=False): qemu-char: correct return value from chr_read functions
/*0  */ static gboolean udp_chr_read(GIOChannel *chan, GIOCondition cond, void *opaque)  // (3) 0.07532
/*2  */ {                                                                                // (21) 0.002597
/*4  */     CharDriverState *chr = opaque;                                               // (11) 0.03117
/*6  */     NetCharDriver *s = chr->opaque;                                              // (7) 0.03896
/*8  */     gsize bytes_read = 0;                                                        // (13) 0.02857
/*10 */     GIOStatus status;                                                            // (17) 0.02078
/*14 */     if (s->max_size == 0)                                                        // (9) 0.03377
/*16 */         return FALSE;                                                            // (14) 0.02597
/*18 */     status = g_io_channel_read_chars(s->chan, (gchar *)s->buf, sizeof(s->buf),   // (1) 0.08831
/*20 */                                      &bytes_read, NULL);                         // (0) 0.1117
/*22 */     s->bufcnt = bytes_read;                                                      // (10) 0.03377
/*24 */     s->bufptr = s->bufcnt;                                                       // (8) 0.03636
/*26 */     if (status != G_IO_STATUS_NORMAL) {                                          // (6) 0.04675
/*28 */         return FALSE;                                                            // (15) 0.02597
/*30 */     }                                                                            // (19) 0.01039
/*34 */     s->bufptr = 0;                                                               // (16) 0.02597
/*36 */     while (s->max_size > 0 && s->bufptr < s->bufcnt) {                           // (5) 0.06494
/*38 */         qemu_chr_be_write(chr, &s->buf[s->bufptr], 1);                           // (2) 0.08571
/*40 */         s->bufptr++;                                                             // (12) 0.03117
/*42 */         s->max_size = qemu_chr_be_can_write(chr);                                // (4) 0.07532
/*44 */     }                                                                            // (20) 0.01039
/*48 */     return TRUE;                                                                 // (18) 0.01558
/*50 */ }                                                                                // (22) 0.002597
