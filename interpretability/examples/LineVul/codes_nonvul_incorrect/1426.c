// commit message FFmpeg@b8664c9294 (target=0, prob=0.7066741, correct=False): avcodec/vp8dsp: add VP7 idct and loop filter
/*0  */ static void vp8_idct_dc_add4uv_c(uint8_t *dst, int16_t block[4][16], ptrdiff_t stride)  // (0) 0.2253
/*2  */ {                                                                                       // (5) 0.005495
/*4  */     vp8_idct_dc_add_c(dst+stride*0+0, block[0], stride);                                // (2) 0.1758
/*6  */     vp8_idct_dc_add_c(dst+stride*0+4, block[1], stride);                                // (3) 0.1758
/*8  */     vp8_idct_dc_add_c(dst+stride*4+0, block[2], stride);                                // (4) 0.1758
/*10 */     vp8_idct_dc_add_c(dst+stride*4+4, block[3], stride);                                // (1) 0.1758
/*12 */ }                                                                                       // (6) 0.005495
