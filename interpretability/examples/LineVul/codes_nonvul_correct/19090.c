// commit message qemu@d1fdf257d5 (target=0, prob=0.23816799, correct=True): nbd: rename read_sync and friends
/*0  */ static int nbd_negotiate_write(QIOChannel *ioc, const void *buffer, size_t size)  // (4) 0.09241
/*2  */ {                                                                                 // (13) 0.0033
/*4  */     ssize_t ret;                                                                  // (10) 0.0297
/*6  */     guint watch;                                                                  // (11) 0.0231
/*10 */     assert(qemu_in_coroutine());                                                  // (7) 0.0462
/*12 */     /* Negotiation are always in main loop. */                                    // (8) 0.0429
/*14 */     watch = qio_channel_add_watch(ioc,                                            // (6) 0.05611
/*16 */                                   G_IO_OUT,                                       // (2) 0.1287
/*18 */                                   nbd_negotiate_continue,                         // (0) 0.1386
/*20 */                                   qemu_coroutine_self(),                          // (1) 0.1386
/*22 */                                   NULL);                                          // (3) 0.1155
/*24 */     ret = write_sync(ioc, buffer, size, NULL);                                    // (5) 0.05941
/*26 */     g_source_remove(watch);                                                       // (9) 0.0363
/*28 */     return ret;                                                                   // (12) 0.0198
/*30 */ }                                                                                 // (14) 0.0033
