// commit message FFmpeg@7cc8d616aa (target=1, prob=0.9990453, correct=True): Fix unaligned accesses by doing bytewise access until aligned, then continuing in 32-bit quantities. Fixes crash observed on sparc during FATE mlp test. Patch by Ramiro.
/*0  */ uint8_t ff_mlp_calculate_parity(const uint8_t *buf, unsigned int buf_size)  // (0) 0.1923
/*2  */ {                                                                           // (8) 0.00641
/*4  */     uint32_t scratch = 0;                                                   // (6) 0.07051
/*6  */     const uint8_t *buf_end = buf + buf_size;                                // (2) 0.1218
/*12 */     for (; buf < buf_end - 3; buf += 4)                                     // (3) 0.1154
/*14 */         scratch ^= *((const uint32_t*)buf);                                 // (1) 0.1282
/*18 */     scratch = xor_32_to_8(scratch);                                         // (4) 0.109
/*22 */     for (; buf < buf_end; buf++)                                            // (5) 0.08974
/*27 */     return scratch;                                                         // (7) 0.03846
/*29 */ }                                                                           // (9) 0.00641
