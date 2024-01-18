// commit message qemu@bd5c51ee6c (target=0, prob=0.75984347, correct=False): qemu-char: don't issue CHR_EVENT_OPEN in a BH
/*0  */ static CharDriverState *qemu_chr_open_fd(int fd_in, int fd_out)  // (0) 0.08946
/*2  */ {                                                                // (16) 0.003195
/*4  */     CharDriverState *chr;                                        // (13) 0.03195
/*6  */     FDCharDriver *s;                                             // (14) 0.02875
/*10 */     chr = g_malloc0(sizeof(CharDriverState));                    // (6) 0.0607
/*12 */     s = g_malloc0(sizeof(FDCharDriver));                         // (10) 0.05751
/*14 */     s->fd_in = io_channel_from_fd(fd_in);                        // (4) 0.06709
/*16 */     s->fd_out = io_channel_from_fd(fd_out);                      // (5) 0.06709
/*18 */     fcntl(fd_out, F_SETFL, O_NONBLOCK);                          // (2) 0.07668
/*20 */     s->chr = chr;                                                // (12) 0.03514
/*22 */     chr->opaque = s;                                             // (11) 0.03514
/*24 */     chr->chr_add_watch = fd_chr_add_watch;                       // (3) 0.07348
/*26 */     chr->chr_write = fd_chr_write;                               // (8) 0.0607
/*28 */     chr->chr_update_read_handler = fd_chr_update_read_handler;   // (1) 0.08626
/*30 */     chr->chr_close = fd_chr_close;                               // (9) 0.0607
/*34 */     qemu_chr_be_generic_open(chr);                               // (7) 0.0607
/*38 */     return chr;                                                  // (15) 0.02236
/*40 */ }                                                                // (17) 0.003195
