// commit message FFmpeg@6e42e6c4b4 (target=1, prob=0.99787486, correct=True): cosmetics attack, part I: Remove all tabs and prettyprint/reindent the code.
/*0  */ void palette8tobgr16(const uint8_t *src, uint8_t *dst, long num_pixels, const uint8_t *palette)  // (0) 0.3679
/*2  */ {                                                                                                // (4) 0.009434
/*4  */ 	long i;                                                                                         // (3) 0.03774
/*6  */ 	for(i=0; i<num_pixels; i++)                                                                     // (2) 0.1509
/*8  */ 		((uint16_t *)dst)[i] = bswap_16(((uint16_t *)palette)[ src[i] ]);                              // (1) 0.3302
/*10 */ }                                                                                                // (5) 0.009434
