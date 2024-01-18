// commit message qemu@d368ba4376 (target=0, prob=0.4799211, correct=True): sdhci: Remove class "virtual" methods
/*0  */ static void sdhci_write_dataport(SDHCIState *s, uint32_t value, unsigned size)  // (4) 0.06527
/*2  */ {                                                                               // (21) 0.002331
/*4  */     unsigned i;                                                                 // (18) 0.01399
/*8  */     /* Check that there is free space left in a buffer */                       // (12) 0.03497
/*10 */     if (!(s->prnsts & SDHC_SPACE_AVAILABLE)) {                                  // (8) 0.05594
/*12 */         ERRPRINT("Can't write to data buffer: buffer full\n");                  // (9) 0.05594
/*14 */         return;                                                                 // (16) 0.02098
/*16 */     }                                                                           // (19) 0.009324
/*20 */     for (i = 0; i < size; i++) {                                                // (11) 0.0373
/*22 */         s->fifo_buffer[s->data_count] = value & 0xFF;                           // (6) 0.06294
/*24 */         s->data_count++;                                                        // (13) 0.0303
/*26 */         value >>= 8;                                                            // (14) 0.02797
/*28 */         if (s->data_count >= (s->blksize & 0x0fff)) {                           // (5) 0.06527
/*30 */             DPRINT_L2("write buffer filled with %u bytes of data\n",            // (2) 0.0676
/*32 */                     s->data_count);                                             // (7) 0.05828
/*34 */             s->data_count = 0;                                                  // (10) 0.04429
/*36 */             s->prnsts &= ~SDHC_SPACE_AVAILABLE;                                 // (1) 0.06993
/*38 */             if (s->prnsts & SDHC_DOING_WRITE) {                                 // (3) 0.0676
/*40 */                 SDHCI_GET_CLASS(s)->write_block_to_card(s);                     // (0) 0.08392
/*42 */             }                                                                   // (15) 0.02797
/*44 */         }                                                                       // (17) 0.01865
/*46 */     }                                                                           // (20) 0.009324
/*48 */ }                                                                               // (22) 0.002331
