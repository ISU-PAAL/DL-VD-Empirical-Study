// commit message FFmpeg@1acd7d594c (target=0, prob=0.77416927, correct=False): h264: integrate clear_blocks calls with IDCT.
/*0  */ void FUNCC(ff_h264_idct_dc_add)(uint8_t *_dst, int16_t *block, int stride){  // (0) 0.1813
/*2  */     int i, j;                                                                // (8) 0.04145
/*4  */     int dc = (((dctcoef*)block)[0] + 32) >> 6;                               // (2) 0.1192
/*6  */     pixel *dst = (pixel*)_dst;                                               // (5) 0.07772
/*8  */     stride >>= sizeof(pixel)-1;                                              // (6) 0.06218
/*10 */     for( j = 0; j < 4; j++ )                                                 // (4) 0.0829
/*12 */     {                                                                        // (9) 0.02073
/*14 */         for( i = 0; i < 4; i++ )                                             // (3) 0.1036
/*16 */             dst[i] = av_clip_pixel( dst[i] + dc );                           // (1) 0.1503
/*18 */         dst += stride;                                                       // (7) 0.05699
/*20 */     }                                                                        // (10) 0.02073
/*22 */ }                                                                            // (11) 0.005181
