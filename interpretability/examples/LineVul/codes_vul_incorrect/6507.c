// commit message qemu@5a1972c847 (target=1, prob=0.17945585, correct=False): ppc405_uc: Fix buffer overflow
/*0  */ static void ppc4xx_pob_reset (void *opaque)  // (0) 0.1574
/*2  */ {                                            // (7) 0.009259
/*4  */     ppc4xx_pob_t *pob;                       // (1) 0.1481
/*8  */     pob = opaque;                            // (5) 0.07407
/*10 */     /* No error */                           // (6) 0.06481
/*12 */     pob->bear = 0x00000000;                  // (4) 0.1111
/*14 */     pob->besr[0] = 0x0000000;                // (2) 0.1481
/*16 */     pob->besr[1] = 0x0000000;                // (3) 0.1481
/*18 */ }                                            // (8) 0.009259
