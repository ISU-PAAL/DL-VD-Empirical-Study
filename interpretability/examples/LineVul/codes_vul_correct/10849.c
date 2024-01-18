// commit message FFmpeg@7f526efd17 (target=1, prob=0.9926131, correct=True): Change unsigned->signed and int->long, this fits the asm code better on 64 bit systems. Also fixes several crashes because (long)-i is incorrect if i is unsigned.
/*0  */ void rgb15tobgr15(const uint8_t *src, uint8_t *dst, unsigned int src_size)  // (1) 0.1376
/*2  */ {                                                                           // (13) 0.004587
/*4  */ 	unsigned i;                                                                // (10) 0.01835
/*6  */ 	unsigned num_pixels = src_size >> 1;                                       // (5) 0.05963
/*8  */ 	                                                                           // (14) 0.004587
/*10 */ 	for(i=0; i<num_pixels; i++)                                                // (4) 0.07339
/*12 */ 	{                                                                          // (11) 0.009174
/*14 */ 	    unsigned b,g,r;                                                        // (8) 0.05046
/*16 */ 	    register uint16_t rgb;                                                 // (9) 0.05046
/*18 */ 	    rgb = src[2*i];                                                        // (7) 0.05505
/*20 */ 	    r = rgb&0x1F;                                                          // (6) 0.05963
/*22 */ 	    g = (rgb&0x3E0)>>5;                                                    // (2) 0.08716
/*24 */ 	    b = (rgb&0x7C00)>>10;                                                  // (3) 0.08716
/*26 */ 	    dst[2*i] = (b&0x1F) | ((g&0x1F)<<5) | ((r&0x1F)<<10);                  // (0) 0.1972
/*28 */ 	}                                                                          // (12) 0.009174
/*30 */ }                                                                           // (15) 0.004587
