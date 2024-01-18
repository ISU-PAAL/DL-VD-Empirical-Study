// commit message qemu@2725aec701 (target=1, prob=0.9620813, correct=True): i440fx: avoid destroying memory regions within a transaction
/*0  */ static void i440fx_update_memory_mappings(PCII440FXState *d)                    // (7) 0.0566
/*2  */ {                                                                               // (16) 0.002695
/*4  */     int i, r;                                                                   // (14) 0.02156
/*6  */     uint32_t smram;                                                             // (12) 0.02695
/*8  */     bool smram_enabled;                                                         // (13) 0.02426
/*12 */     memory_region_transaction_begin();                                          // (10) 0.03235
/*14 */     update_pam(d, 0xf0000, 0x100000, (d->dev.config[I440FX_PAM] >> 4) & 3,      // (1) 0.1051
/*16 */                &d->pam_regions[0]);                                             // (5) 0.06739
/*18 */     for(i = 0; i < 12; i++) {                                                   // (9) 0.04313
/*20 */         r = (d->dev.config[(i >> 1) + (I440FX_PAM + 1)] >> ((i & 1) * 4)) & 3;  // (0) 0.1186
/*22 */         update_pam(d, 0xc0000 + 0x4000 * i, 0xc0000 + 0x4000 * (i + 1), r,      // (2) 0.1051
/*24 */                    &d->pam_regions[i+1]);                                       // (4) 0.08356
/*26 */     }                                                                           // (15) 0.01078
/*28 */     smram = d->dev.config[I440FX_SMRAM];                                        // (8) 0.05121
/*30 */     smram_enabled = (d->smm_enabled && (smram & 0x08)) || (smram & 0x40);       // (3) 0.08895
/*32 */     memory_region_set_enabled(&d->smram_region, !smram_enabled);                // (6) 0.06469
/*34 */     memory_region_transaction_commit();                                         // (11) 0.03235
/*36 */ }                                                                               // (17) 0.002695
