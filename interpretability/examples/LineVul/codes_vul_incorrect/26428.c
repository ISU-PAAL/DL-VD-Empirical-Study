// commit message FFmpeg@636ced8e1d (target=1, prob=0.16631103, correct=False): cmdutils: wrap exit explicitly
/*0  */ static void abort_codec_experimental(AVCodec *c, int encoder)                     // (7) 0.07194
/*2  */ {                                                                                 // (11) 0.003597
/*4  */     const char *codec_string = encoder ? "encoder" : "decoder";                   // (5) 0.08273
/*6  */     AVCodec *codec;                                                               // (9) 0.03597
/*8  */     av_log(NULL, AV_LOG_FATAL, "%s '%s' is experimental and might produce bad "   // (3) 0.1079
/*10 */             "results.\nAdd '-strict experimental' if you want to use it.\n",      // (2) 0.1187
/*12 */             codec_string, c->name);                                               // (8) 0.06835
/*14 */     codec = encoder ? avcodec_find_encoder(c->id) : avcodec_find_decoder(c->id);  // (1) 0.1259
/*16 */     if (!(codec->capabilities & CODEC_CAP_EXPERIMENTAL))                          // (4) 0.08633
/*18 */         av_log(NULL, AV_LOG_FATAL, "Or use the non experimental %s '%s'.\n",      // (0) 0.1295
/*20 */                codec_string, codec->name);                                        // (6) 0.07914
/*22 */     exit(1);                                                                      // (10) 0.02518
/*24 */ }                                                                                 // (12) 0.003597
