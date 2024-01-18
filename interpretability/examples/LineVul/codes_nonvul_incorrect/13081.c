// commit message FFmpeg@caa845851d (target=0, prob=0.7660135, correct=False): mlpdec: validate that the reported channel count matches the actual output channel count
/*0  */ static int output_data_internal(MLPDecodeContext *m, unsigned int substr,          // (10) 0.04124
/*2  */                                 uint8_t *data, unsigned int *data_size, int is32)  // (0) 0.101
/*4  */ {                                                                                  // (20) 0.002062
/*6  */     SubStream *s = &m->substream[substr];                                          // (14) 0.03505
/*8  */     unsigned int i, out_ch = 0;                                                    // (15) 0.0268
/*10 */     int32_t *data_32 = (int32_t*) data;                                            // (11) 0.04124
/*12 */     int16_t *data_16 = (int16_t*) data;                                            // (12) 0.04124
/*16 */     if (*data_size < (s->max_channel + 1) * s->blockpos * (is32 ? 4 : 2))          // (4) 0.06598
/*18 */         return -1;                                                                 // (16) 0.02268
/*22 */     for (i = 0; i < s->blockpos; i++) {                                            // (13) 0.03918
/*24 */         for (out_ch = 0; out_ch <= s->max_matrix_channel; out_ch++) {              // (3) 0.06804
/*26 */             int mat_ch = s->ch_assign[out_ch];                                     // (6) 0.05567
/*28 */             int32_t sample = m->sample_buffer[i][mat_ch]                           // (5) 0.05979
/*30 */                           << s->output_shift[mat_ch];                              // (1) 0.07423
/*32 */             s->lossless_check_data ^= (sample & 0xffffff) << mat_ch;               // (2) 0.0701
/*34 */             if (is32) *data_32++ = sample << 8;                                    // (8) 0.05361
/*36 */             else      *data_16++ = sample >> 8;                                    // (7) 0.05567
/*38 */         }                                                                          // (17) 0.01649
/*40 */     }                                                                              // (19) 0.008247
/*44 */     *data_size = i * out_ch * (is32 ? 4 : 2);                                      // (9) 0.04536
/*48 */     return 0;                                                                      // (18) 0.01237
/*50 */ }                                                                                  // (21) 0.002062
