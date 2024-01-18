// commit message FFmpeg@6c77805fc8 (target=0, prob=0.012370415, correct=True): get rid of the [4] limitation of codec tag lists
/*0  */ enum CodecID av_codec_get_id(const AVCodecTag *tags[4], unsigned int tag)  // (0) 0.197
/*2  */ {                                                                          // (7) 0.007576
/*4  */     int i;                                                                 // (5) 0.04545
/*6  */     for(i=0; i<4 && tags[i]; i++){                                         // (3) 0.1515
/*8  */         enum CodecID id= codec_get_id(tags[i], tag);                       // (1) 0.1818
/*10 */         if(id!=CODEC_ID_NONE) return id;                                   // (2) 0.1818
/*12 */     }                                                                      // (6) 0.0303
/*14 */     return CODEC_ID_NONE;                                                  // (4) 0.09848
/*16 */ }                                                                          // (8) 0.007576
