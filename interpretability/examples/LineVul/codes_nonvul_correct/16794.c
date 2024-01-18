// commit message qemu@c2b38b277a (target=0, prob=0.0193998, correct=True): block: move AioContext, QEMUTimer, main-loop to libqemuutil
/*0  */ void aio_set_event_notifier(AioContext *ctx,                               // (6) 0.07083
/*2  */                             EventNotifier *notifier,                       // (3) 0.1417
/*4  */                             bool is_external,                              // (4) 0.1333
/*6  */                             EventNotifierHandler *io_read,                 // (2) 0.15
/*8  */                             AioPollFn *io_poll)                            // (1) 0.1542
/*10 */ {                                                                          // (7) 0.004167
/*12 */     aio_set_fd_handler(ctx, event_notifier_get_fd(notifier), is_external,  // (5) 0.125
/*14 */                        (IOHandler *)io_read, NULL, io_poll, notifier);     // (0) 0.1625
/*16 */ }                                                                          // (8) 0.004167
