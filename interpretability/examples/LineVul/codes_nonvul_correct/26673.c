// commit message qemu@c6a6a5e3bb (target=0, prob=0.05048559, correct=True): e1000: use common checksumming code
/*0  */ do_cksum(uint8_t *dp, uint8_t *de)             // (3) 0.1357
/*2  */ {                                              // (7) 0.007143
/*4  */     unsigned int bsum[2] = {0, 0}, i, sum;     // (2) 0.1429
/*8  */     for (i = 1; dp < de; bsum[i^=1] += *dp++)  // (0) 0.1857
/*10 */         ;                                      // (6) 0.05714
/*12 */     sum = (bsum[0] << 8) + bsum[1];            // (1) 0.1429
/*14 */     sum = (sum >> 16) + (sum & 0xffff);        // (4) 0.1286
/*16 */     return ~(sum + (sum >> 16));               // (5) 0.09286
/*18 */ }                                              // (8) 0.007143
