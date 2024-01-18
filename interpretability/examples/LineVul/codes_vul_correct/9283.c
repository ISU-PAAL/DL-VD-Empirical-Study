// commit message FFmpeg@a2085a7e9d (target=1, prob=0.99909675, correct=True): Guard against output buffer overflows
/*0   */ static int dpcm_decode_frame(AVCodecContext *avctx,                                      // (8) 0.03717
/*1   */                              void *data, int *data_size,                                 // (1) 0.07421
/*2   */                              uint8_t *buf, int buf_size)                                 // (0) 0.07812
/*3   */ {                                                                                        // (27) 0.001953
/*4   */     DPCMContext *s = avctx->priv_data;                                                   // (11) 0.03321
/*5   */     int in, out = 0;                                                                     // (18) 0.01953
/*6   */     int predictor[2];                                                                    // (23) 0.01562
/*7   */     int channel_number = 0;                                                              // (17) 0.01953
/*8   */     short *output_samples = data;                                                        // (15) 0.02344
/*9   */     int shift[2];                                                                        // (22) 0.01563
/*10  */     unsigned char byte;                                                                  // (25) 0.01368
/*11  */     short diff;                                                                          // (26) 0.01172
/*12  */     if (!buf_size)                                                                       // (20) 0.01758
/*13  */         return 0;                                                                        // (19) 0.01953
/*14  */     switch(avctx->codec->id) {                                                           // (14) 0.02735
/*15  */     case CODEC_ID_ROQ_DPCM:                                                              // (12) 0.0332
/*16  */         if (s->channels == 1)                                                            // (13) 0.03125
/*17  */             predictor[0] = AV_RL16(&buf[6]);                                             // (5) 0.04882
/*18  */         else {                                                                           // (21) 0.01758
/*19  */             predictor[0] = buf[7] << 8;                                                  // (6) 0.04492
/*20  */             predictor[1] = buf[6] << 8;                                                  // (7) 0.04492
/*21  */         }                                                                                // (24) 0.01562
/*22  */         SE_16BIT(predictor[0]);                                                          // (10) 0.03515
/*23  */         SE_16BIT(predictor[1]);                                                          // (9) 0.03516
/*24  */         /* decode the samples */                                                         // (16) 0.02344
/*25  */         for (in = 8, out = 0; in < buf_size; in++, out++) {                              // (4) 0.05663
/*26  */             predictor[channel_number] += s->roq_square_array[buf[in]];                   // (3) 0.06249
/*27  */             predictor[channel_number] = av_clip_int16(predictor[channel_number]);        // (2) 0.06445
/*28  */             output_samples[out] = predictor[channel_number];                             // 0.0
/*29  */             /* toggle channel */                                                         // 0.0
/*30  */             channel_number ^= s->channels - 1;                                           // 0.0
/*31  */         }                                                                                // 0.0
/*32  */         break;                                                                           // 0.0
/*33  */     case CODEC_ID_INTERPLAY_DPCM:                                                        // 0.0
/*34  */         in = 6;  /* skip over the stream mask and stream length */                       // 0.0
/*35  */         predictor[0] = AV_RL16(&buf[in]);                                                // 0.0
/*36  */         in += 2;                                                                         // 0.0
/*37  */         SE_16BIT(predictor[0])                                                           // 0.0
/*38  */         output_samples[out++] = predictor[0];                                            // 0.0
/*39  */         if (s->channels == 2) {                                                          // 0.0
/*40  */             predictor[1] = AV_RL16(&buf[in]);                                            // 0.0
/*41  */             in += 2;                                                                     // 0.0
/*42  */             SE_16BIT(predictor[1])                                                       // 0.0
/*43  */             output_samples[out++] = predictor[1];                                        // 0.0
/*44  */         }                                                                                // 0.0
/*45  */         while (in < buf_size) {                                                          // 0.0
/*46  */             predictor[channel_number] += interplay_delta_table[buf[in++]];               // 0.0
/*47  */             predictor[channel_number] = av_clip_int16(predictor[channel_number]);        // 0.0
/*48  */             output_samples[out++] = predictor[channel_number];                           // 0.0
/*49  */             /* toggle channel */                                                         // 0.0
/*50  */             channel_number ^= s->channels - 1;                                           // 0.0
/*51  */         }                                                                                // 0.0
/*52  */         break;                                                                           // 0.0
/*53  */     case CODEC_ID_XAN_DPCM:                                                              // 0.0
/*54  */         in = 0;                                                                          // 0.0
/*55  */         shift[0] = shift[1] = 4;                                                         // 0.0
/*56  */         predictor[0] = AV_RL16(&buf[in]);                                                // 0.0
/*57  */         in += 2;                                                                         // 0.0
/*58  */         SE_16BIT(predictor[0]);                                                          // 0.0
/*59  */         if (s->channels == 2) {                                                          // 0.0
/*60  */             predictor[1] = AV_RL16(&buf[in]);                                            // 0.0
/*61  */             in += 2;                                                                     // 0.0
/*62  */             SE_16BIT(predictor[1]);                                                      // 0.0
/*63  */         }                                                                                // 0.0
/*64  */         while (in < buf_size) {                                                          // 0.0
/*65  */             byte = buf[in++];                                                            // 0.0
/*66  */             diff = (byte & 0xFC) << 8;                                                   // 0.0
/*67  */             if ((byte & 0x03) == 3)                                                      // 0.0
/*68  */                 shift[channel_number]++;                                                 // 0.0
/*69  */             else                                                                         // 0.0
/*70  */                 shift[channel_number] -= (2 * (byte & 3));                               // 0.0
/*71  */             /* saturate the shifter to a lower limit of 0 */                             // 0.0
/*72  */             if (shift[channel_number] < 0)                                               // 0.0
/*73  */                 shift[channel_number] = 0;                                               // 0.0
/*74  */             diff >>= shift[channel_number];                                              // 0.0
/*75  */             predictor[channel_number] += diff;                                           // 0.0
/*76  */             predictor[channel_number] = av_clip_int16(predictor[channel_number]);        // 0.0
/*77  */             output_samples[out++] = predictor[channel_number];                           // 0.0
/*78  */             /* toggle channel */                                                         // 0.0
/*79  */             channel_number ^= s->channels - 1;                                           // 0.0
/*80  */         }                                                                                // 0.0
/*81  */         break;                                                                           // 0.0
/*82  */     case CODEC_ID_SOL_DPCM:                                                              // 0.0
/*83  */         in = 0;                                                                          // 0.0
/*84  */         if (avctx->codec_tag != 3) {                                                     // 0.0
/*85  */             if(*data_size/4 < buf_size)                                                  // 0.0
/*86  */             while (in < buf_size) {                                                      // 0.0
/*87  */                 int n1, n2;                                                              // 0.0
/*88  */                 n1 = (buf[in] >> 4) & 0xF;                                               // 0.0
/*89  */                 n2 = buf[in++] & 0xF;                                                    // 0.0
/*90  */                 s->sample[0] += s->sol_table[n1];                                        // 0.0
/*91  */                  if (s->sample[0] < 0) s->sample[0] = 0;                                 // 0.0
/*92  */                 if (s->sample[0] > 255) s->sample[0] = 255;                              // 0.0
/*93  */                 output_samples[out++] = (s->sample[0] - 128) << 8;                       // 0.0
/*94  */                 s->sample[s->channels - 1] += s->sol_table[n2];                          // 0.0
/*95  */                 if (s->sample[s->channels - 1] < 0) s->sample[s->channels - 1] = 0;      // 0.0
/*96  */                 if (s->sample[s->channels - 1] > 255) s->sample[s->channels - 1] = 255;  // 0.0
/*97  */                 output_samples[out++] = (s->sample[s->channels - 1] - 128) << 8;         // 0.0
/*98  */             }                                                                            // 0.0
/*99  */         } else {                                                                         // 0.0
/*100 */             while (in < buf_size) {                                                      // 0.0
/*101 */                 int n;                                                                   // 0.0
/*102 */                 n = buf[in++];                                                           // 0.0
/*103 */                 if (n & 0x80) s->sample[channel_number] -= s->sol_table[n & 0x7F];       // 0.0
/*104 */                 else s->sample[channel_number] += s->sol_table[n & 0x7F];                // 0.0
/*105 */                 s->sample[channel_number] = av_clip_int16(s->sample[channel_number]);    // 0.0
/*106 */                 output_samples[out++] = s->sample[channel_number];                       // 0.0
/*107 */                 /* toggle channel */                                                     // 0.0
/*108 */                 channel_number ^= s->channels - 1;                                       // 0.0
/*109 */             }                                                                            // 0.0
/*110 */         }                                                                                // 0.0
/*111 */         break;                                                                           // 0.0
/*112 */     }                                                                                    // 0.0
/*113 */     *data_size = out * sizeof(short);                                                    // 0.0
/*114 */     return buf_size;                                                                     // 0.0
/*115 */ }                                                                                        // 0.0
