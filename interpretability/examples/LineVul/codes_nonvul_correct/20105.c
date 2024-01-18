// commit message qemu@85a67692d0 (target=0, prob=0.36493814, correct=True): qemu-char: simplify pty polling
/*0  */ static void pty_chr_state(CharDriverState *chr, int connected)           // (4) 0.06431
/*2  */ {                                                                        // (18) 0.003215
/*4  */     PtyCharDriver *s = chr->opaque;                                      // (8) 0.05145
/*8  */     if (!connected) {                                                    // (14) 0.02572
/*10 */         if (s->fd_tag) {                                                 // (9) 0.05145
/*12 */             g_source_remove(s->fd_tag);                                  // (1) 0.07395
/*14 */             s->fd_tag = 0;                                               // (7) 0.06109
/*16 */         }                                                                // (15) 0.02572
/*18 */         s->connected = 0;                                                // (11) 0.0418
/*20 */         s->polling = 0;                                                  // (10) 0.04502
/*22 */         /* (re-)connect poll interval for idle guests: once per second.  // (3) 0.07074
/*24 */          * We check more frequently in case the guests sends data to     // (5) 0.06431
/*26 */          * the virtual device linked to our pty. */                      // (6) 0.06109
/*28 */         pty_chr_rearm_timer(chr, 1000);                                  // (2) 0.07395
/*30 */     } else {                                                             // (16) 0.01929
/*32 */         if (!s->connected)                                               // (13) 0.0418
/*34 */             qemu_chr_be_generic_open(chr);                               // (0) 0.08682
/*36 */         s->connected = 1;                                                // (12) 0.0418
/*38 */     }                                                                    // (17) 0.01286
/*40 */ }                                                                        // (19) 0.003215
