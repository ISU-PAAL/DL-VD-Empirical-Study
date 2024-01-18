// commit message qemu@496272a701 (target=0, prob=0.07552618, correct=True): target-ppc: Disentangle hash mmu helper functions
/*0  */ int check_prot(int prot, int rw, int access_type)  // (0) 0.05782
/*2  */ {                                                  // (22) 0.003401
/*4  */     int ret;                                       // (18) 0.02041
/*8  */     if (access_type == ACCESS_CODE) {              // (4) 0.05442
/*10 */         if (prot & PAGE_EXEC) {                    // (1) 0.05782
/*12 */             ret = 0;                               // (8) 0.05102
/*14 */         } else {                                   // (12) 0.03401
/*16 */             ret = -2;                              // (5) 0.05442
/*18 */         }                                          // (15) 0.02721
/*20 */     } else if (rw) {                               // (11) 0.03401
/*22 */         if (prot & PAGE_WRITE) {                   // (2) 0.05782
/*24 */             ret = 0;                               // (9) 0.05102
/*26 */         } else {                                   // (13) 0.03401
/*28 */             ret = -2;                              // (6) 0.05442
/*30 */         }                                          // (16) 0.02721
/*32 */     } else {                                       // (19) 0.02041
/*34 */         if (prot & PAGE_READ) {                    // (3) 0.05442
/*36 */             ret = 0;                               // (10) 0.05102
/*38 */         } else {                                   // (14) 0.03401
/*40 */             ret = -2;                              // (7) 0.05442
/*42 */         }                                          // (17) 0.02721
/*44 */     }                                              // (21) 0.01361
/*48 */     return ret;                                    // (20) 0.02041
/*50 */ }                                                  // (23) 0.003401
