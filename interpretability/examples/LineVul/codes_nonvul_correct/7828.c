// commit message qemu@c2b38b277a (target=0, prob=0.00585206, correct=True): block: move AioContext, QEMUTimer, main-loop to libqemuutil
/*0 */ GSource *iohandler_get_g_source(void)        // (1) 0.2746
/*2 */ {                                            // (3) 0.01961
/*4 */     iohandler_init();                        // (2) 0.1569
/*6 */     return aio_get_g_source(iohandler_ctx);  // (0) 0.3529
/*8 */ }                                            // (4) 0.01961
