// commit message qemu@d368ba4376 (target=0, prob=0.060881387, correct=True): sdhci: Remove class "virtual" methods
/*0  */ static inline void sdhci_blkgap_write(SDHCIState *s, uint8_t value)              // (8) 0.05078
/*2  */ {                                                                                // (19) 0.001953
/*4  */     if ((value & SDHC_STOP_AT_GAP_REQ) && (s->blkgap & SDHC_STOP_AT_GAP_REQ)) {  // (0) 0.08594
/*6  */         return;                                                                  // (16) 0.01758
/*8  */     }                                                                            // (18) 0.007812
/*10 */     s->blkgap = value & SDHC_STOP_AT_GAP_REQ;                                    // (10) 0.04883
/*14 */     if ((value & SDHC_CONTINUE_REQ) && s->stopped_state &&                       // (11) 0.04883
/*16 */             (s->blkgap & SDHC_STOP_AT_GAP_REQ) == 0) {                           // (3) 0.07031
/*18 */         if (s->stopped_state == sdhc_gap_read) {                                 // (12) 0.04883
/*20 */             s->prnsts |= SDHC_DAT_LINE_ACTIVE | SDHC_DOING_READ;                 // (2) 0.07227
/*22 */             SDHCI_GET_CLASS(s)->read_block_from_card(s);                         // (4) 0.0625
/*24 */         } else {                                                                 // (15) 0.01953
/*26 */             s->prnsts |= SDHC_DAT_LINE_ACTIVE | SDHC_DOING_WRITE;                // (1) 0.07422
/*28 */             SDHCI_GET_CLASS(s)->write_block_to_card(s);                          // (5) 0.0625
/*30 */         }                                                                        // (17) 0.01562
/*32 */         s->stopped_state = sdhc_not_stopped;                                     // (14) 0.04492
/*34 */     } else if (!s->stopped_state && (value & SDHC_STOP_AT_GAP_REQ)) {            // (6) 0.0625
/*36 */         if (s->prnsts & SDHC_DOING_READ) {                                       // (13) 0.04688
/*38 */             s->stopped_state = sdhc_gap_read;                                    // (9) 0.05078
/*40 */         } else if (s->prnsts & SDHC_DOING_WRITE) {                               // (7) 0.05273
/*42 */             s->stopped_state = sdhc_gap_write;                                   // 0.0
/*44 */         }                                                                        // 0.0
/*46 */     }                                                                            // 0.0
/*48 */ }                                                                                // 0.0
