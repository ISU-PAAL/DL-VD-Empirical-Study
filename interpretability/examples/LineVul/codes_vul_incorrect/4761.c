// commit message FFmpeg@15d14ce47c (target=1, prob=0.1478831, correct=False): avcodec/utils: Fix overflow in get_bit_rates computations
/*0  */ static int64_t get_bit_rate(AVCodecContext *ctx)                                                          // (2) 0.06122
/*2  */ {                                                                                                         // (19) 0.003401
/*4  */     int64_t bit_rate;                                                                                     // (11) 0.03741
/*6  */     int bits_per_sample;                                                                                  // (12) 0.03401
/*10 */     switch (ctx->codec_type) {                                                                            // (6) 0.04422
/*12 */     case AVMEDIA_TYPE_VIDEO:                                                                              // (9) 0.04082
/*14 */     case AVMEDIA_TYPE_DATA:                                                                               // (10) 0.04082
/*16 */     case AVMEDIA_TYPE_SUBTITLE:                                                                           // (4) 0.05102
/*18 */     case AVMEDIA_TYPE_ATTACHMENT:                                                                         // (5) 0.04762
/*20 */         bit_rate = ctx->bit_rate;                                                                         // (3) 0.06122
/*22 */         break;                                                                                            // (13) 0.03061
/*24 */     case AVMEDIA_TYPE_AUDIO:                                                                              // (7) 0.04422
/*26 */         bits_per_sample = av_get_bits_per_sample(ctx->codec_id);                                          // (1) 0.102
/*28 */         bit_rate = bits_per_sample ? ctx->sample_rate * ctx->channels * bits_per_sample : ctx->bit_rate;  // (0) 0.1463
/*30 */         break;                                                                                            // (14) 0.03061
/*32 */     default:                                                                                              // (17) 0.01701
/*34 */         bit_rate = 0;                                                                                     // (8) 0.04422
/*36 */         break;                                                                                            // (15) 0.03061
/*38 */     }                                                                                                     // (18) 0.01361
/*40 */     return bit_rate;                                                                                      // (16) 0.02721
/*42 */ }                                                                                                         // (20) 0.003401
