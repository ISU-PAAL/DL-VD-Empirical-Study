// commit message qemu@c2b38b277a (target=0, prob=0.48356435, correct=True): block: move AioContext, QEMUTimer, main-loop to libqemuutil
/*0 */ static void sigchld_handler(int signal)  // (1) 0.275
/*2 */ {                                        // (2) 0.025
/*4 */     qemu_bh_schedule(sigchld_bh);        // (0) 0.475
/*6 */ }                                        // (3) 0.025
