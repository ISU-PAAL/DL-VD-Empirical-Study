// commit message FFmpeg@54b2d317ed (target=0, prob=0.7186422, correct=False): ffv1: avoid checking a double for equality
/*0  */ static void find_best_state(uint8_t best_state[256][256], const uint8_t one_state[256]){  // (3) 0.0625
/*2  */     int i,j,k,m;                                                                          // (19) 0.02344
/*4  */     double l2tab[256];                                                                    // (20) 0.01953
/*8  */     for(i=1; i<256; i++)                                                                  // (17) 0.0293
/*10 */         l2tab[i]= log2(i/256.0);                                                          // (8) 0.04297
/*14 */     for(i=0; i<256; i++){                                                                 // (14) 0.03125
/*16 */         double best_len[256];                                                             // (18) 0.02734
/*18 */         double p= i/256.0;                                                                // (15) 0.03125
/*22 */         for(j=0; j<256; j++)                                                              // (11) 0.03711
/*24 */             best_len[j]= 1<<30;                                                           // (9) 0.04102
/*28 */         for(j=FFMAX(i-10,1); j<FFMIN(i+11,256); j++){                                     // (2) 0.06641
/*30 */             double occ[256]={0};                                                          // (12) 0.03711
/*32 */             double len=0;                                                                 // (16) 0.03125
/*34 */             occ[j]=1.0;                                                                   // (13) 0.03711
/*36 */             for(k=0; k<256; k++){                                                         // (7) 0.04687
/*38 */                 double newocc[256]={0};                                                   // (6) 0.04687
/*40 */                 for(m=0; m<256; m++){                                                     // (4) 0.05469
/*42 */                     if(occ[m]){                                                           // (5) 0.05078
/*44 */                         len -=occ[m]*(     p *l2tab[    m]                                // (1) 0.08984
/*46 */                                       + (1-p)*l2tab[256-m]);                              // (0) 0.09961
/*48 */                     }                                                                     // (10) 0.03906
/*50 */                 }                                                                         // 0.0
/*52 */                 if(len < best_len[k]){                                                    // 0.0
/*54 */                     best_len[k]= len;                                                     // 0.0
/*56 */                     best_state[i][k]= j;                                                  // 0.0
/*58 */                 }                                                                         // 0.0
/*60 */                 for(m=0; m<256; m++){                                                     // 0.0
/*62 */                     if(occ[m]){                                                           // 0.0
/*64 */                         newocc[    one_state[    m]] += occ[m]*   p ;                     // 0.0
/*66 */                         newocc[256-one_state[256-m]] += occ[m]*(1-p);                     // 0.0
/*68 */                     }                                                                     // 0.0
/*70 */                 }                                                                         // 0.0
/*72 */                 memcpy(occ, newocc, sizeof(occ));                                         // 0.0
/*74 */             }                                                                             // 0.0
/*76 */         }                                                                                 // 0.0
/*78 */     }                                                                                     // 0.0
/*80 */ }                                                                                         // 0.0
