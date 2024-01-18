// commit message FFmpeg@6e42e6c4b4 (target=1, prob=0.99774855, correct=True): cosmetics attack, part I: Remove all tabs and prettyprint/reindent the code.
/*0  */ void palette8tobgr24(const uint8_t *src, uint8_t *dst, long num_pixels, const uint8_t *palette)  // (0) 0.1797
/*2  */ {                                                                                                // (13) 0.004608
/*4  */ 	long i;                                                                                         // (10) 0.01843
/*6  */ /*                                                                                               // (14) 0.004608
/*8  */ 	writes 1 byte o much and might cause alignment issues on some architectures?                    // (5) 0.07373
/*10 */ 	for(i=0; i<num_pixels; i++)                                                                     // (6) 0.07373
/*12 */ 		((unsigned *)(&dst[i*3])) = ((unsigned *)palette)[ src[i] ];                                   // (1) 0.1244
/*14 */ */                                                                                               // (15) 0.004608
/*16 */ 	for(i=0; i<num_pixels; i++)                                                                     // (7) 0.07373
/*18 */ 	{                                                                                               // (11) 0.009217
/*20 */ 		//FIXME slow?                                                                                  // (8) 0.03226
/*22 */ 		dst[0]= palette[ src[i]*4+0 ];                                                                 // (2) 0.08295
/*24 */ 		dst[1]= palette[ src[i]*4+1 ];                                                                 // (3) 0.08295
/*26 */ 		dst[2]= palette[ src[i]*4+2 ];                                                                 // (4) 0.08295
/*28 */ 		dst+= 3;                                                                                       // (9) 0.03226
/*30 */ 	}                                                                                               // (12) 0.009217
/*32 */ }                                                                                                // (16) 0.004608
