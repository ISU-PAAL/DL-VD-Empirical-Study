// commit message qemu@2b316774f6 (target=1, prob=0.50637656, correct=True): qemu-char: do not operate on sources from finalize callbacks
/*0  */ static void fd_chr_update_read_handler(CharDriverState *chr)                             // (1) 0.1186
/*2  */ {                                                                                        // (9) 0.00565
/*4  */     FDCharDriver *s = chr->opaque;                                                       // (4) 0.08475
/*8  */     if (s->fd_in_tag) {                                                                  // (5) 0.0791
/*10 */         g_source_remove(s->fd_in_tag);                                                   // (2) 0.1186
/*12 */         s->fd_in_tag = 0;                                                                // (3) 0.09605
/*14 */     }                                                                                    // (7) 0.0226
/*18 */     if (s->fd_in) {                                                                      // (6) 0.0678
/*20 */         s->fd_in_tag = io_add_watch_poll(s->fd_in, fd_chr_read_poll, fd_chr_read, chr);  // (0) 0.2825
/*22 */     }                                                                                    // (8) 0.0226
/*24 */ }                                                                                        // (10) 0.00565
