// commit message qemu@d368ba4376 (target=0, prob=0.32494262, correct=True): sdhci: Remove class "virtual" methods
/*0  */ static void sdhci_write_block_to_card(SDHCIState *s)                            // (9) 0.04102
/*2  */ {                                                                               // (25) 0.001953
/*4  */     int index = 0;                                                              // (19) 0.01562
/*8  */     if (s->prnsts & SDHC_SPACE_AVAILABLE) {                                     // (8) 0.04492
/*10 */         if (s->norintstsen & SDHC_NISEN_WBUFRDY) {                              // (1) 0.05859
/*12 */             s->norintsts |= SDHC_NIS_WBUFRDY;                                   // (2) 0.05859
/*14 */         }                                                                       // (20) 0.01562
/*16 */         sdhci_update_irq(s);                                                    // (13) 0.03516
/*18 */         return;                                                                 // (18) 0.01758
/*20 */     }                                                                           // (22) 0.007812
/*24 */     if (s->trnmod & SDHC_TRNS_BLK_CNT_EN) {                                     // (5) 0.05078
/*26 */         if (s->blkcnt == 0) {                                                   // (11) 0.03711
/*28 */             return;                                                             // (16) 0.02539
/*30 */         } else {                                                                // (17) 0.01953
/*32 */             s->blkcnt--;                                                        // (12) 0.03711
/*34 */         }                                                                       // (21) 0.01562
/*36 */     }                                                                           // (23) 0.007812
/*40 */     for (index = 0; index < (s->blksize & 0x0fff); index++) {                   // (6) 0.05078
/*42 */         sd_write_data(s->card, s->fifo_buffer[index]);                          // (4) 0.05078
/*44 */     }                                                                           // (24) 0.007812
/*48 */     /* Next data can be written through BUFFER DATORT register */               // (14) 0.0332
/*50 */     s->prnsts |= SDHC_SPACE_AVAILABLE;                                          // (10) 0.04102
/*54 */     /* Finish transfer if that was the last block of data */                    // (15) 0.0293
/*56 */     if ((s->trnmod & SDHC_TRNS_MULTI) == 0 ||                                   // (7) 0.04688
/*58 */             ((s->trnmod & SDHC_TRNS_MULTI) &&                                   // (3) 0.05664
/*60 */             (s->trnmod & SDHC_TRNS_BLK_CNT_EN) && (s->blkcnt == 0))) {          // (0) 0.08594
/*62 */         SDHCI_GET_CLASS(s)->end_data_transfer(s);                               // 0.0
/*64 */     } else if (s->norintstsen & SDHC_NISEN_WBUFRDY) {                           // 0.0
/*66 */         s->norintsts |= SDHC_NIS_WBUFRDY;                                       // 0.0
/*68 */     }                                                                           // 0.0
/*72 */     /* Generate Block Gap Event if requested and if not the last block */       // 0.0
/*74 */     if (s->stopped_state == sdhc_gap_write && (s->trnmod & SDHC_TRNS_MULTI) &&  // 0.0
/*76 */             s->blkcnt > 0) {                                                    // 0.0
/*78 */         s->prnsts &= ~SDHC_DOING_WRITE;                                         // 0.0
/*80 */         if (s->norintstsen & SDHC_EISEN_BLKGAP) {                               // 0.0
/*82 */             s->norintsts |= SDHC_EIS_BLKGAP;                                    // 0.0
/*84 */         }                                                                       // 0.0
/*86 */         SDHCI_GET_CLASS(s)->end_data_transfer(s);                               // 0.0
/*88 */     }                                                                           // 0.0
/*92 */     sdhci_update_irq(s);                                                        // 0.0
/*94 */ }                                                                               // 0.0
