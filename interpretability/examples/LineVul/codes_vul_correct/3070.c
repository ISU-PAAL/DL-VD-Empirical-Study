// commit message qemu@81174dae3f (target=1, prob=0.5225144, correct=True): Upgrade emulated UART to 16550A (Stefano Stabellini)
/*0  */ static void serial_tx_done(void *opaque)                    // (10) 0.04833
/*2  */ {                                                           // (16) 0.003717
/*4  */     SerialState *s = opaque;                                // (13) 0.03717
/*8  */     if (s->tx_burst < 0) {                                  // (6) 0.05204
/*10 */         uint16_t divider;                                   // (7) 0.05204
/*14 */         if (s->divider)                                     // (8) 0.05204
/*16 */           divider = s->divider;                             // (5) 0.0632
/*18 */         else                                                // (14) 0.02974
/*20 */           divider = 1;                                      // (9) 0.05204
/*24 */         /* We assume 10 bits/char, OK for this purpose. */  // (2) 0.07807
/*26 */         s->tx_burst = THROTTLE_TX_INTERVAL * 1000 /         // (1) 0.08922
/*28 */             (1000000 * 10 / (s->baudbase / divider));       // (0) 0.1004
/*30 */     }                                                       // (15) 0.01487
/*32 */     s->thr_ipending = 1;                                    // (11) 0.04833
/*34 */     s->lsr |= UART_LSR_THRE;                                // (4) 0.06691
/*36 */     s->lsr |= UART_LSR_TEMT;                                // (3) 0.07063
/*38 */     serial_update_irq(s);                                   // (12) 0.04461
/*40 */ }                                                           // (17) 0.003717
