// commit message qemu@40545f84cf (target=1, prob=0.029753245, correct=False): packet fix for for netware 3.11 (initial patch by Mark Jonckheere) - security bug fix
/*0   */ static void ne2000_ioport_write(void *opaque, uint32_t addr, uint32_t val)  // (4) 0.05362
/*2   */ {                                                                           // (23) 0.002141
/*4   */     NE2000State *s = opaque;                                                // (17) 0.02154
/*6   */     int offset, page;                                                       // (20) 0.01562
/*10  */     addr &= 0xf;                                                            // (19) 0.01755
/*12  */ #ifdef DEBUG_NE2000                                                         // (21) 0.01365
/*14  */     printf("NE2000: write addr=0x%x val=0x%02x\n", addr, val);              // (2) 0.05655
/*16  */ #endif                                                                      // (22) 0.003909
/*18  */     if (addr == E8390_CMD) {                                                // (14) 0.02924
/*20  */         /* control register */                                              // (18) 0.02144
/*22  */         s->cmd = val;                                                       // (15) 0.02534
/*24  */         if (val & E8390_START) {                                            // (13) 0.03703
/*26  */             s->isr &= ~ENISR_RESET;                                         // (8) 0.04873
/*28  */             /* test specific case: zero length transfert */                 // (12) 0.04093
/*30  */             if ((val & (E8390_RREAD | E8390_RWRITE)) &&                     // (1) 0.06237
/*32  */                 s->rcnt == 0) {                                             // (10) 0.04483
/*34  */                 s->isr |= ENISR_RDC;                                        // (3) 0.05457
/*36  */                 ne2000_update_irq(s);                                       // (7) 0.04873
/*38  */             }                                                               // (16) 0.02339
/*40  */             if (val & E8390_TRANS) {                                        // (9) 0.04483
/*42  */                 qemu_send_packet(s->nd, s->mem + (s->tpsr << 8), s->tcnt);  // (0) 0.08968
/*44  */                 /* signal end of transfert */                               // (11) 0.04288
/*46  */                 s->tsr = ENTSR_PTX;                                         // (5) 0.05266
/*48  */                 s->isr |= ENISR_TX;                                         // (6) 0.05262
/*50  */                 ne2000_update_irq(s);                                       // 0.0
/*52  */             }                                                               // 0.0
/*54  */         }                                                                   // 0.0
/*56  */     } else {                                                                // 0.0
/*58  */         page = s->cmd >> 6;                                                 // 0.0
/*60  */         offset = addr | (page << 4);                                        // 0.0
/*62  */         switch(offset) {                                                    // 0.0
/*64  */         case EN0_STARTPG:                                                   // 0.0
/*66  */             s->start = val << 8;                                            // 0.0
/*68  */             break;                                                          // 0.0
/*70  */         case EN0_STOPPG:                                                    // 0.0
/*72  */             s->stop = val << 8;                                             // 0.0
/*74  */             break;                                                          // 0.0
/*76  */         case EN0_BOUNDARY:                                                  // 0.0
/*78  */             s->boundary = val;                                              // 0.0
/*80  */             break;                                                          // 0.0
/*82  */         case EN0_IMR:                                                       // 0.0
/*84  */             s->imr = val;                                                   // 0.0
/*86  */             ne2000_update_irq(s);                                           // 0.0
/*88  */             break;                                                          // 0.0
/*90  */         case EN0_TPSR:                                                      // 0.0
/*92  */             s->tpsr = val;                                                  // 0.0
/*94  */             break;                                                          // 0.0
/*96  */         case EN0_TCNTLO:                                                    // 0.0
/*98  */             s->tcnt = (s->tcnt & 0xff00) | val;                             // 0.0
/*100 */             break;                                                          // 0.0
/*102 */         case EN0_TCNTHI:                                                    // 0.0
/*104 */             s->tcnt = (s->tcnt & 0x00ff) | (val << 8);                      // 0.0
/*106 */             break;                                                          // 0.0
/*108 */         case EN0_RSARLO:                                                    // 0.0
/*110 */             s->rsar = (s->rsar & 0xff00) | val;                             // 0.0
/*112 */             break;                                                          // 0.0
/*114 */         case EN0_RSARHI:                                                    // 0.0
/*116 */             s->rsar = (s->rsar & 0x00ff) | (val << 8);                      // 0.0
/*118 */             break;                                                          // 0.0
/*120 */         case EN0_RCNTLO:                                                    // 0.0
/*122 */             s->rcnt = (s->rcnt & 0xff00) | val;                             // 0.0
/*124 */             break;                                                          // 0.0
/*126 */         case EN0_RCNTHI:                                                    // 0.0
/*128 */             s->rcnt = (s->rcnt & 0x00ff) | (val << 8);                      // 0.0
/*130 */             break;                                                          // 0.0
/*132 */         case EN0_DCFG:                                                      // 0.0
/*134 */             s->dcfg = val;                                                  // 0.0
/*136 */             break;                                                          // 0.0
/*138 */         case EN0_ISR:                                                       // 0.0
/*140 */             s->isr &= ~(val & 0x7f);                                        // 0.0
/*142 */             ne2000_update_irq(s);                                           // 0.0
/*144 */             break;                                                          // 0.0
/*146 */         case EN1_PHYS ... EN1_PHYS + 5:                                     // 0.0
/*148 */             s->phys[offset - EN1_PHYS] = val;                               // 0.0
/*150 */             break;                                                          // 0.0
/*152 */         case EN1_CURPAG:                                                    // 0.0
/*154 */             s->curpag = val;                                                // 0.0
/*156 */             break;                                                          // 0.0
/*158 */         case EN1_MULT ... EN1_MULT + 7:                                     // 0.0
/*160 */             s->mult[offset - EN1_MULT] = val;                               // 0.0
/*162 */             break;                                                          // 0.0
/*164 */         }                                                                   // 0.0
/*166 */     }                                                                       // 0.0
/*168 */ }                                                                           // 0.0
