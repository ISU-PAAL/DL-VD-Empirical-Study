// commit message qemu@c2b38b277a (target=0, prob=0.007307968, correct=True): block: move AioContext, QEMUTimer, main-loop to libqemuutil
/*0 */ AioContext *iohandler_get_aio_context(void)  // (0) 0.3636
/*2 */ {                                            // (3) 0.02273
/*4 */     iohandler_init();                        // (2) 0.1818
/*6 */     return iohandler_ctx;                    // (1) 0.2045
/*8 */ }                                            // (4) 0.02273
