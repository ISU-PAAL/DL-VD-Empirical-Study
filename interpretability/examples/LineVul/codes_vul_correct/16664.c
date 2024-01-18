// commit message FFmpeg@608708009f (target=1, prob=0.9991054, correct=True): adpcm: Fix crash Fixes half of Ticket794 Bug found by: Oana Stratulat
/*0   */ static int adpcm_decode_frame(AVCodecContext *avctx, void *data,                                                        // (5) 0.04508
/*1   */                               int *got_frame_ptr, AVPacket *avpkt)                                                      // (0) 0.08787
/*2   */ {                                                                                                                       // (27) 0.001953
/*3   */     const uint8_t *buf = avpkt->data;                                                                                   // (10) 0.0332
/*4   */     int buf_size = avpkt->size;                                                                                         // (13) 0.02734
/*5   */     ADPCMDecodeContext *c = avctx->priv_data;                                                                           // (8) 0.03711
/*6   */     ADPCMChannelStatus *cs;                                                                                             // (17) 0.02153
/*7   */     int n, m, channel, i;                                                                                               // (15) 0.02354
/*8   */     short *samples;                                                                                                     // (23) 0.01562
/*9   */     const uint8_t *src;                                                                                                 // (18) 0.02148
/*10  */     int st; /* stereo */                                                                                                // (22) 0.0176
/*11  */     int count1, count2;                                                                                                 // (20) 0.01952
/*12  */     int nb_samples, coded_samples, ret;                                                                                 // (11) 0.03319
/*13  */     nb_samples = get_nb_samples(avctx, buf, buf_size, &coded_samples);                                                  // (1) 0.06052
/*14  */     if (nb_samples <= 0) {                                                                                              // (14) 0.02538
/*15  */         av_log(avctx, AV_LOG_ERROR, "invalid number of samples in packet\n");                                           // (2) 0.06052
/*16  */     }                                                                                                                   // (26) 0.007809
/*17  */     /* get output buffer */                                                                                             // (24) 0.01562
/*18  */     c->frame.nb_samples = nb_samples;                                                                                   // (9) 0.03514
/*19  */     if ((ret = avctx->get_buffer(avctx, &c->frame)) < 0) {                                                              // (4) 0.05076
/*20  */         av_log(avctx, AV_LOG_ERROR, "get_buffer() failed\n");                                                           // (3) 0.05661
/*21  */         return ret;                                                                                                     // (21) 0.01952
/*22  */     }                                                                                                                   // (25) 0.00781
/*23  */     samples = (short *)c->frame.data[0];                                                                                // (12) 0.03124
/*24  */     /* use coded_samples when applicable */                                                                             // (16) 0.02343
/*25  */     /* it is always <= nb_samples, so the output buffer will be large enough */                                         // (6) 0.0449
/*26  */     if (coded_samples) {                                                                                                // (19) 0.02147
/*27  */         if (coded_samples != nb_samples)                                                                                // (7) 0.03904
/*28  */             av_log(avctx, AV_LOG_WARNING, "mismatch in coded sample count\n");                                          // 0.0
/*29  */         c->frame.nb_samples = nb_samples = coded_samples;                                                               // 0.0
/*30  */     }                                                                                                                   // 0.0
/*31  */     src = buf;                                                                                                          // 0.0
/*32  */     st = avctx->channels == 2 ? 1 : 0;                                                                                  // 0.0
/*33  */     switch(avctx->codec->id) {                                                                                          // 0.0
/*34  */     case CODEC_ID_ADPCM_IMA_QT:                                                                                         // 0.0
/*35  */         /* In QuickTime, IMA is encoded by chunks of 34 bytes (=64 samples).                                            // 0.0
/*36  */            Channel data is interleaved per-chunk. */                                                                    // 0.0
/*37  */         for (channel = 0; channel < avctx->channels; channel++) {                                                       // 0.0
/*38  */             int16_t predictor;                                                                                          // 0.0
/*39  */             int step_index;                                                                                             // 0.0
/*40  */             cs = &(c->status[channel]);                                                                                 // 0.0
/*41  */             /* (pppppp) (piiiiiii) */                                                                                   // 0.0
/*42  */             /* Bits 15-7 are the _top_ 9 bits of the 16-bit initial predictor value */                                  // 0.0
/*43  */             predictor = AV_RB16(src);                                                                                   // 0.0
/*44  */             step_index = predictor & 0x7F;                                                                              // 0.0
/*45  */             predictor &= 0xFF80;                                                                                        // 0.0
/*46  */             src += 2;                                                                                                   // 0.0
/*47  */             if (cs->step_index == step_index) {                                                                         // 0.0
/*48  */                 int diff = (int)predictor - cs->predictor;                                                              // 0.0
/*49  */                 if (diff < 0)                                                                                           // 0.0
/*50  */                     diff = - diff;                                                                                      // 0.0
/*51  */                 if (diff > 0x7f)                                                                                        // 0.0
/*52  */                     goto update;                                                                                        // 0.0
/*53  */             } else {                                                                                                    // 0.0
/*54  */             update:                                                                                                     // 0.0
/*55  */                 cs->step_index = step_index;                                                                            // 0.0
/*56  */                 cs->predictor = predictor;                                                                              // 0.0
/*57  */             }                                                                                                           // 0.0
/*58  */             if (cs->step_index > 88){                                                                                   // 0.0
/*59  */                 av_log(avctx, AV_LOG_ERROR, "ERROR: step_index = %i\n", cs->step_index);                                // 0.0
/*60  */                 cs->step_index = 88;                                                                                    // 0.0
/*61  */             }                                                                                                           // 0.0
/*62  */             samples = (short *)c->frame.data[0] + channel;                                                              // 0.0
/*63  */             for (m = 0; m < 32; m++) {                                                                                  // 0.0
/*64  */                 *samples = adpcm_ima_qt_expand_nibble(cs, src[0] & 0x0F, 3);                                            // 0.0
/*65  */                 samples += avctx->channels;                                                                             // 0.0
/*66  */                 *samples = adpcm_ima_qt_expand_nibble(cs, src[0] >> 4  , 3);                                            // 0.0
/*67  */                 samples += avctx->channels;                                                                             // 0.0
/*68  */                 src ++;                                                                                                 // 0.0
/*69  */             }                                                                                                           // 0.0
/*70  */         }                                                                                                               // 0.0
/*71  */         break;                                                                                                          // 0.0
/*72  */     case CODEC_ID_ADPCM_IMA_WAV:                                                                                        // 0.0
/*73  */         if (avctx->block_align != 0 && buf_size > avctx->block_align)                                                   // 0.0
/*74  */             buf_size = avctx->block_align;                                                                              // 0.0
/*75  */         for(i=0; i<avctx->channels; i++){                                                                               // 0.0
/*76  */             cs = &(c->status[i]);                                                                                       // 0.0
/*77  */             cs->predictor = *samples++ = (int16_t)bytestream_get_le16(&src);                                            // 0.0
/*78  */             cs->step_index = *src++;                                                                                    // 0.0
/*79  */             if (cs->step_index > 88){                                                                                   // 0.0
/*80  */                 av_log(avctx, AV_LOG_ERROR, "ERROR: step_index = %i\n", cs->step_index);                                // 0.0
/*81  */                 cs->step_index = 88;                                                                                    // 0.0
/*82  */             }                                                                                                           // 0.0
/*83  */             if (*src++) av_log(avctx, AV_LOG_ERROR, "unused byte should be null but is %d!!\n", src[-1]); /* unused */  // 0.0
/*84  */         }                                                                                                               // 0.0
/*85  */         for (n = (nb_samples - 1) / 8; n > 0; n--) {                                                                    // 0.0
/*86  */             for (i = 0; i < avctx->channels; i++) {                                                                     // 0.0
/*87  */                 cs = &c->status[i];                                                                                     // 0.0
/*88  */                 for (m = 0; m < 4; m++) {                                                                               // 0.0
/*89  */                     uint8_t v = *src++;                                                                                 // 0.0
/*90  */                     *samples = adpcm_ima_expand_nibble(cs, v & 0x0F, 3);                                                // 0.0
/*91  */                     samples += avctx->channels;                                                                         // 0.0
/*92  */                     *samples = adpcm_ima_expand_nibble(cs, v >> 4  , 3);                                                // 0.0
/*93  */                     samples += avctx->channels;                                                                         // 0.0
/*94  */                 }                                                                                                       // 0.0
/*95  */                 samples -= 8 * avctx->channels - 1;                                                                     // 0.0
/*96  */             }                                                                                                           // 0.0
/*97  */             samples += 7 * avctx->channels;                                                                             // 0.0
/*98  */         }                                                                                                               // 0.0
/*99  */         break;                                                                                                          // 0.0
/*100 */     case CODEC_ID_ADPCM_4XM:                                                                                            // 0.0
/*101 */         for (i = 0; i < avctx->channels; i++)                                                                           // 0.0
/*102 */             c->status[i].predictor= (int16_t)bytestream_get_le16(&src);                                                 // 0.0
/*103 */         for (i = 0; i < avctx->channels; i++) {                                                                         // 0.0
/*104 */             c->status[i].step_index= (int16_t)bytestream_get_le16(&src);                                                // 0.0
/*105 */             c->status[i].step_index = av_clip(c->status[i].step_index, 0, 88);                                          // 0.0
/*106 */         }                                                                                                               // 0.0
/*107 */         for (i = 0; i < avctx->channels; i++) {                                                                         // 0.0
/*108 */             samples = (short *)c->frame.data[0] + i;                                                                    // 0.0
/*109 */             cs = &c->status[i];                                                                                         // 0.0
/*110 */             for (n = nb_samples >> 1; n > 0; n--, src++) {                                                              // 0.0
/*111 */                 uint8_t v = *src;                                                                                       // 0.0
/*112 */                 *samples = adpcm_ima_expand_nibble(cs, v & 0x0F, 4);                                                    // 0.0
/*113 */                 samples += avctx->channels;                                                                             // 0.0
/*114 */                 *samples = adpcm_ima_expand_nibble(cs, v >> 4  , 4);                                                    // 0.0
/*115 */                 samples += avctx->channels;                                                                             // 0.0
/*116 */             }                                                                                                           // 0.0
/*117 */         }                                                                                                               // 0.0
/*118 */         break;                                                                                                          // 0.0
/*119 */     case CODEC_ID_ADPCM_MS:                                                                                             // 0.0
/*120 */     {                                                                                                                   // 0.0
/*121 */         int block_predictor;                                                                                            // 0.0
/*122 */         if (avctx->block_align != 0 && buf_size > avctx->block_align)                                                   // 0.0
/*123 */             buf_size = avctx->block_align;                                                                              // 0.0
/*124 */         block_predictor = av_clip(*src++, 0, 6);                                                                        // 0.0
/*125 */         c->status[0].coeff1 = ff_adpcm_AdaptCoeff1[block_predictor];                                                    // 0.0
/*126 */         c->status[0].coeff2 = ff_adpcm_AdaptCoeff2[block_predictor];                                                    // 0.0
/*127 */         if (st) {                                                                                                       // 0.0
/*128 */             block_predictor = av_clip(*src++, 0, 6);                                                                    // 0.0
/*129 */             c->status[1].coeff1 = ff_adpcm_AdaptCoeff1[block_predictor];                                                // 0.0
/*130 */             c->status[1].coeff2 = ff_adpcm_AdaptCoeff2[block_predictor];                                                // 0.0
/*131 */         }                                                                                                               // 0.0
/*132 */         c->status[0].idelta = (int16_t)bytestream_get_le16(&src);                                                       // 0.0
/*133 */         if (st){                                                                                                        // 0.0
/*134 */             c->status[1].idelta = (int16_t)bytestream_get_le16(&src);                                                   // 0.0
/*135 */         }                                                                                                               // 0.0
/*136 */         c->status[0].sample1 = bytestream_get_le16(&src);                                                               // 0.0
/*137 */         if (st) c->status[1].sample1 = bytestream_get_le16(&src);                                                       // 0.0
/*138 */         c->status[0].sample2 = bytestream_get_le16(&src);                                                               // 0.0
/*139 */         if (st) c->status[1].sample2 = bytestream_get_le16(&src);                                                       // 0.0
/*140 */         *samples++ = c->status[0].sample2;                                                                              // 0.0
/*141 */         if (st) *samples++ = c->status[1].sample2;                                                                      // 0.0
/*142 */         *samples++ = c->status[0].sample1;                                                                              // 0.0
/*143 */         if (st) *samples++ = c->status[1].sample1;                                                                      // 0.0
/*144 */         for(n = (nb_samples - 2) >> (1 - st); n > 0; n--, src++) {                                                      // 0.0
/*145 */             *samples++ = adpcm_ms_expand_nibble(&c->status[0 ], src[0] >> 4  );                                         // 0.0
/*146 */             *samples++ = adpcm_ms_expand_nibble(&c->status[st], src[0] & 0x0F);                                         // 0.0
/*147 */         }                                                                                                               // 0.0
/*148 */         break;                                                                                                          // 0.0
/*149 */     }                                                                                                                   // 0.0
/*150 */     case CODEC_ID_ADPCM_IMA_DK4:                                                                                        // 0.0
/*151 */         if (avctx->block_align != 0 && buf_size > avctx->block_align)                                                   // 0.0
/*152 */             buf_size = avctx->block_align;                                                                              // 0.0
/*153 */         for (channel = 0; channel < avctx->channels; channel++) {                                                       // 0.0
/*154 */             cs = &c->status[channel];                                                                                   // 0.0
/*155 */             cs->predictor  = (int16_t)bytestream_get_le16(&src);                                                        // 0.0
/*156 */             cs->step_index = *src++;                                                                                    // 0.0
/*157 */             src++;                                                                                                      // 0.0
/*158 */             *samples++ = cs->predictor;                                                                                 // 0.0
/*159 */         }                                                                                                               // 0.0
/*160 */         for (n = nb_samples >> (1 - st); n > 0; n--, src++) {                                                           // 0.0
/*161 */             uint8_t v = *src;                                                                                           // 0.0
/*162 */             *samples++ = adpcm_ima_expand_nibble(&c->status[0 ], v >> 4  , 3);                                          // 0.0
/*163 */             *samples++ = adpcm_ima_expand_nibble(&c->status[st], v & 0x0F, 3);                                          // 0.0
/*164 */         }                                                                                                               // 0.0
/*165 */         break;                                                                                                          // 0.0
/*166 */     case CODEC_ID_ADPCM_IMA_DK3:                                                                                        // 0.0
/*167 */     {                                                                                                                   // 0.0
/*168 */         unsigned char last_byte = 0;                                                                                    // 0.0
/*169 */         unsigned char nibble;                                                                                           // 0.0
/*170 */         int decode_top_nibble_next = 0;                                                                                 // 0.0
/*171 */         int end_of_packet = 0;                                                                                          // 0.0
/*172 */         int diff_channel;                                                                                               // 0.0
/*173 */         if (avctx->block_align != 0 && buf_size > avctx->block_align)                                                   // 0.0
/*174 */             buf_size = avctx->block_align;                                                                              // 0.0
/*175 */         c->status[0].predictor  = (int16_t)AV_RL16(src + 10);                                                           // 0.0
/*176 */         c->status[1].predictor  = (int16_t)AV_RL16(src + 12);                                                           // 0.0
/*177 */         c->status[0].step_index = src[14];                                                                              // 0.0
/*178 */         c->status[1].step_index = src[15];                                                                              // 0.0
/*179 */         /* sign extend the predictors */                                                                                // 0.0
/*180 */         src += 16;                                                                                                      // 0.0
/*181 */         diff_channel = c->status[1].predictor;                                                                          // 0.0
/*182 */         /* the DK3_GET_NEXT_NIBBLE macro issues the break statement when                                                // 0.0
/*183 */          * the buffer is consumed */                                                                                    // 0.0
/*184 */         while (1) {                                                                                                     // 0.0
/*185 */             /* for this algorithm, c->status[0] is the sum channel and                                                  // 0.0
/*186 */              * c->status[1] is the diff channel */                                                                      // 0.0
/*187 */             /* process the first predictor of the sum channel */                                                        // 0.0
/*188 */             DK3_GET_NEXT_NIBBLE();                                                                                      // 0.0
/*189 */             adpcm_ima_expand_nibble(&c->status[0], nibble, 3);                                                          // 0.0
/*190 */             /* process the diff channel predictor */                                                                    // 0.0
/*191 */             DK3_GET_NEXT_NIBBLE();                                                                                      // 0.0
/*192 */             adpcm_ima_expand_nibble(&c->status[1], nibble, 3);                                                          // 0.0
/*193 */             /* process the first pair of stereo PCM samples */                                                          // 0.0
/*194 */             diff_channel = (diff_channel + c->status[1].predictor) / 2;                                                 // 0.0
/*195 */             *samples++ = c->status[0].predictor + c->status[1].predictor;                                               // 0.0
/*196 */             *samples++ = c->status[0].predictor - c->status[1].predictor;                                               // 0.0
/*197 */             /* process the second predictor of the sum channel */                                                       // 0.0
/*198 */             DK3_GET_NEXT_NIBBLE();                                                                                      // 0.0
/*199 */             adpcm_ima_expand_nibble(&c->status[0], nibble, 3);                                                          // 0.0
/*200 */             /* process the second pair of stereo PCM samples */                                                         // 0.0
/*201 */             diff_channel = (diff_channel + c->status[1].predictor) / 2;                                                 // 0.0
/*202 */             *samples++ = c->status[0].predictor + c->status[1].predictor;                                               // 0.0
/*203 */             *samples++ = c->status[0].predictor - c->status[1].predictor;                                               // 0.0
/*204 */         }                                                                                                               // 0.0
/*205 */         break;                                                                                                          // 0.0
/*206 */     }                                                                                                                   // 0.0
/*207 */     case CODEC_ID_ADPCM_IMA_ISS:                                                                                        // 0.0
/*208 */         for (channel = 0; channel < avctx->channels; channel++) {                                                       // 0.0
/*209 */             cs = &c->status[channel];                                                                                   // 0.0
/*210 */             cs->predictor  = (int16_t)bytestream_get_le16(&src);                                                        // 0.0
/*211 */             cs->step_index = *src++;                                                                                    // 0.0
/*212 */             src++;                                                                                                      // 0.0
/*213 */         }                                                                                                               // 0.0
/*214 */         for (n = nb_samples >> (1 - st); n > 0; n--, src++) {                                                           // 0.0
/*215 */             uint8_t v1, v2;                                                                                             // 0.0
/*216 */             uint8_t v = *src;                                                                                           // 0.0
/*217 */             /* nibbles are swapped for mono */                                                                          // 0.0
/*218 */             if (st) {                                                                                                   // 0.0
/*219 */                 v1 = v >> 4;                                                                                            // 0.0
/*220 */                 v2 = v & 0x0F;                                                                                          // 0.0
/*221 */             } else {                                                                                                    // 0.0
/*222 */                 v2 = v >> 4;                                                                                            // 0.0
/*223 */                 v1 = v & 0x0F;                                                                                          // 0.0
/*224 */             }                                                                                                           // 0.0
/*225 */             *samples++ = adpcm_ima_expand_nibble(&c->status[0 ], v1, 3);                                                // 0.0
/*226 */             *samples++ = adpcm_ima_expand_nibble(&c->status[st], v2, 3);                                                // 0.0
/*227 */         }                                                                                                               // 0.0
/*228 */         break;                                                                                                          // 0.0
/*229 */     case CODEC_ID_ADPCM_IMA_WS:                                                                                         // 0.0
/*230 */         while (src < buf + buf_size) {                                                                                  // 0.0
/*231 */             uint8_t v = *src++;                                                                                         // 0.0
/*232 */             *samples++ = adpcm_ima_expand_nibble(&c->status[0],  v >> 4  , 3);                                          // 0.0
/*233 */             *samples++ = adpcm_ima_expand_nibble(&c->status[st], v & 0x0F, 3);                                          // 0.0
/*234 */         }                                                                                                               // 0.0
/*235 */         break;                                                                                                          // 0.0
/*236 */     case CODEC_ID_ADPCM_XA:                                                                                             // 0.0
/*237 */         while (buf_size >= 128) {                                                                                       // 0.0
/*238 */             xa_decode(samples, src, &c->status[0], &c->status[1],                                                       // 0.0
/*239 */                 avctx->channels);                                                                                       // 0.0
/*240 */             src += 128;                                                                                                 // 0.0
/*241 */             samples += 28 * 8;                                                                                          // 0.0
/*242 */             buf_size -= 128;                                                                                            // 0.0
/*243 */         }                                                                                                               // 0.0
/*244 */         break;                                                                                                          // 0.0
/*245 */     case CODEC_ID_ADPCM_IMA_EA_EACS:                                                                                    // 0.0
/*246 */         src += 4; // skip sample count (already read)                                                                   // 0.0
/*247 */         for (i=0; i<=st; i++)                                                                                           // 0.0
/*248 */             c->status[i].step_index = bytestream_get_le32(&src);                                                        // 0.0
/*249 */         for (i=0; i<=st; i++)                                                                                           // 0.0
/*250 */             c->status[i].predictor  = bytestream_get_le32(&src);                                                        // 0.0
/*251 */         for (n = nb_samples >> (1 - st); n > 0; n--, src++) {                                                           // 0.0
/*252 */             *samples++ = adpcm_ima_expand_nibble(&c->status[0],  *src>>4,   3);                                         // 0.0
/*253 */             *samples++ = adpcm_ima_expand_nibble(&c->status[st], *src&0x0F, 3);                                         // 0.0
/*254 */         }                                                                                                               // 0.0
/*255 */         break;                                                                                                          // 0.0
/*256 */     case CODEC_ID_ADPCM_IMA_EA_SEAD:                                                                                    // 0.0
/*257 */         for (n = nb_samples >> (1 - st); n > 0; n--, src++) {                                                           // 0.0
/*258 */             *samples++ = adpcm_ima_expand_nibble(&c->status[0], src[0] >> 4, 6);                                        // 0.0
/*259 */             *samples++ = adpcm_ima_expand_nibble(&c->status[st],src[0]&0x0F, 6);                                        // 0.0
/*260 */         }                                                                                                               // 0.0
/*261 */         break;                                                                                                          // 0.0
/*262 */     case CODEC_ID_ADPCM_EA:                                                                                             // 0.0
/*263 */     {                                                                                                                   // 0.0
/*264 */         int32_t previous_left_sample, previous_right_sample;                                                            // 0.0
/*265 */         int32_t current_left_sample, current_right_sample;                                                              // 0.0
/*266 */         int32_t next_left_sample, next_right_sample;                                                                    // 0.0
/*267 */         int32_t coeff1l, coeff2l, coeff1r, coeff2r;                                                                     // 0.0
/*268 */         uint8_t shift_left, shift_right;                                                                                // 0.0
/*269 */         /* Each EA ADPCM frame has a 12-byte header followed by 30-byte pieces,                                         // 0.0
/*270 */            each coding 28 stereo samples. */                                                                            // 0.0
/*271 */         src += 4; // skip sample count (already read)                                                                   // 0.0
/*272 */         current_left_sample   = (int16_t)bytestream_get_le16(&src);                                                     // 0.0
/*273 */         previous_left_sample  = (int16_t)bytestream_get_le16(&src);                                                     // 0.0
/*274 */         current_right_sample  = (int16_t)bytestream_get_le16(&src);                                                     // 0.0
/*275 */         previous_right_sample = (int16_t)bytestream_get_le16(&src);                                                     // 0.0
/*276 */         for (count1 = 0; count1 < nb_samples / 28; count1++) {                                                          // 0.0
/*277 */             coeff1l = ea_adpcm_table[ *src >> 4       ];                                                                // 0.0
/*278 */             coeff2l = ea_adpcm_table[(*src >> 4  ) + 4];                                                                // 0.0
/*279 */             coeff1r = ea_adpcm_table[*src & 0x0F];                                                                      // 0.0
/*280 */             coeff2r = ea_adpcm_table[(*src & 0x0F) + 4];                                                                // 0.0
/*281 */             src++;                                                                                                      // 0.0
/*282 */             shift_left  = 20 - (*src >> 4);                                                                             // 0.0
/*283 */             shift_right = 20 - (*src & 0x0F);                                                                           // 0.0
/*284 */             src++;                                                                                                      // 0.0
/*285 */             for (count2 = 0; count2 < 28; count2++) {                                                                   // 0.0
/*286 */                 next_left_sample  = sign_extend(*src >> 4, 4) << shift_left;                                            // 0.0
/*287 */                 next_right_sample = sign_extend(*src,      4) << shift_right;                                           // 0.0
/*288 */                 src++;                                                                                                  // 0.0
/*289 */                 next_left_sample = (next_left_sample +                                                                  // 0.0
/*290 */                     (current_left_sample * coeff1l) +                                                                   // 0.0
/*291 */                     (previous_left_sample * coeff2l) + 0x80) >> 8;                                                      // 0.0
/*292 */                 next_right_sample = (next_right_sample +                                                                // 0.0
/*293 */                     (current_right_sample * coeff1r) +                                                                  // 0.0
/*294 */                     (previous_right_sample * coeff2r) + 0x80) >> 8;                                                     // 0.0
/*295 */                 previous_left_sample = current_left_sample;                                                             // 0.0
/*296 */                 current_left_sample = av_clip_int16(next_left_sample);                                                  // 0.0
/*297 */                 previous_right_sample = current_right_sample;                                                           // 0.0
/*298 */                 current_right_sample = av_clip_int16(next_right_sample);                                                // 0.0
/*299 */                 *samples++ = (unsigned short)current_left_sample;                                                       // 0.0
/*300 */                 *samples++ = (unsigned short)current_right_sample;                                                      // 0.0
/*301 */             }                                                                                                           // 0.0
/*302 */         }                                                                                                               // 0.0
/*303 */         if (src - buf == buf_size - 2)                                                                                  // 0.0
/*304 */             src += 2; // Skip terminating 0x0000                                                                        // 0.0
/*305 */         break;                                                                                                          // 0.0
/*306 */     }                                                                                                                   // 0.0
/*307 */     case CODEC_ID_ADPCM_EA_MAXIS_XA:                                                                                    // 0.0
/*308 */     {                                                                                                                   // 0.0
/*309 */         int coeff[2][2], shift[2];                                                                                      // 0.0
/*310 */         for(channel = 0; channel < avctx->channels; channel++) {                                                        // 0.0
/*311 */             for (i=0; i<2; i++)                                                                                         // 0.0
/*312 */                 coeff[channel][i] = ea_adpcm_table[(*src >> 4) + 4*i];                                                  // 0.0
/*313 */             shift[channel] = 20 - (*src & 0x0F);                                                                        // 0.0
/*314 */             src++;                                                                                                      // 0.0
/*315 */         }                                                                                                               // 0.0
/*316 */         for (count1 = 0; count1 < nb_samples / 2; count1++) {                                                           // 0.0
/*317 */             for(i = 4; i >= 0; i-=4) { /* Pairwise samples LL RR (st) or LL LL (mono) */                                // 0.0
/*318 */                 for(channel = 0; channel < avctx->channels; channel++) {                                                // 0.0
/*319 */                     int32_t sample = sign_extend(src[channel] >> i, 4) << shift[channel];                               // 0.0
/*320 */                     sample = (sample +                                                                                  // 0.0
/*321 */                              c->status[channel].sample1 * coeff[channel][0] +                                           // 0.0
/*322 */                              c->status[channel].sample2 * coeff[channel][1] + 0x80) >> 8;                               // 0.0
/*323 */                     c->status[channel].sample2 = c->status[channel].sample1;                                            // 0.0
/*324 */                     c->status[channel].sample1 = av_clip_int16(sample);                                                 // 0.0
/*325 */                     *samples++ = c->status[channel].sample1;                                                            // 0.0
/*326 */                 }                                                                                                       // 0.0
/*327 */             }                                                                                                           // 0.0
/*328 */             src+=avctx->channels;                                                                                       // 0.0
/*329 */         }                                                                                                               // 0.0
/*330 */         /* consume whole packet */                                                                                      // 0.0
/*331 */         src = buf + buf_size;                                                                                           // 0.0
/*332 */         break;                                                                                                          // 0.0
/*333 */     }                                                                                                                   // 0.0
/*334 */     case CODEC_ID_ADPCM_EA_R1:                                                                                          // 0.0
/*335 */     case CODEC_ID_ADPCM_EA_R2:                                                                                          // 0.0
/*336 */     case CODEC_ID_ADPCM_EA_R3: {                                                                                        // 0.0
/*337 */         /* channel numbering                                                                                            // 0.0
/*338 */            2chan: 0=fl, 1=fr                                                                                            // 0.0
/*339 */            4chan: 0=fl, 1=rl, 2=fr, 3=rr                                                                                // 0.0
/*340 */            6chan: 0=fl, 1=c,  2=fr, 3=rl,  4=rr, 5=sub */                                                               // 0.0
/*341 */         const int big_endian = avctx->codec->id == CODEC_ID_ADPCM_EA_R3;                                                // 0.0
/*342 */         int32_t previous_sample, current_sample, next_sample;                                                           // 0.0
/*343 */         int32_t coeff1, coeff2;                                                                                         // 0.0
/*344 */         uint8_t shift;                                                                                                  // 0.0
/*345 */         unsigned int channel;                                                                                           // 0.0
/*346 */         uint16_t *samplesC;                                                                                             // 0.0
/*347 */         const uint8_t *srcC;                                                                                            // 0.0
/*348 */         const uint8_t *src_end = buf + buf_size;                                                                        // 0.0
/*349 */         int count = 0;                                                                                                  // 0.0
/*350 */         src += 4; // skip sample count (already read)                                                                   // 0.0
/*351 */         for (channel=0; channel<avctx->channels; channel++) {                                                           // 0.0
/*352 */             int32_t offset = (big_endian ? bytestream_get_be32(&src)                                                    // 0.0
/*353 */                                          : bytestream_get_le32(&src))                                                   // 0.0
/*354 */                            + (avctx->channels-channel-1) * 4;                                                           // 0.0
/*355 */             if ((offset < 0) || (offset >= src_end - src - 4)) break;                                                   // 0.0
/*356 */             srcC  = src + offset;                                                                                       // 0.0
/*357 */             samplesC = samples + channel;                                                                               // 0.0
/*358 */             if (avctx->codec->id == CODEC_ID_ADPCM_EA_R1) {                                                             // 0.0
/*359 */                 current_sample  = (int16_t)bytestream_get_le16(&srcC);                                                  // 0.0
/*360 */                 previous_sample = (int16_t)bytestream_get_le16(&srcC);                                                  // 0.0
/*361 */             } else {                                                                                                    // 0.0
/*362 */                 current_sample  = c->status[channel].predictor;                                                         // 0.0
/*363 */                 previous_sample = c->status[channel].prev_sample;                                                       // 0.0
/*364 */             }                                                                                                           // 0.0
/*365 */             for (count1 = 0; count1 < nb_samples / 28; count1++) {                                                      // 0.0
/*366 */                 if (*srcC == 0xEE) {  /* only seen in R2 and R3 */                                                      // 0.0
/*367 */                     srcC++;                                                                                             // 0.0
/*368 */                     if (srcC > src_end - 30*2) break;                                                                   // 0.0
/*369 */                     current_sample  = (int16_t)bytestream_get_be16(&srcC);                                              // 0.0
/*370 */                     previous_sample = (int16_t)bytestream_get_be16(&srcC);                                              // 0.0
/*371 */                     for (count2=0; count2<28; count2++) {                                                               // 0.0
/*372 */                         *samplesC = (int16_t)bytestream_get_be16(&srcC);                                                // 0.0
/*373 */                         samplesC += avctx->channels;                                                                    // 0.0
/*374 */                     }                                                                                                   // 0.0
/*375 */                 } else {                                                                                                // 0.0
/*376 */                     coeff1 = ea_adpcm_table[ *srcC>>4     ];                                                            // 0.0
/*377 */                     coeff2 = ea_adpcm_table[(*srcC>>4) + 4];                                                            // 0.0
/*378 */                     shift = 20 - (*srcC++ & 0x0F);                                                                      // 0.0
/*379 */                     if (srcC > src_end - 14) break;                                                                     // 0.0
/*380 */                     for (count2=0; count2<28; count2++) {                                                               // 0.0
/*381 */                         if (count2 & 1)                                                                                 // 0.0
/*382 */                             next_sample = sign_extend(*srcC++,    4) << shift;                                          // 0.0
/*383 */                         else                                                                                            // 0.0
/*384 */                             next_sample = sign_extend(*srcC >> 4, 4) << shift;                                          // 0.0
/*385 */                         next_sample += (current_sample  * coeff1) +                                                     // 0.0
/*386 */                                        (previous_sample * coeff2);                                                      // 0.0
/*387 */                         next_sample = av_clip_int16(next_sample >> 8);                                                  // 0.0
/*388 */                         previous_sample = current_sample;                                                               // 0.0
/*389 */                         current_sample  = next_sample;                                                                  // 0.0
/*390 */                         *samplesC = current_sample;                                                                     // 0.0
/*391 */                         samplesC += avctx->channels;                                                                    // 0.0
/*392 */                     }                                                                                                   // 0.0
/*393 */                 }                                                                                                       // 0.0
/*394 */             }                                                                                                           // 0.0
/*395 */             if (!count) {                                                                                               // 0.0
/*396 */                 count = count1;                                                                                         // 0.0
/*397 */             } else if (count != count1) {                                                                               // 0.0
/*398 */                 av_log(avctx, AV_LOG_WARNING, "per-channel sample count mismatch\n");                                   // 0.0
/*399 */                 count = FFMAX(count, count1);                                                                           // 0.0
/*400 */             }                                                                                                           // 0.0
/*401 */             if (avctx->codec->id != CODEC_ID_ADPCM_EA_R1) {                                                             // 0.0
/*402 */                 c->status[channel].predictor   = current_sample;                                                        // 0.0
/*403 */                 c->status[channel].prev_sample = previous_sample;                                                       // 0.0
/*404 */             }                                                                                                           // 0.0
/*405 */         }                                                                                                               // 0.0
/*406 */         c->frame.nb_samples = count * 28;                                                                               // 0.0
/*407 */         src = src_end;                                                                                                  // 0.0
/*408 */         break;                                                                                                          // 0.0
/*409 */     }                                                                                                                   // 0.0
/*410 */     case CODEC_ID_ADPCM_EA_XAS:                                                                                         // 0.0
/*411 */         for (channel=0; channel<avctx->channels; channel++) {                                                           // 0.0
/*412 */             int coeff[2][4], shift[4];                                                                                  // 0.0
/*413 */             short *s2, *s = &samples[channel];                                                                          // 0.0
/*414 */             for (n=0; n<4; n++, s+=32*avctx->channels) {                                                                // 0.0
/*415 */                 for (i=0; i<2; i++)                                                                                     // 0.0
/*416 */                     coeff[i][n] = ea_adpcm_table[(src[0]&0x0F)+4*i];                                                    // 0.0
/*417 */                 shift[n] = 20 - (src[2] & 0x0F);                                                                        // 0.0
/*418 */                 for (s2=s, i=0; i<2; i++, src+=2, s2+=avctx->channels)                                                  // 0.0
/*419 */                     s2[0] = (src[0]&0xF0) + (src[1]<<8);                                                                // 0.0
/*420 */             }                                                                                                           // 0.0
/*421 */             for (m=2; m<32; m+=2) {                                                                                     // 0.0
/*422 */                 s = &samples[m*avctx->channels + channel];                                                              // 0.0
/*423 */                 for (n=0; n<4; n++, src++, s+=32*avctx->channels) {                                                     // 0.0
/*424 */                     for (s2=s, i=0; i<8; i+=4, s2+=avctx->channels) {                                                   // 0.0
/*425 */                         int level = sign_extend(*src >> (4 - i), 4) << shift[n];                                        // 0.0
/*426 */                         int pred  = s2[-1*avctx->channels] * coeff[0][n]                                                // 0.0
/*427 */                                   + s2[-2*avctx->channels] * coeff[1][n];                                               // 0.0
/*428 */                         s2[0] = av_clip_int16((level + pred + 0x80) >> 8);                                              // 0.0
/*429 */                     }                                                                                                   // 0.0
/*430 */                 }                                                                                                       // 0.0
/*431 */             }                                                                                                           // 0.0
/*432 */         }                                                                                                               // 0.0
/*433 */         break;                                                                                                          // 0.0
/*434 */     case CODEC_ID_ADPCM_IMA_AMV:                                                                                        // 0.0
/*435 */     case CODEC_ID_ADPCM_IMA_SMJPEG:                                                                                     // 0.0
/*436 */         c->status[0].predictor = (int16_t)bytestream_get_le16(&src);                                                    // 0.0
/*437 */         c->status[0].step_index = bytestream_get_le16(&src);                                                            // 0.0
/*438 */         if (avctx->codec->id == CODEC_ID_ADPCM_IMA_AMV)                                                                 // 0.0
/*439 */             src+=4;                                                                                                     // 0.0
/*440 */         for (n = nb_samples >> (1 - st); n > 0; n--, src++) {                                                           // 0.0
/*441 */             char hi, lo;                                                                                                // 0.0
/*442 */             lo = *src & 0x0F;                                                                                           // 0.0
/*443 */             hi = *src >> 4;                                                                                             // 0.0
/*444 */             if (avctx->codec->id == CODEC_ID_ADPCM_IMA_AMV)                                                             // 0.0
/*445 */                 FFSWAP(char, hi, lo);                                                                                   // 0.0
/*446 */             *samples++ = adpcm_ima_expand_nibble(&c->status[0],                                                         // 0.0
/*447 */                 lo, 3);                                                                                                 // 0.0
/*448 */             *samples++ = adpcm_ima_expand_nibble(&c->status[0],                                                         // 0.0
/*449 */                 hi, 3);                                                                                                 // 0.0
/*450 */         }                                                                                                               // 0.0
/*451 */         break;                                                                                                          // 0.0
/*452 */     case CODEC_ID_ADPCM_CT:                                                                                             // 0.0
/*453 */         for (n = nb_samples >> (1 - st); n > 0; n--, src++) {                                                           // 0.0
/*454 */             uint8_t v = *src;                                                                                           // 0.0
/*455 */             *samples++ = adpcm_ct_expand_nibble(&c->status[0 ], v >> 4  );                                              // 0.0
/*456 */             *samples++ = adpcm_ct_expand_nibble(&c->status[st], v & 0x0F);                                              // 0.0
/*457 */         }                                                                                                               // 0.0
/*458 */         break;                                                                                                          // 0.0
/*459 */     case CODEC_ID_ADPCM_SBPRO_4:                                                                                        // 0.0
/*460 */     case CODEC_ID_ADPCM_SBPRO_3:                                                                                        // 0.0
/*461 */     case CODEC_ID_ADPCM_SBPRO_2:                                                                                        // 0.0
/*462 */         if (!c->status[0].step_index) {                                                                                 // 0.0
/*463 */             /* the first byte is a raw sample */                                                                        // 0.0
/*464 */             *samples++ = 128 * (*src++ - 0x80);                                                                         // 0.0
/*465 */             if (st)                                                                                                     // 0.0
/*466 */               *samples++ = 128 * (*src++ - 0x80);                                                                       // 0.0
/*467 */             c->status[0].step_index = 1;                                                                                // 0.0
/*468 */             nb_samples--;                                                                                               // 0.0
/*469 */         }                                                                                                               // 0.0
/*470 */         if (avctx->codec->id == CODEC_ID_ADPCM_SBPRO_4) {                                                               // 0.0
/*471 */             for (n = nb_samples >> (1 - st); n > 0; n--, src++) {                                                       // 0.0
/*472 */                 *samples++ = adpcm_sbpro_expand_nibble(&c->status[0],                                                   // 0.0
/*473 */                     src[0] >> 4, 4, 0);                                                                                 // 0.0
/*474 */                 *samples++ = adpcm_sbpro_expand_nibble(&c->status[st],                                                  // 0.0
/*475 */                     src[0] & 0x0F, 4, 0);                                                                               // 0.0
/*476 */             }                                                                                                           // 0.0
/*477 */         } else if (avctx->codec->id == CODEC_ID_ADPCM_SBPRO_3) {                                                        // 0.0
/*478 */             for (n = nb_samples / 3; n > 0; n--, src++) {                                                               // 0.0
/*479 */                 *samples++ = adpcm_sbpro_expand_nibble(&c->status[0],                                                   // 0.0
/*480 */                      src[0] >> 5        , 3, 0);                                                                        // 0.0
/*481 */                 *samples++ = adpcm_sbpro_expand_nibble(&c->status[0],                                                   // 0.0
/*482 */                     (src[0] >> 2) & 0x07, 3, 0);                                                                        // 0.0
/*483 */                 *samples++ = adpcm_sbpro_expand_nibble(&c->status[0],                                                   // 0.0
/*484 */                     src[0] & 0x03, 2, 0);                                                                               // 0.0
/*485 */             }                                                                                                           // 0.0
/*486 */         } else {                                                                                                        // 0.0
/*487 */             for (n = nb_samples >> (2 - st); n > 0; n--, src++) {                                                       // 0.0
/*488 */                 *samples++ = adpcm_sbpro_expand_nibble(&c->status[0],                                                   // 0.0
/*489 */                      src[0] >> 6        , 2, 2);                                                                        // 0.0
/*490 */                 *samples++ = adpcm_sbpro_expand_nibble(&c->status[st],                                                  // 0.0
/*491 */                     (src[0] >> 4) & 0x03, 2, 2);                                                                        // 0.0
/*492 */                 *samples++ = adpcm_sbpro_expand_nibble(&c->status[0],                                                   // 0.0
/*493 */                     (src[0] >> 2) & 0x03, 2, 2);                                                                        // 0.0
/*494 */                 *samples++ = adpcm_sbpro_expand_nibble(&c->status[st],                                                  // 0.0
/*495 */                     src[0] & 0x03, 2, 2);                                                                               // 0.0
/*496 */             }                                                                                                           // 0.0
/*497 */         }                                                                                                               // 0.0
/*498 */         break;                                                                                                          // 0.0
/*499 */     case CODEC_ID_ADPCM_SWF:                                                                                            // 0.0
/*500 */     {                                                                                                                   // 0.0
/*501 */         GetBitContext gb;                                                                                               // 0.0
/*502 */         const int *table;                                                                                               // 0.0
/*503 */         int k0, signmask, nb_bits, count;                                                                               // 0.0
/*504 */         int size = buf_size*8;                                                                                          // 0.0
/*505 */         init_get_bits(&gb, buf, size);                                                                                  // 0.0
/*506 */         //read bits & initial values                                                                                    // 0.0
/*507 */         nb_bits = get_bits(&gb, 2)+2;                                                                                   // 0.0
/*508 */         //av_log(NULL,AV_LOG_INFO,"nb_bits: %d\n", nb_bits);                                                            // 0.0
/*509 */         table = swf_index_tables[nb_bits-2];                                                                            // 0.0
/*510 */         k0 = 1 << (nb_bits-2);                                                                                          // 0.0
/*511 */         signmask = 1 << (nb_bits-1);                                                                                    // 0.0
/*512 */         while (get_bits_count(&gb) <= size - 22*avctx->channels) {                                                      // 0.0
/*513 */             for (i = 0; i < avctx->channels; i++) {                                                                     // 0.0
/*514 */                 *samples++ = c->status[i].predictor = get_sbits(&gb, 16);                                               // 0.0
/*515 */                 c->status[i].step_index = get_bits(&gb, 6);                                                             // 0.0
/*516 */             }                                                                                                           // 0.0
/*517 */             for (count = 0; get_bits_count(&gb) <= size - nb_bits*avctx->channels && count < 4095; count++) {           // 0.0
/*518 */                 int i;                                                                                                  // 0.0
/*519 */                 for (i = 0; i < avctx->channels; i++) {                                                                 // 0.0
/*520 */                     // similar to IMA adpcm                                                                             // 0.0
/*521 */                     int delta = get_bits(&gb, nb_bits);                                                                 // 0.0
/*522 */                     int step = ff_adpcm_step_table[c->status[i].step_index];                                            // 0.0
/*523 */                     long vpdiff = 0; // vpdiff = (delta+0.5)*step/4                                                     // 0.0
/*524 */                     int k = k0;                                                                                         // 0.0
/*525 */                     do {                                                                                                // 0.0
/*526 */                         if (delta & k)                                                                                  // 0.0
/*527 */                             vpdiff += step;                                                                             // 0.0
/*528 */                         step >>= 1;                                                                                     // 0.0
/*529 */                         k >>= 1;                                                                                        // 0.0
/*530 */                     } while(k);                                                                                         // 0.0
/*531 */                     vpdiff += step;                                                                                     // 0.0
/*532 */                     if (delta & signmask)                                                                               // 0.0
/*533 */                         c->status[i].predictor -= vpdiff;                                                               // 0.0
/*534 */                     else                                                                                                // 0.0
/*535 */                         c->status[i].predictor += vpdiff;                                                               // 0.0
/*536 */                     c->status[i].step_index += table[delta & (~signmask)];                                              // 0.0
/*537 */                     c->status[i].step_index = av_clip(c->status[i].step_index, 0, 88);                                  // 0.0
/*538 */                     c->status[i].predictor = av_clip_int16(c->status[i].predictor);                                     // 0.0
/*539 */                     *samples++ = c->status[i].predictor;                                                                // 0.0
/*540 */                 }                                                                                                       // 0.0
/*541 */             }                                                                                                           // 0.0
/*542 */         }                                                                                                               // 0.0
/*543 */         src += buf_size;                                                                                                // 0.0
/*544 */         break;                                                                                                          // 0.0
/*545 */     }                                                                                                                   // 0.0
/*546 */     case CODEC_ID_ADPCM_YAMAHA:                                                                                         // 0.0
/*547 */         for (n = nb_samples >> (1 - st); n > 0; n--, src++) {                                                           // 0.0
/*548 */             uint8_t v = *src;                                                                                           // 0.0
/*549 */             *samples++ = adpcm_yamaha_expand_nibble(&c->status[0 ], v & 0x0F);                                          // 0.0
/*550 */             *samples++ = adpcm_yamaha_expand_nibble(&c->status[st], v >> 4  );                                          // 0.0
/*551 */         }                                                                                                               // 0.0
/*552 */         break;                                                                                                          // 0.0
/*553 */     case CODEC_ID_ADPCM_THP:                                                                                            // 0.0
/*554 */     {                                                                                                                   // 0.0
/*555 */         int table[2][16];                                                                                               // 0.0
/*556 */         int prev[2][2];                                                                                                 // 0.0
/*557 */         int ch;                                                                                                         // 0.0
/*558 */         src += 4; // skip channel size                                                                                  // 0.0
/*559 */         src += 4; // skip number of samples (already read)                                                              // 0.0
/*560 */         for (i = 0; i < 32; i++)                                                                                        // 0.0
/*561 */             table[0][i] = (int16_t)bytestream_get_be16(&src);                                                           // 0.0
/*562 */         /* Initialize the previous sample.  */                                                                          // 0.0
/*563 */         for (i = 0; i < 4; i++)                                                                                         // 0.0
/*564 */             prev[0][i] = (int16_t)bytestream_get_be16(&src);                                                            // 0.0
/*565 */         for (ch = 0; ch <= st; ch++) {                                                                                  // 0.0
/*566 */             samples = (short *)c->frame.data[0] + ch;                                                                   // 0.0
/*567 */             /* Read in every sample for this channel.  */                                                               // 0.0
/*568 */             for (i = 0; i < nb_samples / 14; i++) {                                                                     // 0.0
/*569 */                 int index = (*src >> 4) & 7;                                                                            // 0.0
/*570 */                 unsigned int exp = *src++ & 15;                                                                         // 0.0
/*571 */                 int factor1 = table[ch][index * 2];                                                                     // 0.0
/*572 */                 int factor2 = table[ch][index * 2 + 1];                                                                 // 0.0
/*573 */                 /* Decode 14 samples.  */                                                                               // 0.0
/*574 */                 for (n = 0; n < 14; n++) {                                                                              // 0.0
/*575 */                     int32_t sampledat;                                                                                  // 0.0
/*576 */                     if(n&1) sampledat = sign_extend(*src++, 4);                                                         // 0.0
/*577 */                     else    sampledat = sign_extend(*src >> 4, 4);                                                      // 0.0
/*578 */                     sampledat = ((prev[ch][0]*factor1                                                                   // 0.0
/*579 */                                 + prev[ch][1]*factor2) >> 11) + (sampledat << exp);                                     // 0.0
/*580 */                     *samples = av_clip_int16(sampledat);                                                                // 0.0
/*581 */                     prev[ch][1] = prev[ch][0];                                                                          // 0.0
/*582 */                     prev[ch][0] = *samples++;                                                                           // 0.0
/*583 */                     /* In case of stereo, skip one sample, this sample                                                  // 0.0
/*584 */                        is for the other channel.  */                                                                    // 0.0
/*585 */                     samples += st;                                                                                      // 0.0
/*586 */                 }                                                                                                       // 0.0
/*587 */             }                                                                                                           // 0.0
/*588 */         }                                                                                                               // 0.0
/*589 */         break;                                                                                                          // 0.0
/*590 */     }                                                                                                                   // 0.0
/*591 */     default:                                                                                                            // 0.0
/*592 */         return -1;                                                                                                      // 0.0
/*593 */     }                                                                                                                   // 0.0
/*594 */     *got_frame_ptr   = 1;                                                                                               // 0.0
/*595 */     *(AVFrame *)data = c->frame;                                                                                        // 0.0
/*596 */     return src - buf;                                                                                                   // 0.0
/*597 */ }                                                                                                                       // 0.0
