// commit message qemu@141af038dd (target=1, prob=0.24919568, correct=False): bt: rewrite csrhci_write to avoid out-of-bounds writes
/*0  */ static void csrhci_reset(struct csrhci_s *s)       // (3) 0.08333
/*2  */ {                                                  // (12) 0.004902
/*4  */     s->out_len = 0;                                // (9) 0.05392
/*6  */     s->out_size = FIFO_LEN;                        // (4) 0.07843
/*8  */     s->in_len = 0;                                 // (10) 0.05392
/*10 */     s->baud_delay = NANOSECONDS_PER_SECOND;        // (0) 0.1078
/*12 */     s->enable = 0;                                 // (11) 0.04412
/*14 */     s->in_hdr = INT_MAX;                           // (6) 0.06863
/*16 */     s->in_data = INT_MAX;                          // (7) 0.06373
/*20 */     s->modem_state = 0;                            // (8) 0.05882
/*22 */     /* After a while... (but sooner than 10ms) */  // (5) 0.07843
/*24 */     s->modem_state |= CHR_TIOCM_CTS;               // (2) 0.09804
/*28 */     memset(&s->bd_addr, 0, sizeof(bdaddr_t));      // (1) 0.1029
/*30 */ }                                                  // (13) 0.004902
