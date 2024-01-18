// commit message qemu@9bd7854e1e (target=0, prob=0.06889443, correct=True): char: don't limit data sent to backends to 1k per buffer
/*0  */ static void fd_chr_read(void *opaque)                               // (6) 0.0495
/*2  */ {                                                                   // (20) 0.0033
/*4  */     CharDriverState *chr = opaque;                                  // (9) 0.0396
/*6  */     FDCharDriver *s = chr->opaque;                                  // (5) 0.0495
/*8  */     int size, len;                                                  // (17) 0.0264
/*10 */     uint8_t buf[1024];                                              // (10) 0.0363
/*14 */     len = sizeof(buf);                                              // (13) 0.0297
/*16 */     if (len > s->max_size)                                          // (8) 0.0429
/*18 */         len = s->max_size;                                          // (7) 0.0495
/*20 */     if (len == 0)                                                   // (14) 0.0297
/*22 */         return;                                                     // (15) 0.0297
/*24 */     size = read(s->fd_in, buf, len);                                // (4) 0.05611
/*26 */     if (size == 0) {                                                // (11) 0.033
/*28 */         /* FD has been closed. Remove it from the active list.  */  // (3) 0.07261
/*30 */         qemu_set_fd_handler2(s->fd_in, NULL, NULL, NULL, NULL);     // (0) 0.1056
/*32 */         qemu_chr_event(chr, CHR_EVENT_CLOSED);                      // (1) 0.08911
/*34 */         return;                                                     // (16) 0.0297
/*36 */     }                                                               // (18) 0.0132
/*38 */     if (size > 0) {                                                 // (12) 0.033
/*40 */         qemu_chr_read(chr, buf, size);                              // (2) 0.07591
/*42 */     }                                                               // (19) 0.0132
/*44 */ }                                                                   // (21) 0.0033
