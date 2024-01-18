// commit message qemu@12d4536f7d (target=1, prob=0.42780018, correct=False): main: force enabling of I/O thread
/*0  */ int qemu_init_main_loop(void)  // (1) 0.1313
/*2  */ {                              // (8) 0.0101
/*4  */     int ret;                   // (6) 0.06061
/*8  */     ret = qemu_signal_init();  // (0) 0.1414
/*10 */     if (ret) {                 // (5) 0.08081
/*12 */         return ret;            // (4) 0.101
/*14 */     }                          // (7) 0.0404
/*18 */     qemu_init_sigbus();        // (2) 0.1313
/*22 */     return qemu_event_init();  // (3) 0.1212
/*24 */ }                              // (9) 0.0101
