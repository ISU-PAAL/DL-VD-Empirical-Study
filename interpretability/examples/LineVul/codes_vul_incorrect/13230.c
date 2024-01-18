// commit message FFmpeg@f78cd0c243 (target=1, prob=0.3895396, correct=False): prores-idct: fix overflow in c code.
/*0  */ void FUNC(ff_simple_idct)(DCTELEM *block)  // (2) 0.1681
/*2  */ {                                          // (6) 0.00885
/*4  */     int i;                                 // (5) 0.0531
/*8  */     for (i = 0; i < 8; i++)                // (4) 0.1327
/*10 */         FUNC(idctRowCondDC)(block + i*8);  // (0) 0.1947
/*14 */     for (i = 0; i < 8; i++)                // (3) 0.1327
/*16 */         FUNC(idctSparseCol)(block + i);    // (1) 0.177
/*18 */ }                                          // (7) 0.00885
