// commit message qemu@1a29cc8f5e (target=0, prob=0.5976204, correct=False): serial: chardev hotswap support
/*0  */ void serial_realize_core(SerialState *s, Error **errp)                                              // (8) 0.05114
/*2  */ {                                                                                                   // (13) 0.002841
/*4  */     if (!qemu_chr_fe_backend_connected(&s->chr)) {                                                  // (7) 0.07102
/*6  */         error_setg(errp, "Can't create serial device, empty char device");                          // (6) 0.07386
/*8  */         return;                                                                                     // (10) 0.02557
/*10 */     }                                                                                               // (12) 0.01136
/*14 */     s->modem_status_poll = timer_new_ns(QEMU_CLOCK_VIRTUAL, (QEMUTimerCB *) serial_update_msl, s);  // (0) 0.1278
/*18 */     s->fifo_timeout_timer = timer_new_ns(QEMU_CLOCK_VIRTUAL, (QEMUTimerCB *) fifo_timeout_int, s);  // (1) 0.1278
/*20 */     qemu_register_reset(serial_reset, s);                                                           // (9) 0.0483
/*24 */     qemu_chr_fe_set_handlers(&s->chr, serial_can_receive1, serial_receive1,                         // (3) 0.1023
/*26 */                              serial_event, NULL, s, NULL, true);                                    // (2) 0.1136
/*28 */     fifo8_create(&s->recv_fifo, UART_FIFO_LENGTH);                                                  // (4) 0.0767
/*30 */     fifo8_create(&s->xmit_fifo, UART_FIFO_LENGTH);                                                  // (5) 0.0767
/*32 */     serial_reset(s);                                                                                // (11) 0.02557
/*34 */ }                                                                                                   // (14) 0.002841
