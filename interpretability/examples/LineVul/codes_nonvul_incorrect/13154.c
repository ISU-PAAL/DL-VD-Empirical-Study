// commit message qemu@d82831dbc5 (target=0, prob=0.74532384, correct=False): console: allow VCs to be overridden by UI
/*0  */ CharDriverState *text_console_init(QemuOpts *opts)                    // (7) 0.04481
/*2  */ {                                                                     // (27) 0.002358
/*4  */     CharDriverState *chr;                                             // (15) 0.02358
/*6  */     QemuConsole *s;                                                   // (16) 0.02358
/*8  */     unsigned width;                                                   // (22) 0.01415
/*10 */     unsigned height;                                                  // (23) 0.01415
/*14 */     chr = g_malloc0(sizeof(CharDriverState));                         // (8) 0.04481
/*18 */     width = qemu_opt_get_number(opts, "width", 0);                    // (3) 0.05425
/*20 */     if (width == 0)                                                   // (18) 0.02123
/*22 */         width = qemu_opt_get_number(opts, "cols", 0) * FONT_WIDTH;    // (0) 0.08491
/*26 */     height = qemu_opt_get_number(opts, "height", 0);                  // (4) 0.05425
/*28 */     if (height == 0)                                                  // (19) 0.02123
/*30 */         height = qemu_opt_get_number(opts, "rows", 0) * FONT_HEIGHT;  // (1) 0.08019
/*34 */     if (width == 0 || height == 0) {                                  // (9) 0.03302
/*36 */         s = new_console(NULL, TEXT_CONSOLE);                          // (5) 0.04953
/*38 */     } else {                                                          // (24) 0.01415
/*40 */         s = new_console(NULL, TEXT_CONSOLE_FIXED_SIZE);               // (2) 0.06132
/*42 */     }                                                                 // (25) 0.009434
/*46 */     if (!s) {                                                         // (20) 0.01887
/*48 */         g_free(chr);                                                  // (10) 0.03302
/*50 */         return NULL;                                                  // (17) 0.02358
/*52 */     }                                                                 // (26) 0.009434
/*56 */     s->chr = chr;                                                     // (12) 0.02594
/*58 */     s->g_width = width;                                               // (13) 0.02594
/*60 */     s->g_height = height;                                             // (14) 0.02594
/*62 */     chr->opaque = s;                                                  // (11) 0.02594
/*64 */     chr->chr_set_echo = text_console_set_echo;                        // (6) 0.04953
/*66 */     return chr;                                                       // (21) 0.01651
/*68 */ }                                                                     // (28) 0.002358
