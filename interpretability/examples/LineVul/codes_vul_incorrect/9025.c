// commit message qemu@f21126df5f (target=1, prob=0.4546751, correct=False): Fix arm-softmmu compile
/*0   */ static void pl181_fifo_run(pl181_state *s)                            // (12) 0.0332
/*2   */ {                                                                     // (25) 0.001953
/*4   */     uint32_t bits;                                                    // (21) 0.01758
/*6   */     uint32_t value;                                                   // (22) 0.01758
/*8   */     int n;                                                            // (24) 0.01172
/*10  */     int is_read;                                                      // (23) 0.01562
/*14  */     is_read = (s->datactrl & PL181_DATA_DIRECTION) != 0;              // (5) 0.05078
/*16  */     if (s->datacnt != 0 && (!is_read || sd_data_ready(s->card))       // (3) 0.05469
/*18  */             && !s->linux_hack) {                                      // (10) 0.03906
/*20  */         if (is_read) {                                                // (17) 0.02734
/*22  */             n = 0;                                                    // (15) 0.0293
/*24  */             value = 0;                                                // (16) 0.0293
/*26  */             while (s->datacnt && s->fifo_len < PL181_FIFO_LEN) {      // (1) 0.07227
/*28  */                 value |= (uint32_t)sd_read_data(s->card) << (n * 8);  // (0) 0.07812
/*30  */                 s->datacnt--;                                         // (8) 0.04297
/*32  */                 n++;                                                  // (13) 0.0332
/*34  */                 if (n == 4) {                                         // (9) 0.04297
/*36  */                     pl181_fifo_push(s, value);                        // (2) 0.06055
/*38  */                     n = 0;                                            // (7) 0.04492
/*40  */                     value = 0;                                        // (6) 0.04492
/*42  */                 }                                                     // (14) 0.03125
/*44  */             }                                                         // (19) 0.02344
/*46  */             if (n != 0) {                                             // (11) 0.03516
/*48  */                 pl181_fifo_push(s, value);                            // (4) 0.05273
/*50  */             }                                                         // (20) 0.02344
/*52  */         } else { /* write */                                          // (18) 0.02539
/*54  */             n = 0;                                                    // 0.0
/*56  */             while (s->datacnt > 0 && (s->fifo_len > 0 || n > 0)) {    // 0.0
/*58  */                 if (n == 0) {                                         // 0.0
/*60  */                     value = pl181_fifo_pop(s);                        // 0.0
/*62  */                     n = 4;                                            // 0.0
/*64  */                 }                                                     // 0.0
/*66  */                 n--;                                                  // 0.0
/*68  */                 s->datacnt--;                                         // 0.0
/*70  */                 sd_write_data(s->card, value & 0xff);                 // 0.0
/*72  */                 value >>= 8;                                          // 0.0
/*74  */             }                                                         // 0.0
/*76  */         }                                                             // 0.0
/*78  */     }                                                                 // 0.0
/*80  */     s->status &= ~(PL181_STATUS_RX_FIFO | PL181_STATUS_TX_FIFO);      // 0.0
/*82  */     if (s->datacnt == 0) {                                            // 0.0
/*84  */         s->status |= PL181_STATUS_DATAEND;                            // 0.0
/*86  */         /* HACK: */                                                   // 0.0
/*88  */         s->status |= PL181_STATUS_DATABLOCKEND;                       // 0.0
/*90  */         DPRINTF("Transfer Complete\n");                               // 0.0
/*92  */     }                                                                 // 0.0
/*94  */     if (s->datacnt == 0 && s->fifo_len == 0) {                        // 0.0
/*96  */         s->datactrl &= ~PL181_DATA_ENABLE;                            // 0.0
/*98  */         DPRINTF("Data engine idle\n");                                // 0.0
/*100 */     } else {                                                          // 0.0
/*102 */         /* Update FIFO bits.  */                                      // 0.0
/*104 */         bits = PL181_STATUS_TXACTIVE | PL181_STATUS_RXACTIVE;         // 0.0
/*106 */         if (s->fifo_len == 0) {                                       // 0.0
/*108 */             bits |= PL181_STATUS_TXFIFOEMPTY;                         // 0.0
/*110 */             bits |= PL181_STATUS_RXFIFOEMPTY;                         // 0.0
/*112 */         } else {                                                      // 0.0
/*114 */             bits |= PL181_STATUS_TXDATAAVLBL;                         // 0.0
/*116 */             bits |= PL181_STATUS_RXDATAAVLBL;                         // 0.0
/*118 */         }                                                             // 0.0
/*120 */         if (s->fifo_len == 16) {                                      // 0.0
/*122 */             bits |= PL181_STATUS_TXFIFOFULL;                          // 0.0
/*124 */             bits |= PL181_STATUS_RXFIFOFULL;                          // 0.0
/*126 */         }                                                             // 0.0
/*128 */         if (s->fifo_len <= 8) {                                       // 0.0
/*130 */             bits |= PL181_STATUS_TXFIFOHALFEMPTY;                     // 0.0
/*132 */         }                                                             // 0.0
/*134 */         if (s->fifo_len >= 8) {                                       // 0.0
/*136 */             bits |= PL181_STATUS_RXFIFOHALFFULL;                      // 0.0
/*138 */         }                                                             // 0.0
/*140 */         if (s->datactrl & PL181_DATA_DIRECTION) {                     // 0.0
/*142 */             bits &= PL181_STATUS_RX_FIFO;                             // 0.0
/*144 */         } else {                                                      // 0.0
/*146 */             bits &= PL181_STATUS_TX_FIFO;                             // 0.0
/*148 */         }                                                             // 0.0
/*150 */         s->status |= bits;                                            // 0.0
/*152 */     }                                                                 // 0.0
/*154 */ }                                                                     // 0.0
