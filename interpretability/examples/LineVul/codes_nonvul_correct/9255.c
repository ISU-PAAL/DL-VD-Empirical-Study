// commit message qemu@a8170e5e97 (target=0, prob=0.0063746125, correct=True): Rename target_phys_addr_t to hwaddr
/*0   */ static uint64_t lan9118_readl(void *opaque, target_phys_addr_t offset,    // (3) 0.05078
/*2   */                               unsigned size)                              // (0) 0.0625
/*4   */ {                                                                         // (31) 0.001953
/*6   */     lan9118_state *s = (lan9118_state *)opaque;                           // (5) 0.04102
/*10  */     //DPRINTF("Read reg 0x%02x\n", (int)offset);                          // (4) 0.04688
/*12  */     if (offset < 0x20) {                                                  // (22) 0.02344
/*14  */         /* RX FIFO */                                                     // (16) 0.02539
/*16  */         return rx_fifo_pop(s);                                            // (8) 0.03516
/*18  */     }                                                                     // (30) 0.007812
/*20  */     switch (offset) {                                                     // (26) 0.01562
/*22  */     case 0x40:                                                            // (28) 0.01562
/*24  */         return rx_status_fifo_pop(s);                                     // (6) 0.03906
/*26  */     case 0x44:                                                            // (27) 0.01562
/*28  */         return s->rx_status_fifo[s->tx_status_fifo_head];                 // (1) 0.05469
/*30  */     case 0x48:                                                            // (29) 0.01562
/*32  */         return tx_status_fifo_pop(s);                                     // (7) 0.03711
/*34  */     case 0x4c:                                                            // (25) 0.01758
/*36  */         return s->tx_status_fifo[s->tx_status_fifo_head];                 // (2) 0.05469
/*38  */     case CSR_ID_REV:                                                      // (21) 0.02344
/*40  */         return 0x01180001;                                                // (13) 0.02734
/*42  */     case CSR_IRQ_CFG:                                                     // (18) 0.02539
/*44  */         return s->irq_cfg;                                                // (9) 0.0293
/*46  */     case CSR_INT_STS:                                                     // (23) 0.02344
/*48  */         return s->int_sts;                                                // (14) 0.02734
/*50  */     case CSR_INT_EN:                                                      // (24) 0.02148
/*52  */         return s->int_en;                                                 // (15) 0.02734
/*54  */     case CSR_BYTE_TEST:                                                   // (17) 0.02539
/*56  */         return 0x87654321;                                                // (11) 0.0293
/*58  */     case CSR_FIFO_INT:                                                    // (19) 0.02539
/*60  */         return s->fifo_int;                                               // (10) 0.0293
/*62  */     case CSR_RX_CFG:                                                      // (20) 0.02539
/*64  */         return s->rx_cfg;                                                 // (12) 0.02734
/*66  */     case CSR_TX_CFG:                                                      // 0.0
/*68  */         return s->tx_cfg;                                                 // 0.0
/*70  */     case CSR_HW_CFG:                                                      // 0.0
/*72  */         return s->hw_cfg;                                                 // 0.0
/*74  */     case CSR_RX_DP_CTRL:                                                  // 0.0
/*76  */         return 0;                                                         // 0.0
/*78  */     case CSR_RX_FIFO_INF:                                                 // 0.0
/*80  */         return (s->rx_status_fifo_used << 16) | (s->rx_fifo_used << 2);   // 0.0
/*82  */     case CSR_TX_FIFO_INF:                                                 // 0.0
/*84  */         return (s->tx_status_fifo_used << 16)                             // 0.0
/*86  */                | (s->tx_fifo_size - s->txp->fifo_used);                   // 0.0
/*88  */     case CSR_PMT_CTRL:                                                    // 0.0
/*90  */         return s->pmt_ctrl;                                               // 0.0
/*92  */     case CSR_GPIO_CFG:                                                    // 0.0
/*94  */         return s->gpio_cfg;                                               // 0.0
/*96  */     case CSR_GPT_CFG:                                                     // 0.0
/*98  */         return s->gpt_cfg;                                                // 0.0
/*100 */     case CSR_GPT_CNT:                                                     // 0.0
/*102 */         return ptimer_get_count(s->timer);                                // 0.0
/*104 */     case CSR_WORD_SWAP:                                                   // 0.0
/*106 */         return s->word_swap;                                              // 0.0
/*108 */     case CSR_FREE_RUN:                                                    // 0.0
/*110 */         return (qemu_get_clock_ns(vm_clock) / 40) - s->free_timer_start;  // 0.0
/*112 */     case CSR_RX_DROP:                                                     // 0.0
/*114 */         /* TODO: Implement dropped frames counter.  */                    // 0.0
/*116 */         return 0;                                                         // 0.0
/*118 */     case CSR_MAC_CSR_CMD:                                                 // 0.0
/*120 */         return s->mac_cmd;                                                // 0.0
/*122 */     case CSR_MAC_CSR_DATA:                                                // 0.0
/*124 */         return s->mac_data;                                               // 0.0
/*126 */     case CSR_AFC_CFG:                                                     // 0.0
/*128 */         return s->afc_cfg;                                                // 0.0
/*130 */     case CSR_E2P_CMD:                                                     // 0.0
/*132 */         return s->e2p_cmd;                                                // 0.0
/*134 */     case CSR_E2P_DATA:                                                    // 0.0
/*136 */         return s->e2p_data;                                               // 0.0
/*138 */     }                                                                     // 0.0
/*140 */     hw_error("lan9118_read: Bad reg 0x%x\n", (int)offset);                // 0.0
/*142 */     return 0;                                                             // 0.0
/*144 */ }                                                                         // 0.0
