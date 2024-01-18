// commit message FFmpeg@7f526efd17 (target=1, prob=0.9754377, correct=True): Change unsigned->signed and int->long, this fits the asm code better on 64 bit systems. Also fixes several crashes because (long)-i is incorrect if i is unsigned.
/*0  */ static inline void RENAME(yv12touyvy)(const uint8_t *ysrc, const uint8_t *usrc, const uint8_t *vsrc, uint8_t *dst,  // (3) 0.04238
/*2  */ 	unsigned int width, unsigned int height,                                                                           // (4) 0.02564
/*4  */ 	int lumStride, int chromStride, int dstStride)                                                                     // (5) 0.02409
/*6  */ {                                                                                                                   // (2) 0.05166
/*8  */ 	//FIXME interpolate chroma                                                                                         // (0) 0.6
/*10 */ 	RENAME(yuvPlanartouyvy)(ysrc, usrc, vsrc, dst, width, height, lumStride, chromStride, dstStride, 2);               // (1) 0.08969
/*12 */ }                                                                                                                   // (6) 0.002065
