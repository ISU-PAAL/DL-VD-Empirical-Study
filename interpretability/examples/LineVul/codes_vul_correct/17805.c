// commit message qemu@096685fc2a (target=1, prob=0.998796, correct=True): hw/omap_intc.c: Avoid crash on access to nonexistent banked registers
/*0   */ static uint64_t omap2_inth_read(void *opaque, target_phys_addr_t addr,      // (2) 0.05273
/*2   */                                 unsigned size)                              // (0) 0.06641
/*4   */ {                                                                           // (25) 0.001953
/*6   */     struct omap_intr_handler_s *s = (struct omap_intr_handler_s *) opaque;  // (1) 0.05859
/*8   */     int offset = addr;                                                      // (21) 0.01563
/*10  */     int bank_no, line_no;                                                   // (20) 0.02344
/*12  */     struct omap_intr_handler_bank_s *bank = NULL;                           // (6) 0.03906
/*16  */     if ((offset & 0xf80) == 0x80) {                                         // (16) 0.0332
/*18  */         bank_no = (offset & 0x60) >> 5;                                     // (5) 0.04102
/*20  */         if (bank_no < s->nbanks) {                                          // (8) 0.03711
/*22  */             offset &= ~0x60;                                                // (10) 0.03711
/*24  */             bank = &s->bank[bank_no];                                       // (3) 0.04297
/*29  */         }                                                                   // (23) 0.01562
/*31  */     }                                                                       // (24) 0.007812
/*35  */     switch (offset) {                                                       // (22) 0.01562
/*37  */     case 0x00:	/* INTC_REVISION */                                          // (18) 0.0332
/*39  */         return s->revision;                                                 // (19) 0.02539
/*43  */     case 0x10:	/* INTC_SYSCONFIG */                                         // (13) 0.03516
/*45  */         return (s->autoidle >> 2) & 1;                                      // (7) 0.03906
/*49  */     case 0x14:	/* INTC_SYSSTATUS */                                         // (12) 0.03516
/*51  */         return 1;						/* RESETDONE */                                      // (4) 0.04297
/*55  */     case 0x40:	/* INTC_SIR_IRQ */                                           // (11) 0.03711
/*57  */         return s->sir_intr[0];                                              // (15) 0.03516
/*61  */     case 0x44:	/* INTC_SIR_FIQ */                                           // (9) 0.03711
/*63  */         return s->sir_intr[1];                                              // (14) 0.03516
/*67  */     case 0x48:	/* INTC_CONTROL */                                           // (17) 0.0332
/*69  */         return (!s->mask) << 2;					/* GLOBALMASK */                        // 0.0
/*73  */     case 0x4c:	/* INTC_PROTECTION */                                        // 0.0
/*78  */     case 0x50:	/* INTC_IDLE */                                              // 0.0
/*80  */         return s->autoidle & 3;                                             // 0.0
/*84  */     /* Per-bank registers */                                                // 0.0
/*86  */     case 0x80:	/* INTC_ITR */                                               // 0.0
/*88  */         return bank->inputs;                                                // 0.0
/*92  */     case 0x84:	/* INTC_MIR */                                               // 0.0
/*94  */         return bank->mask;                                                  // 0.0
/*98  */     case 0x88:	/* INTC_MIR_CLEAR */                                         // 0.0
/*100 */     case 0x8c:	/* INTC_MIR_SET */                                           // 0.0
/*105 */     case 0x90:	/* INTC_ISR_SET */                                           // 0.0
/*107 */         return bank->swi;                                                   // 0.0
/*111 */     case 0x94:	/* INTC_ISR_CLEAR */                                         // 0.0
/*116 */     case 0x98:	/* INTC_PENDING_IRQ */                                       // 0.0
/*118 */         return bank->irqs & ~bank->mask & ~bank->fiq;                       // 0.0
/*122 */     case 0x9c:	/* INTC_PENDING_FIQ */                                       // 0.0
/*124 */         return bank->irqs & ~bank->mask & bank->fiq;                        // 0.0
/*128 */     /* Per-line registers */                                                // 0.0
/*130 */     case 0x100 ... 0x300:	/* INTC_ILR */                                    // 0.0
/*132 */         bank_no = (offset - 0x100) >> 7;                                    // 0.0
/*134 */         if (bank_no > s->nbanks)                                            // 0.0
/*136 */             break;                                                          // 0.0
/*138 */         bank = &s->bank[bank_no];                                           // 0.0
/*140 */         line_no = (offset & 0x7f) >> 2;                                     // 0.0
/*142 */         return (bank->priority[line_no] << 2) |                             // 0.0
/*144 */                 ((bank->fiq >> line_no) & 1);                               // 0.0
/*146 */     }                                                                       // 0.0
/*150 */ }                                                                           // 0.0
