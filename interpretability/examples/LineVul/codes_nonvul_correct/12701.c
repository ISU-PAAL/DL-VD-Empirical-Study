// commit message qemu@a277c3e094 (target=0, prob=0.23180926, correct=True): usb: Support compilation without poll.h
/*0  */ static int usb_host_init(void)                                   // (10) 0.02915
/*2  */ {                                                                // (22) 0.002915
/*4  */     const struct libusb_pollfd **poll;                           // (7) 0.0379
/*6  */     int i, rc;                                                   // (13) 0.02332
/*10 */     if (ctx) {                                                   // (14) 0.02332
/*12 */         return 0;                                                // (11) 0.02915
/*14 */     }                                                            // (19) 0.01166
/*16 */     rc = libusb_init(&ctx);                                      // (8) 0.03499
/*18 */     if (rc != 0) {                                               // (12) 0.02915
/*20 */         return -1;                                               // (9) 0.03207
/*22 */     }                                                            // (20) 0.01166
/*24 */     libusb_set_debug(ctx, loglevel);                             // (5) 0.04665
/*28 */     libusb_set_pollfd_notifiers(ctx, usb_host_add_fd,            // (3) 0.06997
/*30 */                                 usb_host_del_fd,                 // (0) 0.1137
/*32 */                                 ctx);                            // (2) 0.09913
/*34 */     poll = libusb_get_pollfds(ctx);                              // (6) 0.04665
/*36 */     if (poll) {                                                  // (15) 0.02332
/*38 */         for (i = 0; poll[i] != NULL; i++) {                      // (4) 0.06706
/*40 */             usb_host_add_fd(poll[i]->fd, poll[i]->events, ctx);  // (1) 0.105
/*42 */         }                                                        // (16) 0.02332
/*44 */     }                                                            // (21) 0.01166
/*46 */     free(poll);                                                  // (17) 0.02041
/*48 */     return 0;                                                    // (18) 0.01749
/*50 */ }                                                                // (23) 0.002915
