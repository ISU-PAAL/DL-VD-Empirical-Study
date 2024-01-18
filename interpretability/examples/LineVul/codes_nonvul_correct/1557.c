// commit message qemu@e40a67beed (target=0, prob=0.020959573, correct=True): target-sh4: fix TLB invalidation code
/*0  */  void cpu_sh4_invalidate_tlb(CPUSH4State *s)  // (2) 0.1031
/*2  */ {                                             // (13) 0.005155
/*4  */     int i;                                    // (10) 0.03093
/*8  */     /* UTLB */                                // (8) 0.04124
/*10 */     for (i = 0; i < UTLB_SIZE; i++) {         // (3) 0.1031
/*12 */         tlb_t * entry = &s->utlb[i];          // (0) 0.1134
/*14 */         entry->v = 0;                         // (5) 0.06701
/*16 */     }                                         // (11) 0.02062
/*18 */     /* ITLB */                                // (9) 0.03608
/*20 */     for (i = 0; i < UTLB_SIZE; i++) {         // (4) 0.1031
/*22 */         tlb_t * entry = &s->utlb[i];          // (1) 0.1134
/*24 */         entry->v = 0;                         // (6) 0.06701
/*26 */     }                                         // (12) 0.02062
/*30 */     tlb_flush(s, 1);                          // (7) 0.06186
/*32 */ }                                             // (14) 0.005155
