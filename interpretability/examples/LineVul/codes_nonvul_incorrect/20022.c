// commit message FFmpeg@6ff0ad6bfd (target=0, prob=0.54908705, correct=False): MMX(2) optimized YUY2 input avoid duplicate checks for formats by changeing them (Y8->Y800, IYUV->I420)
/*0   */ static void RENAME(swScale)(SwsContext *c, uint8_t* srcParam[], int srcStrideParam[], int srcSliceY,  // (0) 0.07227
/*2   */              int srcSliceH, uint8_t* dstParam[], int dstStride[]){                                    // (1) 0.06641
/*6   */ 	/* load a few things into local vars to make the code more readable? and faster */                   // (2) 0.03906
/*8   */ 	const int srcW= c->srcW;                                                                             // (24) 0.02148
/*10  */ 	const int dstW= c->dstW;                                                                             // (23) 0.02344
/*12  */ 	const int dstH= c->dstH;                                                                             // (22) 0.02344
/*14  */ 	const int chrDstW= c->chrDstW;                                                                       // (16) 0.0332
/*16  */ 	const int lumXInc= c->lumXInc;                                                                       // (20) 0.02734
/*18  */ 	const int chrXInc= c->chrXInc;                                                                       // (19) 0.0293
/*20  */ 	const int dstFormat= c->dstFormat;                                                                   // (21) 0.02344
/*22  */ 	const int flags= c->flags;                                                                           // (25) 0.01758
/*24  */ 	const int canMMX2BeUsed= c->canMMX2BeUsed;                                                           // (9) 0.03711
/*26  */ 	int16_t *vLumFilterPos= c->vLumFilterPos;                                                            // (5) 0.03906
/*28  */ 	int16_t *vChrFilterPos= c->vChrFilterPos;                                                            // (7) 0.03906
/*30  */ 	int16_t *hLumFilterPos= c->hLumFilterPos;                                                            // (6) 0.03906
/*32  */ 	int16_t *hChrFilterPos= c->hChrFilterPos;                                                            // (8) 0.03906
/*34  */ 	int16_t *vLumFilter= c->vLumFilter;                                                                  // (10) 0.03516
/*36  */ 	int16_t *vChrFilter= c->vChrFilter;                                                                  // (11) 0.03516
/*38  */ 	int16_t *hLumFilter= c->hLumFilter;                                                                  // (12) 0.03516
/*40  */ 	int16_t *hChrFilter= c->hChrFilter;                                                                  // (13) 0.03516
/*42  */ 	int16_t *lumMmxFilter= c->lumMmxFilter;                                                              // (3) 0.03906
/*44  */ 	int16_t *chrMmxFilter= c->chrMmxFilter;                                                              // (4) 0.03906
/*46  */ 	const int vLumFilterSize= c->vLumFilterSize;                                                         // (17) 0.0332
/*48  */ 	const int vChrFilterSize= c->vChrFilterSize;                                                         // (18) 0.0332
/*50  */ 	const int hLumFilterSize= c->hLumFilterSize;                                                         // (15) 0.0332
/*52  */ 	const int hChrFilterSize= c->hChrFilterSize;                                                         // (14) 0.0332
/*54  */ 	int16_t **lumPixBuf= c->lumPixBuf;                                                                   // 0.0
/*56  */ 	int16_t **chrPixBuf= c->chrPixBuf;                                                                   // 0.0
/*58  */ 	const int vLumBufSize= c->vLumBufSize;                                                               // 0.0
/*60  */ 	const int vChrBufSize= c->vChrBufSize;                                                               // 0.0
/*62  */ 	uint8_t *funnyYCode= c->funnyYCode;                                                                  // 0.0
/*64  */ 	uint8_t *funnyUVCode= c->funnyUVCode;                                                                // 0.0
/*66  */ 	uint8_t *formatConvBuffer= c->formatConvBuffer;                                                      // 0.0
/*70  */ 	/* vars whch will change and which we need to storw back in the context */                           // 0.0
/*72  */ 	int dstY= c->dstY;                                                                                   // 0.0
/*74  */ 	int lumBufIndex= c->lumBufIndex;                                                                     // 0.0
/*76  */ 	int chrBufIndex= c->chrBufIndex;                                                                     // 0.0
/*78  */ 	int lastInLumBuf= c->lastInLumBuf;                                                                   // 0.0
/*80  */ 	int lastInChrBuf= c->lastInChrBuf;                                                                   // 0.0
/*82  */ 	int srcStride[3];                                                                                    // 0.0
/*84  */ 	uint8_t *src[3];                                                                                     // 0.0
/*86  */ 	uint8_t *dst[3];                                                                                     // 0.0
/*88  */ 	                                                                                                     // (26) 0.001953
/*90  */ 	if((c->srcFormat == IMGFMT_IYUV) || (c->srcFormat == IMGFMT_I420)){                                  // 0.0
/*92  */ 		src[0]= srcParam[0];                                                                                // 0.0
/*94  */ 		src[1]= srcParam[2];                                                                                // 0.0
/*96  */ 		src[2]= srcParam[1];                                                                                // 0.0
/*98  */ 		srcStride[0]= srcStrideParam[0];                                                                    // 0.0
/*100 */ 		srcStride[1]= srcStrideParam[2];                                                                    // 0.0
/*102 */ 		srcStride[2]= srcStrideParam[1];                                                                    // 0.0
/*104 */ 	}                                                                                                    // 0.0
/*106 */ 	else if(c->srcFormat==IMGFMT_YV12){                                                                  // 0.0
/*108 */ 		src[0]= srcParam[0];                                                                                // 0.0
/*110 */ 		src[1]= srcParam[1];                                                                                // 0.0
/*112 */ 		src[2]= srcParam[2];                                                                                // 0.0
/*114 */ 		srcStride[0]= srcStrideParam[0];                                                                    // 0.0
/*116 */ 		srcStride[1]= srcStrideParam[1];                                                                    // 0.0
/*118 */ 		srcStride[2]= srcStrideParam[2];                                                                    // 0.0
/*120 */ 	}                                                                                                    // 0.0
/*122 */ 	else if(isPacked(c->srcFormat)){                                                                     // 0.0
/*124 */ 		src[0]=                                                                                             // 0.0
/*126 */ 		src[1]=                                                                                             // 0.0
/*128 */ 		src[2]= srcParam[0];                                                                                // 0.0
/*130 */ 		srcStride[0]= srcStrideParam[0];                                                                    // 0.0
/*132 */ 		srcStride[1]=                                                                                       // 0.0
/*134 */ 		srcStride[2]= srcStrideParam[0]<<1;                                                                 // 0.0
/*136 */ 	}                                                                                                    // 0.0
/*138 */ 	else if(c->srcFormat==IMGFMT_Y8){                                                                    // 0.0
/*140 */ 		src[0]= srcParam[0];                                                                                // 0.0
/*142 */ 		src[1]=                                                                                             // 0.0
/*144 */ 		src[2]= NULL;                                                                                       // 0.0
/*146 */ 		srcStride[0]= srcStrideParam[0];                                                                    // 0.0
/*148 */ 		srcStride[1]=                                                                                       // 0.0
/*150 */ 		srcStride[2]= 0;                                                                                    // 0.0
/*152 */ 	}                                                                                                    // 0.0
/*156 */ 	if((c->dstFormat == IMGFMT_IYUV) || (c->dstFormat == IMGFMT_I420)){                                  // 0.0
/*158 */ 		dst[0]= dstParam[0];                                                                                // 0.0
/*160 */ 		dst[1]= dstParam[2];                                                                                // 0.0
/*162 */ 		dst[2]= dstParam[1];                                                                                // 0.0
/*164 */ 		                                                                                                    // 0.0
/*166 */ 	}else{                                                                                               // 0.0
/*168 */ 		dst[0]= dstParam[0];                                                                                // 0.0
/*170 */ 		dst[1]= dstParam[1];                                                                                // 0.0
/*172 */ 		dst[2]= dstParam[2];                                                                                // 0.0
/*174 */ 	}                                                                                                    // 0.0
/*176 */ 	                                                                                                     // 0.0
/*180 */ 	if(dstStride[0]%8 !=0 || dstStride[1]%8 !=0 || dstStride[2]%8 !=0)                                   // 0.0
/*182 */ 	{                                                                                                    // 0.0
/*184 */ 		static int firstTime=1; //FIXME move this into the context perhaps                                  // 0.0
/*186 */ 		if(flags & SWS_PRINT_INFO && firstTime)                                                             // 0.0
/*188 */ 		{                                                                                                   // 0.0
/*190 */ 			fprintf(stderr, "SwScaler: Warning: dstStride is not aligned!\n"                                   // 0.0
/*192 */ 					"SwScaler:          ->cannot do aligned memory acesses anymore\n");                              // 0.0
/*194 */ 			firstTime=0;                                                                                       // 0.0
/*196 */ 		}                                                                                                   // 0.0
/*198 */ 	}                                                                                                    // 0.0
/*202 */ 	/* Note the user might start scaling the picture in the middle so this will not get executed         // 0.0
/*204 */ 	   this is not really intended but works currently, so ppl might do it */                            // 0.0
/*206 */ 	if(srcSliceY ==0){                                                                                   // 0.0
/*208 */ 		lumBufIndex=0;                                                                                      // 0.0
/*210 */ 		chrBufIndex=0;                                                                                      // 0.0
/*212 */ 		dstY=0;	                                                                                            // 0.0
/*214 */ 		lastInLumBuf= -1;                                                                                   // 0.0
/*216 */ 		lastInChrBuf= -1;                                                                                   // 0.0
/*218 */ 	}                                                                                                    // 0.0
/*222 */ 	for(;dstY < dstH; dstY++){                                                                           // 0.0
/*224 */ 		unsigned char *dest =dst[0]+dstStride[0]*dstY;                                                      // 0.0
/*226 */ 		unsigned char *uDest=dst[1]+dstStride[1]*(dstY>>1);                                                 // 0.0
/*228 */ 		unsigned char *vDest=dst[2]+dstStride[2]*(dstY>>1);                                                 // 0.0
/*230 */ 		const int chrDstY= isHalfChrV(dstFormat) ? (dstY>>1) : dstY;                                        // 0.0
/*234 */ 		const int firstLumSrcY= vLumFilterPos[dstY]; //First line needed as input                           // 0.0
/*236 */ 		const int firstChrSrcY= vChrFilterPos[chrDstY]; //First line needed as input                        // 0.0
/*238 */ 		const int lastLumSrcY= firstLumSrcY + vLumFilterSize -1; // Last line needed as input               // 0.0
/*240 */ 		const int lastChrSrcY= firstChrSrcY + vChrFilterSize -1; // Last line needed as input               // 0.0
/*244 */ 		//handle holes (FAST_BILINEAR & weird filters)                                                      // 0.0
/*246 */ 		if(firstLumSrcY > lastInLumBuf) lastInLumBuf= firstLumSrcY-1;                                       // 0.0
/*248 */ 		if(firstChrSrcY > lastInChrBuf) lastInChrBuf= firstChrSrcY-1;                                       // 0.0
/*250 */ //printf("%d %d %d\n", firstChrSrcY, lastInChrBuf, vChrBufSize);                                      // 0.0
/*252 */ 		ASSERT(firstLumSrcY >= lastInLumBuf - vLumBufSize + 1)                                              // 0.0
/*254 */ 		ASSERT(firstChrSrcY >= lastInChrBuf - vChrBufSize + 1)                                              // 0.0
/*258 */ 		// Do we have enough lines in this slice to output the dstY line                                    // 0.0
/*260 */ 		if(lastLumSrcY < srcSliceY + srcSliceH && lastChrSrcY < ((srcSliceY + srcSliceH)>>1))               // 0.0
/*262 */ 		{                                                                                                   // 0.0
/*264 */ 			//Do horizontal scaling                                                                            // 0.0
/*266 */ 			while(lastInLumBuf < lastLumSrcY)                                                                  // 0.0
/*268 */ 			{                                                                                                  // 0.0
/*270 */ 				uint8_t *s= src[0]+(lastInLumBuf + 1 - srcSliceY)*srcStride[0];                                   // 0.0
/*272 */ 				lumBufIndex++;                                                                                    // 0.0
/*274 */ //				printf("%d %d %d %d\n", lumBufIndex, vLumBufSize, lastInLumBuf,  lastLumSrcY);                  // 0.0
/*276 */ 				ASSERT(lumBufIndex < 2*vLumBufSize)                                                               // 0.0
/*278 */ 				ASSERT(lastInLumBuf + 1 - srcSliceY < srcSliceH)                                                  // 0.0
/*280 */ 				ASSERT(lastInLumBuf + 1 - srcSliceY >= 0)                                                         // 0.0
/*282 */ //				printf("%d %d\n", lumBufIndex, vLumBufSize);                                                    // 0.0
/*284 */ 				RENAME(hyscale)(lumPixBuf[ lumBufIndex ], dstW, s, srcW, lumXInc,                                 // 0.0
/*286 */ 						flags, canMMX2BeUsed, hLumFilter, hLumFilterPos, hLumFilterSize,                                // 0.0
/*288 */ 						funnyYCode, c->srcFormat, formatConvBuffer);                                                    // 0.0
/*290 */ 				lastInLumBuf++;                                                                                   // 0.0
/*292 */ 			}                                                                                                  // 0.0
/*294 */ 			while(lastInChrBuf < lastChrSrcY)                                                                  // 0.0
/*296 */ 			{                                                                                                  // 0.0
/*298 */ 				uint8_t *src1= src[1]+(lastInChrBuf + 1 - (srcSliceY>>1))*srcStride[1];                           // 0.0
/*300 */ 				uint8_t *src2= src[2]+(lastInChrBuf + 1 - (srcSliceY>>1))*srcStride[2];                           // 0.0
/*302 */ 				chrBufIndex++;                                                                                    // 0.0
/*304 */ 				ASSERT(chrBufIndex < 2*vChrBufSize)                                                               // 0.0
/*306 */ 				ASSERT(lastInChrBuf + 1 - (srcSliceY>>1) < (srcSliceH>>1))                                        // 0.0
/*308 */ 				ASSERT(lastInChrBuf + 1 - (srcSliceY>>1) >= 0)                                                    // 0.0
/*310 */ 				//FIXME replace parameters through context struct (some at least)                                 // 0.0
/*312 */ 				RENAME(hcscale)(chrPixBuf[ chrBufIndex ], chrDstW, src1, src2, (srcW+1)>>1, chrXInc,              // 0.0
/*314 */ 						flags, canMMX2BeUsed, hChrFilter, hChrFilterPos, hChrFilterSize,                                // 0.0
/*316 */ 						funnyUVCode, c->srcFormat, formatConvBuffer);                                                   // 0.0
/*318 */ 				lastInChrBuf++;                                                                                   // 0.0
/*320 */ 			}                                                                                                  // 0.0
/*322 */ 			//wrap buf index around to stay inside the ring buffer                                             // 0.0
/*324 */ 			if(lumBufIndex >= vLumBufSize ) lumBufIndex-= vLumBufSize;                                         // 0.0
/*326 */ 			if(chrBufIndex >= vChrBufSize ) chrBufIndex-= vChrBufSize;                                         // 0.0
/*328 */ 		}                                                                                                   // 0.0
/*330 */ 		else // not enough lines left in this slice -> load the rest in the buffer                          // 0.0
/*332 */ 		{                                                                                                   // 0.0
/*334 */ /*		printf("%d %d Last:%d %d LastInBuf:%d %d Index:%d %d Y:%d FSize: %d %d BSize: %d %d\n",           // 0.0
/*336 */ 			firstChrSrcY,firstLumSrcY,lastChrSrcY,lastLumSrcY,                                                 // 0.0
/*338 */ 			lastInChrBuf,lastInLumBuf,chrBufIndex,lumBufIndex,dstY,vChrFilterSize,vLumFilterSize,              // 0.0
/*340 */ 			vChrBufSize, vLumBufSize);                                                                         // 0.0
/*342 */ */                                                                                                    // 0.0
/*344 */ 			//Do horizontal scaling                                                                            // 0.0
/*346 */ 			while(lastInLumBuf+1 < srcSliceY + srcSliceH)                                                      // 0.0
/*348 */ 			{                                                                                                  // 0.0
/*350 */ 				uint8_t *s= src[0]+(lastInLumBuf + 1 - srcSliceY)*srcStride[0];                                   // 0.0
/*352 */ 				lumBufIndex++;                                                                                    // 0.0
/*354 */ 				ASSERT(lumBufIndex < 2*vLumBufSize)                                                               // 0.0
/*356 */ 				ASSERT(lastInLumBuf + 1 - srcSliceY < srcSliceH)                                                  // 0.0
/*358 */ 				ASSERT(lastInLumBuf + 1 - srcSliceY >= 0)                                                         // 0.0
/*360 */ 				RENAME(hyscale)(lumPixBuf[ lumBufIndex ], dstW, s, srcW, lumXInc,                                 // 0.0
/*362 */ 						flags, canMMX2BeUsed, hLumFilter, hLumFilterPos, hLumFilterSize,                                // 0.0
/*364 */ 						funnyYCode, c->srcFormat, formatConvBuffer);                                                    // 0.0
/*366 */ 				lastInLumBuf++;                                                                                   // 0.0
/*368 */ 			}                                                                                                  // 0.0
/*370 */ 			while(lastInChrBuf+1 < ((srcSliceY + srcSliceH)>>1))                                               // 0.0
/*372 */ 			{                                                                                                  // 0.0
/*374 */ 				uint8_t *src1= src[1]+(lastInChrBuf + 1 - (srcSliceY>>1))*srcStride[1];                           // 0.0
/*376 */ 				uint8_t *src2= src[2]+(lastInChrBuf + 1 - (srcSliceY>>1))*srcStride[2];                           // 0.0
/*378 */ 				chrBufIndex++;                                                                                    // 0.0
/*380 */ 				ASSERT(chrBufIndex < 2*vChrBufSize)                                                               // 0.0
/*382 */ 				ASSERT(lastInChrBuf + 1 - (srcSliceY>>1) < (srcSliceH>>1))                                        // 0.0
/*384 */ 				ASSERT(lastInChrBuf + 1 - (srcSliceY>>1) >= 0)                                                    // 0.0
/*386 */ 				RENAME(hcscale)(chrPixBuf[ chrBufIndex ], chrDstW, src1, src2, (srcW+1)>>1, chrXInc,              // 0.0
/*388 */ 						flags, canMMX2BeUsed, hChrFilter, hChrFilterPos, hChrFilterSize,                                // 0.0
/*390 */ 						funnyUVCode, c->srcFormat, formatConvBuffer);                                                   // 0.0
/*392 */ 				lastInChrBuf++;                                                                                   // 0.0
/*394 */ 			}                                                                                                  // 0.0
/*396 */ 			//wrap buf index around to stay inside the ring buffer                                             // 0.0
/*398 */ 			if(lumBufIndex >= vLumBufSize ) lumBufIndex-= vLumBufSize;                                         // 0.0
/*400 */ 			if(chrBufIndex >= vChrBufSize ) chrBufIndex-= vChrBufSize;                                         // 0.0
/*402 */ 			break; //we cant output a dstY line so lets try with the next slice                                // 0.0
/*404 */ 		}                                                                                                   // 0.0
/*408 */ #ifdef HAVE_MMX                                                                                       // 0.0
/*410 */ 		b5Dither= dither8[dstY&1];                                                                          // 0.0
/*412 */ 		g6Dither= dither4[dstY&1];                                                                          // 0.0
/*414 */ 		g5Dither= dither8[dstY&1];                                                                          // 0.0
/*416 */ 		r5Dither= dither8[(dstY+1)&1];                                                                      // 0.0
/*418 */ #endif                                                                                                // 0.0
/*420 */ 	    if(dstY < dstH-2)                                                                                // 0.0
/*422 */ 	    {                                                                                                // 0.0
/*424 */ 		if(isPlanarYUV(dstFormat)) //YV12 like                                                              // 0.0
/*426 */ 		{                                                                                                   // 0.0
/*428 */ 			if(dstY&1) uDest=vDest= NULL; //FIXME split functions in lumi / chromi                             // 0.0
/*430 */ 			if(vLumFilterSize == 1 && vChrFilterSize == 1) // Unscaled YV12                                    // 0.0
/*432 */ 			{                                                                                                  // 0.0
/*434 */ 				int16_t *lumBuf = lumPixBuf[0];                                                                   // 0.0
/*436 */ 				int16_t *chrBuf= chrPixBuf[0];                                                                    // 0.0
/*438 */ 				RENAME(yuv2yuv1)(lumBuf, chrBuf, dest, uDest, vDest, dstW);                                       // 0.0
/*440 */ 			}                                                                                                  // 0.0
/*442 */ 			else //General YV12                                                                                // 0.0
/*444 */ 			{                                                                                                  // 0.0
/*446 */ 				int16_t **lumSrcPtr= lumPixBuf + lumBufIndex + firstLumSrcY - lastInLumBuf + vLumBufSize;         // 0.0
/*448 */ 				int16_t **chrSrcPtr= chrPixBuf + chrBufIndex + firstChrSrcY - lastInChrBuf + vChrBufSize;         // 0.0
/*450 */ 				RENAME(yuv2yuvX)(                                                                                 // 0.0
/*452 */ 					vLumFilter+dstY*vLumFilterSize     , lumSrcPtr, vLumFilterSize,                                  // 0.0
/*454 */ 					vChrFilter+(dstY>>1)*vChrFilterSize, chrSrcPtr, vChrFilterSize,                                  // 0.0
/*456 */ 					dest, uDest, vDest, dstW,                                                                        // 0.0
/*458 */ 					lumMmxFilter+dstY*vLumFilterSize*4, chrMmxFilter+(dstY>>1)*vChrFilterSize*4);                    // 0.0
/*460 */ 			}                                                                                                  // 0.0
/*462 */ 		}                                                                                                   // 0.0
/*464 */ 		else                                                                                                // 0.0
/*466 */ 		{                                                                                                   // 0.0
/*468 */ 			int16_t **lumSrcPtr= lumPixBuf + lumBufIndex + firstLumSrcY - lastInLumBuf + vLumBufSize;          // 0.0
/*470 */ 			int16_t **chrSrcPtr= chrPixBuf + chrBufIndex + firstChrSrcY - lastInChrBuf + vChrBufSize;          // 0.0
/*474 */ 			ASSERT(lumSrcPtr + vLumFilterSize - 1 < lumPixBuf + vLumBufSize*2);                                // 0.0
/*476 */ 			ASSERT(chrSrcPtr + vChrFilterSize - 1 < chrPixBuf + vChrBufSize*2);                                // 0.0
/*478 */ 			if(vLumFilterSize == 1 && vChrFilterSize == 2) //Unscaled RGB                                      // 0.0
/*480 */ 			{                                                                                                  // 0.0
/*482 */ 				int chrAlpha= vChrFilter[2*dstY+1];                                                               // 0.0
/*486 */ 				RENAME(yuv2rgb1)(*lumSrcPtr, *chrSrcPtr, *(chrSrcPtr+1),                                          // 0.0
/*488 */ 						 dest, dstW, chrAlpha, dstFormat, flags);                                                       // 0.0
/*490 */ 			}                                                                                                  // 0.0
/*492 */ 			else if(vLumFilterSize == 2 && vChrFilterSize == 2) //BiLinear Upscale RGB                         // 0.0
/*494 */ 			{                                                                                                  // 0.0
/*496 */ 				int lumAlpha= vLumFilter[2*dstY+1];                                                               // 0.0
/*498 */ 				int chrAlpha= vChrFilter[2*dstY+1];                                                               // 0.0
/*502 */ 				RENAME(yuv2rgb2)(*lumSrcPtr, *(lumSrcPtr+1), *chrSrcPtr, *(chrSrcPtr+1),                          // 0.0
/*504 */ 						 dest, dstW, lumAlpha, chrAlpha, dstFormat, flags);                                             // 0.0
/*506 */ 			}                                                                                                  // 0.0
/*508 */ 			else //General RGB                                                                                 // 0.0
/*510 */ 			{                                                                                                  // 0.0
/*512 */ 				RENAME(yuv2rgbX)(                                                                                 // 0.0
/*514 */ 					vLumFilter+dstY*vLumFilterSize, lumSrcPtr, vLumFilterSize,                                       // 0.0
/*516 */ 					vChrFilter+dstY*vChrFilterSize, chrSrcPtr, vChrFilterSize,                                       // 0.0
/*518 */ 					dest, dstW, dstFormat,                                                                           // 0.0
/*520 */ 					lumMmxFilter+dstY*vLumFilterSize*4, chrMmxFilter+dstY*vChrFilterSize*4);                         // 0.0
/*522 */ 			}                                                                                                  // 0.0
/*524 */ 		}                                                                                                   // 0.0
/*526 */             }                                                                                         // 0.0
/*528 */ 	    else // hmm looks like we cant use MMX here without overwriting this arrays tail                 // 0.0
/*530 */ 	    {                                                                                                // 0.0
/*532 */ 		int16_t **lumSrcPtr= lumPixBuf + lumBufIndex + firstLumSrcY - lastInLumBuf + vLumBufSize;           // 0.0
/*534 */ 		int16_t **chrSrcPtr= chrPixBuf + chrBufIndex + firstChrSrcY - lastInChrBuf + vChrBufSize;           // 0.0
/*536 */ 		if(isPlanarYUV(dstFormat)) //YV12                                                                   // 0.0
/*538 */ 		{                                                                                                   // 0.0
/*540 */ 			if(dstY&1) uDest=vDest= NULL; //FIXME split functions in lumi / chromi                             // 0.0
/*542 */ 			yuv2yuvXinC(                                                                                       // 0.0
/*544 */ 				vLumFilter+dstY*vLumFilterSize     , lumSrcPtr, vLumFilterSize,                                   // 0.0
/*546 */ 				vChrFilter+(dstY>>1)*vChrFilterSize, chrSrcPtr, vChrFilterSize,                                   // 0.0
/*548 */ 				dest, uDest, vDest, dstW);                                                                        // 0.0
/*550 */ 		}                                                                                                   // 0.0
/*552 */ 		else                                                                                                // 0.0
/*554 */ 		{                                                                                                   // 0.0
/*556 */ 			ASSERT(lumSrcPtr + vLumFilterSize - 1 < lumPixBuf + vLumBufSize*2);                                // 0.0
/*558 */ 			ASSERT(chrSrcPtr + vChrFilterSize - 1 < chrPixBuf + vChrBufSize*2);                                // 0.0
/*560 */ 			yuv2rgbXinC(                                                                                       // 0.0
/*562 */ 				vLumFilter+dstY*vLumFilterSize, lumSrcPtr, vLumFilterSize,                                        // 0.0
/*564 */ 				vChrFilter+dstY*vChrFilterSize, chrSrcPtr, vChrFilterSize,                                        // 0.0
/*566 */ 				dest, dstW, dstFormat);                                                                           // 0.0
/*568 */ 		}                                                                                                   // 0.0
/*570 */ 	    }                                                                                                // 0.0
/*572 */ 	}                                                                                                    // 0.0
/*576 */ #ifdef HAVE_MMX                                                                                       // 0.0
/*578 */ 	__asm __volatile(SFENCE:::"memory");                                                                 // 0.0
/*580 */ 	__asm __volatile(EMMS:::"memory");                                                                   // 0.0
/*582 */ #endif                                                                                                // 0.0
/*584 */ 	/* store changed local vars back in the context */                                                   // 0.0
/*586 */ 	c->dstY= dstY;                                                                                       // 0.0
/*588 */ 	c->lumBufIndex= lumBufIndex;                                                                         // 0.0
/*590 */ 	c->chrBufIndex= chrBufIndex;                                                                         // 0.0
/*592 */ 	c->lastInLumBuf= lastInLumBuf;                                                                       // 0.0
/*594 */ 	c->lastInChrBuf= lastInChrBuf;                                                                       // 0.0
/*596 */ }                                                                                                     // 0.0
