// commit message FFmpeg@6e42e6c4b4 (target=1, prob=0.99072087, correct=True): cosmetics attack, part I: Remove all tabs and prettyprint/reindent the code.
/*0  */ void rgb15tobgr15(const uint8_t *src, uint8_t *dst, long src_size)  // (1) 0.1343
/*2  */ {                                                                   // (13) 0.00463
/*4  */ 	long i;                                                            // (10) 0.01852
/*6  */ 	long num_pixels = src_size >> 1;                                   // (5) 0.06019
/*10 */ 	for(i=0; i<num_pixels; i++)                                        // (4) 0.07407
/*12 */ 	{                                                                  // (12) 0.009259
/*14 */ 	    unsigned b,g,r;                                                // (9) 0.05093
/*16 */ 	    register uint16_t rgb;                                         // (8) 0.05093
/*18 */ 	    rgb = src[2*i];                                                // (7) 0.05556
/*20 */ 	    r = rgb&0x1F;                                                  // (6) 0.06019
/*22 */ 	    g = (rgb&0x3E0)>>5;                                            // (3) 0.08796
/*24 */ 	    b = (rgb&0x7C00)>>10;                                          // (2) 0.08796
/*26 */ 	    dst[2*i] = (b&0x1F) | ((g&0x1F)<<5) | ((r&0x1F)<<10);          // (0) 0.1991
/*28 */ 	}                                                                  // (11) 0.009259
/*30 */ }                                                                   // (14) 0.00463
