// commit message qemu@a8170e5e97 (target=0, prob=0.028346194, correct=True): Rename target_phys_addr_t to hwaddr
/*0   */ static void gem_write(void *opaque, target_phys_addr_t offset, uint64_t val,   // (2) 0.05078
/*2   */         unsigned size)                                                         // (20) 0.01953
/*4   */ {                                                                              // (27) 0.001953
/*6   */     GemState *s = (GemState *)opaque;                                          // (12) 0.03125
/*8   */     uint32_t readonly;                                                         // (21) 0.01953
/*12  */     DB_PRINT("offset: 0x%04x write: 0x%08x ", offset, (unsigned)val);          // (1) 0.05859
/*14  */     offset >>= 2;                                                              // (23) 0.01563
/*18  */     /* Squash bits which are read only in write value */                       // (15) 0.0293
/*20  */     val &= ~(s->regs_ro[offset]);                                              // (10) 0.0332
/*22  */     /* Preserve (only) bits which are read only in register */                 // (11) 0.0332
/*24  */     readonly = s->regs[offset];                                                // (17) 0.02539
/*26  */     readonly &= s->regs_ro[offset];                                            // (13) 0.03125
/*30  */     /* Squash bits which are write 1 to clear */                               // (16) 0.02734
/*32  */     val &= ~(s->regs_w1c[offset] & val);                                       // (6) 0.04297
/*36  */     /* Copy register write to backing store */                                 // (18) 0.02148
/*38  */     s->regs[offset] = val | readonly;                                          // (14) 0.03125
/*42  */     /* Handle register write side effects */                                   // (22) 0.01953
/*44  */     switch (offset) {                                                          // (24) 0.01562
/*46  */     case GEM_NWCTRL:                                                           // (19) 0.02148
/*48  */         if (val & GEM_NWCTRL_TXSTART) {                                        // (4) 0.04492
/*50  */             gem_transmit(s);                                                   // (9) 0.03516
/*52  */         }                                                                      // (25) 0.01562
/*54  */         if (!(val & GEM_NWCTRL_TXENA)) {                                       // (5) 0.04492
/*56  */             /* Reset to start of Q when transmit disabled. */                  // (7) 0.04297
/*58  */             s->tx_desc_addr = s->regs[GEM_TXQBASE];                            // (0) 0.06055
/*60  */         }                                                                      // (26) 0.01562
/*62  */         if (!(val & GEM_NWCTRL_RXENA)) {                                       // (3) 0.04688
/*64  */             /* Reset to start of Q when receive disabled. */                   // (8) 0.04297
/*66  */             s->rx_desc_addr = s->regs[GEM_RXQBASE];                            // 0.0
/*68  */         }                                                                      // 0.0
/*70  */         break;                                                                 // 0.0
/*74  */     case GEM_TXSTATUS:                                                         // 0.0
/*76  */         gem_update_int_status(s);                                              // 0.0
/*78  */         break;                                                                 // 0.0
/*80  */     case GEM_RXQBASE:                                                          // 0.0
/*82  */         s->rx_desc_addr = val;                                                 // 0.0
/*84  */         break;                                                                 // 0.0
/*86  */     case GEM_TXQBASE:                                                          // 0.0
/*88  */         s->tx_desc_addr = val;                                                 // 0.0
/*90  */         break;                                                                 // 0.0
/*92  */     case GEM_RXSTATUS:                                                         // 0.0
/*94  */         gem_update_int_status(s);                                              // 0.0
/*96  */         break;                                                                 // 0.0
/*98  */     case GEM_IER:                                                              // 0.0
/*100 */         s->regs[GEM_IMR] &= ~val;                                              // 0.0
/*102 */         gem_update_int_status(s);                                              // 0.0
/*104 */         break;                                                                 // 0.0
/*106 */     case GEM_IDR:                                                              // 0.0
/*108 */         s->regs[GEM_IMR] |= val;                                               // 0.0
/*110 */         gem_update_int_status(s);                                              // 0.0
/*112 */         break;                                                                 // 0.0
/*114 */     case GEM_PHYMNTNC:                                                         // 0.0
/*116 */         if (val & GEM_PHYMNTNC_OP_W) {                                         // 0.0
/*118 */             uint32_t phy_addr, reg_num;                                        // 0.0
/*122 */             phy_addr = (val & GEM_PHYMNTNC_ADDR) >> GEM_PHYMNTNC_ADDR_SHFT;    // 0.0
/*124 */             if (phy_addr == BOARD_PHY_ADDRESS) {                               // 0.0
/*126 */                 reg_num = (val & GEM_PHYMNTNC_REG) >> GEM_PHYMNTNC_REG_SHIFT;  // 0.0
/*128 */                 gem_phy_write(s, reg_num, val);                                // 0.0
/*130 */             }                                                                  // 0.0
/*132 */         }                                                                      // 0.0
/*134 */         break;                                                                 // 0.0
/*136 */     }                                                                          // 0.0
/*140 */     DB_PRINT("newval: 0x%08x\n", s->regs[offset]);                             // 0.0
/*142 */ }                                                                              // 0.0
