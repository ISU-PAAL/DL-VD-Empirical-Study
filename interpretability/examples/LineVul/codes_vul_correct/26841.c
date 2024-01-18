// commit message qemu@8be487d8f1 (target=1, prob=0.51809996, correct=True): sdhci: convert the DPRINT() calls into trace events
/*0  */ static void sdhci_write_dataport(SDHCIState *s, uint32_t value, unsigned size)  // (4) 0.06635
/*2  */ {                                                                               // (21) 0.00237
/*4  */     unsigned i;                                                                 // (18) 0.01422
/*8  */     /* Check that there is free space left in a buffer */                       // (12) 0.03555
/*10 */     if (!(s->prnsts & SDHC_SPACE_AVAILABLE)) {                                  // (8) 0.05687
/*12 */         ERRPRINT("Can't write to data buffer: buffer full\n");                  // (9) 0.05687
/*14 */         return;                                                                 // (16) 0.02133
/*16 */     }                                                                           // (19) 0.009479
/*20 */     for (i = 0; i < size; i++) {                                                // (11) 0.03791
/*22 */         s->fifo_buffer[s->data_count] = value & 0xFF;                           // (6) 0.06398
/*24 */         s->data_count++;                                                        // (13) 0.03081
/*26 */         value >>= 8;                                                            // (14) 0.02844
/*28 */         if (s->data_count >= (s->blksize & 0x0fff)) {                           // (5) 0.06635
/*30 */             DPRINT_L2("write buffer filled with %u bytes of data\n",            // (2) 0.06872
/*32 */                     s->data_count);                                             // (7) 0.05924
/*34 */             s->data_count = 0;                                                  // (10) 0.04502
/*36 */             s->prnsts &= ~SDHC_SPACE_AVAILABLE;                                 // (0) 0.07109
/*38 */             if (s->prnsts & SDHC_DOING_WRITE) {                                 // (3) 0.06872
/*40 */                 sdhci_write_block_to_card(s);                                   // (1) 0.06872
/*42 */             }                                                                   // (15) 0.02844
/*44 */         }                                                                       // (17) 0.01896
/*46 */     }                                                                           // (20) 0.009479
/*48 */ }                                                                               // (22) 0.00237
