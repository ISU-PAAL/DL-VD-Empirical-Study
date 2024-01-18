// commit message qemu@0dacea92d2 (target=1, prob=0.13946123, correct=False): net: Transmit zero UDP checksum as 0xFFFF
/*0  */ putsum(uint8_t *data, uint32_t n, uint32_t sloc, uint32_t css, uint32_t cse)  // (0) 0.2312
/*2  */ {                                                                             // (8) 0.00625
/*4  */     uint32_t sum;                                                             // (6) 0.05625
/*8  */     if (cse && cse < n)                                                       // (5) 0.08125
/*10 */         n = cse + 1;                                                          // (3) 0.0875
/*12 */     if (sloc < n-1) {                                                         // (4) 0.08125
/*14 */         sum = net_checksum_add(n-css, data+css);                              // (2) 0.15
/*16 */         stw_be_p(data + sloc, net_checksum_finish(sum));                      // (1) 0.1813
/*18 */     }                                                                         // (7) 0.025
/*20 */ }                                                                             // (9) 0.00625
