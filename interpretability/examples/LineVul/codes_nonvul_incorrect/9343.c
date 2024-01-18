// commit message FFmpeg@76db17dc7d (target=0, prob=0.62959796, correct=False): dpcm: calculate and check actual output data size prior to decoding.
/*0   */ static int dpcm_decode_frame(AVCodecContext *avctx,                      // (4) 0.01365
/*2   */                              void *data, int *data_size,                 // (24) 0.001276
/*4   */                              AVPacket *avpkt)                            // (28) 0.0007825
/*6   */ {                                                                        // (14) 0.002166
/*8   */     const uint8_t *buf = avpkt->data;                                    // (23) 0.00144
/*10  */     int buf_size = avpkt->size;                                          // (21) 0.001506
/*12  */     DPCMContext *s = avctx->priv_data;                                   // (10) 0.003761
/*14  */     int in, out = 0;                                                     // (22) 0.00146
/*16  */     int predictor[2];                                                    // (18) 0.002013
/*18  */     int ch = 0;                                                          // (29) 0.0004489
/*20  */     int stereo = s->channels - 1;                                        // (13) 0.002248
/*22  */     short *output_samples = data;                                        // (20) 0.001634
/*24  */     int shift[2];                                                        // (19) 0.001681
/*26  */     unsigned char byte;                                                  // (9) 0.003793
/*28  */     short diff;                                                          // (15) 0.002156
/*32  */     if (!buf_size)                                                       // (3) 0.0147
/*34  */         return 0;                                                        // (1) 0.05118
/*38  */     // almost every DPCM variant expands one byte of data into two       // (0) 0.6736
/*40  */     if(*data_size/2 < buf_size)                                          // (2) 0.03444
/*42  */         return -1;                                                       // (11) 0.003215
/*46  */     switch(avctx->codec->id) {                                           // (5) 0.005352
/*50  */     case CODEC_ID_ROQ_DPCM:                                              // (6) 0.00415
/*52  */         if (stereo) {                                                    // (12) 0.002658
/*54  */             predictor[0] = buf[7] << 8;                                  // (16) 0.002119
/*56  */             predictor[1] = buf[6] << 8;                                  // (8) 0.00384
/*58  */         } else {                                                         // (25) 0.0012
/*60  */             predictor[0] = AV_RL16(&buf[6]);                             // (17) 0.002115
/*62  */         }                                                                // (30) 0.0003637
/*64  */         SE_16BIT(predictor[0]);                                          // (27) 0.0009304
/*66  */         SE_16BIT(predictor[1]);                                          // (26) 0.001085
/*70  */         /* decode the samples */                                         // (7) 0.004099
/*72  */         for (in = 8, out = 0; in < buf_size; in++, out++) {              // 0.0
/*74  */             predictor[ch] += s->roq_square_array[buf[in]];               // 0.0
/*76  */             predictor[ch] = av_clip_int16(predictor[ch]);                // 0.0
/*78  */             output_samples[out] = predictor[ch];                         // 0.0
/*82  */             /* toggle channel */                                         // 0.0
/*84  */             ch ^= stereo;                                                // 0.0
/*86  */         }                                                                // 0.0
/*88  */         break;                                                           // 0.0
/*92  */     case CODEC_ID_INTERPLAY_DPCM:                                        // 0.0
/*94  */         in = 6;  /* skip over the stream mask and stream length */       // 0.0
/*96  */         predictor[0] = AV_RL16(&buf[in]);                                // 0.0
/*98  */         in += 2;                                                         // 0.0
/*100 */         SE_16BIT(predictor[0])                                           // 0.0
/*102 */         output_samples[out++] = predictor[0];                            // 0.0
/*104 */         if (stereo) {                                                    // 0.0
/*106 */             predictor[1] = AV_RL16(&buf[in]);                            // 0.0
/*108 */             in += 2;                                                     // 0.0
/*110 */             SE_16BIT(predictor[1])                                       // 0.0
/*112 */             output_samples[out++] = predictor[1];                        // 0.0
/*114 */         }                                                                // 0.0
/*118 */         while (in < buf_size) {                                          // 0.0
/*120 */             predictor[ch] += interplay_delta_table[buf[in++]];           // 0.0
/*122 */             predictor[ch] = av_clip_int16(predictor[ch]);                // 0.0
/*124 */             output_samples[out++] = predictor[ch];                       // 0.0
/*128 */             /* toggle channel */                                         // 0.0
/*130 */             ch ^= stereo;                                                // 0.0
/*132 */         }                                                                // 0.0
/*136 */         break;                                                           // 0.0
/*140 */     case CODEC_ID_XAN_DPCM:                                              // 0.0
/*142 */         in = 0;                                                          // 0.0
/*144 */         shift[0] = shift[1] = 4;                                         // 0.0
/*146 */         predictor[0] = AV_RL16(&buf[in]);                                // 0.0
/*148 */         in += 2;                                                         // 0.0
/*150 */         SE_16BIT(predictor[0]);                                          // 0.0
/*152 */         if (stereo) {                                                    // 0.0
/*154 */             predictor[1] = AV_RL16(&buf[in]);                            // 0.0
/*156 */             in += 2;                                                     // 0.0
/*158 */             SE_16BIT(predictor[1]);                                      // 0.0
/*160 */         }                                                                // 0.0
/*164 */         while (in < buf_size) {                                          // 0.0
/*166 */             byte = buf[in++];                                            // 0.0
/*168 */             diff = (byte & 0xFC) << 8;                                   // 0.0
/*170 */             if ((byte & 0x03) == 3)                                      // 0.0
/*172 */                 shift[ch]++;                                             // 0.0
/*174 */             else                                                         // 0.0
/*176 */                 shift[ch] -= (2 * (byte & 3));                           // 0.0
/*178 */             /* saturate the shifter to a lower limit of 0 */             // 0.0
/*180 */             if (shift[ch] < 0)                                           // 0.0
/*182 */                 shift[ch] = 0;                                           // 0.0
/*186 */             diff >>= shift[ch];                                          // 0.0
/*188 */             predictor[ch] += diff;                                       // 0.0
/*192 */             predictor[ch] = av_clip_int16(predictor[ch]);                // 0.0
/*194 */             output_samples[out++] = predictor[ch];                       // 0.0
/*198 */             /* toggle channel */                                         // 0.0
/*200 */             ch ^= stereo;                                                // 0.0
/*202 */         }                                                                // 0.0
/*204 */         break;                                                           // 0.0
/*206 */     case CODEC_ID_SOL_DPCM:                                              // 0.0
/*208 */         in = 0;                                                          // 0.0
/*210 */         if (avctx->codec_tag != 3) {                                     // 0.0
/*212 */             if(*data_size/4 < buf_size)                                  // 0.0
/*214 */                 return -1;                                               // 0.0
/*216 */             while (in < buf_size) {                                      // 0.0
/*218 */                 int n1, n2;                                              // 0.0
/*220 */                 n1 = (buf[in] >> 4) & 0xF;                               // 0.0
/*222 */                 n2 = buf[in++] & 0xF;                                    // 0.0
/*224 */                 s->sample[0] += s->sol_table[n1];                        // 0.0
/*226 */                 if (s->sample[0] < 0)   s->sample[0] = 0;                // 0.0
/*228 */                 if (s->sample[0] > 255) s->sample[0] = 255;              // 0.0
/*230 */                 output_samples[out++] = (s->sample[0] - 128) << 8;       // 0.0
/*232 */                 s->sample[stereo] += s->sol_table[n2];                   // 0.0
/*234 */                 if (s->sample[stereo] < 0)   s->sample[stereo] = 0;      // 0.0
/*236 */                 if (s->sample[stereo] > 255) s->sample[stereo] = 255;    // 0.0
/*238 */                 output_samples[out++] = (s->sample[stereo] - 128) << 8;  // 0.0
/*240 */             }                                                            // 0.0
/*242 */         } else {                                                         // 0.0
/*244 */             while (in < buf_size) {                                      // 0.0
/*246 */                 int n;                                                   // 0.0
/*248 */                 n = buf[in++];                                           // 0.0
/*250 */                 if (n & 0x80) s->sample[ch] -= s->sol_table[n & 0x7F];   // 0.0
/*252 */                 else s->sample[ch] += s->sol_table[n & 0x7F];            // 0.0
/*254 */                 s->sample[ch] = av_clip_int16(s->sample[ch]);            // 0.0
/*256 */                 output_samples[out++] = s->sample[ch];                   // 0.0
/*258 */                 /* toggle channel */                                     // 0.0
/*260 */                 ch ^= stereo;                                            // 0.0
/*262 */             }                                                            // 0.0
/*264 */         }                                                                // 0.0
/*266 */         break;                                                           // 0.0
/*268 */     }                                                                    // 0.0
/*272 */     *data_size = out * sizeof(short);                                    // 0.0
/*274 */     return buf_size;                                                     // 0.0
/*276 */ }                                                                        // 0.0
