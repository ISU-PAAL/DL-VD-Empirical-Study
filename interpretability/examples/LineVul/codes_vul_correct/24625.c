// commit message FFmpeg@48aecf5a7d (target=1, prob=0.6661343, correct=True): Fix a bug causing the generated stream to be corrupt if the buffer contains NAL units previous to the IDR where the SPS/PPS was inserted.
/*0  */ static void alloc_and_copy(uint8_t **poutbuf,          int *poutbuf_size,  // (2) 0.08479
/*2  */                            const uint8_t *sps_pps, uint32_t sps_pps_size,  // (0) 0.1197
/*4  */                            const uint8_t *in,      uint32_t in_size) {     // (1) 0.1197
/*6  */     uint32_t offset = *poutbuf_size;                                       // (11) 0.0399
/*8  */     uint8_t nal_header_size = offset ? 3 : 4;                              // (9) 0.04988
/*12 */     *poutbuf_size += sps_pps_size+in_size+nal_header_size;                 // (6) 0.06983
/*14 */     *poutbuf = av_realloc(*poutbuf, *poutbuf_size);                        // (8) 0.05985
/*16 */     if (sps_pps)                                                           // (12) 0.02494
/*18 */         memcpy(*poutbuf+offset, sps_pps, sps_pps_size);                    // (4) 0.07232
/*20 */     memcpy(*poutbuf+sps_pps_size+nal_header_size+offset, in, in_size);     // (3) 0.08229
/*22 */     if (!offset)                                                           // (13) 0.01746
/*24 */         AV_WB32(*poutbuf+sps_pps_size, 1);                                 // (7) 0.06234
/*26 */     else {                                                                 // (14) 0.01247
/*28 */         (*poutbuf+offset)[0] = (*poutbuf+offset)[1] = 0;                   // (5) 0.07232
/*30 */         (*poutbuf+offset)[2] = 1;                                          // (10) 0.04738
/*32 */     }                                                                      // (15) 0.009975
/*34 */ }                                                                          // (16) 0.002494
