// commit message qemu@586502189e (target=1, prob=0.23377162, correct=False): qemu-char: Inherit ptys and improve output from -serial pty
/*0  */ static CharDriverState *qemu_chr_open_pty(QemuOpts *opts)                     // (5) 0.04883
/*2  */ {                                                                             // (30) 0.001953
/*4  */     CharDriverState *chr;                                                     // (23) 0.01953
/*6  */     PtyCharDriver *s;                                                         // (21) 0.01953
/*8  */     struct termios tty;                                                       // (24) 0.01758
/*10 */     int master_fd, slave_fd, len;                                             // (16) 0.02734
/*12 */ #if defined(__OpenBSD__) || defined(__DragonFly__)                            // (11) 0.0332
/*14 */     char pty_name[PATH_MAX];                                                  // (17) 0.02539
/*16 */ #define q_ptsname(x) pty_name                                                 // (14) 0.02734
/*18 */ #else                                                                         // (29) 0.003906
/*20 */     char *pty_name = NULL;                                                    // (19) 0.02148
/*22 */ #define q_ptsname(x) ptsname(x)                                               // (12) 0.0293
/*24 */ #endif                                                                        // (28) 0.003906
/*28 */     if (openpty(&master_fd, &slave_fd, pty_name, NULL, NULL) < 0) {           // (0) 0.05859
/*30 */         return NULL;                                                          // (22) 0.01953
/*32 */     }                                                                         // (27) 0.007812
/*36 */     /* Set raw attributes on the pty. */                                      // (18) 0.02539
/*38 */     tcgetattr(slave_fd, &tty);                                                // (15) 0.02734
/*40 */     cfmakeraw(&tty);                                                          // (25) 0.01758
/*42 */     tcsetattr(slave_fd, TCSAFLUSH, &tty);                                     // (8) 0.03711
/*44 */     close(slave_fd);                                                          // (26) 0.01758
/*48 */     chr = g_malloc0(sizeof(CharDriverState));                                 // (9) 0.03711
/*52 */     len = strlen(q_ptsname(master_fd)) + 5;                                   // (6) 0.04102
/*54 */     chr->filename = g_malloc(len);                                            // (13) 0.0293
/*56 */     snprintf(chr->filename, len, "pty:%s", q_ptsname(master_fd));             // (2) 0.05664
/*58 */     qemu_opt_set(opts, "path", q_ptsname(master_fd));                         // (3) 0.05273
/*60 */     fprintf(stderr, "char device redirected to %s\n", q_ptsname(master_fd));  // (1) 0.05859
/*64 */     s = g_malloc0(sizeof(PtyCharDriver));                                     // (7) 0.03711
/*66 */     chr->opaque = s;                                                          // (20) 0.02148
/*68 */     chr->chr_write = pty_chr_write;                                           // (10) 0.03711
/*70 */     chr->chr_update_read_handler = pty_chr_update_read_handler;               // (4) 0.05273
/*72 */     chr->chr_close = pty_chr_close;                                           // 0.0
/*76 */     s->fd = master_fd;                                                        // 0.0
/*78 */     s->timer = qemu_new_timer_ms(rt_clock, pty_chr_timer, chr);               // 0.0
/*82 */     return chr;                                                               // 0.0
/*84 */ }                                                                             // 0.0
