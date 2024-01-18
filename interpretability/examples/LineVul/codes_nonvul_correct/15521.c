// commit message qemu@aea390e4be (target=0, prob=0.011388693, correct=True): mmu-hash*: Separate PTEG searching from permissions checking
/*0  */ static int ppc_hash64_pte_update_flags(struct mmu_ctx_hash64 *ctx,  // (2) 0.06468
/*2  */                                        target_ulong *pte1p,         // (0) 0.1194
/*4  */                                        int ret, int rw)             // (1) 0.1119
/*6  */ {                                                                   // (21) 0.002488
/*8  */     int store = 0;                                                  // (15) 0.0199
/*12 */     /* Update page flags */                                         // (16) 0.0199
/*14 */     if (!(*pte1p & HPTE64_R_R)) {                                   // (6) 0.04975
/*16 */         /* Update accessed flag */                                  // (12) 0.02985
/*18 */         *pte1p |= HPTE64_R_R;                                       // (5) 0.05473
/*20 */         store = 1;                                                  // (13) 0.02736
/*22 */     }                                                               // (19) 0.00995
/*24 */     if (!(*pte1p & HPTE64_R_C)) {                                   // (7) 0.04975
/*26 */         if (rw == 1 && ret == 0) {                                  // (9) 0.04478
/*28 */             /* Update changed flag */                               // (10) 0.0398
/*30 */             *pte1p |= HPTE64_R_C;                                   // (3) 0.06468
/*32 */             store = 1;                                              // (11) 0.03731
/*34 */         } else {                                                    // (14) 0.02488
/*36 */             /* Force page fault for first write access */           // (8) 0.04975
/*38 */             ctx->prot &= ~PAGE_WRITE;                               // (4) 0.0597
/*40 */         }                                                           // (17) 0.0199
/*42 */     }                                                               // (20) 0.00995
/*46 */     return store;                                                   // (18) 0.01493
/*48 */ }                                                                   // (22) 0.002488
