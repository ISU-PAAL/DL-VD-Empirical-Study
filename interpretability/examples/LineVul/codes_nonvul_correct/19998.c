// commit message FFmpeg@4b1f5e5090 (target=0, prob=0.3233372, correct=True): cosmetics: Write NULL pointer inequality checks more compactly
/*0  */ av_cold void avcodec_register(AVCodec *codec)  // (1) 0.1141
/*2  */ {                                              // (10) 0.006711
/*4  */     AVCodec **p;                               // (6) 0.0604
/*6  */     avcodec_init();                            // (7) 0.0604
/*8  */     p = &first_avcodec;                        // (5) 0.08054
/*10 */     while (*p != NULL)                         // (8) 0.0604
/*12 */         p = &(*p)->next;                       // (3) 0.1074
/*14 */     *p          = codec;                       // (2) 0.1141
/*16 */     codec->next = NULL;                        // (9) 0.0604
/*20 */     if (codec->init_static_data)               // (4) 0.09396
/*22 */         codec->init_static_data(codec);        // (0) 0.1208
/*24 */ }                                              // (11) 0.006711
