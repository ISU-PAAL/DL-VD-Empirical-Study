// commit message qemu@496272a701 (target=0, prob=0.026858933, correct=True): target-ppc: Disentangle hash mmu helper functions
/*0  */ int pte_update_flags(mmu_ctx_t *ctx, target_ulong *pte1p,  // (0) 0.08333
/*2  */                      int ret, int rw)                      // (1) 0.08333
/*4  */ {                                                          // (20) 0.003086
/*6  */     int store = 0;                                         // (14) 0.02469
/*10 */     /* Update page flags */                                // (15) 0.02469
/*12 */     if (!(*pte1p & 0x00000100)) {                          // (7) 0.05247
/*14 */         /* Update accessed flag */                         // (11) 0.03704
/*16 */         *pte1p |= 0x00000100;                              // (5) 0.05864
/*18 */         store = 1;                                         // (12) 0.03395
/*20 */     }                                                      // (18) 0.01235
/*22 */     if (!(*pte1p & 0x00000080)) {                          // (8) 0.05247
/*24 */         if (rw == 1 && ret == 0) {                         // (6) 0.05556
/*26 */             /* Update changed flag */                      // (9) 0.04938
/*28 */             *pte1p |= 0x00000080;                          // (3) 0.07099
/*30 */             store = 1;                                     // (10) 0.0463
/*32 */         } else {                                           // (13) 0.03086
/*34 */             /* Force page fault for first write access */  // (4) 0.06173
/*36 */             ctx->prot &= ~PAGE_WRITE;                      // (2) 0.07407
/*38 */         }                                                  // (16) 0.02469
/*40 */     }                                                      // (19) 0.01235
/*44 */     return store;                                          // (17) 0.01852
/*46 */ }                                                          // (21) 0.003086
