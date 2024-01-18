// commit message qemu@a8170e5e97 (target=0, prob=0.0075107305, correct=True): Rename target_phys_addr_t to hwaddr
/*0  */ void mcf_uart_write(void *opaque, target_phys_addr_t addr,  // (2) 0.05238
/*2  */                     uint64_t val, unsigned size)            // (0) 0.06667
/*4  */ {                                                           // (29) 0.002381
/*6  */     mcf_uart_state *s = (mcf_uart_state *)opaque;           // (1) 0.05476
/*8  */     switch (addr & 0x3f) {                                  // (14) 0.03095
/*10 */     case 0x00:                                              // (23) 0.01905
/*12 */         s->mr[s->current_mr] = val;                         // (4) 0.04762
/*14 */         s->current_mr = 1;                                  // (8) 0.03571
/*16 */         break;                                              // (16) 0.02143
/*18 */     case 0x04:                                              // (24) 0.01905
/*20 */         /* CSR is ignored.  */                              // (9) 0.03571
/*22 */         break;                                              // (17) 0.02143
/*24 */     case 0x08: /* Command Register.  */                     // (11) 0.03333
/*26 */         mcf_do_command(s, val);                             // (5) 0.04286
/*28 */         break;                                              // (18) 0.02143
/*30 */     case 0x0c: /* Transmit Buffer.  */                      // (7) 0.0381
/*32 */         s->sr &= ~MCF_UART_TxEMP;                           // (3) 0.05238
/*34 */         s->tb = val;                                        // (12) 0.03333
/*36 */         mcf_uart_do_tx(s);                                  // (6) 0.04286
/*38 */         break;                                              // (19) 0.02143
/*40 */     case 0x10:                                              // (25) 0.01905
/*42 */         /* ACR is ignored.  */                              // (10) 0.03571
/*44 */         break;                                              // (20) 0.02143
/*46 */     case 0x14:                                              // (26) 0.01905
/*48 */         s->imr = val;                                       // (13) 0.03333
/*50 */         break;                                              // (21) 0.02143
/*52 */     default:                                                // (27) 0.0119
/*54 */         break;                                              // (22) 0.02143
/*56 */     }                                                       // (28) 0.009524
/*58 */     mcf_uart_update(s);                                     // (15) 0.02857
/*60 */ }                                                           // (30) 0.002381
