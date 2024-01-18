// commit message qemu@9e14037f05 (target=1, prob=0.63320595, correct=True): msmouse: Fix segfault caused by free the chr before chardev cleanup.
/*0  */ static void msmouse_chr_close (struct CharDriverState *chr)  // (0) 0.2262
/*2  */ {                                                            // (5) 0.0119
/*4  */     MouseState *mouse = chr->opaque;                         // (2) 0.1667
/*8  */     qemu_input_handler_unregister(mouse->hs);                // (1) 0.2143
/*10 */     g_free(mouse);                                           // (4) 0.1071
/*12 */     g_free(chr);                                             // (3) 0.119
/*14 */ }                                                            // (6) 0.0119
